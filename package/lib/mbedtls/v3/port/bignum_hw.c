/*
 *  Multi-precision integer library for HW acceleration
 *
 *  Copyright (c) 2025 Newracom Inc. All rights reserved.
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */

#include "config-nrc-basic.h"

#if defined(MBEDTLS_BIGNUM_C)

#include "mbedtls/bignum.h"
#include "mbedtls/platform_util.h"
#include "mbedtls/error.h"
#include "drv_sec.h"

#include <string.h>
#include "mbedtls/platform.h"

#define WORD_OPERATION
//#define BIGNUM_SHOW_RESULT

#define ciL    (sizeof(mbedtls_mpi_uint))         /* chars in limb  */
#define biL    (ciL << 3)               /* bits  in limb  */
#define biH    (ciL << 2)               /* half limb size */

/*
 * Convert between bits/chars and number of limbs
 * Divide first in order to avoid potential overflows
 */
#define BITS_TO_LIMBS(i)  ( (i) / biL + ( (i) % biL != 0 ) )
#define CHARS_TO_LIMBS(i) ( (i) / ciL + ( (i) % ciL != 0 ) )

static uint32_t bignum_get_real_length(const mbedtls_mpi *X)
{
    int j;
    for( j = (X->n-1); j > 0; j-- )
        if( X->p[j] != 0 )
            return j+1;
    return 0;
}

/*
 ret : 
    value    : first bigger index 
    positive : X > Y
    negative : Y < X
*/
static int bignum_cmp_idx(const mbedtls_mpi *X, const mbedtls_mpi *Y)
{
    int i,j, s = 0;
    i = bignum_get_real_length(X);
    j = bignum_get_real_length(Y);

    if(i > j)
        return i;
    else if(i < j)
        return -j;
    
    for(;i > 0; i--)    
    {
        s = (X->p[i] > Y->p[i]);

        if(X->p[i] != Y->p[i])
        {
            return s * i;
        }
    }
    return 0;
}

/*
 * Left-shift: X <<= count
 *
 * TODO: Please check the real operation when its HW is supported.
 */
int mbedtls_mpi_shift_l_hw( mbedtls_mpi *X, size_t count )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    size_t i, v0, t1;
    mbedtls_mpi_uint r0 = 0, r1;

#ifdef BIGNUM_SHOW_RESULT
    bignum_print("A", X);
#endif

    v0 = count / (biL    );
    t1 = count & (biL - 1);

    i = mbedtls_mpi_bitlen( X ) + count;

    if( X->n * biL < i )
        MBEDTLS_MPI_CHK( mbedtls_mpi_grow( X, BITS_TO_LIMBS( i ) ) );


    bignum_clear_op( BIGNUM_OPN_CLR |
                     BIGNUM_OPA_CLR |
                     BIGNUM_OPB_CLR );

    ret = 0;
    
    #ifdef  WORD_OPERATION
        bignum_opA32 ((const uint32_t*)X->p, 0, X->n);
        bignum_opB32 ((const uint32_t*)&count, 0, 1);
    #else
        bignum_opA ((const uint8_t*)X->p, 0, X->n*4);
        bignum_opB ((const uint8_t*)&count, 0, 4);
    #endif  

    bignum_configure(BIGNUM_MODE_SHIFT_L);
    bignum_start ();

    if(bignum_is_done()) {
    #ifdef  WORD_OPERATION
            //TODO : mpi_grow 
            bignum_get32_result ((uint32_t*)X->p, X->n);
    #else
            //TODO : mpi_grow 
            bignum_get_result ((uint8_t*)X->p, X->n*4);
    #endif  
    }

cleanup:
#ifdef BIGNUM_SHOW_RESULT
    mbedtls_printf("B     : %d\n", count);
    bignum_print("A << B", X);
    mbedtls_printf("rtn   : %d\n", ret);
#endif
    return( ret );
}

/*
 * Right-shift: X >>= count
 *
 * TODO: Please check the real operation when its HW is supported.
 */
int mbedtls_mpi_shift_r_hw( mbedtls_mpi *X, size_t count )
{
    size_t i, v0, v1, ret = 0;
    mbedtls_mpi_uint r0 = 0, r1;

#ifdef BIGNUM_SHOW_RESULT
    bignum_print("A", X);
#endif

    v0 = count /  biL;
    v1 = count & (biL - 1);

    if( v0 > X->n || ( v0 == X->n && v1 > 0 ) )
    {
        ret = mbedtls_mpi_lset( X, 0 );
    #ifdef BIGNUM_SHOW_RESULT
        mbedtls_printf("rtn_R : %d\n", ret);
    #endif
        return ret;
    }

    
    bignum_clear_op( BIGNUM_OPN_CLR |
                     BIGNUM_OPA_CLR |
                     BIGNUM_OPB_CLR );

    #ifdef  WORD_OPERATION
        bignum_opA32 ((const uint32_t*)X->p, 0, X->n);
        bignum_opB32 ((const uint32_t*)&count, 0, 1);
    #else
        bignum_opA ((const uint8_t*)X->p, 0, X->n*4);
        bignum_opB ((const uint8_t*)&count, 0, 4);
    #endif  

    bignum_configure(BIGNUM_MODE_SHIFT_R);
    bignum_start ();

    if(bignum_is_done()) {
    #ifdef  WORD_OPERATION
            //TODO : mpi_shrink
            bignum_get32_result ((uint32_t*)X->p, X->n);
    #else
            //TODO : mpi_shrink
            bignum_get_result ((uint8_t*)X->p, X->n*4);
    #endif  
    }
#ifdef BIGNUM_SHOW_RESULT
    mbedtls_printf("B : %d\n", count);
    bignum_print("A >> B", X);
    mbedtls_printf("rtn : %d\n", ret);
#endif
    return( 0 );
}

/*
 * Unsigned addition: X = |A| + |B|  (HAC 14.7)
 *
 * TODO: Please check the real operation when its HW is supported.
 */
int mbedtls_mpi_add_abs_hw( mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B )
{
    int ret;
    size_t i, j;
    mbedtls_mpi_uint *o, *p, c, tmp = 0;

    X->s = 1;

    bignum_clear_op( BIGNUM_OPN_CLR |
                     BIGNUM_OPA_CLR |
                     BIGNUM_OPB_CLR );

    #ifdef  WORD_OPERATION
        bignum_opA32 ((const uint32_t*)A->p, 0, A->n);
        bignum_opB32 ((const uint32_t*)B->p, 0, B->n);
    #else
        bignum_opA ((const uint8_t*)A->p, 0, A->n*4);
        bignum_opB ((const uint8_t*)B->p, 0, B->n*4);
    #endif  

    bignum_configure(BIGNUM_MODE_ADD);
    bignum_start();

    for( j = B->n; j > 0; j-- )
        if( B->p[j - 1] != 0 )
            break;

    for( i = A->n; i > 0; i-- )
        if( A->p[i - 1] != 0 )
            break;

    if(i == j)
    {
        tmp = ((A->p[i-1] + B->p[j-1]));
        if(tmp < A->p[i-1])
        {
            // mbedtls_printf("TMP : %08lx, A : %08lx, B : %08lx, i : %d, j : %d\n", tmp, A->p[i-1], B->p[j-1], i, j);
            mbedtls_mpi_shrink( X, i + 1 );
        }
        else
        {
            mbedtls_mpi_shrink( X, i );   
        }
    }
    else
    {
        mbedtls_mpi_shrink( X, (i > j) ? i : j );
    }

    if(bignum_is_done()) {
    #ifdef  WORD_OPERATION
        bignum_get32_result ((uint32_t*)X->p, X->n);
    #else
        bignum_get_result ((uint8_t*)X->p, X->n*4);
    #endif  
    }
    else
    {
        A("[func: %s] Fail to read buffer\n", __func__);
    }

    return( 0 );
}

/*
 * Unsigned subtraction: X = |A| - |B|  (HAC 14.9, 14.10)
 *
 * TODO: Please check the real operation when its HW is supported.
 */
int mbedtls_mpi_sub_abs_hw( mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B )
{
    mbedtls_mpi TB;
    int ret = 0;
    size_t n;

    if( mbedtls_mpi_cmp_abs( A, B ) < 0 )
        return( MBEDTLS_ERR_MPI_NEGATIVE_VALUE );

    mbedtls_mpi_init( &TB );

    if( X == B )
    {
        mbedtls_mpi_copy( &TB, B );
        B = &TB;
    }

    if( X != A )
        mbedtls_mpi_copy( X, A );

    X->s = 1;

    bignum_clear_op( BIGNUM_OPN_CLR |
                     BIGNUM_OPA_CLR |
                     BIGNUM_OPB_CLR );
    #ifdef  WORD_OPERATION
        bignum_opA32 ((const uint32_t*)A->p, 0, A->n);
        bignum_opB32 ((const uint32_t*)B->p, 0, B->n);
    #else
        bignum_opA ((const uint8_t*)A->p, 0, A->n*4);
        bignum_opB ((const uint8_t*)B->p, 0, B->n*4);
    #endif  
        bignum_configure(BIGNUM_MODE_SUB);
        bignum_start();

    if(bignum_is_done()) {
    #ifdef  WORD_OPERATION
        //TODO : mpi_shrink
        bignum_get32_result ((uint32_t*)X->p, X->n);
    #else
        //TODO : mpi_shrink
        bignum_get_result ((uint8_t*)X->p, X->n*4);
    #endif  
    }

    mbedtls_mpi_free( &TB );

    return( ret );
}

/*
 * Baseline multiplication: X = A * B  (HAC 14.12)
 */
int mbedtls_mpi_mul_mpi_hw( mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B )
{
    int ret = 0;
    size_t i, j;

    for( i = A->n; i > 0; i-- )
        if( A->p[i - 1] != 0 )
            break;

    for( j = B->n; j > 0; j-- )
        if( B->p[j - 1] != 0 )
            break;

    bignum_clear_op( BIGNUM_OPN_CLR |
                     BIGNUM_OPA_CLR |
                     BIGNUM_OPB_CLR );

    #ifdef  WORD_OPERATION
        bignum_opA32 ((const uint32_t*)A->p, 0, A->n);
        bignum_opB32 ((const uint32_t*)B->p, 0, B->n);
    #else
        bignum_opA ((const uint8_t*)A->p, 0, A->n * 4);
        bignum_opB ((const uint8_t*)B->p, 0, B->n * 4);
    #endif  

    bignum_configure(BIGNUM_MODE_MUL);
    bignum_start ();

    mbedtls_mpi_grow( X, i + j );
    mbedtls_mpi_lset( X, 0 );

    if(bignum_is_done()) {
    #ifdef  WORD_OPERATION
        bignum_get32_result ((uint32_t*)X->p, X->n);
    #else
        bignum_get_result ((uint8_t*)X->p, X->n*4);
    #endif  
    } else {
        return -1;
    }

    X->s = A->s * B->s;

#ifdef BIGNUM_SHOW_RESULT
    bignum_print("A", A);
    bignum_print("B", B);
    bignum_print("A * B", X);
    mbedtls_printf("rtn : %d\n", ret);
#endif

    return( ret );
}

/*
 * Modulo: R = A mod B
 */
int mbedtls_mpi_mod_mpi_hw( mbedtls_mpi *R, const mbedtls_mpi *A, const mbedtls_mpi *B )
{
    int ret = 0;
    int length, sig;
    size_t i, j;

#ifdef BIGNUM_SHOW_RESULT
    bignum_print("MOD REAL A", A);
    bignum_print("MOD REAL B", B);
#endif

    bignum_clear_op( BIGNUM_OPN_CLR |
                     BIGNUM_OPA_CLR |
                     BIGNUM_OPB_CLR );

    #ifdef  WORD_OPERATION
        bignum_opA32 ((const uint32_t*)A->p, 0, A->n);
        if(A->n > 16)
            bignum_opB32 ((const uint32_t*)(A->p + 16), 0, (A->n-16));
        bignum_opN32 ((const uint32_t*)B->p, 0, B->n);
    #else
        bignum_opA ((const uint8_t*)A->p, 0, A->n * 4);
        bignum_opN ((const uint8_t*)B->p, 0, B->n * 4);
    #endif  

    bignum_configure(BIGNUM_MODE_MOD);
    bignum_start ();

    if( mbedtls_mpi_cmp_int( B, 0 ) < 0 )
        return( MBEDTLS_ERR_MPI_NEGATIVE_VALUE );

    i = bignum_get_real_length(A);
    j = bignum_get_real_length(B);
    if (i > 16 || j > 16) {
#if defined(INCLUDE_HW_SECURITY_ACC_BN_MOD)
        return mbedtls_mpi_mod_mpi_sw(R, A, B);
#else
        return mbedtls_mpi_mod_mpi(R, A, B);
#endif /* INCLUDE_HW_SECURITY_ACC_BN_MOD */
    }

    sig =  A->s * B->s;
    length = (i > j) ? j : i;

    mbedtls_mpi_shrink(R, length);
    mbedtls_mpi_lset(R, 0);

    if(bignum_is_done()) {
    #ifdef  WORD_OPERATION
        bignum_get32_result ((uint32_t*)R->p, R->n);
    #else
        bignum_get_result ((uint8_t*)R->p, R->n*4);
    #endif  
    } else {
        return -1;
    }

    if(sig < 0)
    {
        R->s = 1;
        mbedtls_mpi_sub_mpi(R, B, R);
        R->s = B->s;
    }

#ifdef BIGNUM_SHOW_RESULT
    bignum_print("A MOD B", R);
    mbedtls_printf("rtn : %d\n", ret);
#endif

    return( ret );
}

/*
 * Multiplication Modulo: X = A * B mod C
 */
int mbedtls_mpi_mul_mpi_mod_mpi( mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B, const mbedtls_mpi *C )
{
    int length, sig;
    size_t i, j, k;

    bignum_clear_op( BIGNUM_OPN_CLR |
                     BIGNUM_OPA_CLR |
                     BIGNUM_OPB_CLR );

    #ifdef  WORD_OPERATION
        bignum_opA32 ((const uint32_t*)A->p, 0, A->n);
        bignum_opB32 ((const uint32_t*)B->p, 0, B->n);
        bignum_opN32 ((const uint32_t*)C->p, 0, C->n);
    #else
        bignum_opA ((const uint8_t*)A->p, 0, A->n * 4);
        bignum_opB ((const uint8_t*)B->p, 0, B->n * 4);
        bignum_opN ((const uint8_t*)C->p, 0, C->n * 4);
    #endif  

    bignum_configure(BIGNUM_MODE_MULMOD);
    bignum_start ();

    if( mbedtls_mpi_cmp_int( C, 0 ) < 0 )
        return( MBEDTLS_ERR_MPI_NEGATIVE_VALUE );

    //Get length for calculate return size
    i = bignum_get_real_length(A);
    j = bignum_get_real_length(B);
    k = bignum_get_real_length(C);
    if (i > 16 || j > 16 || k > 16) {
#if defined(INCLUDE_HW_SECURITY_ACC_BN_MUL)
        if (mbedtls_mpi_mul_mpi_sw(X, A, B) != 0)
#else
        if (mbedtls_mpi_mul_mpi(X, A, B) != 0)
#endif /* INCLUDE_HW_SECURITY_ACC_BN_MUL */
        {
            return( MBEDTLS_ERR_MPI_BAD_INPUT_DATA );
        }
#if defined(INCLUDE_HW_SECURITY_ACC_BN_MOD)
        return mbedtls_mpi_mod_mpi_sw(X, X, C);
#else
        return mbedtls_mpi_mod_mpi(X, X, C);
#endif /* INCLUDE_HW_SECURITY_ACC_BN_MOD */
    }

    sig =  A->s * B->s;
    length = ((i+j) > k) ? k : (i+j);

    mbedtls_mpi_shrink(X, length);
    mbedtls_mpi_lset(X, 0);

    if(bignum_is_done()) {
    #ifdef  WORD_OPERATION
        bignum_get32_result ((uint32_t*)X->p, X->n);
    #else
        bignum_get_result ((uint8_t*)X->p, X->n*4);
    #endif  
    } else {
        return -1;
    }

    if(sig < 0)
    {
        X->s = 1;
        mbedtls_mpi_sub_abs(X, C, X);
        X->s = C->s;
    }

    return 0;
}

/*
 * Multiplication Modulo Ready: modulus N
 */
int mbedtls_mul_mod_ready( const mbedtls_mpi *N )
{
    if (bignum_get_real_length(N) > 16) {
        return( MBEDTLS_ERR_MPI_BAD_INPUT_DATA );
    }

    if(mbedtls_mpi_cmp_int(N, 0) < 0) {
        return( MBEDTLS_ERR_MPI_NEGATIVE_VALUE );
    }

    bignum_clear_op( BIGNUM_OPN_CLR | BIGNUM_OPA_CLR | BIGNUM_OPB_CLR );
#ifdef WORD_OPERATION
    bignum_opN32 ((const uint32_t*)N->p, 0, N->n);
#else
    bignum_opN ((const uint8_t*)N->p, 0, N->n * 4);
#endif
    bignum_configure(BIGNUM_MODE_MULMOD);

    return 0;
}

/*
 * Multiplication Modulo Start: A * B mod N
 */
int mbedtls_mul_mod_start( const mbedtls_mpi *A, const mbedtls_mpi *B, const mbedtls_mpi *N )
{
    int i, j;

    if (A->s * B->s < 0) {
        return( MBEDTLS_ERR_MPI_BAD_INPUT_DATA );
    }

    i = bignum_get_real_length(A);
    j = bignum_get_real_length(B);
    if (i > 16 || j > 16) {
        return( MBEDTLS_ERR_MPI_BAD_INPUT_DATA );
    }

    bignum_clear_op( BIGNUM_OPA_CLR | BIGNUM_OPB_CLR );
#ifdef WORD_OPERATION
    bignum_opA32 ((const uint32_t*)A->p, 0, A->n);
    bignum_opB32 ((const uint32_t*)B->p, 0, B->n);
#else
    bignum_opA ((const uint8_t*)A->p, 0, A->n * 4);
    bignum_opB ((const uint8_t*)B->p, 0, B->n * 4);
#endif
    bignum_start();

    return 0;
}

/*
 * Multiplication Modulo Done: X = A * B mod N
 */
int mbedtls_mul_mod_done( mbedtls_mpi *X, const mbedtls_mpi *N )
{
    mbedtls_mpi_shrink(X, N->n);
    mbedtls_mpi_lset(X, 0);
    if (bignum_is_done()) {
#ifdef WORD_OPERATION
        bignum_get32_result ((uint32_t*)X->p, X->n);
#else
        bignum_get_result ((uint8_t*)X->p, X->n * 4);
#endif
    } else {
        return -1;
    }

    return 0;
}

/*
 * Multiplication Modulo after Ready: X = A * B mod N
 */
int mbedtls_mul_mod( mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B, const mbedtls_mpi *N )
{
    return mbedtls_mul_mod_start( A, B, N ) | mbedtls_mul_mod_done( X, N );
}

/*
 * Scalar exponentiation: X = A^b mod C
 */
int mbedtls_mpi_exp_int_mod_mpi( mbedtls_mpi *X, const mbedtls_mpi *A, const uint32_t b, const mbedtls_mpi *C )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    int sig;
    mbedtls_mpi T;
    uint32_t d = 0, bit = 1;

    if (b == 0) {
        return mbedtls_mpi_lset(X, 1);
    }

    sig = (b & 0x1) ? A->s : 1;
    if (sig < 0 && X == A) {
        return -1;
    }

    mbedtls_mpi_shrink(X, bignum_get_real_length(C));
    if (X != A) {
        mbedtls_mpi_copy( X, A );
    }

    if (b == 1) {
        return mbedtls_mpi_mod_mpi( X, X, C );
    }

    mbedtls_mpi_init( &T );
    mbedtls_mpi_lset( &T, 1 );

    bignum_clear_op( BIGNUM_OPN_CLR |
                     BIGNUM_OPA_CLR |
                     BIGNUM_OPB_CLR );

    #ifdef  WORD_OPERATION
        bignum_opN32 ((const uint32_t*)C->p, 0, C->n);
    #else
        bignum_opN ((const uint8_t*)C->p, 0, C->n * 4);
    #endif

    bignum_configure(BIGNUM_MODE_MULMOD);

    while (b > d) {
        if (!((b ^ d) & bit)) {
            #ifdef  WORD_OPERATION
                bignum_opA32 ((const uint32_t*)X->p, 0, X->n);
                bignum_opB32 ((const uint32_t*)X->p, 0, X->n);
            #else
                bignum_opA ((const uint8_t*)X->p, 0, X->n * 4);
                bignum_opB ((const uint8_t*)X->p, 0, X->n * 4);
            #endif
        } else if (mbedtls_mpi_cmp_int( &T, 1 ) == 0) {
            mbedtls_mpi_copy( &T, X );
            d |= bit;
            continue;
        } else {
            #ifdef  WORD_OPERATION
                bignum_opA32 ((const uint32_t*)X->p, 0, X->n);
                bignum_opB32 ((const uint32_t*)T.p, 0, T.n);
            #else
                bignum_opA ((const uint8_t*)X->p, 0, X->n * 4);
                bignum_opB ((const uint8_t*)T.p, 0, T.n * 4);
            #endif
        }

        bignum_start();
        if (!bignum_is_done()) {
            goto cleanup;
        }

        if (!((b ^ d) & bit)) {
            #ifdef  WORD_OPERATION
                bignum_get32_result ((uint32_t*)X->p, X->n);
            #else
                bignum_get_result ((uint8_t*)X->p, X->n*4);
            #endif
            bit <<= 1;
        } else {
            #ifdef  WORD_OPERATION
                bignum_get32_result ((uint32_t*)T.p, T.n);
            #else
                bignum_get_result ((uint8_t*)T.p, T.n*4);
            #endif
            d |= bit;
        }
    }

    mbedtls_mpi_copy( X, &T );

    if (sig < 0) {
        X->s = 1;
        mbedtls_mpi_sub_abs(X, C, X);
        X->s = C->s;
    }
    ret = 0;

cleanup:
    mbedtls_mpi_free(&T);

    return ret;
}

/*
 * Modulo: X = A - B mod C
 *
 * TODO: Please check the real operation when its HW is supported.
 */
int mbedtls_mpi_sub_mpi_mod_mpi( mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B, const mbedtls_mpi *C )
{
    int length;
    int k;

    bignum_clear_op( BIGNUM_OPN_CLR |
                     BIGNUM_OPA_CLR |
                     BIGNUM_OPB_CLR );

    #ifdef  WORD_OPERATION
        bignum_opA32 ((const uint32_t*)A->p, 0, A->n);
        bignum_opB32 ((const uint32_t*)B->p, 0, B->n);
        bignum_opN32 ((const uint32_t*)C->p, 0, C->n);
    #else
        bignum_opA ((const uint8_t*)A->p, 0, A->n * 4);
        bignum_opB ((const uint8_t*)B->p, 0, B->n * 4);
        bignum_opN ((const uint8_t*)C->p, 0, C->n * 4);
    #endif  

    bignum_configure(BIGNUM_MODE_SUBMOD);
    bignum_start ();

    k = bignum_cmp_idx(A, B);
    
    if(k >= 0)
    {
        length = k;
    }
    else
    {
        length = C->n;
    }
    
    mbedtls_mpi_lset(X, 0);
    mbedtls_mpi_shrink( X, length);

    if(bignum_is_done()) {
    #ifdef  WORD_OPERATION
        bignum_get32_result ((uint32_t*)X->p, X->n);
    #else
        bignum_get_result ((uint8_t*)X->p, X->n*4);
    #endif  
    }

    if(k < 0)
    {
        X->s = 1;
        mbedtls_mpi_sub_abs(X, C, X);
        X->s = C->s;
    }

    return 0;
}

/*
 * Modulo: X = A + B mod C
 *
 * TODO: Please check the real operation when its HW is supported.
 */
int mbedtls_mpi_add_mpi_mod_mpi( mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B, const mbedtls_mpi *C )
{
    int length;
    int i,j,k;
    mbedtls_mpi_uint tmp;

    bignum_clear_op( BIGNUM_OPN_CLR |
                     BIGNUM_OPA_CLR |
                     BIGNUM_OPB_CLR );

    #ifdef  WORD_OPERATION
        bignum_opA32 ((const uint32_t*)A->p, 0, A->n);
        bignum_opB32 ((const uint32_t*)B->p, 0, B->n);
        bignum_opN32 ((const uint32_t*)C->p, 0, C->n);
    #else
        bignum_opA ((const uint8_t*)A->p, 0, A->n * 4);
        bignum_opB ((const uint8_t*)B->p, 0, B->n * 4);
        bignum_opN ((const uint8_t*)C->p, 0, C->n * 4);
    #endif  

    bignum_configure(BIGNUM_MODE_ADDMOD);
    bignum_start ();

    i = bignum_get_real_length(A);
    j = bignum_get_real_length(B);
    
    if(i == j)
    {
        tmp = ((A->p[i-1] + B->p[j-1]));
        if(tmp < A->p[i-1])
        {
            length = i + 1;
        }
        else
        {
            length = i;
        }
    }
    else
    {
        length = (i > j) ? i : j;
    }

    length = (length > C->n) ? C->n : length;
    
    mbedtls_mpi_lset(X, 0);
    mbedtls_mpi_shrink( X, length);

    if(bignum_is_done()) {
    #ifdef  WORD_OPERATION
        bignum_get32_result ((uint32_t*)X->p, X->n);
    #else
        bignum_get_result ((uint8_t*)X->p, X->n*4);
    #endif  
    }

    // if(s < 0)
    // {
    //     X->s = 1;
    //     mbedtls_mpi_sub_abs(X, C, X);
    //     X->s = C->s;
    // }

    return 0;
}

#endif /* MBEDTLS_BIGNUM_C */
