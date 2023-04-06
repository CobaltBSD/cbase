all:
	$(CC) -l9 -I$(PWD)/p9include -shared -fPIC bbuffered.c bfildes.c bflush.c bgetc.c bgetd.c bgetrune.c binit.c boffset.c bprint.c bputc.c bputrune.c brdline.c brdstr.c bread.c bseek.c bvprint.c bwrite.c -o libbio.so

clean:
	rm -fv libbio.so
