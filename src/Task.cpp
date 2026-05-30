#include "Task.hpp"

Task::Task(const std::string& Title, int id, const std::string& description, bool done):title_(Title), id_(id), description_(description),done_(done) {}

void Task::setDone(bool is_done) {
    done_=is_done;
}
void Task::setDescription(const std::string& description) {
    description_ = description;
}
void Task::setId(int id) {
    id_ = id;
}
void Task::setTitle(const std::string& title) {
    title_ = title;
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
std::string Task::getTitle() const {
    return title_;
}