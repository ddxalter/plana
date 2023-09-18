#ifndef PLANA_DENSE_H_
#define PLANA_DENSE_H_

#include "plana/common.h"

// low level basic linear algebra functions for dense data

namespace plana {
namespace dense {

void set(const int n, const float32_t alpha, float32_t* x, const int incx)
{
  for(int i = 0; i < n; ++i)
  {
    x[i * incx] = alpha;
  }
}

void zeros(const int n, float32_t* x, const int incx)
{
  for(int i = 0; i < n; ++i)
  {
    x[i * incx] = 0.f;
  }
}

void copy(const int n, const float32_t* x, const int incx, float32_t* y, const int incy)
{
  for(int i = 0; i < n; ++i)
  {
    y[i * incy] = x[i * incx];
  }
}

float32_t dot(const int n, const float32_t* x, const int incx, const float32_t* y, const int incy)
{
  float32_t result = 0.f;
  
  for(int i = 0; i < n; ++i)
  {
    result += x[i * incx] * y[i * incy];
  }
  
  return result;
}

void axpy(const int n, const float32_t alpha, const float32_t* x, const int incx,
          float32_t* y, const int incy)
{
  for(int i = 0; i < n; ++i)
  {
    y[i] = alpha * x[i] + y[i];
  }
}

void scal(const int n, const float32_t alpha, float32_t* x, const int incx)
{
  for(int i = 0; i < n; ++i)
  {
    x[i * incx] *= alpha;
  }
}

void gemv(const char trans, const int m, const int n, const float32_t alpha,
          const float32_t* A, const int lda, const float32_t* x, const int incx,
          const float32_t beta, float32_t* y, const int incy)
{
  if(trans == 'N' || trans == 'n')
  {
    for(int i = 0; i < m; ++i)
    {
      float32_t aix = 0.f;
      
      for(int j = 0; j < n; ++j)
      {
        aix += A[i * lda + j] * x[j * incx];
      }
      
      y[i * incy] = alpha * aix + beta * y[i * incy];
    }
  }
  else if(trans == 'T' || trans == 't')
  {
    for(int i = 0; i < m; ++i)
    {
      y[i * incy] = beta * y[i * incy];
    }
    
    for(int j = 0; j < n; ++j)
    {
      for(int i = 0; i < m; ++i)
      {
        y[i * incy] += alpha * A[j * lda + i] * x[j * incx];
      }
    }
  }
}

} // namespace dense
} // namespace plana

#endif // PLANA_DENSE_H_
