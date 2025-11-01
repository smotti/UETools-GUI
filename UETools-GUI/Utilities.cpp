#include "Utilities.h"






std::string Utilities::Clipboard::GetClipboardText()
{
    if (OpenClipboard(nullptr))
    {
        HANDLE hData = GetClipboardData(CF_TEXT);
        if (hData)
        {
            char* pData = static_cast<char*>(GlobalLock(hData));
            if (pData)
            {
                std::string text(pData);
                GlobalUnlock(hData);

                CloseClipboard();
                return text;
            }

            GlobalUnlock(hData);
        }

        CloseClipboard();
    }

    return std::string();
}

bool Utilities::Clipboard::SetClipboardText(const std::string& str)
{
    if (OpenClipboard(nullptr))
    {
        EmptyClipboard();
        size_t textSize = str.size() + 1;

        HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, textSize);
        if (hGlobal)
        {
            void* pMem = GlobalLock(hGlobal);
            if (pMem)
            {
                std::memcpy(pMem, str.c_str(), textSize);
                GlobalUnlock(hGlobal);

                SetClipboardData(CF_TEXT, hGlobal);

                CloseClipboard();
                return true;
            }

            GlobalUnlock(hGlobal);
        }

        CloseClipboard();
    }

    return true;
}






std::string Utilities::String::ToLowerCase(const std::string& str)
{
    std::string outString = str;
    std::transform(outString.begin(), outString.end(), outString.begin(), [](unsigned char c)
    {
        return std::tolower(c);
    });

    return outString;
}

std::string Utilities::String::ToUpperCase(const std::string& str)
{
    std::string outString = str;
    std::transform(outString.begin(), outString.end(), outString.begin(), [](unsigned char c) 
    { 
        return std::toupper(c); 
    });

    return outString;
}
