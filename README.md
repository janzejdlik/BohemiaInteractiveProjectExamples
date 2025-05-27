# Pomodoro Timer for macOS

A simple GTK-based Pomodoro timer application that helps you manage work/break intervals.

## Installation

## Prerequisites

- macOS (tested on macOS Monteray, Intel based Mac)
- Homebrew package manager
- Xcode Command Line Tools

### 1. Install Homebrew (if you don't have it)

Open Terminal and run:
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

### 2. Requirements

- macOS (tested on macOS Monteray, Intel based Mac)
```bash
brew install gtk+3 pkg-config
```
- Xcode Command Line Tools
```bash
xcode-select --install
```

### 3. Install GTK+3

First, make sure you have GTK installed on your Mac. You can install it using Homebrew:

```bash
brew install gtk+3
```

### 4. Save the source code

Save the code to a file named pomodoro.cpp

### 5. Compile the program

Compile with the following command:

```bash
g++ -std=c++11 pomodoro.cpp -o pomodoro `pkg-config --cflags --libs gtk+-3.0`
```

### 6. Run the program

Execute the compiled binary with:

```bash
./pomodoro
```

### Notes:

If you encounter compilation errors, ensure all dependencies are properly installed

For M1/M2 Macs, you may need to use:

```bash
arch -arm64 brew install gtk+3
```

Make sure the file pomodoro.cpp is in your current working directory when compiling

Enjoy
