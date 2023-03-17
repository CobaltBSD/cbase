#all: fortunes.dat fortunes2.dat startrek.dat zippy.dat fortunes-o fortunes-o.dat recipes.dat fortunes2-o.dat limerick.dat
all: fortunes.dat fortunes.dat fortunes2-o.dat limerick.dat startrek.dat zippy.dat recipes.dat fortunes-o.dat

install: fortunes fortunes2 startrek zippy recipes fortunes2-o limerick fortunes.dat fortunes2.dat startrek.dat zippy.dat fortunes-o fortunes-o.dat recipes.dat
	(cd $(PWD) && cp -v \
	    fortunes fortunes2 startrek zippy recipes $(DESTDIR)/usr/share/fortunes)
	cp -v fortunes.dat fortunes2.dat startrek.dat zippy.dat fortunes-o fortunes-o.dat recipes.dat \
	    $(DESTDIR)/usr/share/fortunes

fortunes.dat fortunes2.dat fortunes2-o.dat limerick.dat startrek.dat zippy.dat recipes.dat fortunes-o.dat:
	strfile -s $(PWD)/fortunes fortunes.dat
	strfile -s $(PWD)/fortunes2 fortunes2.dat
	strfile -s $(PWD)/fortunes2-o fortunes2-o.dat
	strfile -s $(PWD)/limerick limerick.dat
	strfile -s $(PWD)/startrek startrek.dat
	strfile -s $(PWD)/zippy zippy.dat
	strfile -s $(PWD)/recipes recipes.dat
	strfile -sx $(PWD)/fortunes-o fortunes-o.dat

clean:
	rm -fv *.dat

#fortunes-o: fortunes-o.real
#	tr [a-zA-Z] [n-za-mN-ZA-M] < fortunes-o.real > fortunes-o
