#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "my_evalute.h"

int main(int argc,const char* argv[])
{
	if(argc>1)
	{
		double rez;
		int x;
		for(x=1;x<argc;x++)
		{
			int ret=eval(argv[x],&rez);
			if(!ret)
				printf("%lf\n",rez);
			else
				return 1;
		}
	}
	else
	{
		//help
		short x;
		printf("amv (amv_post@mail.ru)\nConsole calculator v. 1.0 (08.03.2008)\n");
		printf("Released operations:\n");
		for(x=0;x<PRIOR_NUM;x++)
			printf("\t%s\n",oper[x]);
		printf("Released functions:\n");
		for(x=0;x<FUN_NUM;x++)
			printf("\t%s\n",fun[x]);
		printf("PI == %lf\n",PI);
	}
	return 0;
}
