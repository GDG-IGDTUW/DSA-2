import java.util.*;

class HuffmanCoding {

    // Huffman Tree Node
    class Node {
        char ch;
        int freq;
        Node left, right;

        Node(char ch, int freq) {
            this.ch = ch;
            this.freq = freq;
        }

        Node(int freq, Node left, Node right) {
            this.ch = '\0'; // internal node
            this.freq = freq;
            this.left = left;
            this.right = right;
        }
    }

    private Map<Character, Integer> frequencyMap;
    private Map<Character, String> huffmanCodes;
    private PriorityQueue<Node> minHeap;
    private Node root;

    HuffmanCoding() {
        frequencyMap = new HashMap<>();
        huffmanCodes = new HashMap<>();
        minHeap = new PriorityQueue<>(Comparator.comparingInt(n -> n.freq));
    }

    // Step 1: Calculate frequency of each character
    void calculateFrequency(String text) {
        for (char ch : text.toCharArray()) {
            frequencyMap.put(ch, frequencyMap.getOrDefault(ch, 0) + 1);
        }
    }

    // Step 2: Build Huffman Tree
    void buildHuffmanTree() {
        for (Map.Entry<Character, Integer> entry : frequencyMap.entrySet()) {
            minHeap.add(new Node(entry.getKey(), entry.getValue()));
        }

        while (minHeap.size() > 1) {
            Node left = minHeap.poll();
            Node right = minHeap.poll();

            Node merged = new Node(left.freq + right.freq, left, right);
            minHeap.add(merged);
        }

        root = minHeap.poll();
    }

    // Step 3: Generate Huffman Codes
    void generateCodes() {
        generateCodesHelper(root, "");
    }

    private void generateCodesHelper(Node node, String code) {
        if (node == null) return;

        // Leaf node
        if (node.left == null && node.right == null) {
            huffmanCodes.put(node.ch, code);
            return;
        }

        generateCodesHelper(node.left, code + "0");
        generateCodesHelper(node.right, code + "1");
    }

    // Step 4: Encode text
    String encode(String text) {
        StringBuilder encoded = new StringBuilder();
        for (char ch : text.toCharArray()) {
            encoded.append(huffmanCodes.get(ch));
        }
        return encoded.toString();
    }

    // Step 5: Decode binary string
    String decode(String encodedText) {
        StringBuilder decoded = new StringBuilder();
        Node current = root;

        for (char bit : encodedText.toCharArray()) {
            current = (bit == '0') ? current.left : current.right;

            if (current.left == null && current.right == null) {
                decoded.append(current.ch);
                current = root;
            }
        }

        return decoded.toString();
    }

    // Driver code
    public static void main(String[] args) {
        HuffmanCoding hc = new HuffmanCoding();
        String text = "huffman coding";

        hc.calculateFrequency(text);
        hc.buildHuffmanTree();
        hc.generateCodes();

        System.out.println("Huffman Codes:");
        for (Map.Entry<Character, String> entry : hc.huffmanCodes.entrySet()) {
            System.out.println(entry.getKey() + " : " + entry.getValue());
        }

        String encoded = hc.encode(text);
        System.out.println("\nEncoded String:");
        System.out.println(encoded);

        String decoded = hc.decode(encoded);
        System.out.println("\nDecoded String:");
        System.out.println(decoded);
    }
}
