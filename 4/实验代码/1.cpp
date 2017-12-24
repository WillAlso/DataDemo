#include <iostream>
#include <fstream>
#include <string>
using namespace std;
typedef struct Node {
	string data;
	struct Node *next;
}Node;
typedef struct Hashtable{
	int sizeindex;
	struct Node *next;
}Hashtable;
void insert(Hashtable hashtable[],string m);
struct Node* search(Hashtable hashtable[],string m);
int main()
{
	Hashtable hashtable[11];
	for(int i = 0;i < 11;i++)
	{
		hashtable[i].sizeindex = 0;
		hashtable[i].next = NULL;
	}
	fstream table;
	table.open("1.txt");
	if(!table)
	{
		cout << "输入文件有误!" << endl;
		return 0;
	}
	string m;
	while(getline(table,m))
	{
		insert(hashtable,m);
		cout << m << endl;
	}
	table.close();
	cout << "请输入查询信息:";
	string goal;
	while(cin >> goal)
	{
		struct Node* tempnode;
		if(tempnode = search(hashtable,goal))
		{
			cout << tempnode->data << "查询成功" << endl;
		}
		else
			cout << goal <<"查询失败" <<endl;
	}
	return 0;
}
void insert(Hashtable hashtable[],string m)
{
	char first = m[0];
	int index = int(first) % 11;
	struct Node* tempnode;
	hashtable[index].sizeindex++;
	tempnode = new Node;
	tempnode->data = m;
	tempnode->next = hashtable[index].next;
	hashtable[index].next = tempnode;
}
struct Node* search(Hashtable hashtable[],string m)
{
	char first = m[0];
	int index = int(first) % 11;
	struct Node* tempnode = hashtable[index].next;
	while(tempnode)
	{
		if(tempnode->data == m)
			return tempnode;
		tempnode = tempnode->next;
	}
	return NULL;
}

