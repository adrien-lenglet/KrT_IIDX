#include "Subtile/Screen/Layout.hpp"
#include "Track.hpp"

namespace Krt {

class Race;

/*class PlayerScreen : public sb::Screen::Subsection
{
public:
	PlayerScreen(size_t pNum) :
		m_p_num(pNum)
	{
	}
	~PlayerScreen(void) = default;

private:
	size_t m_p_num;
};

class Ui : public sb::Screen::Subsection
{
public:
	Ui(void) :
		p1(0),
		p2(1)
	{
	}
	~Ui(void) = default;

private:
	PlayerScreen p1;
	PlayerScreen p2;
};*/

class Race : public sb::Session<Race>
{
public:
	Race(void) :
		m_unique_track(createWorld<Track>()),
		m_track(*m_unique_track),
		camera(m_track.camera),
		m_layout(createLayout<Screen>())
	{
		bind(m_track.done, [this](){
			done();
		});
	}
	~Race(void) override
	{
	}

	sb::Screen::Layout& getScreenLayout(void) override
	{
		return *m_layout;
	}

	class Screen : public Layout
	{
	public:
		Screen(void) = default;
		~Screen(void) override = default;

	private:
		class Fx : public Subsection
		{
		public:
			Fx(void) :
				Subsection([](auto &r) -> auto& { return r.camera; })
			{
			}
			~Fx(void) override = default;
		};

		Class<Fx> fx;
	};

private:
	std::unique_ptr<Track> m_unique_track;
	Track &m_track;
public:
	sb::Camera &camera;

private:
	std::unique_ptr<sb::Screen::Layout> m_layout;
};

}