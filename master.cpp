#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdint>
#include <iomanip>
#include <sstream>
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


uint32_t md5K[64] = {
    0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,
    0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,
    0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,
    0x6b901122,0xfd987193,0xa679438e,0x49b40821,
    0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,
    0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
    0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,
    0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a,
    0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,
    0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,
    0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,
    0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,
    0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,
    0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,
    0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,
    0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391
};

int md5S[64] = {
    7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,
    5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
    4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,
    6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21
};

uint32_t leftRotate(uint32_t x, int n) {
    return (x << n) | (x >> (32 - n));
}

string md5Hash(string input) {
    vector<uint8_t> msg(input.begin(), input.end());
    uint64_t bitLength = (uint64_t)msg.size() * 8;

    // Step 1: Padding
    msg.push_back(0x80);

    while (msg.size() % 64 != 56)
        msg.push_back(0);

    // Append original length in little-endian
    for (int i = 0; i < 8; i++)
        msg.push_back((bitLength >> (8 * i)) & 0xff);

    // Step 2: Initialize MD5 buffers
    uint32_t a0 = 0x67452301;
    uint32_t b0 = 0xefcdab89;
    uint32_t c0 = 0x98badcfe;
    uint32_t d0 = 0x10325476;

    // Step 3: Process each 512-bit block
    for (size_t offset = 0; offset < msg.size(); offset += 64) {
        uint32_t M[16];

        for (int i = 0; i < 16; i++) {
            size_t j = offset + i * 4;
            M[i] = (uint32_t)msg[j]
                 | ((uint32_t)msg[j + 1] << 8)
                 | ((uint32_t)msg[j + 2] << 16)
                 | ((uint32_t)msg[j + 3] << 24);
        }

        uint32_t A = a0, B = b0, C = c0, D = d0;

        // Step 4: Perform 64 MD5 operations
        for (int i = 0; i < 64; i++) {
            uint32_t F;
            int g;

            if (i < 16) {
                F = (B & C) | (~B & D);
                g = i;
            }
            else if (i < 32) {
                F = (D & B) | (~D & C);
                g = (5 * i + 1) % 16;
            }
            else if (i < 48) {
                F = B ^ C ^ D;
                g = (3 * i + 5) % 16;
            }
            else {
                F = C ^ (B | ~D);
                g = (7 * i) % 16;
            }

            uint32_t temp = D;
            D = C;
            C = B;
            B = B + leftRotate(
                A + F + md5K[i] + M[g], md5S[i]
            );
            A = temp;
        }

        a0 += A;
        b0 += B;
        c0 += C;
        d0 += D;
    }

    // Step 5: Convert result to hexadecimal
    uint32_t H[4] = {a0, b0, c0, d0};
    stringstream result;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result << hex << setfill('0') << setw(2)
                   << ((H[i] >> (8 * j)) & 0xff);
        }
    }

    return result.str();
}


// -------------------- MD5 Hashing --------------------
void runMD5()
{
    string input;
    cout << "Enter a string: ";
    getline(cin >> ws, input);
    cout << "MD5 Hash Value: " << md5Hash(input) << endl;
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
        cout << "6. MD5 Hashing\n";
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
            case 6: runMD5(); break;
            case 0: cout << "Exiting Network Security Practicals.\n"; break;
            default: cout << "Invalid choice! Please select 0-6.\n";
        }
    } while (choice != 0);
    return 0;
}
