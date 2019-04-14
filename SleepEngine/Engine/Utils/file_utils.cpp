#include "stdafx.h"
#include "file_utils.h"
#include <fmt/ostream.h>

std::optional<std::string> readFile(std::filesystem::path path)
{
    if (!std::filesystem::exists(path))
    {
        return std::nullopt;
    }

    std::uintmax_t bytesCount = std::filesystem::file_size(path);
    std::string data(bytesCount, '#');
    std::ifstream fstream;

    if (fstream.is_open())
    {
        LOG_AND_FAIL_ERROR("file already open : {}", path);
        return std::nullopt;
    }

    fstream.open(path, std::fstream::in | std::fstream::binary);
    fstream.read(data.data(), bytesCount);
    fstream.close();

    return data;
}
