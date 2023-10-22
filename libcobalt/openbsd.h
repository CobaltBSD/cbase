#pragma once

// Includes various BSD-specific functions

#include <stdio.h>
#include <sys/stat.h>
#include <inttypes.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/cdefs.h>
#include <signal.h>
#include<stddef.h>

#define GID_MAX 65535
#define UID_MAX 65535

#ifndef __dead
#define __dead
#endif

#ifndef DEFFILEMODE
#define DEFFILEMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH) // 0666
#endif

#define S_ISTXT S_ISVTX

#define SIGINFO 29

#define	timespecclear(tsp)		(tsp)->tv_sec = (tsp)->tv_nsec = 0
#define	timespecisset(tsp)		((tsp)->tv_sec || (tsp)->tv_nsec)
#define	timespeccmp(tsp, usp, cmp)					\
	(((tsp)->tv_sec == (usp)->tv_sec) ?				\
	    ((tsp)->tv_nsec cmp (usp)->tv_nsec) :			\
	    ((tsp)->tv_sec cmp (usp)->tv_sec))
#define	timespecsub(tsp, usp, vsp)					\
	do {								\
		(vsp)->tv_sec = (tsp)->tv_sec - (usp)->tv_sec;		\
		(vsp)->tv_nsec = (tsp)->tv_nsec - (usp)->tv_nsec;	\
		if ((vsp)->tv_nsec < 0) {				\
			(vsp)->tv_sec--;				\
			(vsp)->tv_nsec += 1000000000L;			\
		}							\
	} while (0)

#define	MNT_LOCAL	0x00001000
#define MNT_NOWAIT	2

#define	MFSNAMELEN	16	/* length of fs type name, including nul */

static const char *const sys_signame[NSIG] = {
	"Signal 0",
	"HUP",		/* SIGHUP */
	"INT",		/* SIGINT */
	"QUIT",		/* SIGQUIT */
	"ILL",		/* SIGILL */
	"TRAP",		/* SIGTRAP */
	"ABRT",		/* SIGABRT */
	"EMT",		/* SIGEMT */
	"FPE",		/* SIGFPE */
	"KILL",		/* SIGKILL */
	"BUS",		/* SIGBUS */
	"SEGV",		/* SIGSEGV */
	"SYS",		/* SIGSYS */
	"PIPE",		/* SIGPIPE */
	"ALRM",		/* SIGALRM */
	"TERM",		/* SIGTERM */
	"URG",		/* SIGURG */
	"STOP",		/* SIGSTOP */
	"TSTP",		/* SIGTSTP */
	"CONT",		/* SIGCONT */
	"CHLD",		/* SIGCHLD */
	"TTIN",		/* SIGTTIN */
	"TTOU",		/* SIGTTOU */
	"IO",		/* SIGIO */
	"XCPU",		/* SIGXCPU */
	"XFSZ",		/* SIGXFSZ */
	"VTALRM",	/* SIGVTALRM */
	"PROF",		/* SIGPROF */
	"WINCH",	/* SIGWINCH */
	"INFO",		/* SIGINFO */
	"USR1",		/* SIGUSR1 */
	"USR2",		/* SIGUSR2 */
	"THR",		/* SIGTHR */
};

// Specifically the portions of sys/stat.h that do not overlap with musl's version
/*
 * Definitions of flags stored in file flags word.
 *
 * Super-user and owner changeable flags.
 */
#define	UF_SETTABLE	0x0000ffff	/* mask of owner changeable flags */
#define	UF_NODUMP	0x00000001	/* do not dump file */
#define	UF_IMMUTABLE	0x00000002	/* file may not be changed */
#define	UF_APPEND	0x00000004	/* writes to file may only append */
#define	UF_OPAQUE	0x00000008	/* directory is opaque wrt. union */
/*
 * Super-user changeable flags.
 */
#define	SF_SETTABLE	0xffff0000	/* mask of superuser changeable flags */
#define	SF_ARCHIVED	0x00010000	/* file is archived */
#define	SF_IMMUTABLE	0x00020000	/* file may not be changed */
#define	SF_APPEND	0x00040000	/* writes to file may only append */

#define IPV6_MAXPACKET	65535

#define	IPTOS_DSCP_CS0		0x00
#define	IPTOS_DSCP_CS1		0x20
#define	IPTOS_DSCP_CS2		0x40
#define	IPTOS_DSCP_CS3		0x60
#define	IPTOS_DSCP_CS4		0x80
#define	IPTOS_DSCP_CS5		0xa0
#define	IPTOS_DSCP_CS6		0xc0
#define	IPTOS_DSCP_CS7		0xe0

#define IPV6_MAXHLIM	255

#define	RT_TABLEID_MAX		255

#define MACHINE "amd64"
#define MACHINE_ARCH "amd64"

#define	_PATH_LOGIN_CONF_D	"/etc/login.conf.d"
#define	_PATH_LOGIN_CONF	"/etc/login.conf"

#define	REG_STARTEND	00004

#define	_PATH_DEVDB	"/var/run/dev.db"

#define	WAIT_ANY	(-1)

// Get name of invoking program
const char *getprogname(void);

// Stub for pledging
int pledge(const char *promises, const char *execpromises);

long long strtonum(const char *numstr, long long minval, long long maxval, const char **errstrp);

mode_t getmode(const void *bbox, mode_t omode);

void *setmode(const char *p);

long long strtonum(const char *nptr, long long minval, long long maxval, const char **errstr);

int uid_from_user(const char *name, uid_t *uid);

int gid_from_group(const char *name, gid_t *gid);

void warnc(int code, const char *format, ...);

void vwarnc(int code, const char *fmt, va_list ap);

int chflags(const char *path, unsigned int flags);

void *recallocarray(void *ptr, size_t oldnmemb, size_t nmemb, size_t size);

void verrc(int eval, int code, const char *fmt, va_list ap);

void errc(int eval, int code, const char *fmt, ...);

// Stub for unveiling
int unveil(const char *path, const char *permissions);

char *getbsize(int *headerlenp, long *blocksizep);

#define EFTYPE		79

#define	M_32_SWAP(a) {							\
	u_int32_t _tmp = a;						\
	((char *)&a)[0] = ((char *)&_tmp)[3];				\
	((char *)&a)[1] = ((char *)&_tmp)[2];				\
	((char *)&a)[2] = ((char *)&_tmp)[1];				\
	((char *)&a)[3] = ((char *)&_tmp)[0];				\
}
#define	P_32_COPY(a, b) {						\
	((char *)&(b))[0] = ((char *)&(a))[3];				\
	((char *)&(b))[1] = ((char *)&(a))[2];				\
	((char *)&(b))[2] = ((char *)&(a))[1];				\
	((char *)&(b))[3] = ((char *)&(a))[0];				\
}
#define	M_16_SWAP(a) {							\
	u_int16_t _tmp = a;						\
	((char *)&a)[0] = ((char *)&_tmp)[1];				\
	((char *)&a)[1] = ((char *)&_tmp)[0];				\
}
#define	P_16_COPY(a, b) {						\
	((char *)&(b))[0] = ((char *)&(a))[1];				\
	((char *)&(b))[1] = ((char *)&(a))[0];				\
}

void strmode(int mode, char *p);

const char *user_from_uid(uid_t uid, int noname);

const char *group_from_gid(gid_t gid, int noname);

#define PT_OPENBSD_RANDOMIZE	0x65a3dbe6

#define FMT_SCALED_STRSIZE 7

int fmt_scaled(long long number, char *result);

int radixsort(const u_char **a, int n, const u_char *tab, u_int endch);

int sradixsort(const u_char **a, int n, const u_char *tab, u_int endch);

#if __BYTE_ORDER == __LITTLE_ENDIAN
#define betoh16(x) __bswap16(x)
#define betoh32(x) __bswap32(x)
#define betoh64(x) __bswap64(x)
#define letoh16(x) (uint16_t)(x)
#define letoh32(x) (uint32_t)(x)
#define letoh64(x) (uint64_t)(x)
#else
#define betoh16(x) (uint16_t)(x)
#define betoh32(x) (uint32_t)(x)
#define betoh64(x) (uint64_t)(x)
#define letoh16(x) __bswap16(x)
#define letoh32(x) __bswap32(x)
#define letoh64(x) __bswap64(x)
#endif

size_t strlcpy(char *dst, const char *src, size_t dsize);
size_t strlcat(char *dst, const char *src, size_t dsize);
char *fgetln(FILE *stream, size_t *len);
