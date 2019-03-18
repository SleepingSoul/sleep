#include "stdafx.h"
#include "file_utils.h"

std::optional<std::string> readFile(std::filesystem::path path)
{
    if (!std::filesystem::exists(path))
    {
        return std::nullopt;
    }

    int bytes = static_cast<int>(std::filesystem::file_size(path));

    std::string data(bytes, '#');
    std::ifstream fstream;

    assertion(!fstream.is_open(), "stats file already open");
    fstream.open(path, std::fstream::in | std::fstream::binary);
    fstream.read(data.data(), bytes);
    fstream.close();

    return data;
}
