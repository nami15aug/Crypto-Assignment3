#include<stdio.h>
#include<math.h>
#include <time.h>
#include <sys/time.h>
#include <openssl/aes.h>
#include <openssl/bn.h>
#include <openssl/applink.c>

#define USE_REGULAR_RSA 0

/**
 * @brief       Returns the GCD of two input numbers
 * @param [in]  a  input number
 * @param [in]  b  input number
 * @return      GCD of a and b
 */
int gcd(int a, int b)
{
    int temp;
    while (1)
    {
        temp = a%b;
        if (temp == 0)
          return b;
        a = b;
        b = temp;
    }
}

/**
 * @brief       Returns inverse of a number modulo m
 * @param [in]  a  input number
 * @param [in]  modulo value
 * @return      inverse of a modulo m
 */
int inverse(int a, int m)
{
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    /* Apply Extended Euclid Algorithm */
    while (a > 1)
    {
        /* q is quotient */
        q = a / m;
        t = m;

        /* m is remainder now, process same as euclid's algo */
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    /* Make x1 positive */
    if (x1 < 0)
        x1 += m0;
    return x1;
}

int main()
{
    /* Two random prime numbers */
    double p = 5;
    double q = 13;

    /* First part of public key */
    double n = p*q;

    /* Finding other part of public key */
    /* e stands for encrypt */
    double e = 5;
    double phi = (p-1)*(q-1);


    while (e < phi)
    {
        /* e must be co-prime to phi and smaller than phi */
        if (gcd(e, phi)==1)
            break;
        else
            e++;
    }

    /* Private key (d stands for decrypt) */
    /*choosing d such that it satisfies d*e = 1 + k * totient */

    int k = 3;  // a constant value
    double d = (1 + (k*phi))/e;

    /* Message to be encrypted */
    double msg = 7;

    printf("Message data = %lf", msg);

    /* RSA Encryption c = (msg ^ e) % n */
    double c = pow(msg, e);
    c = fmod(c, n);
    printf("\nRSA Encrypted data = %lf", c);

    /* Calculate the time taken by Decryption */
    clock_t t;
    t = clock();

    struct timeval start, end;

    gettimeofday(&start, NULL);

#if USE_REGULAR_RSA
    /* RSA Decryption m = (c ^ d) % n */

    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *r = BN_new();
    BIGNUM *a = BN_new();
    BIGNUM *p1 = BN_new();
    BIGNUM *m = BN_new();

    BN_set_word(a, c);
    BN_set_word(p1, d);
    BN_set_word(m, n);

    BN_mod_exp(r, a, p1, m, ctx);

    printf("\nRSA Decrypted data  :\n");
    BN_print_fp(stdout, r);
    puts("");

    BN_free(r);
    BN_free(a);
    BN_free(p1);
    BN_free(m);
    BN_CTX_free(ctx);

#else

    /* RSA Decryption using CRT */
    int dp = fmod(d,p-1);
    int dq = fmod(d,q-1);

    int n1 = pow((int)c, dp);
    int n2 = pow((int)c, dq);;

    double xp = fmod(n1, p);
    double xq = fmod(n2, q);

    double mp = xp * q * inverse(q,p);
    double mq = xq * p * inverse(p,q);

    printf("\nRSA Decrypted data using CRT = %lf\n", fmod(mp+mq, n));

#endif

    gettimeofday(&end, NULL);

    long seconds = (end.tv_sec - start.tv_sec);
    long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    printf("The elapsed time is %d seconds and %d micros\n", seconds, micros);

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;

    printf("fun() took %f seconds to execute \n", time_taken);

    return 0;
}
