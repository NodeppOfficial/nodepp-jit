#include <nodepp/nodepp.h>
#include <jit/exec.h>

using namespace nodepp;

void onMain() {

    string_t code = fs::read_file("code.bin");
    exec_t jit( code );

    int result = jit.emit<int>( 5, 10 );
    console::log( "<>", result );
    
}