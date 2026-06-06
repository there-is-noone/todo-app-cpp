#pragma once
#include <vector>
#include "Task.hpp"
#include "Storage.hpp"
class TodoList{
public:
    TodoList(Storage& storage): storage(storage), nextId(1) {
        TaskList=this->storage.load();
        for (const auto& task : TaskList) {
            if (task.getId() >= nextId) {
                nextId = task.getId() + 1;
            }
        }
    }
    TodoList(TodoList& todoList)=default;
    TodoList(TodoList&& todoList)=default;
    ~TodoList()=default;
    Task* findById(int id);
    void markTaskDone(int Id);
    void addTask(const std::string& description, Task::Priority priority);
     void removeTask(Task* task);
    void removeTask(int Id);
    std::string showAllTasks();

    int getNextId();

    private:
    std::vector<Task> TaskList;
    Storage& storage;
    int nextId;
};