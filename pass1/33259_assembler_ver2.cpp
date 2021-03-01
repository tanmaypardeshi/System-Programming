// Tokenize the line and count words

#include <bits/stdc++.h>
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
        int temp = 0;
        int flag = 0;

        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
            {
                flag = 0;
            }
            else if (flag == 0)
            {
                flag = 1;
                temp++;
            }
        }
        cout << "Line is:- " << str << "\nWord count is:- " << temp << "\n"
             << endl;
    }
    fin.close();
    return 0;
}
