#ifndef LAB4_PRIORITYQUEUE_HPP
#define LAB4_PRIORITYQUEUE_HPP

#include "Sequence.h"
#include "ArraySequence.h"
#include "../pair/Pair.hpp"
#include <stdexcept>

template<typename T>
class PriorityQueue : public Sequence<T> {
public:
    PriorityQueue() = default;
    ~PriorityQueue() override = default;

    void enqueue(const T& item, int priority) {
        Pair<T,int> new_pair(item, priority);

        int insert_pos = 0;
        while (insert_pos < data_.get_length()) {
            int exist_priority = data_.get(insert_pos).value2;
            if (exist_priority >= priority) {
                insert_pos++;
            } else {
                break;
            }
        }
        data_.insert_at(new_pair, insert_pos);
    }

    T dequeue() {
        if (data_.get_length() == 0) {
            throw std::out_of_range("priority_queue is empty (dequeue)");
        }
        auto top = data_.get(0);
        data_.remove_at(0);
        return top.value1;
    }

    T peek(int i) {
        if (i < 0 || i >= data_.get_length()) {
            throw std::out_of_range("Index out of range in peek()");
        }
        return data_.get(i).value1;
    }

    T peek_first() {
        if (data_.get_length() == 0) {
            throw std::out_of_range("priority_queue is empty (peek_first)");
        }
        return data_.get(0).value1;
    }

    T peek_last() {
        int len = data_.get_length();
        if (len == 0) {
            throw std::out_of_range("priority_queue is empty (peek_last)");
        }
        return data_.get(len - 1).value1;
    }

    int get_length() const override {
        return data_.get_length();
    }

private:
    ArraySequence<Pair<T,int>> data_;

    const T& get(int) const override {
        throw std::logic_error("get(int) is hidden in priority_queue");
    }
    T& get(int) override {
        throw std::logic_error("get(int) is hidden in priority_queue");
    }

    const T& get_first() const override {
        throw std::logic_error("get_first() is hidden in priority_queue; use peek_first()");
    }
    const T& get_last() const override {
        throw std::logic_error("get_last() is hidden in priority_queue; use peek_last()");
    }

    Sequence<T>* get_subSequence(int, int) const override {
        throw std::logic_error("get_subSequence(...) is hidden in priority_queue");
    }

    void append(const T& item) override {
        enqueue(item, 0);
    }
    void prepend(const T& item) override {
        enqueue(item, 0);
    }

    void insert_at(const T&, int) override {
        throw std::logic_error("insert_at(...) is invalid operation in priority_queue");
    }

    void remove_at(int) override {
        throw std::logic_error("remove_at(...) is invalid operation in priority_queue");
    }

    bool remove_item(const T&) override {
        throw std::logic_error("remove_item(...) is invalid operation in priority_queue");
    }

    bool contains(const T&) const override {
        throw std::logic_error("contains(...) is invalid in priority_queue");
    }

    int index_of(const T&) const override {
        throw std::logic_error("index_of(...) is invalid in priority_queue");
    }

    void set(int, const T&) override {
        throw std::logic_error("set(...) is invalid in priority_queue");
    }

    Sequence<T>* concat(Sequence<T>*) const override {
        throw std::logic_error("concat(...) is invalid in priority_queue");
    }

    void swap(int, int) override {
        throw std::logic_error("swap(...) is invalid in priority_queue");
    }

    void reserve(int) override {
        throw std::logic_error("reserve(int) is hidden in priority_queue");
    }
};

#endif
