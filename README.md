*This project has been created as part of the 42 curriculum by \<vebastos\>.*

# Codexion

## Description
**Codexion** is a concurrent programming project from the 42 curriculum that reimagines the classic **Dining Philosophers** problem. In this multithreaded simulation, **coders** sitting around a virtual table must share a limited set of **dongles** to get their work done.

The challenge is one of resource management and synchronization. To **compile** code, a coder requires exclusive access to two specific dongles. Once compilation is complete, they release the resources and proceed to **debug** and **refactor**. The system must carefully orchestrate these threads to prevent deadlocks and starvation; if a coder waits too long for dongles, they suffer **burnout**, and the simulation fails.

## Instructions
### 1. Compilation
To compile the `codexion` program:

```bash
make
```

### 2. Execution
Run the simulation with the following arguments: `./codexion [number_of_coders] [time_to_burnout] [time_to_compile] [time_to_debug] [time_to_refactor] [compiles_required] [dongle_cooldown] [scheduler]`

| Argument | Description |
| :---- | :---- |
| `number_of_coders` | The number of coders (threads) and dongles. |
| `time_to_burnout` | Time (in ms) a coder can go without compiling before burning out. |
| `time_to_compile` | Duration (in ms) of the compilation process (requires 2 dongles). |
| `time_to_debug` | Duration (in ms) spent debugging after compiling. |
| `time_to_refactor` | Duration (in ms) spent refactoring after debugging. |
| `compiles_required` | Number of times each coder must compile to finish the simulation. |
| `dongle_cooldown` | Time (in ms) a dongle remains unavailable after being used. |
| `scheduler` | The scheduling algorithm to use: fifo or edf. |

**Example:**

```bash
./codexion 5 800 200 200 200 5 10 fifo
```

## Blocking cases handled
This simulation robustly addresses standard concurrency issues to ensure stability and correctness:

*   **Deadlock Prevention (Priority Queue Arbitration): Instead of allowing threads to blindly grab physical dongles and cause a circular wait, this engine forces coders to register in a centralized Priority Queue. A coder only attempts to lock physical dongles when they reach the front of the queue (queue_head), making deadlocks mathematically impossible.

*   **Starvation Prevention (Custom Scheduler)**: The dynamic waiting queue manages dongle requests using two distinct arbitration policies:
    
    *   **FIFO (First-In-First-Out)**: Ensures strict fairness, meaning no coder can be bypassed indefinitely by faster threads.
        
    *   **EDF (Earliest Deadline First)**: Prioritizes coders based on urgency. The algorithm calculates the last\_compile\_start of all waiting entities and grants queue priority to the coder whose burnout deadline is approaching fastest.
        
*   **Precise Burnout Detection**: A dedicated **Monitor Thread** continuously scans the state of all coders. It utilizes a mutex-protected heartbeat mechanism to detect inactivity. If a coder fails to compile within the time\_to\_burnout window, the monitor instantly flags sim\_stop and halts execution without printing overlapping phantom logs.
    
*   **Log Serialization**: All output to the console is guarded by a shared print\_mutex. This prevents race conditions in the standard output (scrambled or interleaved messages) when multiple threads attempt to print status updates simultaneously.

## Thread synchronization mechanisms
The project utilizes strict POSIX threading primitives to coordinate access to shared resources and memory:


### Mutexes (pthread\_mutex\_t)

Mutexes are the primary defense against data races, ensuring mutually exclusive access to critical zones:

*   **Dongle Locks**: Each physical dongle has a dedicated mutex. A coder must successfully acquire both locks (left and right) to enter the critical "compiling" section.
    
*   **State Lock (state\_mutex)**: A global shield protecting shared simulation variables, including the sim\_stop flag and each coder's last\_compile\_start. This prevents the Monitor from reading corrupted time data while a Coder is updating it.
    
*   **Queue Lock (queue\_mutex)**: Protects the Intrusive Linked List structure. It guarantees that coders can safely enqueue and dequeue themselves from the scheduler without memory corruption.
    
*   **Print Lock (print\_mutex)**: Specifically designated for I/O operations to ensure atomic log entries.


### Intrusive Linked List & CPU Polling

To manage the scheduling queue with high performance and zero memory leaks, the project avoids dynamic allocation (malloc/free) during the execution loop:

*   **Zero-Allocation Nodes**: The t\_coder structure inherently acts as a linked list node (next\_in\_queue).
    
*   **Smart Polling**: Instead of busy-looping aggressively and throttling the CPU, waiting coders check their queue position and, if it is not their turn, yield CPU time using a micro-sleep (usleep(500)). This allows the Monitor thread and active coders to execute smoothly.

## Resources
Since this project relies heavily on the POSIX standard, the following documentation was referenced:

- **POSIX Threads (pthreads) Specification**: [The Open Group Base Specifications Issue 7](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/pthread.h.html) - For details on pthread_mutex and thread creation.

- **The Dining Philosophers Problem**: [Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem) - For the theoretical background of the resource sharing problem.

- **Valgrind User Manual**: [Helgrind: a thread error detector](https://valgrind.org/docs/manual/hg-manual.html) - For interpreting data race reports.

### AI Usage
AI assistance was utilized in this project for:

- **Conceptual Tutoring**: acting as a Socratic tutor to clarify doubts regarding core concurrent programming concepts. This included explaining the theoretical behavior of threads, the mechanics of race conditions, and the differences between busy-waiting versus sleeping.

- **Debugging Analysis**: Analyzing complex logs from Valgrind and Helgrind to identify the root causes of race conditions and distinguish them from false positives.

- **Edge Case Generation**: Suggesting rigorous stress tests (e.g., 200 threads, 0 durations) to verify system stability under load.

- **Documentation Drafting**: Assisting in structuring and refining the README file to ensure clarity, coherence, and adherence to project submission requirements.