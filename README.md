# 🧠 DS-Project: Dijkstra's Algorithm in C++

An educational yet efficient C++ implementation of Dijkstra's algorithm, designed for computing the shortest path in weighted graphs using adjacency lists and priority queues.

---

## 🚀 Features
- Utilizes `unordered_map<Vertex*, int>` for dynamic distance tracking
- Implements a priority-based processing system for optimal node traversal
- Prints the shortest path and total cost from source to destination

---

## 🛠️ How It Works

This project applies **Dijkstra's algorithm** with the following steps:

1. Identify source and destination nodes from the input graph.
2. Initialize all node distances from the source as infinity.
3. Set the source distance to zero and push it into the priority queue.
4. In the main loop:
   - Process the current node with the smallest tentative distance.
   - Update the distances of its neighbors if a shorter path is found.
5. Continue until the destination is reached or the queue is empty.
6. Finally, output the shortest path and total travel time.

This structured approach ensures precise and efficient pathfinding in any graph topology.

---

## 👥 Team Members
- Reyhun
- Fatemeh
- Zeynab

---

## 📁 Files
> Main logic and algorithm implementation can be found in the respective `.cpp` files. Comments and modular structure are included for readability and future improvements.

---

## 📌 Note
This project was developed as part of our **Data Structures course** to demonstrate real-world applications of graph algorithms in C++.

---

Feel free to fork, test, or extend the logic for more advanced use cases such as bidirectional search or dynamic graph updates.
