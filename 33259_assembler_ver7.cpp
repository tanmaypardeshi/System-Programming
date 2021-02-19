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

Mot motValues[18];

map<string, pair<char, int>> operand_1_map;
map<string, Mot> hash_table;
map<string, int> symbol_table;

ifstream hash_file, input_file;

void initialise_operand1();
void create_mot_hash_table();

int main()
{
    string token1, token2, token3, token4;
    int count = 0, index = 0, lc = 0;

    // Create map for operand 1 array
    initialise_operand1();

    // Creating MOT hash table
    create_mot_hash_table();

    // Taking the input from file and appyling pass 1 algorithm
    input_file.open("input.txt");

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
            token1 = token;

            token = strtok_r(rest, " ", &rest);
            token2 = token;

            token = strtok_r(rest, " ", &rest);
            token3 = token;

            token = strtok_r(rest, "\t", &rest);
            token4 = token;

            // cout << token1 << "\t" << token2 << "\t" << token3 << "\t" << token4 << "\n";

            if (lc == 0)
            {
                // initial state
                cout << "-\t";
            }
            else
            {
                cout << lc << "\t";
            }

            if (token1.compare("-") == 0)
            {
                //if label is  not present
                cout << token1 << "\t";
            }
            else
            {
                // if label is present
                if (symbol_table.find(token1) == symbol_table.end())
                    symbol_table[token1] = index++;
                cout << symbol_table[token1] << "\t";
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

            if (isalpha(token4[0]) != 0)
            {
                if (symbol_table.find(token4) == symbol_table.end())
                    symbol_table[token4] = index++;
                cout << "("
                     << "S, " << symbol_table[token4] << ")\t\n";
                lc += stoi(hash_table[token2].size);
            }
            else
            {
                cout << "(C, " << token4 << ")\t\n";
                lc += stoi(token4);
            }

            count++;
        }
    }
    cout << "-------------------------------------" << endl;

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