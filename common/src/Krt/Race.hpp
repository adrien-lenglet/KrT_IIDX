#include "Subtile/Screen/Layout.hpp"
#include "Track.hpp"

namespace Krt {

class Race;

/*class PlayerScreen : public Subtile::Screen::Subsection
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

class Ui : public Subtile::Screen::Subsection
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

class Race : public Subtile::Session<Race>
{
public:
	Race(void) :
		m_unique_track(createWorld<Track>()),
		m_track(*m_unique_track),
		m_layout(createLayout<Screen::Class>())
	{
		bind(m_track.done(), [this](){
			done();
		});
	}
	~Race(void) override
	{
	}

	Subtile::Screen::Layout& getScreenLayout(void) override
	{
		return *m_layout;
	}

	class Screen : public Layout<Screen>
	{
	public:
		Screen(void) = default;
		~Screen(void) override = default;

	private:
		class Fx : public Subsection<Fx>
		{
		public:
			Fx(void) :
				Subsection<Fx>(*(Subtile::Camera*)nullptr)
			{
			}
			~Fx(void) override = default;
		};

		Fx::Class fx;
	};

private:
	std::unique_ptr<Track> m_unique_track;
	Track &m_track;
	std::unique_ptr<Subtile::Screen::Layout> m_layout;
};

}