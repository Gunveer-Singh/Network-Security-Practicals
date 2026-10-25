#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

// -------------------- Caesar Cipher --------------------
string caesarEncrypt(string text)
{
    for (int i = 0; i < (int)text.length(); i++)
    {
        unsigned char ch = static_cast<unsigned char>(text[i]);
        if (isupper(ch))
            text[i] = 'A' + (text[i] - 'A' + 3) % 26;
        else if (islower(ch))
            text[i] = 'a' + (text[i] - 'a' + 3) % 26;
    }
    return text;
}

string caesarDecrypt(string text)
{
    for (int i = 0; i < (int)text.length(); i++)
    {
        unsigned char ch = static_cast<unsigned char>(text[i]);
        if (isupper(ch))
            text[i] = 'A' + (text[i] - 'A' - 3 + 26) % 26;
        else if (islower(ch))
            text[i] = 'a' + (text[i] - 'a' - 3 + 26) % 26;
    }
    return text;
}

void runCaesarCipher()
{
    int action;
    string text;
    cout << "\n1. Encryption\n2. Decryption\nEnter action: ";
    cin >> action;
    if (action == 1 || action == 2)
    {
        cout << (action == 1 ? "Enter Plain Text: " : "Enter Cipher Text: ");
        getline(cin >> ws, text);
        cout << (action == 1 ? "Ciphertext => " : "Plaintext => ")
             << (action == 1 ? caesarEncrypt(text) : caesarDecrypt(text)) << endl;
    }
    else cout << "Invalid choice!\n";
}

// -------------------- Modified Caesar Cipher --------------------
string modifiedCaesarEncrypt(string text, int key)
{
    key = ((key % 26) + 26) % 26;
    for (int i = 0; i < (int)text.length(); i++)
    {
        unsigned char ch = static_cast<unsigned char>(text[i]);
        if (isupper(ch)) text[i] = 'A' + (text[i] - 'A' + key) % 26;
        else if (islower(ch)) text[i] = 'a' + (text[i] - 'a' + key) % 26;
    }
    return text;
}

string modifiedCaesarDecrypt(string text, int key)
{
    key = ((key % 26) + 26) % 26;
    for (int i = 0; i < (int)text.length(); i++)
    {
        unsigned char ch = static_cast<unsigned char>(text[i]);
        if (isupper(ch)) text[i] = 'A' + (text[i] - 'A' - key + 26) % 26;
        else if (islower(ch)) text[i] = 'a' + (text[i] - 'a' - key + 26) % 26;
    }
    return text;
}

void runModifiedCaesarCipher()
{
    int action, key;
    string text;
    cout << "\n1. Encryption\n2. Decryption\nEnter action: ";
    cin >> action;
    if (action != 1 && action != 2) { cout << "Invalid choice!\n"; return; }
    cout << (action == 1 ? "Enter Plain Text: " : "Enter Cipher Text: ");
    getline(cin >> ws, text);
    cout << "Enter Key: ";
    cin >> key;
    cout << (action == 1 ? "Ciphertext => " : "Plaintext => ")
         << (action == 1 ? modifiedCaesarEncrypt(text, key) : modifiedCaesarDecrypt(text, key)) << endl;
}

// -------------------- Rail Fence Cipher (as in the submitted program) --------------------
string railFenceEncrypt(string input, int rails)
{
    vector<string> rail(rails);
    for (int i = 0; i < (int)input.length(); i++) rail[i % rails] += input[i];
    string output;
    for (int i = 0; i < rails; i++) output += rail[i];
    return output;
}

string railFenceDecrypt(string input, int rails)
{
    int len = (int)input.length();
    vector<string> rail(rails);
    for (int i = 0; i < len; i++) rail[i % rails] += ' ';
    int index = 0;
    for (int i = 0; i < rails; i++)
        for (int j = 0; j < (int)rail[i].length(); j++) rail[i][j] = input[index++];
    string output;
    vector<int> position(rails, 0);
    for (int i = 0; i < len; i++)
    {
        int r = i % rails;
        output += rail[r][position[r]];
        position[r]++;
    }
    return output;
}

void runRailFence()
{
    int action, rails;
    string text;
    cout << "\n1. Encryption\n2. Decryption\nEnter action: ";
    cin >> action;
    if (action != 1 && action != 2) { cout << "Invalid choice!\n"; return; }
    cout << "Enter number of rails: ";
    cin >> rails;
    if (rails <= 0) { cout << "Number of rails must be positive.\n"; return; }
    cout << (action == 1 ? "Enter plaintext: " : "Enter ciphertext: ");
    getline(cin >> ws, text);
    cout << (action == 1 ? "Ciphertext: " : "Plaintext: ")
         << (action == 1 ? railFenceEncrypt(text, rails) : railFenceDecrypt(text, rails)) << endl;
}

// -------------------- Diffie-Hellman Key Exchange --------------------
long long dhPowerMod(long long base, long long exp, long long mod)
{
    long long result = 1;
    while (exp > 0) { result = (result * base) % mod; exp--; }
    return result;
}

void runDiffieHellman()
{
    long long p, g, privateA, privateB, x, y, K1, K2;
    cout << "Enter prime number (p): "; cin >> p;
    cout << "Enter primitive root (g): "; cin >> g;
    cout << "Enter big number of Alice (X): "; cin >> privateA;
    cout << "Enter big number of Bob (Y): "; cin >> privateB;
    if (p <= 1 || g < 1 || privateA < 0 || privateB < 0)
    { cout << "Please enter valid positive values.\n"; return; }
    x = dhPowerMod(g, privateA, p);
    y = dhPowerMod(g, privateB, p);
    K1 = dhPowerMod(y, privateA, p);
    K2 = dhPowerMod(x, privateB, p);
    cout << "\nPublic value of Alice: " << x << endl;
    cout << "Public value of Bob: " << y << endl;
    cout << "Secret key calculated by Alice (K1): " << K1 << endl;
    cout << "Secret key calculated by Bob (K2): " << K2 << endl;
    if (K1 == K2) cout << "\nKey exchange successful!\n";
    else cout << "\nKey exchange failed!\n";
}

// -------------------- RSA Algorithm --------------------
long long rsaPowerMod(long long base, long long exp, long long mod)
{
    long long result = 1;
    while (exp > 0) { result = (result * base) % mod; exp--; }
    return result;
}

long long rsaGcd(long long a, long long b)
{
    while (b != 0) { long long temp = b; b = a % b; a = temp; }
    return a;
}

long long rsaModInverse(long long e, long long phi)
{
    for (long long d = 1; d < phi; d++)
        if ((e * d) % phi == 1) return d;
    return -1;
}

void runRSA()
{
    long long p, q, n, phi, e, d, message, encrypted, decrypted;
    cout << "Enter the value of p: "; cin >> p;
    cout << "Enter the value of q: "; cin >> q;
    if (p <= 1 || q <= 1) { cout << "p and q must be greater than 1.\n"; return; }
    n = p * q;
    phi = (p - 1) * (q - 1);
    e = 2;
    while (e < phi && rsaGcd(e, phi) != 1) e++;
    if (e >= phi) { cout << "Unable to find a valid public key.\n"; return; }
    d = rsaModInverse(e, phi);
    if (d == -1) { cout << "Unable to find the private key.\n"; return; }
    cout << "Public Key: " << e << endl;
    cout << "Private Key: " << d << endl;
    cout << "-----------------------------------\n";
    cout << "Enter message (integer smaller than n=" << n << "): ";
    cin >> message;
    if (message < 0 || message >= n) { cout << "Message must be between 0 and n-1.\n"; return; }
    encrypted = rsaPowerMod(message, e, n);
    decrypted = rsaPowerMod(encrypted, d, n);
    cout << "Encrypted message: " << encrypted << endl;
    cout << "Decrypted message: " << decrypted << endl;
}

// -------------------- Master Menu --------------------
int main()
{
    int choice;
    do
    {
        cout << "\n========== NETWORK SECURITY PRACTICALS ==========\n";
        cout << "1. Caesar Cipher\n";
        cout << "2. Modified Caesar Cipher\n";
        cout << "3. Rail Fence Cipher\n";
        cout << "4. Diffie-Hellman Key Exchange\n";
        cout << "5. RSA Algorithm\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice)) { cout << "Invalid input. Exiting.\n"; break; }

        switch (choice)
        {
            case 1: runCaesarCipher(); break;
            case 2: runModifiedCaesarCipher(); break;
            case 3: runRailFence(); break;
            case 4: runDiffieHellman(); break;
            case 5: runRSA(); break;
            case 0: cout << "Exiting Network Security Practicals.\n"; break;
            default: cout << "Invalid choice! Please select 0-5.\n";
        }
    } while (choice != 0);
    return 0;
}
