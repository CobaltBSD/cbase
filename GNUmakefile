CFLAGS += -lzxcvbn -lcobalt -lm -lncurses
BINDIR := /usr/bin
SBINDIR := /usr/sbin

all:
	$(MAKE) -C doas
	$(MAKE) -C fortune
	EXECNAME=cbase LIBS=-lncurses ./crunchgen/genmakefile.sh > cbase-makefile
	$(MAKE) -f cbase-makefile

clean:
	rm -rfv cbase-makefile crunchgen/cbase crunchgen/entry_points.h
	$(MAKE) -C doas clean
	$(MAKE) -C fortune clean
	find . -name "*.o" -delete

install:
	$(MAKE) -C doas install
	$(MAKE) -C fortune install-datfiles
	$(MAKE) -C units install-lib
	install -D crunchgen/cbase $(DESTDIR)$(BINDIR)/cbase
	mkdir -p $(DESTDIR)$(SBINDIR)
	ln -sf cbase $(DESTDIR)$(BINDIR)/cp
	ln -sf cbase $(DESTDIR)$(BINDIR)/mv
	ln -sf cbase $(DESTDIR)$(BINDIR)/fortune
	ln -sf cbase $(DESTDIR)$(BINDIR)/grdc
	ln -sf cbase $(DESTDIR)$(BINDIR)/locale
	ln -sf cbase $(DESTDIR)$(BINDIR)/ls
	ln -sf cbase $(DESTDIR)$(BINDIR)/number
	ln -sf cbase $(DESTDIR)$(BINDIR)/tetris
	ln -sf cbase $(DESTDIR)$(BINDIR)/units
	ln -sf cbase $(DESTDIR)$(BINDIR)/arch
	ln -sf cbase $(DESTDIR)$(BINDIR)/banner
	ln -sf cbase $(DESTDIR)$(BINDIR)/basename
	ln -sf cbase $(DESTDIR)$(BINDIR)/cat
	ln -sf ../bin/cbase $(DESTDIR)$(SBINDIR)/chroot
	ln -sf cbase $(DESTDIR)$(BINDIR)/cmp
	ln -sf cbase $(DESTDIR)$(BINDIR)/comm
	ln -sf cbase $(DESTDIR)$(BINDIR)/cut
	ln -sf cbase $(DESTDIR)$(BINDIR)/date
	ln -sf cbase $(DESTDIR)$(BINDIR)/dd
	ln -sf cbase $(DESTDIR)$(BINDIR)/diff
	ln -sf cbase $(DESTDIR)$(BINDIR)/dirname
	ln -sf cbase $(DESTDIR)$(BINDIR)/echo
	ln -sf cbase $(DESTDIR)$(BINDIR)/expr
	ln -sf cbase $(DESTDIR)$(BINDIR)/false
	ln -sf cbase $(DESTDIR)$(BINDIR)/fold
	ln -sf cbase $(DESTDIR)$(BINDIR)/getopt
	ln -sf cbase $(DESTDIR)$(BINDIR)/head
	ln -sf cbase $(DESTDIR)$(BINDIR)/hostname
	ln -sf cbase $(DESTDIR)$(BINDIR)/indent
	ln -sf cbase $(DESTDIR)$(BINDIR)/jot
	ln -sf cbase $(DESTDIR)$(BINDIR)/kill
	ln -sf cbase $(DESTDIR)$(BINDIR)/ln
	ln -sf cbase $(DESTDIR)$(BINDIR)/logger
	ln -sf cbase $(DESTDIR)$(BINDIR)/logname
	ln -sf cbase $(DESTDIR)$(BINDIR)/mkdir
	ln -sf cbase $(DESTDIR)$(BINDIR)/mktemp
	ln -sf cbase $(DESTDIR)$(BINDIR)/nl
	ln -sf cbase $(DESTDIR)$(BINDIR)/printenv
	ln -sf cbase $(DESTDIR)$(BINDIR)/printf
	ln -sf cbase $(DESTDIR)$(BINDIR)/pwd
	ln -sf cbase $(DESTDIR)$(BINDIR)/readlink
	ln -sf cbase $(DESTDIR)$(BINDIR)/realpath
	ln -sf cbase $(DESTDIR)$(BINDIR)/rev
	ln -sf cbase $(DESTDIR)$(BINDIR)/rm
	ln -sf cbase $(DESTDIR)$(BINDIR)/rmdir
	ln -sf cbase $(DESTDIR)$(BINDIR)/rs
	ln -sf cbase $(DESTDIR)$(BINDIR)/seq
	ln -sf cbase $(DESTDIR)$(BINDIR)/sleep
	ln -sf cbase $(DESTDIR)$(BINDIR)/split
	ln -sf cbase $(DESTDIR)$(BINDIR)/tail
	ln -sf cbase $(DESTDIR)$(BINDIR)/timeout
	ln -sf cbase $(DESTDIR)$(BINDIR)/touch
	ln -sf cbase $(DESTDIR)$(BINDIR)/tr
	ln -sf cbase $(DESTDIR)$(BINDIR)/true
	ln -sf cbase $(DESTDIR)$(BINDIR)/tsort
	ln -sf cbase $(DESTDIR)$(BINDIR)/tty
	ln -sf cbase $(DESTDIR)$(BINDIR)/uname
	ln -sf cbase $(DESTDIR)$(BINDIR)/uniq
	ln -sf cbase $(DESTDIR)$(BINDIR)/unvis
	ln -sf cbase $(DESTDIR)$(BINDIR)/vis
	ln -sf cbase $(DESTDIR)$(BINDIR)/wc
	ln -sf cbase $(DESTDIR)$(BINDIR)/yes
	ln -sf cbase $(DESTDIR)$(BINDIR)/freq
	ln -sf cbase $(DESTDIR)$(BINDIR)/unicode
	ln -sf cbase $(DESTDIR)$(BINDIR)/wisdom
	ln -sf cbase $(DESTDIR)$(BINDIR)/shsecret
	ln -sf cbase $(DESTDIR)$(BINDIR)/unifdef
	# `version` utility is deliberately un-symlinked
	install -m755 -d "${DESTDIR}/usr/share/man"
	cp -rf doc/man1 "${DESTDIR}/usr/share/man"
	cp -rf doc/man5 "${DESTDIR}/usr/share/man"
	cp -rf doc/man6 "${DESTDIR}/usr/share/man"
	cp -rf doc/man8 "${DESTDIR}/usr/share/man"
