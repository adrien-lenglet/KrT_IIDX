#pragma once

#include <vector>
#include <string>
#include <map>
#include "../Subtile.hpp"
#include "Shader.hpp"
#include "Image.hpp"
#include "Swapchain.hpp"
#include "Semaphore.hpp"
#include "Fence.hpp"
#include "Buffer.hpp"
#include "Queue.hpp"
#include "Event/Observer.hpp"

namespace Subtile {

class System
{
public:
	class Input : public Event::Observer
	{
	public:
		virtual void update(void) override = 0;

		virtual const std::string& getName(void) const = 0;
		virtual double getActivity(void) const = 0;

		class Analog;
		class Button;
		class Keyboard;
	};

	virtual ~System(void) = default;

	virtual void scanInputs(void) = 0;
	virtual const std::map<std::string, System::Input&>& getInputs(void) = 0;

	virtual std::unique_ptr<RenderPass> createRenderPass(rs::RenderPass &renderpass) = 0;
	virtual std::unique_ptr<Shader> createShader(rs::Shader &shader) = 0;
	virtual std::unique_ptr<Shader::DescriptorSet::Layout> createDescriptorSetLayout(const Shader::DescriptorSet::Layout::Description &desc) = 0;
	virtual std::unique_ptr<Image> createImage(Image::Type type, Format format, Image::Sample sample, const svec3 &extent, size_t layers, Image::Usage usage, Queue &queue) = 0;
	virtual std::unique_ptr<Swapchain> createSwapchain(const svec2 &extent, Image::Usage usage, Queue &queue) = 0;
	virtual std::unique_ptr<Semaphore> createSemaphore(void) = 0;
	virtual std::unique_ptr<Fence> createFence(bool isSignaled) = 0;
	virtual std::unique_ptr<Buffer> createBuffer(size_t size, Buffer::Location location, Buffer::Usage usage, Queue &queue) = 0;
	virtual std::unique_ptr<Model> createModel(Buffer &vertexBuffer, size_t vertexCount) = 0;
	virtual std::unique_ptr<Model> createModelIndexed(Buffer &vertexBuffer, Buffer &indexBuffer, Model::IndexType indexType, size_t indexCount) = 0;

	virtual std::unique_ptr<Queue> getQueue(Queue::Flag flags, size_t index) = 0;
};

class System::Input::Analog : public System::Input
{
public:
	virtual double getState(void) const = 0;
};

class System::Input::Button : public System::Input
{
public:
	virtual bool getState(void) const = 0;
};

class System::Input::Keyboard : public System::Input
{
public:
	virtual std::vector<uint32_t> poll(void) const = 0;
};

}