#include <bits/stdc++.h>
using namespace std;

typedef struct mot
{
    string opcode;
    string size;
    string type;
    string noOfOperands;
} Mot;

typedef struct op1
{
    string operand;
    char type;
    int code;
} Op1;

typedef struct symtab
{
    int lc;
    int value;
    int size;
} SymTab;

Op1 values[11] = {
    {"AREG", 'r', 1},
    {"BREG", 'r', 2},
    {"CREG", 'r', 3},
    {"DREG", 'r', 4},
    {"LT", 'c', 1},
    {"LE", 'c', 2},
    {"GT", 'c', 3},
    {"GE", 'c', 4},
    {"EQ", 'c', 5},
    {"NE", 'c', 6},
    {"ANY", 'c', 7}};

string arr[18];
string token1, token2, token3, token4, filename;

int lc = 0;

Mot motValues[18];

map<string, pair<char, int>> operand_1_map;
map<string, Mot> hash_table;
map<string, SymTab> symbol_table;
vector<::pair<string, int>> literal_table;
vector<int> pool_table;
map<string, SymTab>::iterator itrs;
vector<::pair<string, int>>::iterator itrl;

ifstream hash_file, input_file;

void initialise_operand1();
void create_mot_hash_table();
bool find_literal(string);
int get_index(string);

int main()
{
    pool_table.push_back(0);
    // Create map for operand 1 array
    initialise_operand1();

    // Creating MOT hash table
    create_mot_hash_table();

    // Taking the input from file and appyling pass 1 algorithm
    // cout << "Enter input file:- ";
    // cin >> filename;
    input_file.open("input2.txt");

    if (input_file.good()) // If input file is found
    {
        cout << "-------------------------------------" << endl;

        string temp;
        while (getline(input_file, temp))
        {
            char tempArray[200];
            // Tokenise words in the line
            strcpy(tempArray, temp.c_str());

            char *token;
            char *rest = tempArray;

            token = strtok_r(rest, " ", &rest);
            token1 = token;

            token = strtok_r(rest, " ", &rest);
            token2 = token;

            token = strtok_r(rest, " ", &rest);
            token3 = token;

            token = strtok_r(rest, "\t", &rest);
            token4 = token;

            if (token2.compare("END") == 0 || token2.compare("LTORG") == 0)
            {
                bool first = false;
                int index = pool_table[pool_table.size() - 1];
                for (auto x = literal_table.begin() + index; x != literal_table.end(); x++)
                {
                    cout << lc << "\t";
                    if (!first)
                        cout << "(" << hash_table[token2].type << ", " << hash_table[token2].opcode << ")\t";
                    else
                        cout << "-\t\t";
                    cout << "-\t";
                    cout << x->first << endl;
                    x->second = lc;
                    first = true;
                    lc += 1;
                }

                if (token2.compare("LTORG") == 0)
                {
                    pool_table.push_back(literal_table.size());
                }
                if (token2.compare("END") == 0)
                {
                    cout << "\nSymbol Table is:- " << endl;
                    for (auto x : symbol_table)
                    {
                        cout << x.first << "\t" << x.second.lc << "\t" << x.second.value << "\t" << x.second.size << endl;
                    }
                    cout << "\nLiteral Table is:- " << endl;
                    for (auto x : literal_table)
                    {
                        cout << x.first << "\t" << x.second << endl;
                    }
                    cout << "\nPool Table is:- " << endl;
                    for (auto x : pool_table)
                    {
                        cout << "#" << x << endl;
                    }
                    return 0;
                }
            }
            else
            {
                if (lc == 0)
                {
                    // initial state
                    cout << "-\t";
                }
                else
                {
                    cout << lc << "\t";
                }

                if (token1.compare("-") != 0)
                {
                    if (symbol_table.find(token1) == symbol_table.end())
                    {
                        symbol_table[token1].lc = lc;
                        symbol_table[token1].value = -1;
                        symbol_table[token1].size = -1;
                    }
                }

                cout << "(" << hash_table[token2].type << ", " << hash_table[token2].opcode << ")\t";

                if (token3.compare("-") == 0)
                {
                    // if operand 1 is absent
                    cout << token3 << "\t";
                }
                else
                {
                    cout << "(" << operand_1_map[token3].first << ", " << operand_1_map[token3].second << ")\t";
                }

                if (token2.compare("DC") == 0 || token2.compare("DS") == 0)
                {
                    if (token4.at(0) == '\'')
                        token4 = token4.substr(1, token4.length() - 2);
                    cout
                        << "(C, " << token4 << ")\t" << endl;
                    symbol_table[token1].lc = lc;
                    symbol_table[token1].lc = lc;
                    if (token2.compare("DC") == 0)
                    {
                        symbol_table[token1].value = stoi(token4);
                        symbol_table[token1].size = 1;
                        lc += 1;
                    }
                    else if (token2.compare("DS") == 0)
                    {
                        symbol_table[token1].value = -1;
                        symbol_table[token1].size = stoi(token4);
                        lc += stoi(token4);
                    }
                }
                else if (token4.compare("-") == 0)
                {
                    cout << token4 << endl;
                    lc += stoi(hash_table[token2].size);
                }
                else if (token4.at(0) == '=')
                {
                    bool found = find_literal(token4);
                    int index;
                    if (!found)
                    {
                        literal_table.push_back(::pair<string, int>(token4, -1));
                        index = literal_table.size() - 1;
                    }
                    else
                    {
                        index = get_index(token4);
                    }
                    cout << "(L, " << index << ")\t" << endl;
                    lc += stoi(hash_table[token2].size);
                }
                else if (isalpha(token4[0]) != 0)
                {
                    if (symbol_table.find(token4) == symbol_table.end())
                    {
                        symbol_table[token4].lc = -1;
                        symbol_table[token4].value = -1;
                        symbol_table[token4].size = -1;
                    }
                    itrs = symbol_table.find(token4);
                    size_t index = distance(symbol_table.begin(), itrs);
                    cout << "(S, " << index << ")\t" << endl;
                    lc += stoi(hash_table[token2].size);
                }
                else
                {
                    if (token4.at(0) == '\'')
                        token4 = token4.substr(1, token4.length() - 2);
                    cout
                        << "(C, " << token4 << ")\t" << endl;
                    lc += stoi(token4);
                }
                symbol_table.erase("-");
            }
        }

        cout << "-------------------------------------" << endl;
    }
    else
    {
        cout << "File " << filename << "does not exist" << endl;
        return 0;
    }

    input_file.close();

    return 0;
}

void initialise_operand1()
{
    // Create a map for the operand 1 array
    for (int i = 0; i < 11; i++)
    {
        operand_1_map.insert(make_pair((values[i].operand), (make_pair(values[i].type, values[i].code))));
    }
}

void create_mot_hash_table()
{
    int count = 0;

    // Open the MOT
    hash_file.open("hashing.txt", ios::in);

    //Traversing the file and creating the hash table
    if (hash_file.good()) // Ff file is found
    {
        string temp;
        while (getline(hash_file, temp))
        // Read the MOT file line by line
        {
            char tempCharArray[200];

            strcpy(tempCharArray, temp.c_str());

            char *token;
            char *rest = tempCharArray;
            // Tokenise words in the line
            token = strtok_r(rest, " ", &rest);
            arr[count] = token;

            token = strtok_r(rest, " ", &rest);
            motValues[count].opcode = token;

            token = strtok_r(rest, " ", &rest);
            motValues[count].size = token;

            token = strtok_r(rest, " ", &rest);
            motValues[count].type = token;

            token = strtok_r(rest, " ", &rest);
            motValues[count].noOfOperands = token;

            count++;
        }
    }

    hash_file.close();

    //Creating the hash table

    for (int i = 0; i < 18; i++)
    {
        hash_table[arr[i]] = motValues[i];
    }
}

bool find_literal(string token)
{
    int index = pool_table[pool_table.size() - 1];
    for (auto x = literal_table.begin() + index; x != literal_table.end(); x++)
    {
        if (x->first.compare(token) == 0)
            return true;
        return false;
    }
}

int get_index(string token)
{
    int index = pool_table[pool_table.size() - 1];
    for (auto x = literal_table.begin() + index; x != literal_table.end(); x++)
    {
        if (x->first == token)
            return x - literal_table.begin();
        return -1;
    }
}