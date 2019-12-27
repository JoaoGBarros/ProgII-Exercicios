/***************************************************************
Trabalho Computacional – Programação II – 2019/2 – Ciência/Engenharia da
Computação
Grupo: Enzo Pereira Tristão e João Gabriel de Barros Rocha
***************************************************************/




#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//Definicao de valores para facilitar a leitura
#define ataque 1
#define movimento 2
#define direita 3
#define esquerda 4
#define frente 5
#define tras 6
#define erro 7 
#define agua 8
#define fogo 9
#define empate 10


struct mago{
    int vida; //Quantidade de Vida do jogador
    int PosicaoLinha; //Posicao linha atual do jogador  
    int PosicaoColuna; //Posicao coluna atual do jogador
    int PosicaoLinhaP; //Posicao linha passada do jogador
    int PosicaoColunaP; //Posicao coluna passada do jogador
    char tipo; //Tipo do mago (fogo ou agua)
    char posicao; //caracter que o mago se encontra 
    char especial; //Ataque do mago
    char posicaoP; //caracter que o mago estava
    char artefato; // Artefato do mago
};

struct tabuleiro{
    int linhas; //Quantida de linhas da matriz
    int colunas; // Quantida de colunas da matriz
    char tabuleiro[100][100]; //Matriz
    int Dano; //Retorna 1 se o mago tomou dano no ataque, caso nao, retorna 0
    int encurralamentoF; //Caso o mago F seja encurralado retorna 1
    int encurralamentoAG; //Caso o mago A seja encurralado por seu proprio ataque no Gelo retorna 1
    int encurralamentoA; //Caso o mago A seja encurralado retorna 1
    char PF; //Altera a posicao do mago de fogo caso ele seja encurralado
    char PA; //Altera a posicao do mago de agua caso ele seja encurralado
};


typedef struct tabuleiro Tabuleiro;
typedef struct mago Mago;



void ImprimeTabuleiro(Tabuleiro mapa){   //Imprime o tabuleiro
    for(int i = 0; i < mapa.linhas; i++){
        for(int j = 0; j < mapa.colunas; j++){
            printf("%c", mapa.tabuleiro[i][j]);
        }
        printf("\n");
    }
}


void ImprimeRodape(Mago MagoAgua, Mago MagoFogo, int turnos, Tabuleiro mapa, int controlador){   //Imprime as informacoes do Rodape
    printf("Jogador da vez: ");
    if(turnos%2 == 0){
        printf("%c\n", MagoFogo.tipo);
    }else{
        printf("%c\n", MagoAgua.tipo);
    }
    printf("%c: %c\n", MagoFogo.tipo, MagoFogo.posicao);
    printf("%c: %c\n", MagoAgua.tipo, MagoAgua.posicao);
    printf("Vida %c: %d\n", MagoFogo.tipo, MagoFogo.vida);
    printf("Vida %c: %d\n\n", MagoAgua.tipo, MagoAgua.vida);
    if(controlador == 0){
        printf("Comando: \n\n\n");
    }

}



int Comando(char comando[]){ //Verifica se o comando eh de movimento ou de ataque
    if(comando[0] == 'A' || comando[0] == 'a'){
        return ataque;
    }else if(comando[0] == 'e'|| comando[0] == 'd' || comando[0] == 'f' || comando[0] == 't'){
        return movimento;
    }else if(comando[0] == 'E'|| comando[0] == 'D' || comando[0] == 'F' || comando[0] == 'T'){
        return movimento;
    }else{
        return erro;
    } 
}

int ChecaDirecao(char comando[]){ //Ve para qual direcao o jogador vai se mover
    if(comando[0] == 'E'|| comando[0] == 'e'){
        return esquerda;
    }else if(comando[0] == 'D' || comando[0] == 'd'){
        return direita;
    }else if(comando[0] == 'F' || comando[0] == 'f'){
        return frente;
    }else if(comando[0] == 'T' || comando[0] == 't'){
        return tras;
    }else{
        return erro;
    }
}


int JogadaValida(int casas){ //Verifica se a jogada eh valida
    if(casas < 1){
        return 0;
    }else{
        return 1;
    }
}


Mago CaminhoValido(int casas, int direcao, Tabuleiro mapa, Mago mago1, Mago mago2){ //Movimenta o mago no tabuleiro

    /*Verifica a proxima casa de acordo com a direcao e caso seja possivel andar nessa casa ele se movimenta, caso nao ele para 1 antes.
    Caso passe por uma casa ja marcada pelo poder do mago inimigo, se move, porem perde 10 de vida*/

    int i, j;
    mago1.PosicaoLinhaP = mago1.PosicaoLinha; //Armazaena a posicao do mago antes do movimento que ira acontecer
    mago1.PosicaoColunaP = mago1.PosicaoColuna;

    if(direcao == esquerda){
        for(j = mago1.PosicaoColuna, i = mago1.PosicaoLinha; casas > 0 && mago1.PosicaoColuna > 0; j--, casas--){
            if(mapa.tabuleiro[i][j - 1] != 'P' && mapa.tabuleiro[i][j -1] != 'X' && mapa.tabuleiro[i][j - 1] != 'G' && mapa.tabuleiro[i][j - 1] != mago2.tipo){
                if(mapa.tabuleiro[i][j - 1] == mago2.especial){
                    mago1.PosicaoColuna = mago1.PosicaoColuna - 1;
                    mago1.vida = mago1.vida - 10;

                    
                }else if(mapa.tabuleiro[i][j - 1] == mago2.artefato){
                    break;

                   
                }else{
                    mago1.PosicaoColuna = mago1.PosicaoColuna - 1;
                }
            }else{
                break;
            }
                
        }
        
           
    }else if(direcao == direita){
        for(j = mago1.PosicaoColuna, i = mago1.PosicaoLinha; casas > 0 && mago1.PosicaoColuna < mapa.colunas -1; j++, casas--){
            if(mapa.tabuleiro[i][j + 1] != 'P' && mapa.tabuleiro[i][j + 1] != 'X' && mapa.tabuleiro[i][j + 1] != 'G'&& mapa.tabuleiro[i][j + 1] != mago2.tipo){
                if(mapa.tabuleiro[i][j + 1] == mago2.especial){
                    mago1.PosicaoColuna = mago1.PosicaoColuna + 1;
                    mago1.vida = mago1.vida - 10;

                    
                }else if(mapa.tabuleiro[i][j + 1] == mago2.artefato){
                    break;

                   
                }else{
                    mago1.PosicaoColuna = mago1.PosicaoColuna + 1;
                }
            }else{
                break;
            }
                
        }

    }else if(direcao == frente){
        for(j = mago1.PosicaoColuna, i = mago1.PosicaoLinha; casas > 0 && mago1.PosicaoLinha > 0; i--, casas--){
            if(mapa.tabuleiro[i - 1][j] != 'P' && mapa.tabuleiro[i - 1][j] != 'X' && mapa.tabuleiro[i - 1][j] != 'G'&& mapa.tabuleiro[i - 1][j] != mago2.tipo){
                if(mapa.tabuleiro[i - 1][j] == mago2.especial){
                    mago1.PosicaoLinha= mago1.PosicaoLinha - 1;
                    mago1.vida = mago1.vida - 10;

                    
                }else if(mapa.tabuleiro[i - 1][j] == mago2.artefato){
                    break;

                   
                }else{
                    mago1.PosicaoLinha = mago1.PosicaoLinha - 1;
                }
            }else{
                break;
            }
                
        }
            
    }else if(direcao == tras){
        for(j = mago1.PosicaoColuna, i = mago1.PosicaoLinha; casas > 0 && mago1.PosicaoLinha < mapa.linhas - 1; i++, casas--){
            if(mapa.tabuleiro[i + 1][j] != 'P' && mapa.tabuleiro[i + 1][j] != 'X' && mapa.tabuleiro[i + 1][j] != 'G'&& mapa.tabuleiro[i + 1][j] != mago2.tipo){
                if(mapa.tabuleiro[i + 1][j] == mago2.especial){
                    mago1.PosicaoLinha= mago1.PosicaoLinha + 1;
                    mago1.vida = mago1.vida - 10;

                    
                }else if(mapa.tabuleiro[i + 1][j] == mago2.artefato){
                    break;

                   
                }else{
                    mago1.PosicaoLinha = mago1.PosicaoLinha + 1;
                }
            }else{
                break;
            }            
        }
     }

     return mago1;
}


Tabuleiro AtualizaTabuleiroMovimento(Mago mago1, Tabuleiro mapa, Tabuleiro reserva){ //Atualiza o Mago no tabuleiro
    mapa.tabuleiro[mago1.PosicaoLinhaP][mago1.PosicaoColunaP] = reserva.tabuleiro[mago1.PosicaoLinhaP][mago1.PosicaoColunaP];
    //A posicao que o mago estava recebe o valor de um mapa reserva que nao possui os magos
    mapa.tabuleiro[mago1.PosicaoLinha][mago1.PosicaoColuna] = mago1.tipo; //A posicao atual do mago no tabuleiro recebe o tipo do mago (a ou f)
    
    return mapa;
}


void Vencedor(int controlador){
    if(controlador == fogo){
        printf("O mago de fogo venceu!\n");
    }

    if(controlador == agua){
        printf("O mago da agua venceu!\n");
    }

    if(controlador == empate){
        printf("Empate!\n");
    }
}

int AcabouOJogo(Tabuleiro mapa, Mago MagoFogo, Mago MagoAgua){ //Verifica se o jogo acabou
    int cont = 0;
    
    if(MagoFogo.vida <= 0){
        cont = agua;
    }

    if(MagoAgua.vida <= 0){
        cont = fogo;
    }

    if(MagoAgua.posicao == MagoAgua.artefato){
        cont = agua;
    }

    if(MagoFogo.posicao == MagoFogo.artefato){
        cont = fogo;
    }

    if(mapa.encurralamentoA == 1 && mapa.encurralamentoF == 1){
        cont = empate;
    }else if(mapa.encurralamentoF == 1){
        cont = agua;
    }else if(mapa.encurralamentoA){
        return fogo;
    }else if(MagoAgua.posicao == 'G'){
        return fogo;
    }

    if(MagoAgua.posicao == 'F'){
        cont = fogo;
    }else if(MagoFogo.posicao == 'A'){
        cont = agua;
    }

    return cont;
   
}


Mago AtualizaMagoMovimento(Mago mago1, Tabuleiro mapa, Tabuleiro reserva, Mago mago2){ //Atualiza o Mago depois de se mover
    Mago mago;


    mago = mago1;

    if(mapa.PA != '0' && mago.tipo == 'a'){ //Caso o mago seja encurralado, a posicao dele eh atualizada
        mago.posicao = mapa.PA;
    }else if(mapa.PF != '0' && mago.tipo == 'f'){
        mago.posicao = mapa.PF;
    }else{
        mago.posicao = reserva.tabuleiro[mago1.PosicaoLinha][mago1.PosicaoColuna];
    }

    if(mago.tipo == 'a' && mago.posicao == 'A' && mapa.encurralamentoAG == 1){ //Caso mago de agua seja encurralado no gelo, a posicao dele eh atualizada
        mago.posicao = 'G';
    }   
    

    return mago;
}


Mago AtualizaMagoAtaque(Tabuleiro mapa, Mago mago2){ //Atualiza o Mago apos atacar
    Mago mago;
    
    mago = mago2;
    if(mapa.Dano == 1){ //Se o ataque tiver acertado o mago 2, ele perde 10 de vida
        mago.vida = mago.vida - 10;
    }else if(mapa.PF != '0' && mago.tipo == 'f'){
        mago.posicao = mapa.PF;
    }if(mapa.PA != '0'  && mago.tipo == 'a'){
        mago.posicao = mapa.PA;
    }

    if(mago.tipo == 'a' && mago.posicao == 'A' && mapa.encurralamentoAG == 1){
        mago.posicao = 'G';
    }

    return mago;
}


Tabuleiro QueimaGrama(int i, int j, Mago mago1, Tabuleiro mapa, Mago mago2){ // Queimar as plantas 'P'. 'P' -> 'F'
    int x;

    for(i, x = -1, j; x < 2 ;x++){
        if(mapa.tabuleiro[i-1][j + x] == 'P'){
            mapa.tabuleiro[i-1][j+x] = 'F';
        }
    }
            
    for(i, x = -1, j; x < 2; x++){
        if(mapa.tabuleiro[i][j + x] == 'P'){
            mapa.tabuleiro[i][j+x] = 'F';    
        }
    }

    for(i, x = -1, j; x < 2; x++){
        if(mapa.tabuleiro[i+1][j+x] == 'P'){
            mapa.tabuleiro[i+1][j+x] = 'F';
            
        }
    }

    return mapa;
}


Tabuleiro DerreteGelo(int i, int j, Mago mago1, Tabuleiro mapa, Mago mago2){ //Derreter o Gelo 'G'. 'G' -> 'A'
    int x;

    for(i, x = -1, j; x < 2 ;x++){
        if(mapa.tabuleiro[i-1][j + x] == 'G'){
            mapa.tabuleiro[i-1][j+x] = 'A';
        } 
    }
    
    for(i, x = -1, j; x < 2 ;x++){
        if(mapa.tabuleiro[i-1][j + x] == '.'){
            mapa.tabuleiro[i-1][j+x] = 'A';
        } 
    }
            
    for(i, x = -1, j; x < 2; x++){
        if(mapa.tabuleiro[i][j + x] == 'G'){
            mapa.tabuleiro[i][j+x] = 'A';
        }
    }
    
    for(i, x = -1, j; x < 2; x++){
        if(mapa.tabuleiro[i][j+x] == '.'){
            mapa.tabuleiro[i][j+x] = 'A';
        }
    }

    for(i, x = -1, j; x < 2; x++){
        if(mapa.tabuleiro[i + 1][j + x] == 'G'){
            mapa.tabuleiro[i+1][j+x] = 'A';
        }
    }
    
    for(i, x = -1, j; x < 2; x++){
        if(mapa.tabuleiro[i + 1][j + x] == '.'){
            mapa.tabuleiro[i+1][j+x] = 'A';
        }
    }

    return mapa;
}

Tabuleiro EvaporaAgua(int i, int j, Mago mago1, Tabuleiro mapa, Mago mago2, int d){ //Evaporar a agua 'A'. 'A' -> '.'
    int x;

    if(d == 1){
        for(i = i;mapa.tabuleiro[i][j] == 'A'; j--){
            if(mapa.tabuleiro[i][j] == 'A'){
                mapa.tabuleiro[i][j] = '.';
            }
        }
    }

    if(d == 2){
        for(i = i;mapa.tabuleiro[i][j] == 'A'; j++){
            if(mapa.tabuleiro[i][j] == 'A'){
                mapa.tabuleiro[i][j] = '.';
            }
        }
    }

    if(d == 3){
        for(i = i;mapa.tabuleiro[i][j] == 'A'; i--){
            if(mapa.tabuleiro[i][j] == 'A'){
                mapa.tabuleiro[i][j] = '.';
            }
        }
    }

    if(d == 4){
        for(i = i; mapa.tabuleiro[i][j] == 'A'; i++){
            if(mapa.tabuleiro[i][j] == 'A'){
                mapa.tabuleiro[i][j] = '.';
            }
        }
    }
    
    return mapa;
}

Tabuleiro Renascimento(int i, int j, Mago mago1, Tabuleiro mapa, Mago mago2){ //Criar plantas novas 'P', '.' -> 'P'
    int x;

    for(i, x = -1, j; x < 2 ;x++){
        if(mapa.tabuleiro[i-1][j + x] == '.'){
            mapa.tabuleiro[i-1][j+x] = 'P';
        }if(mapa.tabuleiro[i-1][j+x] == mago1.tipo){
            mapa.encurralamentoA = 1;
            mapa.PA = 'P';
        }else if(mapa.tabuleiro[i-1][j+x] == mago2.tipo){
            mapa.encurralamentoF = 1;
            mapa.PF = 'P';
        }
    } 
    
            
    for(i, x = -1, j; x < 2; x++){
        if(mapa.tabuleiro[i][j + x] == '.'){
            mapa.tabuleiro[i][j+x] = 'P';
        }if(mapa.tabuleiro[i][j+x] == mago1.tipo){
            mapa.encurralamentoA = 1;
            mapa.PA = 'P';
        }else if(mapa.tabuleiro[i][j+x] == mago2.tipo){
            mapa.encurralamentoF = 1;
            mapa.PF = 'P';
        }
    }
    

    for(i, x = -1, j; x < 2; x++){
        if(mapa.tabuleiro[i+1][j+x] == '.'){
            mapa.tabuleiro[i+1][j+x] = 'P';
        }if(mapa.tabuleiro[i+1][j+x] == mago1.tipo){
            mapa.encurralamentoA = 1;
            mapa.PA = 'P';
        }else if(mapa.tabuleiro[i+1][j+x] == mago2.tipo){
            mapa.encurralamentoF = 1;
            mapa.PF = 'P';
        }
    }

    return mapa;
}

Tabuleiro Bombeiro(int i, int j, Mago mago1, Tabuleiro mapa, Mago mago2, int d){ //Apagar o fogo 'F' -> '.'
    int x;

   if(d == 1){
        for(i = i;mapa.tabuleiro[i][j] == 'F'; j--){
            if(mapa.tabuleiro[i][j] == 'F'){
                mapa.tabuleiro[i][j] = '.';
            }
        }
    }

    if(d == 2){
        for(i = i;mapa.tabuleiro[i][j] == 'F'; j++){
            if(mapa.tabuleiro[i][j] == 'F'){
                mapa.tabuleiro[i][j] = '.';
            }
        }
    }

    if(d == 3){
        for(i = i;mapa.tabuleiro[i][j] == 'F'; i--){
            if(mapa.tabuleiro[i][j] == 'F'){
                mapa.tabuleiro[i][j] = '.';
            }
        }
    }

    if(d == 4){
        for(i = i; mapa.tabuleiro[i][j] == 'F'; i++){
            if(mapa.tabuleiro[i][j] == 'F'){
                mapa.tabuleiro[i][j] = '.';
            }
        }
    }
    
    return mapa;
}

Tabuleiro FicaFrio(int i, int j, Mago mago1, Tabuleiro mapa, Mago mago2){ //Transformar agua em gelo 'A' -> 'G'
    int x;

     for(i, x = -1, j; x < 2 ;x++){
        if(mapa.tabuleiro[i-1][j + x] == 'A'){
            mapa.tabuleiro[i-1][j+x] = 'G';
        }if(mapa.tabuleiro[i-1][j+x] == mago1.tipo){
                mapa.encurralamentoAG = 1;
            }
    }
    
            
    for(i, x = -1, j; x < 2; x++){
        if(mapa.tabuleiro[i][j + x] == 'A'){
            mapa.tabuleiro[i][j+x] = 'G';
        }if(mapa.tabuleiro[i][j+x] == mago1.tipo){
                mapa.encurralamentoAG = 1;
        }
    }

    for(i, x = -1, j; x < 2; x++){
        if(mapa.tabuleiro[i+1][j+x] == 'A'){
            mapa.tabuleiro[i+1][j+x] = 'G';
        }if(mapa.tabuleiro[i+1][j+x] == mago1.tipo){
                mapa.encurralamentoAG = 1;
        }
    }

    return mapa;
}



Tabuleiro mapaEsquerda(Mago mago1, Mago mago2, Tabuleiro mapa){ //Analisa o mapa para a esquerda do mago
    int i, j, d;
    

    d = 1;

    for(i = mago1.PosicaoLinha, j = mago1.PosicaoColuna; j >=0; j--){
        if(mapa.tabuleiro[i][j - 1] == 'X'){
            break;
        }

        if(mago1.tipo == 'f'){
            if(mapa.tabuleiro[i][j] == 'A'){
                mapa = EvaporaAgua(i, j, mago1, mapa, mago2, d);
                     
            }else if(mapa.tabuleiro[i][j] == 'G'){
                mapa = DerreteGelo(i, j, mago1, mapa, mago2);
                break;
                
            }else if(mapa.tabuleiro[i][j] == 'P'){
                mapa = QueimaGrama(i, j, mago1, mapa, mago2);
                break;
                
            }
        }

        if(mago1.tipo == 'a'){
            if(mapa.tabuleiro[i][j] == 'P'){
                mapa = Renascimento(i, j, mago1, mapa, mago2);
                break;
                
            }else if(mapa.tabuleiro[i][j] == 'F'){
                mapa = Bombeiro(i, j, mago1, mapa, mago2, d);
                
            }else if(mapa.tabuleiro[i][j] == 'A'){
                mapa = FicaFrio(i, j, mago1, mapa, mago2);
                break;
                
            }
        }

        if(mapa.tabuleiro[i][j+1]== mago2.tipo){
            mapa.Dano = 1;
        }
    }
    return mapa;
}


Tabuleiro mapaDireita(Mago mago1, Mago mago2, Tabuleiro mapa){ //Analisa o mapa pela direita do mago
    int i, j;
    int d = 2;

    for(i = mago1.PosicaoLinha, j = mago1.PosicaoColuna; j < mapa.colunas; j++){
        if(mapa.tabuleiro[i][j + 1] == 'X'){
            break;
        }

        if(mago1.tipo == 'f'){
            if(mapa.tabuleiro[i][j] == 'A'){
                mapa = EvaporaAgua(i, j, mago1, mapa, mago2, d);
                      
            }else if(mapa.tabuleiro[i][j] == 'G'){
                mapa = DerreteGelo(i, j, mago1, mapa, mago2);
                break;
                
            }else if(mapa.tabuleiro[i][j] == 'P'){
                
                mapa = QueimaGrama(i, j, mago1, mapa, mago2);
                break;
            }
        }

        if(mago1.tipo == 'a'){
            if(mapa.tabuleiro[i][j] == 'P'){
                mapa = Renascimento(i, j, mago1, mapa, mago2);
                break;
                
            }else if(mapa.tabuleiro[i][j] == 'F'){
                mapa = Bombeiro(i, j, mago1, mapa, mago2, d);
                
            }else if(mapa.tabuleiro[i][j] == 'A'){
                mapa = FicaFrio(i, j, mago1, mapa, mago2);
                break;
                
            }
        }

        if(mapa.tabuleiro[i][j+1]== mago2.tipo){
            mapa.Dano = 1;
        }
    }
    return mapa;

}

Tabuleiro mapaCima(Mago mago1, Mago mago2, Tabuleiro mapa){ //Analisa o mapa pela frente do mago
    int i, j;
    int d = 3;
    

    for(i = mago1.PosicaoLinha, j = mago1.PosicaoColuna;i >=0; i--){
        if(mapa.tabuleiro[i-1][j] == 'X'){
            break;
        }

        if(mago1.tipo == 'f'){
            if(mapa.tabuleiro[i][j] == 'A'){
                mapa = EvaporaAgua(i, j, mago1, mapa, mago2, d);
                      
            }else if(mapa.tabuleiro[i][j] == 'G'){
                mapa = DerreteGelo(i, j, mago1, mapa, mago2);
                break;
                
            }else if(mapa.tabuleiro[i][j] == 'P'){
                mapa = QueimaGrama(i, j, mago1, mapa, mago2);
                break;
                
            }
        }

        if(mago1.tipo == 'a'){
            if(mapa.tabuleiro[i][j] == 'P'){
                mapa = Renascimento(i, j, mago1, mapa, mago2);
                break;
                
            }else if(mapa.tabuleiro[i][j] == 'F'){
                mapa = Bombeiro(i, j, mago1, mapa, mago2, d);
                
            }else if(mapa.tabuleiro[i][j] == 'A'){
                mapa = FicaFrio(i, j, mago1, mapa, mago2);
                break;
                
            }
        }

        if(mapa.tabuleiro[i][j+1]== mago2.tipo){
            mapa.Dano = 1;
        }
    }
    return mapa;

}

Tabuleiro mapaBaixo(Mago mago1, Mago mago2, Tabuleiro mapa){ //Analisa o mapa por tras do mago
    int i, j;
    int d = 4;
    

    for(i = mago1.PosicaoLinha, j = mago1.PosicaoColuna; i < mapa.linhas; i++){
        if(mapa.tabuleiro[i+1][j] == 'X'){
            break;
        }

        if(mago1.tipo == 'f'){
            if(mapa.tabuleiro[i][j] == 'A'){
                mapa = EvaporaAgua(i, j, mago1, mapa, mago2, d);
                
            }else if(mapa.tabuleiro[i][j] == 'G'){
                mapa = DerreteGelo(i, j, mago1, mapa, mago2);
                break;
                
            }else if (mapa.tabuleiro[i][j] == 'P'){
                mapa = QueimaGrama(i, j, mago1, mapa, mago2);
                break;
            }
        }

        if(mago1.tipo == 'a'){
            if(mapa.tabuleiro[i][j] == 'P'){
                mapa = Renascimento(i, j, mago1, mapa, mago2);
                break;
                
            }else if(mapa.tabuleiro[i][j] == 'F'){
                mapa = Bombeiro(i, j, mago1, mapa, mago2, d);
                
            }else if(mapa.tabuleiro[i][j] == 'A'){
                mapa = FicaFrio(i, j, mago1, mapa, mago2);
                break;
                
            }
        }

        if(mapa.tabuleiro[i][j]== mago2.tipo){
            mapa.Dano = 1;
        }
    }
    return mapa;

}

Tabuleiro AtualizaTabuleiroAtaque(Tabuleiro mapa, Mago mago1, Mago mago2){ //Analisa cada direcao de ataque e atualiza o mapa
    

    mapa = mapaEsquerda(mago1, mago2, mapa);
    mapa = mapaDireita(mago1, mago2, mapa);
    mapa = mapaCima(mago1, mago2, mapa);
    mapa = mapaBaixo(mago1, mago2, mapa);

    return mapa;
}



Tabuleiro PreencheReserva(Tabuleiro mapa){ //Preenche o tabuleiro reserva

    Tabuleiro res;

    for(int i = 0; i < mapa.linhas; i++){
        for(int j = 0; j < mapa.colunas; j++){
            if(mapa.tabuleiro[i][j] == 'f' || mapa.tabuleiro[i][j] == 'a'){
                res.tabuleiro[i][j] = '.';
            }else{
                res.tabuleiro[i][j] = mapa.tabuleiro[i][j];
            }
        }
    }

    return res;
}


Tabuleiro AtualizaReserva(Tabuleiro mapa, Mago mago1, Tabuleiro reserva){ //Atualiza o mapa reserva
    Tabuleiro aux;

    for(int i = 0; i < mapa.linhas; i++){
        for(int j = 0; j < mapa.colunas; j++){
            if(mapa.tabuleiro[i][j] != 'f' && mapa.tabuleiro[i][j] != 'a'){
                reserva.tabuleiro[i][j] = mapa.tabuleiro[i][j];
            }
        }
    }

    return reserva;
}



void Jogo(Tabuleiro mapa, Mago MagoAgua, Mago MagoFogo){ //Basicamente onde vai rodar o jogo
    int casas, direcao, controlador = 0, comand, turnos = 0;
    char comando[9];
    Mago mago1, mago2;
    Tabuleiro reserva;



    reserva = PreencheReserva(mapa);



    while(1){
        controlador = AcabouOJogo(mapa, MagoFogo, MagoAgua);
        ImprimeTabuleiro(mapa);
        printf("\n");
        ImprimeRodape(MagoAgua, MagoFogo, turnos, mapa, controlador);

        
        if(controlador == fogo || controlador == agua || controlador == empate){
            Vencedor(controlador);
            break;
        }else{
            mapa.Dano = 0;
            mapa.encurralamentoA = 0;
            mapa.encurralamentoF = 0;
            mapa.PA = '0';
            mapa.PF = '0';   
        }

        if(turnos%2 == 0){
            mago1 = MagoFogo;
            mago2 = MagoAgua;
        }else{
            mago1 = MagoAgua;
            mago2 = MagoFogo;
        }


        scanf("%s", comando);
        comand = Comando(comando);
        if(comand != ataque && comand != movimento){
            while(1){
                printf("Jogada Invalida, tente novamente:\n");
                scanf("%s", comando);
                comand = Comando(comando);
                if(comand == ataque || comand == movimento){
                    break;
                }
            }
        }

        if(comand == movimento){
            scanf("%d", &casas);
            direcao = ChecaDirecao(comando);
            if(JogadaValida(casas)){
                mago1 = CaminhoValido(casas, direcao, mapa, mago1, mago2);
                if(turnos%2 == 0){
                    MagoFogo = AtualizaMagoMovimento(mago1, mapa, reserva, mago2);
                }else{
                    MagoAgua = AtualizaMagoMovimento(mago1, mapa, reserva, mago2);
                }
                mapa = AtualizaTabuleiroMovimento(mago1, mapa, reserva);
            }else{
                while(1){
                printf("Jogada Invalida, tente novamente:\n");
                scanf("%s", comando);
                comand = Comando(comando);
                if(comand == ataque){
                    break;
                }else if(comand == movimento){
                    scanf("%d", &casas);
                    if(JogadaValida(casas)){
                        mago1 = CaminhoValido(casas, direcao, mapa, mago1, mago2);
                        if(turnos%2 == 0){
                            MagoFogo = AtualizaMagoMovimento(mago1, mapa, reserva, mago2);
                        }else{
                             MagoAgua = AtualizaMagoMovimento(mago1, mapa, reserva, mago2);
                        }
                        mapa = AtualizaTabuleiroMovimento(mago1, mapa, reserva);
                        break;
                    }else{
                        continue;
                    }
                }
            }
        }
        
    }

        if(comand == ataque){
            mapa = AtualizaTabuleiroAtaque(mapa, mago1, mago2);
            reserva = AtualizaReserva(mapa, mago1, reserva);
            if(turnos%2 == 0){
                MagoAgua = AtualizaMagoAtaque(mapa, mago2);
                MagoFogo = AtualizaMagoMovimento(mago1, mapa, reserva, mago2);
            }else{
                MagoFogo = AtualizaMagoAtaque(mapa, mago2);
                MagoAgua = AtualizaMagoMovimento(mago1, mapa, reserva, mago2);
            }
        }

        turnos++;
    }
}


    


Tabuleiro LerArquivo(FILE* arq){ //Funcao para pegar a informacao dos arquivos

   Tabuleiro tab;

    while (!feof(arq)){
        fscanf(arq,"%d", &tab.linhas);
        fscanf(arq," %d", &tab.colunas);
        
        for(int i = 0; i < tab.linhas; i++){
            for(int j = 0; j < tab.colunas; j++){
                fscanf(arq, " %c", &tab.tabuleiro[i][j]);
            }
        }
    }

    tab.encurralamentoA = 0;
    tab.encurralamentoAG = 0;
    tab.encurralamentoF = 0;

    return tab; 
}



Mago InicializaMago(Tabuleiro mapa, Mago mago){ //Inicializa as informacoes do mago

    mago.vida = 30;
    
    for(int i = 0; i < mapa.linhas; i++){
        for(int j = 0; j < mapa.colunas; j++){
            if(mapa.tabuleiro[i][j] == mago.tipo){
                mago.PosicaoLinha = i;
                mago.PosicaoColuna = j;
            }
        }
    }
    
    mago.especial = mago.tipo - 32;
    mago.posicao = '.';
    


    return mago;
}




void Inicializacao(){
    Tabuleiro mapa;
    FILE* arq;
    Mago MagoAgua, MagoFogo;
    

    MagoFogo.tipo = 'f';
    MagoAgua.tipo = 'a';
    MagoFogo.artefato = '*';
    MagoAgua.artefato ='$';

    arq = fopen("teste.txt", "r"); //Abrir o aqruivo

    if(arq == NULL){ //Caso o arquivo esteja vazio da error
        printf("Error\n");
        exit(1);
    }else{
        mapa = LerArquivo(arq);
        fclose(arq);     
        MagoAgua = InicializaMago(mapa, MagoAgua); //Cada Mago recebe a devida inicializacao
        MagoFogo = InicializaMago(mapa, MagoFogo);
        Jogo(mapa, MagoAgua, MagoFogo);
    }
}  



int main(){
    Inicializacao();
    return 0;
}