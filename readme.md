# eg-cpp-library
An example repository for C++ library development using [`clangd`](https://clangd.llvm.org/) to lint/format code, and [`cmake`](https://cmake.org) to configure the build. Doxygen is used to build [documentation](https://mfbolus.github.io/eg-cpp-library/) for this library.

## Example `cmake` development
Probably the best way to develop a C++ project and configure the build is to use `cmake`. It is widely-used, cross-platform, and flexible. The heart of this approach to configuring a build is to develop `CMakeLists.txt` file(s). This project includes a commented, generic example for how to write a C++ library and configure using `cmake`. Armadillo, OpenBLAS, and HDF5 are used in this project to show how to deal with external dependencies. Please see `CMakeLists.txt`, `src/CMakeLists.txt`, and `examples/CMakeLists.txt`.

## `clangd` Setup (e.g., using Sublime Text)
For linting, formatting, autocomplete and more, use `clangd` from LLVM. The directions below are specific to Sublime Text, but it should be easy to set up in VS Code. The latter is a free editor and widely used.

1. Install `clangd` and the rest of `llvm` if you have not already. Make sure `clang-tidy` and `clang-format` are included. I installed llvm-11 via macports package manager on MacOS. Its resources are available at `/opt/local/libexec/llvm-11` if you have used the default macports install prefix. For MacOS, there is also the Homebrew package manager if you prefer that. LLVM should also be available as a package in your Linux distribution's package manager.

2. For `clangd` to know where to look for header files, use `cmake` to configure the project build. While I do not recommend it, for simple projects, you may write line-delimited compiler flags to a file called `compiler_flags.txt` in your project root instead.

 - Here is an example `compiler_flags.txt` for macOS:
 ```shell
-Iinclude
-I/opt/local/include
-I/usr/local/include
-stdlib=libc++
-I/opt/local/libexec/llvm-11/include/c++/v1
-I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1
-I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/local/include
-I/opt/local/libexec/llvm-11/lib/clang/11.0.0/include
-I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include
 ```

 - As mentioned above, a good way to develop a C++ project and configure the build is to use `cmake`. Install this tool, and optionally install the `CMake` Sublime package for syntax highlighting and snippets. Run `cmake` with the `-DCMAKE_EXPORT_COMPILE_COMMANDS=1` option. *n.b.* I hard-coded this option in the `CMakeLists.txt` in this example because I do not know a reason not to do it. This will create a `compile_commands.json` file in the build directory you created for your binaries. You can copy this to your project root for `clangd` to see by default or you can point `clangd` to this build directory using one of its options (see `clangd` settings below). Here is an example for getting the project build setup with `cmake`.
 ```shell
 cd /path/to/this/project
 mkdir build && cd build
 cmake ..
 ```

3. For linting, write a clang-tidy configuration file (`.clang-tidy`), and save it to your project root. See the example here, which I adapted from Google Cloud API repository.

4. For formatting, write clang-format file (`.clang-format`), and save it to your project root. `clang-format` currently supports a few standards including Google, LLVM, Microsoft, Mozilla, etc. You can generate a configuration file from one of these presets with the following command:
```shell
clang-format --style=google --dump-config > .clang-format
```

5. Install Language Server Protocol (LSP) package in Sublime.

6. Enable `clangd` server globally (or just locally) in the LSP package.

7. Use LSP settings similar to this :
```yaml
{
  "clients":
  {
    "clangd":
    {
      "command":
      [
        "/opt/local/libexec/llvm-11/bin/clangd", # insert your clangd here if not already in `PATH`
        "--compile-commands-dir=build", # point clangd to `compile_commands.json` directory
        "--background-index",
        "--cross-file-rename",
        "--header-insertion=none",
        "--fallback-style=google",
        "--clang-tidy",
        "--all-scopes-completion",
        "--completion-style=detailed",
        "--log=verbose",
        "--j=4",
        "--pch-storage=disk",
      ],
      "enabled": true
    },
  },
  "additionalTextEdits": true,
  "log_debug": true,
  "log_server": true,
  "log_stderr": true,
  "log_stdout": true,
}
```

*Now, you should be ready to develop your C++ project with the benefits of an IDE-like experience.*

## (Re)Generate sourcelist before configuring build
For libraries that are built from a large number of source files, it is convenient to use glob pattern matching like `src/*.cpp`, rather than manually listing the source files for the project build target(s). This is especially true as the list of source files changes over the course of project development. `cmake` warns against using their built-in glob matching to get a list of sources.

I have made a simple `generate-lib-sourcelist.sh` shell script that will do this, but you must remember to run it if you have added or renamed source files since the last build. Run this shell script before calling `cmake`. It (re)creates a `src/sourcelist.txt` file.

```shell
cd /path/to/this/project/scripts
./generate-lib-sourcelist.sh
```

## Using a library derived from this template in future projects
Developing a library (rather than executable) implies its use in other programs. Therefore, you need to know how to use it!

For this reason, I have included two examples of how to use this library after installation with `make install`. One of these applies to the case where you are developing a program, whose build is also configured via CMake. Please see `misc/test-cmake-installation` for details. Another of these applies to the scenario where you are developing Makefiles directly and using `pkg-config` to fetch the necessary flags. Similarly, please see `misc/test-pkgconfig-installtion` for more details.
