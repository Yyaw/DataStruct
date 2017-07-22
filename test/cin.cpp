#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string txt = "input.txt";
    ifstream in(txt.c_str());
    int size;
    while (!in.eof())
    {
        in >> size;
        cout << size << " ";
    }
}