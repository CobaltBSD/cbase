# Crunchgen

This is a mini reimplementation of NetBSD crunchgen.

Unlike the original crunchgen, this does not exist as a standalone program. Rather, it is a skeleton for incorporating several main functions into a single program, which can then be executed according to argv.

The syntax for the configuration file is very rudimentary. Each line is a whitespace-delimited list describing how an executable is built. The first item is the program's name, as well as the base directory it resides in, and every item after that represents a path to a source code file, relative to the user's current directory. Separate makefiles should be used for source code files that need to be dynamically generated, or to control installation.

Create a makefile by running genmakefile.sh in the same directory as your crunchgen.conf. A few environment variables are also respected:
LIBS: The contents of this variable will be added to the final compilation. Use to add additional libraries to link to.
EXECNAME: The name of the crunchgen executable. Is set to `crunchgen` by default, but can be changed.
CFLAGS and LDFLAGS both are applied to compilation.

## Caveats
At the moment, the symbols of each executable are "mangled" by prefixing their prognam name to the symbol itself. While unlikely, it is possible that this will result in collisions with some programs. For this reason, weak symbols are to not be used at all, as a collision then will result in strange behavior rather than failing to link in the first place.
