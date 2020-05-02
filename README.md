# ggtime

ggtime is a fixed point timestamp library for C++.

ggtime supports Windows, Linux and OpenBSD.


## Usage

ggtime only has a few functions, which can be found in the header. Basic
usage looks like this:

```cpp
#include <stdio.h>
#include "ggtime.h"

int main() {
	Time before = GetMonotonicTime();
	Time after = GetMonotonicTime();

	printf( "%f\n", ToSeconds( after - before ) );
	printf( "%f\n", ToSeconds( FromMilliseconds( 50 ) ) );

	return 0;
}
```


## Implementation details

ggtime uses a [flick](https://github.com/facebookarchive/Flicks) as its
unit of time, and can be seen as an STL free rewrite of the original
library.
