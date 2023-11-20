// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <cassert>
#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz == 0||sz>MAX_VECTOR_SIZE)
            throw out_of_range("Vector size should be greater than zero");
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        for (size_t i = 0; i < sz; i++) {
            pMem[i] = v.pMem[i];
        }
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        pMem = nullptr;
        swap(*this, v);
    }
    ~TDynamicVector()
    {
        delete[] pMem;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this != &v) {
            if (sz != v.sz) {
                T* p = new T[v.sz];
                delete[] pMem;
                sz = v.sz;
                pMem = p;
            }
            for (size_t i = 0; i < sz; i++) {
                pMem[i] = v.pMem[i];
            }   
        }
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        swap(*this, v);
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
    {
        if (ind < 0 || ind >= sz) {
            throw out_of_range("Index out of range");
    }
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        if (ind < 0 || ind >= sz) {
            throw out_of_range("Index out of range");
        }
        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind < 0 || ind >= sz ){
            throw out_of_range("Index out of range");
        }
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind < 0 || ind >= sz) {
            throw out_of_range("Index out of range");
        }
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        bool res = true;
        if (sz != v.sz) {
            res = false;
        }
        else
            for (size_t i = 0; i < sz; i++) {
                if (pMem[i] != v.pMem[i])
                    res = false;
            }
        return res;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        if (*this == v)
            return false;
        else return true;
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] + val;
        }
        return res;
    }
    TDynamicVector operator-(T val)
    {
       
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] - val;
        }
        return res;
    }
    TDynamicVector operator*(T val)
    {
       
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] * val;
        }
        return res;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz) {
            throw invalid_argument("Vector sizes do not match");
        }
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] + v.pMem[i];
        }
        return res;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz) {
            throw invalid_argument("Vector sizes do not match");
        }
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] -v.pMem[i];
        }
        return res;
    }
    T operator*(const TDynamicVector& v) 
    {
        if (sz != v.sz) {
            throw invalid_argument("Vector sizes do not match");
        }
        T res = 0;
        for (size_t i = 0; i < sz; i++) {
            res += pMem[i] * v.pMem[i];
        }
        return res;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (s < 0 || s >= MAX_MATRIX_SIZE)
            throw out_of_range("a");
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        bool res = true;
        if (sz !=m.sz) {
            res = false;
        }
        else
            for (size_t i = 0; i < sz; i++) {
                if (pMem[i].operator!=( m.pMem[i]))
                    res = false;
            }
        return res;
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++) {
            pMem[i] *= val;
        }
        return res;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.sz) {
            throw invalid_argument("Vector sizes do not match");
        }
        TDynamicVector <T> res(sz);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] * v;
        }
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz) {
            throw invalid_argument("Vector sizes do not match");
        }
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++)
            res.pMem[i] = pMem[i] + m.pMem[i];
        return res;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz) {
            throw invalid_argument("Vector sizes do not match");
    }
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++)
            res.pMem[i] = pMem[i] -m.pMem[i];
        return res;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz) {
            throw invalid_argument("Vector sizes do not match");
        }
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++)
            for (size_t j = 0; j < sz; j++)
                for (size_t k = 0; k < sz; k++)
                    res.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
        return res; 
    }
    size_t size() const noexcept { return sz; }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++) {
            istr >> v.pMem[i];
        }
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++) {
            ostr <<v. pMem[i] << endl;
        }
        return ostr;
    }

};
#endif