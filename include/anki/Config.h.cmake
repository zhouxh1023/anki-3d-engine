#ifndef ANKI_CONFIG_H
#define ANKI_CONFIG_H

/// @addtogroup config
/// @{

#define ANKI_VERSION_MINOR ${ANKI_VERSION_MINOR}
#define ANKI_VERSION_MAJOR ${ANKI_VERSION_MAJOR}
#define ANKI_REVISION ${ANKI_REVISION}

#define ANKI_DEBUG ${ANKI_DEBUG}
#define ANKI_ASSERTIONS ANKI_DEBUG

// Operating system
#define ANKI_OS_LINUX 1 
#define ANKI_OS_ANDROID 2
#define ANKI_OS_MACOS 3
#define ANKI_OS_IOS 4
#define ANKI_OS_WINDOWS 5

#if defined(__WIN32__) || defined(_WIN32)
#	define ANKI_OS ANKI_OS_WINDOWS
#elif defined(__APPLE_CC__)
#	if (defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) \
		&& __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ >= 40000) \
	|| (defined(__IPHONE_OS_VERSION_MIN_REQUIRED) \
		&& __IPHONE_OS_VERSION_MIN_REQUIRED >= 40000)
#		define ANKI_OS ANKI_OS_IOS
#	else
#		define ANKI_OS ANKI_OS_MACOS
#	endif
#elif defined(__ANDROID__)
#	define ANKI_OS ANKI_OS_ANDROID
#else
#	define ANKI_OS ANKI_OS_LINUX
#endif

// POSIX system or not
#if ANKI_OS == ANKI_OS_LINUX || ANKI_OS == ANKI_OS_ANDROID \
	|| ANKI_OS == ANKI_OS_MACOS || ANKI_OS == ANKI_OS_IOS
#	define ANKI_POSIX 1
#else
#	define ANKI_POSIX 0
#endif

// CPU architecture
#define ANKI_CPU_ARCH_INTEL 1
#define ANKI_CPU_ARCH_ARM 2

#if defined(__GNUC__)
#	if defined(__arm__)
#		define ANKI_CPU_ARCH ANKI_CPU_ARCH_ARM
#		define ANKI_CPU_ARCH_STR "ANKI_CPU_ARCH_ARM"
#	elif defined(__i386__) || defined(__amd64__)
#		define ANKI_CPU_ARCH ANKI_CPU_ARCH_INTEL
#		define ANKI_CPU_ARCH_STR "ANKI_CPU_ARCH_INTEL"
#	else
#		error "Unknown CPU arch"
#	endif
#else
#	error "Unsupported compiler"
#endif

// SIMD
#define ANKI_ENABLE_SIMD ${_ANKI_ENABLE_SIMD}

#define ANKI_SIMD_NONE 1
#define ANKI_SIMD_SSE 2
#define ANKI_SIMD_NEON 3

#if !ANKI_ENABLE_SIMD
#	define ANKI_SIMD ANKI_SIMD_NONE
#else
#	if ANKI_CPU_ARCH == ANKI_CPU_ARCH_INTEL
#		define ANKI_SIMD ANKI_SIMD_SSE
#	elif ANKI_CPU_ARCH == ANKI_CPU_ARCH_ARM
#		define ANKI_SIMD ANKI_SIMD_NEON
#	endif
#endif

// Window backend
#define ANKI_WINDOW_BACKEND_GLXX11 1
#define ANKI_WINDOW_BACKEND_EGLX11 2
#define ANKI_WINDOW_BACKEND_EGLFBDEV 3
#define ANKI_WINDOW_BACKEND_MACOS 4
#define ANKI_WINDOW_BACKEND_ANDROID 5
#define ANKI_WINDOW_BACKEND_SDL 6
#define ANKI_WINDOW_BACKEND ANKI_WINDOW_BACKEND_${ANKI_WINDOW_BACKEND}
#define ANKI_WINDOW_BACKEND_STR "ANKI_WINDOW_BACKEND_${ANKI_WINDOW_BACKEND}"

// OpenGL version
#define ANKI_GL_DESKTOP 1
#define ANKI_GL_ES 2
#if ANKI_OS == ANKI_OS_LINUX \
	|| ANKI_OS == ANKI_OS_MACOS \
	|| ANKI_OS == ANKI_OS_WINDOWS
#	define ANKI_GL ANKI_GL_DESKTOP
#	define ANKI_GL_STR "ANKI_GL_DESKTOP"
#else
#	define ANKI_GL ANKI_GL_ES
#	define ANKI_GL_STR "ANKI_GL_ES"
#endif

// Enable performance counters
#define ANKI_ENABLE_COUNTERS ${_ANKI_ENABLE_COUNTERS}

//==============================================================================
// Engine config                                                               =
//==============================================================================

// General config
#define ANKI_SAFE_ALIGNMENT 16

// Renderer and rendering related config options
#define ANKI_RENDERER_MAX_TILES_X 64
#define ANKI_RENDERER_MAX_TILES_Y 64

#define ANKI_RENDERER_USE_MATERIAL_UBOS 0

/// @{
/// Used to optimize the initial vectors of VisibilityTestResults
#define ANKI_FRUSTUMABLE_AVERAGE_VISIBLE_RENDERABLES_COUNT 16
#define ANKI_FRUSTUMABLE_AVERAGE_VISIBLE_LIGHTS_COUNT 8
/// @}

/// If true then we can place spatials in a thread-safe way
#define ANKI_CFG_OCTREE_THREAD_SAFE 1

// GL
#define ANKI_GL_MAX_MIPMAPS 32
#define ANKI_GL_MAX_TEXTURE_LAYERS 32
#define ANKI_GL_MAX_SUB_DRAWCALLS 64
#define ANKI_GL_MAX_INSTANCES 64

//==============================================================================
// Other                                                                       =
//==============================================================================

#define ANKI_FILE __FILE__
#define ANKI_FUNC __func__

// Some compiler struff
#if defined(__GNUC__)
#	define ANKI_LIKELY(x) __builtin_expect((x), 1)
#	define ANKI_UNLIKELY(x) __builtin_expect((x), 0)
#	define ANKI_RESTRICT __restrict
#	define ANKI_USE_RESULT __attribute__((warn_unused_result))
#else
#	define ANKI_LIKELY(x) ((x) == 1)
#	define ANKI_UNLIKELY(x) ((x) == 1)
#	define ANKI_RESTRICT
#	define ANKI_USE_RESULT
#endif
/// @}

#endif
