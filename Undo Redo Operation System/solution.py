def undo_redo_system(initial_state, operations):
    document = initial_state
    undo_stack = []
    redo_stack = []

    for op in operations:
        if op.startswith("TYPE"):
            # Save current state for undo
            undo_stack.append(document)
            
            # Apply operation
            text = op.split(" ", 1)[1]
            document += text
            
            # Clear redo history
            redo_stack.clear()

        elif op == "UNDO":
            if undo_stack:
                redo_stack.append(document)
                document = undo_stack.pop()

        elif op == "REDO":
            if redo_stack:
                undo_stack.append(document)
                document = redo_stack.pop()

    return document
