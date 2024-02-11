#include <iostream>
#include <map>
#include <string>
#include <fstream>
using namespace std;

map<string, string> map2to8 = {
    {"000", "0"},
    {"001", "1"},
    {"010", "2"},
    {"011", "3"},
    {"100", "4"},
    {"101", "5"},
    {"110", "6"},
    {"111", "7"}
};

bool checkCorrect(string number) {
    bool IsCorrect = true;
    bool IsPoint = false;
    for (int i = 0; (i < int(number.length())) && IsCorrect; i++){
        if (((number[i] != '0') && (number[i] != '1'))) {
            if ((number[i] != ',') && (number[i] != '.')) IsCorrect = false;
            else if (!IsPoint) IsPoint = true;
            else if (IsPoint) IsCorrect = false;
        }
    }
    return IsCorrect;
}

string Convert2to8(string number) {
    int countInt = 0;
    for (int i=0; (number[i] != ',') && (number[i] != '.') && i < int(number.length()); i++) {
        countInt++;
    }

    string digit = "";
    string res = "";

    // дополнение целой части до триад
    while (countInt % 3 != 0) {
        number = "0" + number;;
        countInt++;
    }

    // перевод целой части
    for (int i = 1; i <= countInt; i++) {
        digit += number[i - 1];
        if (i % 3 == 0) {
            res += map2to8[digit];
            digit = "";
        }
    }

    // перевод дробной части, если она существует
    if (countInt != number.length()) {
        res += ",";
        digit = "";
        for (int i = countInt + 2; i <= int(number.length()); i++) {
            digit += number[i - 1];
            if ((i - countInt - 1) % 3 == 0) {
                res += map2to8[digit];
                digit = "";
            }
        }
        // дополнение дробной части до триад
        if (digit.length() % 3 != 0) {
            while (digit.length() % 3 != 0) {
                digit += "0";
                number += "0";
            }
            res += map2to8[digit];
        }
    }
    return res;
}

int main()
{
    setlocale(LC_ALL, "Rus");

    ifstream fin;
    fin.open("input.txt");
    if (fin) {
        ofstream fout;
        fout.open("output.txt");
        fout << "Задание: Перевод из 2сс в 8сс." << endl << endl;
        while (!fin.eof())
        {
            string str2;
            fin >> str2;
            fout << "2cc: " << str2 << endl;
            if (checkCorrect(str2))
                fout << "8cc: " << Convert2to8(str2) << endl << endl;
            else fout << "Некорректные данные!" << endl << endl;
        }
        fin.close();
        fout.close();
    }
    else cout << "Невозможно открыть файл для чтения!" << endl;
}