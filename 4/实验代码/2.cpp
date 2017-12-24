/***内部排序
  直接插入排序
  折半插入排序
  希尔排序
  冒泡排序
  快速排序
  选择排序
  归并排序
 ***/
#include <iostream>
using namespace std;
void print(int m[],int n);
int firstsort(int demo[],int n);
int secondsort(int demo[],int n);
int thirdsort(int demo[],int n);
int fouthsort(int demo[],int n);
int fifthsort(int demo[],int s,int t);
int sixthsort(int demo[],int n);
int sevensort(int demo[],int n);
int eightsort(int demo[],int n);
int ninesort(int demo[],int n);
int cnt = 0;
int main()
{
	cout << "直接插入排序" << endl;
	cout << "初始序列:";
	int demo1[] ={3,1,7,9,4,2,5,8,6,0};
	print(demo1,10);
	int step = firstsort(demo1,10);
	cout << "处理序列:";
	print(demo1,10);
	cout << "处理步数:" << step << endl << endl;

	cout << "折半插入排序" << endl;
	cout << "初始序列:";
	int demo2[] ={3,1,7,9,4,2,5,8,6,0};
	print(demo2,10);
	step = secondsort(demo2,10);
	cout << "处理序列:";
	print(demo2,10);
	cout << "处理步数:" << step << endl;

	cout << "希尔排序" << endl;
	cout << "初始序列:";
	int demo3[] ={3,1,7,9,4,2,5,8,6,0};
	print(demo3,10);
	step = thirdsort(demo3,10);
	cout << "处理序列:";
	print(demo3,10);
	cout << "处理步数:" << step << endl << endl;

	cout << "冒泡排序" << endl;
	cout << "初始序列:";
	int demo4[] ={3,1,7,9,4,2,5,8,6,0};
	print(demo4,10);
	step = fouthsort(demo4,10);
	cout << "处理序列:";
	print(demo4,10);
	cout << "处理步数:" << step << endl << endl;

	cout << "快速排序" << endl;
	cout << "初始序列:";
	int demo5[] ={-1,3,1,7,9,4,2,5,8,6,0};//-1为标识，不是排序中元素
	for(int i = 1;i < 11;i++)
		cout << demo5[i] << " ";
	cout << endl;
	step = fifthsort(demo5,1,10);
	cout << "处理序列:";
	for(int i = 1;i < 11;i++)
		cout << demo5[i] << " ";
	cout << endl;
	cout << "处理步数:" << cnt << endl << endl;

	cnt = 0;
	cout << "选择排序" << endl;
	cout << "初始序列:";
	int demo6[] ={3,1,7,9,4,2,5,8,6,0};
	print(demo6,10);
	step = sixthsort(demo6,10);
	cout << "处理序列:";
	print(demo6,10);
	cout << "处理步数:" << cnt << endl << endl;

	cnt = 0;
	cout << "归并排序" << endl;
	cout << "初始序列:";
	int demo7[] ={3,1,7,9,4,2,5,8,6,0};
	print(demo7,10);
	step = eightsort(demo7,10);
	cout << "处理序列:";
	print(demo7,10);
	cout << "处理步数:" << cnt << endl << endl;
}
//直接插入排序
int firstsort(int demo[],int n)
{
	int count = 0;
	int temp;
	int i,j;
	for(i = 1;i < n;i++)
	{
		if(demo[i] < demo[i-1])
		{
			temp = demo[i];
			j = i - 1;
			while(demo[j] > temp)
			{
				count ++;
				demo[j+1] = demo[j];
				j--;
			}
			count ++;
			demo[j+1] = temp;
		}
	}
	return count;
}
//折半插入排序
int secondsort(int demo[],int n)
{
	int count = 0;
	int i,j,low,high,mid;
	int temp;
	for(i = 1;i < n;i++)
	{
		temp = demo[i];
		low = 0;
		high = i - 1;
		while(low <= high)
		{
			mid = (low + high) / 2;
			if(temp > demo[mid])
				low = mid + 1;
			else
				high = mid - 1;
			count++;
		}
		for(j = i-1;j >= high+1;j--)
		{
			demo[j+1] = demo[j];
			count++;
		}
		demo[high+1] = temp;
	}
	return count;
}
//希尔排序
int thirdsort(int demo[],int n)
{
	int d = 1;
	int count = 0;
	int i,j,temp;
	for(i = d;i < n;i++)
	{
		if(demo[i] < demo[i-d])
		{
			temp = demo[i];
			for(j = i - d;j >= 0 && temp <demo[j];j = j-d)
				demo[j+d] = demo[j],count++;
			demo[j+d] = temp;
		}
	}
	return count;
}
//冒泡排序
int fouthsort(int demo[],int n)
{
	int count = 0;
	int i,j,temp,swap;
	for(i = 0;i < n - 1;i++)
	{
		swap = -1;
		for(j = 0;j < n-i-1;j++)
		{
			count++;
			if(demo[j] > demo[j+1])
			{
				temp = demo[j];
				demo[j] = demo[j+1];
				demo[j+1] = temp;
				swap = 1;
			}
		}
		if(swap == -1)
			break;
	}
	return count;
}
int part(int demo[],int i,int j)
{
	demo[0] = demo[i];
	int key = demo[i];
	while(i < j)
	{
		cnt++;
		while(i < j && demo[j] >= key)
			j--,cnt++;
		demo[i] = demo[j];
		while(i < j && demo[i] <= key)
			i++,cnt++;
		demo[j] = demo[i];
	}
	demo[i] = demo[0];
	return i;
}
//快速排序
int fifthsort(int demo[],int s,int t)
{
	int i;
	if(s < t)
	{
		i = part(demo,s,t);
		fifthsort(demo,s,i-1);
		fifthsort(demo,i+1,t);
	}
	return 0;
}
//选择排序
int sixthsort(int demo[],int n)
{
	int t,i,j;
	for(i = 0;i < n;i++)
	{
		j = i;
		for(int m = j;m < n;m++)
		{
			cnt++;
			if(demo[j] >demo[m])
			{
				int x = j;
				j = m;
				m = x;
			}
		}
		if(i != j)
		{
			t = demo[i];
			demo[i] = demo[j];
			demo[j] = t;
		}
	}
	return 0;
}
void merge(int demo1[],int demo2[],int k,int n)
{
	int i,j,l1,u1,l2,u2,m;
	l1 = 0;
	m = 0;
	while(l1 + k < n)
	{
		l2 = l1 + k;
		u1 = l2 -1;
		if(l2 + k - 1 < n)
			u2 = l2 + k -1;
		else
			u2 = n - 1;
		for(i = l1,j = l2;i <= u1 && j <= u2;m++)
		{
			cnt++;
			if(demo1[i] < demo1[j])
				demo2[m] = demo1[i++];
			else
				demo2[m] = demo1[j++];
		}
		while(i <= u1)
			demo2[m++] = demo1[i++],cnt++;
		while(j <= u2)
			demo2[m++] = demo1[j++],cnt++;
		l1 = u2 + 1;
	}
	for(i = l1;i < n;i++,m++)
		demo2[i] = demo1[i],cnt++;
}
//归并排序
int eightsort(int demo[],int n)
{
	int i,k;
	int demo2[30];
	k = 1;
	while(k < n)
	{
		merge(demo,demo2,k,n);
		for(i = 0;i < n;i++)
			demo[i] = demo2[i],cnt++;
		k = 2 * k;
	}
	return 0;
}
void print(int m[],int n)
{
	for(int i = 0;i < n;i++)
		cout << m[i] << " ";
	cout << endl;
}
