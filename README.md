# Nodepp-JIT
The Nodepp project provides a C++ library for advanced runtime code manipulation and execution. This library offers two core components: one for dynamic linking of shared libraries and another for executing raw machine code in memory.

## Dependencies & Cmake Integration
```bash
include(FetchContent)

FetchContent_Declare(
	nodepp
	GIT_REPOSITORY   https://github.com/NodeppOfficial/nodepp
	GIT_TAG          origin/main
	GIT_PROGRESS     ON
)
FetchContent_MakeAvailable(nodepp)

FetchContent_Declare(
	nodepp-jit
	GIT_REPOSITORY   https://github.com/NodeppOfficial/nodepp-jit
	GIT_TAG          origin/main
	GIT_PROGRESS     ON
)
FetchContent_MakeAvailable(nodepp-jit)

#[...]

target_link_libraries( #[...]
	PUBLIC nodepp nodepp-jit #[...]
)
```

## dll_t: Dynamic Library Loader
The dll_t class provides a way to load and execute .dll and .so, within your c++ program.

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
The exec_t class provides a way to create and execute machine code at runtime.
```cpp
extern "C" { int add( int a, int b ){ return a + b; } }
// compile : g++ -c -fPIC -o code.o code.cpp ; objcopy -O binary --only-section=.text code.o code.bin
```
```cpp
#include <nodepp/nodepp.h>
#include <jit/exec.h>

using namespace nodepp;

void onMain() {

    string_t code = fs::read_file("code.bin");
    exec_t jit( code );

    int result = jit.emit<int>( 5, 10 );
    console::log( "<>", result );
    
}
```

## License
**Nodepp-jit** is distributed under the MIT License. See the LICENSE file for more details.