#include <bits/stdc++.h>
using namespace std;

typedef struct litTab
{
    string literal;
    int address;
} Literal;

typedef struct symTab
{
    string symbol;
    int address;
    int value;
    int size;
} Symbol;

string filename;

vector<Literal> literal_table;
vector<Symbol> symbol_table;
Literal templ;
Symbol temps;

ifstream input_file, literal_file, symbol_file;

void create_literal_table();
void create_symbol_table();

int main()
{

    create_literal_table();
    create_symbol_table();

    cout << "Enter input filename:- ";
    // cin >> filename;

    // input_file.open(filename, ios::in);

    // if (input_file.good())
    // {
    //     string temp;
    //     while (getline(input_file, temp))
    //     {
    //         char tempCharArray[200];
    //         strcpy(tempCharArray, temp.c_str());

    //         char *token;
    //         char *rest = tempCharArray;
    //     }
    // }
    // else
    // {
    //     cout << filename << " does not exist" << endl;
    // }

    return 0;
}

void create_literal_table()
{
    literal_file.open("literal.txt", ios::in);

    if (literal_file.good())
    {
        string temp;
        while (getline(literal_file, temp))
        {
            char tempCharArray[200];
            strcpy(tempCharArray, temp.c_str());

            char *literal;
            char *address;
            char *rest = tempCharArray;
            // Tokenise words in the line
            literal = strtok_r(rest, " ", &rest);
            address = strtok_r(rest, " ", &rest);
            templ.literal = literal;
            templ.address = stoi(address);
            literal_table.push_back(templ);
        }
    }
    else
    {
        cout << "Literal table does not exist" << endl;
    }
    literal_file.close();
}

void create_symbol_table()
{
    symbol_file.open("symbol.txt", ios::in);

    if (symbol_file.good())
    {
        string temp;
        while (getline(symbol_file, temp))
        {
            char tempCharArray[200];
            strcpy(tempCharArray, temp.c_str());

            char *symbol;
            char *address;
            char *value;
            char *size;
            char *rest = tempCharArray;
            // Tokenise words in the line

            symbol = strtok_r(rest, " ", &rest);
            address = strtok_r(rest, " ", &rest);
            value = strtok_r(rest, " ", &rest);
            size = strtok_r(rest, " ", &rest);
            temps.symbol = symbol;
            temps.address = stoi(address);
            temps.value = stoi(value);
            temps.size = stoi(size);
            symbol_table.push_back(temps);
        }
    }
    else
    {
        cout << "Literal table does not exist" << endl;
    }
    symbol_file.close();
}
