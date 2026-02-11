import heapq
from collections import defaultdict

class Node:
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None

    def __lt__(self, other):
        return self.freq < other.freq


class HuffmanCoding:
    def __init__(self):
        self.frequency = {}
        self.heap = []
        self.codes = {}
        self.reverse_codes = {}
        self.root = None

    def calculate_frequency(self, text):
        self.frequency = defaultdict(int)
        for ch in text:
            self.frequency[ch] += 1

    def build_huffman_tree(self):
        self.heap = []
        for char, freq in self.frequency.items():
            heapq.heappush(self.heap, Node(char, freq))

        while len(self.heap) > 1:
            left = heapq.heappop(self.heap)
            right = heapq.heappop(self.heap)

            merged = Node(None, left.freq + right.freq)
            merged.left = left
            merged.right = right

            heapq.heappush(self.heap, merged)

        self.root = self.heap[0]

    def generate_codes(self):
        self.codes = {}
        self.reverse_codes = {}

        def dfs(node, current_code):
            if not node:
                return

            if node.char is not None:
                self.codes[node.char] = current_code
                self.reverse_codes[current_code] = node.char
                return

            dfs(node.left, current_code + "0")
            dfs(node.right, current_code + "1")

        dfs(self.root, "")

        print("\nHuffman Codes:")
        for ch, code in self.codes.items():
            print(f"{ch} : {code}")

    def encode(self, text):
        encoded_text = ""
        for ch in text:
            encoded_text += self.codes[ch]

        print("\nEncoded String:")
        print(encoded_text)
        return encoded_text

    def decode(self, encoded_text):
        current = ""
        decoded_text = ""

        for bit in encoded_text:
            current += bit
            if current in self.reverse_codes:
                decoded_text += self.reverse_codes[current]
                current = ""

        print("\nDecoded String:")
        print(decoded_text)
        return decoded_text


if __name__ == "__main__":
    hc = HuffmanCoding()
    text = "huffman coding"

    hc.calculate_frequency(text)
    hc.build_huffman_tree()
    hc.generate_codes()

    encoded = hc.encode(text)
    decoded = hc.decode(encoded)
