<p align="center"><a href="https://github.com/kbrsh/slash" target="_blank"><img width="75" src="https://raw.githubusercontent.com/kbrsh/slash/master/img/logo.png"></a></p>

<h1 align="center">Slash</h1>

<p align="center">Fast, efficient hash</p>

### Usage

Slash is a non-cryptographic hash function intended to be used for general purposes. It is highly collision resistant, results in uniformly distributed hashes, and has good avalanche properties.

```c
#include "slash.h"

const unsigned char *key = "Slash";
unsigned long long hash = slash(key, 5);

//-> 0x2EF187C88FB36176
```

### Building

```shell
$ git clone https://github.com/kbrsh/slash
$ cd slash
$ make
```

### Support

Support Slash [on Patreon](https://patreon.com/kbrsh) to help sustain the development of the project. The maker of the project works on open source for free. If you or your company depend on this project, then it makes sense to donate to ensure that the project is maintained.

### License

Licensed under the [MIT License](https://kbrsh.github.io/license) by [Kabir Shah](https://kabir.sh)
