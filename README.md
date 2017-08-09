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

Slash is implemented in 64 bit assembly, optimized for speed. It doesn't compile, as the carry-less multiplication isn't implemented by the target architecture yet. The actual hashing process goes like:

1. The result is initialized at `1`
2. For each byte (8 bits):
   * Set the result to `ror((result @ prime) ^ (byte), 7)`
3. Return masked 64 bit unsigned result

##### Details

* `@` denotes carry-less multiplication
* `^` denotes bitwise exclusive OR (XOR)
* `ror` denotes bitwise circular right shift
* `byte` denotes the current byte being operated on
* `prime` is a 64 bit constant chosen by a simulated annealing algorithm (`0xA171020315130201ULL`)

Any overflows should be handled by "wrapping around" the number, equivalent to a modulo with `0xFFFFFFFFFFFFFFFF`.

##### Verification

To verify the implementation is correct, run it against byte arrays of `0`, `0, 1`, `0, 1, 2`...`0...255`, and store all of the results in a byte array (each hash takes up 64 entries).

Hash the result byte array, and the resulting hash should be `0x1fd71bf7b3370f18`.

### License

Licensed under the [MIT License](https://kbrsh.github.io/license) by [Kabir Shah](https://kabir.ml)
