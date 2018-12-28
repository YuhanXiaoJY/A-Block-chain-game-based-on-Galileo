#include <xinu.h>

double atof(char *str)
{
	double s=0.0;
	double d=10.0;
	int count=0;
	bool8 flag=FALSE;
	while(*str==' ')
		str++;

	if(*str=='-'){
		flag=TRUE;
		str++;
	}
	
	if(!(*str>='0'&&*str<='9'))//如果一开始非数字则退出，返回0.0
		return s;

	while(*str>='0'&&*str<='9'&&*str!='.')//计算小数点前整数部分
	{
		s=s*10.0+*str-'0';
		str++;
	}

	if(*str=='.')//以后为小树部分
		str++;

	while(*str>='0'&&*str<='9')//计算小数部分
	{
		s=s+(*str-'0')/d;
		d*=10.0;
		str++;
	}
	if(*str=='e'||*str=='E')//考虑科学计数法
	{
		str++;
		if(*str=='+')
		{
			str++;
			while(*str>='0'&&*str<='9')
			{
				count=count*10+*str-'0';
				str++;
			}
			while(count>0)
			{
				s*=10;
				count--;
			}
		}
		
		if(*str=='-')
		{
			str++;
			while(*str>='0'&&*str<='9')
			{
				count=count*10+*str-'0';
				str++;
			}
			while(count>0)
			{
				s/=10;
				count--;
			}
		}
	}
	return s*(flag?-1.0:1.0);
}
