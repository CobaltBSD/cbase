#include <u.h>
#include <libc.h>

static Lock privlock;
static ulong privmap;

int
privalloc(void)
{
	int i;

	lock(&privlock);
	for(i=0; i<NPRIV; i++)
		if((privmap&(1<<i)) == 0){
			privmap |= (1<<i);
			unlock(&privlock);
			return i;
		}
	unlock(&privlock);
	return -1;
}

void**
privmem(int i)
{
	return NULL; // Stub
}
