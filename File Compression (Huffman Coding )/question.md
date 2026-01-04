**File Compression (Huffman Coding)**

### *Problem Statement*

Develop a file compression system using **Huffman Coding**, which is a lossless data compression algorithm. The goal is to compress a given text by assigning variable-length binary codes to characters based on their frequencies. Characters with higher frequency should get shorter codes, while less frequent characters get longer codes.

The system should support the following functionalities:

- Calculate frequency of characters in the input text
- Build a Huffman Tree using a priority queue (min-heap)
- Generate Huffman codes for each character
- Encode the input text using the generated codes
- Decode the encoded binary string back to the original text

### *Input Format*

The input consists of a string representing the text to be compressed.

**Example Input:**

huffman coding

### *Output Format*

- Display Huffman codes for each character
- Display the encoded binary string
- Display the decoded original string

**Example Output:**

Huffman Codes:
h : 110
u : 111
f : 00
m : 101
a : 100
n : 011

Encoded String:
110111000101...

Decoded String:
huffman coding


### *Concepts Used*

- Greedy Algorithm
- Binary Trees
- Priority Queue (Min Heap)
- Hash Maps
- Recursion

### *Constraints*

1 ≤ Length of input string ≤ 100000  
Input consists of standard ASCII characters  
Compression must be lossless

Provide a screenshot of the accepted solution on Leetcode (if applicable), including the left pane in the description of pull request and push the solution.

