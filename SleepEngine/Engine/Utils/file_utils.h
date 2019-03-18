#pragma once

// if file does not exists, or open or read operation failed, returns empty string
std::optional<std::string> readFile(std::filesystem::path path);