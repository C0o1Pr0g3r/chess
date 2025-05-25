#include "fs.h"

string getFilePath(const fs::path& appRootDir, const string& filePath)
{
    return (appRootDir / filePath).string();
}
