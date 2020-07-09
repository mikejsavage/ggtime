# ggtime

ggtime is a fixed point timestamp library for C++. It has near
nanosecond precision and nicely divides FPS values that are common in
games.

It supports Windows, Linux and OpenBSD.


## Usage

ggtime only has one function:

```cpp
uint64_t ggtime();
```

which returns a monotonic number of flicks since some arbitrary
reference time.

Basic usage looks like this:

```cpp
#include <stdio.h>
#include <stdint.h>
#include "ggtime.h"

uint64_t FromMilliseconds( uint64_t ms ) { return { ms * GGTIME_FLICKS_PER_SECOND / 1000 }; }
float ToSeconds( uint64_t flicks ) { return flicks / float( GGTIME_FLICKS_PER_SECOND ); }

int main() {
	uint64_t before = ggtime();
	uint64_t after = ggtime();

	printf( "%f\n", ToSeconds( after - before ) );
	printf( "%f\n", ToSeconds( FromMilliseconds( 50 ) ) );

	return 0;
}
```


## Implementation details

ggtime uses a [flick](https://github.com/facebookarchive/Flicks) as its
unit of time, and can be seen as an STL free rewrite of the original
library.
