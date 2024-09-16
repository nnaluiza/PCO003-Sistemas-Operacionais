#include "philosophers.h"  // Inclui o cabeçalho com as definições necessárias para o código.

/*
** Função 'ft_isdigit': verifica se o caractere passado como argumento é um dígito numérico (entre '0' e '9').
** Retorna 1 (verdadeiro) se o caractere for um dígito, caso contrário retorna 0 (falso).
*/
int	ft_isdigit(int c)
{
	// Verifica se o valor de 'c' está entre os caracteres '0' e '9' na tabela ASCII.
	return (c >= '0' && c <= '9');  // Se 'c' for um número entre '0' e '9', retorna 1, senão retorna 0.
}
