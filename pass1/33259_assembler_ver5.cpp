// Tokenize the line and count words

#include <bits/stdc++.h>
using namespace std;

typedef struct MOT
{
    char mnemonic[10];
    int opcode;
    int size;
    char type[3];
    char operands[3];
} Mot;

void createhashtable(Mot[]);
int search(Mot[], string);

int main()
{
    string filename;
    Mot t[200];

    int count;

    for (int i = 0; i < 200; i++)
    {
        t[i].opcode = 0;
        memset(t[i].mnemonic, ' ', 10);
        t[i].size = 0;
        memset(t[i].type, ' ', 3);
        memset(t[i].operands, ' ', 3);
    }

    cout << "Creating a hash table.." << endl;
    createhashtable(t);
    cout << "Hash table created successfully" << endl;

    cout << "\nEnter the filename to be read:- ";
    cin >> filename;

    ifstream fin;

    fin.open(filename, ios::in);

    if (fin.fail())
    {
        cout << "Error, " << filename << " does not exist" << endl;
        return 0;
    }

    string str;

    cout << "Contents of the file are:- " << endl;
    while (getline(fin, str))
    {
        cout << "Line is:- " << str << endl;

        char *dup = strdup(str.c_str());
        char *token = strtok(dup, " ");
        vector<string> tok;

        while (token)
        {
            tok.push_back(token);
            token = strtok(NULL, " ");
        }

        int id = search(t, tok[1]);

        cout << "Found at id:- " << id << endl;
        cout << "Values in hash table are:- " << endl;
        cout << "Mnemonic:- " << t[id].mnemonic << endl;
        cout << "Opcode:- " << t[id].opcode << endl;
        cout << "Size:- " << t[id].size << endl;
        cout << "Type:- " << t[id].type << endl;

        cout << endl;
    }

    return 0;
}

void createhashtable(Mot t[])
{
    string str;
    ifstream fin;

    fin.open("hashing.txt", ios::in);
    if (fin.fail())
    {
        cout << "Error, file does not exist" << endl;
        return;
    }
    cout << endl;

    while (getline(fin, str))
    {
        char *dup = strdup(str.c_str());
        char *token = strtok(dup, "\t");
        vector<string> tok;

        while (token)
        {
            tok.push_back(token);
            token = strtok(NULL, "\t");
        }

        int hash_code = abs(tolower(*tok[0].begin()) - *tok[0].rbegin());

        if (t[hash_code].opcode == 0)
        {
            strcpy(t[hash_code].mnemonic, tok[0].c_str());
            t[hash_code].opcode = atoi(tok[1].c_str());
            t[hash_code].size = atoi(tok[2].c_str());
            strcpy(t[hash_code].type, tok[3].c_str());
            strcpy(t[hash_code].operands, tok[4].c_str());
        }
        else
        {
            hash_code += *tok[0].begin();
            if (hash_code > 100)
            {
                hash_code %= 14;
            }
            strcpy(t[hash_code].mnemonic, tok[0].c_str());
            t[hash_code].opcode = atoi(tok[1].c_str());
            t[hash_code].size = atoi(tok[2].c_str());
            strcpy(t[hash_code].type, tok[3].c_str());
            strcpy(t[hash_code].operands, tok[4].c_str());
        }
    }

    fin.close();
}

int search(Mot t[], string instruction)
{
    int hash_code = abs(*instruction.begin() - *instruction.rbegin());

    if (t[hash_code].opcode != 0)
    {
        return hash_code;
    }
    hash_code += *instruction.begin();
    if (hash_code > 100)
    {
        hash_code %= 14;
        return hash_code;
    }
    return hash_code;
}