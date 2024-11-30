#include <stdio.h>
#include <string.h>


void inverte(char str[]) {
	/*Fun��o que inverte a string recebida.
	Ser� necess�ria pois a convers�o � feita de tr�s para frente.*/
	int tamanho = strlen(str), i;
	char inv[tamanho + 1];
	strcpy(inv, str);
	for (i = 0; i < tamanho; i++){
		str[i] = inv[tamanho - 1 - i];
	}
	str[i] = '\0';
}


void converte (char strinvert[], int n) {
	/*Fun��o que converte o n�mero recebido para n�meros romanos.
	O vetor menor[] cont�m os n�meros romanos que correspondem ao menor algarismo numa faixa de pot�ncia de 10,
	que s�o I = 1, X = 10, C = 100 e M = 1000.
	O vetor maior[] cont�m os n�meros romanos que correspondem ao maior algarismo numa faixa de pot�ncia de 10,
	que s�o V = 5, L = 50 e D = 500.
	Os vetores repetem a sequ�ncia para n�meros maiores que 3999, seguindo a l�gica da numera��o romana, 
	que coloca um tra�o sobre os n�meros a partir de 4000. Neste programa os tra�os s�o substitu�dos por dois underscores.*/
	char menor[] = {'I', 'X', 'C', 'M', 'X', 'C', 'M'};
	char maior[]= {'V', 'L', 'D', 'V', 'L', 'D'};
	
	/*Inicializa��o de vari�veis. 
	"i" corresponde ao �ndice atual dos vetores menor e maior.
	"j" ser� usado na itera��o em caso de n�meros que precisam de m�ltiplas unidades (ex: 3 = III).
	"divisor" � o divisor atual que ser� usado na opera��o de resto, mudando em multiplos de 10.
	"controle" � o �ndice atual da string que armazenar� os n�meros romanos.
	"resto" � o resto da divis�o entre o n�mero e o divisor atual.
	"razao" � o n�mero pelo qual o resto precisa ser dividido para ficar entre 1 e 9.
	"resto2" � o resto da divis�o entre (resto/razao) e 5, e vai ser util para o programa saber quantas unidades menores v�o ser necess�rias na itera��o.
	"mediano" � 5 * razao e representa o n�mero m�dio da faixa (5, 50, 500), com o qual o resto ser� comparado.
	"milhares" informa se o n�mero entrou nos milhares acima de 3999 (nesse caso os n�meros romanos mudam de l�gica).*/
	int i = 0, j, divisor = 1, controle = 0, resto, razao, resto2, mediano, milhares = 0;
	
	while (divisor <= n) {
		divisor *= 10;
		resto = n % divisor;
		if (resto) {
			razao = divisor / 10;
			mediano = 5 * razao;
			resto2 = resto / razao % 5;
			
			/*O quarto elemento do vetor menor armazena M, por�m, na l�gica dos n�meros romanos, 
			se o n�mero for maior que 3999 o M � trocado por I.*/
			if (i == 3 && resto >= 4000) {
				menor[i] = 'I';
			}
			
			/*Adi��o de underscore em n�meros de 4000 para cima.
			A vari�vel milhares garante que seja apenas um (outro ser� adicionado s� no fim)*/
			if (resto >= 4000 && !milhares) {
				strinvert[controle] = '_';
				controle++;
				milhares = 1;
			}
			
			/*No caso em que o resto2 n�o d� 4, o programa ir� adiocionar por itera��o a quantidade necess�ria de unidades menores.*/
			if (resto2 != 4) {
				for (j = 0; j < resto2; j++) {
					strinvert[controle] = menor[i];
					controle++;
				}
				/*Se o resto for maior ou igual ao n�mero m�dio, a unidade maior deve ser adicionada.*/
				if (resto >= mediano) {
					strinvert[controle] = maior[i];
					controle++;
				}
			}
			else {
				/*Se o resto2 for 4, significa que o n�mero na faixa atual tem a l�gica romana de subtra��o da unidade maior
				pela unidade menor que vem logo antes (IV = 4, IX = 9, XL = 40, XC = 90 etc).
				Se o resto for menor que o n�mero m�dio, o que ser� subtra�do � a unidade maior da faixa atual. � o caso do IV (4), por exemplo.
				Mas se ele for maior, o que ser� subtra�do � a unidade menor da faixa seguinte (i + 1). Exemplo: XC (90).*/
				if (resto < mediano) {
					strinvert[controle] = maior[i];
				}
				else {
					strinvert[controle] = menor[i+1];
				}
				controle++;
				/*Depois � necess�rio adicionar a unidade menor da faixa atual 
				(lembrando que a string est� invertida, ent�o ela vir� antes no fim).*/
				strinvert[controle] = menor[i];
				controle++;	
			}
		}
		i++;
		n -= resto;
	}
	
	/*Se o n�mero ultrapassou a quantidade de 3999, milhares foi acionado e � necess�rio adicionar um underscore final.*/
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


