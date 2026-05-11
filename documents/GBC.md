# Garbage Collection

# Overview
We have implemented parallel and concurrent garbage collection (GC) in Easy-ISLisp, a learning and research-oriented processing system compliant with ISOLisp. Using the mark-and-sweep method and Pthread, we added parallel and concurrent functionalities. Since there were challenging aspects specifically related to the concurrent part, we decided to document them for future reference.

# Memory Configuration
Easy-ISLisp is designed for learning purposes and implements cells as arrays of C language structures. The total number of cells is 20 megacells. In the interpreter, the environment is implemented as an associative list. The compiler adopts a method of converting Lisp code into C code.

# Processing Phases
Concurrent GC consists of the following four phases:

## Initial Marking
The concurrent_flag is set to ON to notify the main thread that the GC thread is running. Symbols connected to a hash table are marked. During this phase, if the main thread consumes cells, their addresses are stored in the remark array.

## Remark Phase
The concurrent_stop_flag is set to ON to notify the main thread that it has entered the "stop the world" phase. During this phase, cell consumption is halted on the main thread. Cells that need to be saved, such as the associative list representing the environment, are stored. Additionally, the remark array is used to mark the cells that were consumed during the initial marking phase.

## Sequential Sweep
During the "stop the world" phase, 20% of all cells are reclaimed. At this stage, the concurrent_stop_flag is set to OFF, and the system returns to concurrent operation.

# Key Considerations

## Remaining Cell Count at GC Startup
After initiating GC, an initial marking is performed while the main thread is operating concurrently. It is necessary to keep cells for this purpose. Empirically, we have launched GC with 900,000 cells remaining.

## Sequential Sweep
When attempting to perform cell reclamation and cell consumption simultaneously, synchronization with the main thread using a mutex becomes necessary. This results in a decrease in speed. Additionally, if the consumption count exceeds the reclamation count, cells cannot be supplied. Therefore, we perform sequential processing to reclaim 20% of cells before transitioning to concurrent processing. The value of 20% was determined through computational experiments.
