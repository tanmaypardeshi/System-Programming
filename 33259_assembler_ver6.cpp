#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

typedef struct mot
{
    string mne;
    string opcode;
    string size;
    string type;
    string noOfOperands;

} mot;

typedef struct value
{
    string opcode;
    string size;
    string type;
    string noOfOperands;
} value;

typedef struct op1
{
    string operand;
    char type;
    int code;
} op1;

int main()
{
    int i, count = 0;

    mot arr[18];
    value motValues[18];

    op1 values[11] = {
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

    map<string, pair<char, int>> mapOperand;
    map<string, value> m;

    for (i = 0; i < 11; i++)
    {
        mapOperand.insert(std::make_pair((values[i].operand), (std::make_pair(values[i].type, values[i].code))));
    }

    fstream mneFile, testFile;
    mneFile.open("hashing.txt", ios::in);

    //Traversing the file and creating the necessary structure
    if (mneFile.is_open())
    {
        string temp;
        while (getline(mneFile, temp))
        {
            char tempCharArray[200];

            strcpy(tempCharArray, temp.c_str());

            char *token;
            char *rest = tempCharArray;

            token = strtok_r(rest, "\t", &rest);
            arr[count].mne = token;

            token = strtok_r(rest, "\t", &rest);
            arr[count].opcode = token;
            motValues[count].opcode = token;

            token = strtok_r(rest, "\t", &rest);
            arr[count].size = token;
            motValues[count].size = token;

            token = strtok_r(rest, "\t", &rest);
            arr[count].type = token;
            motValues[count].type = token;

            token = strtok_r(rest, "\t", &rest);
            arr[count].noOfOperands = token;
            motValues[count].noOfOperands = token;

            count++;
        }
    }

    mneFile.close();

    //Creating the map
    for (int i = 0; i < 18; i++)
    {
        m[arr[i].mne] = motValues[i];
    }

    tuple<string, int> mnemonic;
    tuple<char, int> operand1;
    tuple<char, int> operand2;

    string label, mne, op1, op2;
}