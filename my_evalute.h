#ifndef MY_EVALUTE
#define MY_EVALUTE

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define ERROR_FORMULA 1
#define PI acos(-1)
#define FUN_NUM 18
#define PRIOR_NUM 3

const char *oper[PRIOR_NUM]={"^","*/","+-"};
const char *fun[FUN_NUM]={"arcsin","arccos","arctg","arcctg","ctg","tg","sin","cos","arccth","cth","th","sh","ch","abs","log10","log","exp","pi"};

short eval(const char *f,double *rez);
short eval_function(const char *f,double *rez);
short eval_formula(const char *f,double *rez);

short eval(const char *f,double *rez)
{
	int size=strlen(f);
	int x,from,to;
	double really_rez;
	char *fm=(char*)malloc(size+1);
	char *next_fm;
	char *fm_to_eval=(char*)malloc(size+1);
	strcpy(fm,f);
	from=-1;
	x=0;
	for(;x<size;x++)
	{
		if(fm[x]=='(')
			from=x;
		else if(fm[x]==')')
		{
			if(from>-1)
			{
				to=x;
				strncpy(fm_to_eval,&fm[from+1],to-from-1);
				fm_to_eval[to-from-1]='\0';
				if(eval_function(fm_to_eval,&really_rez))
				{
					free(fm);
					free(fm_to_eval);
					return ERROR_FORMULA;
				}
				size=size-(to-from+1)+17;
				next_fm=(char*)malloc(size);
				strncpy(next_fm,fm,from);
				sprintf(&next_fm[from],"%lf%s",really_rez,&fm[to+1]);
				free(fm);
				fm=next_fm;
				size=strlen(fm);
				x=-1;
				from=-1;
			}
			else
			{
				free(fm);
				free(fm_to_eval);
				return ERROR_FORMULA;
			}
		}
	}
	if(from>-1 || eval_function(fm,rez))
	{
		free(fm);
		free(fm_to_eval);
		return ERROR_FORMULA;
	}
	return 0;
}

short eval_function(const char *f,double *rez)
{
	unsigned int size=strlen(f);
	char *from,*to,*next_fm;
	int x;
	double op,really_rez;
	char *fm=(char*)malloc(size+1);
	strcpy(fm,f);
	for(x=0;x<FUN_NUM;x++)
	{
		from=strstr(fm,fun[x]);
		while(from)
		{
			to=from;
			to+=strlen(fun[x]);
			op=strtod(to,&to);
			size=size-(to-from+1)+17;
			next_fm=(char*)malloc(size);
			switch(x)
			{
				case 6:
				{
					//sin
					really_rez=sin(op);
					break;
				}
				case 7:
				{
					//cos
					really_rez=cos(op);
					break;
				}
				case 5:
				{
					//tg
					if(cos(op))
						really_rez=tan(op);
					else
					{
						free(fm);
						return ERROR_FORMULA;
					}
					break;
				}
				case 4:
				{
					//ctg
					double temp_tan=tan(op);
					if(temp_tan)
						really_rez=1/temp_tan;
					else
					{
						free(fm);
						return ERROR_FORMULA;
					}
					break;
				}
				case 0:
				{
					//arcsin
					really_rez=asin(op);
					break;
				}
				case 1:
				{
					//arccos
					really_rez=acos(op);
					break;
				}
				case 2:
				{
					//arctg
					really_rez=atan(op);
					break;
				}
				case 3:
				{
					//arcctg
					really_rez=PI/2-atan(op);
					break;
				}
				case 11:
				{
					//sh
					really_rez=sinh(op);
					break;
				}
				case 12:
				{
					//ch
					really_rez=cosh(op);
					break;
				}
				case 10:
				{
					//th
					really_rez=tanh(op);
					break;
				}
				case 9:
				{
					//cth
					double temp_th=tanh(op);
					if(temp_th)
						really_rez=1/temp_th;
					else
					{
						free(fm);
						return ERROR_FORMULA;
					}
					break;
				}
				case 8:
				{
					//arccth
					if(op!=1)
						really_rez=0.5*log((1+op)/(op-1));
					else
					{
						free(fm);
						return ERROR_FORMULA;
					}
					break;
				}
				case 13:
				{
					//abs
					really_rez=fabs(op);
					break;
				}
				case 14:
				{
					//log10
					really_rez=log10(op);
					break;
				}
				case 15:
				{
					//log
					really_rez=log(op);
					break;
				}
				case 16:
				{
					//exp
					really_rez=exp(op);
					break;
				}
				case 17:
				{
					//pi: really_rez=pi*op
					really_rez=PI*op;
					break;
				}
			}
			strncpy(next_fm,fm,from-fm);
			sprintf(&next_fm[from-fm],"%lf%s",really_rez,to);
			free(fm);
			fm=next_fm;
			size=strlen(fm);
			from=strstr(fm,fun[x]);
		}
	}
	if(eval_formula(fm,rez))
	{
		free(fm);
		return ERROR_FORMULA;
	}
	else
		free(fm);
	return 0;
}

short eval_formula(const char *f,double *rez)
{
	int size=strlen(f);
	int x;
	char *ser,*begin,*end,*next_fm;
	char operations;
	double op[2],really_rez=0;
	char *fm=(char*)malloc(size+1);
	if(f[0]=='-' && f[1]=='-')
		strcpy(fm,&f[2]);
	else
		strcpy(fm,f);
	for(x=0;x<size;x++)
		if(!isdigit(fm[x]) && fm[x]!='.' && fm[x]!='^' && fm[x]!='*' && fm[x]!='/' && fm[x]!='+' && fm[x]!='-')
		{
			free(fm);
			return ERROR_FORMULA;
		}
	for(x=0;x<PRIOR_NUM;x++)
	{
		ser=strpbrk(fm+1,oper[x]);
		while(ser)
		{
			operations=*ser;
			op[1]=strtod(ser+1,&end);
			if(ser+1==end)
			{
				free(fm);
				return ERROR_FORMULA;
			}
			while(ser>fm && (isdigit(*(ser-1)) || *(ser-1)=='.'))
				ser--;
			if(ser>f && *(ser-1)=='-' && (ser==f+1 || !isdigit(*(ser-2))))
				ser--;
			begin=ser;
			op[0]=strtod(ser,&ser);
			if(begin==ser)
			{
				free(fm);
				return ERROR_FORMULA;
			}
			switch(operations)
			{
				case '^':
				{
					really_rez=pow(op[0],op[1]);
					break;
				}
				case '*':
				{
					really_rez=op[0]*op[1];
					break;
				}
				case '/':
				{
					if(op[1])
						really_rez=op[0]/op[1];
					else
					{
						free(fm);
						return ERROR_FORMULA;
					}
					break;
				}
				case '-':
				{
					really_rez=op[0]-op[1];
					break;
				}
				case '+':
				{
					really_rez=op[0]+op[1];
					break;
				}
			}
			size=size-(end-begin+1)+17;
			next_fm=(char*)malloc(size);
			strncpy(next_fm,fm,begin-fm);
			sprintf(&next_fm[begin-fm],"%lf%s",really_rez,end);
			//free(fm);
			fm=next_fm;
			size=strlen(fm);
			ser=strpbrk(fm+1,oper[x]);
		}
	}
	(*rez)=strtod(fm,&begin);
	return 0;
}

#endif
