#include "EntityTest.hpp"
#include "res.hpp"
#include "../../res/shaders/diffuse.hpp"

#include <iostream>

#include "Subtile/Cache.hpp"

namespace Krt {

class IntCache : public sb::Cache<std::tuple<size_t, double>, int>
{
public:
	IntCache(void) = default;
	~IntCache(void) = default;

protected:
	int build(const size_t &s, const double &d) const override
	{
		return s + d;
	}
};

class DummyClass
{
public:
	DummyClass(void)
	{
		std::cout << "const" << std::endl;
	}
	~DummyClass(void)
	{
		std::cout << "dest" << std::endl;
	}
};

class DummyCache : public sb::Cache<std::tuple<>, DummyClass>
{
public:
	DummyCache(void) = default;
	~DummyCache(void) = default;

protected:
	DummyClass build(void) const override
	{
		return DummyClass();
	}
};

EntityTest::EntityTest(void) :
	entity1(add<EntityTest2>()),
	entity2(add<EntityTest2>())
{
	bind(world.events.system.input.button.pressed("quit"), [this](){
		std::cout << "quit pressed" << std::endl;
		trigger(just_died, 14.2);
	});

	bind(world.events.system.input.button.released("quit"), [this](){
		std::cout << "quit released" << std::endl;
		trigger(got_score, 7.92);
	});

	bind(world.events.update, [this](auto &t){
		pos.x += t;
		transformed();
	});

	res.models().npc().gordon_diff();

	//auto &npc = res.models().npc();
	//bind(world.render, res.shaders().diffuse()(npc.gordon(), npc.gordon_diff());

	/*IntCache icache;

	const auto l = icache.resolve(12, 6);
	const auto m = icache.resolve(60, 2.5);
	std::cout << *l << std::endl;
	std::cout << *m << std::endl;

	DummyCache cache;

	auto a = cache.resolve();
	auto b = cache.resolve();

	util::vector<DummyClass> vec;

	for (size_t i = 0; i < 64; i++)
		vec.emplace_back();*/
}

EntityTest::~EntityTest(void)
{
}

}