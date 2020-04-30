#pragma once

#include "util.hpp"

namespace Subtile {

class Binding
{
public:
	virtual ~Binding(void) = 0;

	//class Socket;

	class Dependency;
	class Source
	{
	public:
		template <typename T>
		class Weak;
		template <typename T>
		class Strong;

		Source(void)
		{
		}
		virtual ~Source(void)
		{
		}

	private:
		friend Dependency;
		virtual void depDestroyed(Dependency &dep) = 0;
	};

	class Dependency
	{
	public:
		class Socket
		{
		public:
			Socket(void)
			{
			}
			~Socket(void)
			{
			}

			void add(Source &source)
			{
				m_deps.emplace(source);
			}

		private:
			util::unique_set<Dependency> m_deps;
		};

		Dependency(Source &source) :
			m_source(source)
		{
		}
		~Dependency(void)
		{
			m_source.depDestroyed(*this);
		}

	private:
		Source &m_source;
	};

	template <typename T>
	class Source::Weak
	{
	public:
		class Element : public Source
		{
		public:
			template <typename ...Args>
			Element(Weak<T> &socket, Args &&...args) :
				m_socket(socket),
				m_obj(std::forward<Args>(args)...)
			{
			}
			~Element(void)
			{
			}

			operator T&(void)
			{
				return m_obj;
			}

		private:
			Weak<T> &m_socket;
			T m_obj;

			void depDestroyed(Dependency&) override
			{
				m_socket.destroyElement(*this);
			}
		};

		Weak(void)
		{
		}
		~Weak(void)
		{
			if (m_elements.size() > 0)
				util::fatal_throw([](){
					throw std::runtime_error("Elements still in weak socket");
				});
		}

		template <typename ...Args>
		void bind(Dependency::Socket &socket, Args &&...args)
		{
			socket.add(m_elements.emplace(*this, std::forward<Args>(args)...));
		}

	private:
		friend Element;
		util::unique_set<Element> m_elements;

		void destroyElement(Element &elem)
		{
			auto got = m_elements.find(elem);

			if (got == m_elements.end())
				throw std::runtime_error("Can't destroy element");
			m_elements.erase(got);
		}
	};
};

/*class Binding::Socket
{
public:
	Socket(void);
	~Socket(void);

private:
	//util::unique_set<Binding> m_bindings;
};*/

}

//#include "Binding/Source.hpp"
//#include "Binding/Dependency.hpp"