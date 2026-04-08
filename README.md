# Search Engine

## What it is
This project is a Command-Line Interface (CLI) based search engine designed to manage and query a local database of individuals. Users can add new profiles (with attributes like name, age, description, and category—e.g., Tech, Cinema, Sports) and perform highly optimized searches. It features functionalities to search for people by their name or category, and dynamically list them sorted by age or popularity.

## Tech Stack
* **Language:** C++
* **Concepts:** Object-Oriented Programming (OOP), Custom Advanced Data Structures, CLI Application Design

## How it is Built
Instead of relying heavily on standard library containers, this search engine is engineered from the ground up using custom data structures tailored for specific query optimizations:

* **Binary Search Tree (BST):** Used for indexing profiles by name. When a user searches for a specific individual, the BST ensures fast, logarithmic average-case time complexity ($O(\log n)$) for retrieving the profile.
* **Array-Based Linked List (ABLL):** Designed specifically for the "List by age" feature. It utilizes an array of 101 pointers (representing ages 0 to 100), where each index acts as the head of a linked list. This allows the system to insert and group people of the exact same age in absolute constant time ($O(1)$) and rapidly print out users sorted by age.
* **Heap (Priority Queue):** Architected to power the "List by popularity" feature. By maintaining a max-heap structure, the engine can efficiently keep track of the most popular individuals and extract them in sorted order.
* **Menu-Driven CLI (`driver.cpp`):** The application is tied together by an interactive terminal loop that routes user choices to the corresponding internal data structure operations.
