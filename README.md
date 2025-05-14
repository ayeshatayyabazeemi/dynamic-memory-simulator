
# 🧠 Dynamic Memory Management Simulation in C

This project simulates **dynamic memory allocation and deallocation** in a system where processes arrive and leave over time. It mimics how memory is managed in an operating system using **First-Fit Allocation Strategy** and handles **memory fragmentation** by merging adjacent free blocks.

---

## 📁 Features

- ✅ Dynamic memory allocation using a **linked list** structure.
- 🧩 Merges adjacent free memory blocks after deallocation to reduce fragmentation.
- 📊 Tracks and displays memory usage over simulated time.
- ⏰ Simulates process arrival and termination at specific time units.
- 📈 Displays statistics (max, min, average) of memory usage by processes.

---

## 📌 How It Works

1. **User Input**:
   - Total main memory size in MB.
   - Process details: `arrival_time`, `size`, and `end_time`.

2. **Memory Simulation**:
   - At each time step:
     - Allocates memory to new processes (if space is available).
     - Deallocates memory from finished processes.
     - Merges adjacent free memory blocks.
     - Retries allocation for previously failed processes.
     - Displays memory status if any change occurs.

3. **At the End**:
   - Outputs statistics about process memory sizes.

---

## 🧪 Sample Input
Enter total size of Main Memory (in MB): 100
Enter process details (arrival_time size end_time), enter -1 to stop:
Process 1: 0 30 5
Process 2: 2 50 6
Process 3: 3 40 7
Process 4: -1

📊 Output Example
gcc memory_simulator.c -o memory_simulator
./memory_simulator
Allocated Process 1 at time 0
Allocated Process 2 at time 2
Failed to allocate Process 3 at time 3 (Not enough memory)
Deallocated Process 1 at time 5
Allocated Process 3 at time 5
...
Simulation Complete!

--- Process Size Statistics ---
Max Process Size Entered: 50MB
Min Process Size Entered: 30MB
Average Process Size Entered: 40.00MB

