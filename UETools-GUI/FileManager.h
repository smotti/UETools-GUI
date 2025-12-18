#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>






class FileManager
{
public:
	explicit FileManager(const std::filesystem::path& filePath);
	virtual ~FileManager() = default;

	std::string GetFilePath();
	bool DoesFileExist();
	bool DoesDirectoryExist();

	bool LoadText(std::string* outText);
	bool SaveText(const std::string& text);

	bool LoadLines(std::vector<std::string>* outLines);
	bool SaveLines(const std::vector<std::string>& lines);


private:
	std::filesystem::path _filePath;
};

