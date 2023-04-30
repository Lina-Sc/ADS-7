// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <string>
#inclede <iostream>

template<typename T>
class TPQueue {
 private:
  struct Item {
    T data;
    Item* next;
    Item* prev;
  };
  Item* head;
  Item* tail;
  TPQueue::Item* create(const T& data) {
    Item* item = new Item;
    item->data = data;
    item->next = nullptr;
    item->prev = nullptr;
    return item;
  }

 public:
  TPQueue() : head(nullptr), tail(nullptr) {}
  ~TPQueue() {
    while (head) {
      pop();
    }
  }
  void push(const T& newData) {
    if (head == nullptr) {
      head = create(newData);
      tail = head;
    } else if (tail->data.prior >= newData.prior) {
      if (tail->data.ch == newData.ch) {
        tail->data = newData;
      } else {
        tail->next = create(newData);
        tail->next->prev = tail;
        tail = tail->next;
      }
    } else if (head == tail) {
      tail->prev = create(newData);
      head = tail->prev;
      head->next = tail;
    } else {
      Item* temp = tail;
      while (temp != head && temp->data.prior < newData.prior) {
        temp = temp->prev;
      }
      if (temp->data.prior > newData.prior) {
        Item* newItem = new Item;
        newItem->next = temp->next;
        newItem->prev = temp;
        newItem->data = newData;
        temp->next->prev = newItem;
        temp->next = newItem;
      }
      if (temp == head && temp->data.prior < newData.prior) {
        head->prev = create(newData);
        head = head->prev;
        head->next = temp;
      }
    }
  }
  T pop() {
    if (!head) {
      throw std::string("Queue is Empty!");
    } else {
      Item* temp = head->next;
      T data = head->data;
      delete head;
      head = temp;
      return data;
    }
  }
  void print() const {
    Item* temp = head;
    while (temp) {
      std::cout << temp->data << " ";
      temp = temp->next;
    }
    std::cout << std::endl;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
