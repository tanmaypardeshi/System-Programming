#include <bits/stdc++.h>
using namespace std;

// Global tables to store data
vector<string> us_table, symbol_table, literal_table, keyword_table, operator_table, double_operator_table;

// Function declarations
void add_data();
void write_data();
int is_operator(string);
int is_double_operator(string);
int is_keyword(string);
bool is_separator(char);
bool is_literal(string);
void process_line(string);
void add_to_ust(string, string, int, string);

int main()
{
    ifstream input_file;
    string temp;

    // Adding keywords, operators from text files;
    add_data();

    // Taking input from user and reading and processing it line by line
    input_file.open("input.txt");

    if (input_file.good())
    {
        while (getline(input_file, temp))
        {
            process_line(temp);
        }
    }
    else
    {
        cout << "\nInput file not found" << endl;
        return 0;
    }

    input_file.close();

    // Writing data to the console

    write_data();

    return 0;
}

// Function populate keyword and operator tables
void add_data()
{
    string temp;
    ifstream keywords_file, operators_file;

    //Adding keywords

    keywords_file.open("keywords.txt", ios::in);

    if (keywords_file.good())
    {
        while (getline(keywords_file, temp))
        {
            keyword_table.push_back(temp);
        }
        cout << "Keywords added" << endl;
    }
    else
    {
        cout << "Keywords file is missing" << endl;
        return;
    }

    keywords_file.close();

    // Adding operators

    operators_file.open("operators.txt", ios::in);

    if (operators_file.good())
    {
        while (getline(operators_file, temp))
        {
            operator_table.push_back(temp);
        }
    }
    else
    {
        cout << "Operators file is missing" << endl;
        return;
    }

    operators_file.close();

    operators_file.open("double_operators.txt", ios::in);

    if (operators_file.good())
    {
        while (getline(operators_file, temp))
        {
            double_operator_table.push_back(temp);
        }
        cout << "Operators added" << endl;
    }
    else
    {
        cout << "Operators file is missing" << endl;
        return;
    }

    operators_file.close();
}

void write_data()
{
    int id = 0;
    cout << "---------------------Universal Symbol table----------------------------" << endl;
    cout << "LEXEME\t\tTYPE\t\tINDEX\t\tTOKEN" << endl;
    cout << "-----------------------------------------------------------------------" << endl;
    for (auto x : us_table)
    {
        cout << x << endl;
    }
    cout << "-----------------------------------------------------------------------" << endl;
    cout << "\n\n----------Symbol table-------------" << endl;
    cout << "INDEX\tSYMBOL" << endl;
    cout << "-----------------------------------" << endl;
    for (auto x : symbol_table)
    {
        cout << id << "\t" << x << endl;
        id++;
    }
    cout << "-----------------------------------" << endl;
    cout << "\n\n----------Literal table-------------" << endl;
    cout << "INDEX\tLITERAL" << endl;
    cout << "------------------------------------" << endl;
    id = 0;
    for (auto x : literal_table)
    {
        cout << id << "\t" << x << endl;
        id++;
    }
    cout << "-----------------------------------" << endl;
}

// Check if token passed operator
int is_operator(string op)
{
    for (int i = 0; i < operator_table.size(); i++)
        if (op == operator_table[i])
            return i;
        else if (op == "=")
            return 2;
        else if (op == ";")
            return 1;
        else if (op == ",")
            return 0;
    return -1;
}

// Check if token passed operator
int is_double_operator(string op)
{
    for (int i = 0; i < double_operator_table.size(); i++)
        if (op == double_operator_table[i])
            return i;
    return -1;
}

// Check if token passed is a keyword
int is_keyword(string word)
{
    for (int i = 0; i < keyword_table.size(); i++)
        if (word.compare(keyword_table[i]) == 0)
            return i;
    return -1;
}

// Check if there is a space
bool is_separator(char a)
{
    if (a == ' ')
        return true;
    return false;
}

// Check if token passed a literal
bool is_literal(string word)
{
    int flag = 0;
    for (int i = 0; i < word.length(); i++)
    {
        if (word[i] == '0' || word[i] == '1' || word[i] == '2' || word[i] == '3' ||
            word[i] == '4' || word[i] == '5' || word[i] == '6' || word[i] == '7' ||
            word[i] == '8' || word[i] == '9')
            flag = 1;
        else
        {
            flag = 0;
            break;
        }
    }
    if (flag)
        return true;
    return false;
}

// Add data to UST after formatting tabs and spaces
void add_to_ust(string lexeme, string type, int index, string token)
{
    string temp = "";
    temp.append(lexeme);
    temp.append("\t\t");
    temp.append(type);
    temp.append("\t\t");
    temp.append(to_string(index));
    temp.append("\t\t");
    temp.append(token);
    us_table.push_back(temp);
}

void process_line(string line)
{
    // Dealing with comments
    if (line[0] == '/' && line[1] == '/')
        return;

    // Initialisation
    string temp = "";
    int check;

    // Iterating line character by character
    for (int i = 0; i < line.length(); i++)
    {
        temp.append(string(1, line[i]));

        // Dealing with double operator
        if (i > 0)
        {
            check = is_double_operator(line.substr(i - 1, 2));
            if (check != -1)
            {
                add_to_ust(line.substr(i - 1, 2), "TERM", check, line.substr(i - 1, 2));
                us_table.erase(us_table.end() - 3);
                i++;
                if (temp.length() > 0)
                {
                    temp = temp.substr(0, temp.length() - 2);
                    check = is_keyword(temp);
                    if (check != -1)
                    {
                        add_to_ust(temp, "KEYW", check, temp);
                    }
                    else if (is_literal(temp))
                    {
                        literal_table.push_back(temp);
                        add_to_ust(temp, "LIT", literal_table.size() - 1, "ID");
                    }
                    else if (int(temp[0]) != 0)
                    {
                        if (temp[0] == '"')
                        {
                            string lit = "";
                            lit.append(string(1, temp[0]));
                            int j = 1;
                            while (temp[j] != '"')
                            {
                                lit.append(string(1, temp[j++]));
                            }
                            lit.append(string(1, '"'));
                            literal_table.push_back(lit);
                            add_to_ust(lit, "LIT", literal_table.size() - 1, "CONST");
                        }
                        else if (temp[0] == '\'')
                        {
                            string lit = "";
                            lit.append(string(1, temp[0]));
                            int j = 1;
                            while (temp[j] != '\'')
                            {
                                lit.append(string(1, temp[j++]));
                            }
                            lit.append(string(1, '\''));
                            literal_table.push_back(lit);
                            add_to_ust(lit, "LIT", literal_table.size() - 1, "CONST");
                        }
                    }
                }
                temp = "";
            }
        }

        // Dealing with operator
        check = is_operator(string(1, line[i]));

        if (check != -1)
        {
            add_to_ust(string(1, line[i]), "TERM", check, string(1, line[i]));

            if (temp.length() > 0)
            {
                temp = temp.substr(0, temp.length() - 1);
                check = is_keyword(temp);
                if (check != -1)
                {
                    add_to_ust(temp, "KEYW", check, temp);
                }
                else if (is_literal(temp))
                {
                    literal_table.push_back(temp);
                    add_to_ust(temp, "LIT", literal_table.size() - 1, "CONST");
                }
                else if (int(temp[0]) != 0)
                {
                    if (temp[0] == '"')
                    {
                        string lit = "";
                        lit.append(string(1, temp[0]));
                        int j = 1;
                        while (temp[j] != '"')
                        {
                            lit.append(string(1, temp[j++]));
                        }
                        lit.append(string(1, '"'));
                        literal_table.push_back(lit);
                        add_to_ust(lit, "LIT", literal_table.size() - 1, "CONST");
                    }
                    else if (temp[0] == '\'')
                    {
                        string lit = "";
                        lit.append(string(1, temp[0]));
                        int j = 1;
                        while (temp[j] != '\'')
                        {
                            lit.append(string(1, temp[j++]));
                        }
                        lit.append(string(1, '\''));
                        literal_table.push_back(lit);
                        add_to_ust(lit, "LIT", literal_table.size() - 1, "CONST");
                    }
                    else
                    {
                        int id = -1;
                        for (int i = 0; i < symbol_table.size(); i++)
                        {
                            if (temp == symbol_table[i])
                            {
                                id = i;
                                break;
                            }
                        }
                        if (id == -1)
                        {
                            symbol_table.push_back(temp);
                            id = symbol_table.size() - 1;
                        }
                        add_to_ust(temp, "SYM", id, "ID");
                    }
                }
            }
            temp = "";
        }

        // Checking for spaces
        else if (is_separator(line[i]))
        {
            if (temp.length() > 1)
            {
                temp = temp.substr(0, temp.length() - 1);
                int id = -1;
                for (int i = 0; i < symbol_table.size(); i++)
                {
                    if (temp == symbol_table[i])
                    {
                        id = i;
                        break;
                    }
                }
                if (id == -1)
                {
                    symbol_table.push_back(temp);
                    id = symbol_table.size() - 1;
                }
                add_to_ust(temp, "SYM", id, "ID");
            }
            temp = "";
        }
        // Checking for keywords
        else if (is_keyword(temp) != -1)
        {
            check = is_keyword(temp);
            add_to_ust(temp, "KEYW", check, temp);
            temp = "";
        }
        // Checking for literals
        else if (is_literal(temp))
        {
            while (is_literal(temp))
            {
                temp.append(string(1, line[++i]));
            }
            temp = temp.substr(0, temp.length() - 1);
            literal_table.push_back(temp);
            add_to_ust(temp, "LIT", literal_table.size() - 1, "CONST");
        }
    }
}

/* Output - 

tanmay@Predator:~/Code/SP/lexical$ g++ 33259_lexical.cpp 
tanmay@Predator:~/Code/SP/lexical$ ./a.out 
Keywords added
Operators added
---------------------Universal Symbol table----------------------------
LEXEME          TYPE            INDEX           TOKEN
-----------------------------------------------------------------------
(               TERM            15              (
main            SYM             0               ID
)               TERM            16              )
{               TERM            13              {
int             KEYW            16              int
,               TERM            0               ,
a               SYM             1               ID
;               TERM            1               ;
b               SYM             2               ID
a               SYM             1               ID
++              TERM            0               ++
;               TERM            1               ;
int             KEYW            16              int
;               TERM            1               ;
c               SYM             3               ID
c               SYM             3               ID
=               TERM            2               =
a               SYM             1               ID
+               TERM            5               +
;               TERM            1               ;
b               SYM             2               ID
(               TERM            15              (
printf          SYM             4               ID
)               TERM            16              )
"Hello"         LIT             0               CONST
;               TERM            1               ;
return          KEYW            19              return
0               LIT             1               CONST
}               TERM            14              }
-----------------------------------------------------------------------


----------Symbol table-------------
INDEX   SYMBOL
-----------------------------------
0       main
1       a
2       b
3       c
4       printf
-----------------------------------


----------Literal table-------------
INDEX   LITERAL
------------------------------------
0       "Hello"
1       0
-----------------------------------
tanmay@Predator:~/Code/SP/lexical$ 

*/
