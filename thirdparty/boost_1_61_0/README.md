# boost

## How to extract needed parts of boost

1. build bjam

        cd tools/build
        ./bootstrap.sh

2. build bcp

        cd tools/bcp
        ../build/bjam .

    Then, "bcp" lies in a directory like this.

        bin.v2/tools/bcp/gcc-4.9.4/release/link-static

3. use bcp to extract needed parts

        mkdir needed
        ./bcp \
            algorithm/string.hpp \
            asio.hpp \
            bind.hpp \
            filesystem.hpp \
            foreach.hpp \
            random.hpp \
            regex.hpp \
            scoped_ptr.hpp \
            thread.hpp \
            unordered_map.hpp \
            unordered_set.hpp \
            needed

    "needed" is what we want.

## How to get the compilation flags

Windows with MSVC

    bjam.exe address-model=64 debug-symbols=off link=static runtime-link=shared threading=multi toolset=msvc variant=release --with-atomic --with-date_time --with-filesystem --with-regex --with-system --with-thread -n

Linux with GCC

    ./bjam address-model=64 debug-symbols=off link=static runtime-link=shared threading=multi toolset=gcc variant=release --with-atomic --with-date_time --with-filesystem --with-regex --with-system --with-thread -n
