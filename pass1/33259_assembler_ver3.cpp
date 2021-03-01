// Tokenize the line and count words

#include <bits/stdc++.h>
using namespace std;

int main()
{
    string filename, str, mnemonic;
    int lineno = 1, flag = 0;
    cout << "Enter filename:- ";
    cin >> filename;

    ifstream fin(filename);

    if (!fin)
    {
        cout << "Error, file " << filename << " not found." << endl;
        return 0;
    }
    cout << endl;

    cout << "Enter the mnemonic:- ";
    cin >> mnemonic;

    cout << endl;

    while (getline(fin, str))
    {
        if (str.find(mnemonic) != -1)
        {
            cout << str << endl;
            flag = 1;
        }
    }
    if (!flag)
    {
        cout << "Could not find the opcode for " << mnemonic << "." << endl;
    }
    fin.close();
    return 0;
}
