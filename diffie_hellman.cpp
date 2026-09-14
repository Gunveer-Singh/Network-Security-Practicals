#include <iostream>
using namespace std;

// Function to calculate (base^exp) % mod
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
    long long publicA, publicB;
    long long keyA, keyB;

    // Publicly known values
    cout << "Enter prime number (p): ";
    cin >> p;

    cout << "Enter primitive root (g): ";
    cin >> g;

    // Private keys
    cout << "Enter private key of Alice: ";
    cin >> privateA;

    cout << "Enter private key of Bob: ";
    cin >> privateB;

    // Generate public keys
    publicA = powerMod(g, privateA, p);
    publicB = powerMod(g, privateB, p);

    // Generate shared secret key
    keyA = powerMod(publicB, privateA, p);
    keyB = powerMod(publicA, privateB, p);

    cout << "\nAlice's public key: " << publicA << endl;
    cout << "Bob's public key: " << publicB << endl;

    cout << "\nShared key calculated by Alice: " << keyA << endl;
    cout << "Shared key calculated by Bob: " << keyB << endl;

    if (keyA == keyB)
        cout << "\nKey exchange successful!" << endl;
    else
        cout << "\nKey exchange failed!" << endl;

    return 0;
}