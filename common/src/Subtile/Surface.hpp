#pragma once

#include <memory>
#include <optional>
#include <vector>
#include <map>
#include "Queue.hpp"
#include "Input.hpp"
#include "Monitor.hpp"

namespace Subtile {

class Surface
{
public:
	virtual ~Surface(void) = default;

	virtual svec2 getExtent(void) const = 0;
	virtual std::optional<svec2> isResized(void) const = 0;
	virtual bool shouldClose(void) const = 0;
	virtual void setMonitor(Monitor &monitor, const Monitor::VideoMode &videoMode) = 0;
	virtual void setWindowed(void) = 0;
	virtual const std::vector<Input*>& getInputs(void) const = 0;
	virtual const std::map<std::string, Input*>& getInputsId(void) const = 0;
	virtual const std::vector<Button*>& getButtons(void) const = 0;
	virtual const std::map<std::string, Button*>& getButtonsId(void) const = 0;
	virtual const std::vector<Analog*>& getAnalogs(void) const = 0;
	virtual const std::map<std::string, Analog*>& getAnalogsId(void) const = 0;
	virtual glm::dvec2 cursor(void) const = 0;
	virtual void cursorMode(bool show) = 0;

	class Handle
	{
	public:
		Handle(std::unique_ptr<Surface> &&surface) :
			m_surface(std::move(surface))
		{
		}

		auto extent(void) const
		{
			return m_surface->getExtent();
		}

		auto resized(void) const
		{
			return m_surface->isResized();
		}

		bool shouldClose(void) const
		{
			return m_surface->shouldClose();
		}

		void setMonitor(Monitor &monitor, const Monitor::VideoMode &videoMode)
		{
			return m_surface->setMonitor(monitor, videoMode);
		}

		void setWindowed(void)
		{
			return m_surface->setWindowed();
		}

		auto& inputs(void) const
		{
			return m_surface->getInputs();
		}
		auto& inputsId(void) const
		{
			return m_surface->getInputsId();
		}

		auto& buttons(void) const
		{
			return m_surface->getButtons();
		}
		auto& buttonsId(void) const
		{
			return m_surface->getButtonsId();
		}

		auto& analogs(void) const
		{
			return m_surface->getAnalogs();
		}
		auto& analogsId(void) const
		{
			return m_surface->getAnalogsId();
		}

		auto cursor(void) const
		{
			return m_surface->cursor();
		}

		void cursorMode(bool show)
		{
			m_surface->cursorMode(show);
		}

		operator Surface&(void)
		{
			return *m_surface;
		}

	private:
		std::unique_ptr<Surface> m_surface;
	};
};

}