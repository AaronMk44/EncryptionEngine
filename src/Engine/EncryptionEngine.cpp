#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include "EncryptionEngine.h"

EncryptionEngine::EncryptionEngine(const std::string& path)
{
	this->p = new std::filesystem::path{path};
}
EncryptionEngine::~EncryptionEngine()
{
	delete this->p;
}

void EncryptionEngine::setStartingDir(const std::string& path)
{
	delete this->p;
	this->p = new std::filesystem::path{path};
}
std::string EncryptionEngine::getStartingDir() const
{
	return this->p->string();
}

void EncryptionEngine::encrypt()
{
	try
	{
		for(auto const& dir_entry: std::filesystem::recursive_directory_iterator{*this->p})
		{
			if(std::filesystem::is_regular_file(dir_entry))
			{
				std::filesystem::path p{dir_entry};
				if(p.extension() != ENC_FILE_EXT)
				{
					this->encrypt_logic(dir_entry);
				}
			}

		}
	}catch(...)
	{
		std::cout << "An error occurred.\n Possible cause could be undefined directory." << std::endl;
	}

}
void EncryptionEngine::decrypt()
{
	try
	{
		for(auto const& dir_entry: std::filesystem::recursive_directory_iterator{*this->p})
			{
				if(std::filesystem::is_regular_file(dir_entry))
				{
					std::filesystem::path p{dir_entry};
					if(p.extension() == ENC_FILE_EXT)
					{
						this->decrypt_logic(dir_entry);
					}
				}

			}
	}catch(...)
	{
		std::cout << "An error occurred.\n Possible cause could be undefined directory." << std::endl;
	}

}
std::string EncryptionEngine::getLog()
{
	return std::string("");
}


// Logic
template <class T> //simply because we don't know the exact type for dir_entry
void EncryptionEngine::encrypt_logic(T tmp_p)
{
	std::filesystem::path original_path{tmp_p};

	//filenames
	std::string original_filename = original_path.filename().string();
	std::string output_filename = original_filename+ENC_FILE_EXT;
	std::filesystem::path output_path = original_path;
	output_path.replace_filename(output_filename);

	//file size
	int filename_size = original_filename.size();

	//write file size & file name to output_file
	std::fstream output_file(output_path.string().c_str(), std::ios::binary | std::ios::out);
	output_file.write(reinterpret_cast<char*>(&filename_size), sizeof(filename_size));

	char tmp[1];
	for(int i = 0; i < filename_size; i++)
	{
		tmp[0] = original_filename.at(i);
		output_file.write(tmp, sizeof(tmp));
	}
	output_file.close();

	//write remainder of data from original file to output file
	std::ifstream fin(original_path.string().c_str(), std::ios::binary);
	std::ofstream fout(output_path.string().c_str(), std::ios::binary | std::ios::app); //size + name+ data

	while(fin.read(tmp, sizeof(tmp)))
	{
		tmp[0] = tmp[0] + (7*filename_size);// replace 9 with key
		fout.write(tmp, sizeof(tmp));
	}
	fin.close();
	fout.close();
	remove(original_path.string().c_str());
}

template <class T> //simply because we don't know the exact type for dir_entry
void EncryptionEngine::decrypt_logic(T tmp_p)
{
	std::filesystem::path output_path{tmp_p};

	//filenames
	std::string output_filename = output_path.filename().string();
	std::string original_filename = "dec_";

	//file size
	int filename_size;
	std::fstream output_file(output_path.string().c_str(), std::ios::binary | std::ios::in);
	output_file.read(reinterpret_cast<char*>(&filename_size), sizeof(filename_size));

	char tmp[1];
	for(int i = 0; i < filename_size; i++)
	{
		output_file.read(tmp, sizeof(tmp));
		original_filename += tmp[0];
	}

	//produce original file
	std::filesystem::path original_path = output_path;
	original_path.replace_filename(original_filename);
	std::ofstream original_file(original_path.string().c_str(), std::ios::binary);

	while(output_file.read(tmp, sizeof(tmp)))
	{
		tmp[0] = tmp[0] - (7*filename_size);//replace 9 with key
		original_file.write(tmp, sizeof(tmp));
	}

	original_file.close();
	output_file.close();
	remove(output_path.string().c_str());
}
