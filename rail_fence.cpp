#include <iostream>
#include <string>


int displayMessage()
{
    int choice = 0;
    std::cout << "Action to be performed:" << std::endl;
    std::cout << "Encryption => Enter 1" << std::endl;
    std::cout << "Decryption => Enter 2" << std::endl;
    std::cout << "Action: ";
    std::cin >> choice;
    return choice;
}


std::string encrypt(std::string input)
{
    std::string rail1,rail2,rail3;
    int i = 0, end = input.length()-1;
    while (i <= end){
        if (i % 3 == 0){
            rail1 += input[i];
        } else if (i % 3 == 1){
            rail2 += input[i];
        } else{
            rail3 += input[i];
        }
        i++;
    }

    return rail1+rail2+rail3;
}

std::string decrypt(std::string input)
{
    int len = input.length();
    int r1 = (len + 2) / 3;
    int r2 = (len + 1) / 3;

    std::string rail1 = input.substr(0, r1);
    std::string rail2 = input.substr(r1, r2);
    std::string rail3 = input.substr(r1 + r2);

    std::string output;

    for (int i = 0, a = 0, b = 0, c = 0; i < len; i++)
    {
        if (i % 3 == 0) output += rail1[a++];
        else if (i % 3 == 1) output += rail2[b++];
        else output += rail3[c++];
    }

    return output;
}


int main()
{
    std::string plain_text,cipher_text;

    int action = displayMessage();
    if (action == 1){
        std::cout << "Enter plaintext: ";
        std::cin >> plain_text;
        cipher_text = encrypt(plain_text);
        std::cout << "Ciphertext: " << cipher_text << std::endl;
    } else if (action == 2){
        std::cout << "Enter ciphertext: ";
        std::cin >> cipher_text;
        plain_text = decrypt(cipher_text);
        std::cout << "Plaintext: " << plain_text << std::endl;
    } else {
        std::cout << "Invalid choice !" << std::endl;
    }
}
