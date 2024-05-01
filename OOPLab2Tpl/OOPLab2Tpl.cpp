#include <iostream>
#include <fstream>
#include <cstring>
#include <bitset>

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

// Calculate pbit1
bool ParityBit1(unsigned short input)
{
    unsigned char leastSignificant8Bits = input & 0b11111111;

    bool parity = false;
    while (leastSignificant8Bits)
    {
        parity = !parity;
        leastSignificant8Bits = leastSignificant8Bits & (leastSignificant8Bits - 1);
    }

    return parity;
}

// Calculate pbit2
bool ParityBit2(unsigned short input)
{
    unsigned char leastSignificant8Bits = (input >> 10) & 0b11111;

    bool parity = false;
    while (leastSignificant8Bits)
    {
        parity = !parity;
        leastSignificant8Bits = leastSignificant8Bits & (leastSignificant8Bits - 1);
    }

    return parity;
}

// Encryption
unsigned short EncryptChar(char input, char i, char pos)
{
    unsigned short result;
    char msb, lsb;

    result = i & 0b00001111;

    msb = input & 0b11110000;

    result |= msb;

    result |= ParityBit1(result) << 8;

    lsb = input & 0b00001111;

    result |= lsb << 9;

    result |= pos << 13;

    result |= ParityBit2(result) << 15;

    return result;
}

// Decryption
char DecryptChar(unsigned short input)
{
    unsigned short result;
    unsigned short msb, lsb;

    lsb = input & 0b0001111000000000;
    result = lsb >> 9;

    msb = input & 0b0000000011110000;
    result |= msb;

    return result & 0b11111111;
}

/*
Задано текст, який складається з 16 рядків до 4 символів у рядку.
Доповнити пробілами рядки до 16 символів.
Шифрувати тексти таким чином, щоб кожний символ тексту записувався у два байти.
Два байти мають таку структуру:
- у бітах 0-3 знаходиться номер рядка символу (4 біти) - НРС,
- у бітах 4-7 старша частина ASCII - коду символу (4 біти) - СЧКС,
- 8 біт – біт парності перших двох полів (1 біт) - БП,
- у бітах 9-12 молодша частина ASCII - коду символу (4 біти) - МЧКС,
- у бітах 13-14 позиція символу в рядку (2 біти) - ПСР,
- 15 біт - біт парності попередніх двох полів (1 біт) - БП.
 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
|БП||ПСР| |  МЧКС   ||БП||  СЧКС   | |   НРС   |
*/
void Task2()
{
    char input[16][5];
    unsigned short encrypted[16][4];
    char decrypted[16][4];

    // Console input
    cout << "Input 16x4 array" << endl;
    for (int i = 0; i < 16; i++)
    {
        cin.getline(input[i], 5);
        int n = strlen(input[i]);
        for (int j = n; j < 4; j++)
        {
            input[i][j] = ' ';
        }
    }

    // Open text file
    ofstream ofs("in.txt");
    if (!ofs)
    {
        cout << "File not open" << endl;
        return;
    }

    // Write to text file
    for (int i = 0; i < 16; i++)
    {
        ofs << input[i];
    }
    ofs.close();

    // Encrypt and decrypt
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            encrypted[i][j] = EncryptChar(input[i][j], i, j);
            decrypted[i][j] = DecryptChar(encrypted[i][j]);
        }
    }

    // Display encrypted array
    cout << "\nEncrypted (bit)" << endl;
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << bitset<16>(encrypted[i][j]) << " ";
        }
        cout << endl;
    }

    cout << "\nEncrypted (unsigned short)";
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << static_cast<unsigned char>(encrypted[i][j]);
        }
        cout << endl;
    }

    // Display decrypted array
    cout << "\nDecrypted";
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << decrypted[i][j];
        }
        cout << endl;
    }

    // Write to binary file
    ofstream ofs_bin("outb.bin", ios::binary);
    if (!ofs_bin)
    {
        cout << "File not open" << endl;
        return;
    }
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ofs_bin.write(reinterpret_cast<char *>(&encrypted[i][j]), sizeof(encrypted[i][j]));
        }
    }
    ofs_bin.close();

    return;
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
            Task2();
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
