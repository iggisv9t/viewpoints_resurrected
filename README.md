Original readme is in [LEGACY_README.md](LEGACY_README.md)

# Viewpoints Resurrected

A modernized fork of the Viewpoints visualization tool, originally developed by Creon Levit and Paul Gazis at NASA.

## About

Viewpoints is a fast interactive tool for linked plotting of large multivariate data sets. This fork aims to modernize the codebase while maintaining compatibility with existing functionality.

## Current Status

This is a work in progress. The current version has been updated to compile and run on modern systems with some temporary fixes in place. Works on my machine, not tested anywhere else.

### Known Issues
- VBOs are currently disabled as a temporary workaround
- Point selection uses fallback rendering

## Building from Source

### Prerequisites
- CMake 3.10 or higher
- A C++17 compatible compiler
- OpenGL development libraries
- FLTK 1.3.x development libraries
- GSL (GNU Scientific Library)

### Build Instructions
```bash
mkdir -p build && cd build
cmake ..
make -j$(nproc)
```

## Usage

```
./vp [options] [input_file]
```

For detailed usage instructions, please see [LEGACY_README.md](LEGACY_README.md).

## License

This software is provided as-is. Please see the original project for licensing information.

## Disclaimer

This is an unofficial fork maintained by the community. This is not an official NASA project.
Vibecoding applied.