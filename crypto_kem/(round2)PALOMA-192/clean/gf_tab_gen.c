/*
 * Copyright (c) 2024 FDL(Future cryptography Design Lab.) Kookmin University
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "gf_tab_gen.h"

/**
 * @brief print all table
 *
 * @param [in] gf2m_tables tables for efficient arithmetic over GF(2^m).
 */
void print_all_tab(IN const gf2m_tab* gf2m_tables)
{
    print_mul_tab(gf2m_tables);
    print_square_tab(gf2m_tables->square_tab);
    print_sqrt_tab(gf2m_tables->sqrt_tab);
    print_inv_tab(gf2m_tables->inv_tab);
}

/**
 * @brief generate precomputation table
 *
 * @param [out] gf2m_tables tables for efficient arithmetic over GF(2^m).
 */
void gen_precomputation_tab(OUT gf2m_tab* gf2m_tables)
{
    gen_mul_tab(gf2m_tables);
    gen_square_tab(gf2m_tables->square_tab);
    gen_sqrt_tab(gf2m_tables->sqrt_tab);
    gen_inv_tab(gf2m_tables->inv_tab);
}

/**
 * @brief generate gf2m multiplication table
 *
 * @param [out] gf2m_tables tables for efficient arithmetic over GF(2^m).
 */
void gen_mul_tab(OUT gf2m_tab* gf2m_tables)
{
    gf A1_z7, B1_z7;

    for (gf i = 0; i < (1 << GF2M_SPLIT_LOW); i++)
    {
        for (gf j = 0; j < (1 << GF2M_SPLIT_LOW); j++)
        {
            gf2m_tables->mul_00_tab[i][j] = gf2m_mul(i, j); // lower 7bit

            if ((i < (1 << GF2M_SPLIT_HIGH)) && (j < (1 << GF2M_SPLIT_HIGH)))
            {
                A1_z7 = (i << GF2M_SPLIT_LOW); // times z^7
                B1_z7 = (j << GF2M_SPLIT_LOW); // times z^7

                // upper 6bit
                gf2m_tables->mul_11_tab[i][j] = gf2m_mul(A1_z7, B1_z7); 
            }

            if (i < (1 << GF2M_SPLIT_HIGH))
            {
                A1_z7 = (i << GF2M_SPLIT_LOW); // times z^7
                
                // upper 6bit x lower 7bit
                gf2m_tables->mul_10_tab[i][j] = gf2m_mul(A1_z7, j); 
            }
        }
    }
}

/**
 * @brief generate gf2m square table
 *
 * @param [out] gf2m_tables tables for efficient arithmetic over GF(2^m).
 */
void gen_square_tab(OUT gf* square_tab)
{
    for (gf i = 0; i < BITSIZE; i++)
    {
        square_tab[i] = gf2m_square(i);
    }
}

/**
 * @brief generate gf2m square root table
 *
 * @param [out] gf2m_tables tables for efficient arithmetic over GF(2^m).
 */
void gen_sqrt_tab(OUT gf* sqrt_tab)
{
    for (gf i = 0; i < BITSIZE; i++)
    {
        sqrt_tab[i] = gf2m_sqrt(i);
    }
}

/**
 * @brief generate gf2m inverse table
 *
 * @param [out] gf2m_tables tables for efficient arithmetic over GF(2^m).
 */
void gen_inv_tab(OUT gf* inv_tab)
{
    for (gf i = 0; i < BITSIZE; i++)
    {
        inv_tab[i] = gf2m_inv(i);
    }
}

/**
 * @brief print mul table
 *
 * @param [in] gf2m_tables tables for efficient arithmetic over GF(2^m).
 */
void print_mul_tab(IN const gf2m_tab* gf2m_tables)
{
    printf("GF2M MUL TABLE ={ {");

    int count = 0;

    for (gf i = 0; i < (1 << GF2M_SPLIT_HIGH); i++)
    {
        printf("{");
        for (gf j = 0; j < (1 << GF2M_SPLIT_HIGH); j++)
        {
            printf("0x%04x", gf2m_tables->mul_11_tab[i][j]);
            if (j != GF2M_SPLIT_MASK_HIGH_BIT)
                printf(", ");
            count++;
            if ((count % 20) == 0)
                printf("\n      ");
        }
        printf("}");
        if (i != GF2M_SPLIT_MASK_HIGH_BIT)
            printf(",");
    }
    printf("},\n");

    printf("   {");
    count = 0;
    for (gf i = 0; i < (1 << GF2M_SPLIT_HIGH); i++)
    {
        printf("{");
        for (gf j = 0; j < (1 << GF2M_SPLIT_LOW); j++)
        {
            printf("0x%04x", gf2m_tables->mul_10_tab[i][j]);
            if (j != GF2M_SPLIT_MASK_LOW_BIT)
                printf(", ");
            count++;
            if ((count % 20) == 0)
                printf("\n      ");
        }
        printf("}");
        if (i != GF2M_SPLIT_MASK_HIGH_BIT)
            printf(",");
    }
    printf("},\n");

    printf("   {");

    count = 0;
    for (gf i = 0; i < (1 << GF2M_SPLIT_LOW); i++)
    {
        printf("{");
        for (gf j = 0; j < (1 << GF2M_SPLIT_LOW); j++)
        {
            printf("0x%04x", gf2m_tables->mul_00_tab[i][j]);
            if (j != GF2M_SPLIT_MASK_HIGH_BIT)
                printf(", ");
            count++;
            if ((count % 20) == 0)
                printf("\n      ");
        }
        printf("}");
        if (i != GF2M_SPLIT_MASK_HIGH_BIT)
            printf(",");
    }
    printf("}};\n");
}

/**
 * @brief print square table
 *
 * @param [in] gf2m_tables tables for efficient arithmetic over GF(2^m).
 */
void print_square_tab(IN const gf* square_tab)
{
    printf("GF2M MUL TABLE = {");

    for (gf j = 0; j < BITSIZE; j++)
    {
        printf("0x%04x", square_tab[j]);
        if (j != 0x1FFF)
            printf(", ");
        if ((j + 1) % 20 == 0)
            printf("\n      ");
    }
    printf("};\n");
}

/**
 * @brief print sqrt table
 *
 * @param [in] gf2m_tables tables for efficient arithmetic over GF(2^m).
 */
void print_sqrt_tab(IN const gf* sqrt_tab)
{
    printf("gf2m sqrt_tab = {");

    for (gf j = 0; j < BITSIZE; j++)
    {
        printf("0x%04x", sqrt_tab[j]);
        if (j != 0x1FFF)
            printf(", ");
        if ((j + 1) % 20 == 0)
            printf("\n      ");
    }
    printf("};\n");
}

/**
 * @brief print inv table
 *
 * @param [in] gf2m_tables tables for efficient arithmetic over GF(2^m).
 */
void print_inv_tab(IN const gf* inv_tab)
{
    printf("gf2m inv_tab [(1<<GF2M_DEG)] = {");

    for (gf j = 0; j < BITSIZE; j++)
    {
        printf("0x%04x", inv_tab[j]);
        if (j != 0x1FFF)
            printf(", ");
        if ((j + 1) % 20 == 0)
            printf("\n      ");
    }
    printf("};\n");
}

/**
 * @brief gf2m table performance measurement function
 *
 * @param [in] gf2m_tables tables for efficient arithmetic over GF(2^m).
 */
void gf2m_performance(IN const gf2m_tab* gf2m_tables)
{
    clock_t start, end;
    double res;
    int count = 10000000;
    gf finite_a, finite_b;
    srand(time(NULL));

    /**************  Addition  **************/
    finite_a = rand() % 0x1FFF;
    finite_b = rand() % 0x1FFF;

    start = clock();
    for (int i = 0; i < count; i++)
    {
        finite_a = gf2m_add(finite_a, finite_b);
    }
    end = clock();
    res = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%lf sec. ", res);
    printf("%d-ADD over GF(2^m)\n", count);

    /**************  Multiplication  **************/
    finite_a = rand() % 0x1FFF;
    finite_b = rand() % 0x1FFF;

    start = clock();
    for (int i = 0; i < count; i++)
    {
        finite_a = gf2m_mul(finite_a, finite_b);
    }
    end = clock();
    res = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%lf sec. ", res);
    printf("%d-MUL over GF(2^m)\n", count);

    start = clock();
    for (int i = 0; i < count; i++)
    {
        finite_a = gf2m_mul_w_tab(finite_a, finite_b, gf2m_tables);
    }
    end = clock();
    res = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%lf sec. ", res);
    printf("%d-MUL over GF(2^m) with TABLE\n", count);

    /**************  Square  **************/
    finite_a = rand() % 0x1FFF;

    start = clock();
    for (int i = 0; i < count; i++)
    {
        finite_a = gf2m_square(finite_a);
    }
    end = clock();
    res = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%lf sec. ", res);
    printf("%d-SQU over GF(2^m)\n", count);

    start = clock();
    for (int i = 0; i < count; i++)
    {
        finite_a = gf2m_square_w_tab(finite_a, gf2m_tables->square_tab);
    }
    end = clock();
    res = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%lf sec. ", res);
    printf("%d-SQU over GF(2^m) with TABLE\n", count);

    /**************  Square root  **************/
    finite_a = rand() % 0x1FFF;

    start = clock();
    for (int i = 0; i < count; i++)
    {
        finite_a = gf2m_sqrt(finite_a);
    }
    end = clock();
    res = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%lf sec. ", res);
    printf("%d-SQRT over GF(2^m)\n", count);

    start = clock();
    for (int i = 0; i < count; i++)
    {
        finite_a = gf2m_sqrt_w_tab(finite_a, gf2m_tables->sqrt_tab);
    }
    end = clock();
    res = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%lf sec. ", res);
    printf("%d-SQRT over GF(2^m) with TABLE\n", count);

    /**************  Inverse  **************/
    finite_a = rand() % 0x1FFF;

    start = clock();
    for (int i = 0; i < count; i++)
    {
        finite_a = gf2m_inv(finite_a);
    }
    end = clock();
    res = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%lf sec. ", res);
    printf("%d-INV over GF(2^m)\n", count);

    start = clock();
    for (int i = 0; i < count; i++)
    {
        finite_a = gf2m_inv_w_tab(finite_a, gf2m_tables->inv_tab);
    }
    end = clock();
    res = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%lf sec. ", res);
    printf("%d-INV over GF(2^m) with TABLE\n", count);
}

/**
 * @brief gf2m table verification
 *
 * @param [in] gf2m_tables tables for efficient arithmetic over GF(2^m).
 */
void tab_verify_check(IN const gf2m_tab* gf2m_tables)
{
    int count = 1000000;
    srand(time(NULL));

    /**************  Multiplication  **************/
    gf finite_a, finite_b;
    finite_a = rand() % 0x1FFF;
    finite_b = rand() % 0x1FFF;
    gf finite_c = finite_a;

    for (int i = 0; i <= count; i++)
    {
        finite_a = gf2m_mul(finite_a, finite_b);
        finite_c = gf2m_mul_w_tab(finite_c, finite_b, gf2m_tables);
        if (finite_a != finite_c)
            printf("error!!\n");
    }
    printf("Multiplication Check\n");

    /**************  Square  **************/
    finite_a = rand() % 0x1FFF;
    finite_c = finite_a;

    for (int i = 0; i <= count; i++)
    {
        finite_a = gf2m_square(finite_a);
        finite_c = gf2m_square_w_tab(finite_c, gf2m_tables->square_tab);
        if (finite_a != finite_c)
            printf("error!!\n");
    }
    printf("Square check \n");

    /**************  Square root  **************/
    finite_a = rand() % 0x1FFF;
    finite_c = finite_a;

    for (int i = 0; i <= count; i++)
    {
        finite_a = gf2m_sqrt(finite_a);
        finite_c = gf2m_sqrt_w_tab(finite_c, gf2m_tables->sqrt_tab);
        if (finite_a != finite_c)
            printf("error!!\n");
    }
    printf("Square root check \n");

    /**************  Inverse  **************/
    finite_a = rand() % 0x1FFF;
    finite_c = finite_a;

    for (int i = 0; i <= count; i++)
    {
        finite_a = gf2m_inv(finite_a);
        finite_c = gf2m_inv_w_tab(finite_c, gf2m_tables->inv_tab);
        if (finite_a != finite_c)
            printf("error!!\n");
    }
    printf("Inverse check \n");
}
