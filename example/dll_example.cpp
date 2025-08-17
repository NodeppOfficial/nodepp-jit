#include <nodepp/nodepp.h>
#include <jit/dll.h>

using namespace nodepp;

void onMain() {

    dll_t dll( "./main.so" );
    auto out = dll.emit<int>( "add", 10, 20 );
    console::log( "<>", out );

}