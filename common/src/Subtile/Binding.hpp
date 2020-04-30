#pragma once

#include <optional>
#include "util.hpp"

namespace Subtile {

class Binding
{
public:
	virtual ~Binding(void) = 0;

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
		class Point;
		class Socket
		{
		public:
			Socket(void)
			{
			}
			~Socket(void)
			{
				for (auto &d : m_deps)
					d.destroyBound();
			}

			Dependency& add(Source &source)
			{
				return m_deps.emplace(source);
			}

		private:
			friend Point;
			util::unique_set<Dependency> m_deps;

			void destroy(Dependency &dep)
			{
				auto got = m_deps.find(dep);

				if (got == m_deps.end())
					throw std::runtime_error("Can't destroy dependency");
				m_deps.erase(got);
			}
		};

		class Point
		{
		public:
			Point(Socket &socket, Dependency &dependency) :
				m_socket(socket),
				m_dependency(&dependency)
			{
			}
			~Point(void)
			{
			}

			Dependency& getDependency(void)
			{
				if (m_dependency == nullptr)
					throw std::runtime_error("Empty dependency, can't resolve");
				return *m_dependency;
			}

			void destroyBound(void)
			{
				if (m_dependency)
					m_socket.destroy(*m_dependency);
			}

			void clear(void)
			{
				m_dependency = nullptr;
			}

		private:
			Socket &m_socket;
			Dependency *m_dependency;
		};

		Dependency(Source &source) :
			m_source(source)
		{
		}
		~Dependency(void)
		{
		}

		void destroyBound(void)
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

	template <typename T>
	class Source::Strong
	{
	public:
		class Multiple
		{
		public:
			class Element : public Source
			{
			public:
				template <typename ...Args>
				Element(Strong<T> &socket, Args &&...args) :
					m_socket(socket),
					m_obj(std::forward<Args>(args)...)
				{
				}
				~Element(void)
				{
					for (auto &d : m_dependencies)
						d.destroyBound();
				}

				operator T&(void)
				{
					return m_obj;
				}

			private:
				friend Strong<T>;
				Strong<T> &m_socket;
				util::unique_set<Dependency::Point> m_dependencies;
				T m_obj;

				void addDep(Dependency::Socket &socket, Dependency &dep)
				{
					m_dependencies.emplace(socket, dep);
				}

				void depDestroyed(Dependency &dep) override
				{
					for (auto &d : m_dependencies)
						if (&d.getDependency() != &dep)
							d.destroyBound();
					m_dependencies.clear();
					m_socket.destroyElement(*this);
				}
			};

			Multiple(void)
			{
			}
			~Multiple(void)
			{
			}

			template <typename ...Args>
			void bind(const std::vector<std::reference_wrapper<Dependency::Socket>> &sockets, Args &&...args)
			{
				auto &el = m_elements.emplace(*this, std::forward<Args>(args)...);

				for (auto &s : sockets)
					el.addDep(s, s.get().add(el));
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

		class Element : public Source
		{
		public:
			template <typename ...Args>
			Element(Strong<T> &socket, Dependency::Socket &depSocket, Args &&...args) :
				m_socket(socket),
				m_dependency(depSocket, depSocket.add(*this)),
				m_obj(std::forward<Args>(args)...)
			{
			}
			~Element(void)
			{
				m_dependency.destroyBound();
			}

			operator T&(void)
			{
				return m_obj;
			}

		private:
			friend Strong<T>;
			Strong<T> &m_socket;
			Dependency::Point m_dependency;
			T m_obj;

			void depDestroyed(Dependency&) override
			{
				m_dependency.clear();
				m_socket.destroyElement(*this);
			}
		};

		Strong(void)
		{
		}
		~Strong(void)
		{
		}

		template <typename ...Args>
		void bind(Dependency::Socket &socket, Args &&...args)
		{
			m_elements.emplace(*this, socket, std::forward<Args>(args)...);
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

}