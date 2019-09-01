// Copyright 2019 Taras Martinyuk, Tihran Katolikian

#pragma once

std::optional<std::string> readFile(std::filesystem::path const& path);
// creates if not exists
bool ensureFileExists(std::filesystem::path const& path);
void createFile(std::filesystem::path const& path);