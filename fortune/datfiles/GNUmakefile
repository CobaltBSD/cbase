all: fortunes.dat fortunes2.dat startrek.dat zippy.dat fortunes-o fortunes-o.dat recipes.dat fortunes2-o.dat limerick.dat

fortunes.dat fortunes2.dat fortunes2-o.dat limerick.dat startrek.dat zippy.dat recipes.dat fortunes-o.dat:
	strfile -s $(PWD)/fortune/datfiles/fortunes fortunes.dat
	strfile -s $(PWD)/fortune/datfiles/fortunes2 fortunes2.dat
	strfile -s $(PWD)/fortune/datfiles/fortunes2-o fortunes2-o.dat
	strfile -s $(PWD)/fortune/datfiles/limerick limerick.dat
	strfile -s $(PWD)/fortune/datfiles/startrek startrek.dat
	strfile -s $(PWD)/fortune/datfiles/zippy zippy.dat
	strfile -s $(PWD)/fortune/datfiles/recipes recipes.dat
	strfile -sx $(PWD)/fortune/datfiles/fortunes-o fortunes-o.dat

clean:
	rm -fv $(PWD)/fortune/datfiles/*.dat
