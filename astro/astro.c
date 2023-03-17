#include	<u.h>
#include	<libc.h>

#ifdef VARARGCK
#pragma	varargck	type	"R"	double
#pragma	varargck	type	"D"	double
#endif

#undef sun
#define sun astrosun	/* not the machine! */
#undef fmod
#define fmod astrofmod	/* ours is always positive */

typedef	struct	Obj1	Obj1;
typedef	struct	Obj2	Obj2;
typedef	struct	Obj3	Obj3;
typedef	struct	Occ	Occ;
typedef	struct	Event	Event;
typedef	struct	Tim	Tim;
typedef	struct	Moontab	Moontab;

#define	NPTS	12
#define	PER	1.0

enum
{
	DARK	= 1<<0,
	SIGNIF	= 1<<1,
	PTIME	= 1<<2,
	LIGHT	= 1<<3
};

struct	Obj1
{
	double	ra;
	double	decl2;
	double	semi2;
	double	az;
	double	el;
	double	mag;
};
struct	Obj2
{
	char*	name;
	char*	name1;
	void	(*obj)(void);
	Obj1	point[NPTS+2];
};
struct	Obj3
{
	double	t1;
	double	e1;
	double	t2;
	double	e2;
	double	t3;
	double	e3;
	double	t4;
	double	e4;
	double	t5;
	double	e5;
};
struct Event
{
	char*	format;
	char*	arg1;
	char*	arg2;
	double	tim;
	int	flag;
};
struct	Moontab
{
	double	f;
	char	c[4];
};
struct	Occ
{
	Obj1	act;
	Obj1	del0;
	Obj1	del1;
	Obj1	del2;
};
struct	Tim
{
	double	ifa[5];
	char	tz[4];
};

double	converge;

char	flags[128];
int	nperiods;
double	wlong, awlong, nlat, elev;
double	obliq, phi, eps, tobliq;
double	dphi, deps;
double	day, deld, per;
double	eday, capt, capt2, capt3, gst;
double	pi, pipi, radian, radsec, deltat;
double	erad, glat;
double	xms, yms, zms;
double	xdot, ydot, zdot;
double	ecc, incl, node, argp, mrad, anom, motion;

double	lambda, beta, rad, mag, semi;
double	alpha, delta, rp, hp;
double	ra, decl, semi2;
double	lha, decl2, lmb2;
double	az, el;

double	meday, seday, mhp, salph, sdelt, srad;

double*	cafp;
char*	cacp;

double	rah, ram, ras, dday, dmin, dsec;
long	sao;
double	da, dd, px, epoch;
char	line[100];
Obj2	osun;
Obj2	omoon;
Obj2	oshad;
Obj2	omerc;
Obj2	ovenus;
Obj2	omars;
Obj2	osat;
Obj2	ouran;
Obj2	onept;
Obj2	oplut;
Obj2	ojup;
Obj2	ostar;
Obj2	ocomet;
Obj3	occ;
Obj2*	eobj1;
Obj2*	eobj2;

char*	startab;

extern	int	dmo[];
extern	Obj2*	objlst[];

extern	double	venfp[];
extern	char	vencp[];
extern	double	sunfp[];
extern	char	suncp[];
extern	double	mercfp[];
extern	char	merccp[];
extern	double	nutfp[];
extern	char	nutcp[];
extern	Moontab moontab[];

extern	void	args(int, char**);
extern	void	bdtsetup(double, Tim*);
extern	double	betcross(double);
extern	double	convdate(Tim*);
extern	double	cosadd(int, ...);
extern	double	cosx(double, int, int, int, int, double);
extern	double	dist(Obj1*, Obj1*);
extern	double	dsrc(double, Tim*, int);
extern	void	dtsetup(double, Tim*);
/*extern	int	evcomp(void*, void*);*/
extern	void	event(char*, char*, char*, double, int);
extern	void	evflush(void);
extern	double	fmod(double, double);
extern	void	fstar(void);
extern	void	fsun(void);
extern	void	geo(void);
extern	void	helio(void);
extern	void	icosadd(double*, char*);
extern	void	init(void);
extern	void	jup(void);
extern	int	lastsun(Tim*, int);
extern	int	main(int, char**);
extern	void	mars(void);
extern	double	melong(Obj2*);
extern	void	merc(void);
extern	void	moon(void);
extern	void	numb(int);
extern	void	nutate(void);
extern	void	occult(Obj2*, Obj2*, double);
extern	void	output(char*, Obj1*);
extern	void	pdate(double);
extern	double	pinorm(double);
extern	void	ptime(double);
extern	void	pstime(double);
extern	double	pyth(double);
extern	double	readate(void);
extern	double	readdt(void);
extern	void	readlat(int);
extern	double	rise(Obj2*, double);
extern	int	rline(int);
extern	void	sat(void);
extern	void	uran(void);
extern	void	nept(void);
extern	void	plut(void);
extern	void	satel(double);
extern	void	satels(void);
extern	void	search(void);
extern	double	set(Obj2*, double);
extern	void	set3pt(Obj2*, int, Occ*);
extern	void	setime(double);
extern	void	setobj(Obj1*);
extern	void	setpt(Occ*, double);
extern	void	shad(void);
extern	double	sinadd(int, ...);
extern	double	sinx(double, int, int, int, int, double);
extern	char*	skip(int);
extern	double	solstice(int);
extern	void	star(void);
extern	void	stars(void);
extern	void	sun(void);
extern	double	sunel(double);
extern	void	venus(void);
extern	int	vis(double, double, double, double);
extern	void	comet(void);
extern	int	Rconv(Fmt*);
extern	int	Dconv(Fmt*);
extern	double	etdate(long, int, double);


Obj2*	objlst[] =
{
	&osun,
	&omoon,
	&oshad,
	&omerc,
	&ovenus,
	&omars,
	&ojup,
	&osat,
	&ouran,
	&onept,
	&oplut,
	&ocomet,
	0
};

struct	idata
{
	char*	name;
	char*	name1;
	void	(*obj)(void);
} idata[] =
{
	"The sun",	"sun",		fsun,
	"The moon",	"moon",		moon,
	"The shadow",	"shadow",	shad,
	"Mercury",	"mercury",	merc,
	"Venus",	"venus",	venus,
	"Mars",		"mars",		mars,
	"Jupiter",	"jupiter",	jup,
	"Saturn",	"saturn",	sat,
	"Uranus",	"uranus",	uran,
	"Neptune",	"neptune",	nept,
	"Pluto",	"pluto",	plut,
	"Comet",	"comet",	comet
};

void
init(void)
{
	Obj2 *q;
	int i;

	glat = nlat - (692.74*radsec)*sin(2.*nlat)
		 + (1.16*radsec)*sin(4.*nlat);
	erad = .99832707e0 + .00167644e0*cos(2.*nlat)
		 - 0.352e-5*cos(4.*nlat)
		 + 0.001e-5*cos(6.*nlat)
		 + 0.1568e-6*elev;

	for(i=0; q=objlst[i]; i++) {
		q->name = idata[i].name;
		q->name1 = idata[i].name1;
		q->obj = idata[i].obj;
	}
	ostar.obj = fstar;
	ostar.name = "star";
}

void
setime(double d)
{
	double x, xm, ym, zm;

	eday = d + deltat/86400.;
	wlong = awlong + 15.*deltat*radsec;

	capt = eday/36524.220e0;
	capt2 = capt*capt;
	capt3 = capt*capt2;
	nutate();
	eday += .1;
	sun();
	srad = rad;
	xm = rad*cos(beta)*cos(lambda);
	ym = rad*cos(beta)*sin(lambda);
	zm = rad*sin(beta);
	eday -= .1;
	sun();
	xms = rad*cos(beta)*cos(lambda);
	yms = rad*cos(beta)*sin(lambda);
	zms = rad*sin(beta);
	x = .057756;
	xdot = x*(xm-xms);
	ydot = x*(ym-yms);
	zdot = x*(zm-zms);
}

void
setobj(Obj1 *op)
{
	Obj1 *p;

	p = op;
	p->ra = ra;
	p->decl2 = decl2;
	p->semi2 = semi2;
	p->az = az;
	p->el = el;
	p->mag = mag;
}

long	starsao = 0;

void
fstar(void)
{

	ra = ostar.point[0].ra;
	decl2 = ostar.point[0].decl2;
	semi2 = ostar.point[0].semi2;
	az = ostar.point[0].az;
	el = ostar.point[0].el;
	mag = ostar.point[0].mag;
}

void
fsun(void)
{

	beta = 0;
	rad = 0;
	lambda = 0;
	motion = 0;
	helio();
	geo();
	seday = eday;
	salph = alpha;
	sdelt = delta;
	mag = lmb2;
}

void
shad(void)
{

	if(seday != eday)
		fsun();
	if(meday != eday)
		moon();
	alpha = fmod(salph+pi, pipi);
	delta = -sdelt;
	hp = mhp;
	semi = 1.0183*mhp/radsec - 969.85/srad;
	geo();
}

char*	solstr[] =
{
	"Fall equinox",
	"Winter solstice",
	"Spring equinox",
	"Summer solstice"
};

struct
{
	double	beta;
	int	rta;
	int	dec;
	char	*betstr;
} bettab[] =
{
	-1.3572, 231,	50,	"Quadrantid",
	 0.7620, 336,	0,	"Eta aquarid",
	 1.5497, 260,	-20,	"Ophiuchid",
	 2.1324, 315,	-15,	"Capricornid",
	 2.1991, 339,	-17,	"Delta aquarid",
	 2.2158, 340,	-30,	"Pisces australid",
	 2.4331, 46,	58,	"Perseid",
	-2.6578, 95,	15,	"Orionid",
	-1.8678, 15,	-55,	"Phoenicid",
	-1.7260, 113,	32,	"Geminid",
	0
};

void
search(void)
{
	Obj2 *p, *q;
	int i, j;
	double t;

	for(i=0; objlst[i]; i++) {
		p = objlst[i];
		if(p == &oshad)
			continue;
		t = rise(p, -.833);
		if(t >= 0.)
			event("%s rises at ", p->name, "", t,
				i==0? PTIME: PTIME|DARK);
		t = set(p, -.833);
		if(t >= 0.)
			event("%s sets at ", p->name, "", t,
				i==0? PTIME: PTIME|DARK);
		if(p == &osun) {
			for(j=0; j<4; j++) {
				t = solstice(j);
				if(t >= 0)
					event("%s at ", solstr[j], "", t,
						SIGNIF|PTIME);
			}
			for(j=0; bettab[j].beta!=0; j++) {
				t = betcross(bettab[j].beta);
				if(t >= 0)
					event("%s  meeteeor shouwer",
					bettab[j].betstr, "", t, SIGNIF);
			}
			t = rise(p, -18);
			if(t >= 0)
				event("Twilight starts at ", "", "", t, PTIME);
			t = set(p, -18);
			if(t >= 0)
				event("Twilight ends at ", "", "", t, PTIME);
		}
		if(p == &omoon)
		for(j=0; j<NPTS; j++) {
			if(p->point[j].mag > .75 && p->point[j+1].mag < .25)
				event("New moon", "", "", 0, 0);
			if(p->point[j].mag <= .25 && p->point[j+1].mag > .25)
				event("First quarter moon", "", "", 0, 0);
			if(p->point[j].mag <= .50 && p->point[j+1].mag > .50)
				event("Full moon", "", "", 0, 0);
			if(p->point[j].mag <= .75 && p->point[j+1].mag > .75)
				event("Last quarter moon", "", "", 0, 0);
		}
		if(p == &omerc || p == &ovenus) {
			t = melong(p);
			if(t >= 0) {
				t = rise(p, 0) - rise(&osun, 0);
				if(t < 0)
					t += NPTS;
				if(t > NPTS)
					t -= NPTS;
				if(t > NPTS/2)
				event("Morning elongation of %s", p->name,
					"", 0, SIGNIF);
				else
				event("Evening elongation of %s", p->name,
					"", 0, SIGNIF);
			}
		}
		for(j=i; objlst[j]; j++) {
			if(i == j)
				continue;
			q = objlst[j];
			if(p == &omoon || q == &omoon) {
				occult(p, q, 0);
				if(occ.t3 < 0)
					continue;
				if(p == &osun || q == &oshad) {
					if(occ.t1 >= 0)
					event("Partial eclipse of %s begins at ", p->name, "",
						occ.t1, SIGNIF|PTIME);
					if(occ.t2 >= 0)
					event("Total eclipse of %s begins at ", p->name, "",
						occ.t2, SIGNIF|PTIME);
					if(occ.t4 >= 0)
					event("Total eclipse of %s ends at ", p->name, "",
						occ.t4, SIGNIF|PTIME);
					if(occ.t5 >= 0)
					event("Partial eclipse of %s ends at ", p->name, "",
						occ.t5, SIGNIF|PTIME);
				} else {
					if(occ.t1 >= 0)
					event("Occultation of %s begins at ", q->name, "",
						occ.t1, SIGNIF|PTIME);
					if(occ.t5 >= 0)
					event("Occultation of %s ends at ", q->name, "",
						occ.t5, SIGNIF|PTIME);
				}
				continue;
			}
			if(p == &osun) {
				if(q != &omerc && q != &ovenus)
					continue;
				occult(p, q, -1);
				if(occ.t3 >= 0.) {
					if(occ.t1 >= 0)
					event("Transit of %s begins at ", q->name, "",
						occ.t1, SIGNIF|LIGHT|PTIME);
					if(occ.t5 >= 0)
					event("Transit of %s ends at ", q->name, "",
						occ.t5, SIGNIF|LIGHT|PTIME);
				}
				continue;
			}
			t = dist(&p->point[0], &q->point[0]);
			if(t > 5000)
				continue;
			event("%s is in the house of %s",
				p->name, q->name, 0, 0);
		}
	}
	if(flags['o'])
		stars();
	if(flags['a'])
		satels();
	evflush();
}

char*	herefile;

int
main(int argc, char *argv[])
{
	int i, j;
	double d;

	pi = atan(1.0)*4;
	pipi = pi*2;
	radian = pi/180;
	radsec = radian/3600;
	converge = 1.0e-14;

	startab = unsharp("#9/sky/estartab");
	herefile = unsharp("#9/sky/here");

	fmtinstall('R', Rconv);
	fmtinstall('D', Dconv);

	per = PER;
	deld = PER/NPTS;
	init();
	args(argc, argv);
	init();

loop:
	d = day;
	pdate(d);
	if(flags['p'] || flags['e']) {
		print(" ");
		ptime(d);
		pstime(d);
	}
	print("\n");
	for(i=0; i<=NPTS+1; i++) {
		setime(d);

		for(j=0; objlst[j]; j++) {
			(*objlst[j]->obj)();
			setobj(&objlst[j]->point[i]);
			if(flags['p']) {
				if(flags['m'])
					if(strcmp(objlst[j]->name, "Comet"))
						continue;
				output(objlst[j]->name, &objlst[j]->point[i]);
			}
		}
		if(flags['e']) {
			d = dist(&eobj1->point[i], &eobj2->point[i]);
			print("dist %s to %s = %.4f\n", eobj1->name, eobj2->name, d);
		}
/*		if(flags['p']) { */
/*			pdate(d); */
/*			print(" "); */
/*			ptime(d); */
/*			print("\n"); */
/*		} */
		if(flags['p'] || flags['e'])
			break;
		d += deld;
	}
	if(!(flags['p'] || flags['e']))
		search();
	day += per;
	nperiods -= 1;
	if(nperiods > 0)
		goto loop;
	exits(0);
	return 0;		/* gcc */
}

void
args(int argc, char *argv[])
{
	char *p;
	long t;
	int f, i;
	Obj2 *q;

	memset(flags, 0, sizeof(flags));
	ARGBEGIN {
	default:
		fprint(2, "astro [-adeklmopst] [-c nperiod] [-C tperiod]\n");
		exits(0);

	case 'c':
		nperiods = 1;
		p = ARGF();
		if(p)
			nperiods = atol(p);
		flags['c']++;
		break;
	case 'C':
		p = ARGF();
		if(p)
			per = atof(p);
		break;
	case 'e':
		eobj1 = nil;
		eobj2 = nil;
		p = ARGF();
		if(p) {
			for(i=0; q=objlst[i]; i++) {
				if(strcmp(q->name, p) == 0)
					eobj1 = q;
				if(strcmp(q->name1, p) == 0)
					eobj1 = q;
			}
			p = ARGF();
			if(p) {
				for(i=0; q=objlst[i]; i++) {
					if(strcmp(q->name, p) == 0)
						eobj2 = q;
					if(strcmp(q->name1, p) == 0)
						eobj2 = q;
				}
			}
		}
		if(eobj1 && eobj2) {
			flags['e']++;
			break;
		}
		fprint(2, "cant recognize eclipse objects\n");
		exits("eflag");

	case 'a':
	case 'd':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'o':
	case 'p':
	case 's':
	case 't':
		flags[ARGC()]++;
		break;
	} ARGEND
	if(*argv){
		fprint(2, "usage: astro [-dlpsatokm] [-c nday] [-e obj1 obj2]\n");
		exits("usage");
	}

	t = time(0);
	day = t/86400. + 25567.5;
	if(flags['d'])
		day = readate();
	if(flags['j'])
		print("jday = %.4f\n", day);
	deltat = day * .001704;
	if(deltat > 32.184)		/* assume date is utc1 */
		deltat = 32.184;	/* correct by leap sec */
	if(flags['t'])
		deltat = readdt();

	if(flags['l']) {
		fprint(2, "nlat wlong elev\n");
		readlat(0);
	} else {
		f = open(herefile, OREAD);
		if(f < 0) {
			fprint(2, "%s?\n", herefile);
			/* btl mh */
			nlat = (40 + 41.06/60)*radian;
			awlong = (74 + 23.98/60)*radian;
			elev = 150 * 3.28084;
		} else {
			readlat(f);
			close(f);
		}
	}
}

double
readate(void)
{
	int i;
	Tim t;

	fprint(2, "year mo da hr min\n");
	rline(0);
	for(i=0; i<5; i++)
		t.ifa[i] = atof(skip(i));
	return convdate(&t);
}

double
readdt(void)
{

	fprint(2, "ΔT (sec) (%.3f)\n", deltat);
	rline(0);
	return atof(skip(0));
}

double
etdate(long year, int mo, double day)
{
	Tim t;

	t.ifa[0] = year;
	t.ifa[1] = mo;
	t.ifa[2] = day;
	t.ifa[3] = 0;
	t.ifa[4] = 0;
	return convdate(&t) + 2415020;
}

void
readlat(int f)
{

	rline(f);
	nlat = atof(skip(0)) * radian;
	awlong = atof(skip(1)) * radian;
	elev = atof(skip(2)) * 3.28084;
}

double
fmod(double a, double b)
{
	return a - floor(a/b)*b;
}
double
dist(Obj1 *p, Obj1 *q)
{
	double a;

	a = sin(p->decl2)*sin(q->decl2) +
		cos(p->decl2)*cos(q->decl2)*cos(p->ra-q->ra);
	a = fabs(atan2(pyth(a), a)) / radsec;
	return a;
}

int
rline(int f)
{
	char *p;
	int c;
	static char buf[1024];
	static int bc, bn, bf;

	if(bf != f) {
		bf = f;
		bn = 0;
	}
	p = line;
	do {
		if(bn <= 0) {
			bn = read(bf, buf, sizeof(buf));
			if(bn <= 0)
				return 1;
			bc = 0;
		}
		c = buf[bc];
		bn--; bc++;
		*p++ = c;
	} while(c != '\n');
	return 0;
}

double
sunel(double t)
{
	int i;

	i = floor(t);
	if(i < 0 || i > NPTS+1)
		return -90;
	t = osun.point[i].el +
		(t-i)*(osun.point[i+1].el - osun.point[i].el);
	return t;
}

double
rise(Obj2 *op, double el)
{
	Obj2 *p;
	int i;
	double e1, e2;

	e2 = 0;
	p = op;
	for(i=0; i<=NPTS; i++) {
		e1 = e2;
		e2 = p->point[i].el;
		if(i >= 1 && e1 <= el && e2 > el)
			goto found;
	}
	return -1;

found:
	return i - 1 + (el-e1)/(e2-e1);
}

double
set(Obj2 *op, double el)
{
	Obj2 *p;
	int i;
	double e1, e2;

	e2 = 0;
	p = op;
	for(i=0; i<=NPTS; i++) {
		e1 = e2;
		e2 = p->point[i].el;
		if(i >= 1 && e1 > el && e2 <= el)
			goto found;
	}
	return -1;

found:
	return i - 1 + (el-e1)/(e2-e1);
}

double
solstice(int n)
{
	int i;
	double d1, d2, d3;

	d3 = (n*pi)/2 - pi;
	if(n == 0)
		d3 += pi;
	d2 = 0.;
	for(i=0; i<=NPTS; i++) {
		d1 = d2;
		d2 = osun.point[i].ra;
		if(n == 0) {
			d2 -= pi;
			if(d2 < -pi)
				d2 += pipi;
		}
		if(i >= 1 && d3 >= d1 && d3 < d2)
			goto found;
	}
	return -1;

found:
	return i - (d3-d2)/(d1-d2);
}

double
betcross(double b)
{
	int i;
	double d1, d2;

	d2 = 0;
	for(i=0; i<=NPTS; i++) {
		d1 = d2;
		d2 = osun.point[i].mag;
		if(i >= 1 && b >= d1 && b < d2)
			goto found;
	}
	return -1;

found:
	return i - (b-d2)/(d1-d2);
}

double
melong(Obj2 *op)
{
	Obj2 *p;
	int i;
	double d1, d2, d3;

	d2 = 0;
	d3 = 0;
	p = op;
	for(i=0; i<=NPTS; i++) {
		d1 = d2;
		d2 = d3;
		d3 = dist(&p->point[i], &osun.point[i]);
		if(i >= 2 && d2 >= d1 && d2 >= d3)
			goto found;
	}
	return -1;

found:
	return i - 2;
}

#define	NEVENT	100
Event	events[NEVENT];
Event*	eventp = 0;

void
event(char *format, char *arg1, char *arg2, double tim, int flag)
{
	Event *p;

	if(flag & DARK)
		if(sunel(tim) > -12)
			return;
	if(flag & LIGHT)
		if(sunel(tim) < 0)
			return;
	if(eventp == 0)
		eventp = events;
	p = eventp;
	if(p >= events+NEVENT) {
		fprint(2, "too many events\n");
		return;
	}
	eventp++;
	p->format = format;
	p->arg1 = arg1;
	p->arg2 = arg2;
	p->tim = tim;
	p->flag = flag;
}

int	evcomp(const void*, const void*);

void
evflush(void)
{
	Event *p;

	if(eventp == 0)
		return;
	qsort(events, eventp-events, sizeof *p, evcomp);
	for(p = events; p<eventp; p++) {
		if((p->flag&SIGNIF) && flags['s'])
			print("ding ding ding ");
		print(p->format, p->arg1, p->arg2);
		if(p->flag & PTIME)
			ptime(day + p->tim*deld);
		print("\n");
	}
	eventp = 0;
}

int
evcomp(const void *a1, const void *a2)
{
	double t1, t2;
	Event *p1, *p2;

	p1 = (Event*)a1;
	p2 = (Event*)a2;
	t1 = p1->tim;
	t2 = p2->tim;
	if(p1->flag & SIGNIF)
		t1 -= 1000.;
	if(p2->flag & SIGNIF)
		t2 -= 1000.;
	if(t1 > t2)
		return 1;
	if(t2 > t1)
		return -1;
	return 0;
}

double
pyth(double x)
{

	x *= x;
	if(x > 1)
		x = 1;
	return sqrt(1-x);
}

char*
skip(int n)
{
	int i;
	char *cp;

	cp = line;
	for(i=0; i<n; i++) {
		while(*cp == ' ' || *cp == '\t')
			cp++;
		while(*cp != '\n' && *cp != ' ' && *cp != '\t')
			cp++;
	}
	while(*cp == ' ' || *cp == '\t')
		cp++;
	return cp;
}

static	double	elem_plut[] =
{
	36525.0,		/* [0] eday of epoc */

	39.48168677,		/* [1] semi major axis (au) */
	0.24880766,		/* [2] eccentricity */
 	17.14175,		/* [3] inclination (deg) */
	110.30347,		/* [4] longitude of the ascending node (deg) */
	224.06676,		/* [5] longitude of perihelion (deg) */
	238.92881,		/* [6] mean longitude (deg) */

	-0.00076912,		/* [1+6] (au/julian century) */
	0.00006465,		/* [2+6] (e/julian century) */
  	11.07,			/* [3+6] (arcsec/julian century) */
	-37.33,			/* [4+6] (arcsec/julian century) */
	-132.25,		/* [5+6] (arcsec/julian century) */
	522747.90,		/* [6+6] (arcsec/julian century) */
};

void
plut(void)
{
	double pturbl, pturbb, pturbr;
	double lograd;
	double dele, enom, vnom, nd, sl;

	double capj, capn, eye, comg, omg;
	double sb, su, cu, u, b, up;
	double sd, ca, sa;

	double cy;

	cy = (eday - elem_plut[0]) / 36525.;		/* per julian century */

	mrad = elem_plut[1] + elem_plut[1+6]*cy;
	ecc = elem_plut[2] + elem_plut[2+6]*cy;

	cy = cy / 3600;				/* arcsec/deg per julian century */
	incl = elem_plut[3] + elem_plut[3+6]*cy;
	node = elem_plut[4] + elem_plut[4+6]*cy;
	argp = elem_plut[5] + elem_plut[5+6]*cy;

	anom = elem_plut[6] + elem_plut[6+6]*cy - argp;
	motion = elem_plut[6+6] / 36525. / 3600;

	incl *= radian;
	node *= radian;
	argp *= radian;
	anom = fmod(anom,360.)*radian;

	enom = anom + ecc*sin(anom);
	do {
		dele = (anom - enom + ecc * sin(enom)) /
			(1. - ecc*cos(enom));
		enom += dele;
	} while(fabs(dele) > converge);
	vnom = 2.*atan2(sqrt((1.+ecc)/(1.-ecc))*sin(enom/2.),
		cos(enom/2.));
	rad = mrad*(1. - ecc*cos(enom));

	lambda = vnom + argp;
	pturbl = 0.;
	lambda += pturbl*radsec;
	pturbb = 0.;
	pturbr = 0.;

/*
 *	reduce to the ecliptic
 */

	nd = lambda - node;
	lambda = node + atan2(sin(nd)*cos(incl),cos(nd));

	sl = sin(incl)*sin(nd) + pturbb*radsec;
	beta = atan2(sl, pyth(sl));

	lograd = pturbr*2.30258509;
	rad *= 1. + lograd;


	lambda -= 1185.*radsec;
	beta -= 51.*radsec;

	motion *= radian*mrad*mrad/(rad*rad);
	semi = 83.33;

/*
 *	here begins the computation of magnitude
 *	first find the geocentric equatorial coordinates of Saturn
 */

	sd = rad*(cos(beta)*sin(lambda)*sin(obliq) +
		sin(beta)*cos(obliq));
	sa = rad*(cos(beta)*sin(lambda)*cos(obliq) -
		sin(beta)*sin(obliq));
	ca = rad*cos(beta)*cos(lambda);
	sd += zms;
	sa += yms;
	ca += xms;
	alpha = atan2(sa,ca);
	delta = atan2(sd,sqrt(sa*sa+ca*ca));

/*
 *	here are the necessary elements of Saturn's rings
 *	cf. Exp. Supp. p. 363ff.
 */

	capj = 6.9056 - 0.4322*capt;
	capn = 126.3615 + 3.9894*capt + 0.2403*capt2;
	eye = 28.0743 - 0.0128*capt;
	comg = 168.1179 + 1.3936*capt;
	omg = 42.9236 - 2.7390*capt - 0.2344*capt2;

	capj *= radian;
	capn *= radian;
	eye *= radian;
	comg *= radian;
	omg *= radian;

/*
 *	now find saturnicentric ring-plane coords of the earth
 */

	sb = sin(capj)*cos(delta)*sin(alpha-capn) -
		cos(capj)*sin(delta);
	su = cos(capj)*cos(delta)*sin(alpha-capn) +
		sin(capj)*sin(delta);
	cu = cos(delta)*cos(alpha-capn);
	u = atan2(su,cu);
	b = atan2(sb,sqrt(su*su+cu*cu));

/*
 *	and then the saturnicentric ring-plane coords of the sun
 */

	su = sin(eye)*sin(beta) +
		cos(eye)*cos(beta)*sin(lambda-comg);
	cu = cos(beta)*cos(lambda-comg);
	up = atan2(su,cu);

/*
 *	at last, the magnitude
 */


	sb = sin(b);
	mag = -8.68 +2.52*fabs(up+omg-u)-
		2.60*fabs(sb) + 1.25*(sb*sb);

	helio();
	geo();
}

void
merc(void)
{
	double pturbl, pturbr;
	double lograd;
	double dele, enom, vnom, nd, sl;
	double q0, v0, t0, j0 , s0;
	double lsun, elong, ci, dlong;

	ecc = .20561421 + .00002046*capt - 0.03e-6*capt2;
	incl = 7.0028806 + .0018608*capt - 18.3e-6*capt2;
	node = 47.145944 + 1.185208*capt + .0001739*capt2;
	argp = 75.899697 + 1.555490*capt + .0002947*capt2;
	mrad = .3870986;
	anom = 102.279381 + 4.0923344364*eday + 6.7e-6*capt2;
	motion = 4.0923770233;

	q0 = 102.28  + 4.092334429*eday;
	v0 = 212.536 + 1.602126105*eday;
	t0 = -1.45  + .985604737*eday;
	j0 = 225.36 + .083086735*eday;
	s0 = 175.68 + .033455441*eday;

	q0 *= radian;
	v0 *= radian;
	t0 *= radian;
	j0 *= radian;
	s0 *= radian;

	incl *= radian;
	node *= radian;
	argp *= radian;
	anom = fmod(anom, 360.)*radian;


	enom = anom + ecc*sin(anom);
	do {
		dele = (anom - enom + ecc * sin(enom)) /
			(1. - ecc*cos(enom));
		enom += dele;
	} while(fabs(dele) > converge);
	vnom = 2.*atan2(sqrt((1.+ecc)/(1.-ecc))*sin(enom/2.),
			cos(enom/2.));
	rad = mrad*(1. - ecc*cos(enom));

	icosadd(mercfp, merccp);
	pturbl =  cosadd(2, q0, -v0);
	pturbl += cosadd(2, q0, -t0);
	pturbl += cosadd(2, q0, -j0);
	pturbl += cosadd(2, q0, -s0);

	pturbr =  cosadd(2, q0, -v0);
	pturbr += cosadd(2, q0, -t0);
	pturbr += cosadd(2, q0, -j0);

/*
 *	reduce to the ecliptic
 */

	lambda = vnom + argp + pturbl*radsec;
	nd = lambda - node;
	lambda = node + atan2(sin(nd)*cos(incl), cos(nd));

	sl = sin(incl)*sin(nd);
	beta = atan2(sl, pyth(sl));

	lograd = pturbr*2.30258509;
	rad *= 1. + lograd;

	motion *= radian*mrad*mrad/(rad*rad);
	semi = 3.34;

	lsun = 99.696678 + 0.9856473354*eday;
	lsun *= radian;
	elong = lambda - lsun;
	ci = (rad - cos(elong))/sqrt(1. + rad*rad - 2.*rad*cos(elong));
	dlong = atan2(pyth(ci), ci)/radian;
	mag = -.003 + .01815*dlong + .0001023*dlong*dlong;

	helio();
	geo();
}


void
venus(void)
{
	double pturbl, pturbb, pturbr;
	double lograd;
	double dele, enom, vnom, nd, sl;
	double v0, t0, m0, j0, s0;
	double lsun, elong, ci, dlong;

/*
 *	here are the mean orbital elements
 */

	ecc = .00682069 - .00004774*capt + 0.091e-6*capt2;
	incl = 3.393631 + .0010058*capt - 0.97e-6*capt2;
	node = 75.779647 + .89985*capt + .00041*capt2;
	argp = 130.163833 + 1.408036*capt - .0009763*capt2;
	mrad = .7233316;
	anom = 212.603219 + 1.6021301540*eday + .00128605*capt2;
	motion = 1.6021687039;

/*
 *	mean anomalies of perturbing planets
 */

	v0 = 212.60 + 1.602130154*eday;
	t0 = 358.63  + .985608747*eday;
	m0 = 319.74 + 0.524032490*eday;
	j0 = 225.43 + .083090842*eday;
	s0 = 175.8  + .033459258*eday;

	v0 *= radian;
	t0 *= radian;
	m0 *= radian;
	j0 *= radian;
	s0 *= radian;

	incl *= radian;
	node *= radian;
	argp *= radian;
	anom = fmod(anom, 360.)*radian;

/*
 *	computation of long period terms affecting the mean anomaly
 */

	anom +=
		   (2.761-0.022*capt)*radsec*sin(
		  13.*t0 - 8.*v0 + 43.83*radian + 4.52*radian*capt)
		 + 0.268*radsec*cos(4.*m0 - 7.*t0 + 3.*v0)
		 + 0.019*radsec*sin(4.*m0 - 7.*t0 + 3.*v0)
		 - 0.208*radsec*sin(s0 + 1.4*radian*capt);

/*
 *	computation of elliptic orbit
 */

	enom = anom + ecc*sin(anom);
	do {
		dele = (anom - enom + ecc * sin(enom)) /
			(1 - ecc*cos(enom));
		enom += dele;
	} while(fabs(dele) > converge);
	vnom = 2*atan2(sqrt((1+ecc)/(1-ecc))*sin(enom/2),
		cos(enom/2));
	rad = mrad*(1 - ecc*cos(enom));

	lambda = vnom + argp;

/*
 *	perturbations in longitude
 */

	icosadd(venfp, vencp);
	pturbl = cosadd(4, v0, t0, m0, j0);
	pturbl *= radsec;

/*
 *	perturbations in latidude
 */

	pturbb = cosadd(3, v0, t0, j0);
	pturbb *= radsec;

/*
 *	perturbations in log radius vector
 */

	pturbr = cosadd(4, v0, t0, m0, j0);

/*
 *	reduction to the ecliptic
 */

	lambda += pturbl;
	nd = lambda - node;
	lambda = node + atan2(sin(nd)*cos(incl),cos(nd));

	sl = sin(incl)*sin(nd);
	beta = atan2(sl, pyth(sl)) + pturbb;

	lograd = pturbr*2.30258509;
	rad *= 1 + lograd;


	motion *= radian*mrad*mrad/(rad*rad);

/*
 *	computation of magnitude
 */

	lsun = 99.696678 + 0.9856473354*eday;
	lsun *= radian;
	elong = lambda - lsun;
	ci = (rad - cos(elong))/sqrt(1 + rad*rad - 2*rad*cos(elong));
	dlong = atan2(pyth(ci), ci)/radian;
	mag = -4 + .01322*dlong + .0000004247*dlong*dlong*dlong;

	semi = 8.41;

	helio();
	geo();
}

void
mars(void)
{
	double pturbl, pturbb, pturbr;
	double lograd;
	double dele, enom, vnom, nd, sl;
	double lsun, elong, ci, dlong;


	ecc = .09331290 + .000092064*capt;
	incl = 1.850333 - 6.75e-4*capt;
	node = 48.786442 + .770992*capt;
	argp = 334.218203 + 1.840758*capt + 1.30e-4*capt2;
	mrad = 1.5236915;
	anom = 319.529425 + .5240207666*eday + 1.808e-4*capt2;
	motion = 0.5240711638;


	incl = incl*radian;
	node = node*radian;
	argp = argp*radian;
	anom = fmod(anom,360.)*radian;

	enom = anom + ecc*sin(anom);
	do {
		dele = (anom - enom + ecc * sin(enom)) /
			(1. - ecc*cos(enom));
		enom += dele;
	} while(fabs(dele) > converge);
	vnom = 2.*atan2(sqrt((1.+ecc)/(1.-ecc))*sin(enom/2.),cos(enom/2.));
	rad = mrad*(1. - ecc*cos(enom));

	lambda = vnom + argp;
	pturbl = 0.;
	lambda = lambda + pturbl*radsec;
	pturbb = 0.;
	pturbr = 0.;

/*
 *	reduce to the ecliptic
 */

	nd = lambda - node;
	lambda = node + atan2(sin(nd)*cos(incl),cos(nd));

	sl = sin(incl)*sin(nd) + pturbb*radsec;
	beta = atan2(sl, pyth(sl));

	lograd = pturbr*2.30258509;
	rad *= 1. + lograd;


	motion *= radian*mrad*mrad/(rad*rad);
	semi = 4.68;

	lsun = 99.696678 + 0.9856473354*eday;
	lsun *= radian;
	elong = lambda - lsun;
	ci = (rad - cos(elong))/sqrt(1. + rad*rad - 2.*rad*cos(elong));
	dlong = atan2(pyth(ci), ci)/radian;
	mag = -1.30 + .01486*dlong;

	helio();
	geo();
}

void
jup(void)
{
	double pturbl, pturbb, pturbr;
	double lograd;
	double dele, enom, vnom, nd, sl;


	ecc = .0483376 + 163.e-6*capt;
	incl = 1.308660 - .0055*capt;
	node = 99.43785 + 1.011*capt;
	argp = 12.71165 + 1.611*capt;
	mrad = 5.202803;
	anom = 225.22165 + .0830912*eday - .0484*capt;
	motion = 299.1284/3600.;

	incl *= radian;
	node *= radian;
	argp *= radian;
	anom = fmod(anom,360.)*radian;

	enom = anom + ecc*sin(anom);
	do {
		dele = (anom - enom + ecc * sin(enom)) /
			(1. - ecc*cos(enom));
		enom += dele;
	} while(fabs(dele) > converge);
	vnom = 2.*atan2(sqrt((1.+ecc)/(1.-ecc))*sin(enom/2.),
		cos(enom/2.));
	rad = mrad*(1. - ecc*cos(enom));

	lambda = vnom + argp;

	pturbl = 0.;

	lambda += pturbl*radsec;

	pturbb = 0.;

	pturbr = 0.;

/*
 *	reduce to the ecliptic
 */

	nd = lambda - node;
	lambda = node + atan2(sin(nd)*cos(incl),cos(nd));

	sl = sin(incl)*sin(nd) + pturbb*radsec;
	beta = atan2(sl, pyth(sl));

	lograd = pturbr*2.30258509;
	rad *= 1. + lograd;


	lambda += 555.*radsec;
	beta -= 51.*radsec;
	motion *= radian*mrad*mrad/(rad*rad);
	semi = 98.47;

	mag = -8.93;
	helio();
	geo();
}

void
sat(void)
{
	double pturbl, pturbb, pturbr;
	double lograd;
	double dele, enom, vnom, nd, sl;

	double capj, capn, eye, comg, omg;
	double sb, su, cu, u, b, up;
	double sd, ca, sa;

	ecc = .0558900 - .000347*capt;
	incl = 2.49256 - .0044*capt;
	node = 112.78364 + .87306*capt;
	argp = 91.08897 + 1.95917*capt;
	mrad = 9.538843;
	anom = 175.47630 + .03345972*eday - .56527*capt;
	motion = 120.4550/3600.;

	incl *= radian;
	node *= radian;
	argp *= radian;
	anom = fmod(anom, 360.)*radian;

	enom = anom + ecc*sin(anom);
	do {
		dele = (anom - enom + ecc * sin(enom)) /
			(1. - ecc*cos(enom));
		enom += dele;
	} while(fabs(dele) > converge);
	vnom = 2.*atan2(sqrt((1.+ecc)/(1.-ecc))*sin(enom/2.),
		cos(enom/2.));
	rad = mrad*(1. - ecc*cos(enom));

	lambda = vnom + argp;
	pturbl = 0.;
	lambda += pturbl*radsec;
	pturbb = 0.;
	pturbr = 0.;

/*
 *	reduce to the ecliptic
 */

	nd = lambda - node;
	lambda = node + atan2(sin(nd)*cos(incl),cos(nd));

	sl = sin(incl)*sin(nd) + pturbb*radsec;
	beta = atan2(sl, pyth(sl));

	lograd = pturbr*2.30258509;
	rad *= 1. + lograd;


	lambda -= 1185.*radsec;
	beta -= 51.*radsec;

	motion *= radian*mrad*mrad/(rad*rad);
	semi = 83.33;

/*
 *	here begins the computation of magnitude
 *	first find the geocentric equatorial coordinates of Saturn
 */

	sd = rad*(cos(beta)*sin(lambda)*sin(obliq) +
		sin(beta)*cos(obliq));
	sa = rad*(cos(beta)*sin(lambda)*cos(obliq) -
		sin(beta)*sin(obliq));
	ca = rad*cos(beta)*cos(lambda);
	sd += zms;
	sa += yms;
	ca += xms;
	alpha = atan2(sa,ca);
	delta = atan2(sd,sqrt(sa*sa+ca*ca));

/*
 *	here are the necessary elements of Saturn's rings
 *	cf. Exp. Supp. p. 363ff.
 */

	capj = 6.9056 - 0.4322*capt;
	capn = 126.3615 + 3.9894*capt + 0.2403*capt2;
	eye = 28.0743 - 0.0128*capt;
	comg = 168.1179 + 1.3936*capt;
	omg = 42.9236 - 2.7390*capt - 0.2344*capt2;

	capj *= radian;
	capn *= radian;
	eye *= radian;
	comg *= radian;
	omg *= radian;

/*
 *	now find saturnicentric ring-plane coords of the earth
 */

	sb = sin(capj)*cos(delta)*sin(alpha-capn) -
		cos(capj)*sin(delta);
	su = cos(capj)*cos(delta)*sin(alpha-capn) +
		sin(capj)*sin(delta);
	cu = cos(delta)*cos(alpha-capn);
	u = atan2(su,cu);
	b = atan2(sb,sqrt(su*su+cu*cu));

/*
 *	and then the saturnicentric ring-plane coords of the sun
 */

	su = sin(eye)*sin(beta) +
		cos(eye)*cos(beta)*sin(lambda-comg);
	cu = cos(beta)*cos(lambda-comg);
	up = atan2(su,cu);

/*
 *	at last, the magnitude
 */


	sb = sin(b);
	mag = -8.68 +2.52*fabs(up+omg-u)-
		2.60*fabs(sb) + 1.25*(sb*sb);

	helio();
	geo();
}

static	double	elem_uran[] =
{
	36525.0,		/* [0] eday of epoc */

	19.19126393,		/* [1] semi major axis (au) */
	0.04716771,		/* [2] eccentricity */
 	0.76986,		/* [3] inclination (deg) */
	74.22988,		/* [4] longitude of the ascending node (deg) */
	170.96424,		/* [5] longitude of perihelion (deg) */
	313.23218,		/* [6] mean longitude (deg) */

	0.00152025,		/* [1+6] (au/julian century) */
	-0.00019150,		/* [2+6] (e/julian century) */
  	-2.09,			/* [3+6] (arcsec/julian century) */
	-1681.40,		/* [4+6] (arcsec/julian century) */
	1312.56,		/* [5+6] (arcsec/julian century) */
	1542547.79,		/* [6+6] (arcsec/julian century) */
};

void
uran(void)
{
	double pturbl, pturbb, pturbr;
	double lograd;
	double dele, enom, vnom, nd, sl;

	double capj, capn, eye, comg, omg;
	double sb, su, cu, u, b, up;
	double sd, ca, sa;

	double cy;

	cy = (eday - elem_uran[0]) / 36525.;		/* per julian century */

	mrad = elem_uran[1] + elem_uran[1+6]*cy;
	ecc = elem_uran[2] + elem_uran[2+6]*cy;

	cy = cy / 3600;				/* arcsec/deg per julian century */
	incl = elem_uran[3] + elem_uran[3+6]*cy;
	node = elem_uran[4] + elem_uran[4+6]*cy;
	argp = elem_uran[5] + elem_uran[5+6]*cy;

	anom = elem_uran[6] + elem_uran[6+6]*cy - argp;
	motion = elem_uran[6+6] / 36525. / 3600;

	incl *= radian;
	node *= radian;
	argp *= radian;
	anom = fmod(anom,360.)*radian;

	enom = anom + ecc*sin(anom);
	do {
		dele = (anom - enom + ecc * sin(enom)) /
			(1. - ecc*cos(enom));
		enom += dele;
	} while(fabs(dele) > converge);
	vnom = 2.*atan2(sqrt((1.+ecc)/(1.-ecc))*sin(enom/2.),
		cos(enom/2.));
	rad = mrad*(1. - ecc*cos(enom));

	lambda = vnom + argp;
	pturbl = 0.;
	lambda += pturbl*radsec;
	pturbb = 0.;
	pturbr = 0.;

/*
 *	reduce to the ecliptic
 */

	nd = lambda - node;
	lambda = node + atan2(sin(nd)*cos(incl),cos(nd));

	sl = sin(incl)*sin(nd) + pturbb*radsec;
	beta = atan2(sl, pyth(sl));

	lograd = pturbr*2.30258509;
	rad *= 1. + lograd;


	lambda -= 1185.*radsec;
	beta -= 51.*radsec;

	motion *= radian*mrad*mrad/(rad*rad);
	semi = 83.33;

/*
 *	here begins the computation of magnitude
 *	first find the geocentric equatorial coordinates of Saturn
 */

	sd = rad*(cos(beta)*sin(lambda)*sin(obliq) +
		sin(beta)*cos(obliq));
	sa = rad*(cos(beta)*sin(lambda)*cos(obliq) -
		sin(beta)*sin(obliq));
	ca = rad*cos(beta)*cos(lambda);
	sd += zms;
	sa += yms;
	ca += xms;
	alpha = atan2(sa,ca);
	delta = atan2(sd,sqrt(sa*sa+ca*ca));

/*
 *	here are the necessary elements of Saturn's rings
 *	cf. Exp. Supp. p. 363ff.
 */

	capj = 6.9056 - 0.4322*capt;
	capn = 126.3615 + 3.9894*capt + 0.2403*capt2;
	eye = 28.0743 - 0.0128*capt;
	comg = 168.1179 + 1.3936*capt;
	omg = 42.9236 - 2.7390*capt - 0.2344*capt2;

	capj *= radian;
	capn *= radian;
	eye *= radian;
	comg *= radian;
	omg *= radian;

/*
 *	now find saturnicentric ring-plane coords of the earth
 */

	sb = sin(capj)*cos(delta)*sin(alpha-capn) -
		cos(capj)*sin(delta);
	su = cos(capj)*cos(delta)*sin(alpha-capn) +
		sin(capj)*sin(delta);
	cu = cos(delta)*cos(alpha-capn);
	u = atan2(su,cu);
	b = atan2(sb,sqrt(su*su+cu*cu));

/*
 *	and then the saturnicentric ring-plane coords of the sun
 */

	su = sin(eye)*sin(beta) +
		cos(eye)*cos(beta)*sin(lambda-comg);
	cu = cos(beta)*cos(lambda-comg);
	up = atan2(su,cu);

/*
 *	at last, the magnitude
 */


	sb = sin(b);
	mag = -8.68 +2.52*fabs(up+omg-u)-
		2.60*fabs(sb) + 1.25*(sb*sb);

	helio();
	geo();
}

static	double	elem_nept[] =
{
	36525.0,		/* [0] eday of epoc */

	30.06896348,		/* [1] semi major axis (au) */
	0.00858587,		/* [2] eccentricity */
 	1.76917,		/* [3] inclination (deg) */
	131.72169,		/* [4] longitude of the ascending node (deg) */
	44.97135,		/* [5] longitude of perihelion (deg) */
	304.88003,		/* [6] mean longitude (deg) */

	-0.00125196,		/* [1+6] (au/julian century) */
	0.0000251,		/* [2+6] (e/julian century) */
  	-3.64,			/* [3+6] (arcsec/julian century) */
	-151.25,		/* [4+6] (arcsec/julian century) */
	-844.43,		/* [5+6] (arcsec/julian century) */
	786449.21,		/* [6+6] (arcsec/julian century) */
};

void
nept(void)
{
	double pturbl, pturbb, pturbr;
	double lograd;
	double dele, enom, vnom, nd, sl;

	double capj, capn, eye, comg, omg;
	double sb, su, cu, u, b, up;
	double sd, ca, sa;

	double cy;

	cy = (eday - elem_nept[0]) / 36525.;		/* per julian century */

	mrad = elem_nept[1] + elem_nept[1+6]*cy;
	ecc = elem_nept[2] + elem_nept[2+6]*cy;

	cy = cy / 3600;				/* arcsec/deg per julian century */
	incl = elem_nept[3] + elem_nept[3+6]*cy;
	node = elem_nept[4] + elem_nept[4+6]*cy;
	argp = elem_nept[5] + elem_nept[5+6]*cy;

	anom = elem_nept[6] + elem_nept[6+6]*cy - argp;
	motion = elem_nept[6+6] / 36525. / 3600;

	incl *= radian;
	node *= radian;
	argp *= radian;
	anom = fmod(anom,360.)*radian;

	enom = anom + ecc*sin(anom);
	do {
		dele = (anom - enom + ecc * sin(enom)) /
			(1. - ecc*cos(enom));
		enom += dele;
	} while(fabs(dele) > converge);
	vnom = 2.*atan2(sqrt((1.+ecc)/(1.-ecc))*sin(enom/2.),
		cos(enom/2.));
	rad = mrad*(1. - ecc*cos(enom));

	lambda = vnom + argp;
	pturbl = 0.;
	lambda += pturbl*radsec;
	pturbb = 0.;
	pturbr = 0.;

/*
 *	reduce to the ecliptic
 */

	nd = lambda - node;
	lambda = node + atan2(sin(nd)*cos(incl),cos(nd));

	sl = sin(incl)*sin(nd) + pturbb*radsec;
	beta = atan2(sl, pyth(sl));

	lograd = pturbr*2.30258509;
	rad *= 1. + lograd;


	lambda -= 1185.*radsec;
	beta -= 51.*radsec;

	motion *= radian*mrad*mrad/(rad*rad);
	semi = 83.33;

/*
 *	here begins the computation of magnitude
 *	first find the geocentric equatorial coordinates of Saturn
 */

	sd = rad*(cos(beta)*sin(lambda)*sin(obliq) +
		sin(beta)*cos(obliq));
	sa = rad*(cos(beta)*sin(lambda)*cos(obliq) -
		sin(beta)*sin(obliq));
	ca = rad*cos(beta)*cos(lambda);
	sd += zms;
	sa += yms;
	ca += xms;
	alpha = atan2(sa,ca);
	delta = atan2(sd,sqrt(sa*sa+ca*ca));

/*
 *	here are the necessary elements of Saturn's rings
 *	cf. Exp. Supp. p. 363ff.
 */

	capj = 6.9056 - 0.4322*capt;
	capn = 126.3615 + 3.9894*capt + 0.2403*capt2;
	eye = 28.0743 - 0.0128*capt;
	comg = 168.1179 + 1.3936*capt;
	omg = 42.9236 - 2.7390*capt - 0.2344*capt2;

	capj *= radian;
	capn *= radian;
	eye *= radian;
	comg *= radian;
	omg *= radian;

/*
 *	now find saturnicentric ring-plane coords of the earth
 */

	sb = sin(capj)*cos(delta)*sin(alpha-capn) -
		cos(capj)*sin(delta);
	su = cos(capj)*cos(delta)*sin(alpha-capn) +
		sin(capj)*sin(delta);
	cu = cos(delta)*cos(alpha-capn);
	u = atan2(su,cu);
	b = atan2(sb,sqrt(su*su+cu*cu));

/*
 *	and then the saturnicentric ring-plane coords of the sun
 */

	su = sin(eye)*sin(beta) +
		cos(eye)*cos(beta)*sin(lambda-comg);
	cu = cos(beta)*cos(lambda-comg);
	up = atan2(su,cu);

/*
 *	at last, the magnitude
 */


	sb = sin(b);
	mag = -8.68 +2.52*fabs(up+omg-u)-
		2.60*fabs(sb) + 1.25*(sb*sb);

	helio();
	geo();
}

#define	MAXE	(.999)	/* cant do hyperbolas */

struct elem
{
	double	t;	/* time of perihelion */
	double	q;	/* perihelion distance */
	double	e;	/* eccentricity */
	double	i;	/* inclination */
	double	w;	/* argument of perihelion */
	double	o;	/* longitude of ascending node */
};

struct elem
mkelem(double t, double q, double e, double i, double w, double o)
{
	struct elem el;

	el.t = t;
	el.q = q;
	el.e = e;
	el.i = i;
	el.w = w;
	el.o = o;
	return el;
}

void
comet(void)
{
	double pturbl, pturbb, pturbr;
	double lograd;
	double dele, enom, vnom, nd, sl;
	struct elem elem;

/*	elem = (struct elem)
	{
		etdate(1990, 5, 19.293),
		0.9362731,
		0.6940149,
		11.41096,
		198.77059,
		69.27130,
	};	/* p/schwassmann-wachmann 3, 1989d */
/*	elem = (struct elem)
	{
		etdate(1990, 4, 9.9761),
		0.349957,
		1.00038,
		58.9596,
		61.5546,
		75.2132,
	};	/* austin 3, 1989c */
/*	elem = (struct elem)
	{
		etdate(1990, 10, 24.36),
		0.9385,
		1.00038,
		131.62,
		242.58,
		138.57,
	};	/* levy 6 , 1990c */
/*	elem=(struct elem)
	{
		etdate(1996, 5, 1.3965),
		0.230035,
		0.999662,
		124.9098,
		130.2102,
		188.0430,
	};	/* C/1996 B2 (Hyakutake) */
/*	elem=(struct elem)
	{
		etdate(1997, 4, 1.13413),
		0.9141047,
		0.9950989,
		89.42932,
		130.59066,
		282.47069,
	};	/*C/1995 O1 (Hale-Bopp) */
/*	elem=(struct elem)
	{
		etdate(2000, 7, 26.1754),
		0.765126,
		0.999356,
		149.3904,
		151.0510,
		83.1909,
	};	/*C/1999 S4 (Linear) */
	elem = mkelem(
		etdate(2002, 3, 18.9784),
		0.5070601,
		0.990111,
		28.12106,
		34.6666,
		93.1206
	);	/*C/2002 C1 (Ikeya-Zhang) */

	ecc = elem.e;
	if(ecc > MAXE)
		ecc = MAXE;
	incl = elem.i * radian;
	node = (elem.o + 0.4593) * radian;
	argp = (elem.w + elem.o + 0.4066) * radian;
	mrad = elem.q / (1-ecc);
        motion = .01720209895 * sqrt(1/(mrad*mrad*mrad))/radian;
	anom = (eday - (elem.t - 2415020)) * motion * radian;
	enom = anom + ecc*sin(anom);

	do {
		dele = (anom - enom + ecc * sin(enom)) /
			(1 - ecc*cos(enom));
		enom += dele;
	} while(fabs(dele) > converge);

	vnom = 2*atan2(
		sqrt((1+ecc)/(1-ecc))*sin(enom/2),
		cos(enom/2));
	rad = mrad*(1-ecc*cos(enom));
	lambda = vnom + argp;
	pturbl = 0;
	lambda += pturbl*radsec;
	pturbb = 0;
	pturbr = 0;

/*
 *	reduce to the ecliptic
 */
	nd = lambda - node;
	lambda = node + atan2(sin(nd)*cos(incl),cos(nd));

	sl = sin(incl)*sin(nd) + pturbb*radsec;
	beta = atan2(sl, sqrt(1-sl*sl));

	lograd = pturbr*2.30258509;
	rad *= 1 + lograd;

	motion *= radian*mrad*mrad/(rad*rad);
	semi = 0;

	mag = 5.47 + 6.1/2.303*log(rad);

	helio();
	geo();
}

double	venfp[]	=
{
	4.889,		2.0788,
	11.261,		2.5870,
	7.128,		6.2384,
	3.446,		2.3721,
	1.034,		0.4632,
	1.575,		3.3847,
	1.439,		2.4099,
	1.208,		4.1464,
	2.966,		3.6318,
	1.563,		4.6829,
	0.,
	0.122,		4.2726,
	0.300,		0.0218,
	0.159,		1.3491,
	0.,
	2.246e-6,	0.5080,
	9.772e-6,	1.0159,
	8.271e-6,	4.6674,
	0.737e-6,	0.8267,
	1.426e-6,	5.1747,
	0.510e-6,	5.7009,
	1.572e-6,	1.8188,
	0.717e-6,	2.2969,
	2.991e-6,	2.0611,
	1.335e-6,	0.9628,
	0.
};

char	vencp[]	=
{
	1,-1,0,0,
	2,-2,0,0,
	3,-3,0,0,
	2,-3,0,0,
	4,-4,0,0,
	4,-5,0,0,
	3,-5,0,0,
	1,0,-3,0,
	1,0,0,-1,
	0,0,0,-1,

	0,-1,0,
	4,-5,0,
	1,0,-2,

	1,-1,0,0,
	2,-2,0,0,
	3,-3,0,0,
	2,-3,0,0,
	4,-4,0,0,
	5,-5,0,0,
	4,-5,0,0,
	2,0,-3,0,
	1,0,0,-1,
	2,0,0,-2
};

double	mercfp[] =
{
	0.013,		0.6807,
	0.048,		0.6283,
	0.185,		0.6231,
	0.711,		0.6191,
	0.285,		0.5784,
	0.075,		0.5411,
	0.019,		0.5585,
	0.010,		2.8449,
	0.039,		2.8117,
	0.147,		2.8135,
	0.552,		2.8126,
	2.100,		2.8126,
	3.724,		2.8046,
	0.729,		2.7883,
	0.186,		2.7890,
	0.049,		2.7943,
	0.013,		2.7402,
	0.033,		1.8361,
	0.118,		1.8396,
	0.431,		1.8391,
	1.329,		1.8288,
	0.539,		4.8686,
	0.111,		4.8904,
	0.027,		4.8956,
	0.012,		3.9794,
	0.056,		3.9636,
	0.294,		3.9910,
	0.484,		3.9514,
	0.070,		3.9270,
	0.018,		3.9270,
	0.013,		6.1261,
	0.050,		6.1052,
	0.185,		6.1069,
	0.685,		6.1011,
	2.810,		6.1062,
	7.356,		6.0699,
	1.471,		6.0685,
	0.375,		6.0687,
	0.098,		6.0720,
	0.026,		6.0476,
	0.062,		5.1540,
	0.122,		5.1191,
	0.011,		0.9076,
	0.074,		1.0123,
	0.106,		0.9372,
	0.017,		0.9425,
	0.020,		0.0506,
	0.052,		0.0384,
	0.052,		3.0281,
	0.012,		3.0543,
	0.011,		2.1642,
	0.016,		2.2340,
	0.040,		4.3912,
	0.080,		4.4262,
	0.016,		4.4506,
	0,

	0.014,		1.0996,
	0.056,		1.1153,
	0.219,		1.1160,
	0.083,		1.0734,
	0.024,		0.9442,
	0.018,		3.8432,
	0.070,		3.8293,
	0.256,		3.8230,
	0.443,		3.8132,
	0.080,		3.7647,
	0.020,		3.7734,
	0.019,		0.0000,
	0.133,		0.1134,
	0.129,		6.2588,
	0.026,		6.2413,
	0.026,		2.6599,
	0.087,		2.6232,
	0.374,		2.6496,
	0.808,		2.5470,
	0.129,		2.5587,
	0.019,		2.5534,
	0.012,		2.1642,
	0,

	0.014,		3.1416,
	0.047,		3.1625,
	0.179,		3.1695,
	0.697,		3.1603,
	0.574,		4.1315,
	0.181,		4.2537,
	0.047,		4.2481,
	0.013,		4.2062,
	0.018,		0.6650,
	0.069,		0.6405,
	0.253,		0.6449,
	0.938,		0.6454,
	3.275,		0.6458,
	0.499,		0.5569,
	0.119,		0.5271,
	0.032,		0.5184,
	0.030,		0.4939,
	0.106,		0.4171,
	0.353,		0.4510,
	0.056,		0.3840,
	0.013,		0.3142,
	0.028,		0.2531,
	0,

	0.034,		0.9512,
	0.060,		4.7962,
	0.028,		4.7124,
	0.028,		4.1836,
	0.102,		4.1871,
	0.380,		4.1864,
	0.059,		4.1818,
	0.015,		4.2185,
	0.012,		4.1713,
	0.050,		4.1870,
	0,

	0.218e-6,	5.3369,
	0.491e-6,	5.3281,
	0.172e-6,	2.1642,
	0.091e-6,	2.1084,
	0.204e-6,	1.2460,
	0.712e-6,	1.2413,
	2.370e-6,	1.2425,
	0.899e-6,	1.2303,
	0.763e-6,	4.3633,
	0.236e-6,	4.3590,
	0.163e-6,	0.2705,
	0.541e-6,	0.2710,
	1.157e-6,	0.2590,
	0.099e-6,	0.1798,
	0.360e-6,	2.4237,
	0.234e-6,	2.3740,
	0.253e-6,	4.5365,
	0.849e-6,	4.5293,
	2.954e-6,	4.5364,
	0.282e-6,	4.4581,
	1.550e-6,	1.3570,
	0.472e-6,	1.3561,
	0.135e-6,	1.3579,
	0.081e-6,	3.5936,
	0.087e-6,	3.5500,
	0.087e-6,	5.7334,
	0,

	0.181e-6,	5.8275,
	0.095e-6,	2.2427,
	0.319e-6,	2.2534,
	0.256e-6,	2.2403,
	0.157e-6,	4.8292,
	0.106e-6,	1.0332,
	0.397e-6,	1.0756,
	0.143e-6,	4.0980,
	0,

	0.222e-6,	1.6024,
	0.708e-6,	1.5949,
	0.191e-6,	5.7914,
	0.100e-6,	5.3564,
	0.347e-6,	5.3548,
	1.185e-6,	5.3576,
	3.268e-6,	5.3579,
	0.371e-6,	2.2148,
	0.160e-6,	2.1241,
	0.134e-6,	5.1260,
	0.347e-6,	5.1620,
	0
};

char	merccp[] =
{
	 4,	1,
	 3,	1,
	 2,	1,
	 1,	1,
	 0,	1,
	-1,	1,
	-2,	1,
	 6,	2,
	 5,	2,
	 4,	2,
	 3,	2,
	 2,	2,
	 1,	2,
	 0,	2,
	-1,	2,
	-2,	2,
	-3,	2,
	 5,	3,
	 4,	3,
	 3,	3,
	 2,	3,
	 1,	3,
	 0,	3,
	-1,	3,
	 5,	4,
	 4,	4,
	 3,	4,
	 2,	4,
	 1,	4,
	 0,	4,
	 7,	5,
	 6,	5,
	 5,	5,
	 4,	5,
	 3,	5,
	 2,	5,
	 1,	5,
	 0,	5,
	-1,	5,
	-2,	5,
	 4,	6,
	 3,	6,
	 5,	7,
	 4,	7,
	 3,	7,
	 2,	7,
	 5,	8,
	 4,	8,
	 3,	8,
	 2,	8,
	 5,	9,
	 4,	9,
	 5,	10,
	 4,	10,
	 3,	10,

	 3,	1,
	 2,	1,
	 1,	1,
	 0,	1,
	-1,	1,
	 4,	2,
	 3,	2,
	 2,	2,
	 1,	2,
	 0,	2,
	-1,	2,
	 3,	3,
	 2,	3,
	 1,	3,
	 0,	3,
	 4,	4,
	 3,	4,
	 2,	4,
	 1,	4,
	 0,	4,
	-1,	4,
	 2,	5,

	 4,	1,
	 3,	1,
	 2,	1,
	 1,	1,
	 0,	1,
	-1,	1,
	-2,	1,
	-3,	1,
	 5,	2,
	 4,	2,
	 3,	2,
	 2,	2,
	 1,	2,
	 0,	2,
	-1,	2,
	-2,	2,
	 3,	3,
	 2,	3,
	 1,	3,
	 0,	3,
	-1,	3,
	 1,	4,

	 1,	1,
	 0,	1,
	-1,	1,
	 3,	2,
	 2,	2,
	 1,	2,
	 0,	2,
	-1,	2,
	 2,	3,
	 1,	3,

	 2,	1,
	 1,	1,
	 0,	1,
	-1,	1,
	 4,	2,
	 3,	2,
	 2,	2,
	 1,	2,
	 0,	2,
	-1,	2,
	 4,	3,
	 3,	3,
	 2,	3,
	 0,	3,
	 3,	4,
	 2,	4,
	 5,	5,
	 4,	5,
	 3,	5,
	 2,	5,
	 1,	5,
	 0,	5,
	-1,	5,
	 4,	6,
	 3,	6,
	 4,	7,

	 1,	1,
	 3,	2,
	 2,	2,
	 1,	2,
	 2,	3,
	 3,	4,
	 2,	4,
	 0,	4,

	 2,	1,
	 1,	1,
	-1,	1,
	 4,	2,
	 3,	2,
	 2,	2,
	 1,	2,
	 0,	2,
	-1,	2,
	 2,	3,
	 1,	3
};


char*	month[] =
{
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};

double
dsrc(double d, Tim *t, int i)
{
	double y;

	do {
		t->ifa[i] += 1.;
		y = convdate(t);
	} while(d >= y);
	do {
		t->ifa[i] -= 1.;
		y = convdate(t);
	} while(d < y);
	return d - y;
}

void
dtsetup(double d, Tim *t)
{
	double v;

	t->ifa[0] = floor(1900 + d/365.24220);
	t->ifa[1] = 1;
	t->ifa[2] = 1;
	t->ifa[3] = 0;
	t->ifa[4] = 0;
	t->ifa[1] = floor(1 + dsrc(d, t, 0)/30);
	t->ifa[2] = floor(1 + dsrc(d, t, 1));
	dsrc(d, t, 2);

	v = (d - convdate(t)) * 24;
	t->ifa[3] = floor(v);
	t->ifa[4] = (v - t->ifa[3]) * 60;
	convdate(t);	/* to set timezone */
}

void
pdate(double d)
{
	int i;
	Tim t;

	dtsetup(d, &t);
	if(flags['s']) {
		i = t.ifa[1];
		print("%s ", month[i-1]);
		i = t.ifa[2];
		numb(i);
		print("...");
		return;
	}

	/* year month day */
	print("%4d %2d %2d",
		(int)t.ifa[0],
		(int)t.ifa[1],
		(int)t.ifa[2]);
}

void
ptime(double d)
{
	int h, m, s;
	char *mer;
	Tim t;

	if(flags['s']) {
		/* hour minute */
		dtsetup(d + .5/(24*60), &t);
		h = t.ifa[3];
		m = floor(t.ifa[4]);

		mer = "AM";
		if(h >= 12) {
			mer = "PM";
			h -= 12;
		}
		if(h == 0)
			h = 12;
		numb(h);
		if(m < 10) {
			if(m == 0) {
				print("%s exactly ...", mer);
				return;
			}
			print("O ");
		}
		numb(m);
		print("%s ...", mer);
		return;
	}
	/* hour minute second */
	dtsetup(d, &t);
	h = t.ifa[3];
	m = floor(t.ifa[4]);
	s = floor((t.ifa[4]-m) * 60);
	print("%.2d:%.2d:%.2d %.*s", h, m, s, utfnlen(t.tz, 3), t.tz);
}

char*	unit[] =
{
	"zero",
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine",
	"ten",
	"eleven",
	"twelve",
	"thirteen",
	"fourteen",
	"fifteen",
	"sixteen",
	"seventeen",
	"eighteen",
	"nineteen"
};
char*	decade[] =
{
	"twenty",
	"thirty",
	"forty",
	"fifty",
	"sixty",
	"seventy",
	"eighty",
	"ninety"
};

void
pstime(double d)
{

	setime(d);

	semi = 0;
	motion = 0;
	rad = 1.e9;
	lambda = 0;
	beta = 0;

/* uses lambda, beta, rad, motion */
/* sets alpha, delta, rp */

	helio();

/* uses alpha, delta, rp */
/* sets ra, decl, lha, decl2, az, el */

	geo();

	print(" %R %D %D %4.0f", lha, nlat, awlong, elev/3.28084);
}

void
numb(int n)
{

	if(n >= 100) {
		print("%d ", n);
		return;
	}
	if(n >= 20) {
		print("%s ", decade[n/10 - 2]);
		n %= 10;
		if(n == 0)
			return;
	}
	print("%s ", unit[n]);
}

double
tzone(double y, Tim *z)
{
	double t, l1, l2;
	Tm t1, t2;

	/*
	 * get a rough approximation to unix mean time
	 */
	t = (y - 25567.5) * 86400;

	/*
	 * if outside unix conversions,
	 * just call it GMT
	 */
	if(t < 0 || t > 2.1e9)
		return y;

	/*
	 * convert by both local and gmt
	 */
	t1 = *localtime((long)t);
	t2 = *gmtime((long)t);

	/*
	 * pick up year crossings
	 */
	if(t1.yday == 0 && t2.yday > 1)
		t1.yday = t2.yday+1;
	if(t2.yday == 0 && t1.yday > 1)
		t2.yday = t1.yday+1;

	/*
	 * convert times to days
	 */
	l1 = t1.yday + t1.hour/24. + t1.min/1440. + t1.sec/86400.;
	l2 = t2.yday + t2.hour/24. + t2.min/1440. + t2.sec/86400.;

	/*
	 * return difference
	 */
	strncpy(z->tz, t1.zone, sizeof(z->tz));
	return y + (l2 - l1);
}

int	dmo[12] =
{
	0,
	31,
	59,
	90,
	120,
	151,
	181,
	212,
	243,
	273,
	304,
	334
};

/*
 * input date conversion
 * output is done by zero crossing
 * on this input conversion.
 */
double
convdate(Tim *t)
{
	double y, d;
	int m;

	y = t->ifa[0];
	m = t->ifa[1];
	d = t->ifa[2];

	/*
	 * normalize the month
	 */
	while(m < 1) {
		m += 12;
		y -= 1;
	}
	while(m > 12) {
		m -= 12;
		y += 1;
	}

	/*
	 * bc correction
	 */
	if(y < 0)
		y += 1;

	/*
	 * normal conversion
	 */
	y += 4712;
	if(fmod(y, 4) == 0 && m > 2)
		d += 1;
	y = y*365 + floor((y+3)/4) + dmo[m-1] + d - 1;

	/*
	 * gregorian change
	 */
	if(y > 2361232)
		y -= floor((y-1794167)/36524.220) -
			floor((y-1721117)/146100);
	y += t->ifa[3]/24 + t->ifa[4]/1440 - 2415020.5;

	/*
	 * kitchen clock correction
	 */
	strncpy(t->tz, "GMT", sizeof(t->tz));
	if(flags['k'])
		y = tzone(y, t);
	return y;
}


void
icosadd(double *fp, char *cp)
{

	cafp = fp;
	cacp = cp;
}

double
cosadd(int n, ...)
{
	double *coefp, coef[10];
	char *cp;
	int i;
	double sum, a1, a2;
	va_list arg;

	sum = 0;
	cp = cacp;
	va_start(arg, n);
	for(i=0; i<n; i++)
		coef[i] = va_arg(arg, double);
	va_end(arg);

loop:
	a1 = *cafp++;
	if(a1 == 0) {
		cacp = cp;
		return sum;
	}
	a2 = *cafp++;
	i = n;
	coefp = coef;
	do
		a2 += *cp++ * *coefp++;
	while(--i);
	sum += a1 * cos(a2);
	goto loop;
}

double
sinadd(int n, ...)
{
	double *coefp, coef[10];
	char *cp;
	int i;
	double sum, a1, a2;
	va_list arg;

	sum = 0;
	cp = cacp;
	va_start(arg, n);
	for(i=0; i<n; i++)
		coef[i] = va_arg(arg, double);
	va_end(arg);

loop:
	a1 = *cafp++;
	if(a1 == 0) {
		cacp = cp;
		return sum;
	}
	a2 = *cafp++;
	i = n;
	coefp = coef;
	do
		a2 += *cp++ * *coefp++;
	while(--i);
	sum += a1 * sin(a2);
	goto loop;
}

Occ	 o1, o2;
Obj2	 xo1, xo2;

void
occult(Obj2 *p1, Obj2 *p2, double d)
{
	int i, i1, N;
	double d1, d2, d3, d4;
	double x, di, dx, x1;

	USED(d);

	d3 = 0;
	d2 = 0;
	occ.t1 = -100;
	occ.t2 = -100;
	occ.t3 = -100;
	occ.t4 = -100;
	occ.t5 = -100;
	for(i=0; i<=NPTS+1; i++) {
		d1 = d2;
		d2 = d3;
		d3 = dist(&p1->point[i], &p2->point[i]);
		if(i >= 2 && d2 <= d1 && d2 <= d3)
			goto found;
	}
	return;

found:
	N = 2880*PER/NPTS; /* 1 min steps */
	i -= 2;
	set3pt(p1, i, &o1);
	set3pt(p2, i, &o2);

	di = i;
	x = 0;
	dx = 2./N;
	for(i=0; i<=N; i++) {
		setpt(&o1, x);
		setpt(&o2, x);
		d1 = d2;
		d2 = d3;
		d3 = dist(&o1.act, &o2.act);
		if(i >= 2 && d2 <= d1 && d2 <= d3)
			goto found1;
		x += dx;
	}
	fprint(2, "bad 1 \n");
	return;

found1:
	if(d2 > o1.act.semi2+o2.act.semi2+50)
		return;
	di += x - 3*dx;
	x = 0;
	for(i=0; i<3; i++) {
		setime(day + deld*(di + x));
		(*p1->obj)();
		setobj(&xo1.point[i]);
		(*p2->obj)();
		setobj(&xo2.point[i]);
		x += 2*dx;
	}
	dx /= 60;
	x = 0;
	set3pt(&xo1, 0, &o1);
	set3pt(&xo2, 0, &o2);
	for(i=0; i<=240; i++) {
		setpt(&o1, x);
		setpt(&o2, x);
		d1 = d2;
		d2 = d3;
		d3 = dist(&o1.act, &o2.act);
		if(i >= 2 && d2 <= d1 && d2 <= d3)
			goto found2;
		x += 1./120.;
	}
	fprint(2, "bad 2 \n");
	return;

found2:
	if(d2 > o1.act.semi2 + o2.act.semi2)
		return;
	i1 = i-1;
	x1 = x - 1./120.;
	occ.t3 = di + i1 * dx;
	occ.e3 = o1.act.el;
	d3 = o1.act.semi2 - o2.act.semi2;
	if(d3 < 0)
		d3 = -d3;
	d4 = o1.act.semi2 + o2.act.semi2;
	for(i=i1,x=x1;; i++) {
		setpt(&o1, x);
		setpt(&o2, x);
		d1 = d2;
		d2 = dist(&o1.act, &o2.act);
		if(i != i1) {
			if(d1 <= d3 && d2 > d3) {
				occ.t4 = di + (i-.5) * dx;
				occ.e4 = o1.act.el;
			}
			if(d2 > d4) {
				if(d1 <= d4) {
					occ.t5 = di + (i-.5) * dx;
					occ.e5 = o1.act.el;
				}
				break;
			}
		}
		x += 1./120.;
	}
	for(i=i1,x=x1;; i--) {
		setpt(&o1, x);
		setpt(&o2, x);
		d1 = d2;
		d2 = dist(&o1.act, &o2.act);
		if(i != i1) {
			if(d1 <= d3 && d2 > d3) {
				occ.t2 = di + (i+.5) * dx;
				occ.e2 = o1.act.el;
			}
			if(d2 > d4) {
				if(d1 <= d4) {
					occ.t1 = di + (i+.5) * dx;
					occ.e1 = o1.act.el;
				}
				break;
			}
		}
		x -= 1./120.;
	}
}

void
setpt(Occ *o, double x)
{
	double y;

	y = x * (x-1);
	o->act.ra = o->del0.ra +
		x*o->del1.ra + y*o->del2.ra;
	o->act.decl2 = o->del0.decl2 +
		x*o->del1.decl2 + y*o->del2.decl2;
	o->act.semi2 = o->del0.semi2 +
		x*o->del1.semi2 + y*o->del2.semi2;
	o->act.el = o->del0.el +
		x*o->del1.el + y*o->del2.el;
}


double
pinorm(double a)
{

	while(a < -pi)
		a += pipi;
	while(a > pi)
		a -= pipi;
	return a;
}

void
set3pt(Obj2 *p, int i, Occ *o)
{
	Obj1 *p1, *p2, *p3;
	double a;

	p1 = p->point+i;
	p2 = p1+1;
	p3 = p2+1;

	o->del0.ra = p1->ra;
	o->del0.decl2 = p1->decl2;
	o->del0.semi2 = p1->semi2;
	o->del0.el = p1->el;

	a = p2->ra - p1->ra;
	o->del1.ra = pinorm(a);
	a = p2->decl2 - p1->decl2;
	o->del1.decl2 = pinorm(a);
	o->del1.semi2 = p2->semi2 - p1->semi2;
	o->del1.el = p2->el - p1->el;

	a = p1->ra + p3->ra - 2*p2->ra;
	o->del2.ra = pinorm(a)/2;
	a = p1->decl2 + p3->decl2 - 2*p2->decl2;
	o->del2.decl2 = pinorm(a)/2;
	o->del2.semi2 = (p1->semi2 + p3->semi2 - 2*p2->semi2) / 2;
	o->del2.el = (p1->el + p3->el - 2*p2->el) / 2;
}

char*	satlst[] =
{
	0
};

struct
{
	double	time;
	double	tilt;
	double	pnni;
	double	psi;
	double	ppi;
	double	d1pp;
	double	peri;
	double	d1per;
	double	e0;
	double	deo;
	double	rdp;
	double	st;
	double	ct;
	double	rot;
	double	semi;
} satl;

void
satels(void)
{
	double ifa[10], t, t1, t2, tinc;
	char **satp;
	int flag, f, i, n;

	satp = satlst;

loop:
	if(*satp == 0)
		return;
	f = open(*satp, 0);
	if(f < 0) {
		fprint(2, "cannot open %s\n", *satp);
		satp += 2;
		goto loop;
	}
	satp++;
	rline(f);
	tinc = atof(skip(6));
	rline(f);
	rline(f);
	for(i=0; i<9; i++)
		ifa[i] = atof(skip(i));
	n = ifa[0];
	i = ifa[1];
	t = dmo[i-1] + ifa[2] - 1.;
	if(n%4 == 0 && i > 2)
		t += 1.;
	for(i=1970; i<n; i++) {
		t += 365.;
		if(i%4 == 0)
			t += 1.;
	}
	t = (t * 24. + ifa[3]) * 60. + ifa[4];
	satl.time = t * 60.;
	satl.tilt = ifa[5] * radian;
	satl.pnni = ifa[6] * radian;
	satl.psi = ifa[7];
	satl.ppi = ifa[8] * radian;
	rline(f);
	for(i=0; i<5; i++)
		ifa[i] = atof(skip(i));
	satl.d1pp = ifa[0] * radian;
	satl.peri = ifa[1];
	satl.d1per = ifa[2];
	satl.e0 = ifa[3];
	satl.deo = 0;
	satl.rdp = ifa[4];

	satl.st = sin(satl.tilt);
	satl.ct = cos(satl.tilt);
	satl.rot = pipi / (1440. + satl.psi);
	satl.semi = satl.rdp * (1. + satl.e0);

	n = PER*288.; /* 5 min steps */
	t = day;
	for(i=0; i<n; i++) {
		if(sunel((t-day)/deld) > 0.)
			goto out;
		satel(t);
		if(el > 0) {
			t1 = t;
			flag = 0;
			do {
				if(el > 30.)
					flag++;
				t -= tinc/(24.*3600.);
				satel(t);
			} while(el > 0.);
			t2 = (t - day)/deld;
			t = t1;
			do {
				t += tinc/(24.*3600.);
				satel(t);
				if(el > 30.)
					flag++;
			} while(el > 0.);
			if(flag)
				if((*satp)[0] == '-')
					event("%s pass at ", (*satp)+1, "",
						t2, SIGNIF+PTIME+DARK); else
					event("%s pass at ", *satp, "",
						t2, PTIME+DARK);
		}
	out:
		t += 5./(24.*60.);
	}
	close(f);
	satp++;
	goto loop;
}

void
satel(double time)
{
	int i;
	double amean, an, coc, csl, d, de, enom, eo;
	double pp, q, rdp, slong, ssl, t, tp;

	i = 500;
	el = -1;
	time = (time-25567.5) * 86400;
	t = (time - satl.time)/60;
	if(t < 0)
		return; /* too early for satelites */
	an = floor(t/satl.peri);
	while(an*satl.peri + an*an*satl.d1per/2. <= t) {
		an += 1;
		if(--i == 0)
			return;
	}
	while((tp = an*satl.peri + an*an*satl.d1per/2.) > t) {
		an -= 1;
		if(--i == 0)
			return;
	}
	amean = (t-tp)/(satl.peri+(an+.5)*satl.d1per);
	pp = satl.ppi+(an+amean)*satl.d1pp;
	amean *= pipi;
	eo = satl.e0+satl.deo*an;
	rdp = satl.semi/(1+eo);
	enom = amean+eo*sin(amean);
	do {
		de = (amean-enom+eo*sin(enom))/(1.0-eo*cos(enom));
		enom += de;
		if(--i == 0)
			return;
	} while(fabs(de) >= 1.0e-6);
	q = 3963.35*erad/(rdp*(1-eo*cos(enom))/(1-eo));
	d = pp + 2*atan2(sqrt((1+eo)/(1-eo))*sin(enom/2),cos(enom/2));
	slong = satl.pnni + t*satl.rot -
		atan2(satl.ct*sin(d), cos(d));
	ssl = satl.st*sin(d);
	csl = pyth(ssl);
	if(vis(time, atan2(ssl,csl), slong, q)) {
		coc = ssl*sin(glat) + csl*cos(glat)*cos(wlong-slong);
		el = atan2(coc-q, pyth(coc));
		el /= radian;
	}
}

int
vis(double t, double slat, double slong, double q)
{
	double t0, t1, t2, d;

	d = t/86400 - .005375 + 3653;
	t0 = 6.238030674 + .01720196977*d;
	t2 = t0 + .0167253303*sin(t0);
	do {
		t1 = (t0 - t2 + .0167259152*sin(t2)) /
			(1 - .0167259152*cos(t2));
		t2 = t2 + t1;
	} while(fabs(t1) >= 1.e-4);
	t0 = 2*atan2(1.01686816*sin(t2/2), cos(t2/2));
	t0 = 4.926234925 + 8.214985538e-7*d + t0;
	t1 = 0.91744599 * sin(t0);
	t0 = atan2(t1, cos(t0));
	if(t0 < -pi/2)
		t0 = t0 + pipi;
	d = 4.88097876 + 6.30038809*d - t0;
	t0 = 0.43366079 * t1;
	t1 = pyth(t0);
	t2 = t1*cos(slat)*cos(d-slong) - t0*sin(slat);
	if(t2 > 0.46949322e-2) {
		if(0.46949322e-2*t2 + 0.999988979*pyth(t2) < q)
			return 0;
	}
	t2 = t1*cos(glat)*cos(d-wlong) - t0*sin(glat);
	if(t2 < .1)
		return 0;
	return 1;
}

void
geo(void)
{

/*
 *	uses alpha, delta, rp
 */

/*
 *	sets ra, decl, lha, decl2, az, el
 */

/*
 *	geo converts geocentric equatorial coordinates
 *	to topocentric equatorial and topocentric horizon
 *	coordinates.
 *	All are (usually) referred to the true equator.
 */

	double sel, saz, caz;
	double f;
	double sa, ca, sd;

/*
 *	convert to local hour angle and declination
 */

	lha = gst - alpha - wlong;
	decl = delta;

/*
 *	compute diurnal parallax (requires geocentric latitude)
 */

	sa = cos(decl)*sin(lha);
	ca = cos(decl)*cos(lha) - erad*cos(glat)*sin(hp);
	sd = sin(decl)           - erad*sin(glat)*sin(hp);

	lha = atan2(sa, ca);
	decl2 = atan2(sd, sqrt(sa*sa+ca*ca));
	f = sqrt(sa*sa+ca*ca+sd*sd);
	semi2 = semi/f;
	ra = gst - lha - wlong;
	ra = pinorm(ra);

/*
 *	convert to horizon coordinates
 */

	sel = sin(nlat)*sin(decl2) + cos(nlat)*cos(decl2)*cos(lha);
	el = atan2(sel, pyth(sel));
	saz = sin(lha)*cos(decl2);
	caz = cos(nlat)*sin(decl2) - sin(nlat)*cos(decl2)*cos(lha);
	az = pi + atan2(saz, -caz);

	az /= radian;
	el /= radian;
}

void
helio(void)
{
/*
 *	uses lambda, beta, rad, motion
 *	sets alpha, delta, rp
 */

/*
 *	helio converts from ecliptic heliocentric coordinates
 *	referred to the mean equinox of date
 *	to equatorial geocentric coordinates referred to
 *	the true equator and equinox
 */

	double xmp, ymp, zmp;
	double beta2;

/*
 *	compute geocentric distance of object and
 *	compute light-time correction (i.i. planetary aberration)
 */

	xmp = rad*cos(beta)*cos(lambda);
	ymp = rad*cos(beta)*sin(lambda);
	zmp = rad*sin(beta);
	rp = sqrt((xmp+xms)*(xmp+xms) +
		(ymp+yms)*(ymp+yms) +
		(zmp+zms)*(zmp+zms));
	lmb2 = lambda - .0057756e0*rp*motion;

	xmp = rad*cos(beta)*cos(lmb2);
	ymp = rad*cos(beta)*sin(lmb2);
	zmp = rad*sin(beta);

/*
 *	compute annual parallax from the position of the sun
 */

	xmp += xms;
	ymp += yms;
	zmp += zms;
	rp = sqrt(xmp*xmp + ymp*ymp + zmp*zmp);

/*
 *	compute annual (i.e. stellar) aberration
 *	from the orbital velocity of the earth
 *	(by an incorrect method)
 */

	xmp -= xdot*rp;
	ymp -= ydot*rp;
	zmp -= zdot*rp;

/*
 *	perform the nutation and so convert from the mean
 *	equator and equinox to the true
 */

	lmb2 = atan2(ymp, xmp);
	beta2 = atan2(zmp, sqrt(xmp*xmp+ymp*ymp));
	lmb2 += phi;

/*
 *	change to equatorial coordinates
 */

	xmp = rp*cos(lmb2)*cos(beta2);
	ymp = rp*(sin(lmb2)*cos(beta2)*cos(tobliq) - sin(tobliq)*sin(beta2));
	zmp = rp*(sin(lmb2)*cos(beta2)*sin(tobliq) + cos(tobliq)*sin(beta2));

	alpha = atan2(ymp, xmp);
	delta = atan2(zmp, sqrt(xmp*xmp+ymp*ymp));

	hp = 8.794e0*radsec/rp;
	semi /= rp;
	if(rad > 0 && rad < 2.e5)
		mag += 2.17*log(rad*rp);
}

void
output(char *s, Obj1 *p)
{

	if(s == 0)
		print(" SAO %5ld", sao);
	else
		print("%10s", s);
	print(" %R %D %9.4f %9.4f %9.4f",
		p->ra, p->decl2, p->az, p->el, p->semi2);
	if(s == osun.name || s == omoon.name)
		print(" %7.4f", p->mag);
	print("\n");
}

int
Rconv(Fmt *f)
{
	double v;
	int h, m, c;

	v = va_arg(f->args, double);
	v = fmod(v*12/pi, 24);		/* now hours */
	h = floor(v);
	v = fmod((v-h)*60, 60);		/* now leftover minutes */
	m = floor(v);
	v = fmod((v-m)*60, 60);		/* now leftover seconds */
	c = floor(v);
	return fmtprint(f, "%2dh%.2dm%.2ds", h, m, c);
}

int
Dconv(Fmt *f1)
{
	double v;
	int h, m, c, f;

	v = va_arg(f1->args, double);
	v = fmod(v/radian, 360);	/* now degrees */
	f = 0;
	if(v > 180) {
		v = 360 - v;
		f = 1;
	}
	h = floor(v);
	v = fmod((v-h)*60, 60);		/* now leftover minutes */
	m = floor(v);
	v = fmod((v-m)*60, 60);		/* now leftover seconds */
	c = floor(v);
	return fmtprint(f1, "%c%.2d°%.2d'%.2d\"", "+-"[f], h, m, c);
}

double k1, k2, k3, k4;
double mnom, msun, noded, dmoon;

void
moon(void)
{
	Moontab *mp;
	double dlong, lsun, psun;
	double eccm, eccs, chp, cpe;
	double v0, t0, m0, j0;
	double arg1, arg2, arg3, arg4, arg5, arg6, arg7;
	double arg8, arg9, arg10;
	double dgamma, k5, k6;
	double lterms, sterms, cterms, nterms, pterms, spterms;
	double gamma1, gamma2, gamma3, arglat;
	double xmp, ymp, zmp;
	double obl2;

/*
 *	the fundamental elements - all referred to the epoch of
 *	Jan 0.5, 1900 and to the mean equinox of date.
 */

	dlong = 270.434164 + 13.1763965268*eday - .001133*capt2
		 + 2.e-6*capt3;
	argp = 334.329556 + .1114040803*eday - .010325*capt2
		 - 12.e-6*capt3;
	node = 259.183275 - .0529539222*eday + .002078*capt2
		 + 2.e-6*capt3;
	lsun = 279.696678 + .9856473354*eday + .000303*capt2;
	psun = 281.220833 + .0000470684*eday + .000453*capt2
		 + 3.e-6*capt3;

	dlong = fmod(dlong, 360.);
	argp = fmod(argp, 360.);
	node = fmod(node, 360.);
	lsun = fmod(lsun, 360.);
	psun = fmod(psun, 360.);

	eccm = 22639.550;
	eccs = .01675104 - .00004180*capt;
	incl = 18461.400;
	cpe = 124.986;
	chp = 3422.451;

/*
 *	some subsidiary elements - they are all longitudes
 *	and they are referred to the epoch 1/0.5 1900 and
 *	to the fixed mean equinox of 1850.0.
 */

	v0 = 342.069128 + 1.6021304820*eday;
	t0 =  98.998753 + 0.9856091138*eday;
	m0 = 293.049675 + 0.5240329445*eday;
	j0 = 237.352319 + 0.0830912295*eday;

/*
 *	the following are periodic corrections to the
 *	fundamental elements and constants.
 *	arg3 is the "Great Venus Inequality".
 */

	arg1 = 41.1 + 20.2*(capt+.5);
	arg2 = dlong - argp + 33. + 3.*t0 - 10.*v0 - 2.6*(capt+.5);
	arg3 = dlong - argp + 151.1 + 16.*t0 - 18.*v0 - (capt+.5);
	arg4 = node;
	arg5 = node + 276.2 - 2.3*(capt+.5);
	arg6 = 313.9 + 13.*t0 - 8.*v0;
	arg7 = dlong - argp + 112.0 + 29.*t0 - 26.*v0;
	arg8 = dlong + argp - 2.*lsun + 273. + 21.*t0 - 20.*v0;
	arg9 = node + 290.1 - 0.9*(capt+.5);
	arg10 = 115. + 38.5*(capt+.5);
	arg1 *= radian;
	arg2 *= radian;
	arg3 *= radian;
	arg4 *= radian;
	arg5 *= radian;
	arg6 *= radian;
	arg7 *= radian;
	arg8 *= radian;
	arg9 *= radian;
	arg10 *= radian;

	dlong +=
		   (0.84 *sin(arg1)
		 +  0.31 *sin(arg2)
		 + 14.27 *sin(arg3)
		 +  7.261*sin(arg4)
		 +  0.282*sin(arg5)
		 +  0.237*sin(arg6)
		 +  0.108*sin(arg7)
		 +  0.126*sin(arg8))/3600.;

	argp +=
		 (- 2.10 *sin(arg1)
		 -  0.118*sin(arg3)
		 -  2.076*sin(arg4)
		 -  0.840*sin(arg5)
		 -  0.593*sin(arg6))/3600.;

	node +=
		   (0.63*sin(arg1)
		 +  0.17*sin(arg3)
		 + 95.96*sin(arg4)
		 + 15.58*sin(arg5)
		 +  1.86*sin(arg9))/3600.;

	t0 +=
		 (- 6.40*sin(arg1)
		 -  1.89*sin(arg6))/3600.;

	psun +=
		   (6.40*sin(arg1)
		 +  1.89*sin(arg6))/3600.;

	dgamma = -  4.318*cos(arg4)
		 -  0.698*cos(arg5)
		 -  0.083*cos(arg9);

	j0 +=
		   0.33*sin(arg10);

/*
 *	the following factors account for the fact that the
 *	eccentricity, solar eccentricity, inclination and
 *	parallax used by Brown to make up his coefficients
 *	are both wrong and out of date.  Brown did the same
 *	thing in a different way.
 */

	k1 = eccm/22639.500;
	k2 = eccs/.01675104;
	k3 = 1. + 2.708e-6 + .000108008*dgamma;
	k4 = cpe/125.154;
	k5 = chp/3422.700;

/*
 *	the principal arguments that are used to compute
 *	perturbations are the following differences of the
 *	fundamental elements.
 */

	mnom = dlong - argp;
	msun = lsun - psun;
	noded = dlong - node;
	dmoon = dlong - lsun;

/*
 *	solar terms in longitude
 */

	lterms = 0.0;
	mp = moontab;
	for(;;) {
		if(mp->f == 0.0)
			break;
		lterms += sinx(mp->f,
			mp->c[0], mp->c[1],
			mp->c[2], mp->c[3], 0.0);
		mp++;
	}
	mp++;

/*
 *	planetary terms in longitude
 */

	lterms += sinx(0.822, 0,0,0,0, t0-v0);
	lterms += sinx(0.307, 0,0,0,0, 2.*t0-2.*v0+179.8);
	lterms += sinx(0.348, 0,0,0,0, 3.*t0-2.*v0+272.9);
	lterms += sinx(0.176, 0,0,0,0, 4.*t0-3.*v0+271.7);
	lterms += sinx(0.092, 0,0,0,0, 5.*t0-3.*v0+199.);
	lterms += sinx(0.129, 1,0,0,0, -t0+v0+180.);
	lterms += sinx(0.152, 1,0,0,0, t0-v0);
	lterms += sinx(0.127, 1,0,0,0, 3.*t0-3.*v0+180.);
	lterms += sinx(0.099, 0,0,0,2, t0-v0);
	lterms += sinx(0.136, 0,0,0,2, 2.*t0-2.*v0+179.5);
	lterms += sinx(0.083, -1,0,0,2, -4.*t0+4.*v0+180.);
	lterms += sinx(0.662, -1,0,0,2, -3.*t0+3.*v0+180.0);
	lterms += sinx(0.137, -1,0,0,2, -2.*t0+2.*v0);
	lterms += sinx(0.133, -1,0,0,2, t0-v0);
	lterms += sinx(0.157, -1,0,0,2, 2.*t0-2.*v0+179.6);
	lterms += sinx(0.079, -1,0,0,2, -8.*t0+6.*v0+162.6);
	lterms += sinx(0.073, 2,0,0,-2, 3.*t0-3.*v0+180.);
	lterms += sinx(0.643, 0,0,0,0, -t0+j0+178.8);
	lterms += sinx(0.187, 0,0,0,0, -2.*t0+2.*j0+359.6);
	lterms += sinx(0.087, 0,0,0,0, j0+289.9);
	lterms += sinx(0.165, 0,0,0,0, -t0+2.*j0+241.5);
	lterms += sinx(0.144, 1,0,0,0, t0-j0+1.0);
	lterms += sinx(0.158, 1,0,0,0, -t0+j0+179.0);
	lterms += sinx(0.190, 1,0,0,0, -2.*t0+2.*j0+180.0);
	lterms += sinx(0.096, 1,0,0,0, -2.*t0+3.*j0+352.5);
	lterms += sinx(0.070, 0,0,0,2, 2.*t0-2.*j0+180.);
	lterms += sinx(0.167, 0,0,0,2, -t0+j0+178.5);
	lterms += sinx(0.085, 0,0,0,2, -2.*t0+2.*j0+359.2);
	lterms += sinx(1.137, -1,0,0,2, 2.*t0-2.*j0+180.3);
	lterms += sinx(0.211, -1,0,0,2, -t0+j0+178.4);
	lterms += sinx(0.089, -1,0,0,2, -2.*t0+2.*j0+359.2);
	lterms += sinx(0.436, -1,0,0,2, 2.*t0-3.*j0+7.5);
	lterms += sinx(0.240, 2,0,0,-2, -2.*t0+2.*j0+179.9);
	lterms += sinx(0.284, 2,0,0,-2, -2.*t0+3.*j0+172.5);
	lterms += sinx(0.195, 0,0,0,0, -2.*t0+2.*m0+180.2);
	lterms += sinx(0.327, 0,0,0,0, -t0+2.*m0+224.4);
	lterms += sinx(0.093, 0,0,0,0, -2.*t0+4.*m0+244.8);
	lterms += sinx(0.073, 1,0,0,0, -t0+2.*m0+223.3);
	lterms += sinx(0.074, 1,0,0,0, t0-2.*m0+306.3);
	lterms += sinx(0.189, 0,0,0,0, node+180.);

/*
 *	solar terms in latitude
 */

	sterms = 0;
	for(;;) {
		if(mp->f == 0)
			break;
		sterms += sinx(mp->f,
			mp->c[0], mp->c[1],
			mp->c[2], mp->c[3], 0);
		mp++;
	}
	mp++;

	cterms = 0;
	for(;;) {
		if(mp->f == 0)
			break;
		cterms += cosx(mp->f,
			mp->c[0], mp->c[1],
			mp->c[2], mp->c[3], 0);
		mp++;
	}
	mp++;

	nterms = 0;
	for(;;) {
		if(mp->f == 0)
			break;
		nterms += sinx(mp->f,
			mp->c[0], mp->c[1],
			mp->c[2], mp->c[3], 0);
		mp++;
	}
	mp++;

/*
 *	planetary terms in latitude
 */

	pterms =
		   sinx(0.215, 0,0,0,0, dlong);

/*
 *	solar terms in parallax
 */

	spterms = 3422.700;
	for(;;) {
		if(mp->f == 0)
			break;
		spterms += cosx(mp->f,
			mp->c[0], mp->c[1],
			mp->c[2], mp->c[3], 0);
		mp++;
	}

/*
 *	planetary terms in parallax
 */

	//spterms = spterms;

/*
 *	computation of longitude
 */

	lambda = (dlong + lterms/3600.)*radian;

/*
 *	computation of latitude
 */

	arglat = (noded + sterms/3600.)*radian;
	gamma1 = 18519.700 * k3;
	gamma2 = -6.241 * k3*k3*k3;
	gamma3 = 0.004 * k3*k3*k3*k3*k3;

	k6 = (gamma1 + cterms) / gamma1;

	beta = k6 * (gamma1*sin(arglat) + gamma2*sin(3.*arglat)
		 + gamma3*sin(5.*arglat) + nterms)
		 + pterms;
	if(flags['o'])
		beta -= 0.6;
	beta *= radsec;

/*
 *	computation of parallax
 */

	spterms = k5 * spterms *radsec;
	hp = spterms + (spterms*spterms*spterms)/6.;

	rad = hp/radsec;
	rp = 1.;
	semi = .0799 + .272453*(hp/radsec);
	if(dmoon < 0.)
		dmoon += 360.;
	mag = dmoon/360.;

/*
 *	change to equatorial coordinates
 */

	lambda += phi;
	obl2 = obliq + eps;
	xmp = rp*cos(lambda)*cos(beta);
	ymp = rp*(sin(lambda)*cos(beta)*cos(obl2) - sin(obl2)*sin(beta));
	zmp = rp*(sin(lambda)*cos(beta)*sin(obl2) + cos(obl2)*sin(beta));

	alpha = atan2(ymp, xmp);
	delta = atan2(zmp, sqrt(xmp*xmp+ymp*ymp));
	meday = eday;
	mhp = hp;

	geo();
}

double
sinx(double coef, int i, int j, int k, int m, double angle)
{
	double x;

	x = i*mnom + j*msun + k*noded + m*dmoon + angle;
	x = coef*sin(x*radian);
	if(i < 0)
		i = -i;
	for(; i>0; i--)
		x *= k1;
	if(j < 0)
		j = -j;
	for(; j>0; j--)
		x *= k2;
	if(k < 0)
		k = -k;
	for(; k>0; k--)
		x *= k3;
	if(m & 1)
		x *= k4;

	return x;
}

double
cosx(double coef, int i, int j, int k, int m, double angle)
{
	double x;

	x = i*mnom + j*msun + k*noded + m*dmoon + angle;
	x = coef*cos(x*radian);
	if(i < 0)
		i = -i;
	for(; i>0; i--)
		x *= k1;
	if(j < 0)
		j = -j;
	for(; j>0; j--)
		x *= k2;
	if(k < 0)
		k = -k;
	for(; k>0; k--)
		x *= k3;
	if(m & 1)
		x *= k4;

	return x;
}

void
sun(void)
{
	double mven, merth, mmars, mjup, msat;
	double dmoon, mmoon, gmoon;
	double pturbb, pturbl, pturbr, lograd;

	ecc = .01675104 - 4.180e-5 * capt - 1.26e-7*capt2;
	incl = 0;
	node = 0;
	argp = 281.220833 + .0000470684*eday + .000453*capt2
		 + .000003*capt3;
	mrad = 1;
	anom = 358.475845 + .9856002670*eday - .000150*capt2
		 - .000003*capt3;
	motion = .9856473354;

	dmoon = 350.737681+12.1907491914*eday-.001436*capt2;
	gmoon = 11.250889 + 13.2293504490*eday - .003212*capt2;
	mmoon = 296.104608 + 13.0649924465*eday + 9.192e-3*capt2;
	mven  = 212.448 + 1.602121635*eday;
	merth = 358.476 + 0.985600267*eday;
	mmars = 319.590 + .524024095*eday;
	mjup = 225.269 + .083082362*eday;
	msat  = 175.593 + .033450794*eday;

	dmoon = fmod(dmoon, 360.)*radian;
	gmoon = fmod(gmoon, 360.)*radian;
	mmoon = fmod(mmoon, 360.)*radian;
	mven  *= radian;
	merth *= radian;
	mmars *= radian;
	mjup *= radian;
	msat  *= radian;

	icosadd(sunfp, suncp);
	anom += cosadd(4, mmars, merth, mven, mjup)/3600.;
	anom += sinadd(5, mmars, merth, mven, mjup, .07884*capt)/3600.;

	incl *= radian;
	node *= radian;
	argp *= radian;
	anom = fmod(anom, 360.)*radian;

/*
 *	computation of elliptic orbit
 */

	lambda = anom + argp;

	pturbl = (6910.057 - 17.240*capt - 0.052*capt2)*sin(anom)
		 + (72.338 - 0.361*capt) * sin(2.*anom)
		 + (1.054 - 0.001*capt) * sin(3.*anom)
		 + 0.018 * sin(4.*anom);

	lambda += pturbl*radsec;

	beta = 0.;

	lograd = (30.57e-6 - 0.15e-6*capt)
		 - (7274.12e-6 - 18.14e-6*capt - 0.05e-6*capt2)*cos(anom)
		 - (91.38e-6 - 0.46e-6*capt) * cos(2.*anom)
		 - (1.45e-6 - 0.01e-6*capt) * cos(3.*anom)
		 - 0.02e-6 * cos(4.*anom);

	pturbl = cosadd(5, mmars, merth, mven, mjup, msat);
	pturbl += sinadd(3, dmoon, mmoon, merth) + .9;
	pturbl *= radsec;

	pturbb =  cosadd(3, merth, mven, mjup);
	pturbb += sinadd(3, gmoon, mmoon, dmoon);
	pturbb *= radsec;

	pturbr =  cosadd(5, mmars, merth, mven, mjup, msat);
	pturbr += cosadd(3, dmoon, mmoon, merth);

	lambda += pturbl;
	if(lambda > pipi)
		lambda -= pipi;

	beta += pturbb;

	lograd = (lograd+pturbr) * 2.30258509;
	rad = 1 + lograd * (1 + lograd * (.5 + lograd/6));

	motion *= radian*mrad*mrad/(rad*rad);

	semi = 961.182;
	if(flags['o'])
		semi = 959.63;
	mag = -26.5;
}

double	sunfp[]	=
{
	-.265, 0,
	3.760, 0,
	 .200, 0,
	0,

	-.021, 0,
	5.180, 0,
	1.882, 3.8991,
	-.030, 0,
	0,

	0.075, 5.1766,
	4.838, 5.2203,
	0.074, 3.6285,
	0.116, 2.5988,
	5.526, 2.5885,
	2.497, 5.5143,
	0.044, 5.4350,
	0.666, 3.1016,
	1.559, 6.0258,
	1.024, 5.5527,
	0.210, 3.5989,
	0.144, 3.4104,
	0.152, 6.0004,
	0.084, 4.1120,
	0.037, 3.8711,
	0.123, 3.4086,
	0.154, 6.2762,
	0.038, 4.6094,
	0.020, 5.1313,
	0.042, 4.5239,
	0.032, 0.8517,
	0.273, 3.7996,
	0.048, 4.5431,
	0.041, 6.0388,
	2.043, 6.0020,
	1.770, 3.4977,
	0.028, 2.5831,
	0.129, 5.1348,
	0.425, 5.9146,
	0.034, 1.2391,
	0.500, 1.8357,
	0.585, 5.8304,
	0.085, 0.9529,
	0.204, 1.7593,
	0.020, 3.2463,
	0.154, 3.9689,
	0.101, 1.6808,
	0.049, 3.0805,
	0.106, 3.8868,
	0.052, 6.0895,
	0.021, 3.7559,
	0.028, 5.2011,
	0.062, 6.0388,
	0.044, 1.8483,
	0.045, 3.9759,
	0.021, 5.3931,
	0.026, 1.9722,
	0.163, 3.4662,
	7.208, 3.1334,
	2.600, 4.5940,
	0.073, 4.8223,
	0.069, 1.4102,
	2.731, 1.5210,
	1.610, 1.9110,
	0.073, 4.4087,
	0.164, 2.9758,
	0.556, 1.4425,
	0.210, 1.7261,
	0.044, 2.9356,
	0.080, 1.3561,
	0.419, 1.7555,
	0.320, 4.7030,
	0.108, 5.0719,
	0.112, 5.1243,
	0.021, 5.0440,
	0,

	6.454, 0,
	0.177, 0,
	-.424, 0,
	0.039, 0,
	-.064, 0,
	0.172, 0,
	0,

	-.092, 1.6354,
	-.067, 2.1468,
	-.210, 2.6494,
	-.166, 4.6338,
	0,

	0.576, 0,
	-.047, 0,
	0.021, 0,
	0,

	2.359e-6, 3.6607,
	6.842e-6, 1.0180,
	0.869e-6, 3.9567,
	1.045e-6, 1.5332,
	1.497e-6, 4.4691,
	0.376e-6, 2.0295,
	2.057e-6, 4.0941,
	0.215e-6, 4.3459,
	0.478e-6, 0.2648,
	0.208e-6, 1.9548,
	7.067e-6, 1.5630,
	0.244e-6, 5.9097,
	4.026e-6, 6.2526,
	1.459e-6, 0.3409,
	0.281e-6, 1.4172,
	0.803e-6, 6.1533,
	0.429e-6, 0.1850,
	0,

	13.36e-6, 0,
	-1.33e-6, 0,
	 0.37e-6, 0,
	 0.36e-6, 0,
	0
};
char	suncp[]	=
{
	4, -7, 3, 0,
	-8, 4, 0, 3,
	15, -8, 0, 0,

	4, -7, 3, 0, 0,
	-8, 4, 0, 3, 0,
	0, 13, -8, 0, 1,
	15, -8, 0, 0, 0,

	0,0,1,0,0,
	0,-1,1,0,0,
	0,-2,1,0,0,
	0,-1,2,0,0,
	0,-2,2,0,0,
	0,-3,2,0,0,
	0,-4,2,0,0,
	0,-3,3,0,0,
	0,-4,3,0,0,
	0,-5,3,0,0,
	0,-4,4,0,0,
	0,-5,4,0,0,
	0,-6,4,0,0,
	0,-5,5,0,0,
	0,-6,5,0,0,
	0,-7,5,0,0,
	0,-8,5,0,0,
	0,-6,6,0,0,
	0,-7,7,0,0,
	0,-12,8,0,0,
	0,-14,8,0,0,
	-1,1,0,0,0,
	-1,0,0,0,0,
	-2,3,0,0,0,
	-2,2,0,0,0,
	-2,1,0,0,0,
	-2,0,0,0,0,
	-3,3,0,0,0,
	-3,2,0,0,0,
	-4,4,0,0,0,
	-4,3,0,0,0,
	-4,2,0,0,0,
	-5,4,0,0,0,
	-5,3,0,0,0,
	-6,5,0,0,0,
	-6,4,0,0,0,
	-6,3,0,0,0,
	-7,5,0,0,0,
	-7,4,0,0,0,
	-8,5,0,0,0,
	-8,4,0,0,0,
	-9,6,0,0,0,
	-9,5,0,0,0,
	-11,6,0,0,0,
	-13,7,0,0,0,
	-15,9,0,0,0,
	-17,9,0,0,0,
	0,2,0,-1,0,
	0,1,0,-1,0,
	0,0,0,-1,0,
	0,-1,0,-1,0,
	0,3,0,-2,0,
	0,2,0,-2,0,
	0,1,0,-2,0,
	0,0,0,-2,0,
	0,3,0,-3,0,
	0,2,0,-3,0,
	0,1,0,-3,0,
	0,3,0,-4,0,
	0,2,0,-4,0,
	0,1,0,0,-1,
	0,0,0,0,-1,
	0,2,0,0,-2,
	0,1,0,0,-2,
	0,2,0,0,-3,

	1,0,0,
	1,1,0,
	1,-1,0,
	3,-1,0,
	1,0,1,
	1,0,-1,

	-2,1,0,
	-3,2,0,
	-4,2,0,
	1,0,-2,

	1,0,0,
	1,-1,0,
	-1,0,2,

	0,-1,1,0,0,
	0,-2,2,0,0,
	0,-3,2,0,0,
	0,-3,3,0,0,
	0,-4,3,0,0,
	0,-4,4,0,0,
	-2,2,0,0,0,
	-3,2,0,0,0,
	-4,3,0,0,0,
	0,2,0,-1,0,
	0,1,0,-1,0,
	0,0,0,-1,0,
	0,2,0,-2,0,
	0,1,0,-2,0,
	0,3,0,-3,0,
	0,2,0,-3,0,
	0,1,0,0,-1,

	1,0,0,
	1,-1,0,
	1,1,0,
	1,0,-1
};

void
nutate(void)
{

/*
 *	uses radian, radsec
 *	sets phi, eps, dphi, deps, obliq, gst, tobliq
 */

	double msun, mnom, noded, dmoon;

/*
 *	nutation of the equinoxes is a wobble of the pole
 *	of the earths rotation whose magnitude is about
 *	9 seconds of arc and whose period is about 18.6 years.
 *
 *	it depends upon the pull of the sun and moon on the
 *	equatorial bulge of the earth.
 *
 *	phi and eps are the two angles which specify the
 *	true pole with respect to the mean pole.
 *
 *	all coeffieients are from Exp. Supp. pp.44-45
 */

	mnom = 296.104608 + 13.0649924465*eday + 9.192e-3*capt2
		 + 14.38e-6*capt3;
	mnom *= radian;
	msun = 358.475833 + .9856002669*eday - .150e-3*capt2
		 - 3.33e-6*capt3;
	msun *= radian;
	noded = 11.250889 + 13.2293504490*eday - 3.211e-3*capt2
		 - 0.33e-6*capt3;
	noded *= radian;
	dmoon = 350.737486 + 12.1907491914*eday - 1.436e-3*capt2
		 + 1.89e-6*capt3;
	dmoon *= radian;
	node = 259.183275 - .0529539222*eday + 2.078e-3*capt2
		 + 2.22e-6*capt3;
	node *= radian;

/*
 *	long period terms
 */

	phi = 0.;
	eps = 0.;
	dphi = 0.;
	deps = 0.;


	icosadd(nutfp, nutcp);
	phi = -(17.2327+.01737*capt)*sin(node);
	phi += sinadd(4, node, noded, dmoon, msun);

	eps = cosadd(4, node, noded, dmoon, msun);

/*
 *	short period terms
 */


	dphi = sinadd(4, node, noded, mnom, dmoon);

	deps = cosadd(3, node, noded, mnom);

	phi = (phi+dphi)*radsec;
	eps = (eps+deps)*radsec;
	dphi *= radsec;
	deps *= radsec;

	obliq = 23.452294 - .0130125*capt - 1.64e-6*capt2
		 + 0.503e-6*capt3;
	obliq *= radian;
	tobliq = obliq + eps;

	gst = 99.690983 + 360.9856473354*eday + .000387*capt2;
	gst -= 180.;
	gst = fmod(gst, 360.);
	if(gst < 0.)
		gst += 360.;
	gst *= radian;
	gst += phi*cos(obliq);
}

Moontab	moontab[] =
{
	    0.127,	0,0,0,6,
	   13.902,	0,0,0,4,
	 2369.912,	0,0,0,2,
	    1.979,	1,0,0,4,
	  191.953,	1,0,0,2,
	22639.500,	1,0,0,0,
	-4586.465,	1,0,0,-2,
	  -38.428,	1,0,0,-4,
	    -.393,	1,0,0,-6,
	    -.289,	0,1,0,4,
	  -24.420,	0,1,0,2,
	 -668.146,	0,1,0,0,
	 -165.145,	0,1,0,-2,
	   -1.877,	0,1,0,-4,
	    0.403,	0,0,0,3,
	 -125.154,	0,0,0,1,
	    0.213,	2,0,0,4,
	   14.387,	2,0,0,2,
	  769.016,	2,0,0,0,
	 -211.656,	2,0,0,-2,
	  -30.773,	2,0,0,-4,
	    -.570,	2,0,0,-6,
	   -2.921,	1,1,0,2,
	 -109.673,	1,1,0,0,
	 -205.962,	1,1,0,-2,
	   -4.391,	1,1,0,-4,
	    -.072,	1,1,0,-6,
	    0.283,	1,-1,0,4,
	   14.577,	1,-1,0,2,
	  147.687,	1,-1,0,0,
	   28.475,	1,-1,0,-2,
	    0.636,	1,-1,0,-4,
	    -.189,	0,2,0,2,
	   -7.486,	0,2,0,0,
	   -8.096,	0,2,0,-2,
	    -.151,	0,2,0,-4,
	    -.085,	0,0,2,4,
	   -5.741,	0,0,2,2,
	 -411.608,	0,0,2,0,
	  -55.173,	0,0,2,-2,
	   -8.466,	1,0,0,1,
	   18.609,	1,0,0,-1,
	    3.215,	1,0,0,-3,
	    0.150,	0,1,0,3,
	   18.023,	0,1,0,1,
	    0.560,	0,1,0,-1,
	    1.060,	3,0,0,2,
	   36.124,	3,0,0,0,
	  -13.193,	3,0,0,-2,
	   -1.187,	3,0,0,-4,
	    -.293,	3,0,0,-6,
	    -.290,	2,1,0,2,
	   -7.649,	2,1,0,0,
	   -8.627,	2,1,0,-2,
	   -2.740,	2,1,0,-4,
	    -.091,	2,1,0,-6,
	    1.181,	2,-1,0,2,
	    9.703,	2,-1,0,0,
	   -2.494,	2,-1,0,-2,
	    0.360,	2,-1,0,-4,
	   -1.167,	1,2,0,0,
	   -7.412,	1,2,0,-2,
	    -.311,	1,2,0,-4,
	    0.757,	1,-2,0,2,
	    2.580,	1,-2,0,0,
	    2.533,	1,-2,0,-2,
	    -.103,	0,3,0,0,
	    -.344,	0,3,0,-2,
	    -.992,	1,0,2,2,
	  -45.099,	1,0,2,0,
	    -.179,	1,0,2,-2,
	    -.301,	1,0,2,-4,
	   -6.382,	1,0,-2,2,
	   39.528,	1,0,-2,0,
	    9.366,	1,0,-2,-2,
	    0.202,	1,0,-2,-4,
	    0.415,	0,1,2,0,
	   -2.152,	0,1,2,-2,
	   -1.440,	0,1,-2,2,
	    0.076,	0,1,-2,0,
	    0.384,	0,1,-2,-2,
	    -.586,	2,0,0,1,
	    1.750,	2,0,0,-1,
	    1.225,	2,0,0,-3,
	    1.267,	1,1,0,1,
	    0.137,	1,1,0,-1,
	    0.233,	1,1,0,-3,
	    -.122,	1,-1,0,1,
	   -1.089,	1,-1,0,-1,
	    -.276,	1,-1,0,-3,
	    0.255,	0,0,2,1,
	    0.584,	0,0,2,-1,
	    0.254,	0,0,2,-3,
	    0.070,	4,0,0,2,
	    1.938,	4,0,0,0,
	    -.952,	4,0,0,-2,
	    -.551,	3,1,0,0,
	    -.482,	3,1,0,-2,
	    -.100,	3,1,0,-4,
	    0.088,	3,-1,0,2,
	    0.681,	3,-1,0,0,
	    -.183,	3,-1,0,-2,
	    -.297,	2,2,0,-2,
	    -.161,	2,2,0,-4,
	    0.197,	2,-2,0,0,
	    0.254,	2,-2,0,-2,
	    -.250,	1,3,0,-2,
	    -.123,	2,0,2,2,
	   -3.996,	2,0,2,0,
	    0.557,	2,0,2,-2,
	    -.459,	2,0,-2,2,
	   -1.370,	2,0,-2,0,
	    0.538,	2,0,-2,-2,
	    0.173,	2,0,-2,-4,
	    0.263,	1,1,2,0,
	    0.083,	1,1,-2,2,
	    -.083,	1,1,-2,0,
	    0.426,	1,1,-2,-2,
	    -.304,	1,-1,2,0,
	    -.372,	1,-1,-2,2,
	    0.083,	1,-1,-2,0,
	    0.418,	0,0,4,0,
	    0.074,	0,0,4,-2,
	    0.130,	3,0,0,-1,
	    0.092,	2,1,0,1,
	    0.084,	2,1,0,-3,
	    -.352,	2,-1,0,-1,
	    0.113,	5,0,0,0,
	    -.330,	3,0,2,0,
	    0.090,	1,0,4,0,
	    -.080,	1,0,-4,0,
	        0,	0,0,0,0,

	 -112.79,	0,0,0,1,
	 2373.36,	0,0,0,2,
	   -4.01,	0,0,0,3,
	   14.06,	0,0,0,4,
	    6.98,	1,0,0,4,
	  192.72,	1,0,0,2,
	  -13.51,	1,0,0,1,
	22609.07,	1,0,0,0,
	    3.59,	1,0,0,-1,
	-4578.13,	1,0,0,-2,
	    5.44,	1,0,0,-3,
	  -38.64,	1,0,0,-4,
	   14.78,	2,0,0,2,
	  767.96,	2,0,0,0,
	    2.01,	2,0,0,-1,
	 -152.53,	2,0,0,-2,
	  -34.07,	2,0,0,-4,
	    2.96,	3,0,0,2,
	   50.64,	3,0,0,0,
	  -16.40,	3,0,0,-2,
	    3.60,	4,0,0,0,
	   -1.58,	4,0,0,-2,
	   -1.59,	0,1,0,4,
	  -25.10,	0,1,0,2,
	   17.93,	0,1,0,1,
	 -126.98,	0,1,0,0,
	 -165.06,	0,1,0,-2,
	   -6.46,	0,1,0,-4,
	   -1.68,	0,2,0,2,
	  -16.35,	0,2,0,-2,
	  -11.75,	1,1,0,2,
	    1.52,	1,1,0,1,
	 -115.18,	1,1,0,0,
	 -182.36,	1,1,0,-2,
	   -9.66,	1,1,0,-4,
	   -2.27,	-1,1,0,4,
	  -23.59,	-1,1,0,2,
	 -138.76,	-1,1,0,0,
	  -31.70,	-1,1,0,-2,
	   -1.53,	-1,1,0,-4,
	  -10.56,	2,1,0,0,
	   -7.59,	2,1,0,-2,
	   -2.54,	2,1,0,-4,
	    3.32,	2,-1,0,2,
	   11.67,	2,-1,0,0,
	   -6.12,	1,2,0,-2,
	   -2.40,	-1,2,0,2,
	   -2.32,	-1,2,0,0,
	   -1.82,	-1,2,0,-2,
	  -52.14,	0,0,2,-2,
	   -1.67,	0,0,2,-4,
	   -9.52,	1,0,2,-2,
	  -85.13,	-1,0,2,0,
	    3.37,	-1,0,2,-2,
	   -2.26,	0,1,2,-2,
	       0,	0,0,0,0,

	   -0.725,	0,0,0,1,
	    0.601,	0,0,0,2,
	    0.394,	0,0,0,3,
	    -.445,	1,0,0,4,
	    0.455,	1,0,0,1,
	    0.192,	1,0,0,-3,
	    5.679,	2,0,0,-2,
	    -.308,	2,0,0,-4,
	    -.166,	3,0,0,2,
	   -1.300,	3,0,0,0,
	    0.258,	3,0,0,-2,
	   -1.302,	0,1,0,0,
	    -.416,	0,1,0,-4,
	    -.740,	0,2,0,-2,
	    0.787,	1,1,0,2,
	    0.461,	1,1,0,0,
	    2.056,	1,1,0,-2,
	    -.471,	1,1,0,-4,
	    -.443,	-1,1,0,2,
	    0.679,	-1,1,0,0,
	   -1.540,	-1,1,0,-2,
	    0.259,	2,1,0,0,
	    -.212,	2,-1,0,2,
	    -.151,	2,-1,0,0,
	        0,	0,0,0,0,

	 -526.069,	0,0,1,-2,
	   -3.352,	0,0,1,-4,
	   44.297,	1,0,1,-2,
	   -6.000,	1,0,1,-4,
	   20.599,	-1,0,1,0,
	  -30.598,	-1,0,1,-2,
	  -24.649,	-2,0,1,0,
	   -2.000,	-2,0,1,-2,
	  -22.571,	0,1,1,-2,
	   10.985,	0,-1,1,-2,
	        0,	0,0,0,0,

	    0.2607,	0,0,0,4,
	   28.2333,	0,0,0,2,
	    0.0433,	1,0,0,4,
	    3.0861,	1,0,0,2,
	  186.5398,	1,0,0,0,
	   34.3117,	1,0,0,-2,
	    0.6008,	1,0,0,-4,
	    -.3000,	0,1,0,2,
	    -.3997,	0,1,0,0,
	    1.9178,	0,1,0,-2,
	    0.0339,	0,1,0,-4,
	   -0.9781,	0,0,0,1,
	    0.2833,	2,0,0,2,
	   10.1657,	2,0,0,0,
	    -.3039,	2,0,0,-2,
	    0.3722,	2,0,0,-4,
	    0.0109,	2,0,0,-6,
	    -.0484,	1,1,0,2,
	    -.9490,	1,1,0,0,
	    1.4437,	1,1,0,-2,
	    0.0673,	1,1,0,-4,
	    0.2302,	1,-1,0,2,
	    1.1528,	1,-1,0,0,
	    -.2257,	1,-1,0,-2,
	    -.0102,	1,-1,0,-4,
	    0.0918,	0,2,0,-2,
	    -.0124,	0,0,2,0,
	    -.1052,	0,0,2,-2,
	    -.1093,	1,0,0,1,
	    0.0118,	1,0,0,-1,
	    -.0386,	1,0,0,-3,
	    0.1494,	0,1,0,1,
	    0.0243,	3,0,0,2,
	    0.6215,	3,0,0,0,
	    -.1187,	3,0,0,-2,
	    -.1038,	2,1,0,0,
	    -.0192,	2,1,0,-2,
	    0.0324,	2,1,0,-4,
	    0.0213,	2,-1,0,2,
	    0.1268,	2,-1,0,0,
	    -.0106,	1,2,0,0,
	    0.0484,	1,2,0,-2,
	    0.0112,	1,-2,0,2,
	    0.0196,	1,-2,0,0,
	    -.0212,	1,-2,0,-2,
	    -.0833,	1,0,2,-2,
	    -.0481,	1,0,-2,2,
	    -.7136,	1,0,-2,0,
	    -.0112,	1,0,-2,-2,
	    -.0100,	2,0,0,1,
	    0.0155,	2,0,0,-1,
	    0.0164,	1,1,0,1,
	    0.0401,	4,0,0,0,
	    -.0130,	4,0,0,-2,
	    0.0115,	3,-1,0,0,
	    -.0141,	2,0,-2,-2,
	         0,	0,0,0,0
};

double	nutfp[] =
{
	  .2088,	0,
	-1.2730,	0,
	  .1258,	0,
	 -.0496,	0,
	  .0214,	0,
	  .0124,	0,
	      0,

	 9.2109,	0,
	 -.0904,	0,
	  .5519,	0,
	  .0215,	0,
	 -.0093,	0,
	 -.0066,	0,
	      0,

	 -.2037,	0,
	  .0675,	0,
	 -.0342,	0,
	 -.0261,	0,
	 -.0149,	0,
	  .0114,	0,
	  .0060,	0,
	  .0058,	0,
	 -.0057,	0,
	 -.0052,	0,
	      0,

	  .0884,	0,
	  .0183,	0,
	  .0113,	0,
	 -.0050,	0,
	      0
};

char	nutcp[] =
{
	2,0,0,0,
	2,2,-2,0,
	0,0,0,1,
	2,2,-2,1,
	2,2,-2,-1,
	1,2,-2,0,

	1,0,0,0,
	2,0,0,0,
	2,2,-2,0,
	2,2,-2,1,
	2,2,-2,-1,
	1,2,-2,0,

	2,2,0,0,
	0,0,1,0,
	1,2,0,0,
	2,2,1,0,
	0,0,1,-2,
	2,2,-1,0,
	0,0,0,2,
	1,0,1,0,
	1,0,-1,0,
	2,2,-1,2,

	2,2,0,
	1,2,0,
	2,2,1,
	2,2,-1
};

char*	startab;

void
stars(void)
{
	double lomoon, himoon, sd;
	int wrap, f, i;
	char *saop;
	static char saoa[100];

	sd = 1000*radsec;
	lomoon = omoon.point[0].ra - sd;
	if(lomoon < 0)
		lomoon += pipi;
	himoon = omoon.point[NPTS+1].ra + sd;
	if(himoon > pipi)
		himoon -= pipi;
	lomoon *= 12/pi;
	himoon *= 12/pi;
	wrap = 0;
	if(lomoon > himoon)
		wrap++;

	f = open(startab, OREAD);
	if(f < 0) {
		fprint(2, "%s?\n", startab);
		return;
	}
	epoch = 1950.0;
	epoch = (epoch-1900.0) * 365.24220 + 0.313;
	saop = saoa;

/*
 *	read mean places of stars at epoch of star table
 */

loop:
	if(rline(f)) {
		close(f);
		return;
	}
	rah = atof(line+17);
	ram = atof(line+20);
	ras = atof(line+23);

	alpha = rah + ram/60 + ras/3600;
	if(wrap == 0) {
		if(alpha < lomoon || alpha > himoon)
			goto loop;
	} else
		if(alpha < lomoon && alpha > himoon)
			goto loop;

	sao = atof(line+0);
	sprint(saop, "%ld", sao);
	da = atof(line+30);
	dday = atof(line+37);
	dmin = atof(line+41);
	dsec = atof(line+44);
	dd = atof(line+50);
	px = atof(line+57);
	mag = atof(line+61);

/*
 *	convert rt ascension and declination to internal format
 */

	delta = fabs(dday) + dmin/60 + dsec/3600;
	if(dday < 0)
		delta = -delta;

	star();
/*
 *	if(fabs(beta) > 6.55*radian)
 *		goto loop;
 */
	sd = .0896833e0*cos(beta)*sin(lambda-1.3820+.00092422117*eday)
		 + 0.99597*sin(beta);
	if(fabs(sd) > .0183)
		goto loop;

	for(i=0; i<=NPTS+1; i++)
		setobj(&ostar.point[i]);

	occult(&omoon, &ostar, 0);
	if(occ.t1 >= 0 || occ.t5 >= 0) {
		i = PTIME;
		if(mag > 2)
			i |= DARK;
		if(mag < 5)
			i |= SIGNIF;
		if(occ.t1 >= 0 && occ.e1 >= 0)
			event("Occultation of SAO %s begins at ",
				saop, "", occ.t1, i);
		if(occ.t5 >= 0 && occ.e5 >= 0)
			event("Occultation of SAO %s ends at ",
				saop, "", occ.t5, i);
		while(*saop++)
			;
	}
	goto loop;
}

void
star(void)
{
	double xm, ym, zm, dxm, dym, dzm;
	double xx, yx, zx, yy, zy, zz, tau;
	double capt0, capt1, capt12, capt13, sl, sb, cl;

/*
 *	remove E-terms of aberration
 *	except when finding catalog mean places
 */

	alpha += (.341/(3600.*15.))*sin((alpha+11.26)*15.*radian)
		  /cos(delta*radian);
	delta += (.341/3600.)*cos((alpha+11.26)*15.*radian)
		  *sin(delta*radian) - (.029/3600.)*cos(delta*radian);

/*
 *	correct for proper motion
 */

	tau = (eday - epoch)/365.24220;
	alpha += tau*da/3600.;
	delta += tau*dd/3600.;
	alpha *= 15.*radian;
	delta *= radian;

/*
 *	convert to rectangular coordinates merely for convenience
 */

	xm = cos(delta)*cos(alpha);
	ym = cos(delta)*sin(alpha);
	zm = sin(delta);

/*
 *	convert mean places at epoch of startable to current
 *	epoch (i.e. compute relevant precession)
 */

	capt0 = (epoch - 18262.427)/36524.220e0;
	capt1 = (eday - epoch)/36524.220;
	capt12 = capt1*capt1;
	capt13 = capt12*capt1;

	xx = - (.00029696+26.e-8*capt0)*capt12
		  - 13.e-8*capt13;
	yx =  -(.02234941+1355.e-8*capt0)*capt1
		  - 676.e-8*capt12 + 221.e-8*capt13;
	zx = -(.00971690-414.e-8*capt0)*capt1
		  + 207.e-8*capt12 + 96.e-8*capt13;
	yy = - (.00024975+30.e-8*capt0)*capt12
		  - 15.e-8*capt13;
	zy = -(.00010858+2.e-8*capt0)*capt12;
	zz = - (.00004721-4.e-8*capt0)*capt12;

	dxm =  xx*xm + yx*ym + zx*zm;
	dym = - yx*xm + yy*ym + zy*zm;
	dzm = - zx*xm + zy*ym + zz*zm;

	xm = xm + dxm;
	ym = ym + dym;
	zm = zm + dzm;

/*
 *	convert to mean ecliptic system of date
 */

	alpha = atan2(ym, xm);
	delta = atan2(zm, sqrt(xm*xm+ym*ym));
	cl = cos(delta)*cos(alpha);
	sl = cos(delta)*sin(alpha)*cos(obliq) + sin(delta)*sin(obliq);
	sb = -cos(delta)*sin(alpha)*sin(obliq) + sin(delta)*cos(obliq);
	lambda = atan2(sl, cl);
	beta = atan2(sb, sqrt(cl*cl+sl*sl));
	rad = 1.e9;
	if(px != 0)
		rad = 20600/px;
	motion = 0;
	semi = 0;

	helio();
	geo();
}
