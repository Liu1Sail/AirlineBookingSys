#pragma once
#include <algorithm>

namespace Utils
{

    template<typename T>
    class List
    {

    private:
        struct node
        {
            T* m_pObject;
            node* m_pPrev;
            node* m_pNext;

            node(T* pObject = nullptr, node* prev = nullptr, node* next = nullptr) : m_pObject(pObject), m_pPrev(prev),
                m_pNext(next)
            {
            }

            ~node()
            {
                if (!m_pObject)return;
                m_pPrev->m_pNext = m_pNext;
                m_pNext->m_pPrev = m_pPrev;
                delete m_pObject;
            }
        };//node

        node* m_pHead;
        node* m_pTail;
        unsigned m_uSize;


    public:

        class iterator
        {
        protected:
            node* m_pNode;
        public:
            friend List;

            explicit iterator(node* pNode = nullptr) : m_pNode(pNode) {}

            bool operator==(const iterator& otherIterator) const {
                return m_pNode == otherIterator.m_pNode;
            }

            bool operator!=(const iterator& otherIterator) const {
                return m_pNode != otherIterator.m_pNode;
            }

            virtual iterator operator++(int)
            {
                iterator old(*this);
                ++(*this);
                return old;
            }

            virtual iterator& operator++()
            {
                m_pNode = m_pNode->m_pNext;
                return *this;
            }

            virtual iterator operator--(int)
            {
                auto old = *this;
                --(*this);
                return old;
            }

            virtual iterator& operator--() {
                m_pNode = m_pNode->m_pPrev;
                return *this;
            }

            virtual T& operator*() {
                return *(m_pNode->m_pObject);
            }
        };//iterator

        class const_iterator : public iterator
        {
        public:
            explicit const_iterator(node* pNode = nullptr) : iterator(pNode) {}

            const_iterator operator++(int)
            {
                const_iterator old(*this);
                ++(*this);
                return old;
            }

            const_iterator& operator++()
            {
                this->m_pNode = this->m_pNode->m_pNext;
                return *this;
            }

            const_iterator operator--(int)
            {
                auto old = *this;
                --(*this);
                return old;
            }

            const_iterator& operator--()
            {
                this->m_pNode = this->m_pNode->m_pPrev;
                return *this;
            }

            const T& operator*() {
                return iterator::operator*(*this);
            }
        };//const_iterator

        List() : m_uSize(0)
        {
            m_pHead = new node;
            m_pTail = new node;
            m_pHead->m_pNext = m_pTail;
            m_pTail->m_pPrev = m_pHead;
        }

        List(const List& otherList) : List()
        {
            for (auto& ele : otherList) {
                push_back(ele);
            }
        }

        List(List&& otherList) : List()
        {
            std::swap(m_uSize, otherList.m_uSize);
            std::swap(m_pHead, otherList.m_pHead);
            std::swap(m_pTail, otherList.m_pTail);
        }

        List& operator=(List&& otherList)
        {
            std::swap(m_uSize, otherList.m_uSize);
            std::swap(m_pHead, otherList.m_pHead);
            std::swap(m_pTail, otherList.m_pTail);
            return *this;
        }

        List& operator=(const List& otherList)
        {
            if (this == &otherList)return *this;
            auto copy = otherList;
            std::swap(*this, copy);
            return *this;
        }

        ~List()
        {
            clear();
            delete m_pHead;
            delete m_pTail;
        }

        void push_back(const T& object)
        {
            auto p = new node(new T(object), m_pTail->m_pPrev, m_pTail);
            p->m_pPrev->m_pNext = p;
            m_pTail->m_pPrev = p;
            m_uSize++;
        }

        void push_back(T&& object)
        {
            auto p = new node(new T(std::move(object)), m_pTail->m_pPrev, m_pTail);
            p->m_pPrev->m_pNext = p;
            m_pTail->m_pPrev = p;
            m_uSize++;
        }


        iterator begin() {
            return iterator(m_pHead->m_pNext);
        }

        const_iterator begin() const {
            return const_iterator(m_pHead->m_pNext);
        }

        iterator end() {
            return iterator(m_pTail);
        }

        const_iterator end() const
        {
            return const_iterator(m_pTail);
        }

        iterator find(const T& obj)
        {
            for (auto it = begin(); it != end(); it++)
            {
                if (*it == obj) {
                    return it;
                }
            }
            return end();
        }


        iterator insert(const iterator& itr, const T& obj)
        {
            auto p = new node(new T(obj), itr.m_pNode->m_pPrev, itr.m_pNode);
            p->m_pPrev->m_pNext = p;
            itr.m_pNode->m_pPrev = p;
            m_uSize++;
            return iterator(p);
        }

        iterator insert(const iterator& itr, T&& obj)
        {
            auto p = new node(new T(std::move(obj)), itr.m_pNode->m_pPrev, itr.m_pNode);
            p->m_pPrev->m_pNext = p;
            itr.m_pNode->m_pPrev = p;
            m_uSize++;
            return iterator(p);
        }

        unsigned size()
        {
            return m_uSize;
        }

        iterator erase(const iterator& itr)
        {
            iterator tmp(itr.m_pNode->m_pNext);
            delete itr.m_pNode;
            --m_uSize;
            return tmp;
        }

        iterator erase(const iterator& from, const iterator& to)
        {
            for (auto it = from; it != to;)
            {
                it = erase(it);
            }
            return to;
        }

        void clear() {
            erase(begin(), end());
        }

        void reverse()
        {
            std::swap(m_pHead, m_pTail);
            auto it = m_pHead;
            while (it)
            {
                std::swap(it->m_pNext, it->m_pPrev);
                it = it->m_pNext;
            }
        }

    };//List



} // MDS
