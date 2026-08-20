#include <iostream>
#include <string>


std::string encrypt(std::string plainText)
{
    for (int i = 0; i < plainText.length(); i++)
    {
        if (std::isupper(plainText[i])){
            plainText[i] = 'A' + (plainText[i] - 'A' + 3) % 26;
        } else if (std::islower(plainText[i])){
            plainText[i] = 'a' + (plainText[i] - 'a' + 3) % 26;
        }
    }
    return plainText;
}


std::string decrypt(std::string cipherText)
{
    for (int i = 0; i < cipherText.length(); i++)
    {
        if (std::isupper(cipherText[i])){
            cipherText[i] = 'A' + (cipherText[i] - 'A' - 3 + 26) % 26;
        } else if (std::islower(cipherText[i])){
            cipherText[i] = 'a' + (cipherText[i] - 'a' - 3 + 26) % 26;
        }
    }
    return cipherText;
}

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

int main()
{
    std::string output_text;
    int action = displayMessage();
    std::string input_text;
    
    if(action == 1){
        std::cout << "Enter Plain Text: ";
        std::getline(std::cin >> std::ws, input_text);
        output_text = encrypt(input_text);
        std::cout << "Ciphertext => " << output_text << std::endl;
    } else if (action == 2){
        std::cout << "Enter Cipher Text: ";
        std::getline(std::cin >> std::ws, input_text);
        output_text = decrypt(input_text);
        std::cout << "Plaintext => " << output_text << std::endl;
    } else {
        std::cout << "Invalid choice !" << std::endl;
    }
}