# eg-cpplint
An example repository for using [clangd](https://clangd.llvm.org/) to lint C++ code.

# Setup (using Sublime text editor)
1. Install `clangd` and rest of `llvm` if not already. Make sure `clang-tidy` is included. I installed llvm-11 via macports. Its resources are available at `/opt/local/libexec/llvm-11`.
2. For `include`s to work, use `cmake` to build project or (for simple projects) write line-delimited compiler flags to `compiler_flags.txt` in project root.
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
 - The Best way is to use `cmake`. Install this tool, and optionally install `CMake` Sublime package for syntax highlighting and snippets. Run `cmake` with the `-DCMAKE_EXPORT_COMPILE_COMMANDS=1` option. This will create a `compile_commands.json` file in the build directory you created for your binaries. You can copy this to your project root for `clangd` to see by default or you can point `clangd` to this build directory using one of its options.


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

# Sublime text useful feature
I stumbled upon an autocomplete snippet for class definitions that expands to include constructor/destructor.
