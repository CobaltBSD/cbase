#include<stdio.h>
#include<zxcvbn.h>

int main(void) {
	char in[BUFSIZ] = {0};
	(void) fread(in, sizeof(char), BUFSIZ, stdin);

	int rc = ZxcvbnInit("/usr/share/misc/zxcvbn.dict");
	if(rc == 0) {
		(void) fputs("Failed to init zxcvbn\n", stderr);
	}
	double entropy = ZxcvbnMatch(in, NULL, NULL);
	ZxcvbnUnInit();

	(void) printf("%lf\n", entropy);
	return 0;
}
