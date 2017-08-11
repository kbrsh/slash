<p align="center"><a href="https://github.com/kbrsh/slash" target="_blank"><img width="75" src="https://raw.githubusercontent.com/kbrsh/slash/master/img/logo.png"></a></p>

<h1 align="center">Slash</h1>

<p align="center">Fast, efficient hash</p>

### Usage

Slash is a _non-cryptographic_ hash, and is intended to be used as a general hash function. It has very few collisions and shows good avalanche properties.

```c
#include "slash.h"

char *str = "Slash";
unsigned long long hash = slash(str);
```

### Implementation

Slash is implemented in 64 bit assembly, optimized for speed. The hashing process goes like:

1. The result is initialized at `1`
2. For each byte (8 bits):
   * Set the result to `ror((result * prime) ^ (byte), 7)`
3. Return 64 bit unsigned result

##### Details

* `*` denotes a 64 bit multiplication (mod 2<sup>64</sup>)
* `^` denotes a 64 bit bitwise exclusive OR (XOR)
* `ror` denotes a 64 bit bitwise circular right shift
* `byte` denotes a the current byte being operated on
* `prime` is a 64 bit constant chosen by a simulated annealing algorithm (`0xA171020315130201`)

Any overflows should be handled by "wrapping around" the number, equivalent to a modulo with `0xFFFFFFFFFFFFFFFF` (2<sup>64</sup>).

##### Verification

To verify the implementation is correct, run it against byte arrays of `0`, `0, 1`, `0, 1, 2`...`0...255`, and store all of the results in a byte array (each hash takes up 8 entries in little-endian format).

Hash the result byte array, and the resulting hash should be `0xC5C1D27F4283993A`. A C implementation of this is in the `test` directory.

### License

Licensed under the [MIT License](https://kbrsh.github.io/license) by [Kabir Shah](https://kabir.ml)
