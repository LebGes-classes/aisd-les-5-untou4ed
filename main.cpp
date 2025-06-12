#include <iostream>
#include <string>
#include "MonotonicPriorityQueue.cpp"

int main() {
    MonotonicPriorityQueue<std::string, int> queue;
    try {
        std::cout << queue.peek() << std::endl;
    } catch (std::out_of_range e) {
        std::cout << e.what() << std::endl;
    }
    queue.enqueue("1", 10);
    queue.enqueue("2", 15);
    queue.enqueue("3", 20);
    queue.enqueue("4", 18);
    std::cout << queue.peek() << std::endl;

    while (!queue.empty()) {
        std::cout << queue.dequeue() << std::endl;
    }

    return 0;
}