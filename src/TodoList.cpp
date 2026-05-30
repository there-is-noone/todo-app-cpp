#include "TodoList.hpp"
#include "Storage.hpp"
#include "Task.hpp"

Task* TodoList::findById(int Id) {
    for (auto& task : TaskList) {
        if (task.getId() == Id) {
            return &task;
        }
    }
    return nullptr;
}
void TodoList::markTaskDone(int Id) {
    Task* task= findById(Id);
    if (!task) {
        return;
    }
    task->setDone();
}
void TodoList::addTask(const std::string& description){
    Task newTask(getNextId(), description, false);
    TaskList.push_back(newTask);
}
void TodoList::removeTask(Task* task) {
    if (!task) {
        return;
    }
    removeTask(task->getId());
}
void TodoList::removeTask(int Id) {
    for (auto it=TaskList.begin(); it!=TaskList.end(); ++it) {
        if (it->getId() == Id) {
            TaskList.erase(it);
            return;
        }
    }
}
std::string TodoList::showAllTasks() {
    std::string result;

    for (const auto& task : TaskList) {
        result += std::to_string(task.getId()) + ". ";

        result += task.getDescription();

        result += task.isDone() ? " [DONE]\n" : " [TODO]\n";
    }

    return result;
}
int TodoList::getNextId() {
    return nextId++;
}