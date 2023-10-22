BLDS=	fortunes.dat fortunes-o.dat startrek.dat zippy.dat recipes.dat limerick.dat

all: $(BLDS)

clean:
	rm -fv *.dat strfile/strfile

install-datfiles: $(BLDS)
	install -d -m 755 $(DESTDIR)/usr/share/fortunes
	install -D -m 644 $(BLDS) $(DESTDIR)/usr/share/fortunes

$(BLDS): strfile/strfile
	./strfile/strfile -s datfiles/$(basename $@) $@

strfile/strfile:
	$(CC) -I../libcobalt -lcobalt -L../libcobalt -Wl,-rpath,../libcobalt strfile/strfile.c -o strfile/strfile
