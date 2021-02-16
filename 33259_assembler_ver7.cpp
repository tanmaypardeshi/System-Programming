#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
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

int main()
{
    // i and count for loops
    int i, count = 0;

    // Op1 values
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

    // Array of string for storing mnemonics
    string arr[18];

    // Array of struct to store the rest of the MOT entities
    Mot motValues[18];

    // Operand 1 map to map the Op1 array
    map<string, pair<char, int>> operand_1_map;

    // Hash table of key as mnemonic and value as the MOT entities
    map<string, Mot> hash_table;

    // Input file stream for taking the MOT text file as input
    ifstream hash_file;

    // Input file stream for the input code to be converted to IC
    ifstream input_file;

    // Entities of the input file
    string label, mnemonic, operand1, operand2;

    // Operand 2 symbol table as a map
    map<string, int> symbol_table;

    // To maintain index in symbol table
    int index = 0;

    // Create a map for the operand 1 array
    for (i = 0; i < 11; i++)
    {
        operand_1_map.insert(std::make_pair((values[i].operand), (std::make_pair(values[i].type, values[i].code))));
    }

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
            token = strtok_r(rest, "\t", &rest);
            arr[count] = token;

            token = strtok_r(rest, "\t", &rest);
            motValues[count].opcode = token;

            token = strtok_r(rest, "\t", &rest);
            motValues[count].size = token;

            token = strtok_r(rest, "\t", &rest);
            motValues[count].type = token;

            token = strtok_r(rest, "\t", &rest);
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

    // Taking the input from file and appyling pass 1 algorithm
    input_file.open("input.txt");

    // Reinitialise the count to 0

    count = 0;

    cout << "-------------------------------------" << endl;

    if (input_file.good()) // If input file is found
    {
        string temp;
        while (getline(input_file, temp))
        {
            char tempArray[200];

            // Tokenise words in the line
            strcpy(tempArray, temp.c_str());

            char *token;
            char *rest = tempArray;

            token = strtok_r(rest, " ", &rest);
            label = token;

            token = strtok_r(rest, " ", &rest);
            mnemonic = token;

            token = strtok_r(rest, " ", &rest);
            operand1 = token;

            token = strtok_r(rest, "\t", &rest);
            operand2 = token;

            cout << "\nLine number : " << count + 1 << endl;
            cout << "Label : " << label << endl;

            // Look for the data of the mnemonic in the hash_table
            cout << "Intermediate code will be : " << endl;
            cout << "\nMnemonic : " << mnemonic << endl;
            cout << "(Type, Opcode) : (" << hash_table[mnemonic].type << ", " << hash_table[mnemonic].opcode << ")" << endl;

            // Look for the operand 1 type and code in the operand 1 map
            cout << "\nOperand 1 : " << operand1 << endl;
            if (operand_1_map[operand1].first != '-')
                cout << "(Type, Code) : (" << operand_1_map[operand1].first << ", " << operand_1_map[operand1].second << ")" << endl;

            cout << "\nOperand 2 : " << operand2 << endl;
            // If operand 2 contains an alphabet, find/add to symbol table
            if (isalpha(operand2[0]) != 0)
            {
                // Find the operand in the operand table first, and if not found, add the operand to the next index in the map
                if (symbol_table.find(operand2) == symbol_table.end())
                    //not found
                    symbol_table[operand2] = index++;
                // Display Operand 2
                cout << "(Type, Index) : ("
                     << "S, " << symbol_table[operand2] << ")" << endl;
            }
            // If operand 2 is a digit, then directly write it as a constant
            else
            {
                cout << "(Type, Value) : "
                     << "(C, " << operand2 << ")" << endl;
            }

            count++;
        }
    }
    cout << "-------------------------------------" << endl;

    input_file.close();

    return 0;
}

/* Output

tanmay@Predator:~/Code/SP$ g++ 33259_assembler_ver6.cpp 
tanmay@Predator:~/Code/SP$ ./a.out 
-------------------------------------

Line number : 1
Label : -
Intermediate code will be : 

Mnemonic : START
(Type, Opcode) : (    AD, 01)

Operand 1 : -
(Type, Code) : (, 0)

Operand 2 : 2000
(Type, Value) : (C, 2000)

Line number : 2
Label : -
Intermediate code will be : 

Mnemonic : MOVER
(Type, Opcode) : (    IS, 04)

Operand 1 : AREG
(Type, Code) : (r, 1)

Operand 2 : A
(Type, Index) : (S, 0)

Line number : 3
Label : -
Intermediate code will be : 

Mnemonic : ADD
(Type, Opcode) : (    IS,     01)

Operand 1 : AREG
(Type, Code) : (r, 1)

Operand 2 : X
(Type, Index) : (S, 1)

Line number : 4
Label : -
Intermediate code will be : 

Mnemonic : DIV
(Type, Opcode) : (    IS,     08)

Operand 1 : BREG
(Type, Code) : (r, 2)

Operand 2 : A
(Type, Index) : (S, 0)

Line number : 5
Label : XYZ
Intermediate code will be : 

Mnemonic : SUB
(Type, Opcode) : (    IS,     02)

Operand 1 : DREG
(Type, Code) : (r, 4)

Operand 2 : A
(Type, Index) : (S, 0)

Line number : 6
Label : -
Intermediate code will be : 

Mnemonic : STOP
(Type, Opcode) : (    IS, 00)

Operand 1 : -
(Type, Code) : (, 0)

Operand 2 : C
(Type, Index) : (S, 2)

Line number : 7
Label : A
Intermediate code will be : 

Mnemonic : DC
(Type, Opcode) : (    DL,     01)

Operand 1 : -
(Type, Code) : (, 0)

Operand 2 : 10
(Type, Value) : (C, 10)

Line number : 8
Label : X
Intermediate code will be : 

Mnemonic : DS
(Type, Opcode) : (    DL,     02)

Operand 1 : -
(Type, Code) : (, 0)

Operand 2 : 100
(Type, Value) : (C, 100)

Line number : 9
Label : -
Intermediate code will be : 

Mnemonic : END
(Type, Opcode) : (    AD,     04)

Operand 1 : -
(Type, Code) : (, 0)

Operand 2 : B
(Type, Index) : (S, 3)
-------------------------------------
tanmay@Predator:~/Code/SP$ 

*/