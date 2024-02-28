#pragma once

#include <utility>

namespace Utils
{
    template<typename T>
    class Stack
    {
    public:
        bool empty() { return !(pTop->next); }
        void push(T&& data) {
            pTop->next = new Node{ new T(std::move(data)) , pTop->next };
        }
        void push(const T& data) {
            pTop->next = new Node{ new T(data) , pTop->next };
        }
        void pop() {
            if (!empty())
            {
                auto tmp = pTop->next;
                pTop->next = tmp->next;
                delete tmp;
            }
        }
        const T& top() {
            return *(pTop->next->data);
        }

        Stack() { pTop = new Node{ nullptr , nullptr }; }
        Stack(const Stack& st) :Stack() {
            auto p = st.pTop->next;
            while (p)
                push(*p->data);
        }
        Stack(Stack&& st) :Stack() { std::swap(pTop, st.pTop); }
        ~Stack()
        {
            while (!empty())
                pop();
            delete pTop;
        }
        Stack& operator=(const Stack& st) {
            if (&st == this)
                return *this;
            Stack s(st);
            std::swap(*this, s);
            return *this;
        }
        Stack& operator=(Stack&& st) {
            std::swap(st.pTop, this->pTop);
            return *this;
        }
    private:
        struct Node
        {
            T* data;
            Node* next;
            ~Node() { delete data; }
        };
        Node* pTop;
    };
}

