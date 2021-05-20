#include <bits/stdc++.h>
using namespace std;

/*
Grammar : 
A -> aAa | bBb
B -> bBb | NULL
*/

void A();
void B();

string s;
int ptr = 0;

int main()
{
    cout << "Enter a string(Please end the string with a $):- ";
    cin >> s;

    A();

    if (s[ptr] == '$')
    {
        cout << "String " << s << " accepted" << endl;
    }
    else
    {
        cout << "String " << s << " rejected" << endl;
    }
    return 0;
}

void A()
{
    if (s[ptr] == 'a')
    {
        ptr++;
        A();
        if (s[ptr] == 'a')
            ptr++;
        else
            return;
    }
    if (s[ptr] == 'b')
    {
        ptr++;
        B();
        if (s[ptr] == 'b')
            ptr++;
        else
            return;
    }
    else
        return;
}

void B()
{
    if (s[ptr] == 'b')
    {
        ptr++;
        B();
        if (s[ptr] == 'b')
            ptr++;
        else
            return;
    }
}
