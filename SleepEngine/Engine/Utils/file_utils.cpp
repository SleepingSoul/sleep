#include "stdafx.h"
#include "file_utils.h"
#include <fmt/ostream.h>


std::optional<std::string> readFile(std::filesystem::path path)
{
    std::ifstream stream(path, std::fstream::in | std::fstream::binary);

    if (!stream.is_open())
    {
        LOG_AND_FAIL("file already open : {}", path);
        return std::nullopt;
    }
    
    return std::string(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());
}