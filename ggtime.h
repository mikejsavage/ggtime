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

#pragma once

#include <stdint.h>

static constexpr uint64_t GGTIME_FLICKS_PER_SECOND = UINT64_C( 705600000 );

struct Time { uint64_t flicks; };

Time GetMonotonicTime();

constexpr Time operator+( Time a, Time b ) { return { a.flicks + b.flicks }; }
constexpr Time operator-( Time a, Time b ) { return { a.flicks - b.flicks }; }

constexpr bool operator==( Time a, Time b ) { return a.flicks == b.flicks; }
constexpr bool operator!=( Time a, Time b ) { return a.flicks != b.flicks; }
constexpr bool operator<( Time a, Time b ) { return a.flicks < b.flicks; }
constexpr bool operator<=( Time a, Time b ) { return a.flicks <= b.flicks; }
constexpr bool operator>( Time a, Time b ) { return a.flicks > b.flicks; }
constexpr bool operator>=( Time a, Time b ) { return a.flicks >= b.flicks; }

constexpr Time FromMilliseconds( uint64_t ms ) { return { ms * GGTIME_FLICKS_PER_SECOND / 1000 }; }
constexpr Time FromSeconds( uint64_t secs ) { return { secs * GGTIME_FLICKS_PER_SECOND }; }

float ToSeconds( Time t );
double ToSecondsDouble( Time t );
