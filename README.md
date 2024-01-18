# Notice: repo unmaintained

As it turns out, glibc causes a lot of unexpected and difficult-to-diagnose breakage with many of these ports, which do not affect musl or presumably other sane Linux C libraries.

For the time being, the utilities provided here have been merged with the [CobaltBSD source tree](https://github.com/CobaltBSD/src). To save time and to redirect effort to more important projects, these portable utilities are no longer being maintained. Some of them have known bugs, but should largely work fine.

# cbase (Cobalt Coreutils)

A portable OpenBSD-derived userspace package.

Most, but not all, of the utilities included here originate from OpenBSD. Cbase does not include any utilities such as init or server management which are highly kernel-specific. Those can be found in the non-portable cbutils package.

## Dependencies
* C compiler
* [libcobalt](https://github.com/CobaltBSD/libcobalt)

## Installation
cbase uses GNU Make and crunchgen (which is provided in the source tree) to build. Run your make program (normally `make` or `gmake`) to build it.

## License
See each source file for its licensing terms. For all other components of cbase, 0BSD license applies. See `LICENSE`
