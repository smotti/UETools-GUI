#include "FileManager.h"






FileManager::FileManager(const std::filesystem::path& filePath)
    : _filePath(filePath)
{
}




std::string FileManager::GetFilePath()
{
    return std::filesystem::absolute(_filePath).string();
}

bool FileManager::DoesFileExist()
{
    if (_filePath.empty() == true)
        return false;

    std::error_code errorCode;
    return std::filesystem::exists(_filePath, errorCode) == true
           && std::filesystem::is_regular_file(_filePath, errorCode) == true;
}

bool FileManager::DoesDirectoryExist()
{
    const std::filesystem::path parentPath = _filePath.parent_path();

    /* No parent directory specified -> use current working directory. */
    if (parentPath.empty() == true)
        return true;

    std::error_code errorCode;
    if (std::filesystem::exists(parentPath, errorCode) == true)
        return true;

    return std::filesystem::create_directories(parentPath, errorCode);
}




bool FileManager::LoadText(std::string* outText)
{
    if (outText == nullptr)
        return false;

    outText->clear();

    std::ifstream file(_filePath, std::ios::in | std::ios::binary);
    if (file.is_open() == false)
        return false;

    std::ostringstream stringStream;
    stringStream << file.rdbuf();
    *outText = stringStream.str();

    return true;
}

bool FileManager::SaveText(const std::string& text)
{
    if (DoesDirectoryExist() == false)
        return false;

    std::ofstream file(_filePath, std::ios::out | std::ios::binary | std::ios::trunc);
    if (file.is_open() == false)
        return false;

    file.write(text.data(), static_cast<std::streamsize>(text.size()));
    return file.good();
}




bool FileManager::LoadLines(std::vector<std::string>* outLines)
{
    if (outLines == nullptr)
        return false;

    outLines->clear();

    std::ifstream file(_filePath);
    if (file.is_open() == false)
        return false;

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty() == false && line.back() == '\r')
            line.pop_back();

        outLines->push_back(line);
    }

    return true;
}

bool FileManager::SaveLines(const std::vector<std::string>& lines)
{
    if (DoesDirectoryExist() == false)
        return false;

    std::ofstream file(_filePath, std::ios::out | std::ios::trunc);
    if (file.is_open() == false)
        return false;

    for (const std::string& line : lines)
    {
        file << line << "\n";
        if (file.good() == false)
            return false;
    }

    return true;
}
