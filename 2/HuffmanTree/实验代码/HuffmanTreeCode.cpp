#include <iostream>
#include <malloc.h>
#include <cstring>
using namespace std;

typedef struct
{
	int weight;
	int parent,lchild,rchild;
}HTNode,*HuffmanTree;
typedef char** HuffmanCode;

void SelectMin(HuffmanTree HT,int n,int &s1,int &s2)
{
	s1 = s2 = 0;
	int i;
	for(i = 1;i < n;++i)
	{
		if(HT[i].parent == 0)
		{
			if(s1 == 0)
			{
				s1 = i;
			}
			else
			{
				s2 = i;break;
			}
		}
	}
	if(HT[s1].weight > HT[s2].weight)
	{
		int t = s1;
		s1 = s2;
		s2 = t;
	}

	for(i += 1;i < n;++i)
	{
		if(HT[i].parent == 0)
		{
			if(HT[i].weight < HT[s1].weight)
			{
				s2 = s1;
				s1 = i;
			}
			else if(HT[i].weight < HT[s2].weight)
			{
				s2 = i;
			}
		}
	}
}

void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n)
{
	if(n <= 1) return ;
	int m = 2*n-1;
	HT = (HuffmanTree)malloc((m+1)*sizeof(HTNode));
	HuffmanTree p;
	int i;
	for(p = HT,i = 1;i <= n;++i,++p,++w)
	{
		p[i].weight = *w;
		p[i].parent = p[i].lchild = p[i].rchild = 0;
	}
	for(;i <= m;++i,++p)
	{
		p[i].weight = p[i].parent = p[i].lchild = p[i].rchild = 0;
	}
	for(i = n+1;i <= m;++i)
	{
		int s1,s2;
		SelectMin(HT,i-1,s1,s2);
		HT[s1].parent = HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	HC = (HuffmanCode)malloc((n+1)*sizeof(char*));
	char* cd = (char*)malloc(n*sizeof(char));
	cd[n-1] = '\0';
	int c,start;
	for(i = 1;i <= n;++i)
	{
		start = n -1;
		int f;
		for(c = i,f = HT[i].parent; f != 0;c = f,f = HT[f].parent)
			if(HT[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		HC[i] = (char*)malloc((n-start)*sizeof(char));
		strcpy(HC[i],&cd[start]);
	}
	free(cd);
}

int main()
{
	cout << "Please input the source(eg:C:\\1.txt)" << endl;

	return 0;
}
