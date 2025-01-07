#ifndef LAB4_PRIORITYQUEUE_HPP
#define LAB4_PRIORITYQUEUE_HPP

#include <stdexcept>
#include "data_structures/Sequence.h"
#include "data_structures/ArraySequence.h"
#include "pair/Pair.hpp"

template<typename TItem, typename TPriority>
class PriorityQueue : public Sequence<TItem> {
public:
    PriorityQueue() = default;
    ~PriorityQueue() override = default;

    void enqueue(const TItem& item, const TPriority& priority) {
        Pair<TItem, TPriority> new_pair(item, priority);

        int insert_pos = 0;
        while (insert_pos < data_.get_length()) {
            TPriority exist_priority = data_.get(insert_pos).value2;

            if (exist_priority >= priority) {
                insert_pos++;
            } else {
                break;
            }
        }

        data_.insert_at(new_pair, insert_pos);
    }

    TItem dequeue() {
        if (data_.get_length() == 0) {
            throw std::out_of_range("priority_queue is empty");
        }

        auto top = data_.get(0);
        data_.remove_at(0);
        return top.value1;
    }

    TItem peek(int i) {
        if (i < 0 || i >= data_.get_length()) {
            throw std::out_of_range("Index out of range in peek");
        }
        return data_.get(i).value1;
    }

    TItem peek_first() {
        if (data_.get_length() == 0) {
            throw std::out_of_range("priority_queue is empty");
        }
        return data_.get(0).value1;
    }

    TItem peek_last() {
        int len = data_.get_length();
        if (len == 0) {
            throw std::out_of_range("priority_queue is empty");
        }
        return data_.get(len - 1).value1;
    }

    int get_length() const override {
        return data_.get_length();
    }

private:
    ArraySequence<Pair<TItem, TPriority>> data_;

    const TItem& get(int) const override {
        throw std::logic_error("get(int) is hidden in priority_queue");
    }
    TItem& get(int) override {
        throw std::logic_error("get(int) is hidden in priority_queue");
    }


    const TItem& get_first() const override {
        throw std::logic_error("get_first() is hidden in priority_queue; use peek_first()");
    }
    const TItem& get_last() const override {
        throw std::logic_error("get_last() is hidden in priority_queue; use peek_last()");
    }

    Sequence<TItem>* get_subSequence(int, int) const override {
        throw std::logic_error("get_subSequence(...) is hidden in priority_queue");
    }

    void append(const TItem& item) override {
        enqueue(item, TPriority{});
    }
    void prepend(const TItem& item) override {
        enqueue(item, TPriority{});
    }

    void insert_at(const TItem&, int) override {
        throw std::logic_error("insert_at(...) is invalid operation in priority_queue");
    }

    void remove_at(int) override {
        throw std::logic_error("remove_at(...) is invalid operation in priority_queue");
    }

    bool remove_item(const TItem&) override {
        throw std::logic_error("remove_item(...) is invalid operation in priority_queue");
    }

    bool contains(const TItem&) const override {
        throw std::logic_error("contains(...) is invalid in priority_queue");
    }

    int index_of(const TItem&) const override {
        throw std::logic_error("index_of(...) is invalid in priority_queue");
    }

    void set(int, const TItem&) override {
        throw std::logic_error("set(...) is invalid in priority_queue");
    }

    Sequence<TItem>* concat(Sequence<TItem>*) const override {
        throw std::logic_error("concat(...) is invalid in priority_queue");
    }

    void swap(int, int) override {
        throw std::logic_error("swap(...) is invalid in priority_queue");
    }

    void reserve(int) override {
        throw std::logic_error("reserve(int) is hidden in priority_queue");
    }
};

#endif // LAB4_PRIORITYQUEUE_HPP
