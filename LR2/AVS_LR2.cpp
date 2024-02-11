#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool checkCorrect(string number) {
    bool IsCorrect = true;
    bool IsPoint = false;
    int i;
    if (number[0] == '-') i = 1;
    else i = 0;
    for (i; (i < int(number.length())) && IsCorrect; i++) {
        if (number[i] < '0' || number[i] > '9') {
            if (number[i] != ',') IsCorrect = false;
            else if (!IsPoint) IsPoint = true;
            else if (IsPoint) IsCorrect = false;
        }
    }
    return IsCorrect;
}
// Добавление нулей в начало числа, который короче
void AddToTop(string& num1, string& num2) {
    int c1 = num1.length();
    int c2 = num2.length();
    if (c1 > c2)  {
        if (num2[0] == '-')
            while (c1 != c2) {
                num2[0] = '0';
                num2 = "-" + num2;
                c2++;
            }
        else 
            while (c1 != c2) {
            num2 = "0" + num2;
            c2++;
            }
        }
    else
        if (num1[0] == '-')
            while (c1 != c2) {
                num1[0] = '0';
                num1 = "-" + num1;
                c1++;
            }
        else
            while (c1 != c2) {
                num1 = "0" + num1;
                c1++;
            }
}
// Добавление нулей конец числа, который короче
void AddToEnd(string& num1, string& num2){
    if (num1.length() > num2.length())
        while (num1.length() != num2.length())
            num2 += "0";
    else
        while (num1.length() != num2.length())
            num1 += "0";
}
string MOK(string sign, string s)
{
    if (sign == "11") {
        string MOKnum;
        //MOKnum += "11:";
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '0')
                MOKnum += '1';
            if (s[i] == '1')
                MOKnum += '0';
        }
        return MOKnum;
    }
    else return s;
        //return ("00:" + s);
}
// суммирование двух чисел
string summation(string num1, string num2) {
    string res = num1;
    int digit = 0;
    int div = 0;
    int mod = 0;
    for (int i = num1.length() - 1; i >= 0; i--) {
        digit = int(num1[i]) + int(num2[i]) + div -96;
        mod = digit % 2;
        div = digit / 2;
        if (mod == 0) res[i] = '0';
        else res[i] = '1';
    }
    if (div != 0) {
        res = "1" + res;
    }
    return res;
}
// срез строки от begin до end
string slice(string str, int begin, int end) {
    string newstr;
    for (int i = begin; i < end; i++)
        newstr += str[i];
    return newstr;
}
// Суммирует целые числа
string sumInt(string sign1, string Int1, string sign2, string Int2) {

    string signRes = summation(sign1, sign2);
    string intMok1 = MOK(sign1, Int1);
    string intMok2 = MOK(sign2, Int2);
    string resIntMok = summation(intMok1, intMok2);
    //cout << '%' << signRes << ' ' << resIntMok << ' ';
    if (((signRes == "11") || (signRes == "110")) && (resIntMok.length() != intMok1.length())) {
        // прибавить к числу 1
        string one = "1";
        AddToTop(resIntMok, one);
        resIntMok = summation(resIntMok, one);
        // убрать первую цифру числа
        resIntMok = slice(resIntMok, 1, resIntMok.length());
        // обновить знак
        if (signRes == "11") signRes = "00";
        else signRes = "11";
    }
    else if ((signRes == "110")) {
        resIntMok = '0' + resIntMok;
        // прибавить к числу 1
        string one = "1";
        AddToTop(resIntMok, one);
        resIntMok = summation(resIntMok, one);
        if (resIntMok[0] == '1') resIntMok = slice(resIntMok, 1, resIntMok.length());
        signRes = "11";
    }
    return signRes + MOK(signRes, resIntMok);
}
// разделение результата суммирования на знак и число
void divide(string& signRes, string& res) {
    signRes = res[0];
    signRes += res[1];
    string newstr="";
    for (int i = 2; i < res.length(); i++) 
        newstr += res[i];
    res = newstr;
}
// Вставка el на место n в cтроке str
string insert(string str, int n, char el) {
    string res;
    for (int i = 0; i < n; i++)
        res += str[i];
    res += el;
    for (int i = n; i < str.length(); i++)
        res += str[i];
    return res;
}
// получить целую часть числа
string SelectInt(string num) {
    string res;
    int i = 0;
    if (num[0] == '-') i++;
    for (i; (num[i] != ',') && (num[i] != '.') && i < int(num.length()); i++)
        res += num[i];
    return res;
}
int CountInt(string num) {
    int res = 0;
    int i = 0;
    if (num[0] == '-') i++;
    for (i; (num[i] != ',') && (num[i] != '.') && i < int(num.length()); i++)
        res++;
    return res;
}
// получить дрробную часть числа
string SelectFract(string num) {
    int cInt = CountInt(num);
    string res;
    int i = cInt + 1;
    if (num[0] == '-') i++;
    //cout << num << ' ' << i << ' ' << cInt << endl;
    for (i; i < int(num.length()); i++)
        res += num[i];
    return res;
}

string Sum(string num1, string num2) {
    // Разделим числа num1 и num2 на целую и дробную части
    string Int1 = SelectInt(num1);
    string Int2 = SelectInt(num2);
    string Fract1 = SelectFract(num1);
    string Fract2 = SelectFract(num2);

    // Сравняем разряды, добавив незначащие нули
    if (Int1.length() != Int2.length()) AddToTop(Int1, Int2);
    if (Fract1.length() != Fract2.length()) AddToEnd(Fract1, Fract2);

    // Определим код знака
    string sign1;
    if (num1[0] == '-') sign1 = "11";
    else sign1 = "00";
    string sign2;
    if (num2[0] == '-') sign2 = "11";
    else sign2 = "00";
    string signRes = summation(sign1, sign2);

    // Просуммируем целую часть
    string resInt = sumInt(sign1, Int1, sign2, Int2);
    // разделить результат на знак и число
    string signResInt;
    divide(signResInt, resInt);

    // Просуммируем дробную часть
    string resFract = sumInt(sign1, Fract1, sign2, Fract2);
    // разделить результат на знак и число
    string signResFract;
    divide(signResFract, resFract);

    // подготовка к сложению целой и дробной частей
    int n = resInt.length();
    if (resFract.length() != Fract1.length()) n--;
    for (int i = 0; i < n; i++)
        resFract = '0' + resFract;
    if (resInt.length() != resFract.length()) AddToEnd(resInt, resFract);

    // сложить целую и дробную часть
    string res = sumInt(signResInt, resInt, signResFract, resFract);
    // разделить результат на знак и число
    divide(signRes, res);

    // Вставим запятую
    res = insert(res, resInt.length() - Fract1.length(), ',');
    // Добавим знак, если необходим
    if (signRes == "11") res = '-' + res;

    return res;
}

string To2(string s) {

    double res = 0.0;
    int int_cnt = CountInt(s);
    int intPart = atoi(SelectInt(s).c_str());
    int mod = 0;
    for (int i = 0; intPart > 0; i++) {
        mod = intPart % 2;
        intPart /= 2;
        res += (static_cast<unsigned __int64>(mod)) * pow(10, i);
    }
    double fractPart = stod("0,"+SelectFract(s));
    int k;
    for (int i = 0; i < SelectFract(s).length(); i++) {
        k = fractPart * 2;
        res +=  k * pow(10, -(i + 1));
        fractPart *= 2;
        if (fractPart > 1) fractPart--;
    }
    if (s[0] == '-')
        return to_string((-1)*res);
    else return to_string(res);
}

double To10(string str){
    double p = 0;
    int pos = str.find(','); //позициязапятой
    for (int i = str.size() - 1; i >= 0; i--)
    {
        if (str[i] != ',')
        {
            int k = 0;
            if (str[i] == '1')
                k = 1;
            if (i > pos)
            {
                p += k * pow(2, pos - i);  // выполняем сложение полинома в 10-ой сс.
            }
            if (i < pos)
                p += k * pow(2, pos - i - 1);
        }
    }
    if (str.find('-') != string::npos)
        p *= -1; // умножаем результат на минус 1, чтобы сделать его отрицатльным, если
                 //изначально был найден минус у числа
    return p;
}

int main()
{
    setlocale(LC_ALL, "Rus");

    ifstream fin;
    fin.open("input.txt");
    if (fin) {
        ofstream fout;
        fout.open("output.txt");
        fout << "Задание: сложение двоичных чисел с фиксированной точкой с использованием МОК." << endl << endl;
        while (!fin.eof())
        {
            string str1, str2;
            fin >> str1 >> str2;
            fout << "Сумма в 10cc:                 " << str1 << " + " << str2 << endl;
            if (checkCorrect(str1) && checkCorrect(str2)) {
                fout << "Ожидаемый результат в 10сс:   " << stod(str1) + atof(str2.c_str()) << endl;
                str1 = To2(str1);
                str2 = To2(str2);
                fout << "Сумма в 2сс:                  " << str1 << " + " << str2 << endl;
                string s = Sum(str1, str2);
                fout << "Фактический результат в 2сс:  " << s << endl;
                fout << "Фактический результат в 10сс: " << To10(s) << endl << endl; 
            }
            else fout << "Некорректные данные!" << endl << endl;
        }
        fin.close();
        fout.close();
    }
    else cout << "Невозможно открыть файл для чтения!" << endl;
}