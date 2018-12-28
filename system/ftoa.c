#include <xinu.h>

void ftoa(double d, char* s, int prec){
	int i = 0;
	double tmp =  d;
	for (i = 0; i < prec; i++){
		tmp = tmp * 10;
	}
	int n = tmp;
	sprintf(s, "%d", n);
	if (d >= 1){
		int len = strlen(s);
		s[len + 1] = 0;
		for (i = 0; i < prec; i++){
			s[len] = s[len - 1];
			--len;
		}
		s[len] = '.';
	}else{
		int flen = prec + 2;
		int blen = strlen(s);
		s[flen] = 0;
		for (i = flen - 1; i > 1; i--){
			if (blen > 0)
				s[i] = s[--blen];
			else
				s[i] = '0';
		}
		s[0] = '0';
		s[1] = '.';
	}
}
