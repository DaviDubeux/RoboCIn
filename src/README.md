Os maiores problemas na execução do projeto foram definir o leitor do encoder e o tempo para cálculo da velocidade

A idéia da função readPos era comparar a posição dos canais A e B para assim ter também a medição do sentido de rotação do motor, já que minha idéia inicial apresentava problemas em altas velocidades no dia 04/05;

a função original era:
void readEncoder() {
int b = ChB;
pos = 0;
if (b>0) {
pos++;
}
else {
pos--;
}
}

entretando, a altas velocidades, a rotação do motor está tão alta que, no intervalo entre o interrupt chamar a voidEncoder e a função ler o canal b para identificar se a posição aumentou ou diminuiu, o valor do ChB já mudou, gerando vários errors
