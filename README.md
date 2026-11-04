# sz
A Linux utility for viewing file sizes.

It displays file sizes in human readable format.

## Example
- command:
```
sz README.md
```
- output:
```
type: File
size: 402.00 B
```

## Development Environment
- OS: Linux Mint
- GCC Toolchain
- GNU Make

## Make Commands
- `make` - Build the project
- `make all` - Same as make
- `make -j$(nproc)` - Build using all available CPU cores
- `make clean` - Remove build/ and the output binary
- `make rebuild` - Clean everything and rebuild

## sz Usage

```
sz <no args>   -> Print sz version and help
sz -v          -> Print sz version
sz -h          -> Print sz help
sz file.txt    -> Print file size

```


## License
MIT