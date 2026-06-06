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

    task->setDone();
    storage.save(TaskList);
}
void TodoList::addTask(const std::string& description,Task::Priority priority){
    Task newTask(getNextId(), description,priority=Task::Priority::LOW, false);
    TaskList.push_back(newTask);
    storage.save(TaskList);
}
void TodoList::removeTask(Task* task) {
    if (!task) {
        return;
    }
    removeTask(task->getId());
    storage.save(TaskList);
}
void TodoList::removeTask(int Id) {
    for (auto it=TaskList.begin(); it!=TaskList.end(); ++it) {
        if (it->getId() == Id) {
            TaskList.erase(it);
            storage.save(TaskList);
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