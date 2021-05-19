#include <bits/stdc++.h>
using namespace std;

string s;
int ptr = 0;

void A()
{
    if (s[ptr] == 'a')
        ptr++;
    A();
    if (s[ptr] == 'a')
        ptr++;
    else
        return;
}

int main()
{

    cin >> s;
}