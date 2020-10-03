#pragma once

#include <memory>
#include <vector>

namespace Subtile {

class Monitor
{
public:
	virtual ~Monitor(void) = default;

	struct VideoMode
	{
		size_t width;
		size_t height;
		size_t refresh_rate;

		size_t red_bits;
		size_t green_bits;
		size_t blue_bits;
	};

	virtual const std::vector<VideoMode>& getVideoModes(void) const = 0;

	class Handle
	{
	public:
		Handle(std::unique_ptr<Monitor> &&monitor) :
			m_monitor(std::move(monitor))
		{
		}

		operator Monitor&(void) const
		{
			return *m_monitor;
		}

		auto& videoModes(void) const
		{
			return m_monitor->getVideoModes();
		}

	private:
		std::unique_ptr<Monitor> m_monitor;
	};
};

}