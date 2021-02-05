# eg-cpp-library
An example repository for C++ library development using [`clangd`](https://clangd.llvm.org/) to lint code, and `cmake` to configure build.

## `clangd` Setup (using Sublime text editor)
1. Install `clangd` and rest of `llvm` if not already. Make sure `clang-tidy` is included. I installed llvm-11 via macports. Its resources are available at `/opt/local/libexec/llvm-11`.
2. For `clangd` to know where to looks for includes, use `cmake` to build project or (for simple projects) write line-delimited compiler flags to `compiler_flags.txt` in project root.
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
 - The Best way to develop a C++ project and configure the build is to use `cmake`. Install this tool, and optionally install `CMake` Sublime package for syntax highlighting and snippets. Run `cmake` with the `-DCMAKE_EXPORT_COMPILE_COMMANDS=1` option. *n.b.* I hard-coded this option in the `CMakeLists.txt` in this example because I do not know a reason not to do it. This will create a `compile_commands.json` file in the build directory you created for your binaries. You can copy this to your project root for `clangd` to see by default or you can point `clangd` to this build directory using one of its options (see `clangd` settings below). Here is an example for getting the project build setup with `cmake`.
 ```shell
 cd /path/to/this/project
 mkdir build && cd build
 cmake ..
 ```

3. For linting, write clang-tidy configuration file `.clang-tidy` (see example, which I adapted from Google Cloud API repo).
4. For formatting, write clang-format file `.clang-format`. `clang-format` currently supports a few standards including Google, LLVM, Mozilla, etc. Can generate a file with the following command:
```shell
clang-format --style=google --dump-config > .clang-format
```

5. Install Language Server Protocol (LSP) in Sublime.
6. Enable clangd server globally in LSP package.
7. Use LSP settings similar to this :
```yaml
{
  "clients":
  {
    "clangd":
    {
      "command":
      [
        "/opt/local/libexec/llvm-11/bin/clangd",
        "--compile-commands-dir=build",
        "--background-index",
        "--cross-file-rename",
        "--header-insertion=iwyu",
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

## (Re)Generate sourcelist before configuring build
For libraries that are built from a large number of source files, it is convenient to use glob pattern matching like `src/*.cpp`, rather than manually listing the source files for the project. This is specially true as the list of source files changes over the course of project development. `cmake` warns against using glob matching to get a list of sources. I have made a `generate_lib_sourcelist.sh` shell script that will do this for us.

If you have made changes to the source files in the project, run this shell script before calling `cmake` to configure the build. It (re)creates a `src/sourcelist.txt` file.

```shell
cd /path/to/this/project/scripts
./generate_lib_sourcelist.sh
```
