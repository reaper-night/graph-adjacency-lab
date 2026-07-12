# C Project Template

A modern C language project template with common directory structure.

## Features

- **Modular Architecture**: Clean separation of source code and headers
- **Logging System**: Custom logger with multiple levels (DEBUG, INFO, WARN, ERROR)
- **Utility Functions**: Common utility functions (math, comparison, swap)
- **Build Support**: Makefile, CMakeLists.txt, and Windows batch scripts
- **Unit Testing**: Integrated test framework

## Project Structure

```
c_project/
├── src/              # Source code
│   ├── main.c        # Main entry point
│   ├── logger.c      # Logging module implementation
│   └── utils.c       # Utility functions implementation
├── include/          # Header files
│   ├── logger.h      # Logging module interface
│   └── utils.h       # Utility functions interface
├── tests/            # Test files
│   └── test_utils.c  # Unit tests for utils module
├── lib/              # External libraries
├── docs/             # Documentation
├── build.bat         # Windows build script
├── clean.bat         # Windows clean script
├── Makefile          # Linux/Mac build script
├── CMakeLists.txt    # CMake configuration
└── .gitignore        # Git ignore rules
```

## Usage

### Windows

```cmd
build.bat          # Build and run
clean.bat          # Clean build files
```

### Linux / macOS

```bash
make               # Build (release)
make debug         # Build (debug)
make clean         # Clean build files
make test          # Build and run tests
```

### CMake

```bash
mkdir build && cd build
cmake ..
make
```

## Modules

### Logger Module

- `logger_init()` - Initialize logger
- `logger_set_level(level)` - Set log level
- `LOG_DEBUG()`, `LOG_INFO()`, `LOG_WARN()`, `LOG_ERROR()` - Log macros

### Utils Module

- `utils_add(a, b)` - Addition
- `utils_subtract(a, b)` - Subtraction
- `utils_multiply(a, b)` - Multiplication
- `utils_divide(a, b)` - Division (with zero protection)
- `utils_swap(a, b)` - Swap values
- `utils_max(a, b)` - Maximum value
- `utils_min(a, b)` - Minimum value