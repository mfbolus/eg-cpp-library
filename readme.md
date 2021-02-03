#eg-cpplint
An example repository for using [clangd](https://clangd.llvm.org/) to lint C++ code.

#Setup (using Sublime text editor)
1. Install `clangd` and rest of `llvm` if not already. Make sure `clang-tidy` is included.
2. For `include`s to work, use `cmake` to build project or (for simple projects) write line-delimited compiler flags to `compiler_flags.txt` in project root.
3. For linting, write clang-tidy configuration file `.clang-tidy` (see example, which I adapted from Google Cloud API repo).
4. For formatting, write clang-format file `.clang-format`. `clang-format` currently supports a few standards including Google, LLVM, Mozilla, etc. Can generate a file with the following command:
```shell
clang-format --style=google --dump-config > .clang-format
```

5. Install Language Server Protocol (LSP) in Sublime
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
        "clangd",
        "--background-index",
        "--cross-file-rename",
        "--header-insertion=iwyu",
        "--fallback-style=google",
        "--clang-tidy",
        "--all-scopes-completion",
        "--completion-style=detailed",
        "--log=verbose"
      ],
      "enabled": true
    },
  },
  "additionalTextEdits": true,
  "log_debug": true,
  "log_server": true,
  "log_stderr": true,
  "log_stdout": true,
  "only_show_lsp_completions": true
}
```

#Weirdly-triggered, but useful feature
I stumbled upon an autocompletion for class definitions that expands to include constructor/destructor. This autocompletion **only** becomes available if you type keyword `class`, delete last to letters to `cla`, add back one `s` and wait for this autocomplete option.
