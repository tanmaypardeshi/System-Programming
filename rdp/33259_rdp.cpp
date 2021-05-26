#include <bits/stdc++.h>
using namespace std;

string s;
int ptr = 0;

/* Grammar - 

S -> TL
L -> + S | e
T -> UM
M -> *T | e
U -> (S) | V
V -> 0 | 1 | 2 | ..... | 9

*/

void S();
void L();
void T();
void M();
void U();
void V();

int main()
{

    cout << "Enter a string to parse:- ";
    cin >> s;

    s.append("$");

    S();

    if (s[ptr] == '$')
        cout << "String " << s.substr(0, s.length() - 1) << " accepted." << endl;
    else
        cout << "String " << s.substr(0, s.length() - 1) << "rejected." << endl;

    return 0;
}

void S()
{
    T();
    L();
}

void L()
{
    if (s[ptr] == '+')
    {
        ptr++;
        S();
    }
    else
    {
        return;
    }
}

void T()
{
    U();
    M();
}

void M()
{
    if (s[ptr] == '*')
    {
        ptr++;
        T();
    }
}

void U()
{
    if (s[ptr] == '(')
    {
        ptr++;
        S();
        if (s[ptr] == ')')
        {
            ptr++;
        }
    }
    else
    {
        V();
    }
}

void V()
{
    if (s[ptr] == '0' || s[ptr] == '1' || s[ptr] == '2' || s[ptr] == '3' || s[ptr] == '4' || s[ptr] == '5' || s[ptr] == '6' || s[ptr] == '7' || s[ptr] == '8' || s[ptr] == '9')
        ptr++;
}