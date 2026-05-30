#pragma once

#include <string>

class Task {
private:
    std::string title_;
    int id_;
    std::string description_;
    bool done_;

public:
    Task(const std::string& Title, int id, const std::string& description, bool done=false);

    int getId() const;
    std::string getDescription() const;
    bool isDone() const;
    std::string getTitle() const;

    void setDone(bool is_done=true);
    void setDescription(const std::string& description);
    void setId(int id);
    void setTitle(const std::string& title);

    Task(const Task& other);
    Task(Task&& other) noexcept;
    Task& operator=(const Task& other);
    Task& operator=(Task&& other) noexcept;
    ~Task()=default;
};