#include <nodepp/nodepp.h>
#include <jit/exec.h>

using namespace nodepp;

void onMain() {

    string_t code = "\x48\x89\xf8\x48\x01\xf0\xc3";
    nodepp::exec_t jit( code );

    int result = jit.emit<int>( 5, 10 );
    console::log( "<>", result );
    
}