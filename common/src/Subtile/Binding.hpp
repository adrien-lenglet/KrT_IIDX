#pragma once

#include <optional>
#include "util.hpp"

namespace Subtile {

class Binding
{
public:
	virtual ~Binding(void) = 0;

	class Dependency;

private:
	class Source
	{
	public:
		template <typename T, bool emptyCallback>
		class WeakElement;
		template <typename T, bool emptyCallback>
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

public:
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
			friend Socket;
			Socket &m_socket;
			Dependency *m_dependency;
		};

	public:
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

	template <typename T, bool emptyCallback = false>
	class Strong;

private:
	template <typename Element>
	class StorageBase
	{
		using UniqueSet = util::unique_set<Element>;

	public:
		StorageBase(void)
		{
		}
		~StorageBase(void)
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

		auto size(void) const
		{
			return m_elements.size();
		}

	protected:
		UniqueSet m_elements;
	};

	template <typename Element>
	class StorageBasic : public StorageBase<Element>
	{
	public:
		StorageBasic(void)
		{
		}
		~StorageBasic(void)
		{
		}

	protected:
		friend Element;

		void destroyElement(Element &elem)
		{
			auto got = this->m_elements.find(elem);

			if (got == this->m_elements.end())
				throw std::runtime_error("Can't destroy element");
			this->m_elements.erase(got);
		}
	};

	template <typename Element>
	class StorageEmptyCallback : public StorageBase<Element>
	{
	public:
		using callback_type = std::function<void (void)>;

		StorageEmptyCallback(const callback_type &cb) :
			m_callback(cb)
		{
		}
		~StorageEmptyCallback(void)
		{
		}

	protected:
		friend Element;
		const callback_type m_callback;

		void destroyElement(Element &elem)
		{
			auto got = this->m_elements.find(elem);

			if (got == this->m_elements.end())
				throw std::runtime_error("Can't destroy element");
			this->m_elements.erase(got);
			if (this->m_elements.size() == 0)
				m_callback();
		}
	};

	template <typename Element, bool emptyCallback = false>
	class Storage : public std::conditional<emptyCallback, StorageEmptyCallback<Element>, StorageBasic<Element>>::type
	{
		using InheritedStorage = typename std::conditional<emptyCallback, StorageEmptyCallback<Element>, StorageBasic<Element>>::type;

	public:
		template <typename ...Args>
		Storage(Args &&...args) :
			InheritedStorage(std::forward<Args>(args)...)
		{
		}
		~Storage(void)
		{
		}
	};

public:
	template <typename T, bool emptyCallback = false>
	class Weak;

	template <typename T, bool emptyCallback>
	class Weak : public Storage<Source::WeakElement<T, emptyCallback>, emptyCallback>
	{
	public:
		template <typename ...Args>
		Weak(Args &&...args) :
			Storage<Source::WeakElement<T, emptyCallback>, emptyCallback>(std::forward<Args>(args)...)
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

public:
	template <typename T, bool emptyCallback>
	class Strong : public Storage<Source::StrongElement<T, emptyCallback>, emptyCallback>
	{
	public:
		class Multiple;

	private:
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
			friend Multiple;
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

	public:
		class Multiple : public Storage<MutipleElement, emptyCallback>
		{
		public:
			template <typename ...Args>
			Multiple(Args &&...args) :
				Storage<MutipleElement, emptyCallback>(std::forward<Args>(args)...)
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

		template <typename ...Args>
		Strong(Args &&...args) :
			Storage<Source::StrongElement<T, emptyCallback>, emptyCallback>(std::forward<Args>(args)...)
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

template <typename T, bool emptyCallback>
class Binding::Source::WeakElement : public Source
{
public:
	using value_type = T;

	template <typename ...Args>
	WeakElement(Weak<T, emptyCallback> &socket, Args &&...args) :
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
	Weak<T, emptyCallback> &m_socket;
	T m_obj;

	void depDestroyed(Dependency&) override
	{
		m_socket.destroyElement(*this);
	}
};

template <typename T, bool emptyCallback>
class Binding::Source::StrongElement : public Source
{
public:
	using value_type = T;

	template <typename ...Args>
	StrongElement(Strong<T, emptyCallback> &socket, Dependency::Socket &depSocket, Args &&...args) :
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
	friend Strong<T, emptyCallback>;
	Strong<T, emptyCallback> &m_socket;
	Dependency::Point m_dependency;
	T m_obj;

	void depDestroyed(Dependency&) override
	{
		m_dependency.clear();
		m_socket.destroyElement(*this);
	}
};

}