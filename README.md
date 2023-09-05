# cbtutils (Cobalt Utils)

An OpenBSD-derived userspace package and library.

Almost all utilities and library functions included here originate from OpenBSD. This does not include a handful of utilities that are highly dependent on Linux-specific functionality or are not used in favor of more sophisticated alternatives. Of particular note, cbtutils does not include any init, logging, device or service management programs, besides for those that used a standardized interface.

At the moment, cbtutils is "complete" but amounts to a bloody hackjob. It also is not yet particularly portable or tested; you may need to kick it a few times in order for it to build properly on a particular system. Future developments to this project will focus on consistency, portability and organization.

## Installation
cbtutils uses BSD Make and crunchgen to build. If you do not have BSD make installed, we include a GNUmakefile for quickly bootstrapping a standalone version.

Do note that cbtutils will can and will collide with a myriad of other packages, including but not limited to, libbsd, glibc and whatever core utilities you have installed. It is recommended that you DESTDIR install and then only install the parts you are interested in.

## License
See each source file for its licensing terms. For all other components of cbtutils, 0BSD license applies. See `LICENSE`
