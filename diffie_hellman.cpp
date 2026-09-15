#include <iostream>
using namespace std;


long long powerMod(long long base, long long exp, long long mod)
{
    long long result = 1;

    while (exp > 0)
    {
        result = (result * base) % mod;
        exp--;
    }

    return result;
}

int main()
{
    long long p, g;
    long long privateA, privateB;
    long long x, y;
    long long K1, K2;


    cout << "Enter prime number (p): ";
    cin >> p;

    cout << "Enter primitive root (g): ";
    cin >> g;


    cout << "Enter big number of Alice (X): ";
    cin >> privateA;

    cout << "Enter big number of Bob (Y): ";
    cin >> privateB;


    x = powerMod(g, privateA, p);
    y = powerMod(g, privateB, p);


    K1 = powerMod(y, privateA, p);
    K2 = powerMod(x, privateB, p);


    cout << "\nSecret key calculated by Alice (K1): " << K1 << endl;
    cout << "Secret key calculated by Bob (K2): " << K2 << endl;

    if (K1 == K2)
        cout << "\nKey exchange successful!" << endl;
    else
        cout << "\nKey exchange failed!" << endl;

    return 0;
}