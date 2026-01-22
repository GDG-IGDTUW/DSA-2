// This program stimulates simple undo-redo system involving functions to type, undo, redo, and display

// Since text can only be added, undo removes text from document and redo adds it back

// redo cannot be done without an undo first and vice versa so there is no possibility of redo 
// having to perform removal operation and and undo having to perform addition operation

// type function adds text to the document and clears the redo operation, and display function gives the final output

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
        // PERFORMS THE FOLLOWING OPERATIONS:
        //Adds text to document
        //Adds the text to undoStack (so it can be undone)
        //Clears redoStack
      
        document+= text;
        undoStack.push(text);
      
        //clearing the redoStack
        while (!redoStack.empty()){
            redoStack.pop();
        }
    }

    // UNDO operation
    void undo() {
        //PERFORMS THE FOLLOWING OPERATIONS
        //Does nothing if undoStack is empty
        //removes the top element of undoStack from the document
        //adds the top element of undoStack to redoStack (so undo can be redone if needed)
        // removes the top element from undoStack after having performed undo operation

        if (undoStack.empty()) return;

        //document.erase(position,number of elements)
        //where position is length of document- length of element to be removed
        document.erase(document.size()-undoStack.top().size());
        redoStack.push(undoStack.top());
        undoStack.pop();
        
    }

    // REDO operation
    void redo() {
        // PERFORMS THE FOLLOWING TASKS
        //does nothing if redoStack is empty
        //adds the top element of redoStack and appends it to undoStack
        //adds the top element of redoStack to document
        //removes the top element from redoStack

        if (redoStack.empty()) return;
        document+= redoStack.top();
        undoStack.push(redoStack.top());
        redoStack.pop();
    }

    string getDocument() {
        // Returns final document state
        return document;
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
