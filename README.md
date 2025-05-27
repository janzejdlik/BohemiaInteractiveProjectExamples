# Pomodoro Timer for macOS

A simple GTK-based Pomodoro timer application that helps you manage work/break intervals.

## Prerequisites

- macOS (tested on macOS Monteray, Intel based Mac)
- Homebrew package manager
- Xcode Command Line Tools

## Installation

### 1. Install Homebrew (if you don't have it)

Open Terminal and run:
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

### 2. Install GTK+3

First, make sure you have GTK installed on your Mac. You can install it using Homebrew:

```bash
brew install gtk+3
```

### 3. Save the source code

Save the code to a file named pomodoro.cpp

### 4. Compile the program

Compile with the following command:

```bash
g++ -std=c++11 pomodoro.cpp -o pomodoro `pkg-config --cflags --libs gtk+-3.0`
```

### 5. Run the program

Execute the compiled binary with:

```bash
./pomodoro
```
