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

using json=nlohmann::json;

JsonStorage::JsonStorage(const std::string& name) {
    std::string home;

#ifdef _WIN32
    char* userProfile = std::getenv("USERPROFILE");
    home = userProfile ? userProfile : "";
#else
    char* homeDir = std::getenv("HOME");
    home = homeDir ? homeDir : "";
#endif

    FileName = home + "/.todo-app/tasks.json";

    std::filesystem::path path(FileName);
    std::filesystem::create_directories(path.parent_path());

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