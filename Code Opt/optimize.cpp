// ● Eliminate Dead code/ unreachable code
// ● Common subexpression elimination
// ● Constant folding and Constant propagation
// ● Copy propagation

#include <bits/stdc++.h>
using namespace std;

void read_file(map<int, vector<string> > &stmts)
{
    ifstream fi;
    fi.open("inp.txt", ios::in);
    string line;
    string attr;
    int i = 0;
    while (getline(fi, line))
    {
        i++;
        stringstream s(line);
        while (getline(s, attr, ' '))
        {
            stmts[i].push_back(attr);
        }
    }
}

void display(map<int, vector<string> > &stmts)
{
    for (auto x : stmts)
    {
        cout << x.first << " " << x.second[0] << " " << x.second[1] << " " << x.second[2] << " " << x.second[3] << endl;
    }
}

void dead_code_elimination(map<int, vector<string> > &stmts)
{
    //after return everything is dead
    vector<pair<int, vector<string> > > v;
    for (auto x : stmts)
    {
        v.push_back(make_pair(x.first, x.second));
    }
    for (auto it1 = v.begin(); it1 != v.end(); it1++)
    {
        string ret = it1->second[0];
        if (ret == "return")
        {
            for (auto it2 = it1 + 1; it2 != v.end(); it2++)
            {
                auto it3 = it2;
                stmts.erase(it3->first);
            }
        }
    }
    cout << "\nAfter removing stmts below return\n"
         << endl;
    display(stmts);

    // // eliminate variables that are not used anywhere furthur
    // vector<pair<int, vector<string>>> v1;
    // for (auto x : stmts)
    // {
    //     v1.push_back(make_pair(x.first, x.second));
    // }
    // for (auto it1 = v1.begin(); it1 != v1.end(); it1++)
    // {
    //     string res = it1->second[3];
    //     string op = it1->second[0];
    //     auto it2 = it1 + 1;
    //     if (op == "ifFalse" || op == "Label" || op == "return" || op == "goto")
    //     {
    //         continue;
    //     }
    //     int flag = 0;
    //     for (; it2 != v1.end(); it2++)
    //     {
    //         if (res == it2->second[1] || res == it2->second[2])
    //         {
    //             flag = 1;
    //             break;
    //         }
    //     }
    //     if (flag == 0)
    //     {
    //         stmts.erase(it1->first);
    //     }
    // }
    // cout << "\nAfter removing unused variables\n"
    //      << endl;
    // display(stmts);

    //eliminate variables that are defined and not used before their next definition
    vector<pair<int, vector<string> > > v2;
    for (auto x : stmts)
    {
        v2.push_back(make_pair(x.first, x.second));
    }
    for (auto it1 = v2.begin(); it1 != v2.end(); it1++)
    {
        string res = it1->second[3];
        string op = it1->second[0];
        if (op == "ifFalse" || op == "Label" || op == "return" || op == "goto")
        {
            continue;
        }
        for (auto it2 = it1 + 1; it2 != v2.end(); it2++)
        {
            if (res == it2->second[1] || res == it2->second[2])
                break;
            if (res == it2->second[3] && (it2->second[0] == "=" || it2->second[0] == "+" || it2->second[0] == "-" || it2->second[0] == "*" || it2->second[0] == "/"))
            {
                stmts.erase(it1->first);
            }
        }
    }
    cout << "\nAfter removing variables that are redifined before their use\n"
         << endl;
    display(stmts);
}

bool is_number(const string &s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

void constant_propagation_and_folding(map<int, vector<string> > &stmts)
{
    vector<pair<int, vector<string> > > v;
    for (auto x : stmts)
    {
        v.push_back(make_pair(x.first, x.second));
    }
    for (auto it1 = v.begin(); it1 != v.end(); it1++)
    {
        string res = it1->second[3];
        string op = it1->second[0];
        string arg1 = it1->second[1];
        string arg2 = it1->second[2];
        if (op == "ifFalse" || op == "Label" || op == "return" || op == "goto")
        {
            continue;
        }
        if (is_number(arg1) && arg2 == "NULL")
        {
            string num = arg1;
            for (auto it2 = it1 + 1; it2 != v.end(); it2++)
            {
                if (it2->second[3] == res && (it2->second[1] != res && it2->second[1] != res))
                    break;
                if (it2->second[1] == res)
                {
                    it2->second[1] = num;
                    stmts[it2->first][1] = num;
                }
                if (it2->second[2] == res)
                {
                    it2->second[2] = num;
                    stmts[it2->first][2] = num;
                }
            }
        }
        if (is_number(arg1) && is_number(arg2))
        {
            string num;
            if (op == "+")
            {
                stringstream s1(arg1);
                stringstream s2(arg2);
                int num1, num2, num3;
                s1 >> num1;
                s2 >> num2;
                num = to_string(num1 + num2);
            }
            else if (op == "*")
            {
                stringstream s1(arg1);
                stringstream s2(arg2);
                int num1, num2, num3;
                s1 >> num1;
                s2 >> num2;
                num = to_string(num1 * num2);
            }
            else if (op == "-")
            {
                stringstream s1(arg1);
                stringstream s2(arg2);
                int num1, num2, num3;
                s1 >> num1;
                s2 >> num2;
                num = to_string(num1 - num2);
            }
            else if (op == "/")
            {
                stringstream s1(arg1);
                stringstream s2(arg2);
                int num1, num2, num3;
                s1 >> num1;
                s2 >> num2;
                num = to_string(num1 / num2);
            }
            else if (op == "<")
            {
                stringstream s1(arg1);
                stringstream s2(arg2);
                int num1, num2, num3;
                s1 >> num1;
                s2 >> num2;
                it1->second[1] = it1->second[0];
                it1->second[0] = to_string(num1);
                //cout<<num1<<" "<<num2<<endl;
                cout<<(int)(num1 < num2)<<endl;
                num = to_string((num2));
            } else if (op == ">")
            {
                stringstream s1(arg1);
                stringstream s2(arg2);
                int num1, num2, num3;
                s1 >> num1;
                s2 >> num2;
                num = to_string(num1 > num2);
            } 

            if(op != "<" && op != ">") {
                it1->second[1] = num;
                it1->second[2] = "NULL";
                stmts[it1->first][1] = num;
                stmts[it1->first][2] = "NULL";
                for (auto it2 = it1 + 1; it2 != v.end(); it2++)
                {
                    if (it2->second[3] == res && (it2->second[1] != res && it2->second[1] != res))
                        break;
                    if (it2->second[1] == res)
                    {
                        it2->second[1] = num;
                        stmts[it2->first][1] = num;
                    }
                    if (it2->second[2] == res)
                    {
                        it2->second[2] = num;
                        stmts[it2->first][2] = num;
                    }
                }
            }
        }
    }
}

void cse(map<int, vector<string> > &stmts)
{
    vector<pair<int, vector<string> > > v;
    for (auto x : stmts)
    {
        v.push_back(make_pair(x.first, x.second));
    }

    for (auto it1 = v.begin(); it1 != v.end(); it1++)
    {
        string op = it1->second[0];
        for (auto it2 = it1 + 1; it2 != v.end(); it2++)
        {
            if (op == "ifFalse" || op == "Label" || op == "return" || op == "goto")
            {
                continue;
            }
            if (it1->second[1] == it2->second[1] && it1->second[2] == it2->second[2] && it1->second[0] == it2->second[0])
            {
                string replace = it1->second[3];
                string res = it2->second[3];
                stmts.erase(it2->first);
                for (auto it3 = it2 + 1; it3 != v.end(); it3++)
                {
                    if (it3->second[1] == res)
                    {
                        it3->second[1] = replace;
                        stmts[it3->first][1] = replace;
                    }
                    if (it3->second[2] == res)
                    {
                        it3->second[2] = replace;
                        stmts[it3->first][2] = replace;
                    }
                }
            }
        }
    }
}

void copy_propagation(map<int, vector<string> > &stmts)
{
    vector<pair<int, vector<string> > > v;
    for (auto x : stmts)
    {
        v.push_back(make_pair(x.first, x.second));
    }
    for (auto it1 = v.begin(); it1 != v.end(); it1++)
    {
        string op = it1->second[0];
        string arg1 = it1->second[1];
        string res = it1->second[3];
        if (op == "=")
        {
            for (auto it2 = it1 + 1; it2 != v.end(); it2++)
            {
                if (it2->second[3] == res)
                    break;
                if (it2->second[1] == res)
                {
                    it2->second[1] = arg1;
                    stmts[it2->first][1] = arg1;
                }
                if (it2->second[2] == res)
                {
                    it2->second[2] = arg1;
                    stmts[it2->first][2] = arg1;
                }
            }
        }
    }
}

int main()
{
    map<int, vector<string> > stmts;
    read_file(stmts);
    cout << "Quadruple format before optimization\n"
         << endl;
    display(stmts);
    dead_code_elimination(stmts);
    cse(stmts);
    cout << "\nAfter common subexpression elimination\n"
         << endl;
    display(stmts);
    copy_propagation(stmts);
    cout << "\nAfter copy propagation\n"
         << endl;
    display(stmts);
    constant_propagation_and_folding(stmts);
    cout << "\nAfter constant propagation and constant folding\n"
         << endl;
    display(stmts);
}

