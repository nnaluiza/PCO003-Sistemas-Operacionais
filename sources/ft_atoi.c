#include "philosophers.h"  // Inclui o cabeçalho com as definições necessárias para o código.

/*
** Função 'ft_atoi': converte uma string que representa um número para um inteiro (int).
** Similar à função padrão 'atoi' da biblioteca C.
*/
int	ft_atoi(const char *nptr)
{
	int		sign;  // Variável para armazenar o sinal (positivo ou negativo).
	int		res;   // Variável para armazenar o resultado final.

	// Ignora espaços em branco e caracteres de controle (como '\n', '\t').
	while ((*nptr && *nptr == ' ') || (*nptr >= 9 && *nptr <= 13))  // Verifica por espaços e tabulações.
		nptr++;  // Avança o ponteiro enquanto encontrar espaços ou caracteres de controle.

	sign = 1;  // Inicializa o sinal como positivo.
	// Verifica se há um sinal '+' ou '-' antes do número.
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')  // Se for o sinal de menos ('-'), define o sinal como negativo.
			sign = -sign;  // Muda o sinal para negativo.
		nptr++;  // Avança o ponteiro para o próximo caractere.
	}

	res = 0;  // Inicializa o resultado como 0.
	// Converte a sequência de caracteres numéricos para um valor inteiro.
	while (*nptr && (*nptr >= '0' && *nptr <= '9'))  // Enquanto o caractere for um dígito (entre '0' e '9').
	{
		// Calcula o valor numérico multiplicando o resultado atual por 10 e somando o dígito atual.
		res = (res * 10) + (*nptr - '0');  // O caractere numérico é convertido para o valor correspondente ('0' = 48 na tabela ASCII).
		nptr++;  // Avança o ponteiro para o próximo caractere.
	}

	// Retorna o resultado final multiplicado pelo sinal.
	// Isso garante que o número seja positivo ou negativo, dependendo do sinal.
	return (res * sign);
}
