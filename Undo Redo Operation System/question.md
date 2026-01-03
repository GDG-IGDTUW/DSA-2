# Undo–Redo Operation System

## Problem Statement

You are tasked with designing an **Undo–Redo Operation System** similar to what is used in text editors, drawing tools, or IDEs.

The system maintains a document (or state) and supports a sequence of operations that modify this state. The user can **undo** previously executed operations or **redo** operations that were undone, following standard undo–redo rules.

Your task is to process a list of operations and return the **final state** of the document.

---

## System Rules

1. **Perform Operation**
   - Applies a new operation to the document.
   - Clears the redo history (redo stack).

2. **Undo**
   - Reverts the most recent operation.
   - The undone operation moves to the redo stack.
   - If no operation is available to undo, do nothing.

3. **Redo**
   - Re-applies the most recently undone operation.
   - The redone operation moves back to the undo stack.
   - If no operation is available to redo, do nothing.

---

## Input Format

1. **Initial State**
   - A string representing the initial document content.

2. **Operations**
   - A list of commands where each command is one of the following:
     - `TYPE <text>` → Append `<text>` to the document
     - `UNDO` → Undo the last operation
     - `REDO` → Redo the last undone operation

---

## Output Format

Return the **final state of the document** after processing all operations.

---

## Example Input

```plaintext
Initial State:
""

Operations:
TYPE Hello
TYPE  World
UNDO
REDO
TYPE !
UNDO
UNDO
REDO
```

## Example Output

```plaintext
Output:
"Hello World"
```

---

## Step-by-Step Explanation

| Operation   | Document State | Undo Stack        | Redo Stack        |
|------------|----------------|-------------------|-------------------|
| TYPE Hello | Hello          | [Hello]           | []                |
| TYPE World | Hello World    | [Hello, World]    | []                |
| UNDO       | Hello          | [Hello]           | [World]           |
| REDO       | Hello World    | [Hello, World]    | []                |
| TYPE !     | Hello World!   | [Hello, World, !] | []                |
| UNDO       | Hello World    | [Hello, World]    | [!]               |
| UNDO       | Hello          | [Hello]           | [!, World]        |
| REDO       | Hello World    | [Hello, World]    | [!]               |

**Final Output → `"Hello World"`**

---

## Constraints

- 1 ≤ Number of operations ≤ 100,000  
- Each `TYPE` operation appends at most 100 characters  
- `UNDO` and `REDO` operations are case-sensitive  
- The document size can grow up to 1,000,000 characters  
- All operations must be processed in **O(1)** time per operation  

---

## Expected Approach

Use **two stacks**:

- **Undo Stack** → stores performed operations  
- **Redo Stack** → stores undone operations  

### On `TYPE`
- Push operation to undo stack  
- Clear redo stack  

### On `UNDO`
- Pop from undo stack  
- Reverse the operation  
- Push to redo stack  

### On `REDO`
- Pop from redo stack  
- Reapply operation  
- Push to undo stack  

---

## Edge Cases

- Calling `UNDO` when no operation exists  
- Calling `REDO` when redo stack is empty  
- Multiple consecutive `UNDO` or `REDO` calls  
- New `TYPE` operation after `UNDO` (redo history must be cleared)



