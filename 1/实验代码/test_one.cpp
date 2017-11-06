#include <iostream>
#define ADD true
#define SUB false
using namespace std;
struct pnode* putin();
struct pnode* opera( pnode* pa,pnode* pb,bool f);
void Rank(pnode* pa);
void print(pnode* pa);
struct pnode{
	int expo;
	double coef;
	struct pnode *next;
};
int main()
{
	int choice;
	pnode* pa=putin();
	pnode* pc;;
	Rank(pa);
	pnode* pb=putin();
	Rank(pb);
	cout << "\n请输入两多项式操作类型:(1)相加(2)相减\n";
	cin>> choice;
	if(choice == 1)
	{
		cout <<"\n以上两个相加结果:";
		pc = opera(pa,pb,ADD);
		print(pc);
	}
	if(choice == 2)
	{
		cout <<"\n以上两个相减结果:";
		pc = opera(pa,pb,SUB);
		print(pc);
	}
	return 0;
}

struct pnode* putin()
{
	int temp1;
	double temp2;
	cout << "指数 系数(输入为零结束)\n";
	pnode* head = new pnode;
	pnode* walk = head;
	cin >> temp1 >> temp2;
	while(temp1 != 0 || temp2 != 0)
	{
		walk->next = new pnode;
		walk = walk->next;
		walk->expo = temp1;
		walk->coef = temp2;
		cin >> temp1;//指数
		cin >> temp2;//系数		
	}
	walk->next = NULL;
	return head;
}

struct pnode* opera( pnode* pa,pnode* pb,bool f)
{
	pnode* pc = new pnode;
	pnode *p,*q,*rc;
	p = pa->next;
	q = pb->next;
	rc = pc;
	while(p&&q)
	{
		if(p->expo < q->expo)
		{
			rc->next = p;
			rc = p;
			p = p->next;
		}
		else if(p->expo == q->expo)
		{
			double x;
			if(f) x = p->coef+q->coef;
			else x = p->coef-q->coef;
			rc->next = p;
			p->coef = x;
			rc = p;
			p = p->next;
			q = q->next;
		}
		else if(p->expo > q->expo)
			{
				rc->next=q;
				rc=q;
				if(!f)	rc->coef*=-1;
				q=q->next;
			}
	}
	if (p) rc->next=p; 
	else 
		if(f) rc->next=q;
		else
			while(q)
			{
				rc->next = q;
				q->coef= q->coef *(-1);
				q = q->next;
			}
	return pc;
}

void print(pnode* pa)
{
	pnode* temp = pa;
	temp = temp->next;
	while(temp!=NULL)
	{
		if(temp->coef == 0)
		{
			temp = temp->next;
			continue;
		}
		if(temp->coef != 1)
			cout << temp->coef;
		cout << "X^" << temp->expo;
		if(temp->next!=NULL)
		  {
		    if(temp->next->coef >=0)
			cout << "+";
		  }
		temp = temp->next;
	}
	cout << endl;
}

void Rank(pnode* pa)
{
	int temp;
	double temp1;
	pnode *now_pnode = pa->next;
	pnode *walk = now_pnode;
	while(now_pnode)
	{
		walk = now_pnode;
		while(walk)
		{
			if(walk->expo < now_pnode->expo)
			{
				temp = now_pnode->expo;
				temp1 = now_pnode->coef;
				now_pnode->expo = walk->expo;
				now_pnode->coef = walk->coef;
				walk->expo = temp; 
				walk->coef = temp1;
			}
			walk = walk->next;
		}
		now_pnode = now_pnode->next;
	}
}
