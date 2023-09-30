# cppcon2023
Overview on how to constuct a plugin based system in C++

## Build project
To build the plugin manager, run the following commands:
Unix:
```
cmake -S . -B build
cmake --build build
ctest --test-dir build
```

Windows: TODO
MacOS: TODO

## Running the example plugin manager
To Run the example plugin manager, run the following command from the build directory you created above:
```
./plugin_cpp
```
The expected output should be print the message `I am planning motion simply`.

## Inspect library symbols in Linux
To inspect the symbols of a library in Linux, run the follow command
```
nm -gD <Path To Library Artifact>
```
If you wish to unmangle the cpp symbols, add the `-C` flag
```
nm -gDC <Path To Library Artifact>
```
