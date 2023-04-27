all:
	$(CC) -l9 -I$(PWD)/p9include -fPIC bbuffered.c bfildes.c bflush.c bgetc.c bgetd.c bgetrune.c binit.c boffset.c bprint.c bputc.c bputrune.c brdline.c brdstr.c bread.c bseek.c bvprint.c bwrite.c -c
	ar -crs libbio.a *.o

clean:
	rm -fv *.o libbio.a
