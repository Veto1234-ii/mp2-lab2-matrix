﻿// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

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
  TDynamicVector(size_t size = 1) 
  {

      if (size == 0)
          throw 1;

      if (size > MAX_VECTOR_SIZE)
          throw 2;

      sz = size;

      pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }

  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");

    pMem = new T[sz];

    std::copy(arr, arr + sz, pMem);

  }

  TDynamicVector(const TDynamicVector& v)// контсруктор копирования
  {
      sz = v.sz;
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);

  }

  TDynamicVector(TDynamicVector&& v) noexcept
  {
      pMem = nullptr;
      swap(*this, v);
  }

  ~TDynamicVector()
  {
      delete[]pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v)
          return *this;

      TDynamicVector tmp(v);
      swap(*this, tmp);

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
      if (ind < 0 || ind >= sz)
          throw 3;
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      if (ind < 0 || ind >= sz)
          throw 3;

      const T& tm = pMem[ind];
      return tm;
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if ((ind < 0) || (ind >= sz))
          throw 3;
      return pMem[ind];

  }
  const T& at(size_t ind) const
  {
      if ((ind < 0) || (ind >= sz))
          throw 3;

      const T& tm = pMem[ind];
      return tm;
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const //noexcept
  {
      if (this == &v)
          return true;

      if (sz != v.sz)
          return false;

      for (int i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i])
              return false;
      }

      return true;

  }
  bool operator!=(const TDynamicVector& v) const //noexcept
  {
      if (this == &v)
          return false;

      if (sz != v.sz)
          return true;

      for (int i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i])
              return true;
      }

      return false;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector tmp(sz);

      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] + val;

      return tmp;
  }

  TDynamicVector operator-(double val)
  {
      TDynamicVector tmp(sz);

      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] - val;

      return tmp;
  }

  TDynamicVector operator*(double val)
  {
      TDynamicVector tmp(sz);

      for (size_t i = 0; i < sz; i++)

          tmp.pMem[i] = pMem[i] * val;

      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw -2;

      TDynamicVector tmp(v.sz);

      for (int i = 0; i < sz && i < v.sz; i++)
          tmp.pMem[i] = pMem[i] + v.pMem[i];

      return tmp;
  }

  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw - 2;

      TDynamicVector tmp(v.sz);

      for (int i = 0; i < sz && i < v.sz; i++)
          tmp.pMem[i] = pMem[i] - v.pMem[i];

      return tmp;
  }

  T operator*(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw - 2;

      int res = 0;

      for (size_t i = 0; i < sz; i++)
          res += pMem[i] * v.pMem[i];

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

    TDynamicMatrix transpose(const TDynamicMatrix& m) {

        TDynamicMatrix tmp(m.sz);

        for (int i = 0; i < m.sz; i++)
            for (int j = 0; j < m.sz; j++)

                tmp[i][j] = m[j][i];

        return tmp;
    }

public:

    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (s > MAX_MATRIX_SIZE)
            throw 1;

        for (size_t i = 0; i < s; i++)
            pMem[i] = TDynamicVector<T>(s);
    }

    TDynamicMatrix(const TDynamicVector<TDynamicVector<T>>& v) : TDynamicVector<TDynamicVector<T>>(v) {}

    using TDynamicVector<TDynamicVector<T>>::operator[];
    // сравнение

    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        return TDynamicVector<TDynamicVector<T>>::operator==(m);
    }

    // матрично-скалярные операции
    TDynamicMatrix<T> operator*(const double val)
    {
        return TDynamicVector<TDynamicVector<T>>::operator*(val);
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        TDynamicVector<T> tmp(sz);

        for (int i = 0; i < sz; i++)
            tmp[i] = pMem[i] * v;

        return tmp;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw -3;

        TDynamicMatrix tmp(sz);

        for (int i = 0; i < sz; i++)
            tmp.pMem[i] = pMem[i] + m.pMem[i];

        return tmp;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw -3;

        TDynamicMatrix tmp(sz);

        for (int i = 0; i < sz; i++)
            tmp.pMem[i] = pMem[i] - m.pMem[i];

        return tmp;
    }

    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw -3;

        TDynamicMatrix res(sz);

        TDynamicMatrix tmp = transpose(m);

        for (int i = 0; i < sz; i++)
            for (int j = 0; j < sz; j++)

                res[i][j] = pMem[i] * tmp[j];

        return res;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << endl; // требуется оператор<< для типа T
        return ostr;
    }
};

#endif


