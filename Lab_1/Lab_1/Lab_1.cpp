#include <iostream>

using namespace std;
//Нахождение модуля числа
int mod_aX(int a, int x, int p)
{
    int rez = 0;
    rez = a;
    for (int i = 2; i <= x; i++)
    {
        rez *= a;
        while (rez >= p) { rez -= p; }
    }
    if (x == 1)
    {
        while (rez >= p) { rez -= p; }
    }
    return rez;
}

// Расширенный алгоритм Евклида , понадобится при нахождении обработанного элемента
void extended_euclid(unsigned long a, unsigned long b, long* x, long* y, long* d)
{
    long q, r, x1, x2, y1, y2;
    if (b == 0)
    {
        *d = a, * x = 1, * y = 0;
        return;
    }
    x2 = 1, x1 = 0, y2 = 0, y1 = 1;
    while (b > 0)
    {
        q = a / b, r = a - q * b;
        *x = x2 - q * x1, * y = y2 - q * y1;
        a = b, b = r;
        x2 = x1, x1 = *x, y2 = y1, y1 = *y;
    }
    *d = a, * x = x2, * y = y2;
}

//Поиск обратного элемента по модулю
long inverse(unsigned long a, unsigned long n)
{
    long d, x, y;
    extended_euclid(a, n, &x, &y, &d);
    if (d != 1) { return 0; }
    else
        return x;
}
//Шифр Диффи-Хеллмана
void Diffy_Hellman(long p, long g, long XA, long XB)
{
    int a = 1000, b = 2000;
    long A, B, K;
    A = mod_aX(g, a, p);
    cout << "\n-----------Diffy-Hellman-----------\n";
    cout << "OpenKey A:" << A << endl;
    B = mod_aX(g, b, p);
    cout << "OpenKey B:" << B << endl;
    K = mod_aX(A, b, p);
    cout << "SecretKey A:" << K << endl;
    K = mod_aX(B, a, p);
    cout << "SecretKey B:" << K << endl;
}
//Шифр Шамира
void Shamir(long p = 30803, long d1 = 501, long d2 = 601, long m = 11111)
{
    long C1, C2, C3;
    long e1, e2;
    e1 = inverse(d1, (p - 1));
    e2 = inverse(d2, (p - 1));
    cout << "\n-----------Shamir-----------\n";
    cout << "Start message: " << m << endl;
    C1 = mod_aX(m, e1, p);
    cout << "Encripting by A: " << C1 << endl;
    C2 = mod_aX(C1, e2, p);
    cout << "Encripting by B: " << C2 << endl;
    C3 = mod_aX(C2, d1, p);
    cout << "Decripting by A: " << C3 << endl;
    m = mod_aX(C2, d2, p);
    cout << "Decripting by B(message from A): " << m << endl;
    cout << m << endl;
}
//Шифр Эль-Гамаля
void El_Gamal(long p, long g, long c, long k, long M)
{
    long a, b, y;
    y = mod_aX(g, c, p);
    a = mod_aX(g, k, p);
    b = mod_aX(y, k, p);
    b = mod_aX((b * M), 1, p);
    cout << "\n-----------El-Gamal-----------\n";
    cout << "Sipher (" << a << ";" << b << ")" << endl;
}
//Шифр RSA
void RSA(long p, long q, long d, long m)
{
    long e = inverse(d, p);
    long P = mod_aX(m, e, (p * q));
    cout << "\n-----------RSA-----------\n";
    cout << "Secret key: " << e << "\n";
    cout << "Message: " << P << endl;
}

int main()
{
    //Меню выбора шифра
    int choose = 99;
    while (choose != 0) {
        cout << "\n\nChoose a cipher:\n 1) Diffy - Hellman\n 2)Shamir\n 3)El-Gamal\n 4)RSA\n 0) Exit";
        cin >> choose;
        switch (choose) {
        case 1: Diffy_Hellman(30803, 2, 1000, 2000);
            break;
        case 2: Shamir(30803, 501, 601, 11111);
            break;
        case 3: El_Gamal(30803, 2, 500, 600, 11111);
            break;
        case 4: RSA(131, 227, 3, 11111);
            break;
        case 0: cout << "Exiting...";
            break;
        default: cout << "Wrong number";
        }
    }
}
