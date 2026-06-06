# Todo CLI App

A lightweight, feature-rich command-line todo list application written in modern C++. Organize your tasks by priority, mark them complete, and manage your workflow directly from the terminal.

## Features

✨ **Priority-based task management**
- Add tasks with LOW, MEDIUM, or HIGH priority
- Tasks automatically sorted by priority (HIGH first)
- Visual color-coded priority indicators

📋 **Flexible filtering**
- View all tasks or filter by status (`--pending`, `--done`)
- Filter by priority (`--high`, `--medium`, `--low`)
- Combine filters for precise task management

✏️ **Full CRUD operations**
- **Add** new tasks: `./todo -a "task description" [priority]`
- **List** all tasks with smart filtering
- **Edit** task priority on the fly
- **Remove** tasks by ID
- **Mark as done** to track completion

💾 **Persistent storage**
- All tasks saved to JSON file (`data/tasks.json`)
- Survives application restarts
- Easy to backup and share

🎨 **User-friendly interface**
- Clean, minimal terminal output
- Color-coded priority levels (Red/Yellow/Gray)
- Built-in help system: `./todo -h [command]`
- Responsive summary statistics

## Requirements

- **C++17** or later
- **CMake 3.10+**
- **Linux/macOS/Windows** (any system with a C++ compiler)
- No external dependencies (uses only standard library)

## Installation & Build

### Clone the repository
```bash
git clone https://github.com/yourusername/todo-app.git
cd todo-app
```

### Build from source
```bash
mkdir -p cmake-build-debug
cd cmake-build-debug
cmake ..
cmake --build .
```

### Run the application
```bash
./todo --help          # Show help menu
./todo -l              # List all tasks
./todo -a "Buy milk" high   # Add a task
```

## Usage Guide

### Basic Commands

#### Add a task
```bash
./todo -a "Buy groceries"              # Default: LOW priority
./todo -a "Finish project" high        # HIGH priority
./todo -a "Read a book" medium         # MEDIUM priority

# Interactive mode (no arguments)
./todo -a
# Prompts:
# Enter description: Study for exam
# Enter priority (low/medium/high): medium
```

#### List tasks
```bash
./todo -l                   # Show all tasks
./todo -l --pending (-p)    # Show only incomplete tasks
./todo -l --done (-d)       # Show only completed tasks
./todo -l --high            # Show only HIGH priority tasks
./todo -l --medium          # Show only MEDIUM priority tasks
./todo -l --low             # Show only LOW priority tasks

# Combine filters
./todo -l --high --pending  # HIGH priority tasks that are TODO
./todo -l --medium --done   # MEDIUM priority tasks that are DONE
```

#### Mark task as done
```bash
./todo -d 1                 # Mark task #1 as done
./todo --done 3             # Mark task #3 as done
```

#### Edit task priority
```bash
./todo -e 2 high            # Change task #2 to HIGH priority
./todo --edit 5 low         # Change task #5 to LOW priority
```

#### Remove a task
```bash
./todo -r 1                 # Delete task #1
./todo --remove 3           # Delete task #3
```

### Command Shortcuts

All commands support both long and short forms:

| Command    | Short | Purpose                           |
|------------|-------|-----------------------------------|
| `--add`    | `-a`  | Add a new task                    |
| `--list`   | `-l`  | Display tasks                     |
| `--done`   | `-d`  | Mark task as complete             |
| `--edit`   | `-e`  | Edit task priority                |
| `--remove` | `-r`  | Remove a task                     |
| `--help`   | `-h`  | Show help information             |

### Help System

Get detailed help for any command:
```bash
./todo -h              # Main help menu
./todo -h add          # Help for add command (or: ./todo -h a)
./todo -h list         # Help for list command (or: ./todo -h l)
./todo -h edit         # Help for edit command (or: ./todo -h e)
./todo -h done         # Help for done command (or: ./todo -h d)
./todo -h remove       # Help for remove command (or: ./todo -h r)
```

## Example Workflow

```bash
# Start fresh
./todo -a "Study for C++ exam" high
./todo -a "Buy coffee" low
./todo -a "Finish project report" high
./todo -a "Read documentation" medium

# View all tasks (sorted by priority)
./todo -l

# View only pending HIGH priority tasks
./todo -l --high --pending

# Mark task #1 as done
./todo -d 1

# Change priority of task #4
./todo -e 4 high

# View completed tasks
./todo -l --done

# Remove a task
./todo -r 2

# Final summary
./todo -l
```

## Output Example

```
● #1 Study for C++ exam [⏳ TODO]
● #3 Finish project report [⏳ TODO]
● #4 Read documentation [✓ DONE]
● #2 Buy coffee [⏳ TODO]

━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Shown: 4 | Done: 1 | Pending: 3
```

## Project Architecture

### File Structure
```
todo-app/
├── src/
│   ├── main.cpp          # Application entry point
│   ├── App.cpp           # Command handling logic
│   ├── TodoList.cpp      # Task list management
│   ├── Task.cpp          # Individual task operations
│   ├── JsonStorage.cpp   # JSON persistence
│   └── Storage.cpp       # Storage interface
├── include/
│   ├── App.hpp
│   ├── TodoList.hpp
│   ├── Task.hpp
│   ├── JsonStorage.hpp
│   └── Storage.hpp
├── data/
│   └── tasks.json        # Task database (auto-created)
├── external/
│   └── json.hpp          # nlohmann/json library
├── CMakeLists.txt
└── README.md
```

### Design Patterns Used

- **RAII** (Resource Acquisition Is Initialization) - Memory management
- **Strategy Pattern** - Storage abstraction (polymorphic Storage interface)
- **MVC-like** - Separation of App (controller), TodoList (model), and I/O logic
- **Move Semantics** - Efficient resource handling in C++11+

### Core Classes

**Task** - Represents a single todo item
- Properties: ID, description, priority, completion status
- Methods: getters, setters, priority parsing

**TodoList** - Manages collection of tasks
- Methods: add, remove, edit, filter, sort
- Handles persistence through Storage interface

**App** - Command-line interface and argument parsing
- Methods: handle user commands, display help
- Manages task creation, deletion, listing

**JsonStorage** - Persistent storage implementation
- Serializes/deserializes tasks to/from JSON
- Automatic file creation and management

## Data Storage

Tasks are stored in `data/tasks.json`:

```json
[
  {
    "id": 1,
    "description": "Study for C++ exam",
    "priority": "high",
    "done": false
  },
  {
    "id": 2,
    "description": "Buy coffee",
    "priority": "low",
    "done": true
  }
]
```

The JSON format ensures:
- Easy human readability
- Portability across systems
- Simple backup and migration
- Compatibility with other tools

## Error Handling

The application includes robust error handling for:
- Invalid user input (non-numeric IDs)
- Non-existent tasks
- Malformed priority values
- File I/O errors
- Out-of-range IDs

All errors provide clear, actionable messages to the user.

## Future Enhancements

Potential features for future versions:
- 📅 Due dates and deadline tracking
- 🏷️ Task categories and tags
- 🔍 Full-text search functionality
- ⏰ Time tracking and productivity stats
- 🌐 Cloud sync support
- 🎨 Configurable themes and colors
- 📊 Task history and statistics

## Technical Highlights

✅ **Modern C++ (C++17)**
- Move semantics for efficiency
- Auto type deduction
- Smart use of std::vector and algorithms

✅ **External Library Integration**
- nlohmann/json for robust JSON handling
- Clean abstraction around third-party code

✅ **Best Practices**
- Const-correctness throughout
- Proper memory management (RAII)
- Separation of concerns
- User-friendly error messages

✅ **Code Quality**
- Consistent naming conventions
- Modular class design
- Clear method documentation
- Minimal dependencies

## Building & Deployment

### Clean build
```bash
cd cmake-build-debug
rm -rf *
cd ..
cmake --build cmake-build-debug
```

### Run tests
```bash
./cmake-build-debug/todo -h    # Verify help works
./cmake-build-debug/todo -l    # Verify list works
```

## License

This project is provided as-is for educational purposes.

## Author

**Kamil** - Created as a university C++ project demonstrating:
- Modern C++ programming practices
- CLI application design
- Data persistence and JSON handling
- Software architecture principles

---

## Getting Help

- **First time using the app?** Run `./todo --help` for interactive guide
- **Forgot a command?** Try `./todo -h add` (or any command name)
- **Issues?** Check that the `data/` directory exists and is writable
- **Lost data?** Check `data/tasks.json` - it's just plain JSON!

## University Assignment

This project fulfills the requirements for a custom software engineering assignment:
- ✅ Presented to class
- ✅ Uses external library (nlohmann/json)
- ✅ Complete, coherent implementation
- ✅ Comprehensive README and in-app help
- ✅ Code hosted on GitHub

---

**Enjoy organizing your tasks! 🚀**

*Last Updated: June 2024*
