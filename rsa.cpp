#include <iostream>
#include <string>

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


int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int modInverse(int e, int phi)
{
    for (int d = 1; d < phi; d++)
    {
        if ((e * d) % phi == 1)
            return d;
    }

    return -1;
}


int main()
{
    long long p, q, n,euler_totient;
    int input_message, encoded_message, decoded_message;
    
    std::cout << "Enter the value of p: ";
    std::cin >> p;
    std::cout << "Enter the value of q: ";
    std::cin >> q;

    n = p*q;
    euler_totient = (p-1)*(q-1);

    long long e = 2;
    while (e < euler_totient && gcd(e, euler_totient) != 1) e++;
    
    long long d = modInverse(e, euler_totient);

    std::cout << "Public Key: " << e << std::endl;
    std::cout << "Private Key: " << d << std::endl;
    std::cout << "-----------------------------------" << std::endl;


    std::cout << "Enter message: ";
    std::cin >> input_message;

    encoded_message = powerMod(input_message, e, n);
    std::cout << "Encrypted message: " << encoded_message << std::endl;
    
    decoded_message = powerMod(encoded_message, d, n);
    std::cout << "Decrypted message: " << decoded_message << std::endl;

}