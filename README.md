# PakFS

A simple C++ class for handling Quake2 PAK files from a base folder (and optionally including non-PAKed files). Two examples are included, along with an example base folder with bare files, a base PAK (pak0) and a PAK file with some overrides (pak2). The file pak1 intentionally doesn't exist.

## example1.cpp

Reads a single text file as a string from PAK files only.

## example2.cpp

Reads a selection of files from PAK files and the base directory, storing them in a char array (as you would for a binary file).
