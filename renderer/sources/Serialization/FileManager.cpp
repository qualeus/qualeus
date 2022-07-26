#include "../../include/Serialization/FileManager.hpp"

namespace srz {

FileManager::FileManager() {}

std::string FileManager::CurrentPath() {
    std::string current_path = "";
#ifdef WIN32
    wchar_t extr_path[MAX_PATH];
    GetModuleFileNameW(NULL, extr_path, MAX_PATH);
    std::wstring r_path = std::wstring(extr_path);
    current_path = std::string(r_path.begin(), r_path.end());
    current_path = current_path.substr(0, current_path.find_last_of("\\/"));
#endif
#ifdef __linux__
// TODO
#endif
    return current_path;
}

void FileManager::OpenFileExplorer(std::string path) {
#ifdef WIN32
    ShellExecute(0, nullptr, "explorer.exe", path.c_str(), nullptr, SW_SHOWNORMAL);
#endif
#ifdef __linux__
// TODO
#endif
}
std::string FileManager::SelectFile(std::string name, std::string path, const char* filter, bool saving) {
    std::string fileNameStr;

#ifdef WIN32
    OPENFILENAME open;
    char fileName[MAX_PATH] = "";

    ZeroMemory(&open, sizeof(open));
    open.lStructSize = sizeof(OPENFILENAME);
    open.lpstrFile = fileName;
    open.nMaxFile = MAX_PATH;
    open.lpstrTitle = name.c_str();
    open.Flags = OFN_EXPLORER | OFN_HIDEREADONLY | (saving ? OFN_NOTESTFILECREATE : OFN_FILEMUSTEXIST);
    open.lpstrInitialDir = path.c_str();
    open.lpstrFilter = filter;
    // open.nFilterIndex = 0;
    open.lpstrDefExt = "";

    if (saving ? GetSaveFileName(&open) : GetOpenFileName(&open)) fileNameStr = fileName;

    return fileNameStr;
#endif
#ifdef __linux__
    char filename[1024];

    std::string subject = filter;
    std::string command = "zenity --file-selection --save --title='" + name + "' --file-filter='" + subject + "'";
    FILE* f = popen(command.c_str(), "r");
    fgets(filename, 1024, f);

    fileNameStr = filename;
#endif
    return fileNameStr;
}

ctx::State FileManager::LoadState(std::string path) {
    std::string extension = path.substr(path.find_last_of("."));

    ctx::State state;

    // Format from file extension
    if (extension == ".json") {
        std::ifstream file = std::ifstream(path);
        cereal::JSONInputArchive iarchive = cereal::JSONInputArchive(file);
        iarchive(cereal::make_nvp<ctx::State>("state", state));

    } else if (extension == ".latio") {
        std::ifstream file = std::ifstream(path, std::ios::binary);
        cereal::BinaryInputArchive iarchive = cereal::BinaryInputArchive(file);
        iarchive(cereal::make_nvp<ctx::State>("state", state));
    }

    return state;
}

void FileManager::SaveState(const ctx::State& state, std::string path) {
    std::string extension = path.substr(path.find_last_of("."));

    // Format from file extension
    if (extension == ".json") {
        std::ofstream file = std::ofstream(path);
        cereal::JSONOutputArchive oarchive = cereal::JSONOutputArchive(file);
        oarchive(cereal::make_nvp<ctx::State>("state", state));
    } else if (extension == ".latio") {
        std::ofstream file = std::ofstream(path, std::ios::binary);
        cereal::BinaryOutputArchive oarchive = cereal::BinaryOutputArchive(file);
        oarchive(cereal::make_nvp<ctx::State>("state", state));
    }
}

}  // namespace srz