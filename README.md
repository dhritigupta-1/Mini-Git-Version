# Mini Git Version (C++ Project)

A lightweight Git-like version control system implemented in C++.

---

## 📖 About the Project

**Mini Git Version** is a systems-level C++ project that reimplements the fundamental concepts of a distributed version control system similar to Git.
The project focuses on low-level design, data integrity, and efficient file tracking, demonstrating strong proficiency in C++, algorithms, and software architecture.

It showcases the ability to:

Design complex command-line tools

Implement content-addressable storage using hashing

Manage persistent data structures

Handle file system operations at scale

Build modular, maintainable systems in modern C++

This project is ideal for demonstrating skills relevant to:

Systems programming

Backend development

Developer tools engineering

Software infrastructure

Performance-oriented C++ development

⚖️ How This Differs from Real Git

While inspired by Git, this project is a simplified educational implementation and does not aim to fully replicate Git’s complete functionality.

Key differences include:

🔹 Scope & Complexity

Implements core concepts only

Omits many advanced Git features

Designed for learning rather than production use

🔹 Storage Model

Simplified object storage format

May not use Git’s exact packfile or delta compression mechanisms

Focuses on clarity over maximum efficiency

🔹 Branching & Merging

Limited or simplified branch management

Merge conflict handling may be basic or absent

🔹 Networking

No remote repositories, push/pull, or distributed synchronization

Operates entirely on a local repository

🔹 Performance Optimizations

Does not implement Git’s advanced performance techniques

Prioritizes readability and correctness

🔹 Security & Robustness

Minimal error recovery and edge-case handling

Not hardened for real-world usage

Despite these differences, the project faithfully demonstrates the core principles that make distributed version control systems work, providing valuable insight into Git’s internal design.

---

## 🧰 Prerequisites

* C++17 compatible compiler (GCC / Clang / MSVC)
* CMake (recommended)
* Git
* vcpkg (for dependency management)

---

## 📦 Install vcpkg

### Windows (Recommended)

1. Clone vcpkg:

```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
```

2. Bootstrap vcpkg:

```bash
.\bootstrap-vcpkg.bat
```

3. (Optional but recommended) Enable system integration:

```bash
.\vcpkg integrate install
```

---

### Linux / macOS

```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
```

---

## 📚 Install Required Libraries

Install the dependencies used by this project:

```bash
vcpkg install <package-name>
```

Example:

```bash
vcpkg install fmt
vcpkg install nlohmann-json
```

*(Replace with the actual packages your project uses.)*

---

## 📄 Using vcpkg Manifest Mode (Recommended)

If the project includes a `vcpkg.json` file, simply run:

```bash
vcpkg install
```

vcpkg will automatically install all dependencies listed in the manifest.

---

## 🏗️ Build the Project (CMake)

```bash
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake
cmake --build .
```

Example (Windows):

```bash
cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
```

---

## ▶️ Run

After building:

```bash
./MiniGit
```

(or the generated executable for your platform)

---

## 🧹 Notes

* The `vcpkg/` directory is intentionally ignored in this repository.
* Dependencies can be restored automatically using the steps above.
* This keeps the repository lightweight and reproducible.
