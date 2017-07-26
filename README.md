# Slash

Fast, efficient hash

### Usage

Slash is a _non-cryptographic_ hash, and is intended to be used as a general hash function. It has very few collisions and shows good avalanche properties.

```c
#include "slash.h"

char *str = "Slash";
unsigned long long hash = slash(str);
```

### Implementation

Slash is implemented in 64 bit assembly, optimized for speed. It doesn't compile, as the carry-less multiplication isn't implemented by the target architecture yet. The actual hashing process goes like:

1. The result is initialized at `1`
2. For each byte (8 bits):
   * Set the result to `(result @ prime) ^ (byte)`
3. Return masked 64 bit unsigned result

##### Details

* `@` denotes carry-less multiplication
* `^` denotes exclusive OR (XOR)
* `byte` denotes the current byte being operated on
* `prime` is a constant chosen by a simulated annealing algorithm (`0xA1720315130235ULL`)

### License

Licensed under the [MIT License](https://kingpixil.github.io/license) by [Kabir Shah](https://kabir.ml)
