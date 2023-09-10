# cbtutils (Cobalt Utils)

An OpenBSD-derived userspace package and library.

## The utilities
Almost all utilities and library functions included here originate from OpenBSD. This does not include a handful of utilities that are highly dependent on Linux-specific functionality or are not used in favor of more sophisticated alternatives. Of particular note, cbtutils does not include any init, logging, device or service management programs, besides for those that used a standardized interface.

At the moment, cbtutils is "complete" but amounts to a bloody hackjob. It also is not yet particularly portable or tested; you may need to kick it a few times in order for it to build properly on a particular system. Future developments to this project will focus on consistency, portability and organization.

## The library
Cobalt ships with an extension utility library called libcobalt. This is not a particularly heavy library and mainly contains ports of different features from OpenBSD. Some of these are broadly useful: For example, we include an implementation of `fts` for musl systems that don't have one. Among other features are the `vis` and `unvis` facilities which are commonplace on the BSDs, as well as numerous hashing functions, a radix sort implementation, improved hash table implementation and a memory-mapped database facility. This library, like libbsd, also makes it easier to port different OpenBSD software to Linux, such as by providing stubs for pledge and unveil. However, programs will still need to be modified as the headers are arranged differently.

Not all of the functionality provided by libcobalt is necessarily used for Cobalt. Some of it has been provided simply because it is highly useful in general.

## Installation
cbtutils uses BSD Make and crunchgen to build. If you do not have BSD make installed, we include a GNUmakefile for quickly bootstrapping a standalone version.

Do note that cbtutils will can and will collide with a myriad of other packages, including but not limited to, libbsd, glibc and whatever core utilities you have installed. It is recommended that you DESTDIR install and then only install the parts you are interested in. On glibc systems in particular, this will almost certainly not build nor is it meant to, and if you somehow get it to anyways it will end up overwriting some of glibc's header files.

Compiling one included program, `entropy`, requires [zxcvbn-c](https://github.com/tsyrogit/zxcvbn-c). You will also need to install one of the `.dict` files to `/usr/share/misc/zxcvbn.dict`.

## License
See each source file for its licensing terms. For all other components of cbtutils, 0BSD license applies. See `LICENSE`
