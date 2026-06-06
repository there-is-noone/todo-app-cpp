#pragma once

#include <string>

class Task {
public:
    enum class Priority { LOW, MEDIUM, HIGH };
    Priority priority_;
    static Priority parsePriority(const std::string& input) {
        if (input == "high") return Priority::HIGH;
        if (input == "medium") return Priority::MEDIUM;
        return Priority::LOW;
    }
    Task(int id, const std::string& description, Priority p, bool done=false);

    int getId() const;
    std::string getDescription() const;
    bool isDone() const;
    Priority getPriority() const;

    void setDone(bool is_done=true);
    void setDescription(const std::string& description);
    void setId(int id);


    Task(const Task& other)=default;
    Task(Task&& other) noexcept =default;
    Task& operator=(const Task& other) =default;
    Task& operator=(Task&& other) noexcept = default;
    ~Task()=default;

private:
    int id_;
    std::string description_;
    bool done_;
};