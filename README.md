# cbtutils (Cobalt Utils)

# Notice: musl support has been dropped in favor of glibc. Building on musl may no longer work until portability is improved.

An OpenBSD-derived userspace package and library.

## The utilities
Almost all utilities and library functions included here originate from OpenBSD. This does not include a handful of utilities that are highly dependent on Linux-specific functionality or are not used in favor of more sophisticated alternatives. Of particular note, cbtutils does not include any init, logging, device or service management programs, besides for those that used a standardized interface.

## The library
Cobalt ships with a utility library called libcobalt. This is not a particularly heavy library and mainly contains ports of different features from OpenBSD. Some of these are broadly useful: Among the included features are the `vis` and `unvis` facilities which are commonplace on the BSDs, as well as numerous hashing functions, a radix sort implementation, improved hash table implementation and a memory-mapped database. This library, like libbsd, also makes it easier to port different OpenBSD software to Linux, such as by providing stubs for pledge and unveil. However, programs will still need to be modified as the headers are arranged differently as to not conflict with the other ones you have installed.

Not all of the functionality provided by libcobalt is necessarily used for Cobalt. Some of it has been provided simply because it is highly useful in general, eliminates the need for additional libraries, and/or provides functionality that is commonly requested by other packages.

## Installation
cbtutils uses BSD Make and crunchgen to build. If you do not have BSD make installed, we include a GNUmakefile for quickly bootstrapping a standalone version. This is not necessarily for compiling cbtutils, but rather because there are no other BSD make ports that are easy to install.

At the moment, this project is heavily work-in-progress and so you can expect lacking portability.

Compiling one included program, `entropy`, requires [zxcvbn-c](https://github.com/tsyrogit/zxcvbn-c). You will also need to install one of the `.dict` files to `/usr/share/misc/zxcvbn.dict`.

## License
See each source file for its licensing terms. For all other components of cbtutils, 0BSD license applies. See `LICENSE`
