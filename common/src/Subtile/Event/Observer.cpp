#include "Observer.hpp"
#include "Subtile/scp.hpp"

namespace Subtile {
namespace Event {

root_scc(Observer::Cluster,
	void scp()update(void)
	{
		for (auto &o : m_observers)
			o.get().update();
	}

	void scp()add(Observer &observer)
	{
		m_observers.emplace_back(observer);
	}

	scc(Optimized,
		void scp()update(void)
		{
			for (auto &o : m_observers)
				o.first.get().update();
		}

		void scp()add(Observer &observer)
		{
			m_observers[observer]++;
		}

		void scp()remove(Observer &observer)
		{
			auto got = m_observers.find(observer);

			if (got == m_observers.end())
				throw std::runtime_error("No instance of that observer in the cluster");
			got->second--;
			if (got->second == 0)
				m_observers.erase(got);
		}
	)
)

}
}