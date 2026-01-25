package CollectionsFramework;

import java.util.*;

class UndoRedoSystem {

    private StringBuilder document;
    private Stack<String> undoStack;

    public UndoRedoSystem(String initialState) {
        this.document = new StringBuilder(initialState);
        this.undoStack = new Stack<>();
    }

    // TYPE operation
    public void type(String text) {
        text = text.trim(); //remove leading spaces
        if(text.isEmpty())
            return; //do not add only spaces
        if(!document.isEmpty())
            document.append(" "); //if are preceding words then append a space
        document.append(text); //append the current word
        undoStack.clear(); //do not allow the redo operation now.
    }

    // UNDO operation
    public void undo() {
        // Implement UNDO logic
        if(document.isEmpty())
            return; //nothing has been typed as yet

        int lastIndex = document.lastIndexOf(" "); //get the index of last space
        String lastWord = document.substring(lastIndex+1); //get the last word
        undoStack.push(lastWord); //push the last word in the undo stack
        document.delete(Math.max(0, lastIndex), document.length()); //remove this from document
    }

    // REDO operation
    public void redo() {
        // Implement REDO logic
        if(undoStack.isEmpty()) //nothing to redo
            return;
        if(!document.isEmpty())
            document.append(" "); // add a space after the last word.

        document.append(undoStack.pop());
    }

    public String getDocument() {
        // Return final document state
        return document.toString();
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
