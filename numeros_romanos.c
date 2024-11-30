#include <stdio.h>
#include <string.h>

void converte (char strinvert[], int n) {
	char menor[] = {'I', 'X', 'C', 'M', 'X', 'C', 'M'};
	char maior[]= {'V', 'L', 'D', 'V', 'L', 'D'};
	int i = 0, divisor = 1, controle = 0, resto, resto2, o, p, q, j;
	while (divisor <= n) {
		divisor *= 10;
		resto = n % divisor;
		if (resto) {
			p = divisor / 10;
			o = resto / p;
			q = 4 * p;
			resto2 = o % 5;
			if (i == 3 && resto >= 4000) {
				menor[i] = 'I';
			}
			if (resto >= 4000) {
				strinvert[controle] = 95;
				controle++;
			}
			if (resto2 != 4) {
				for (j = 0; j < resto2; j++) {
					strinvert[controle] = menor[i];
					controle++;
				}
				if (resto > q) {
					strinvert[controle] = maior[i];
					controle++;
				}
			}
			else {
				if (resto < 5 * p) {
					strinvert[controle] = maior[i];
				}
				else {
					strinvert[controle] = menor[i+1];
				}
				controle++;
				strinvert[controle] = menor[i];
				controle++;	
			}
			if (resto >= 4000) {
				strinvert[controle] = 95;
				controle++;
				}
		}
		i++;
		n -= resto;
	}
	strinvert[controle] = '\0';
}

void inverte(char str[]) {
	int tamanho = strlen(str), i;
	char inv[tamanho + 1];
	strcpy(inv, str);
	for (i = 0; i < tamanho; i++){
		str[i] = inv[tamanho - 1 - i];
	}
	str[i] = '\0';
}


int main() {
	char s[20];
	int num = 0;
	printf("Este programa converte um numero inteiro entre 1 e 1 milhao para numeros romanos.\nDigite um numero inteiro entre 1 e 1.000.000: ");
	scanf("%d", &num);
	if (num < 1 || num > 1000000) printf("Input invalido.");
	else{
		converte(s, num);
		inverte(s);
		printf("%s", s);	
	}
	return 0;
}

