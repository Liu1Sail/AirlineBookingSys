#pragma once
#include <initializer_list>
#include <algorithm>
namespace Utils {
    template<class T>
    class Array
    {
    private:
        unsigned m_uCapacity;
        unsigned  m_uSize;
        T* m_pObjects = nullptr;
    public:
        explicit Array(unsigned int uInitSize = 0) : m_uCapacity(uInitSize + 16), m_uSize(uInitSize) {
            m_pObjects = new T[m_uCapacity];
        }
        Array(const Array& initArray) : m_uCapacity(initArray.m_uCapacity), m_uSize(initArray.m_uSize) {
            m_pObjects = new T[m_uCapacity];
            for (int i = 0; i < m_uSize; ++i)
            {
                m_pObjects[i] = initArray.m_pObjects[i];
                // 从非右值 拷贝的话不应该使用迁移资产的std::move
            }
        }
        Array(Array&& initArray) : m_uCapacity(initArray.m_uCapacity), m_uSize(initArray.m_uSize), m_pObjects(initArray.m_pObjects) {
            initArray.m_pObjects = nullptr;
        }
        Array(const std::initializer_list<T>& initList) : m_uCapacity(initList.size()), m_uSize(0), m_pObjects(new T[m_uCapacity])
        {
            for (const auto& ele : initList)
            {
                this->push_back(ele);
            }
        }
        ~Array() {
            delete[] m_pObjects;
        }
        Array& operator=(const Array& otherArray)
        {
            if (&otherArray == this)
                return *this;

            //代码服用 不是最有效率的
            auto copy = otherArray;
            std::swap(*this, copy);
            return *this;
        }
        Array& operator=(Array&& otherArray)
        {
            std::swap(m_uCapacity, otherArray.m_uCapacity);
            std::swap(m_uSize, otherArray.m_uSize);
            std::swap(m_pObjects, otherArray.m_pObjects);
            return *this;
        }

        typedef  T* iterator;
        typedef const T* const_iterator;

        iterator begin() {
            return m_pObjects;
        }
        const_iterator begin()const {
            return m_pObjects;
        }
        iterator end() {
            return m_pObjects + m_uSize;
        }
        const_iterator end()const {
            return m_pObjects + m_uSize;
        }

        T& operator[](int iIndex) {
            return m_pObjects[iIndex];
        }
        const T& operator[](int iIndex) const {
            return m_pObjects[iIndex];
        }

        void reverse(unsigned uNewCapacity) {
            if (m_uSize > uNewCapacity)
                return;
            T* pNewObjects = new T[uNewCapacity];
            for (int i = 0; i < m_uSize; ++i)
            {
                pNewObjects[i] = std::move(m_pObjects[i]);
            }
            std::swap(m_pObjects, pNewObjects);
            delete[]pNewObjects;
        }
        void resize(unsigned uNewSize) {
            if (uNewSize > m_uCapacity)
                reverse(uNewSize * 2);
            m_uSize = uNewSize;
        }

        bool empty() const {
            return m_uSize == 0;
        }
        unsigned size() const {
            return m_uSize;
        }
        unsigned capacity() const {
            return m_uCapacity;
        }




        void push_back(const T& object)
        {
            if (m_uSize >= m_uCapacity)
                reverse(m_uSize * 2 + 1);
            m_pObjects[m_uSize] = object;
            m_uSize++;
        }
        void push_back(T&& object) {
            if (m_uSize >= m_uCapacity)
                reverse(m_uSize * 2 + 1);
            m_pObjects[m_uSize] = std::move(object);
            m_uSize++;
        }

    };


}