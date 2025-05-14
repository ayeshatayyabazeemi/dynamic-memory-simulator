
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
![image](https://github.com/user-attachments/assets/61727239-404b-4566-919d-6babf63a2f0c)
---
📊 Output Example
![image](https://github.com/user-attachments/assets/bcd0393a-52fa-4336-9ddb-8376ed1263af)
![image](https://github.com/user-attachments/assets/d82c7120-1657-4726-a379-37c32f4df839)
---


