#ifndef FileManager_HPP
#define FileManager_HPP

#include <stdio.h>

#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <fstream>
#include <iostream>
#include <string>

#include "../Context/State.hpp"
#include "Serialization.hpp"

#ifdef WIN32
#include <windows.h>
// Must be second
#include <ShellAPI.h>
#endif

#ifdef linux
// TODO
#endif

namespace srl {

class FileManager {
   private:
    FileManager();

   public:
    static std::string CurrentPath();
    static void OpenFileExplorer(std::string path);
    static std::string SelectFile(std::string name = "Explorer", std::string path = nullptr, const char* filter = "All\0*.*\0Text\0*.txt\0Json\0*.json\0", bool saving = false);

    static ctx::State LoadState(std::string path);
    static void SaveState(const ctx::State& state, std::string path);
};

}  // namespace srl

#endif