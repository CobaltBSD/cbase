#include<stdlib.h>

void srandom_deterministic(unsigned int seed) {
	srandom(seed); // Simply redirects to srandom
}
