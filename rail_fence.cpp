#include <iostream>
#include <string>
#include <vector>

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

std::string encrypt(std::string input, int rails)
{
    std::vector<std::string> rail(rails);

    for (int i = 0; i < input.length(); i++)
    {
        rail[i % rails] += input[i];
    }

    std::string output;

    for (int i = 0; i < rails; i++)
    {
        output += rail[i];
    }

    return output;
}

std::string decrypt(std::string input, int rails)
{
    int len = input.length();

    std::vector<std::string> rail(rails);

    // Find how many characters go into each rail
    for (int i = 0; i < len; i++)
    {
        rail[i % rails] += ' ';
    }

    // Fill the rails from ciphertext
    int index = 0;

    for (int i = 0; i < rails; i++)
    {
        for (int j = 0; j < rail[i].length(); j++)
        {
            rail[i][j] = input[index++];
        }
    }

    // Read the rails in original order
    std::string output;

    std::vector<int> position(rails, 0);

    for (int i = 0; i < len; i++)
    {
        int r = i % rails;

        output += rail[r][position[r]];
        position[r]++;
    }

    return output;
}

int main()
{
    std::string plain_text, cipher_text;
    int rails;

    int action = displayMessage();

    if (action == 1)
    {
        std::cout << "Enter number of rails: ";
        std::cin >> rails;

        std::cout << "Enter plaintext: ";
        std::cin >> plain_text;

        cipher_text = encrypt(plain_text, rails);

        std::cout << "Ciphertext: " << cipher_text << std::endl;
    }
    else if (action == 2)
    {
        std::cout << "Enter number of rails: ";
        std::cin >> rails;

        std::cout << "Enter ciphertext: ";
        std::cin >> cipher_text;

        plain_text = decrypt(cipher_text, rails);

        std::cout << "Plaintext: " << plain_text << std::endl;
    }
    else
    {
        std::cout << "Invalid choice !" << std::endl;
    }
}