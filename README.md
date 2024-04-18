# Targalib

Targalib or `targalib.h` is STB influenced header only image library for C/C++. Targalib designed to be compact and easy to use for graphics programs with no thirdparty dependencies(Like SDL, SFML etc.) but only utilize standart C library.
Users can load images to the memory from disk, create new .tga images, or manipulate them with Targalib.

## Usage
As mentioned, Targalib follows the STB style Header Only Library pattern. All you have to do is obtain the targalib.h file and place it in your include or headers directory. Then, include targalib.h in your source code and add the following macro when compiling:
```bash
-DTARGALIB_IMPLEMENTATION
```
here is an example of how to compile your source code with targalib.h
```bash
gcc -o load_image load_image.c -DTARGALIB_IMPLEMENTATION
```

## Features
- Load images from disk into memory
- Create new .tga images
- Perform basic image manipulations
- Header-only library, no external dependencies

## Getting Started
Check out the Usage section below for a quick guide on how to use Targalib in your projects.

## Examples
For comprehensive examples showcasing various use cases of Targalib, see the [example](./example/) directory.

## License
Targalib is under [unlicense](./LICENSE)

## Related Projects

## Version History
- v0.1.0    Initial Release 04.17.2024
  - Basic utilities