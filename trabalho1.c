#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/***************************************************************************
*** ***
*** LABORAT´ORIO 1 ***
*** Grupo n.: ***
*** Nome completo dos alunos que comp~oe o grupo ***
*** ***
***************************************************************************/

int main(){
	
  long int semente; /*semente utilizada no enunciado do professor.*/
  double xp; /*valor da coordenada x do ponto*/
  double yp; /*valor da coordenada y do ponto*/
  double mpq; /*modulo do ponto ao quadrado, ou seja, sua distância da origem*/
  double erro; /*valor da tolerância do erro para o fim do cáculo utilizando o método de Newton*/
  double e_obtido; /*erro obtido durante o método de Newton*/
  double pi; /*valor calculado de pi*/
  double p; /*probabilidade de um ponto estar dentro do semi-círculo*/
  double soma_pi; /*soma dos valores obtidos de pi*/
  double somaq_pi; /*soma do quadrado dos valores de pi*/
  double media_pi; /*média obtida dos valores de pi*/
  double var_pi; /*variância dos valores obtidos de pi*/
  double dp_pi; /*desvio padrão dos valores obtidos de pi*/
  double xa; /*valor inicial do método de Newton (xk)*/
  double xb; /*valor seguinte a xa do método de Newton (xk+1)*/
  int n_rep; /*número de repetições do cálculode pi desejados*/
  int n_pontos; /*número total de pontos*/
  int n_pc; /*número de pontos dentro da área do semi-círculo*/
  int i; /*contador auxiliar do laço que calcula pi (laço mais interno)*/
  int j; /*contador auxiliar do laço que calcula a média, variância e desvio padrão (laço mais externo)*/
  
	/*Valores iniciais e fixos de algumas variáveis*/
	erro = 0.00001;
	j = 0;
	media_pi = 0;
	soma_pi = 0;
	somaq_pi = 0;
	var_pi = 0;
	dp_pi = 0;
  
	printf("Entre com o numero de repeticoes desejadas: ");
	scanf("%d", &n_rep);
	
	printf("Entre com o numero de pontos aleatorios que voce deseja gerar: ");
	scanf("%d", &n_pontos);
	
	/*Gera uma semente/seed aleatoria baseada o relogio do seu computador.
	Note que não é necessário fazer outra chamada de srand() para gerar um numero aleatorio novo e diferente do anterior.*/
	srand( time(&semente) );
	
	while(j < n_rep){
	  
		/*A cada nova interação do laço mais externo, precisamos zerar esses dois valores para calcularmos um valor novo de pi no laço mais interno.*/
		n_pc = 0;
		i = 0;		
		
		/*Com base na semente/seed gerada anteriormente, faremos duas chamadas de rand() para gerar o valor X e Y dos pontos.
		O laço irá se repetir até que sejam gerados todos os pontos desejados.
		Cada vez que um ponto é gerado, o laço também irá verificar se ele se encontra dentro do semi-círculo.
		Note também que não precisamos guardar os pontos, apenas precisamos saber se ele se encontra dentro ou fora do semi-círculo*/
		while(i < n_pontos){
			xp = (double)rand()/RAND_MAX;
			yp = (double)rand()/RAND_MAX;
			
			/*Para sabermos se um ponto se encontra dentro da semi-círculo, utilizaremos uma comparação de seu módulo com o raio.
			Não podemos utilizar nem funções nem a biblioteca math.h então faremos uma comparação do quadrado do módulo do ponto com o quadrado do raio, assim eliminamos a necessidade de extraír a raíz quadrada.
			Essa comparação é válida dado que todos os números são positivos. Verifique isso formalmente caso tenha alguma dúvida.
			Como a semi-círculo possúi raio 1, o quadrado de seu raio também vale 1, então a comparação será do quadrado do módulo do ponto com 1*/
			mpq = xp * xp + yp * yp;
			if(mpq <= 1)
				n_pc++;
					
			i++;
		}
		
		/*Aqui, calculamos um valor aproximado de pi com a fórmula disponibilziada pelo professor*/
		p = (double)n_pc / n_pontos;
		pi = 4 * p;
		
		/*Aqui, calculamos a primeira parte da média de pi, ainda não dividimos pelo número total de operações realizadas.*/
		soma_pi = soma_pi + pi;
		
		/*Usaremos a soma do quadrado dos valores de pi futuramente no cálculo da variância.*/
		somaq_pi = somaq_pi + pi * pi;
		
		j++;
	}
	
	/*Agora calculamos, de fato, a média de pi.*/
	media_pi = soma_pi / n_rep;
	
	/*Para o cálculo da variância, expandimos o somatório e fazemos os devidos agrupamentos e conseguimos reduzir a fórmula de forma que eliminamos os termos individuais e ficamos somente com a soma dos valores de pi
	e a soma dos quadrados dos valores pi, assim, possibilitando o cálculo da variância sem que haja a necessidade de armazenamento de cada valor de pi obtidos anteriormente.
	obs.:Para não ficar uma linha com uma expressão muito grande e evitar confusões, o cálculo da variância de pi foi dividido em duas linhas.*/
	var_pi = media_pi * (n_rep * media_pi - 2 * soma_pi) + somaq_pi; 
	var_pi = var_pi / (n_rep - 1);
	
	
	/*Calcularemos o desvio padrão de pi, que é a raíz quadrada da variância de pi, utilizando o método de Newton.
	Como e enunciado diz, devemos adotar como chute inicial, o próprio radicando.*/
	xa = var_pi;
	
	/*Utilizaremos a fórmula disponibilizada no enunciado para o cálculo de raíz quadrada.
	O comando do{}while(); será utilizado para isso pois precisamos entrar na primeira interação do laço independentemente do primeiro valor de xk+1 e a verificação de parada do laço é feita somente no final das interações.*/
	do{
		xb = 0.5 * (xa + var_pi / xa);
		e_obtido = (xb - xa) / xa;
		/*Como estamos trabalhando em módulo, caso o valor do erro seja menor que zero, multiplicaremos ele por -1.*/
		if(e_obtido < 0)
			e_obtido = -1 * e_obtido;
		/*Essa troca é feita aqui pois não precisaremos mais do valor antigo de xa para a próxima interação e mesmo que não haja uma próxima interação, essa variável não será mais utilizada.*/
		xa = xb;
	} while( e_obtido >= erro );
	dp_pi = xb;
		
	printf("Numero total de pontos aleatorios = %d\n", n_pontos);
	printf("Numero de repeticoes = %d\n\n", n_rep);
	printf("pi = %f\n", media_pi);
	printf("variancia = %f\n", var_pi);
	printf("desvio padrao = %f\n", dp_pi);
	
	system("PAUSE");
	return 0;	
	
}