# Reaction-Reef-Game
Its a two player game.Dive into Reaction Reef, a vibrant reflex-based game where glowing symbols appear from the deep. React fast, press the correct keys, and prove your lightning-speed focus before the reef overwhelms you.



# 🎮 Reaction Reef Game (C++)

A console-based reflex and reaction speed game implemented in C++.
The game challenges players to quickly press the correct keys before symbols disappear. It features colorful console graphics, dynamic symbol movement, score tracking, and fast-paced gameplay.

---

## 📂 File Structure

Before compiling, ensure your code is saved into the following **three** specific files in the same folder:

1. **`Header.h`**
   *Contains structure definitions (such as `Symbol`), global variables, and function declarations.*

2. **`ReactionReef.cpp`** (or `functions.cpp` if that’s your file name)
   *Contains the core game logic, symbol generation, movement mechanics, scoring system, and graphics rendering.*

3. **`main.cpp`**
   *Contains the `main()` function, game initialization, and main game loop.*

---

## 💻 How to Run in VS Code

### ✅ Prerequisites

* You must have a C++ compiler installed (MinGW / G++).
* All 3 files (`Header.h`, `ReactionReef.cpp`, `main.cpp`) must be in the same folder.

### ▶ Steps

1. Open **Visual Studio Code**.
2. Open the folder containing your three files.
3. Open a **New Terminal**:

   * Right-click inside `main.cpp` → Click **Run File**
     OR
   * Click **Terminal → New Terminal**
   * Make sure the terminal directory matches your project folder.

If you get this error:

```
collect2.exe: error: ld returned 1 exit status
```

It means the files are compiled separately. You must compile them together.

### 🔧 Compile Command

```
g++ *.cpp -o main
```

OR

```
g++ main.cpp ReactionReef.cpp -o main
```

### ▶ Run the Game

```
main
```

OR (for some systems)

```
./main
```

---

## 💻 How to Run in Dev-C++

Since this project uses multiple files, you must create a **Project** so the compiler links all files together.

### ▶ Steps

1. Open **Dev-C++**.
2. Go to **File → New → Project**.
3. Select **Console Application**.
4. Choose **C++ Project**.
5. Name the project (e.g., `ReactionReef`) and click **OK**.
6. Remove the auto-generated `main.cpp`.
7. Right-click project name → **Add to Project**.
8. Add:

   * `Header.h`
   * `ReactionReef.cpp`
   * `main.cpp`
9. Press **F11** or go to **Execute → Compile & Run**.

---

## 🎮 How to Play

1. **Start the Game:**
   The reef environment initializes with animated symbols.

2. **Objective:**
   React quickly and press the correct key corresponding to the appearing symbol.

3. **Gameplay Mechanics:**

   * Symbols appear dynamically on screen.
   * You must press the correct key before time runs out.
   * Each correct response increases your score.
   * Wrong or delayed responses reduce lives.

4. **Winning Condition:**

   * Achieve the highest score possible before losing all lives.
   * The game ends when lives reach zero.

---

## ⚡ Game Features

* 🎨 Colored console graphics
* 🎲 Random symbol generation
* ⚡ Fast-paced reflex gameplay
* 📊 Score tracking system
* ❤️ Life/health system
* 🕹 Real-time keyboard interaction

---

If you want, I can also make a ✨ GitHub-ready polished version with badges, emojis aligned properly, and a cool tagline like:

> *“Where reflex meets chaos beneath the cosmic reef.”* 🌊⚡

