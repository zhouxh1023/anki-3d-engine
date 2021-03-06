// Copyright (C) 2009-2015, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#ifndef ANKI_RESOURCE_DUMMY_RSRC_H
#define ANKI_RESOURCE_DUMMY_RSRC_H

#include "anki/resource/ResourceObject.h"
#include "anki/resource/ResourcePointer.h"

namespace anki {

/// @addtogroup resource_private
/// @{

/// A dummy resource for the unit tests of the ResourceManager
class DummyRsrc: public ResourceObject
{
public:
	DummyRsrc(ResourceManager* manager)
	:	ResourceObject(manager)
	{}

	~DummyRsrc()
	{
		if(m_memory)
		{
			getAllocator().deallocate(m_memory, 128);
		}
	}

	ANKI_USE_RESULT Error load(const CString& filename)
	{
		Error err = ErrorCode::NONE;
		if(filename.find("error") == CString::NPOS)
		{
			m_memory = getAllocator().allocate(128);
			void* tempMem = getTempAllocator().allocate(128);
			(void)tempMem;

			getTempAllocator().deallocate(tempMem, 128);
		}
		else
		{
			ANKI_LOGE("Dummy error");
			err = ErrorCode::USER_DATA;
		}

		return err;
	}

private:
	void* m_memory = nullptr;
};
/// @}

} // end namespace anki

#endif
