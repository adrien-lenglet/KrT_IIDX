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
		class WeakElement;
		template <typename T>
		class StrongElement;

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

	template <typename Element>
	class Storage
	{
		using UniqueSet = util::unique_set<Element>;

	public:
		Storage(void)
		{
		}
		~Storage(void)
		{
		}

		class iterator : public UniqueSet::iterator
		{
			using unique_set_iterator = typename UniqueSet::iterator;

		public:
			using difference_type = std::ptrdiff_t;
			using value_type = typename Element::value_type;
			using pointer = value_type*;
			using reference = value_type&;
			using iterator_category = std::bidirectional_iterator_tag;

			iterator(const unique_set_iterator &it) :
				UniqueSet::iterator(it)
			{
			}
			~iterator(void)
			{
			}

			reference operator*(void) const
			{
				return UniqueSet::iterator::operator*();
			}
		};

		iterator begin(void)
		{
			return m_elements.begin();
		}

		iterator end(void)
		{
			return m_elements.end();
		}

	protected:
		friend Element;
		UniqueSet m_elements;

		void destroyElement(Element &elem)
		{
			auto got = m_elements.find(elem);

			if (got == m_elements.end())
				throw std::runtime_error("Can't destroy element");
			m_elements.erase(got);
		}
	};

	template <typename T>
	class Weak;
	template <typename T>
	class Source::WeakElement : public Source
	{
	public:
		using value_type = T;

		template <typename ...Args>
		WeakElement(Weak<T> &socket, Args &&...args) :
			m_socket(socket),
			m_obj(std::forward<Args>(args)...)
		{
		}
		~WeakElement(void)
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

	template <typename T>
	class Weak : public Storage<Source::WeakElement<T>>
	{
	public:
		Weak(void)
		{
		}
		~Weak(void)
		{
			if (this->m_elements.size() > 0)
				util::fatal_throw([](){
					throw std::runtime_error("Elements still in weak socket");
				});
		}

		template <typename ...Args>
		void bind(Dependency::Socket &socket, Args &&...args)
		{
			socket.add(this->m_elements.emplace(*this, std::forward<Args>(args)...));
		}
	};

	template <typename T>
	class Strong;
	template <typename T>
	class Source::StrongElement : public Source
	{
	public:
		using value_type = T;

		template <typename ...Args>
		StrongElement(Strong<T> &socket, Dependency::Socket &depSocket, Args &&...args) :
			m_socket(socket),
			m_dependency(depSocket, depSocket.add(*this)),
			m_obj(std::forward<Args>(args)...)
		{
		}
		~StrongElement(void)
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

	template <typename T>
	class Strong : public Storage<Source::StrongElement<T>>
	{
	public:
		class Multiple;
		class MutipleElement : public Source
		{
		public:
			using value_type = T;

			template <typename ...Args>
			MutipleElement(Multiple &socket, Args &&...args) :
				m_socket(socket),
				m_obj(std::forward<Args>(args)...)
			{
			}
			~MutipleElement(void)
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
			Multiple &m_socket;
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

		class Multiple : public Storage<MutipleElement>
		{
		public:
			Multiple(void)
			{
			}
			~Multiple(void)
			{
			}

			template <typename ...Args>
			void bind(const std::vector<std::reference_wrapper<Dependency::Socket>> &sockets, Args &&...args)
			{
				auto &el = this->m_elements.emplace(*this, std::forward<Args>(args)...);

				for (auto &s : sockets)
					el.addDep(s, s.get().add(el));
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
			this->m_elements.emplace(*this, socket, std::forward<Args>(args)...);
		}
	};
};

}