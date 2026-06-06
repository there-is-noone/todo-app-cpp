#include "Task.hpp"

Task::Task(int id, const std::string& description,Priority p, bool done): id_(id), description_(description),done_(done) {}



void Task::setDone(bool is_done) {
    done_=is_done;
}
void Task::setDescription(const std::string& description) {
    description_ = description;
}
void Task::setId(int id) {
    id_ = id;
}

int Task::getId() const {
    return id_;
}
std::string Task::getDescription()  const{
    return description_;
}
bool Task::isDone() const {
    return done_;
}
Task::Priority Task::getPriority() const {
    return priority_;
}
