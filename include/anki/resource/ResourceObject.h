// Copyright (C) 2009-2015, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#ifndef ANKI_RESOURCE_RESOURCE_OBJECT_H
#define ANKI_RESOURCE_RESOURCE_OBJECT_H

#include "anki/resource/Common.h"
#include "anki/util/Atomic.h"
#include "anki/util/String.h"

namespace anki {

/// @addtogroup resource
/// @{

/// The base of all resource objects.
class ResourceObject
{
public:
	ResourceObject(ResourceManager* manager)
	:	m_manager(manager),
		m_refcount(0)
	{}

	virtual ~ResourceObject();

	/// @privatesection
	/// @{
	ResourceManager& getManager()
	{
		return *m_manager;
	}

	ResourceAllocator<U8> getAllocator() const;
	TempResourceAllocator<U8> getTempAllocator() const;

	Atomic<I32>& getRefcount()
	{
		return m_refcount;
	}

	const Atomic<I32>& getRefcount() const
	{
		return m_refcount;
	}

	const String& getUuid() const
	{
		ANKI_ASSERT(!m_uuid.isEmpty());
		return m_uuid;
	}

	void setUuid(const CString& uuid)
	{
		ANKI_ASSERT(m_uuid.isEmpty());
		m_uuid.create(getAllocator(), uuid);
	}
	/// @}

private:
	ResourceManager* m_manager;
	Atomic<I32> m_refcount;
	String m_uuid; ///< Unique resource name.
};
/// @}

} // end namespace anki

#endif

