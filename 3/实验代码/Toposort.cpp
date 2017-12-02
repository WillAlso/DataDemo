#include <iostream>
#include <stack>
#include <fstream>
#include <malloc.h>
#include <cstring>
using namespace std;
typedef struct ArcNode
{
	int adjvex;
	struct ArcNode *next;
}ArcNode;
typedef struct VNode
{
	int vertex;
	int indegree;
	double score;
	char name[4];
	char bename[10][4];
	int benum;
	ArcNode *firstarc;
}VNode;

void CreatAdjlist(VNode g[],int n)
{
	cout << "������γ�:\n    ���  ѧ��  ���޿γ���Ŀ ���ޱ��" << endl;
	ArcNode *p;
	for(int i = 0;i < n;i++)
	{
		cout << "��" << i+1 << "��:";
		g[i].vertex = i;
		g[i].indegree = 0;
		cin >> g[i].name;
		cin >> g[i].score;
		cin >> g[i].benum;
		for(int t =0;t < g[i].benum;t++)
		{
			cin >> g[i].bename[t];
		}
		g[i].firstarc = NULL;
	}
	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < g[i].benum;j++)
		{
			for(int t = 0;t < n;t++)
			{
				if(strcmp(g[i].bename[j],g[t].name) == 0)
				{
					p = (ArcNode *)malloc(sizeof(ArcNode));
					p->adjvex = i;
					g[i].indegree++;
					p->next = g[t].firstarc;
					g[t].firstarc = p;
				}
			}
		}
	}
}
bool toposort(VNode g[],int n,int *id)
{
	stack<int> s;
	for(int i = 0;i < n;i++)
	{
		if(g[i].indegree == 0)
		{
			s.push(i);
		}
	}
	int count = 0;
	int temp;
	while(!s.empty())
	{
		temp = s.top();	s.pop();
		id[count++] = temp;
		for(ArcNode *p = g[temp].firstarc;p != NULL;p=p->next)
		{
			int k = p->adjvex;
			if((--g[k].indegree) == 0)
			{
				s.push(k);
			}
		}
	}
	if(count<n)
	{
		return false;
	}
	return true;
}

int main()
{
	int term_num;
	int class_num;
	double max_score;
	cout << "������ѧ������:";
	cin >> term_num;
	cout << "������γ���Ŀ:";
	cin >> class_num;
	cout << "������ѧ������:";
	cin >> max_score;
	VNode *g;
	g = (VNode *)malloc(class_num*sizeof(VNode));
	CreatAdjlist(g,class_num);\
	int *id = (int *)malloc(class_num*sizeof(int));
	if(!toposort(g,class_num,id))
	{
		cout << "���ڻ�·!" << endl;
		return 0;
	}
	for(int i = 0;i < class_num;i++)
	{
		cout << g[id[i]].name << " ";
	}
	char chice;
	cout << "��ѡ��\nA����ʹѧ���ڸ�ѧ���е�ѧϰ������������\nB����ʹ�γ̾����ܵؼ�����ǰ����ѧ����" << endl;
	cin >> chice;
	ofstream fout;
	fout.open("1.txt");
	if(!fout)
	{
		cout << "��ʧ��!" << endl;
		return 1;
	}
	if(chice == 'A' || chice == 'a')
	{
		double score_sum = 0;
		for(int i = 0;i < class_num;i++)
		{
			score_sum += g[i].score;
		}
		double score_avg = score_sum / term_num;
		double temp = 0;
		int cnt = 0;
		for(int i = 0;i < term_num && cnt < class_num;i++)
		{
			cout << "��" << i + 1<< "ѧ��:";
			fout << "��" << i + 1<< "ѧ��:";
			bool flag = false;
			while((temp < double(i)*score_avg && cnt < class_num) || !flag)
			{
				temp += g[id[cnt]].score;
				if(temp <= double(i)*score_avg ||!flag)
				{
					cout << g[id[cnt++]].name << " ";
					fout << g[id[cnt-1]].name << " ";
				}
				else
					break;
				flag = true;
			}
			cout << endl;
			fout << endl;
		}
	}
	else if(chice == 'B' || chice == 'b')
	{
		int cnt = 0;
		for(int i = 0;i < term_num && cnt < class_num;i++)
		{
			cout << "��" << i + 1 << "ѧ��:";
			fout << "��" << i + 1 << "ѧ��:";
			double temp = 0;
			bool flag = false;
			while((temp < max_score && cnt < class_num)||!flag)
			{
				temp += g[id[cnt]].score;
				if(temp <= max_score ||!flag)
				{
					cout << g[id[cnt++]].name << " ";
					fout << g[id[cnt-1]].name << " ";
				}
				else
					break;
				flag = true;
			}
			cout << endl;
			fout << endl;
		}
	}
	else
	{
	     cout << "ѡ�����!" << endl;
	     return 0;
	}
	fout.close();
	return 0;
}
