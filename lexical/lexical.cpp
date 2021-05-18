#include <bits/stdc++.h>
using namespace std;

vector<string> us_table, symbol_table, literal_table, keyword_table, operator_table, double_operator_table;

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

    write_data();

    return 0;
}

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

int is_double_operator(string op)
{
    for (int i = 0; i < double_operator_table.size(); i++)
        if (op == double_operator_table[i])
            return i;
    return -1;
}

int is_keyword(string word)
{
    for (int i = 0; i < keyword_table.size(); i++)
        if (word.compare(keyword_table[i]) == 0)
            return i;
    return -1;
}

bool is_separator(char a)
{
    if (a == ' ')
        return true;
    return false;
}

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
    string temp = "";
    int check;
    for (int i = 0; i < line.length(); i++)
    {
        temp.append(string(1, line[i]));

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
        else if (is_keyword(temp) != -1)
        {
            check = is_keyword(temp);
            add_to_ust(temp, "KEYW", check, temp);
            temp = "";
        }
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
