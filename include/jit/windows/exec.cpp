/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOfficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#pragma once

namespace nodepp { class exec_t {
protected:

    struct NODE {
        void* mem   = nullptr;
        ulong size  = 0;
        bool  state = 0;
    };  ptr_t<NODE> obj;

public:

    virtual ~exec_t() { if( obj.count()>1 ){ return; } VirtualFree( obj->mem, 0, MEM_RELEASE ); }

    exec_t( string_t code ) : obj( new NODE() ){

        SYSTEM_INFO sysInfo; GetSystemInfo( &sysInfo );
        auto size= sysInfo.dwPageSize; DWORD protect;
        obj->size= (code.size()+size-1) &~ (size-1);

        obj->mem = VirtualAlloc( NULL, obj->size, MEM_COMMIT | MEM_RESERVE, 
        /*--------------------*/ PAGE_EXECUTE_READWRITE );

        if( obj->mem == NULL )
          { throw except_t( "virtual mmap failed" ); }

        memcpy( obj->mem, code.get(), code.size() );
        
        if( !VirtualProtect( obj->mem, obj->size, PAGE_EXECUTE_READ, &protect ))
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