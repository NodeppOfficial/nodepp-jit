/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOfficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_POSIX_EXEC_JIT
#define NODEPP_POSIX_EXEC_JIT

/*────────────────────────────────────────────────────────────────────────────*/

#include <sys/mman.h>

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { class exec_t {
protected:

    struct NODE {
        void* mem   = nullptr;
        ulong size  = 0;
        bool  state = 0;
    };  ptr_t<NODE> obj;

public:

   ~exec_t() { if( obj.count()>1 ){ return; } munmap( obj->mem, obj->size ); }

    exec_t( string_t code ) : obj( new NODE() ){

        auto size= sysconf(_SC_PAGESIZE);
        obj->size= (code.size()+size-1) &~ (size-1);

        obj->mem = mmap( NULL, obj->size, PROT_READ | PROT_WRITE,
        /*------------*/ MAP_PRIVATE | MAP_ANONYMOUS, -1, 0 );

        if( obj->mem == MAP_FAILED )
          { throw except_t( "virtual mmap failed" ); }

        memcpy( obj->mem, code.get(), code.size() );

        if( mprotect( obj->mem, obj->size, PROT_READ | PROT_EXEC )==-1 )
          { throw except_t( "virtual mprotect failed" ); }

    }

    template< class T, class... V >
    T emit( V... args ) const {
        if( obj->mem == nullptr ){ throw except_t( "invalid callback" ); }
        T (*func)(V...) = (T(*)(V...))( obj->mem ); return func( args... );
    }

    exec_t() noexcept : obj( new NODE() ) {}

}; }

/*────────────────────────────────────────────────────────────────────────────*/

#endif

/*────────────────────────────────────────────────────────────────────────────*/