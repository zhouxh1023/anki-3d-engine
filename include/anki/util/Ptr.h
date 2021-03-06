// Copyright (C) 2009-2015, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#ifndef ANKI_UTIL_PTR_H
#define ANKI_UTIL_PTR_H

#include "anki/util/Assert.h"
#include "anki/util/StdTypes.h"

namespace anki {

/// @addtogroup util_memory
/// @{

/// Common code for all pointers
template<typename T>
class PtrBase
{
	template<typename Y>
	friend class PtrBase;

public:
	/// Dereference
	T& operator*() const
	{
		ANKI_ASSERT(m_ptr);
		return *m_ptr;
	}

	/// Dereference
	T* operator->() const
	{
		ANKI_ASSERT(m_ptr);
		return m_ptr;
	}

	T& get()
	{
		ANKI_ASSERT(m_ptr);
		return *m_ptr;
	}

	const T& get() const
	{
		ANKI_ASSERT(m_ptr);
		return *m_ptr;
	}

	Bool isCreated() const
	{
		return m_ptr != nullptr;
	}

	/// @name Compare operators
	/// @{
	operator bool() const
	{
    	return isCreated();
	}

	Bool operator==(const PtrBase& other) const
	{
		return m_ptr == other.m_ptr;
	}

	Bool operator!=(const PtrBase& other) const
	{
		return m_ptr != other.m_ptr;
	}

	Bool operator<(const PtrBase& other) const
	{
		return m_ptr < other.m_ptr;
	}

	Bool operator<=(const PtrBase& other) const
	{
		return m_ptr <= other.m_ptr;
	}

	Bool operator>(const PtrBase& other) const
	{
		return m_ptr > other.m_ptr;
	}

	Bool operator>=(const PtrBase& other) const
	{
		return m_ptr >= other.m_ptr;
	}
	/// @}

protected:
	T* m_ptr;

	PtrBase()
	:	m_ptr(nullptr)
	{}

	PtrBase(T* ptr)
	:	m_ptr(ptr)
	{}
};

/// A simple template class to wrap simple pointers
template<typename T>
class Ptr: public PtrBase<T>
{
public:
	using Base = PtrBase<T>;

	Ptr()
	:	Base()
	{}

	Ptr(T* ptr)
	:	Base(ptr)
	{}

	Ptr(const Ptr& other)
	:	Base(other.m_ptr)
	{}

	Ptr(Ptr&& other)
	:	Base(other.m_ptr)
	{
		other.m_ptr = nullptr;
	}

	/// Destroy.
	~Ptr()
	{
		Base::m_ptr = nullptr;
	}

	/// Copy.
	Ptr& operator=(const Ptr& other)
	{
		Base::m_ptr = other.m_ptr;
		return *this;
	}

	/// Move.
	Ptr& operator=(Ptr&& other)
	{
		Base::m_ptr = other.m_ptr;
		other.m_ptr = nullptr;
		return *this;
	}

	/// @name Arithmetic operators
	/// @{
	Ptr& operator++()
	{
		ANKI_ASSERT(Base::m_ptr);
		++Base::m_ptr;
		return *this;
	}

	Ptr& operator--()
	{
		ANKI_ASSERT(Base::m_ptr);
		--Base::m_ptr;
		return *this;
	}

	Ptr operator+(const Ptr& other) const
	{
		ANKI_ASSERT(Base::m_ptr);
		Ptr out(Base::m_ptr + other.m_ptr);
		return out;
	}

	Ptr& operator+=(const Ptr& other)
	{
		ANKI_ASSERT(Base::m_ptr);
		Base::m_ptr += other.m_ptr;
		return *this;
	}

	Ptr operator-(const Ptr& other) const
	{
		ANKI_ASSERT(Base::m_ptr);
		Ptr out(Base::m_ptr - other.m_ptr);
		return out;
	}

	Ptr& operator-=(const Ptr& other)
	{
		ANKI_ASSERT(Base::m_ptr);
		Base::m_ptr -= other.m_ptr;
		return *this;
	}
	/// @}
};

/// UniquePtr default deleter.
template<typename T>
class DefaultPtrDeleter
{
public:
	void operator()(T* x)
	{
		auto alloc = x->getAllocator();
		alloc.template deleteInstance<T>(x);
	}
};

/// A unique pointer.
template<typename T, typename TDeleter = DefaultPtrDeleter<T>>
class UniquePtr: public PtrBase<T>
{
public:
	using Base = PtrBase<T>;

	UniquePtr()
	:	Base()
	{}

	explicit UniquePtr(T* ptr)
	:	Base(ptr)
	{}

	/// Non-copyable.
	UniquePtr(const UniquePtr& other) = delete;

	/// Move.
	UniquePtr(UniquePtr&& other)
	:	Base()
	{
		move(other);
	}

	/// Destroy.
	~UniquePtr()
	{
		destroy();
	}

	/// Non-copyable.
	UniquePtr& operator=(const UniquePtr& other) = delete;

	/// Move.
	UniquePtr& operator=(UniquePtr&& other)
	{
		move(other);
		return *this;
	}

	/// Set a new pointer. Will destroy the previous.
	void reset(T* ptr)
	{
		destroy();
		Base::m_ptr = ptr;
	}

private:
	void destroy()
	{
		if(Base::m_ptr)
		{
			TDeleter deleter;
			deleter(Base::m_ptr);
			Base::m_ptr = nullptr;
		}
	}

	void move(UniquePtr& b)
	{
		reset(b.m_ptr);
		b.m_ptr = nullptr;
	}
};

/// An intrusive pointer.
template<typename T, typename TDeleter = DefaultPtrDeleter<T>>
class IntrusivePtr: public PtrBase<T>
{
	template<typename Y, typename TD>
	friend class IntrusivePtr;

public:
	using Base = PtrBase<T>;

	IntrusivePtr()
	:	Base()
	{}

	IntrusivePtr(T* ptr)
	:	Base()
	{
		reset(ptr);
	}

	/// Copy.
	IntrusivePtr(const IntrusivePtr& other)
	:	Base()
	{
		reset(other.m_ptr);
	}

	/// Copy, compatible pointer.
	template<typename Y>
	IntrusivePtr(const IntrusivePtr<Y, TDeleter>& other)
	:	Base()
	{
		reset(other.m_ptr);
	}

	/// Decrease refcount and delete the pointer if refcount is zero.
	~IntrusivePtr()
	{
		destroy();
	}

	/// Copy.
	IntrusivePtr& operator=(const IntrusivePtr& other)
	{
		reset(other.m_ptr);
		return *this;
	}

	/// Copy, compatible.
	template<typename Y>
	IntrusivePtr& operator=(const IntrusivePtr<Y, TDeleter>& other)
	{
		reset(other.m_ptr);
		return *this;
	}

	/// Set a new pointer. Will destroy the previous.
	void reset(T* ptr)
	{
		destroy();
		if(ptr)
		{
			ptr->getRefcount().fetchAdd(1);
			Base::m_ptr = ptr;
		}
	}

private:
	void destroy()
	{
		if(Base::m_ptr)
		{
			auto count = Base::m_ptr->getRefcount().fetchSub(1);
			if(count == 1)
			{
				TDeleter deleter;
				deleter(Base::m_ptr);
			}

			Base::m_ptr = nullptr;
		}
	}
};
/// @}

} // end namespace anki

#endif

