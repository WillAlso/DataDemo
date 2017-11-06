#include <iostream>
#include <fstream>
using namespace std;
int main()
{
    int char_num[128];
    for(int i=0;i<128;i++)
        char_num[i] = 0;
    ifstream fout("C:\\1.txt");
    if(!fout)
    {
        cout << "Error" << endl;
        return 0;
    }
    char c;
    while(fout.get(c))
    {
        char_num[(int)c]++;
        cout << c;
    }
    fout.close();
    for(int i = 0;i<128;i++)
    {
        if(char_num[i]!=0)
            cout << (char)i << " " << char_num[i] << "\n";
    }
    return 0;
}
