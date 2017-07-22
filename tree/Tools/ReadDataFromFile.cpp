#include "ReadDataFromFile.h"

int main()
{
    using namespace std;
    string file = "input.txt";
    ReadFile f(file);
    auto result = f.readData();
    for (auto line : result)
    {
        for (auto d : line)
            cout << d << " ";
        cout << endl;
    }
    return 0;
}