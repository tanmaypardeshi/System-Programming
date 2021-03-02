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
bool first = true;

vector<Literal> literal_table;
vector<Symbol> symbol_table;
Literal templ;
Symbol temps;

ifstream input_file, literal_file, symbol_file;

void create_literal_table();
void create_symbol_table();
bool isDc(int);

int main()
{

    create_literal_table();
    create_symbol_table();

    // cout << "Enter input filename:- ";
    // cin >> filename;

    input_file.open("input.txt", ios::in);

    if (input_file.good())
    {
        string temp;
        while (getline(input_file, temp))
        {
            char tempCharArray[200];
            strcpy(tempCharArray, temp.c_str());

            char *token;
            char *rest = tempCharArray;
            char *lct, *mnemonict, *op1t, *op2t;
            string lc, mnemonic, op1, op2;
            lct = strtok_r(rest, " ", &rest);
            mnemonict = strtok_r(rest, " ", &rest);
            op1t = strtok_r(rest, " ", &rest);
            op2t = strtok_r(rest, " ", &rest);
            lc.assign(lct);
            mnemonic.assign(mnemonict);
            op1.assign(op1t);
            op2.assign(op2t);
            if (!first)
            {
                if (mnemonic.compare("-") != 0)
                {
                    mnemonic.erase(0, 1);
                    mnemonic.erase(mnemonic.size() - 1);
                    if (mnemonic.substr(0, 2).compare("IS") == 0)
                    {
                        if (op1.compare("-") != 0)
                        {
                            int index;
                            if (op2.at(1) == 'L')
                            {
                                op2.pop_back();
                                index = stoi(op2.substr(3, 4));
                                cout << lc << "\t+" << mnemonic.substr(3, 5) << "\t" << op1.at(3) << "\t" << literal_table[index].address << endl;
                            }
                            else if (op2.at(1) == 'S')
                            {
                                op2.pop_back();
                                index = stoi(op2.substr(3, 4));
                                cout << lc << "\t+" << mnemonic.substr(3, 5) << "\t" << op1.at(3) << "\t" << symbol_table[index].address << endl;
                            }
                        }
                    }
                    else if (mnemonic.substr(0, 2).compare("AD") == 0)
                    {
                        op2.pop_back();
                        cout << lc << "\t+00\t00\t" << op2.substr(2, op2.size() - 1) << endl;
                    }
                    else if (mnemonic.substr(0, 2).compare("DL") == 0)
                    {
                        bool flag = isDc(stoi(lc));
                        if (flag)
                        {
                            op2.pop_back();
                            cout << lc << "\t+00\t00\t" << op2.substr(3, op2.size() - 1) << endl;
                        }
                        else
                        {
                            cout << lc << "\t+00\t00\t00" << endl;
                        }
                    }
                }
                else
                {
                    op2.pop_back();
                    cout << lc << "\t+00\t00\t" << op2.substr(2, op2.size() - 1) << endl;
                }
            }
            first = false;
        }
    }
    else
    {
        cout << filename << " does not exist" << endl;
    }

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

bool isDc(int address)
{
    for (auto x : symbol_table)
    {
        if (address == x.address)
        {
            if (x.size != -1)
                return false;
        }
    }
    return true;
}