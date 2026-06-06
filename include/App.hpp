#pragma once
#include "TodoList.hpp"

class App {
public:
    explicit App(TodoList& todo):todo(todo){}
    void run(int argc,char* argv[]);

    private:
    void printDefault() const;
    void printHelp() const;
    void handleList();

    void handleAdd(int argc, char* argv[]);
    void handleRemove(int argc, char* argv[]);
    void handleDone(int argc, char* argv[]);
    TodoList& todo;
};