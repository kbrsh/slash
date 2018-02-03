<p align="center"><a href="https://github.com/kbrsh/slash" target="_blank"><img width="75" src="https://raw.githubusercontent.com/kbrsh/slash/master/img/logo.png"></a></p>

<h1 align="center">Slash</h1>

<p align="center">Fast, efficient hash</p>

### Usage

Slash is a non-cryptographic hash function intended to be used for general purposes. It is highly collision resistant, results in uniformly distributed hashes, and has good avalanche properties.

```c
#include "slash.h"

const unsigned char *key = "Slash";
unsigned long long hash = slash(key);
```

### Implementation

Slash is implemented in 64 bit assembly, optimized for speed. The hashing process goes like:

1. The result is initialized to `0`
2. For each byte (8 bits):
   * Set the result to `ror((result ^ byte) * (prime), 8)`
3. Return 64 bit unsigned result

##### Details

* `*` denotes a 64 bit multiplication (mod 2<sup>64</sup>)
* `^` denotes a 64 bit bitwise exclusive OR (XOR)
* `ror` denotes a 64 bit bitwise circular right shift
* `byte` denotes a the current byte being operated on
* `prime` is a 64 bit constant chosen by a simulated annealing algorithm (`0xA01731A5AC74E8DB`)

Any overflows should be handled by "wrapping around" the number, equivalent to a modulo with 2<sup>64</sup>.

<!-- Prime: f(num, current) = num * (current ^ num) + 17, where num = current sub prime (3, 5, 7), current = XOR of all outputs, f(num, current) = output after sub prime in prime -->

##### Verification

To verify the implementation is correct, run it against byte arrays of `{1}, {1, 2}, {1, 2, 3} ... {1 - 255}`, and store all of the results in a byte array (in little-endian format).

The hash of the resulting byte array should be `0xD12CE2D383EF536F`. A C implementation of this is in the `test` directory (`test/test.c`).

### Support

Support Slash [on Patreon](https://patreon.com/kbrsh) to help sustain the development of the project. The maker of the project works on open source for free. If you or your company depend on this project, then it makes sense to donate to ensure that the project is maintained.

### License

Licensed under the [MIT License](https://kbrsh.github.io/license) by [Kabir Shah](https://kabir.ml)
