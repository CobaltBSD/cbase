PREFIX = /usr

all:
	make -C lib9
	make -C libbio
	make -C fortune/datfiles
	crunchgen -m cbtutils-makefile cbtutils.conf 2>/dev/null
	make -f cbtutils-makefile CFLAGS="$(CFLAGS) -I$(PWD)/p9include"

clean:
	make -C lib9 clean
	make -C libbio clean
	find -name "*.o" -delete
	rm -fv *{_stub.c,.lo}
	rm -fv cbtutils{,.c{,ache},-makefile}

install:
	mkdir -pv $(DESTDIR)$(PREFIX)/bin
	cp -v cbtutils $(DESTDIR)$(PREFIX)/bin
	ln -sf cbtutils $(DESTDIR)$(PREFIX)/bin/banner
	ln -sf cbtutils $(DESTDIR)$(PREFIX)/bin/bs
	ln -sf cbtutils $(DESTDIR)$(PREFIX)/bin/fortune
	ln -sf cbtutils $(DESTDIR)$(PREFIX)/bin/strfile
	ln -sf cbtutils $(DESTDIR)$(PREFIX)/bin/unstr
	ln -sf cbtutils $(DESTDIR)$(PREFIX)/bin/freq
	ln -sf cbtutils $(DESTDIR)$(PREFIX)/bin/grdc
	ln -sf cbtutils $(DESTDIR)$(PREFIX)/bin/locale
	ln -sf cbtutils $(DESTDIR)$(PREFIX)/bin/ls
	ln -sf cbtutils $(DESTDIR)$(PREFIX)/bin/news
	ln -sf cbtutils $(DESTDIR)$(PREFIX)/bin/number
	ln -sf cbtutils $(DESTDIR)$(PREFIX)/bin/primes
	ln -sf cbtutils $(DESTDIR)$(PREFIX)/bin/rs
	ln -sf cbtutils $(DESTDIR)$(PREFIX)/bin/tetris
	ln -sf cbtutils $(DESTDIR)$(PREFIX)/bin/unicode
	ln -sf cbtutils $(DESTDIR)$(PREFIX)/bin/units
	ln -sf cbtutils $(DESTDIR)$(PREFIX)/bin/unutf
	mkdir -pv $(DESTDIR)$(PREFIX)/share/man/man{1,3,6}
	cp -v banner/banner.1 "$(DESTDIR)$(PREFIX)/share/man/man1"
	cp -v bs/bs.6 "$(DESTDIR)$(PREFIX)/share/man/man6"
	cp -v fortune/strfile/strfile.1 "$(DESTDIR)$(PREFIX)/share/man/man1"
	cp -v fortune/fortune/fortune.6 "$(DESTDIR)$(PREFIX)/share/man/man6"
	cp -v freq/freq.1 "$(DESTDIR)$(PREFIX)/share/man/man1"
	cp -v grdc/grdc.6 "$(DESTDIR)$(PREFIX)/share/man/man6"
	#cp -v libbio/bio.3 "$(DESTDIR)$(PREFIX)/share/man/man3"
	cp -v locale/locale.1 "$(DESTDIR)$(PREFIX)/share/man/man1"
	cp -v ls/ls.1 "$(DESTDIR)$(PREFIX)/share/man/man1"
	cp -v news/news.1 "$(DESTDIR)$(PREFIX)/share/man/man1"
	cp -v number/number.6 "$(DESTDIR)$(PREFIX)/share/man/man6"
	cp -v rs/rs.1 "$(DESTDIR)$(PREFIX)/share/man/man1"
	cp -v tetris/tetris.6 "$(DESTDIR)$(PREFIX)/share/man/man6"
	#cp -v unicode/ascii.1 "$(DESTDIR)$(PREFIX)/share/man/man1"
	cp -v units/units.1 "$(DESTDIR)$(PREFIX)/share/man/man1"
	mkdir -v $(DESTDIR)$(PREFIX)/share/fortunes
	cp -v fortune/datfiles/{fortunes{,2}{,-o},startrek,zippy,recipes,limerick}{,.dat} $(DESTDIR)$(PREFIX)/share/fortunes
	mkdir -v "$(DESTDIR)$(PREFIX)/share/news" # Note: Expects a $HOME/.local/share directory in order to save which news items have already been read
	cp -v units/units.lib "$(DESTDIR)$(PREFIX)/share"
