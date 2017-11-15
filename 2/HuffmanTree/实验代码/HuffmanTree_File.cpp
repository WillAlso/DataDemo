#include <iostream>
#include <string>
#include <malloc.h>
#include <fstream>
using namespace std;

//初始化
//编码
//译码
//打印译码文件

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

//初始化函数
charAndNum* charNum()
{
		int char_num[128];
    	for(int i=0;i<128;i++)
		char_num[i] = 0;
		charAndNum *p = new charAndNum;
    	charAndNum *head = p;
		head->next = NULL;
		head->num = 0;
		ifstream table("C:\\1.txt");
    	if(!table)
    	{
        		cout << "Error" << endl;
        		return NULL;
    	}
    	char c;
    	while(table.get(c))
    	{
        		char_num[(int)c]++;
    	}
    	table.close();
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

//选择最小
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

//编码
void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,charAndNum *l,int n)
{
	if(n <= 1) return ;
	int m = 2*n-1;
	HT = (HuffmanTree)malloc((m)*sizeof(HTNode));
	HuffmanTree p;
	int i;
	l = l->next;
	//++w;
	for(p = HT,i = 0;i < n;++i,l = l->next)
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
		cout << "编号\t权值\t左孩子\t右孩子\t父母" << endl;
		cout <<j + 1 << '\t' << HT[j].weight << '\t' << HT[j].lchild + 1 << '\t' << HT[j].rchild + 1 << '\t' << HT[j].parent + 1 << endl;
	}
	/*char* cd = new char[n];
	int l = m;
	int cdlen = 0;
	for(int i =0;i <= m;++i)
		HT[i].weight = 0;
	while(l)
	{
		if(HT[l].weight == 0)
		{
			HT[l].weight = 1;
			if(HT[l].lchild != 0)
			{
				l = HT[l].lchild;cd[cdlen++] = '0';
			}
			else if(HT[l].rchild == 0)
			{
				HC[l] = (char*)malloc((cdlen+1)*sizeof(char));
				cd[cdlen] = '\0';
				strcpy(HC[l],cd);
			}
		}
		else if(HT[l].weight == 1)
		{
			HT[l].weight = 2;
			if(HT[l].rchild != 0)
			{
				l = HT[l].rchild;
				cd[cdlen++] = '1';
			}
			else
			{

				HT[l].weight = 0;l=HT[l].parent;--cdlen;
			}
		}
	}
	delete [] cd;*/
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

void Tran(charAndNum *p,char* m,int n)
{
	p = p ->next;
	int i,j;
	int now = 0;
	int cnt = 0;
	string t1,t2;
	for(i = 0;cnt < sizeof(m);i++,cnt++)
	{
		for(j = 0;j < n;j++)
		{
			t1.assign(p[j].code);
			t2.assign(&m[now],i+1);
			if(t1 == t2){
				cout << p[i].c;now = now + i;i = 0;break;}
		}
		
	}
}
void Decode(HuffmanTree &HT,int n,char *source,char *decode)
{
	int root = 2*n-2;
	int p =root;
	int i = 0,k = 0;
	while(source[i])
	{
		if(source[i]=='0')
			p = HT[p].lchild;
		else
			p = HT[p].rchild;
		if(HT[p].lchild == -1 && HT[p].rchild == -1)
		{
			decode[k++] = HT[p].data;
			p = root;
		}
		i++;
	}
	decode[k] = '\0';
}
//
//void Code(Huffman &HT,
//主函数
int main()
{
	cout << "Please input the source(eg:C:\\1.txt)" << endl;
	charAndNum *l = charNum();
	charAndNum *head = l;
	charAndNum *temp = head;
	int n = l->num - 1;
	cout << n;
	l = l->next;
	/*int w[128];
	for(int i = 0;i < 128;i++)
	{
		if(l)
		{
			w[i] = l->num;
			l = l->next;
		}
		else
			w[i] = 0;
	}*/
	HuffmanTree HT;
	HuffmanCode HC;
	HuffmanCoding(HT,HC,l,n);
	for(int i = 0;i < n;i++)
	{	head = head ->next;
		head->code = new char[sizeof(HC[i])];
		cout << HC[i] << endl;
		strcpy(head->code,HC[i]);
	}
	ifstream table("C:\\1.txt");
    	if(!table)
    	{
        		cout << "Error" << endl;
        		return NULL;
    	}
    	char c;
    	while(table.get(c))
    	{
			for(int te = 0;te < n;te++)
			{
				if(HT[te].data == c)
					cout << HC[te];
			}
    	}
    	table.close();
	//for(int i = 0;i<n;i++)
	//	temp = temp->next,cout << temp ->c << " " << temp->code << endl;
		cout << endl;
	char m[] = "0001000100010001000110101010101010101010101010101010101010101010101010101010101110111011101110111011101110111111111111111111111111111111111101101101101101101101101101101101101101100101010101010101010101010101010101010101010101000000000000001001001001001001001001001001001";
//	Tran(temp,m,n);
	char *decode;
	decode = new char[1000];
	Decode(HT,n,m,decode);
	cout << decode;
	return 0;
}
