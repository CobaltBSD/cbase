#pragma once

// From OpenBSD libutil/util.h

#define FMT_SCALED_STRSIZE 7

int fmt_scaled(long long number, char *result);
