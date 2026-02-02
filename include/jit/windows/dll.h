/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOfficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_WINDOWS_DLL_JIT
#define NODEPP_WINDOWS_DLL_JIT

/*────────────────────────────────────────────────────────────────────────────*/

#include <windows.h>
#include <libloaderapi.h>

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { class dll_t {
protected:

    struct NODE {
        HMODULE     mem;
        ulong size  = 0;
        bool  state = 0;
    };  ptr_t<NODE> obj;

public:

   ~dll_t() { if( obj.count()>1 ){ return; } FreeLibrary(obj->mem); }

    dll_t( string_t name ) : obj( new NODE() ){

        obj->mem = LoadLibraryA( name.get() );

        if( !obj->mem )
          { throw except_t( "virtual dlopen failed" ); }

    }

    template< class T, class... V >
    T emit( string_t name, V... args ) const {
        if( obj->mem == nullptr ){ throw except_t( "invalid callback" ); }
        T (*func)(V...)=(T(*)(V...))( GetProcAddress(obj->mem,name.get()) );
        return func( args... );
    }

    dll_t() noexcept : obj( new NODE() ) {}

}; }

/*────────────────────────────────────────────────────────────────────────────*/

#endif

/*────────────────────────────────────────────────────────────────────────────*/