#pragma once

#include <vector>
#include "JsonStorage.hpp"
#include "Task.hpp"
#include <fstream>


JsonStorage::JsonStorage(const std::string& name): FileName(name) {}

std::vector<Task> JsonStorage::load() {
    std::ifstream file(FileName);
    json j;
    file >> j;
    std::vector<Task> tasks;
    for (auto& i : j) {
        tasks.push_back(Task(
            i["title"],
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
        j.push_back({{"title", Task.getTitle()},
            {"id",Task.getId()},
            {"description", Task.getDescription()},
            {"done",Task.isDone()}
        });
    }
}