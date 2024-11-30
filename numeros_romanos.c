#include <stdio.h>
#include <string.h>


void inverte(char str[]) {
	/*Função que inverte a string recebida.
	Será necessária pois a conversão é feita de trás para frente.*/
	int tamanho = strlen(str), i;
	char inv[tamanho + 1];
	strcpy(inv, str);
	for (i = 0; i < tamanho; i++){
		str[i] = inv[tamanho - 1 - i];
	}
	str[i] = '\0';
}


void converte (char strinvert[], int n) {
	/*Função que converte o número recebido para números romanos.
	O vetor menor[] contém os números romanos que correspondem ao menor algarismo numa faixa de potência de 10,
	que são I = 1, X = 10, C = 100 e M = 1000.
	O vetor maior[] contém os números romanos que correspondem ao maior algarismo numa faixa de potência de 10,
	que são V = 5, L = 50 e D = 500.
	Os vetores repetem a sequência para números maiores que 3999, seguindo a lógica da numeração romana, 
	que coloca um traço sobre os números a partir de 4000. Neste programa os traços são substituídos por dois underscores.*/
	char menor[] = {'I', 'X', 'C', 'M', 'X', 'C', 'M'};
	char maior[]= {'V', 'L', 'D', 'V', 'L', 'D'};
	
	/*Inicialização de variáveis. 
	"i" corresponde ao índice atual dos vetores menor e maior.
	"j" será usado na iteração em caso de números que precisam de múltiplas unidades (ex: 3 = III).
	"divisor" é o divisor atual que será usado na operação de resto, mudando em multiplos de 10.
	"controle" é o índice atual da string que armazenará os números romanos.
	"resto" é o resto da divisão entre o número e o divisor atual.
	"razao" é o número pelo qual o resto precisa ser dividido para ficar entre 1 e 9.
	"resto2" é o resto da divisão entre (resto/razao) e 5, e vai ser util para o programa saber quantas unidades menores vão ser necessárias na iteração.
	"mediano" é 5 * razao e representa o número médio da faixa (5, 50, 500), com o qual o resto será comparado.
	"milhares" informa se o número entrou nos milhares acima de 3999 (nesse caso os números romanos mudam de lógica).*/
	int i = 0, j, divisor = 1, controle = 0, resto, razao, resto2, mediano, milhares = 0;
	
	while (divisor <= n) {
		divisor *= 10;
		resto = n % divisor;
		if (resto) {
			razao = divisor / 10;
			mediano = 5 * razao;
			resto2 = resto / razao % 5;
			
			/*O quarto elemento do vetor menor armazena M, porém, na lógica dos números romanos, 
			se o número for maior que 3999 o M é trocado por I.*/
			if (i == 3 && resto >= 4000) {
				menor[i] = 'I';
			}
			
			/*Adição de underscore em números de 4000 para cima.
			A variável milhares garante que seja apenas um (outro será adicionado só no fim)*/
			if (resto >= 4000 && !milhares) {
				strinvert[controle] = '_';
				controle++;
				milhares = 1;
			}
			
			/*No caso em que o resto2 não dê 4, o programa irá adiocionar por iteração a quantidade necessária de unidades menores.*/
			if (resto2 != 4) {
				for (j = 0; j < resto2; j++) {
					strinvert[controle] = menor[i];
					controle++;
				}
				/*Se o resto for maior ou igual ao número médio, a unidade maior deve ser adicionada.*/
				if (resto >= mediano) {
					strinvert[controle] = maior[i];
					controle++;
				}
			}
			else {
				/*Se o resto2 for 4, significa que o número na faixa atual tem a lógica romana de subtração da unidade maior
				pela unidade menor que vem logo antes (IV = 4, IX = 9, XL = 40, XC = 90 etc).
				Se o resto for menor que o número médio, o que será subtraído é a unidade maior da faixa atual. É o caso do IV (4), por exemplo.
				Mas se ele for maior, o que será subtraído é a unidade menor da faixa seguinte (i + 1). Exemplo: XC (90).*/
				if (resto < mediano) {
					strinvert[controle] = maior[i];
				}
				else {
					strinvert[controle] = menor[i+1];
				}
				controle++;
				/*Depois é necessário adicionar a unidade menor da faixa atual 
				(lembrando que a string está invertida, então ela virá antes no fim).*/
				strinvert[controle] = menor[i];
				controle++;	
			}
		}
		i++;
		n -= resto;
	}
	
	/*Se o número ultrapassou a quantidade de 3999, milhares foi acionado e é necessário adicionar um underscore final.*/
	if (milhares) {
		strinvert[controle] = '_';
		controle++;
	}
	
	strinvert[controle] = '\0';
	inverte(strinvert);
}


int main() {
	char s[20];
	int num = 0;
	printf("Este programa converte um n\243mero inteiro entre 1 e 1 milh\706o para n\243meros romanos.\nDigite um n\243mero inteiro entre 1 e 1.000.000: ");
	scanf("%d", &num);
	if (num < 1 || num > 1000000) printf("Input inv\240lido.");
	else{
		converte(s, num);
		printf("%s", s);	
	}
	return 0;
}


