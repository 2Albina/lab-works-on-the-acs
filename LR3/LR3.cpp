// LR3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string> 
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stack>
#include <queue>
using namespace std;
bool fl = true;

//проверка корректности переменных
bool IsCorrect(char ch)
{
    if ((ch == '0' || ch == '1') || (ch == 'x' || ch == 'y' || ch == 'z' || ch == 't'))
        return true;
    return false;
}

//проверка корректности операторов
bool IsOperator(char ch)
{
    if (ch == '!' || ch == '&' || ch == '|' || ch == '/' || ch == '+' || ch == 'V' || ch == '>' || ch == '=')
        return true;
    return false;
}

//установка приоритета операторов
int priority(char oper)
{
    switch (oper)
    {
    case '!':
        return 5;
    case '&':
        return 4;
    case '|':
        return 4;
    case '/':
        return 4;
    case 'V':
        return 3;
    case '+':
        return 3;
    case '>':
        return 2;
    case '=':
        return 1;
    }
    return 0;
}

//отрицание
int fnegation(int x, char oper)
{
    switch (oper)
    {
    case '!':
        return (x == 0) ? 1 : 0;
    }
    return 0;
}

//перевод переменных в цел
int numstl(char ch)
{
    switch (ch)
    {
    case 'x':
        return 0;
    case 'y':
        return 1;
    case 'z':
        return 2;
    case 't':
        return 3;
    }
    return 0;
}

//логичекские операции (кроме отрицания)
int operation(int x, int y, char oper)
{
    switch (oper)
    {
    case '&':
        return (x == 1 && y == 1) ? 1 : 0;
    case 'V':
        return (x == 0 && y == 0) ? 0 : 1;
    case '>':
        return (x == 1 && y == 0) ? 0 : 1;
    case '+':
        return (x == y) ? 0 : 1;
    case '/':
        return (x == 1 && y == 1) ? 0 : 1;
    case '|':
        return (x == 0 && y == 0) ? 1 : 0;
    case '=':
        return (x == y) ? 1 : 0;
    }
    return 0;
}

//алгоритм сортировочной станции (возвращает функцию в постфиксной форме)
string SortStation(string s)
{
    string result = "";

    queue <char> output;
    stack <char> operst;

    int i = 0;
    char ch;
    while (i < s.length())
    {
        ch = s[i];

        if (ch != ' ')
        {
            if (IsCorrect(ch)) 
            {
                output.push(ch);
            }
            else if (IsOperator(ch))
            {
                while (!operst.empty())
                {
                    char ch0 = operst.top();
                    if (IsOperator(ch0) &&
                        ((ch == '!' && (priority(ch) == priority(ch0))) || (ch != '!' && (priority(ch) <= priority(ch0)))))
                    {
                        output.push(ch0);
                        operst.pop();
                    }
                    else
                    {
                        break;
                    }
                }
                operst.push(ch);

            }
            else if (ch == '(')
            {
                operst.push(ch);
            }
            else if (ch == ')')
            {
                bool br = false;
                while (!operst.empty())
                {
                    char ch0 = operst.top();
                    if (ch0 != '(')
                    {
                        output.push(ch0);
                        operst.pop();
                    }
                    else
                    {
                        br = true;
                        break;
                    }
                }

                if (!br)
                {
                    fl = false;
                    throw invalid_argument("Ошибка. Неправильное количество скобок\n");
                }
                else
                {
                    operst.pop(); // удаление (
                }
            }
            else
            {
                fl = false;
                throw invalid_argument("Ошибка. Неверные данные\n");
            }
        }
        i++;
    }

    while (!operst.empty())
    {
        char ch0 = operst.top();

        if (ch0 == '(' || ch0 == ')')
        {
            fl = false;
            throw invalid_argument("Ошибка. Неправильное количество скобок\n");
            break;
        }
        output.push(ch0);
        operst.pop();
    }

    if (output.empty())
    {
        fl = false;
        throw invalid_argument("Ошибка. Функция не содержит переменных\n");
    }

    while (!output.empty())
    {
        result = result + output.front();
        output.pop();
    }

    return result;
}


//нахождения результата лог. выражения
int LogResult(string s, string buf)
{
    int result = 0;
    stack <char> st;

    char ch;
    for (int i = 0; i < s.length(); i++)
    {
        ch = s[i];

        if (IsCorrect(ch))
        {
            st.push(ch);
        }
        else if (IsOperator(ch))
        {
            int res;
            if (ch == '!')
            {
                char ch1 = st.top();
                st.pop();

                int a1;

                if (ch1 == '0')
                    a1 = 0;
                else if (ch1 == '1')
                    a1 = 1;
                else
                    a1 = buf[numstl(ch1)] - '0';

                res = fnegation(a1, ch);
            }
            else
            {
                char ch1 = st.top();
                st.pop();
                char ch2 = st.top();
                st.pop();

                int a1, b1;

                if (ch1 == '0')
                    a1 = 0;
                else if (ch1 == '1')
                    a1 = 1;
                else
                    a1 = buf[numstl(ch1)] - '0';

                if (ch2 == '0')
                    b1 = 0;
                else if (ch2 == '1')
                    b1 = 1;
                else
                    b1 = buf[numstl(ch2)] - '0';

                res = operation(b1, a1, ch);
            }

            char chres = res + '0';
            st.push(chres);
        }
    }

    if (st.size() == 1)
    {
        result = st.top() - '0';
        st.pop();
    }

    return result;
}


int main()
{
    setlocale(LC_ALL, "Rus");
    ifstream fin("input.txt");
    if (!fin.is_open()) {
        cout << "Невозможно открыть текстовый файл для чтения" << endl;
        system("exit");
    }
    ofstream fout("output.txt");

    //создание и заполнение таблицы истинности
    int matrix[16][5];
    string str;
    int num = 16;
    for (int j = 0; j < 4; j++)
    {
        num = num / 2;
        int val = 1;
        for (int i = 0; i < 16; i++)
        {
            if (i % num == 0)
                if (val == 1) val = 0;
                else if (val == 0) val = 1;
            matrix[i][j] = val;
        }
    }

    while (getline(fin, str))
    {
        try
        {
            fout << "_______________________________________________________________________________________" << "\n";
            fout << "Функция: " << str << endl;
            string postfix = SortStation(str);

            if (fl)
            {
                fout << "Постфиксная запись: " << postfix << endl << endl;
                for (int i = 0; i < 16; i++)
                {
                    string buf = "";
                    for (int j = 0; j < 4; j++)
                    {
                        char ch = matrix[i][j] + 48;
                        buf = buf + ch;
                    }
                    matrix[i][4] = LogResult(postfix, buf);
                }

                fout << "x y z t F" << endl;
                for (int i = 0; i < 16; i++)
                {
                    for (int j = 0; j < 5; j++)
                        fout << matrix[i][j] << " ";
                    fout << endl;
                }
            }
            fout << endl;
            fl = true;
        }
        catch (invalid_argument exception)
        {
            fout << exception.what() << endl;
            fl = true;
        }
    }
}
