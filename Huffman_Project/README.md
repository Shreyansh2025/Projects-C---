# High-Performance File Compressor (Huffman Coding)

A C++ based file compression tool that reduces file size by 30-40% using the Huffman Coding algorithm.

### Key Features
* **Custom Data Structures:** Implemented Min-Heap and Binary Tree from scratch.
* **Bitwise Optimization:** Uses bit-manipulation to pack 8-bit characters into variable-length binary codes.
* **Memory Efficient:** Uses `priority_queue` for $O(K \log K)$ tree construction.

### Tech Stack
* C++ (STL: Maps, Vectors, Priority Queue)
* File I/O (fstream, binary mode)

### How to Run
1. Put text in `input.txt`.
2. Compile: `g++ main.cpp -o compressor`
3. Run: `./compressor`
4. Output will be saved to `output.huff`.
