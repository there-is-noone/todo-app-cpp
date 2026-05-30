#pragma once

#include <vector>
#include "JsonStorage.hpp"
#include "Task.hpp"
#include <fstream>

#include "json.hpp"
using json=nlohmann::json;

JsonStorage::JsonStorage(const std::string& name): FileName(name) {}

std::vector<Task> JsonStorage::load() {
    std::ifstream file(FileName);
    if (!file) return{};
    json j;
    file >> j;

    std::vector<Task> tasks;

    for (auto& i : j) {
        tasks.emplace_back(Task(
            i["id"],
            i["description"],
            i["done"]));
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
            {"done",Task.isDone()}
        });
    }
    WriteFile<< j.dump(4);
}

JsonStorage::~JsonStorage() =default;
