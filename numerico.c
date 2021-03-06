/* ************************************************************************ *
 *    Programa que integra metodos da disciplina de Calculo Numerico        *
 *                                                                          *
 *    Copyright (C) 2018 by Douglas Azevedo Pereira Dantas                  *
 *                                                                          *
 *    This program is free software; you can redistribute it and/or modify  *
 *    it under the terms of the GNU General Public License as published by  *
 *    the Free Software Foundation; either version 2 of the License, or     *
 *    (at your option) any later version.                                   *
 *                                                                          *
 *    This program is distributed in the hope that it will be useful,       *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *    GNU General Public License for more details.                          *
 *                                                                          *
 *    You should have received a copy of the GNU General Public License     *
 *    along with this program; if not, write to the                         *
 *    Free Software Foundation, Inc.,                                       *
 *    59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 *                                                                          *
 *    To contact the author, please write to:                               *
 *    Douglas Azevedo Pereira Dantas <douglasazevedo839@gmail.com>          *
 *    Webpage: https://github.com/DodoAz                                    *
 *    Phone: +55 (81) 99158-2473                                            *
 * ************************************************************************ *
 * 
 */

#include <stdio.h>
#include <stdlib.h>

void FatLU(int, int);
void ElimGauss(int, int);
int menu(void);

int main()
{
    int n, nsol;
    int metodo;

    printf("Hello world!\n");

    printf("Qual o tamanho da matriz?\n");
    scanf("%i", &n);

    printf("Qual o numero de solucoes?\n");
    scanf("%i", &nsol);

    metodo = menu();
    switch(metodo)
    {
        case 1:
            ElimGauss(n, nsol);
            break;
        case 2:
            FatLU(n, nsol);
            break;
        default:
            printf("Metodo nao implementado\n");
            break;
    }

    return 0;
}

int menu(void)
{
    int ans;

    printf("Que metodo deve ser usado para solucao?\n");

    printf("1 - Eliminacao de Gauss\n");
    printf("2 - Fatoracao LU\n");

    printf("Metodo: ");
    scanf("%i", &ans);

    return ans;
}

void FatLU(int n, int nsol)
{
    int i, j, k, w;
    double sum; 
    double A[n][n+1], L[n][n]; 
    double Sx[nsol+1][n], Sy[nsol+1][n]; 
    //double Xmax, dAmax; 

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            (i == j)? (L[i][j] = 1.0): (L[i][j] = 0.0);

    for (i = 0; i < n; i++)
        for (j = 0; j < n+1; j++)
        {
            printf("A[%i][%i]: ", i, j);
            scanf("%lf", &A[i][j]);
        }

    puts("\n");

    for (j = 0; j < n; j++)
    {
        printf("Sx[0][%i]: ", j);
        scanf("%lf", &Sx[0][j]);
    }
    
    puts("\n");
    
    for (j = 0; j < n; j++)
    {
        printf("Sy[0][%i]: ", j);
        scanf("%lf", &Sy[0][j]);
    }

    printf("\n\nSistema Recebido:\n");
    for(i = 0, putchar('{'); i < n; i++) 
    {
        for(j = 0, printf("■("); j < n; j++)
            printf("%+.4lfx_%i^((k))  ", A[i][j], j + 1);
        printf("= %.4lf", A[i][n]);
        if(i != (n-1))
            printf("@");
    }
    for(j = 0; j < n; j++)
        putchar(')');
    printf("┤");

    printf("\n\nTransforma-se o sistema nas seguintes matrizes:\n");
    printf("[A^((0))]=|■(");
    for(i = 0; i < n; i++)
    {
        for(j = 0, printf("■("); j < n; j++)
        {
            printf("%.4lf", A[i][j]);
            j == (n-1) ? putchar(')') : putchar('&');
        }
        i == (n-1) ? printf(")|"): putchar('@');
    }

    printf("\n[b]=|■(");
    for(i = 0; i < n; i++)
    {
        printf("%.4lf", A[i][n]);
        i == (n-1) ? puts(")|"): putchar('@');
    }

    for (j = 0; j < n; j++)
        for (i = j + 1; i < n; i++)
        {
            L[i][j] = A[i][j] / A[j][j];
            for (k = 0; k < n; k++)
                A[i][k] = A[i][k] - L[i][j] * A[j][k];
        }

    printf("\nMatriz Triangular Superior (U):\n");
    for(i = 0; i < n; putchar('\n'),i++)
        for(j = 0; j < n; j++)
            printf("%.4lf  ", A[i][j]);

    printf("\nMatriz Triangular Inferior (L):\n");
    for(i = 0; i < n; putchar('\n'), i++)
        for(j = 0; j < n; j++)
            printf("%.4lf  ", L[i][j]);

    for (w = 0; w < nsol + 1; w++)
    {
        for (j = 0; j < n; j++)
        {
            sum = 0;
            for (i = 0; i < j; i++)
                sum += L[j][i] * Sy[w][i];
            Sy[w + 1][j] = Sy[w] [j] + A[j][n] - sum;
        }

        for (i = n - 1; i >= 0; i--)
        {
            sum = 0;
            for (j = i + 1; j < n; j++)
                sum = sum + A[i][j] * Sx[w][j];
            Sx[w + 1][i] = Sx[w][i] + (Sy[w][i] - sum) / A[i][i];
        }
    }

    printf("\n*****************************************************\n");
    printf("%d Solucoes de X:\n", nsol);
    for(w = 0; w < nsol+1; w++)
    {
        printf("\nSx(%d): ", w);
        for(j=0; j < n; j++)
            printf("%.4lf ",Sx[w][j]);
    }
    printf("\n*****************************************************\n");

    printf("\n*****************************************************\n");
    printf("%d Solucoes de Y:\n", nsol);
    for(w = 0; w < nsol+1; w++)
    {
        printf("\nSy(%d): ", w);
        for(j=0; j < n; j++)
            printf("%.4lf ",Sy[w][j]);
    }
    printf("\n*****************************************************\n");

    return;
}

void ElimGauss(int n, int nsol)
{
    int i, j, k, w;
    double m, sum; 
    double A[n][n+1]; 
    double Sx[nsol+1][n];
    /*
       double dr[nsol][n]; 
       double Xmax, dAmax; 
       */

    for (i = 0; i < n; i++)
        for (j = 0; j < n+1; j++)
        {
            printf("A[%i][%i]: ", i, j);
            scanf("%lf", &A[i][j]);
        }

    puts("\n");
    for (j = 0; j < n; j++)
    {
        printf("Sx[0][%i]: ", j);
        scanf("%lf", &Sx[0][j]);
    }

    printf("\n\nMatriz recebida:\n");
    for(i = 0; i < n;  printf("= %.4lf\n", A[i][n]), i++)
        for(j = 0; j < n; j++)
            printf("%.4lf  ", A[i][j]);

    for (j = 0; j < n; j++)
        for (i = j + 1; i < n; i++)
        {
            m = A[i][j] / A[j][j];
            for (k = 0; k < n; k++)
                A[i][k] = A[i][k] - m * A[j][k];
        }

    printf("\nMatriz Triangular Superior:\n");
    for(i = 0; i < n; printf("= %.4lf\n", A[i][n]), i++)
        for(j = 0; j < n; j++)
            printf("%.4lf  ", A[i][j]);

    for (w = 0; w < nsol + 1; w++)
        for (i = n - 1; i >= 0; i--)
        {
            sum = 0;
            for (j = i + 1; j < n; j++)
                sum = sum + A[i][j] * Sx[w][j];
            Sx[w + 1][i] = Sx[w][i] + (A[i][n] - sum) / A[i][i];
        }

    printf("\n*****************************************************\n");
    printf("%d Solucoes de X:\n", nsol);
    for(w = 0; w < nsol+1; w++)
    {
        printf("\nSx(%d): ", w);
        for(j=0; j < n; j++)
            printf("%.4lf ",Sx[w][j]);
    }
    printf("\n*****************************************************\n");

    return;
}

