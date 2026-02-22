#include <bits/stdc++.h>
using namespace std;

class HuffmanCoding {

private:

    // Node structure for Huffman Tree
    struct Node {
        char ch;
        int freq;
        Node* left;
        Node* right;

        Node(char c, int f) {
            ch = c;
            freq = f;
            left = right = nullptr;
        }
    };

    // Comparator for min heap
    struct Compare {
        bool operator()(Node* a, Node* b) {
            return a->freq > b->freq;
        }
    };

    unordered_map<char, int> frequency;
    unordered_map<char, string> huffmanCodes;
    Node* root;

public:

    HuffmanCoding() {
        root = nullptr;
    }

    // Step 1: Calculate frequency of characters
    void calculateFrequency(const string &text) {
        for (char ch : text) {
            frequency[ch]++;
        }
    }

    // Step 2: Build Huffman Tree using min heap
    void buildHuffmanTree() {

        priority_queue<Node*, vector<Node*>, Compare> minHeap;

        // Create leaf nodes and push to heap
        for (auto pair : frequency) {
            minHeap.push(new Node(pair.first, pair.second));
        }

        // Edge case: If only one unique character
        if (minHeap.size() == 1) {
            Node* onlyNode = minHeap.top();
            minHeap.pop();
            root = new Node('\0', onlyNode->freq);
            root->left = onlyNode;
            return;
        }

        // Build tree
        while (minHeap.size() > 1) {
            Node* left = minHeap.top(); minHeap.pop();
            Node* right = minHeap.top(); minHeap.pop();

            Node* merged = new Node('\0', left->freq + right->freq);
            merged->left = left;
            merged->right = right;

            minHeap.push(merged);
        }

        root = minHeap.top();
    }

    // Recursive function to generate codes
    void generateCodesHelper(Node* node, string code) {
        if (!node) return;

        // Leaf node
        if (!node->left && !node->right) {
            huffmanCodes[node->ch] = code;
        }

        generateCodesHelper(node->left, code + "0");
        generateCodesHelper(node->right, code + "1");
    }

    // Step 3: Generate Huffman Codes
    void generateCodes() {
        generateCodesHelper(root, "");

        cout << "Huffman Codes:\n";
        for (auto pair : huffmanCodes) {
            cout << pair.first << " : " << pair.second << "\n";
        }
        cout << endl;
    }

    // Step 4: Encode text
    string encode(const string &text) {
        string encodedText = "";

        for (char ch : text) {
            encodedText += huffmanCodes[ch];
        }

        cout << "Encoded String:\n" << encodedText << "\n\n";
        return encodedText;
    }

    // Step 5: Decode text
    string decode(const string &encodedText) {
        string decodedText = "";
        Node* current = root;

        for (char bit : encodedText) {

            if (bit == '0')
                current = current->left;
            else
                current = current->right;

            // If leaf node
            if (!current->left && !current->right) {
                decodedText += current->ch;
                current = root;
            }
        }

        cout << "Decoded String:\n" << decodedText << "\n";
        return decodedText;
    }
};

int main() {

    HuffmanCoding hc;
    string text = "huffman coding";

    hc.calculateFrequency(text);
    hc.buildHuffmanTree();
    hc.generateCodes();

    string encoded = hc.encode(text);
    string decoded = hc.decode(encoded);

    return 0;
}
