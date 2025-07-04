# virtual-assistant
Author: Chung Duc Nguyen Dang
This is an project about virtual assistant.

The requirements are:

- CMake 3.11 or better; 3.14+ highly recommended.
- A C++17 compatible compiler
- The espeak, mbrola, mbrola-us1 libararies 
- Git
- Doxygen (optional)
- Ollama

To configure:

```bash
cmake -S . -B build
```

Add `-GNinja` if you have Ninja.

To build:

```bash
cmake --build build
```

To test (`--target` can be written as `-t` in CMake 3.15+):

```bash
cmake --build build --target test
```

To build docs (requires Doxygen, output in `build/docs/html`):

```bash
cmake --build build --target docs
```

To use an IDE, such as Xcode:

```bash
cmake -S . -B xbuild -GXcode
cmake --open xbuild
```

The CMakeLists show off several useful design patterns for CMake.
