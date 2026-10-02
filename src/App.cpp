#include "App.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <ctime>
#include <spawn.h>
#include <sys/wait.h>
#include "colors.hpp"

extern char** environ;

void App::run(int argc, char* argv[]) {
    if (argc<2) {
        printDefault();
        return;
    }
    std::string command=argv[1];
    if (command=="--help" || command=="-h") {
        printHelp(argc,argv);
    }
    else if (command=="--list" || command=="-l") {
        handleList(argc,argv);
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
    else if (command=="--edit" || command=="-e") {
        handleEdit(argc,argv);
    }
    else if (command=="--notify" || command=="-n") {
        handleNotify(argc,argv);
    }
    else {
        printDefault();
    }

}

void App::printDefault() const {
    std::cout<< "Unknown or missing command. Use --help" << std::endl;
}
void App::printHelp(int argc,char* argv[]) const {
    if (argc<3){
        std::cout <<
        "Todo CLI - Help\n\n"
        "Usage:\n"
        "  todo [command] [options]\n\n"
        "Commands:\n"
        "  -a, --add       Add a new task\n"
        "  -l, --list      Show all tasks\n"
        "  -r, --remove    Remove a task\n"
        "  -d, --done      Mark task as done\n"
        "  -e, --edit      Edit the priority of a task\n"
        "  -n, --notify    Popup with HIGH priority tasks (once a day)\n\n"
        "More help:\n"
        "  todo -h [add | a]\n"
        "  todo -h [remove | r] \n"
        "  todo -h [list | l]\n"
        "  todo -h [done | d]\n"
        "  todo -h [edit | e]\n"
        "  todo -h [notify | n]\n\n";
    }
    else {
        std::string command=argv[2];
        if (command=="add" || command=="a") {
            std::cout<<
                "ADD COMMAND\n"
"Usage:\n"
"todo -a [description] [priority]\n\n"
"Description:\n"
"Adds a new task to the todo list.\n\n"
"Arguments:\n"
"description   The task description (can contain spaces)\n"
"priority      Optional: low, medium, high (default: low)\n"

"Examples:\n"
"todo -a \"Buy milk\"\n"
"todo -a \"Finish project\" high\n\n"
"Interactive mode:\n"
"If no description is provided, the program will prompt you\n"
"to enter description and priority step-by-step.\n";
        }
        else if (command == "remove" || command=="r") {
            std::cout <<
                "REMOVE COMMAND\n"
                "Usage:\n"
                "todo -r <id>\n\n"
                "Description:\n"
                "Removes a task by its ID.\n\n"
                "Arguments:\n"
                "id    The ID of the task to remove\n\n"
                "Example:\n"
                "todo -r 3\n";
        }
        else if (command == "list" || command =="l") {
            std::cout <<
               "LIST COMMAND\n"
               "Usage:\n"
               "todo -l                    Show all tasks\n"
               "todo -l --pending (-p)     Show only incomplete tasks\n"
               "todo -l --done (-d)        Show only completed tasks\n"
               "todo -l --high             Show only HIGH priority\n"
               "todo -l --medium           Show only MEDIUM priority\n"
               "todo -l --low              Show only LOW priority\n\n"
               "Combine filters:\n"
               "todo -l -p --high          Show HIGH priority tasks that are TODO\n\n"
               "Examples:\n"
               "todo -l\n"
               "todo -l --pending\n"
               "todo -l --high --pending\n";       }
        else if (command == "done" || command == "d") {
            std::cout <<
                "DONE COMMAND\n"
                "Usage:\n"
                "todo -d <id>\n\n"
                "Description:\n"
                "Marks a task as completed.\n\n"
                "Arguments:\n"
                "id    The ID of the task to mark as done\n\n"
                "Example:\n"
                "todo -d 2\n";
        }
        else if (command=="edit" || command=="e") {
            std::cout <<
    "EDIT COMMAND\n"
    "Usage:\n"
    "todo -e <id> <priority>\n\n"
    "Description:\n"
    "Changes the priority of an existing task.\n\n"
    "Arguments:\n"
    "id        The ID of the task to edit\n"
    "priority  New priority: low, medium, high\n\n"
    "Example:\n"
    "todo -e 3 high\n";
        }
        else if (command=="notify" || command=="n") {
            std::cout <<
    "NOTIFY COMMAND\n"
    "Usage:\n"
    "todo -n [--force]\n\n"
    "Description:\n"
    "Shows a desktop popup listing all pending HIGH priority tasks.\n"
    "Only the first call of each day shows the popup, so it is safe\n"
    "to run on every login / screen unlock.\n\n"
    "Options:\n"
    "--force, -f   Show the popup even if it was already shown today\n\n"
    "Example:\n"
    "todo -n\n";
        }
        else {
            std::cout << "Unknown help topic. Use:\n";
            std::cout << "todo -h add|remove|list|done|edit|notify\n";
        }
    }
    }
void App::handleAdd(int argc, char* argv[]) {
    std::string description;
    std::string prioritystring;
    Task::Priority priority = Task::Priority::LOW;
    if (argc < 3) {
        std::cout << BLUE "📝 Add New Task\n" RESET;
        std::cout << "Enter description: ";
        std::getline(std::cin, description);

        if (description.empty()) {
            std::cout << RED "❌ Description cannot be empty\n" RESET;
            return;
        }
        std::cout << "Enter priority (low/medium/high) [default: low]: ";
        std::getline(std::cin, prioritystring);
        if (!prioritystring.empty()) {
            priority = Task::parsePriority(prioritystring);
        }
    } else {
        for (int i = 2; i < argc; i++) {
            std::string arg = argv[i];
            if (arg == "low" || arg == "medium" || arg == "high") {
                priority = Task::parsePriority(arg);
            } else {
                if (!description.empty()) description += " ";
                description += arg;
            }
        }
    }
    todo.addTask(description, priority);
    std::cout << GREEN "✅ Task added: " RESET << description << "\n";
}

void App::handleList(int argc,char* argv[]) {
    Task::Priority priorityFilter = Task::Priority::HIGH;
    bool showPending = false;
    bool showDone = false;
    bool filterByPriority = false;

    for (int i = 2; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--pending" || arg == "-p") {
            showPending = true;
        } else if (arg == "--done" || arg == "-d") {
            showDone = true;
        } else if (arg == "--high") {
            priorityFilter = Task::Priority::HIGH;
            filterByPriority = true;
        } else if (arg == "--medium") {
            priorityFilter = Task::Priority::MEDIUM;
            filterByPriority = true;
        } else if (arg == "--low") {
            priorityFilter = Task::Priority::LOW;
            filterByPriority = true;
        }
    }
    std::cout << "\n";
    std::cout << todo.showAllTasks(showPending, showDone, filterByPriority, priorityFilter) << std::endl;
    std::cout << "\n";
}

void App::handleDone(int argc, char* argv[]) {
    int id;
    try {
        id = std::stoi(argv[2]);
    }
    catch (const std::invalid_argument&) {
        std::cout << RED "❌ Invalid ID: not a number\n" RESET;
        return;
    }
    catch (const std::out_of_range&) {
        std::cout << RED "❌ ID out of range\n" RESET;
        return;
    }

    if (todo.findById(id)) {
        todo.markTaskDone(id);
        std::cout << GREEN "✅ Task " << id << " marked as done!\n" RESET;
    } else {
        std::cout << RED "❌ No task with ID " << id << "\n" RESET;
    }
}

void App::handleRemove(int argc, char* argv[]) {
    int id;
    try {
        id = std::stoi(argv[2]);
    }
    catch (const std::invalid_argument&) {
        std::cout << RED "❌ Invalid ID: not a number\n" RESET;
        return;
    }
    catch (const std::out_of_range&) {
        std::cout << RED "❌ ID out of range\n" RESET;
        return;
    }

    if (todo.findById(id)) {
        todo.removeTask(id);
        std::cout << GREEN "✅ Task removed\n" RESET;
    } else {
        std::cout << RED "❌ No task with ID " << id << "\n" RESET;
    }
}

void App::handleEdit(int argc, char* argv[]) {
    if (argc < 4) {
        std::cout << RED "❌ Usage: todo -e <id> <priority>\n" RESET;
        return;
    }
    int id;
    try {
        id = std::stoi(argv[2]);
    }
    catch (const std::invalid_argument&) {
        std::cout << RED "❌ Invalid ID: not a number\n" RESET;
        return;
    }
    catch (const std::out_of_range&) {
        std::cout << RED "❌ ID out of range\n" RESET;
        return;
    }

    std::string priorityStr = argv[3];
    if (priorityStr != "low" && priorityStr != "medium" && priorityStr != "high") {
        std::cout << RED "❌ Invalid priority. Use: low, medium, high\n" RESET;
        return;
    }

    if (!todo.findById(id)) {
        std::cout << RED "❌ No task with ID " << id << "\n" RESET;
        return;
    }

    Task::Priority newPriority = Task::parsePriority(priorityStr);
    todo.editTaskPriority(id, newPriority);
    std::cout << GREEN "✅ Task " << id << " priority updated to " RESET
              << YELLOW << priorityStr << RESET << "\n";
}

static std::filesystem::path notifyStampPath() {
    std::filesystem::path stateDir;
    if (const char* xdg = std::getenv("XDG_STATE_HOME"); xdg && *xdg) {
        stateDir = xdg;
    } else if (const char* home = std::getenv("HOME")) {
        stateDir = std::filesystem::path(home) / ".local/state";
    } else {
        throw std::runtime_error("Cannot determine HOME directory");
    }
    return stateDir / "todo-app" / "last-notify";
}

static std::string today() {
    std::time_t now = std::time(nullptr);
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", std::localtime(&now));
    return buffer;
}

void App::handleNotify(int argc, char* argv[]) {
    bool force = false;
    for (int i = 2; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--force" || arg == "-f") force = true;
    }

    auto stampPath = notifyStampPath();
    std::string date = today();
    if (!force) {
        std::ifstream stamp(stampPath);
        std::string lastDate;
        if (stamp >> lastDate && lastDate == date) {
            return;
        }
    }

    std::vector<Task> tasks = todo.pendingTasks(Task::Priority::HIGH);
    if (!tasks.empty()) {
        std::string title = "🔥 " + std::to_string(tasks.size()) + " high priority task"
                            + (tasks.size() == 1 ? "" : "s") + " for today";
        std::string body;
        for (const auto& task : tasks) {
            if (!body.empty()) body += "\n";
            body += "• #" + std::to_string(task.getId()) + " " + task.getDescription();
        }

        // Spawn notify-send directly (no shell) so task text is never interpreted as a command.
        // Critical urgency keeps the popup on screen until it is dismissed.
        const char* args[] = {"notify-send", "--app-name=Todo", "--urgency=critical",
                              "--icon=view-task", title.c_str(), body.c_str(), nullptr};
        pid_t pid;
        if (posix_spawnp(&pid, "notify-send", nullptr, nullptr,
                         const_cast<char* const*>(args), environ) != 0) {
            std::cout << RED "❌ Could not run notify-send (is libnotify installed?)\n" RESET;
            return;
        }
        int status = 0;
        waitpid(pid, &status, 0);
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            std::cout << RED "❌ notify-send failed\n" RESET;
            return;
        }
    }

    std::filesystem::create_directories(stampPath.parent_path());
    std::ofstream(stampPath) << date << "\n";
}