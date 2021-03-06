// Copyright (C) 2009-2015, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#include "anki/resource/ShaderResource.h"
#include "anki/resource/ProgramPrePreprocessor.h"
#include "anki/resource/ResourceManager.h"
#include "anki/core/App.h" // To get cache dir
#include "anki/util/File.h"
#include "anki/util/Filesystem.h"
#include "anki/util/Hash.h"
#include "anki/util/Assert.h"

namespace anki {

//==============================================================================
Error ShaderResource::load(const CString& filename)
{
	return load(filename, " ");
}

//==============================================================================
Error ShaderResource::load(const CString& filename, const CString& extraSrc)
{
	auto alloc = getTempAllocator();

	ProgramPrePreprocessor pars(&getManager());
	ANKI_CHECK(pars.parseFile(filename));

	// Allocate new source
	StringAuto source(alloc);

	source.append(getManager()._getShadersPrependedSource());

	if(extraSrc.getLength() > 0)
	{
		source.append(extraSrc);
	}

	source.append(pars.getShaderSource());

	// Create
	m_shader.create(
		&getManager().getGrManager(),
		pars.getShaderType(), &source[0],
		source.getLength() + 1);

	m_type = pars.getShaderType();

	return ErrorCode::NONE;
}

//==============================================================================
Error ShaderResource::createToCache(
	const CString& filename, const CString& preAppendedSrcCode,
	const CString& filenamePrefix, ResourceManager& manager,
	StringAuto& out)
{
	auto alloc = manager.getTempAllocator();

	if(preAppendedSrcCode.getLength() < 1)
	{
		out.create(filename);
		return ErrorCode::NONE;
	}

	// Create suffix
	StringAuto unique(alloc);

	unique.create(filename);
	unique.append(preAppendedSrcCode);

	U64 h = computeHash(&unique[0], unique.getLength());

	StringAuto suffix(alloc);
	suffix.toString(h);

	// Compose cached filename
	StringAuto newFilename(alloc);

	newFilename.sprintf(
		"%s/%s%s.glsl",
		&manager._getCacheDirectory()[0],
		&filenamePrefix[0],
		&suffix[0]);

	if(fileExists(newFilename.toCString()))
	{
		out = std::move(newFilename);
		return ErrorCode::NONE;
	}

	// Read file and append code
	StringAuto src(alloc);

	StringAuto fixedFname(alloc);
	manager.fixResourceFilename(filename, fixedFname);

	File file;
	ANKI_CHECK(file.open(fixedFname.toCString(), File::OpenFlag::READ));
	ANKI_CHECK(file.readAllText(TempResourceAllocator<char>(alloc), src));

	StringAuto srcfull(alloc);
	srcfull.sprintf("%s%s", &preAppendedSrcCode[0], &src[0]);

	// Write cached file
	File f;
	ANKI_CHECK(f.open(newFilename.toCString(), File::OpenFlag::WRITE));
	ANKI_CHECK(f.writeText("%s\n", &srcfull[0]));

	out = std::move(newFilename);
	return ErrorCode::NONE;
}

} // end namespace anki
