#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "racional.h"

const int MAX = 100 ;

//verifica se o numero está no intervalo adequadpo
int ver_intervalo(int n) 
{
	if (n >= 100 || n <= 0)
	{
		printf("NaN, deveria satisfazer 0 < n < 100.\n") ;
		return 0 ;
	}

	return 1 ;
}


void imprimeVetor(int n, struct racional v[])
{
	for (int i = 0; i < n; ++i)
	{
		imprime_r(v[i]) ;
		printf(" ") ;
	}
	printf("\n") ;

	return ;
}

int main ()
{
	int n, i, tam ; 
	struct racional v[MAX],	aux, soma ;
	long num ,den ;

	scanf("%d", &n) ; 	
	if (!ver_intervalo(n))
		return 0 ; 

//cria um vetor com valores racionais
	for (int i = 0; i < n; ++i)
	{
		scanf("%ld %ld", &num, &den) ;
		v[i] = cria_r(num, den) ;
	} 
	
	imprimeVetor(n, v) ;

//retira Nans do vetor
	i = 0 ;
	tam = n - 1 ; 

	while (i < tam)
	{
		if (!valido_r(v[i]))
		{
			while (tam > i && !valido_r(v[tam]))
				--tam;
			
			if (tam > i)
			{
				v[i] = v[tam] ;
				--tam ;
			}
		}
		
		++i ;
	}
	n = tam + 1;

	imprimeVetor(n, v) ;

//ordena o vetor com algoritmo bubblesort 
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n - i - 1; ++j)
	  { 
			if (compara_r( v[j], v[j + 1]) == 1)
			{
				aux = v[j] ;
				v[j] = v[j + 1] ;
				v[j + 1] = aux ;
			}
		}


	imprimeVetor(n, v) ;

//soma os numeros racionais
	soma = cria_r(0, 1) ;

	for (int i = 0; i < n; ++i)
	{
		soma_r(soma, v[i], &soma) ;
	} 
	
	printf("SOMA = ") ;
	imprime_r(soma) ; 
	printf("\n") ;
	
  return 0 ;
} 
