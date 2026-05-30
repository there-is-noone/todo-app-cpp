#pragma once
#include <vector>
#include "Task.hpp"
#include "Storage.hpp"
class TodoList{
public:
    TodoList();
    TodoList(const TodoList& todoList)=default;
    TodoList(TodoList&& todoList)=default;
    ~TodoList()=default;
    Task* findById(int id);
    void markTaskDone(int Id);
    void addTask(const std::string& description);
    void removeTask(Task* task);
    void removeTask(int Id);
    std::string showAllTasks();
    std::vector<Task> loadTasks();
    void SaveTasks(const std::vector<Task>& tasks);

    int getNextId();

    private:
    std::vector<Task> TaskList;
    Storage& storage;
    int nextId;
};