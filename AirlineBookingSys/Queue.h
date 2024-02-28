#pragma once
#include <utility>

namespace Utils
{
    template<typename T>
    class Queue
    {
    private:
        struct Node
        {
            T* data;
            Node* next;
            ~Node() {
                delete data;
            }
        };
    public:
        Queue() { head = tail = new Node{ nullptr , nullptr }; tail->next = head; }
        Queue(Queue&& que) :Queue() {
            std::swap(head, que.head);
            std::swap(tail, que.tail);
        }
        Queue(const Queue& que) :Queue() {
            Node* p = que.head->next;
            while (p) {
                push(*p->data);
                p = p->next;
            }
        }
        Queue& operator=(Queue&& que)
        {
            std::swap(this->head, que.head);
            std::swap(this->tail, que.tail);
            return *this;
        }
        Queue& operator=(const Queue& que) {
            if (&que == this)
                return *this;
            Queue copy(que);
            std::swap(*this, copy);
            return *this;
        }
        ~Queue() {
            while (head != tail)
                pop();
            delete head;
        }


        bool empty() { return head == tail; }
        void push(const T& data)
        {
            tail->next = new Node{ new T(data) , head };
            tail = tail->next;
        }
        void push(T&& data)
        {
            tail->next = new Node{ new T(std::move(data)) , head };
            tail = tail->next;
        }
        void pop()
        {
            if (head != tail)
            {
                Node* tmp = head->next->next;
                delete tail->next;
                tail = tmp;
            }
        }
        const T& front() { return *(head->next->data); }



    private:
        Node* head;
        Node* tail;
    };





}
