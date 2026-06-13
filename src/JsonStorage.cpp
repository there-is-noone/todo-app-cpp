#ifndef JSONSTORAGE_CPP
#define JSONSTORAGE_CPP
#include <vector>
#include "JsonStorage.hpp"
#include "Task.hpp"
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include "json.hpp"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <unistd.h>
#elif __APPLE__
#include <mach-o/dyld.h>
#endif

std::filesystem::path getExecutablePath() {
#ifdef _WIN32
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    return std::filesystem::path(buffer);

#elif __linux__
    char buffer[1024];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1) {
        buffer[len] = '\0';
        return std::filesystem::path(buffer);
    }
    throw std::runtime_error("Cannot get executable path");

#elif __APPLE__
    char buffer[1024];
    uint32_t size = sizeof(buffer);
    if (_NSGetExecutablePath(buffer, &size) == 0) {
        return std::filesystem::path(buffer);
    }
    throw std::runtime_error("Cannot get executable path");

#else
    throw std::runtime_error("Unsupported platform");
#endif
}

using json=nlohmann::json;
JsonStorage::JsonStorage(const std::string& name) {
    const char* home = std::getenv("HOME");

    std::filesystem::path baseDir =
        std::string(home ? home : "") + "/.local/share/todo-app";

    std::filesystem::create_directories(baseDir);

    FileName = (baseDir / "tasks.json").string();

    std::cout << "Using file: " << FileName << std::endl;
}

std::vector<Task> JsonStorage::load() {
    std::ifstream file(FileName);

    // 🔥 If file doesn't exist → create it
    if (!file.is_open()) {
        std::ofstream create(FileName);
        create << "[]";
        create.close();
        return {};
    }

    // 🔥 Check if file is empty
    if (file.peek() == std::ifstream::traits_type::eof()) {
        file.close();
        std::ofstream fix(FileName);
        fix << "[]";
        fix.close();
        return {};
    }

    json j;
    file >> j;

    std::vector<Task> tasks;

    for (auto& i : j) {
        tasks.emplace_back(Task(
            i["id"],
            i["description"],
            Task::parsePriority(i["priority"].get<std::string>()),
            i["done"]
        ));
    }

    return tasks;
}

void JsonStorage::save(const std::vector<Task>& Tasks) {
    std::ofstream WriteFile(FileName);
    json j=json::array();
    for (const Task& Task : Tasks) {
        j.push_back({
            {"id",Task.getId()},
            {"description", Task.getDescription()},
                {"priority", Task::priorityToString(Task.getPriority())},
            {"done",Task.isDone()}
        });
    }
    WriteFile<< j.dump(4);
}

JsonStorage::~JsonStorage() =default;

#endif //JSONSTORAGE_CPP