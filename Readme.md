# Mnemonic Designation Compiler
A small program that converts files containing mnemonic designation into files consisting of a sequence of bytes that are code values. To transfer file paths, you need to list them as application parameters. By default, the translation of the mnemonic string occurs in a code consisting of one byte. There is support for translating codes consisting of 2 and 4 bytes.

# Build
```sh
git clone https://github.com/ausf-software/mnemonic-designation-compiler.git
cmake ./
make
```

# Flags and arguments
* **-R[path]** specifies the path to the file containing the translation rules.
* **-O[path]** specifies the path to the directory to which the translated files will be recorded.
* **-wc a flag** indicating that it is necessary to output the translated files to the current directory.
* **-rc** flag indicating the need to search for a file containing translation rules in the current directory. The file must have the following name "rules".
* **-f flag** indicating the need to search for files for translation in the current directory. The files must have the following filename extension "*.mnemonic".
* **-i a flag** indicating that encoding occurs in 4 bytes.
* **-s a flag** indicating that encoding occurs in 2 bytes.

# Syntax of ".mnemonic" files
```
MNEMONIC_NOTATION_STRING=NUMERICAL_VALUE
```
### Example:
```
ZERO=0
ONE=1
TWO=2
```

# fatal error: filesystem: No such file or directory include <filesystem>
Make sure that in your version of the compiler "filesystem.h" is not an experimental tool.