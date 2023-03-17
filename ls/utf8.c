/*	$OpenBSD: utf8.c,v 1.2 2016/01/18 19:06:37 schwarze Exp $	*/

/*
 * Copyright (c) 2015, 2016 Ingo Schwarze <schwarze@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef SMALL
#include <bsd/stdio.h>
#include <bsd/stdlib.h>
#include <bsd/wchar.h>
#include<fts.h>

extern int f_nonprint;

int
mbsprint(char const *name, int print)
{
	wchar_t	  wc;
	int	  len;  /* length in bytes of UTF-8 encoded string */
	int	  width;  /* display width of a single Unicode char */
	int	  total_width;  /* display width of the whole string */

	for (total_width = 0; *name != '\0'; name += len) {
		if ((len = mbtowc(&wc, name, MB_CUR_MAX)) == -1) {
			(void)mbtowc(NULL, NULL, MB_CUR_MAX);
			if (print)
				putchar(f_nonprint ? '?' : *name);
			total_width++;
			len = 1;
		} else if ((width = wcwidth(wc)) == -1) {
			if (print) {
				if (f_nonprint)
					putchar('?');
				else
					fwrite(name, 1, len, stdout);
			}
			total_width++;
		} else {
			if (print)
				fwrite(name, 1, len, stdout);
			total_width += width;
		}
	}
	return total_width;
}
#endif
