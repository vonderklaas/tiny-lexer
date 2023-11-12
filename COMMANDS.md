This is developed on MacOS in 2023

Have this installed
```
brew install ninja
brew install cmake
```

Build
```
cmake -G Ninja -B bld -DCMAKE_BUILD_TYPE=Release
```

Compile
```
cmake --build bld
```

Run
```
bld/func `tinylang`
```