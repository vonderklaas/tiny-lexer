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
bld/func `example`
```