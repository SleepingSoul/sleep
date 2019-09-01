#include "stdafx.h"
#include "file_utils.h"
#include <fmt/ostream.h>


std::optional<std::string> readFile(std::filesystem::path const& path)
{
    std::ifstream stream(path, std::fstream::in | std::fstream::binary);

    if (!stream.is_open())
    {
        LOG_AND_FAIL("file already open : {}", path);
        return std::nullopt;
    }
    
    return std::string(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());
}

bool ensureFileExists(std::filesystem::path const& path)
{
    namespace fs = std::filesystem;
    bool const creating = !fs::exists(path);
    if (creating)
    {
        createFile(path);
    }

    return creating;
}

void createFile(std::filesystem::path const& path)
{
    std::filesystem::create_directories(path.parent_path());

    std::ofstream ofstream(path);
    ofstream.close();
}
