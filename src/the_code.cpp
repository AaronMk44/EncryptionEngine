#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>


int main2()
{
	std::filesystem::path p{"H:\\Projects\\C++\\EncryptionEngine\\How to be Polite _ SkillsYouNeed.pdf"};

	//filename
	std::string filename = p.filename().string();
	std::string filename_output = filename+".enct";

	//filesize
	int filename_size = filename.size();

	//write file size
	std::cout << filename_size << std::endl;

	//write file name
	std::fstream file_enc(filename_output.c_str(), std::ios::binary | std::ios::out);
	file_enc.write(reinterpret_cast<char*>(&filename_size), sizeof(filename_size));

	char tmp[1];
	for(int i = 0; i < filename_size; i++)
	{
		tmp[0] = filename.at(i);
		file_enc.write(tmp, sizeof(tmp));
		std::cout << tmp[0] << std::endl;
	}
	file_enc.close();

	//write remainder of data

	std::ifstream fin;
	std::ofstream fout;
	fin.open(filename.c_str(), std::ios::binary);
	fout.open(filename_output.c_str(), std::ios::binary | std::ios::app); //size + name+ data
	char c[1];

	while(fin.read(c, 1))
	{
		c[0] = c[0] + 9;
		fout.write(c, 1);
	}
	fin.close();
	fout.close();
	remove(filename.c_str());
	//decryption
	std::fstream file_enc2(filename_output.c_str(), std::ios::binary | std::ios::in);
		file_enc2.read(reinterpret_cast<char*>(&filename_size), sizeof(filename_size));
		std::string file_name_2 = "H:\\Projects\\C++\\";

		for(int i = 0; i < filename_size; i++)
		{
			file_enc2.read(tmp, sizeof(tmp));
			file_name_2 += tmp[0];
		}
		std::cout << "file name done" << std::endl;

		//read remainder of data to file

		std::ofstream fout2;
		fout2.open(file_name_2.c_str(), std::ios::binary);

		while(file_enc2.read(c, 1))
		{
			c[0] = c[0] - 9;
			fout2.write(c, 1);
		}

		fout2.close();
		file_enc2.close();

//	std::filesystem::path p{"H:\\Projects\\C++\\EncryptionEngine\\"};
//	for(auto const& dir_entry: std::filesystem::recursive_directory_iterator{p})
//	{
//		std::cout << dir_entry << std::endl;
//	}
	return 0;
}
