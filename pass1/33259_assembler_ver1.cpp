// Read input line after line

#include <bits/stdc++.h>
#define OUT 0
#define IN 1
using namespace std;

int main()
{
    string filename, str;
    int lineno = 1;
    cout << "Enter filename:- ";
    cin >> filename;

    ifstream fin(filename);

    if (!fin)
    {
        cout << "Error, file " << filename << " not found." << endl;
        return 0;
    }

    cout << endl;

    while (getline(fin, str))
    {
        cout << "Line is:- " << str << "\n"
             << endl;
    }
    fin.close();
    return 0;
}
