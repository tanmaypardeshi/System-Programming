#include <bits/stdc++.h>
using namespace std;

// MOT structure
typedef struct mot
{
    string opcode;
    string size;
    string type;
    string noOfOperands;
} Mot;

// Structure for operand 1 in output
typedef struct op1
{
    string operand;
    char type;
    int code;
} Op1;

// Structure for symbol table
typedef struct symtab
{
    int lc;
    int value;
    int size;
} SymTab;

// Declaration of operand 1
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

// Global variable declarations
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

// Function declarations
void initialise_operand1();
void create_mot_hash_table();
bool find_literal(string);
int get_index(string);
void tokenise(string);
void print_tables();
void handle_ltorg_or_end();
void handle_lc();
void handle_label();
void handle_mnemonic();
void handle_operand1();
void handle_operand2();

int main()
{
    pool_table.push_back(0);
    // Create map for operand 1 array
    initialise_operand1();

    // Creating MOT hash table
    create_mot_hash_table();

    // Taking the input from file and appyling pass 1 algorithm
    cout << "Enter input file:- ";
    cin >> filename;
    input_file.open(filename);

    if (input_file.good()) // If input file is found
    {
        string temp;
        cout << "\n\nIntermediate Code is:- \n";
        cout << "--------------------------------------------------------" << endl;
        cout << "LC\tMNEMONIC\tOPERAND 1\tOPERAND 2\n";
        cout << "--------------------------------------------------------" << endl;
        while (getline(input_file, temp))
        {
            tokenise(temp); // tokenise the line into label, mnemonic, operand 1 and 2

            if (token2.compare("END") == 0 || token2.compare("LTORG") == 0) // if end or ltorg is enountered in the assembly program
            {
                handle_ltorg_or_end(); // function to handle ltorg or end
                if (token2.compare("END") == 0)
                {
                    // If end is reached, print the tables and exit the program
                    cout << "--------------------------------------------------------" << endl;
                    print_tables();
                    return 0;
                }
            }
            else // for all the other cases
            {
                handle_lc();
                handle_label();
                handle_mnemonic();
                handle_operand1();
                handle_operand2();
            }
        }
    }
    else // if file is not found
    {
        cout << "File " << filename << " does not exist" << endl;
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
    // Function to find the literal in the literal table and return false if not found
    int index = pool_table[pool_table.size() - 1];
    for (auto x = literal_table.begin() + index; x != literal_table.end(); x++)
    {
        if (x->first.compare(token) == 0)
            return true;
    }
    return false;
}

int get_index(string token)
{
    // Return index of the literal in the literal table
    int index = pool_table[pool_table.size() - 1];
    for (auto x = literal_table.begin() + index; x != literal_table.end(); x++)
    {
        if (x->first == token)
            return x - literal_table.begin();
    }
    return -1;
}

void tokenise(string line)
{
    // Tokenise the line into label, mnemonic, operand 1 and 2
    char tempArray[200];
    // Tokenise words in the line
    strcpy(tempArray, line.c_str());

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
}

void print_tables()
{
    // Printing of the symbol table
    cout << "\nSymbol Table is:- " << endl;
    cout << "---------------------------------" << endl;
    cout << "Symbol\tIndex\tValue\tSize" << endl;
    cout << "---------------------------------" << endl;
    for (auto x : symbol_table)
    {
        cout << x.first << "\t" << x.second.lc << "\t" << x.second.value << "\t" << x.second.size << endl;
    }

    // Printing of the literal table
    cout << "---------------------------------" << endl;
    cout << "\nLiteral Table is:- " << endl;
    cout << "-----------------" << endl;
    cout << "Literal\tIndex\t" << endl;
    cout << "-----------------" << endl;
    for (auto x : literal_table)
    {
        cout << x.first << "\t" << x.second << endl;
    }

    // Printing of the pool table
    cout << "-----------------" << endl;
    cout << "\nPool Table is:- " << endl;
    cout << "-----------" << endl;
    cout << "Index" << endl;
    cout << "-----------" << endl;
    for (auto x : pool_table)
    {
        cout << "#" << x << endl;
    }
    cout << "-----------" << endl;
}

void handle_ltorg_or_end()
{
    // Handle LTORG and print the values from the literal table
    bool first = false;
    int index = pool_table[pool_table.size() - 1];
    for (auto x = literal_table.begin() + index; x != literal_table.end(); x++)
    {
        cout << lc << "\t";
        if (!first)
            cout << "(" << hash_table[token2].type << ", " << hash_table[token2].opcode << ")\t\t";
        else
            cout << "-\t\t\t";
        cout << "-\t";
        cout << x->first << endl;
        x->second = lc;
        first = true;
        lc += 1;
    }

    // Update value of index in pool table
    if (token2.compare("LTORG") == 0)
    {
        pool_table.push_back(literal_table.size());
    }
}

void handle_lc()
{
    // Display LC
    if (lc == 0)
    {
        // initial state
        cout << "-\t";
    }
    else
    {
        cout << lc << "\t";
    }
}

void handle_label()
{
    // Handle labels and populate symbol table if label does not exist
    if (token1.compare("-") != 0)
    {
        if (symbol_table.find(token1) == symbol_table.end())
        {
            symbol_table[token1].lc = lc;
            symbol_table[token1].value = -1;
            symbol_table[token1].size = -1;
        }
    }
}

void handle_mnemonic()
{
    // Search in hash_table for mnemonic and return necessary information
    cout << "(" << hash_table[token2].type << ", " << hash_table[token2].opcode << ")\t";
}

void handle_operand1()
{
    // Return type and code of operand 1 after looing it up in the operand 1 table
    if (token3.compare("-") == 0)
    {
        // if operand 1 is absent
        cout << token3 << "\t\t";
    }
    else
    {
        cout << "(" << operand_1_map[token3].first << ", " << operand_1_map[token3].second << ")\t\t";
    }
}

void handle_operand2()
{
    // IF DC or DS are encountered
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

    // If - is encountered
    else if (token4.compare("-") == 0)
    {
        cout << token4 << endl;
        lc += stoi(hash_table[token2].size);
    }

    // If literal is encountered
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

    // If symbol is encountered
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

    // If Constant is encountered
    else
    {
        if (token4.at(0) == '\'')
            token4 = token4.substr(1, token4.length() - 2);
        cout
            << "(C, " << token4 << ")\t" << endl;
        lc += stoi(token4);
    }
}

/* Output 1
tanmay@Predator:~/Code/SP$ g++ 33259_assembler_ver7.cpp 
tanmay@Predator:~/Code/SP$ ./a.out 
Enter input file:- a.txt
File a.txt does not exist
tanmay@Predator:~/Code/SP$ 
*/

/* Output 2 
tanmay@Predator:~/Code/SP$ g++ 33259_assembler_ver7.cpp 
tanmay@Predator:~/Code/SP$ ./a.out 
Enter input file:- input.txt


Intermediate Code is:- 
--------------------------------------------------------
LC      MNEMONIC        OPERAND 1       OPERAND 2
--------------------------------------------------------
-       (AD, 01)        -               (C, 1000)
1000    (IS, 04)        (r, 1)          (S, 0)
1003    (IS, 01)        (r, 4)          (S, 1)
1005    (IS, 07)        (c, 1)          (S, 2)
1007    (IS, 08)        (r, 3)          (S, 0)
1009    (IS, 02)        (r, 3)          (L, 0)
1011    (IS, 05)        (r, 1)          (L, 1)
1015    (IS, 00)        -               -
1016    (DL, 01)        -               (C, 10)
1017    (DL, 02)        -               (C, 10)
1027    (AD, 04)                -       ='1'
1028    -                       -       ='2'
--------------------------------------------------------

Symbol Table is:- 
---------------------------------
Symbol  Index   Value   Size
---------------------------------
A       1016    10      1
B       1017    -1      10
XYZ     1003    -1      -1
---------------------------------

Literal Table is:- 
-----------------
Literal Index
-----------------
='1'    1027
='2'    1028
-----------------

Pool Table is:- 
-----------
Index
-----------
#0
-----------
tanmay@Predator:~/Code/SP$ 
*/

/* Output 3 
tanmay@Predator:~/Code/SP$ g++ 33259_assembler_ver7.cpp 
tanmay@Predator:~/Code/SP$ ./a.out 
Enter input file:- input2.txt


Intermediate Code is:- 
--------------------------------------------------------
LC      MNEMONIC        OPERAND 1       OPERAND 2
--------------------------------------------------------
-       (AD, 01)        -               (C, 1000)
1000    (IS, 04)        (r, 1)          (L, 0)
1003    (IS, 02)        (r, 3)          (L, 0)
1005    (IS, 07)        (c, 1)          (S, 0)
1007    (IS, 08)        (r, 1)          (L, 1)
1009    (IS, 01)        (r, 4)          (L, 2)
1011    (AD, 03)                -       ='1'
1012    -                       -       ='2'
1013    -                       -       ='3'
1014    (IS, 08)        (r, 3)          (S, 0)
1016    (IS, 02)        (r, 3)          (L, 3)
1018    (IS, 05)        (r, 1)          (L, 4)
1022    (AD, 03)                -       ='1'
1023    -                       -       ='2'
1024    (IS, 00)        -               -
1025    (DL, 01)        -               (C, 10)
1026    (DL, 02)        -               (C, 10)
--------------------------------------------------------

Symbol Table is:- 
---------------------------------
Symbol  Index   Value   Size
---------------------------------
A       1025    10      1
B       1026    -1      10
XYZ     -1      -1      -1
---------------------------------

Literal Table is:- 
-----------------
Literal Index
-----------------
='1'    1011
='2'    1012
='3'    1013
='1'    1022
='2'    1023
-----------------

Pool Table is:- 
-----------
Index
-----------
#0
#3
#5
-----------
tanmay@Predator:~/Code/SP$ 
*/
