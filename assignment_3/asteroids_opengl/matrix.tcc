#include "matrix.h"
#include <iostream>


template <class FLOAT, size_t N>
SquareMatrix<FLOAT, N>::SquareMatrix(std::initializer_list< Vector<FLOAT, N > > values) {
  std::copy(values.begin(), values.end(), matrix.begin());
}

template <class FLOAT, size_t N>
Vector<FLOAT, N> & SquareMatrix<FLOAT, N>::operator[](std::size_t i) {
  return matrix[i];
 }
template <class FLOAT, size_t N> 
Vector<FLOAT, N> SquareMatrix<FLOAT, N>::operator[](std::size_t i) const {
  return matrix[i];
    
   
}
template <class FLOAT, size_t N>
FLOAT SquareMatrix<FLOAT, N>::at(size_t row, size_t column) const {
  return matrix[column][row];
}
template <class FLOAT, size_t N>
FLOAT & SquareMatrix<FLOAT, N>::at(size_t row, size_t column) {
  return matrix[column][row];
}
template <class FLOAT, size_t N>
Vector<FLOAT,N> SquareMatrix<FLOAT, N>::operator*(const Vector<FLOAT,N> vector) {
  Vector<FLOAT,N> product;
  for (size_t i = 0u; i < N; i++) {
    product[i] = matrix[i]* vector;
  }
  return product;
}
template <class FLOAT, size_t N>
SquareMatrix<FLOAT, N> operator*(const SquareMatrix<FLOAT, N> factor1, const SquareMatrix<FLOAT, N> factor2) {
  SquareMatrix<FLOAT, N> product = factor1;
  
  for (size_t i = 0; i < N-1; i++) {
    
    for (size_t j = 0; j < N-1; j++) {
      product[i][j] = 0;
       for(size_t k = 0; k < N-1; k++) {
       
      
        product[i][j] += factor1.at(j,k)*factor2.at(k,i);
        }
      
    }
  }
  return product;
}
