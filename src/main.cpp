#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include "Engine/EncryptionEngine.h"

int main()
{
	std::cout << "Enter the path to selected directory : ";
	std::string input;
	getline(std::cin, input);


	std::cout << "Would you like to:" << std::endl;
	std::cout << "1. Encrypt." << std::endl;
	std::cout << "2. Decrypt." << std::endl;
	std::cout << "Choose: ";
	short response;
	std::cin >> response;

	if(response == 1)
	{
		EncryptionEngine engine(input);
		engine.encrypt();
		std::cout << "Encryption Complete." << std::endl;
	}else if(response == 2)
	{
		EncryptionEngine engine(input);
		engine.decrypt();
		std::cout << "Decryption Complete." << std::endl;
	}else
	{
		std::cout << "Undefined option." << std::endl;
	}
	std::cin >> response;
	return 0;
}
