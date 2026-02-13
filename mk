
cmake -B build

make -C build
make -C build install 

"./build/release/bin/test"
