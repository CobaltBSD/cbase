# We build doas separately and uncrunched, so that we don't need to setuid the entire cbase binary

CFLAGS+=-I../libcobalt
LDFLAGS+=-lcobalt -L../libcobalt -lcrypt

all: doas

doas: y.tab.c
	$(CC) $(CFLAGS) $(LDFLAGS) doas.c env.c shadow.c y.tab.c -o doas

install: doas
	install -D doas -m 4755 $(DESTDIR)/usr/bin/doas

clean:
	rm -fv doas y.tab.c

y.tab.c:
	$(YACC) parse.y
