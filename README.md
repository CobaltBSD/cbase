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
