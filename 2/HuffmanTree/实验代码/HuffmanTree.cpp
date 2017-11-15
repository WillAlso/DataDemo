#include <iostream>
#include <string>
#include <malloc.h>
using namespace std;
struct charAndNum
{
	char c;
	int num;
	char *code;
	charAndNum* next;
};
typedef struct
{
	char data;
	int weight;
	int parent,lchild,rchild;
}HTNode,*HuffmanTree;
typedef char** HuffmanCode;
charAndNum* charNum()
{
	int char_num[128];
    for(int i=0;i<128;i++)
		char_num[i] = 0;
	charAndNum *p = new charAndNum;
    charAndNum *head = p;
	head->next = NULL;
	head->num = 0;
	string source;
	cout << "ÇëÊäÈëÔ´Âë:" << endl;
	cin >> source;
	for(int j=0;j<source.length();j++)
	{
		char_num[int(source[j])]++;
	}
    for(int i = 0;i < 128;i++)
    {
    	if(char_num[i] != 0)
    	{
			p->next = new charAndNum;
			p = p->next;
    		p->c = char(i);
    		p->num = char_num[i];
			head->num++;
    	}
    }
	p->next = NULL;
	return head;
}

void SelectMin(HuffmanTree HT,int n,int &s1,int &s2)
{
	s1 = s2 = -1;
	int min_1,min_2;
	min_1 = min_2 = 10000;
	for(int i =0;i < n;i++)
	{
		if(HT[i].parent == -1)
		if(HT[i].weight < min_1)
		{
			s1 = i;min_1 = HT[i].weight;
		}
	}
	for(int i = 0;i < n;i++)
	{
		if(HT[i].parent == -1)
		if(HT[i].weight < min_2 && (HT[i].weight >= min_1 && s1 != i))
		{
			s2 = i;min_2 = HT[i].weight;
		}
	}
}

void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,charAndNum *l,int n)
{
	if(n <= 1) return ;
	int m = 2*n-1;
	HT = (HuffmanTree)malloc((m)*sizeof(HTNode));
	HuffmanTree p;
	int i;
	l = l->next;
	for(p = HT,i = 0;i < n && l;++i,l = l->next)
	{
		p[i].weight = l->num;
		p[i].data = l->c;
		p[i].parent = p[i].lchild = p[i].rchild = -1;
	}
	for(;i < m;++i)
	{
		p[i].weight = p[i].parent = p[i].lchild = p[i].rchild = -1;
	}
	for(i = n;i < m;++i)
	{
		int s1,s2;
		SelectMin(HT,i,s1,s2);
		HT[s1].parent = HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	for(int j = 0;j < m;j++)
	{
		cout << "±àºÅ\tÈ¨Öµ\t×óº¢×Ó\tÓÒº¢×Ó\t¸¸Ä¸" << endl;
		cout <<j + 1 << '\t' << HT[j].weight << '\t' << HT[j].lchild + 1 << '\t' << HT[j].rchild + 1 << '\t' << HT[j].parent + 1 << endl;
	}
	HC = (HuffmanCode)malloc((n)*sizeof(char*));
	char* cd = (char*)malloc(n*sizeof(char));
	cd[n-1] = '\0';
	int c,start;
	for(i = 0;i < n;++i)
	{
		start = n -1;
		int f;
		for(c = i,f = HT[i].parent; f != -1;c = f,f = HT[f].parent)
			if(HT[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		HC[i] = (char*)malloc((n-start)*sizeof(char));
		strcpy(HC[i],&cd[start]);
	}
	free(cd);
}
void Decode(HuffmanTree &HT,int n,string source,string &decode)
{
	int root = 2*n-2;
	int p =root;
	int i = 0,k = source.length();
	while(i < k)
	{
		if(source[i]=='0')
			p = HT[p].lchild;
		else
			p = HT[p].rchild;
		if(HT[p].lchild == -1 && HT[p].rchild == -1)
		{
			decode.append(1,HT[p].data);
			p = root;
		}
		i++;
	}
}
int main()
{
	charAndNum *l = charNum();
	int n = l->num;
	HuffmanTree HT;
	HuffmanCode HC;
	charAndNum *head,*temp;
	head = temp = l;
	HuffmanCoding(HT,HC,head,n);
	for(int i = 0;i < n;i++)
	{	head = head ->next;
		head->code = new char[sizeof(HC[i])];
		strcpy(head->code,HC[i]);
	}
	cout << "ÇëÊäÈëÐèÒëÂë:" << endl;
	string m;
	cin >> m;
	string decode;
	Decode(HT,n,m,decode);
	cout << decode;
	return 0;
}
