## JAVA

```java
import java.util.*;

class UndoRedoSystem {

    private StringBuilder document;
    private Stack<String> undoStack;
    private Stack<String> redoStack;

    public UndoRedoSystem(String initialState) {
        this.document = new StringBuilder(initialState);
        this.undoStack = new Stack<>();
        this.redoStack = new Stack<>();
    }

    // TYPE operation
    public void type(String text) {
        // Implement TYPE logic
    }

    // UNDO operation
    public void undo() {
        // Implement UNDO logic
    }

    // REDO operation
    public void redo() {
        // Implement REDO logic
    }

    public String getDocument() {
        // Return final document state
        return "";
    }

    public static void main(String[] args) {
        UndoRedoSystem system = new UndoRedoSystem("");

        system.type("Hello");
        system.type(" World");
        system.undo();
        system.redo();
        system.type("!");
        system.undo();
        system.undo();
        system.redo();

        System.out.println(system.getDocument());
        // Expected Output: Hello World
    }
}
```

## C++
```C++
#include <iostream>
#include <stack>
#include <string>

using namespace std;

class UndoRedoSystem {
private:
    string document;
    stack<string> undoStack;
    stack<string> redoStack;

public:
    UndoRedoSystem(string initialState) {
        document = initialState;
    }

    // TYPE operation
    void type(string text) {
        // Implement TYPE logic
    }

    // UNDO operation
    void undo() {
        // Implement UNDO logic
    }

    // REDO operation
    void redo() {
        // Implement REDO logic
    }

    string getDocument() {
        // Return final document state
        return "";
    }
};

int main() {
    UndoRedoSystem system("");

    system.type("Hello");
    system.type(" World");
    system.undo();
    system.redo();
    system.type("!");
    system.undo();
    system.undo();
    system.redo();

    cout << system.getDocument() << endl;
    // Expected Output: Hello World

    return 0;
}

```
## Python
```python
class UndoRedoSystem:
    def __init__(self, initial_state=""):
        self.document = initial_state
        self.undo_stack = []
        self.redo_stack = []

    # TYPE operation
    def type(self, text):
        # Implement TYPE logic
        pass

    # UNDO operation
    def undo(self):
        # Implement UNDO logic
        pass

    # REDO operation
    def redo(self):
        # Implement REDO logic
        pass

    def get_document(self):
        # Return final document state
        return ""


# Example Usage
if __name__ == "__main__":
    system = UndoRedoSystem("")

    system.type("Hello")
    system.type(" World")
    system.undo()
    system.redo()
    system.type("!")
    system.undo()
    system.undo()
    system.redo()

    print(system.get_document())
    # Expected Output: Hello World
```
