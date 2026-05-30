#include "TodoList.hpp"
#include "Storage.hpp"
#include "Task.hpp"
std::vector<Task> TaskList;
std::vector<Task> loadTasks();
void SaveTasks(const std::vector<Task>& tasks);