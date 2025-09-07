# Implicit Constructor Detector (LLVM Pass)

This project implements a custom **LLVM FunctionPass** that detects **implicit constructor calls** in C++ code.  
It inspects LLVM IR and identifies whether a constructor call is:

- **Default Constructor** – No arguments  
- **Copy Constructor** – Single pointer argument  
- **Parameterized Constructor** – Any other argument pattern  

The pass is demonstrated using a sample `test.cpp` program.

---

## 📂 Project Structure

```

.
├── ImplicitCtorPass.cpp   # LLVM pass implementation
├── test.cpp               # Sample C++ program with an implicit constructor call
├── test.bc                # LLVM bitcode generated from test.cpp

````

---

## 🚀 Getting Started

### 1. Build with CMake (Recommended)

Create a file named `CMakeLists.txt` with the following content:

```cmake
cmake_minimum_required(VERSION 3.13)
project(ImplicitCtorPass LANGUAGES CXX)

find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_library(ImplicitCtorPass SHARED ImplicitCtorPass.cpp)

# Disable RTTI (required for LLVM passes)
target_compile_options(ImplicitCtorPass PRIVATE -fno-rtti)

# Link with LLVM libraries
llvm_map_components_to_libnames(llvm_libs core support irreader)
target_link_libraries(ImplicitCtorPass PRIVATE ${llvm_libs})
````

Then build the pass:

```bash
mkdir build && cd build
cmake ..
make
```

This generates `libImplicitCtorPass.so` (shared object for the pass).

---

### 2. Generate LLVM Bitcode

Compile the `test.cpp` into LLVM bitcode (`.bc` file):

```bash
clang -emit-llvm -c ../test.cpp -o test.bc
```

---

### 3. Run the Pass

Use `opt` to apply the pass to the generated bitcode:

```bash
opt -load ./libImplicitCtorPass.so -implicit-ctor < test.bc > /dev/null
```

---

## 📝 Example Output

For the included `test.cpp`:

```cpp
class MyClass {
public:
    MyClass() { std::cout << "Constructor called\n"; }
};

void testFunction() {
    MyClass obj;  // Implicit constructor invocation
}
```

When run through the pass, the output will be:

```
Implicit constructor detected: _ZN7MyClassC1Ev
Type: Default Constructor
```

---

## ⚡ Requirements

* LLVM/Clang (10.0+)
* CMake (3.13+)
* g++/clang++ compiler

---

## 📌 Notes

* This pass is **analysis only**; it does not modify the IR.
* It uses LLVM’s name mangling convention (`C1` for constructors) to detect constructor calls.
* Works on simple examples but may need refinement for more complex code.

---

## 📖 References

* [Writing an LLVM Pass](https://llvm.org/docs/WritingAnLLVMPass.html)
* [opt Command Guide](https://llvm.org/docs/CommandGuide/opt.html)

---

## 👩‍💻 Author

**Khushi Gupta**
Enthusiastic computer science student passionate about compilers, program analysis, and software engineering.


 
