#include <filesystem>
#include <string>

#ifndef ENCRYPTIONENGINE_H_
#define ENCRYPTIONENGINE_H_

const std::string ENC_FILE_EXT = ".enct";

class EncryptionEngine
{
private:
	std::filesystem::path* p;

	//We make the parameter generic because we don't know the data type for dir_entry
	template <class T>
	void encrypt_logic(T tmp_p);
	template <class T>
	void decrypt_logic(T tmp_p);
public:
	EncryptionEngine(const std::string& path);
	~EncryptionEngine();

	void setStartingDir(const std::string& path);
	std::string getStartingDir() const;

	void setKey(const int& key);
	int getKey() const;

	void encrypt();
	void decrypt();
	std::string getLog();
};



#endif
