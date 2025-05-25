#include <filesystem>
#include <string>

using namespace std;
namespace fs = filesystem;

string getFilePath(const fs::path& appRootDir, const string& filePath);
