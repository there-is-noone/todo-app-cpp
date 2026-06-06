#include "TodoList.hpp"
#include "Storage.hpp"
#include "Task.hpp"
#include "colors.hpp"
#include <algorithm>


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
    Task newTask(getNextId(), description,priority, false);
    TaskList.push_back(newTask);
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
    if (TaskList.empty()) {
        return "\n" CYAN "📋 No tasks yet!\n" RESET
               "   Add one with: ./todo -a \"task\" [priority]\n\n";
    }

    std::string result;
    std::vector<Task> SortedTaskList = TaskList;
    std::sort(SortedTaskList.begin(), SortedTaskList.end(),
    [](const Task& a, const Task& b) {
        return a.getPriority() > b.getPriority();
    });

    result += "\n";
    int done_count = 0;

    for (const auto& task : SortedTaskList) {
        if (task.isDone()) done_count++;

        // Color by priority
        if (task.getPriority() == Task::Priority::HIGH) {
            result += RED "●" RESET;
        } else if (task.getPriority() == Task::Priority::MEDIUM) {
            result += YELLOW "●" RESET;
        } else {
            result += GRAY "●" RESET;
        }

        result += " #" + std::to_string(task.getId());
        result += " " + task.getDescription();
        result += " ";

        if (task.isDone()) {
            result += GREEN "[✓ DONE]" RESET;
        } else {
            result += YELLOW "[⏳ TODO]" RESET;
        }
        result += "\n";
    }

    int total = TaskList.size();
    int pending = total - done_count;
    result += "\n" CYAN "━━━━━━━━━━━━━━━━━━━━━━━━━━━━" RESET "\n";
    result += CYAN "Tasks: " RESET + std::to_string(total) +
              CYAN " | " RESET GREEN "Done: " RESET + std::to_string(done_count) +
              CYAN " | " RESET YELLOW "Pending: " RESET + std::to_string(pending) + "\n\n";

    return result;
}

void TodoList::editTaskPriority(int id, Task::Priority priority) {
    Task* task= findById(id);
    if (!task) {
        return;
    }
    task->setPriority(priority);
    storage.save(TaskList);
}


int TodoList::getNextId() {
    return nextId++;
}