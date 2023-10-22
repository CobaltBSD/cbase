# cbtutils (Cobalt Utils)

## Notice: musl support has been dropped in favor of glibc. Building on musl is no longer supported but should still work, and at the very least will require linking with an external fts implementation.

An OpenBSD-derived userspace package and library.

## The utilities
Most of the utilities and library functions included here originate from OpenBSD. This does not include a handful of utilities that are highly dependent on Linux-specific functionality or are not used in favor of more sophisticated alternatives. Of particular note, cbtutils does not include any init, device or service management programs.

## The library
Cobalt ships with a utility library called libcobalt. This is not a particularly heavy library and mainly contains ports of different features from OpenBSD. Some of these are broadly useful: Among the included features are the `vis` and `unvis` facilities which are commonplace on the BSDs, as well as numerous hashing functions, a radix sort implementation, improved hash table implementation and a memory-mapped database. This library, like libbsd, also makes it easier to port different OpenBSD software to Linux. However, programs will still need to be modified as the headers are arranged differently as to not conflict with the other ones you have installed.

Not all of the functionality provided by libcobalt is necessarily used for Cobalt. Some of it has been provided simply because it is highly useful in general, eliminates the need for additional libraries, and/or provides functionality that is commonly requested by other packages.

## Installation
cbtutils uses GNU Make and crunchgen to build. Run your make program (normally `make` or `gmake`) to build it.

Compiling one included program, `entropy`, requires [zxcvbn-c](https://github.com/tsyrogit/zxcvbn-c). You will also need to install one of the `.dict` files to `/usr/share/misc/zxcvbn.dict`.

## License
See each source file for its licensing terms. For all other components of cbtutils, 0BSD license applies. See `LICENSE`
