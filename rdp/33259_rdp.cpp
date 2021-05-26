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
    cout << "\nEnter a string to parse:- ";
    cin >> s;

    s.append("$");

    S();

    if (s[ptr] == '$')
        cout << "\nString " << s.substr(0, s.length() - 1) << " accepted.\n"
             << endl;
    else
        cout << "\nString " << s.substr(0, s.length() - 1) << " rejected.\n"
             << endl;

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

/* Output - 

tanmay@Predator:~/Code/SP/rdp$ g++ 33259_rdp.cpp 
tanmay@Predator:~/Code/SP/rdp$ ./a.out 

Enter a string to parse:- a+b

String a+b rejected.

tanmay@Predator:~/Code/SP/rdp$ ./a.out 

Enter a string to parse:- 1+2

String 1+2 accepted.

tanmay@Predator:~/Code/SP/rdp$ ./a.out 

Enter a string to parse:- (1) + 3

String (1) accepted.

tanmay@Predator:~/Code/SP/rdp$ ./a.out 

Enter a string to parse:- (1+)3

String (1+)3 rejected.

tanmay@Predator:~/Code/SP/rdp$ 

*/