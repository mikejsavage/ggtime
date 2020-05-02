/*
 * ggtime
 *
 * Copyright (c) 2020 Michael Savage <mike@mikejsavage.co.uk>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#if defined( _WIN32 )
#  define PLATFORM_WINDOWS 1
#elif defined( __linux__ )
#  define PLATFORM_LINUX 1
#elif defined( __APPLE__ )
#  define PLATFORM_MACOS 1
#elif defined( __OpenBSD__ )
#  define PLATFORM_OPENBSD 1
#else
#  error new platform
#endif

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "ggtime.h"

#if PLATFORM_WINDOWS

#include <windows.h>

Time GetMonotonicTime() {
	// https://docs.microsoft.com/en-us/windows/win32/api/profileapi/nf-profileapi-queryperformancecounter
	// "On systems that run Windows XP or later, the function will always succeed and will thus never return zero."
	LARGE_INTEGER now, freq;
	QueryPerformanceCounter( &now );
	QueryPerformanceFrequency( &freq );

	uint64_t a = ( now.QuadPart / freq ) * GGTIME_FLICKS_PER_SECOND;
	uint64_t b = ( ( now.QuadPart % freq ) * GGTIME_FLICKS_PER_SECOND ) / freq;
	return { a + b };
}

#elif PLATFORM_LINUX || PLATFORM_OPENBSD

#include <time.h>

static constexpr uint64_t NS_PER_SECOND = UINT64_C( 1000000000 );

Time GetMonotonicTime() {
	struct timespec ts;
	clock_gettime( CLOCK_MONOTONIC, &ts );
	uint64_t ns = ts.tv_sec * NS_PER_SECOND + ts.tv_nsec;

	uint64_t a = ( ns / NS_PER_SECOND ) * GGTIME_FLICKS_PER_SECOND;
	uint64_t b = ( ( ns % NS_PER_SECOND ) * GGTIME_FLICKS_PER_SECOND ) / NS_PER_SECOND;
	return { a + b };
}

#else
#error new platform
#endif

float ToSeconds( Time t ) {
	assert( t.flicks < 3600 * GGTIME_FLICKS_PER_SECOND );
	return t.flicks / float( GGTIME_FLICKS_PER_SECOND );
}

double ToSecondsDouble( Time t ) {
	return t.flicks / double( GGTIME_FLICKS_PER_SECOND );
}
