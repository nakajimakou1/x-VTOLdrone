/*
 * kalman_dlqe3.c
 *
 * Code generation for function 'kalman_dlqe3'
 *
 * C source code generated on: Tue Feb 19 15:26:31 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "kalman_dlqe3.h"
#include "randn.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static real32_T rt_powf_snf(real32_T u0, real32_T u1);

/* Function Definitions */
static real32_T rt_powf_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  real32_T f1;
  real32_T f2;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = ((real32_T)rtNaN);
  } else {
    f1 = (real32_T)fabs(u0);
    f2 = (real32_T)fabs(u1);
    if (rtIsInfF(u1)) {
      if (f1 == 1.0F) {
        y = ((real32_T)rtNaN);
      } else if (f1 > 1.0F) {
        if (u1 > 0.0F) {
          y = ((real32_T)rtInf);
        } else {
          y = 0.0F;
        }
      } else if (u1 > 0.0F) {
        y = 0.0F;
      } else {
        y = ((real32_T)rtInf);
      }
    } else if (f2 == 0.0F) {
      y = 1.0F;
    } else if (f2 == 1.0F) {
      if (u1 > 0.0F) {
        y = u0;
      } else {
        y = 1.0F / u0;
      }
    } else if (u1 == 2.0F) {
      y = u0 * u0;
    } else if ((u1 == 0.5F) && (u0 >= 0.0F)) {
      y = (real32_T)sqrt(u0);
    } else if ((u0 < 0.0F) && (u1 > (real32_T)floor(u1))) {
      y = ((real32_T)rtNaN);
    } else {
      y = (real32_T)pow(u0, u1);
    }
  }

  return y;
}

void kalman_dlqe3(real32_T dt, real32_T k1, real32_T k2, real32_T k3, const
                  real32_T x_aposteriori_k[3], real32_T z, real32_T posUpdate,
                  real32_T addNoise, real32_T sigma, real32_T x_aposteriori[3])
{
  real32_T A[9];
  int32_T i0;
  static const int8_T iv0[3] = { 0, 0, 1 };

  real_T b;
  real32_T y;
  real32_T b_y[3];
  int32_T i1;
  static const int8_T iv1[3] = { 1, 0, 0 };

  real32_T b_k1[3];
  real32_T f0;
  A[0] = 1.0F;
  A[3] = dt;
  A[6] = 0.5F * rt_powf_snf(dt, 2.0F);
  A[1] = 0.0F;
  A[4] = 1.0F;
  A[7] = dt;
  for (i0 = 0; i0 < 3; i0++) {
    A[2 + 3 * i0] = (real32_T)iv0[i0];
  }

  if (addNoise == 1.0F) {
    b = randn();
    z += sigma * (real32_T)b;
  }

  if (posUpdate != 0.0F) {
    y = 0.0F;
    for (i0 = 0; i0 < 3; i0++) {
      b_y[i0] = 0.0F;
      for (i1 = 0; i1 < 3; i1++) {
        b_y[i0] += (real32_T)iv1[i1] * A[i1 + 3 * i0];
      }

      y += b_y[i0] * x_aposteriori_k[i0];
    }

    y = z - y;
    b_k1[0] = k1;
    b_k1[1] = k2;
    b_k1[2] = k3;
    for (i0 = 0; i0 < 3; i0++) {
      f0 = 0.0F;
      for (i1 = 0; i1 < 3; i1++) {
        f0 += A[i0 + 3 * i1] * x_aposteriori_k[i1];
      }

      x_aposteriori[i0] = f0 + b_k1[i0] * y;
    }
  } else {
    for (i0 = 0; i0 < 3; i0++) {
      x_aposteriori[i0] = 0.0F;
      for (i1 = 0; i1 < 3; i1++) {
        x_aposteriori[i0] += A[i0 + 3 * i1] * x_aposteriori_k[i1];
      }
    }
  }
}

/* End of code generation (kalman_dlqe3.c) */
