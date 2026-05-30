#pragma once
#include "Storage.hpp"
#include "json.hpp"
#include <string>
#include <vector>

using json=nlohmann::json;

class JsonStorage : public Storage {
private:
    std::string FileName;
    public:
    explicit JsonStorage(const std::string& name);
    std::vector<Task> load() override;
    void save(const std::vector<Task>& Tasks) override;
    ~JsonStorage() override;
};