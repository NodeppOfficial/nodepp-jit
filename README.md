# Nodepp-JIT
The Nodepp project provides a C++ library for advanced runtime code manipulation and execution. This library offers two core components: one for dynamic linking of shared libraries and another for executing raw machine code in memory.

## dll_t: Dynamic Library Loader
The dll_t class serves as a C++ wrapper for dynamic link library (DLL) functions on Unix-like operating systems. It encapsulates the low-level POSIX functions such as dlopen, dlsym, and dlclose, providing a type-safe and object-oriented interface.

### create a dll
```cpp
extern "C" { int add( int a, int b ){ return a + b; } }
// compile (Linux)  : g++ -shared -fPIC -o dll.so dll.cpp
// compile (Windows): g++ -shared -o dll.dll dll.cpp
```


```cpp
#include <nodepp/nodepp.h>
#include <jit/dll.h>

using namespace nodepp;

void onMain() {

    dll_t dll( "./dll.so" );
    auto out = dll.emit<int>( "add", 10, 20 );
    console::log( "<>", out );

}
```

## Code Execution: 
Create and execute machine code at runtime, a technique commonly used in JIT compilers.
```cpp
#include <nodepp/nodepp.h>
#include <jit/exec.h>

using namespace nodepp;

void onMain() {

    string_t code = "\x48\x89\xf8\x48\x01\xf0\xc3";
    nodepp::exec_t jit( code );

    int result = jit.emit<int>( 5, 10 );
    console::log( "<>", result );
    
}
```