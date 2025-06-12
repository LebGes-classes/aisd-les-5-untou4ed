#include <vector>
#include <stdexcept>
#include <functional>
#include <iostream>

template <typename T, typename P>
class MonotonicPriorityQueue {
private:
    struct Node {
        T value;
        P priority;
        
        Node(const T& val, const P& prio) : value(val), priority(prio) {}
    };

    P last_priority;
    bool has_priority = false;
    std::vector<Node> heap;

    void up(size_t i) {
        while (i > 0 && heap[i].priority < heap[(i - 1) / 2].priority) {
            std::swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void down() {
        size_t i = 0;
        while (2 * i + 1 < heap.size()) {
            size_t left = 2 * i + 1;
            size_t right = 2 * i + 2;
            size_t smallest = left;

            if (right < heap.size() && heap[right].priority < heap[left].priority) {
                smallest = right;
            }

            if (heap[i].priority <= heap[smallest].priority) {
                break;
            }

            std::swap(heap[i], heap[smallest]);
            i = smallest;
        }
    }

public:
    MonotonicPriorityQueue() = default;

    void enqueue(const T& data, const P& priority) {
        if (has_priority && priority < last_priority) {
            std::cout << "приоритет должен быть не меньше приоритета последнего добавленного элемента" << std::endl;
            return;
        }

        last_priority = priority;
        has_priority = true;
        heap.emplace_back(data, priority);
        up(heap.size() - 1);
    }

    T dequeue() {
        if (heap.empty()) {
            throw std::out_of_range("очередь пуста");
        }

        T result = heap[0].value;
        if (heap.size() == 1) {
            heap.pop_back();
            return result;
        }

        Node last = heap.back();
        heap.pop_back();
        heap[0] = last;
        down();
        return result;
    }

    bool empty() const {
        return heap.empty();
    }

    const T& peek() const {
        if (heap.empty()) {
            throw std::out_of_range("очередь пуста");
        }
        return heap.front().value;
    }
};