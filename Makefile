clean:
	rm -rf cbtutils-makefile crunchgen/cbtutils
	find . -name "*.d" -delete
	find . -name "*.o" -delete
	find . -name "*.so" -delete
	find . -name "*.so.*" -delete
	find . -name "*.tmp" -delete
	find . -name "*.po" -delete
	find . -name "*.a" -delete
	${MAKE} -C fortune clean
	${MAKE} -C m4 clean
	${MAKE} -C awk clean
	${MAKE} -C make clean
	${MAKE} -C doas clean
	${MAKE} -C getent

.include <bsd.prog.mk>

# crunchgen handles these directories for the most part, but including them here is still useful for installation or generating additional source files.
SUBDIR=	libcobalt cp mv make fortune grdc locale ls number tetris units arch awk banner basename cat chroot cmp comm cut date dd diff dirname echo env expr false fold getconf getopt head hostname indent jot kill ln logger logname m4 mkdir mktemp nl printenv printf pwd readlink realpath rev rm rmdir rs seq sleep split tail timeout touch tr true tsort tty uname unifdef uniq unvis vis wc yes freq unicode getent entropy doas version wisdom shsecret

CFLAGS += -lzxcvbn -Ilibcobalt -Llibcobalt -lcobalt

all: ${SUBDIR} fortune/strfile fortune/datfiles
	EXECNAME=cbtutils LIBS=-lcurses ./crunchgen/genmakefile.sh > cbtutils-makefile
	$(MAKE) CFLAGS="${CFLAGS}" -f cbtutils-makefile

install: ${SUBDIR} fortune/datfiles
	${MAKE} -C libcobalt includes
	install -D crunchgen/cbtutils ${DESTDIR}${BINDIR}/cbtutils
	mkdir -p ${DESTDIR}${SBINDIR}
	ln -sf cbtutils ${DESTDIR}${BINDIR}/cp
	ln -sf cbtutils ${DESTDIR}${BINDIR}/mv
	ln -sf cbtutils ${DESTDIR}${BINDIR}/make
	ln -sf cbtutils ${DESTDIR}${BINDIR}/fortune
	ln -sf cbtutils ${DESTDIR}${BINDIR}/grdc
	ln -sf cbtutils ${DESTDIR}${BINDIR}/locale
	ln -sf cbtutils ${DESTDIR}${BINDIR}/ls
	ln -sf cbtutils ${DESTDIR}${BINDIR}/number
	ln -sf cbtutils ${DESTDIR}${BINDIR}/tetris
	ln -sf cbtutils ${DESTDIR}${BINDIR}/units
	ln -sf cbtutils ${DESTDIR}${BINDIR}/arch
	ln -sf cbtutils ${DESTDIR}${BINDIR}/awk
	ln -sf cbtutils ${DESTDIR}${BINDIR}/banner
	ln -sf cbtutils ${DESTDIR}${BINDIR}/basename
	ln -sf cbtutils ${DESTDIR}${BINDIR}/cat
	ln -sf ../bin/cbtutils ${DESTDIR}${SBINDIR}/chroot
	ln -sf cbtutils ${DESTDIR}${BINDIR}/cmp
	ln -sf cbtutils ${DESTDIR}${BINDIR}/comm
	ln -sf cbtutils ${DESTDIR}${BINDIR}/cut
	ln -sf cbtutils ${DESTDIR}${BINDIR}/date
	ln -sf cbtutils ${DESTDIR}${BINDIR}/dd
	ln -sf cbtutils ${DESTDIR}${BINDIR}/diff
	ln -sf cbtutils ${DESTDIR}${BINDIR}/dirname
	ln -sf cbtutils ${DESTDIR}${BINDIR}/echo
	ln -sf cbtutils ${DESTDIR}${BINDIR}/env
	ln -sf cbtutils ${DESTDIR}${BINDIR}/expr
	ln -sf cbtutils ${DESTDIR}${BINDIR}/false
	ln -sf cbtutils ${DESTDIR}${BINDIR}/fold
	ln -sf cbtutils ${DESTDIR}${BINDIR}/getconf
	ln -sf cbtutils ${DESTDIR}${BINDIR}/getopt
	ln -sf cbtutils ${DESTDIR}${BINDIR}/head
	ln -sf cbtutils ${DESTDIR}${BINDIR}/hostname
	ln -sf cbtutils ${DESTDIR}${BINDIR}/indent
	ln -sf cbtutils ${DESTDIR}${BINDIR}/jot
	ln -sf cbtutils ${DESTDIR}${BINDIR}/kill
	ln -sf cbtutils ${DESTDIR}${BINDIR}/ln
	ln -sf cbtutils ${DESTDIR}${BINDIR}/logger
	ln -sf cbtutils ${DESTDIR}${BINDIR}/logname
	ln -sf cbtutils ${DESTDIR}${BINDIR}/m4
	ln -sf cbtutils ${DESTDIR}${BINDIR}/mkdir
	ln -sf cbtutils ${DESTDIR}${BINDIR}/mktemp
	ln -sf cbtutils ${DESTDIR}${BINDIR}/nl
	ln -sf cbtutils ${DESTDIR}${BINDIR}/printenv
	ln -sf cbtutils ${DESTDIR}${BINDIR}/printf
	ln -sf cbtutils ${DESTDIR}${BINDIR}/pwd
	ln -sf cbtutils ${DESTDIR}${BINDIR}/readlink
	ln -sf cbtutils ${DESTDIR}${BINDIR}/realpath
	ln -sf cbtutils ${DESTDIR}${BINDIR}/rev
	ln -sf cbtutils ${DESTDIR}${BINDIR}/rm
	ln -sf cbtutils ${DESTDIR}${BINDIR}/rmdir
	ln -sf cbtutils ${DESTDIR}${BINDIR}/rs
	ln -sf cbtutils ${DESTDIR}${BINDIR}/seq
	ln -sf cbtutils ${DESTDIR}${BINDIR}/sleep
	ln -sf cbtutils ${DESTDIR}${BINDIR}/split
	ln -sf cbtutils ${DESTDIR}${BINDIR}/tail
	ln -sf cbtutils ${DESTDIR}${BINDIR}/timeout
	ln -sf cbtutils ${DESTDIR}${BINDIR}/touch
	ln -sf cbtutils ${DESTDIR}${BINDIR}/tr
	ln -sf cbtutils ${DESTDIR}${BINDIR}/true
	ln -sf cbtutils ${DESTDIR}${BINDIR}/tsort
	ln -sf cbtutils ${DESTDIR}${BINDIR}/tty
	ln -sf cbtutils ${DESTDIR}${BINDIR}/uname
	ln -sf cbtutils ${DESTDIR}${BINDIR}/unifdef
	ln -sf cbtutils ${DESTDIR}${BINDIR}/uniq
	ln -sf cbtutils ${DESTDIR}${BINDIR}/unvis
	ln -sf cbtutils ${DESTDIR}${BINDIR}/vis
	ln -sf cbtutils ${DESTDIR}${BINDIR}/wc
	ln -sf cbtutils ${DESTDIR}${BINDIR}/yes
	ln -sf cbtutils ${DESTDIR}${BINDIR}/freq
	ln -sf cbtutils ${DESTDIR}${BINDIR}/unicode
	ln -sf cbtutils ${DESTDIR}${BINDIR}/getent
	ln -sf cbtutils ${DESTDIR}${BINDIR}/entropy
	ln -sf cbtutils ${DESTDIR}${BINDIR}/wisdom
	ln -sf cbtutils ${DESTDIR}${BINDIR}/shsecret
	# `version` utility is deliberately un-symlinked
	mkdir -p ${DESTDIR}/usr/share
	cp -rf make/mk ${DESTDIR}/usr/share/

#TODO: install libcobalt headers
#TODO: other bsd man pages?

.include <bsd.subdir.mk>
