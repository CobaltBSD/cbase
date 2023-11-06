/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2022 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ Permission to use, copy, modify, and/or distribute this software for         │
│ any purpose with or without fee is hereby granted, provided that the         │
│ above copyright notice and this permission notice appear in all copies.      │
│                                                                              │
│ THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL                │
│ WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED                │
│ WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE             │
│ AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL         │
│ DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR        │
│ PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER               │
│ TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR             │
│ PERFORMANCE OF THIS SOFTWARE.                                                │
╚─────────────────────────────────────────────────────────────────────────────*/
#include <string.h>
#include "pledge.private.h"

static int FindPromise(const char *name) {
  int i;
  for (i = 0; i < ARRAYLEN(kPledge); ++i) {
    if (!strcasecmp(name, kPledge[i].name)) {
      return i;
    }
  }
  return -1;
}

/**
 * Parses the arguments to pledge() into a bitmask.
 *
 * @return 0 on success, or -1 if invalid
 */
int ParsePromises(const char *promises, unsigned long *out) {
  int rc = 0;
  int promise;
  unsigned long ipromises;
  char *tok, *state, *start, buf[256];
  if (promises) {
    ipromises = -1;
    if (memccpy(buf, promises, 0, sizeof(buf))) {
      start = buf;
      while ((tok = strtok_r(start, " \t\r\n", &state))) {
        if ((promise = FindPromise(tok)) != -1) {
          ipromises &= ~(1ULL << promise);
        } else {
          rc = -1;
          break;
        }
        start = 0;
      }
    } else {
      rc = -1;
    }
  } else {
    ipromises = 0;
  }
  if (!rc) {
    *out = ipromises;
  }
  return rc;
}
