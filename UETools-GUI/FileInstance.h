#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>






class FileInstance
{
public:
	explicit FileInstance(const std::filesystem::path& filePath);
	virtual ~FileInstance() = default;

	std::string GetAbsoluteFilePath();
	bool DoesFileDirectoryExist();
	bool DoesFileExist();

	bool LoadText(std::string* outText);
	bool SaveText(const std::string& text);

	bool LoadLines(std::vector<std::string>* outLines);
	bool SaveLines(const std::vector<std::string>& lines);


private:
	std::filesystem::path _filePath;
};

