#include "App.hpp"
#include <iostream>
#include <limits>
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

void App::run(int argc, char* argv[]) {
    if (argc<2) {
        printDefault();
        return;
    }
    std::string command=argv[1];
    if (command=="--help" || command=="-h") {
        printHelp();
    }
    else if (command=="--list" || command=="-l") {
        handleList();
    }
    else if (command=="--add" || command=="-a") {
        handleAdd(argc,argv);
    }
    else if (command=="--remove" || command=="-r") {
        if (argc<3) {
            printDefault();
            return;
        }
        handleRemove(argc,argv);
    }
    else if (command=="--done" || command=="-d") {
        if (argc<3) {
            printDefault();
            return;
        }
        handleDone(argc,argv);
    }
    else {
        printDefault();
    }

}

void App::printDefault() const {
    std::cout<< "Unknown or missing command. Use --help" << std::endl;
}
void App::printHelp() const {
    std::cout<<
        "Todo App Commands: \n"
        "--add (-a) [task] \n"
        "--list (-l) \n"
        "--remove (-r) \n"
        "--done (-d)" << std::endl;
}
void App::handleAdd(int argc, char* argv[]) {
    std::string description;
    std::string prioritystring;
    Task::Priority priority =Task::Priority::LOW;
    if (argc < 3) {
        std::cout << "Enter description: ";
        std::getline(std::cin, description);

        if (description.empty()) {
            std::cout << "Description cannot be empty" << std::endl;
            return;
        }
         std::cout << "Enter priority (low/medium/high): ";
         std::getline(std::cin, prioritystring);
        priority = Task::parsePriority(prioritystring);
    }
    else {
        for (int i=2; i<argc; i++) {
            std::string arg=argv[i];
            if (arg=="low" || arg=="medium" || arg=="high") {
                priority=Task::parsePriority(arg);
            }
            else {
                description+=argv[i];
            }
            if (i<argc-1) {
                description+= " ";
            }
        }
    }
    todo.addTask(description,priority);
    std::cout << GREEN << "added " << description << RESET << std::endl;
}
void App::handleRemove(int argc, char* argv[]) {
    int id = std::stoi(argv[2]);
    if (todo.findById(id)) {
        todo.removeTask(id);
        std::cout<< RED<< "Removed task" << RESET<< std::endl;
    }
}
void App::handleList() {
    std::cout<<todo.showAllTasks()<<std::endl;
}

void App::handleDone(int argc, char* argv[]) {
    int id = std::stoi(argv[2]);
    if (todo.findById(id)) {
        todo.markTaskDone(id);
        std::cout<<GREEN<<"Task "<<id<<" is done"<<RESET << std::endl;
    }
    else std::cout<< RED <<"No task to be marked" << RESET<< std::endl;
}