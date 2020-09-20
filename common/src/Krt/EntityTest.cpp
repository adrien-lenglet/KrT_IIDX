#include <iostream>
#include "EntityTest.hpp"
#include "ModelLoader.hpp"
#include <glm/gtx/transform.hpp>
#include "stb_image.h"
#include <cstring>

namespace Krt {

EntityTest::EntityTest(void) :
	m_shader(world.instance.device.load(res.shaders().diffuse())),
	m_material(m_shader.material(world.instance.graphics)),
	m_object(m_shader.object(world.instance.graphics)),
	m_thick_shader(world.instance.device.load(res.shaders().depth_max())),
	m_thick_object(m_thick_shader.object(world.instance.graphics)),
	m_model_buffer(createModelBuffer()),
	m_model(world.instance.device.model(m_model_buffer)),
	m_model_albedo(createModelAlbedo()),
	m_sampler(world.instance.device.sampler(sb::Filter::Nearest, sb::Filter::Nearest, sb::Sampler::AddressMode::MirroredRepeat, sb::BorderColor::FloatOpaqueWhite, std::nullopt, sb::Sampler::MipmapMode::Linear, 0.0f, 64.0f, 0.0f, std::nullopt))
{
	m_material.counter = 0;

	m_material.albedo.bind(m_sampler, m_model_albedo, sb::Image::Layout::ShaderReadOnlyOptimal);

	/*bind(world.events.system.input.button.pressed("quit"), [this](){
		//std::cout << "quit pressed" << std::endl;
		trigger(just_died, 14.2);
	});

	bind(world.events.system.input.button.released("quit"), [this](){
		//std::cout << "quit released" << std::endl;
		trigger(got_score, 7.92);
	});*/

	bind(world.render, m_shader.render(m_model, world.render.camera, m_material, m_object));
	bind(world.render_thick, m_thick_shader.render(m_model, world.render.camera, m_thick_object));

	bind(world.events.update, [this](auto &time){
		m_material.counter++;
		if (m_material.counter > 256) {
			m_material.counter = 0;
		}
		world.instance.cur_img_res->uploadDescSet(m_material);

		auto &sp = *world.instance.surface->buttonsId().at("KB_SPACE");
		sp.update();
		if (sp.released())
			do_rot = !do_rot;

		if (do_rot)
			m_angle += time / 16.0;
		auto mat = glm::rotate((float)m_angle, glm::normalize(glm::vec3(1.0, 1.0, 1.0)));
		m_object.model_world = mat * glm::scale(glm::vec3(100.0));
		m_object.model_world_normal = mat;
		for (size_t i = 0; i < 3; i++)
			m_object.model_world_normal[3][i] = 0.0f;
		world.instance.cur_img_res->uploadDescSet(m_object);

		m_thick_object.model_world = m_object.model_world;
		world.instance.cur_img_res->uploadDescSet(m_thick_object);
	});
}

EntityTest::~EntityTest(void)
{
}

decltype(EntityTest::m_model_buffer) EntityTest::createModelBuffer(void)
{
	/*std::vector<decltype(m_model_buffer)::value_type> values;

	for (size_t i = 0; i < 100000; i++) {
		decltype(m_model_buffer)::value_type tri[3];
		glm::vec3 points[3];
		for (size_t i = 0; i < 3; i++)
			for (size_t j = 0; j < 3; j++) {
				points[i][j] = world.srandf() * 5.0;
				tri[i].pos[j] = points[i][j];
			}
		glm::vec3 normal = glm::normalize(glm::cross(points[1] - points[0], points[2] - points[0]));
		for (size_t i = 0; i < 3; i++)
			tri[i].normal = normal;
		for (size_t i = 0; i < 3; i++)
			for (size_t j = 0; j < 2; j++)
				tri[i].uv[j] = world.urandf();
		for (size_t i = 0; i < 3; i++)
			values.emplace_back(tri[i]);
	}*/
	auto values_sb = res.models().map().vokselia_spawn().getCompiled().read();
	std::vector<decltype(m_model_buffer)::value_type> values;
	if constexpr (sizeof(decltype(values)::value_type) == sizeof(decltype(values_sb)::value_type)) {
		values.resize(values_sb.size());
		std::memcpy(values.data(), values_sb.data(), values_sb.size() * sizeof(decltype(values)::value_type));
	} else {
		values.reserve(values_sb.size());
		for (auto &vsb : values_sb) {
			decltype(values)::value_type v;
			v.pos = vsb.pos;
			v.normal = vsb.normal;
			v.uv = vsb.uv;
			values.emplace_back(v);
		}
	}
	auto res = world.instance.device.vertexBuffer<decltype(m_model_buffer)::value_type>(values.size(), world.instance.graphics);
	world.instance.cur_img_res->copyBuffer(values, res);
	return res;
}

decltype(EntityTest::m_model_albedo) EntityTest::createModelAlbedo(void)
{
	int w, h, channels;
	res.models().map().vokselia_spawn_albedo().beforeRead();
	auto path = "res/models/map/vokselia_spawn_albedo.png";
	auto pixels = stbi_load(path, &w, &h, &channels, STBI_rgb_alpha);
	if (pixels == nullptr)
		throw std::runtime_error(std::string("Can't load texture: ") + path);
	if (channels != 4)
		throw std::runtime_error(std::string("Corrupted texture: ") + path);

	auto res = world.instance.device.image2D(sb::Format::rgba8_srgb, {w, h}, 1, sb::Image::Usage::TransferDst | sb::Image::Usage::Sampled, world.instance.graphics);

	auto cmd = world.instance.m_transfer_pool.primary();

	cmd.record([&](auto &cmd){
		cmd.imageMemoryBarrier(sb::PipelineStage::BottomOfPipe, sb::PipelineStage::Transfer, {},
			sb::Access::None, sb::Access::TransferWrite,
			sb::Image::Layout::Undefined, sb::Image::Layout::TransferDstOptimal, res);
	});

	world.instance.graphics.submit(util::empty, cmd, util::empty);
	world.instance.graphics.waitIdle();

	world.instance.cur_img_res->copyDataToImage(pixels, channels, res, sb::Image::Layout::TransferDstOptimal, res.blitRegion({0, 0}, res.extent()));

	world.instance.cur_img_res->transfer.imageMemoryBarrier(sb::PipelineStage::Transfer, sb::PipelineStage::BottomOfPipe, {},
		sb::Access::TransferWrite, sb::Access::MemoryRead,
		sb::Image::Layout::TransferDstOptimal, sb::Image::Layout::ShaderReadOnlyOptimal, res);

	stbi_image_free(pixels);
	return res;
}

}