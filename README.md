#File Compression Tool with RLE and Base64 Encoding
#Description
This project implements a File Compression Tool that uses a combination of Run-Length Encoding (RLE) and Base64 encoding to compress and decompress files.

RLE Compression: Reduces the size of a file by encoding consecutive repeated characters as a single character followed by the count of repetitions.

Base64 Encoding: Converts binary data into an ASCII string, making it easier to store or transfer files over text-based systems.

The tool provides options to:

Compress a file: Compresses the file using RLE and then applies Base64 encoding.

Decompress a file: Decodes the Base64 encoded file and then decompresses it using RLE.

#Features:
File Compression: Combines two compression techniques (RLE + Base64).

File Decompression: Decodes and decompresses a file back to its original state.

File Handling: Reads input and writes output to files, ensuring that the original data is correctly reconstructed.

#Requirements
C++ Compiler (G++ recommended)

Basic understanding of file handling in C++
