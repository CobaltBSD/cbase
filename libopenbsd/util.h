#define	FMT_SCALED_STRSIZE	7	/* minus sign, 4 digits, suffix, null byte */

void logwtmp(const char *line, const char *name, const char *host);

int fmt_scaled(long long number, char *result);
