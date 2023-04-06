all:
	$(CC) -lfts -D__USE_MISC -D__S_IFSOCK -D_XOPEN_SOURCE -D_DEFAULT_SOURCE -lbsd fmt_scaled.c cmp.c ls.c main.c print.c util.c utf8.c color.c -o ls

clean:
	rm -fv ls
