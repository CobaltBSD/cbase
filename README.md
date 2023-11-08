# cbtutils (Cobalt Utils)

An OpenBSD-derived userspace package.

Most, but not all, of the utilities included here originate from OpenBSD. This does not include a handful of utilities that are highly dependent on Linux-specific functionality. Of particular note, cbtutils does not include any init, device or service management programs.

## Dependencies
* C compiler
* [libcobalt](https://github.com/CobaltBSD/libcobalt)

## Installation
cbtutils uses GNU Make and crunchgen (which is provided in the source tree) to build. Run your make program (normally `make` or `gmake`) to build it.

## License
See each source file for its licensing terms. For all other components of cbtutils, 0BSD license applies. See `LICENSE`
