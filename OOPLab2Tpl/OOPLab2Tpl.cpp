#include <iostream>

using namespace std;

void MenuTask()
{
    cout << "    Menu Task\n";
    cout << "    1.  Calculation of expressions using bitwise operations\n";
    cout << "    2.  Data encryption using bitwise operations\n";
    cout << "    3.  Exit\n";
}

/*
Обчислення виразів з використанням побітових операцій.
Задано цілі числа a, b, c та d. Обчислити вираз без використання операцій множення та ділення
(замінивши їх операціями зсувів).
Вираз: 2049 * b + ((d * 15 + 12 * a) / 2048) - c * 100 + d * 104
*/
void Task1()
{
    int a, b, c, d, x, y, z;

    cout << "An example of calculating an expression using only bitwise operations" << endl;
    cout << "Expression: x = 2049 * b + ((d * 15 + 12 * a) / 2048) - c * 100 + d * 104" << endl;
    cout << "Input a, b, c, d ";

    cin >> a >> b >> c >> d;

    // Check input state
    auto st = cin.rdstate();
    if (st != cin.goodbit)
    {
        cin.clear();
        cout << "Error: invalid input.\n";
        cin.get();
        cin.get();
        return;
    }

    // Calcucalte expression
    x = 2049 * b + ((d * 15 + 12 * a) / 2048) - c * 100 + d * 104;                                                                                // Check with simple multiplication and division
    y = (2048 * b + b) + (((d * 16 - d) + (8 * a) + (4 * a)) / 2048) - ((128 * c) - (32 * c) + (4 * c)) + ((128 * d) - (16 * d) - (8 * d));       // Checking with multiplications and divisions by 2^n
    z = ((b << 11) + b) + ((((d << 4) - d) + ((a << 3) + (a << 2))) >> 11) - ((c << 6) + (c << 5) + (c << 2)) + ((d << 6) + (d << 5) + (d << 3)); // Checking with bitwise operations

    cout << "x " << x << "\ny " << y << "\nz " << z << "\na " << a << "\nb " << b << "\nc " << c << "\nd " << d << endl;
}

int main()
{
    MenuTask();

    int choice;

    do
    {
        cout << "Choice ";
        cin >> choice;

        switch (choice)
        {
        case 1: // Task 1
        {
            Task1();
            choice = 3;
            break;
        }
        case 2: // Task 2
        {
            choice = 3;
            break;
        }
        case 3: // Exit
            break;
        default:
            cout << "Invalid choice\n";
            break;
        }
    } while (choice != 3);

    return 0;
}
