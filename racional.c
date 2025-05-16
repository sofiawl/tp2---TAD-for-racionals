#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "racional.h"

//retorna um número "aleatório" entre max e min
long aleat (long min, long max)
{
  return min + rand()%(max-min + 1) ;
}

//retorna o máximo divisor comum de a e b
long mdc (long a, long b)
{
	if (a == b)
		return a ;

	if (a % b == 0)
		return b ;

	return mdc(b, a % b) ;
}

//retorna o máximo multiplo comum de a e b
long mmc ( long a, long b)
{
	return a * b / mdc(a, b) ;
}

//simplifica e ajusta os sinais do racional
struct racional simplifica_r (struct racional r)
{
	long divisor ;

	if (r.den == 0)
		return r ;

	divisor = mdc(r.num, r.den) ;

	r.num /= divisor ;
	r.den /= divisor ;


	if (r.den < 0) 
	{
		r.num = -r.num ;
		r.den = -r.den ;
	}

	return r ;
}


/*retorna um  número do tipo racional com o numerador e o denominador
e simplifica ele */
struct racional cria_r (long numerador, long denominador)
{
	struct racional r ;

	r.num = numerador ;
	r.den = denominador ;

	r = simplifica_r(r) ;

	return r ;
}

//verifica se o número é inválido(dividido por 0)
int valido_r (struct racional r)
{
	if (r.den == 0)
		return 0 ;

	return 1 ;
}

//retorna um racional aleatório simplificado
struct racional sorteia_r (long min, long max)
{
	long numerador, denominador ;
	struct racional r ;

	numerador = aleat(min, max) ;
	denominador = aleat(min, max) ;

	r = cria_r(numerador, denominador) ;

	r = simplifica_r(r) ;

	return r ;
}

//imprime os racionais de acordo com as exigências do tp2
void imprime_r (struct racional r)
{ //nao pode imprimir espaços em branco aqui
	if (r.den == 0)
	{
		printf("NaN") ;
		return ;
	}

	if (r.num == 0)
	{
		printf("0") ;
		return ;
	}

	if (r.den == 1)
	{
		printf("%ld", r.num) ;
		return ;
	}

	if (r.den == r.num)
	{
		printf("1") ;
		return ;
  }

	 printf("%ld/%ld", r.num, r.den) ;
	return ;
}

int compara_r (struct racional r1, struct racional r2)
{
	if (!valido_r(r1) || !valido_r(r2))
		return -2 ;
	
	if ((r1.num * r2.den) < (r2.num * r1.den)) //r1 é menor
		return -1 ;

	
	if ((r1.num * r2.den) > (r2.num * r1.den)) //r1 é maior
		return 1 ;


	return 0 ; //se os numeros forem iguais ele retorna 0
}

//soma de r1 e r2 no parâmetro *r3
int soma_r (struct racional r1, struct racional r2, struct racional *r3)
{
	long multcomum ;  //Máximo multiplo comum
	
	if (!r3)
		return 0 ;

	if (!valido_r(r1) || !valido_r(r2))
		return 0 ;

	multcomum = mmc(r1.den, r2.den) ;
	r3->den = multcomum ;

	r3->num = (multcomum/r1.den) * r1.num + (multcomum/r2.den) * r2.num ;

  *r3 = simplifica_r(*r3) ;

	return 1 ;
}

//subtração de r1 e r2 no parâmetro *r3
int subtrai_r (struct racional r1, struct racional r2, struct racional *r3)
{
	long multcomum ;

	if (!r3)
		return 0 ;
	
	if (!valido_r(r1) || !valido_r(r2))
		return 0 ;
	
	multcomum = mmc(r1.den, r2.den) ;
	r3->den = multcomum ;

	r3->num = (multcomum/r1.den) * r1.num - (multcomum/r2.den) * r2.num ;

	*r3 = simplifica_r(*r3) ;

	return 1 ;
}

 //multiplicação  de r1 e r2 no parâmetro *r3
int multiplica_r (struct racional r1, struct racional r2, struct racional *r3)
{
	if (!r3)
    return 0 ;

	if(!valido_r(r1) || !valido_r(r2))
		return 0 ;

  r3->num = r1.num * r2.num ;
  r3->den = r1.den * r2.den ;

  *r3 = simplifica_r(*r3) ;

  return 1 ;
}
//divisão de r1 e r2 no parâmetro *r3
int divide_r (struct racional r1, struct racional r2, struct racional *r3)
{
  if (!r3)
    return 0 ;

	if(!valido_r(r1) || !valido_r(r2))
    return 0 ;

  r3->num = r1.num * r2.den ;
  r3->den = r1.den * r2.num ;

  *r3 = simplifica_r(*r3) ;

  return 1 ;
}
