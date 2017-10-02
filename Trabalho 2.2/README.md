# Sistemas de Tempo Real
# Trabalho 2.2 


#Descrição do programa:

 

- Gere 03 processos: Pai, Filho1, Filho2

 

- Processo Pai:

 

     - Este processo terá prioridade 0.

 

     - Lerá a cada 500ms 02 portas analógicas (AD1, AD2) da Beagle.

 

     - Se o valor de tensão da porta AD1 for maior que 1V, então setar a prioridade do processo Filho1 para 05. Caso contrário, setar a prioridade do processo Filho1 para 19.

 

     - Se o valor de tensão da porta AD2 for maior que 1V, então setar a prioridade do processo Filho2 para 05. Caso contrário, setar a prioridade do processo Filho2 para 19.

 

- Processos Filhos (Filho1 e Filho2) executarão num loop infinito uma função carga (configurar esta função para que ela execute em torno de 1s).

 

- Nas iterações pares no seu loop infinito, o processo Filho (Filho 1 ou Filho2) deverá acender um Led (Led1, para Filho1 e Led2, para Filho2).

 

- Nas iterações ímpares no seu loop infinito, o processo Filho (Filho 1 ou Filho2) deverá apagar um Led (Led1, para Filho1 e Led2, para Filho2).

 

Material necessário:

 

- 02 leds

 

- 02 potenciômetros

 

- 02 resistores

 

- kit beagle board

 

ATENÇÃO: Para não queimar a placa, utilizar o pinos exclusivos do ADC (pino VDD_ADC -1.8V, pino GND_ADC - terra).

 

Gerar vídeo demonstrando os resultados do trabalho. Alterar valores de prioridade dos processos e verificar os seus efeitos.

# Imagem do circuito :

