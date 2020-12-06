#include <iostream>
#include <Windows.h>
#include <string>
#include <iomanip>

using namespace std;

#pragma pack(push, 1)

enum Speciality { ITIS, RE, KN, KI, PZ };

string speciality_str[] = { "Інформатика ",
                            "Радіоелектроніка", "Комп'ютерні науки",
                            "Комп'ютерна інженерія", "Програмне забезпечення" };

struct Students
{
    string surname;
    int course;
    Speciality speciality;
    int grade_physics;
    int grade_math;
    int grade_pedagogy;
    union
    {
        int grade_programming;
        int grade_numerical_methods;
    };
};

#pragma pack(pop)

void Create(Students* S, const int N);
void Print_first(Students* S, const int N);
void Phys_Sort(Students* S, const int N);
int* Index_sort(Students* S, const int N);
void Print_Index_Sorted(Students* S, int* I, const int N);
bool Bin_Search(Students* S, const int N, const string surname, const int speciality, const int third_grade);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів: "; cin >> N;

    Students* S = new Students[N];

    string B_surname;
    int B_speciality;
    int B_third_grade;

    int MenuItem;
    do
    {
        cout << endl << endl << endl;
        cout << "Оберіть дію:" << endl;
        cout << "1 - Ввести інформацію про студентів" << endl;
        cout << "2 - Вивести інформацію про студентів" << endl;
        cout << "3 - Фізично впорядкувати інформацію" << endl;
        cout << "4 - Індексно впорядкувати інформацію" << endl;
        cout << "5 - Пошук студента"; cout << endl;
        cout << "0 - Завершити роботу програми" << endl;
        cout << "Введіть: "; cin >> MenuItem; cout << endl;
        switch (MenuItem)
        {
        case 1:
            Create(S, N);
            break;
        case 2:
            Print_first(S, N);
            break;
        case 3:
            Phys_Sort(S, N);
            Print_first(S, N);
            break;
        case 4:
            Print_Index_Sorted(S, Index_sort(S, N), N);
            break;
        case 5:
            cout << "Введіть критерії пошуку: " << endl;
            cout << "Прізвище: ";
            cin.get();
            cin.sync();
            getline(cin, B_surname); cout << endl;
            do
            {
                cout << "Спеціальність(0 - Інформатика, 1 - Радіоелектроніка, 2 - Комп'ютерні науки,";
                cout << "\n3 - Комп'ютерна інженерія, 4 - Програмне забезпечення): "; cout << endl;
                cout << "Спеціальність: "; cin >> B_speciality;
            } while (B_speciality < 0 || B_speciality > 4);
            do
            {
                cout << "Оцінка з третього предмету: "; cin >> B_third_grade; cout << endl;
            } while (B_third_grade < 0 || B_third_grade > 5);
            if (Bin_Search(S, N, B_surname, B_speciality, B_third_grade) == 1)
                cout << "Так, такий студень є!" << endl;
            else
                cout << "Не знайдено такого студента!" << endl;
            break;
        case 0:
            return 0;
        default:
            cout << "Ви ввели недопустиме значення!" << endl;
        }
    } while (MenuItem != 0);
    return 0;
}
void Create(Students* S, const int N)
{
    int speciality;
    for (int i = 0; i < N; i++)
    {
        cout << "Номер студента: " << i + 1 << endl;
        cin.get();
        cin.sync();
        cout << "Прізвище: "; getline(cin, S[i].surname); cout << endl;
        do
        {
            cout << "Курс: "; cin >> S[i].course; cout << endl;
        } while (S[i].course < 1 || S[i].course > 6);
        do
        {
            cout << "Спеціальність(0 - Інформатика, 1 - Радіоелектроніка, 2 - Комп'ютерні науки,";
            cout << "\n3 - Комп'ютерна інженерія, 4 - Програмне забезпечення): ";
            cin >> speciality;
            S[i].speciality = (Speciality)speciality;
        } while (speciality < 0 || speciality > 4);
        do
        {
            cout << "Оцінка з фізики: "; cin >> S[i].grade_physics;
        } while (S[i].grade_physics < 0 || S[i].grade_physics > 5);
        do
        {
            cout << "Оцінка з математики: "; cin >> S[i].grade_math;
        } while (S[i].grade_math < 0 || S[i].grade_math > 5);

        switch (S[i].speciality)
        {
        case KN:
            do
            {
                cout << "Оцінка з програмування: "; cin >> S[i].grade_programming;
            } while (S[i].grade_programming < 0 || S[i].grade_programming > 5);
            break;
        case ITIS:
            do
            {
                cout << "Оцінка з чисельних методів: "; cin >> S[i].grade_numerical_methods;
            } while (S[i].grade_numerical_methods < 0 || S[i].grade_numerical_methods > 5);
            break;
        default:
            do
            {
                cout << "Оцінка з педагогіки: "; cin >> S[i].grade_pedagogy;
            } while (S[i].grade_pedagogy < 0 || S[i].grade_pedagogy > 5);
        }
        cout << endl;
    }
}
void Print_first(Students* S, const int N)
{
    cout << "==============================================================================================================================" << endl;
    cout << "|  №  |  Прізвище  |  Курс  |  Спеціальність  |  Фізика  |  Математика  |  Програмування  |";
    cout << "  Чисельні методи  |  Педагогіка  |" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "|" << setw(3) << i + 1 << setw(3);
        cout << "|" << setw(3) << S[i].surname << setw(3);
        cout << "|" << setw(4) << S[i].course << setw(4);
        cout << "|" << setw(3) << speciality_str[S[i].speciality] << setw(3);
        cout << "|" << setw(5) << S[i].grade_physics << setw(5);
        cout << "|" << setw(7) << S[i].grade_math << setw(7);
        switch (S[i].speciality)
        {
        case KN:
            cout << "|" << setw(7) << S[i].grade_programming << setw(7);
            cout << "|" << setw(7) << "-" << setw(7);
            cout << "|" << setw(7) << "-" << setw(7) << "|";
            break;
        case ITIS:
            cout << "|" << setw(8) << "-" << setw(8);
            cout << "|" << setw(8) << S[i].grade_numerical_methods << setw(8);
            cout << "|" << setw(8) << "-" << setw(8) << "|";
            break;
        default:
            cout << "|" << setw(7) << "-" << setw(7);
            cout << "|" << setw(8) << "-" << setw(8);
            cout << "|" << setw(7) << S[i].grade_pedagogy << setw(7) << "|";
        }
        cout << endl;
    }
    cout << "=============================================================================================================================" << endl;
}
void Phys_Sort(Students* S, const int N)
{
    Students temp;
    int check, check_next;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
        {
            switch (S[i1].speciality)
            {
            case KN:
                check = S[i1].grade_programming;
                check_next = S[i1 + 1].grade_programming;
                break;
            case ITIS:
                check = S[i1].grade_numerical_methods;
                check_next = S[i1 + 1].grade_numerical_methods;
                break;
            default:
                check = S[i1].grade_pedagogy;
                check_next = S[i1 + 1].grade_pedagogy;
            }
            if ((S[i1].speciality == S[i1 + 1].speciality)
                &&
                (check > check_next)
                ||
                ((S[i1].grade_programming + S[i1 + 1].grade_programming) / N)
                    &&
                    (check > check_next)
                ||
                ((S[i1].speciality == S[i1 + 1].speciality)
                    &&
                    (check == check_next)
                    &&
                    (S[i1].surname > S[i1 + 1].surname)))
            {
                temp = S[i1];
                S[i1] = S[i1 + 1];
                S[i1 + 1] = temp;
            }
        }
}
int* Index_sort(Students* S, const int N)
{
    int* I = new int[N];

    for (int i = 0; i < N; i++)
        I[i] = i;

    int i, j, value;
    int check_index, check_value;
    for (i = 1; i < N; i++)
    {
        value = I[i];
        switch (S[I[i]].speciality)
        {
        case KN:
            check_index = S[I[i]].grade_programming;
            check_value = S[value].grade_programming;
            break;
        case ITIS:
            check_index = S[I[i]].grade_numerical_methods;
            check_value = S[value].grade_numerical_methods;
            break;
        default:
            check_index = S[I[i]].grade_pedagogy;
            check_value = S[value].grade_pedagogy;
        }
        for (j = i - 1;
            j > 0 && ((S[I[j]].speciality == S[value].speciality)
                &&
                (check_index == check_value)
                ||
                ((S[I[j]].grade_programming + S[value].grade_programming) / N)
                &&
                (check_index == check_value)
                ||
                ((S[I[j]].speciality == S[value].speciality)
                    &&
                    (check_index == check_value)
                    &&
                    (S[I[j]].surname > S[value].surname)));
        j--)
        {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }
    return I;
}
void Print_Index_Sorted(Students* S, int* I, const int N)
{
    cout << "==============================================================================================================================" << endl;
    cout << "|  №  |  Прізвище  |  Курс  |  Спеціальність  |  Фізика  |  Математика  |  Програмування  |";
    cout << "  Чисельні методи  |  Педагогіка  |" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "|" << setw(3) << i + 1 << setw(3);
        cout << "|" << setw(4) << S[I[i]].surname << setw(4);
        cout << "|" << setw(6) << S[I[i]].course << setw(6);
        cout << "|" << setw(6) << speciality_str[S[I[i]].speciality] << setw(6);
        cout << "|" << setw(6) << S[I[i]].grade_physics << setw(6);
        cout << "|" << setw(6) << S[I[i]].grade_math << setw(6);
        switch (S[i].speciality)
        {
        case KN:
            cout << "|" << setw(6) << S[I[i]].grade_programming << setw(6);
            cout << "|" << setw(6) << "-" << setw(6);
            cout << "|" << setw(6) << "-" << setw(6) << "|" << endl;
            break;
        case ITIS:
            cout << "|" << setw(6) << "-" << setw(6);
            cout << "|" << setw(6) << S[I[i]].grade_numerical_methods << setw(6);
            cout << "|" << setw(6) << "-" << setw(6) << "|" << endl;
            break;
        default:
            cout << "|" << setw(6) << "-" << setw(6);
            cout << "|" << setw(6) << "-" << setw(6);
            cout << "|" << setw(6) << S[I[i]].grade_pedagogy << setw(6) << "|" << endl;
        }
    }
    cout << "==============================================================================================================================" << endl << endl;
}
bool Bin_Search(Students* S, const int N, const string surname, const int speciality, const int third_grade)
{
    int L = 0, R = N - 1, m, check;
    do
    {
        m = (L + R) / 2;

        switch (S[m].speciality)
        {
        case KN:
            check = S[m].grade_programming;
            break;
        case ITIS:
            check = S[m].grade_numerical_methods;
            break;
        default:
            check = S[m].grade_pedagogy;
        }

        if ((S[m].surname == surname
            &&
            S[m].speciality == speciality)
            &&
            (check == third_grade))
        {
            return 1;
        }

        if ((check < third_grade)
            ||
            (check == third_grade
                &&
                S[m].speciality < speciality)
            ||
            (check == third_grade
                &&
                S[m].speciality == speciality
                &&
                S[m].surname < surname))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);
    return 0;
}
