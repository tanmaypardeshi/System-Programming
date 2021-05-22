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
    char ask = 'Y';

    while (ask == 'Y' || ask == 'y')
    {
        cout << "Enter a string:- ";
        cin >> s;

        if (s == "aa" || s.length() % 2 != 0)
        {
            cout << "String " << s << " rejected" << endl;
            cout << "Do you want to continue? (Y/y):- ";
            cin >> ask;
            break;
        }

        s = s.append("$");

        A();

        if (s[ptr] == '$')
        {
            cout << "String " << s.substr(0, s.length() - 1) << " accepted" << endl;
        }
        else
        {
            cout << "String " << s.substr(0, s.length() - 1) << " rejected" << endl;
        }
        cout << "Do you want to continue? (Y/y):- ";
        cin >> ask;
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

/* Output - 

tanmay@Predator:~/Code/SP/rdp$ ./a.out 
Enter a string:- aaabbaaa
String aaabbaaa accepted
Do you want to continue? (Y/y):- y
Enter a string:- aa
String aa rejected
Do you want to continue? (Y/y):- n

*/