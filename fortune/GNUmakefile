BLDS=	fortunes.dat fortunes-o.dat startrek.dat zippy.dat recipes.dat limerick.dat

all: $(BLDS)

clean:
	rm -fv *.dat strfile/strfile

install-datfiles: $(BLDS)
	install -d -m 755 $(DESTDIR)/usr/share/fortunes
	install -m 644 $(BLDS) $(DESTDIR)/usr/share/fortunes
	install -m 644 $(addprefix datfiles/,$(basename $(BLDS))) $(DESTDIR)/usr/share/fortunes # Also need uncompiled files

$(BLDS): strfile/strfile
	./strfile/strfile -s datfiles/$(basename $@) $@

strfile/strfile:
	$(CC) -I../libcobalt -lcobalt -L../libcobalt -Wl,-rpath,../libcobalt strfile/strfile.c -o strfile/strfile
