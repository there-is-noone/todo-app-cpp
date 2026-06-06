# Todo CLI App

A lightweight command-line todo list application in modern C++. Manage tasks by priority with persistent JSON storage.

## Features

- 🎯 Priority-based task management (HIGH/MEDIUM/LOW)
- 📋 Filter tasks by status (`--pending`, `--done`) or priority
- ✏️ Full CRUD operations (add, list, edit, remove, done)
- 💾 Persistent JSON storage
- 🎨 Color-coded output with clean formatting

## Quick Start

### Build

```bash
git clone https://github.com/yourusername/todo-app.git
cd todo-app
mkdir -p cmake-build-debug && cd cmake-build-debug
cmake .. && cmake --build .
```

### Install Globally

```bash
sudo cp cmake-build-debug/todo /usr/local/bin/todo
```

Now run from anywhere:
```bash
todo -l
todo -a "Buy milk" high
todo -h
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
---
## Data Storage

Tasks saved to `data/tasks.json`:
```json
[
  {"id": 1, "description": "Study", "priority": "high", "done": false},
  {"id": 2, "description": "Coffee", "priority": "low", "done": true}
]
```

## Architecture

**Classes:**
- `Task` - Individual todo item (ID, description, priority, done status)
- `TodoList` - Collection management, filtering, sorting
- `App` - CLI interface and command parsing
- `Storage`/`JsonStorage` - Persistence abstraction

**Patterns:**
- RAII for memory management
- Strategy pattern for storage abstraction
- Move semantics (C++17)
- Const-correctness throughout

## Requirements

- C++17+
- CMake 3.10+ (or Makefile alternative)
- Linux/macOS/Windows

## Build Without CMake

Create `Makefile`:
```makefile
CXX = g++
CXXFLAGS = -std=c++17 -Wall
SOURCES = src/main.cpp src/App.cpp src/TodoList.cpp src/Task.cpp src/JsonStorage.cpp src/Storage.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = todo

all: $(TARGET)
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) -Iinclude
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -Iinclude
clean:
	rm -f $(OBJECTS) $(TARGET)
install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/
.PHONY: all clean install
```

Then:
```bash
make && sudo make install
```

## Example Session

```bash
$ todo -a "Study for exam" high
✅ Task added: Study for exam

$ todo -a "Buy groceries" low
✅ Task added: Buy groceries

$ todo -l
● #1 Study for exam [⏳ TODO]
● #2 Buy groceries [⏳ TODO]

Shown: 2 | Done: 0 | Pending: 2

$ todo -d 1
✅ Task 1 marked as done!

$ todo -l --pending
● #2 Buy groceries [⏳ TODO]

Shown: 1 | Done: 0 | Pending: 1
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
### Technical Highlights

- Modern C++ (C++17) with move semantics
- RAII for automatic resource management
- Minimal dependencies (single header json library)
- Polymorphic storage abstraction
- Error handling with user-friendly messages
- UTF-8 support for international text

---
## Getting Help

- **First time using the app?** Run `./todo --help` for interactive guide
- **Forgot a command?** Try `./todo -h add` (or any command name)
- **Issues?** Check that the `data/` directory exists and is writable
- **Lost data?** Check `data/tasks.json` - it's just plain JSON!



## University Assignment

✅ Presented to class  
✅ External library integration (nlohmann/json)  
✅ Complete, coherent implementation  
✅ Comprehensive documentation  
✅ GitHub repository



---

**Ready to use. A clean CLI todo app.** 🚀

Last updated: 6.06.2026