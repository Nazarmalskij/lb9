// Lab_9_3.cpp
// <Мальський Назар>
// Лабораторна робота No 9.3.
// Опрацювання масиву структур
// Варіант 17
#include <iostream>
#include <iomanip>
#include <string>
#define TESTING


using namespace std;

#pragma pack(push, 1)

struct Bday
{
    int day;
    int month;
    int year;
};

struct Zodiac
{
    string surname;
    string name;
    string zodiac_sign;
};

#pragma pack(pop)

void Create(Zodiac* S, Bday* B, const int N);
void Print(Zodiac* S, Bday* B, const int N);
void sort(Zodiac* S, Bday* B, const int N);
void search(Zodiac* S, Bday* B, const int N, const string f_surname);

#ifdef TESTING
int main()
{
    int N;
    cout << "Введіть кількість користувачів: "; cin >> N;

    Bday* B = new Bday[3];
    Zodiac* S = new Zodiac[N];

    string f_surname;

    int MenuItem;

    while (true)
    {
        cout << endl << endl << endl;
        cout << "Оберіть дію:" << endl;
        cout << "1 - Ввести інформацію про користувача" << endl;
        cout << "2 - Вивести інформацію про користувачів" << endl;
        cout << "3 - Впорядкувати за датами днів народженнями" << endl;
        cout << "4 - Пошук людини за прізвищем" << endl;
        cout << "0 - Завершити роботу програми" << endl;
        cout << "Введіть: "; cin >> MenuItem; cout << endl;

        switch (MenuItem)
        {
        case 1:
            Create(S, B, N);
            break;
        case 2:
            Print(S, B, N);
            break;
        case 3:
            sort(S, B, N);
            Print(S, B, N);
            break;
        case 4:
            cout << "Введіть критерії пошуку: " << endl;
            cout << "Прізвище" << endl;
            cin.get();
            cin.sync();
            getline(cin, f_surname); cout << endl;
            search(S, B, N, f_surname);
            break;
        }
        if (MenuItem == 0) break;
    }

    return 0;
}
#endif

void Create(Zodiac* S, Bday* B, const int N)
{
    for (int i = 0; i < N; i++)
    {

        int speciality;
        cout << "Номер користувача: " << i + 1 << endl;
        cin.get();
        cin.sync();
        cout << "Прізвище: "; getline(cin, S[i].surname); cout << endl;
        cout << "І'мя: "; getline(cin, S[i].name); cout << endl;
        cout << "Знак зодіка: "; getline(cin, S[i].zodiac_sign); cout << endl;
        do
        {
            cout << "День народження: "; cin >> B[i].day; cout << endl;
        } while (B[i].day < 1 || B[i].day > 31);

        do
        {
            cout << "Місяць народження: "; cin >> B[i].month; cout << endl;
        } while (B[i].month < 1 || B[i].month > 12);

        cout << "Рік народження: "; cin >> B[i].year; cout << endl;

        cout << endl;
    }
}

void Print(Zodiac* S, Bday* B, const int N)
{
    cout << "=========================================================================================" << endl;
    cout << "|  №  |  Прізвище  | І'мя | Знак зодіаку  |  День народження  |  Місяць  |  Рік          |" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "|" << setw(3) << i + 1 << setw(3);
        cout << "|" << setw(4) << S[i].surname << setw(8);
        cout << "|" << setw(6) << S[i].name << setw(3);
        cout << "|" << setw(6) << S[i].zodiac_sign << setw(6);
        cout << "|" << setw(6) << B[i].day << setw(12);
        cout << "|" << setw(6) << B[i].month << setw(6);
        cout << "|" << setw(10) << B[i].year << setw(6) << "|" << endl;
    }
    cout << "=========================================================================================" << endl << endl;
}
void sort(Zodiac* S, Bday* B, int N)
{
    Zodiac temp;
    Bday btemp;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N - i - 1; j++)
        {
            if ((B[j].year > B[j + 1].year)
                ||
                (B[j].year == B[j + 1].year)
                &&
                (B[j].month > B[j + 1].month)
                ||
                (B[j].year == B[j + 1].year)
                &&
                (B[j].month == B[j + 1].month)
                &&
                (B[j].day > B[j + 1].day))
            {
                temp = S[j];
                S[j] = S[j + 1];
                S[j + 1] = temp;

                btemp = B[j];
                B[j] = B[j + 1];
                B[j + 1] = btemp;
            }

        }
    }
}

void search(Zodiac* S, Bday* B, const int N, const string f_surname)
{
    int flag = 0;
    for (int i = 0; i < N; i++) {
        if (S[i].surname == f_surname)
        {
            flag = 1;
            cout << "=========================================================================================" << endl;
            cout << "|  №  |  Прізвище  | І'мя | Знак зодіаку  |  День народження  |  Місяць  |  Рік          |" << endl;
            cout << "-----------------------------------------------------------------------------------------" << endl;
            cout << "|" << setw(3) << i + 1 << setw(3);
            cout << "|" << setw(4) << S[i].surname << setw(8);
            cout << "|" << setw(6) << S[i].name << setw(3);
            cout << "|" << setw(6) << S[i].zodiac_sign << setw(6);
            cout << "|" << setw(6) << B[i].day << setw(12);
            cout << "|" << setw(6) << B[i].month << setw(6);
            cout << "|" << setw(10) << B[i].year << setw(6) << "|" << endl;
            cout << "=========================================================================================" << endl << endl;
        }
    }
    if (!flag)
        cout << "Користувач не найдений" << endl;
}