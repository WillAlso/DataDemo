#include <iostream>
using namespace std;
char Precede(char,char);
char Operate(char,char,char);
int main()
{

}
int Precede(char a,char b)
{
	if(a=='+' || a=='-')
	{
		if(b=='+' || b=='-' || b==')' || b=='#')
			return 1;
		else	return -1;
	}
	if(a=='*' || a=='/')
	{
		if(b=='(')
			return -1;
		else	return -1;
	}
	if(a=='(')
	{
		if(b=='#')
			return 100;
		else
			if(b==')')
				return 0;
			else	return -1;
	}
	if(a==')')
	{
		if(b=='(')
			return 100;
		else	return 1;
	}
	if(a=='#')
	{
		if(b=='#')
			return 0;
		else
			if(b==')')
				return 100;
			else	return -1;
	}
}
int Operate(int a,char theta,int b)
{
	switch(theta)
	{
		case '+': return a+b;break;
		case '-': return a-b;break;
		case '*': return a*b;break;
		case '/': return a/b;break;
	}

}
int EvaluateExpression()
{
	stack<char> OPTR;
	stack<int> OPND;
	push(OPER,'#');
	char c;
	c = getchar();
	int flag=1;
	char theta;
	int a,b;
	while(c!='#' || gettop(OPTR)!='#')
	{
		if(!in(c,op))
		{
			int temp = gettop(OPND);
			top(OPND);
			temp = temp*flag+int(c-'0');
			push((OPND,temp));
			falg = 10;
			c = getchar;
		}
		else
		{
			falg=1;
			switch(Precede(gettop(OPTR,c)))
			{
				case -1:
					push(OPTR,c);c=getchar();break;
				case 0:
					pop(OPTR);c=getchar();
					break;
				case 1:
					pop(OPTR,theta);
					pop(OPND,a);pop(OPND,b);
					push(OPND,Operate(a,theta,b));
					break;
			}
		}
	}
	return gettop(OPND);
}
