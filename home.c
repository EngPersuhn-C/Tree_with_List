#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Código ANSI para cada cor
Fonte: GitHub - github.com*/
#define ANSI_COLOR_RED      "\x1b[31m" //Vermelho
#define ANSI_COLOR_GREEN	"\e[0;32m" //Verde
#define ANSI_COLOR_RESET   "\x1b[0m" //Cor original do compilador

int qtt_verification = 0; //Foge das boas práticas, mas não interfere a execução do programa



//--------------------------- Cabeçalho do Programa ----------------------------//

int cabecalho(){
    char nome[30];
    int entrada = 20211;
    int senha;

    printf("--------- BEM VINDO AO TRABALHO PRATICO FINAL DA DISCIPLINA DE ALGORITMOS E ESTRUTURA DE DADOS ---------\n");
    printf("Nosso programa tem como objetivo criar uma arvore AVL a partir de uma sequencia de numeros informados pelo usuario!\n");
    printf("Por favor, informe o nome de usuario\n");
    printf("Usuario: ");
    scanf("%s" ,nome);
    printf("Favor informar PIN de acesso:\n");
    printf("***** DICA: EM QUAL SEMESTRE ESTAMOS *****\n");
    printf("Senha: "); //A senha correta é 20211, mas recomendamos que teste com uma senha aleatória
    scanf("%d" ,&senha);

    if(senha == entrada){
        printf(ANSI_COLOR_GREEN "\nAcesso concedido!\n\n" ANSI_COLOR_RESET);
        return 1;
    }
    else{
        printf(ANSI_COLOR_RED "\nAcesso negado! \n\n" ANSI_COLOR_RESET);
        return 0;
    }
}



//--------------------- Rodapé do Programa -------------------------------//

void rodape(){
    printf("UFSC Blumenau - Universidade Federal de Santa Catarina\n");
    printf("Developed by:\n       Carlos Jose Persuhn");
    printf("\nSemestre: 2021-1\n");
    printf("Plataforma utilizada: VSCode\n");
    printf("Sistema operacional: Windows 10");
}



//---------------------------- Espaço de código fonte para Árvore ------------------------------//

typedef struct Tree{ //Estrutura padrão para tipo árvore
    int numero; //Armazena o campo com o número de cada árvore/subárvore
    int altura; //Armazena a altura de cada árvore/subárvore
    struct Tree *left, *right; //Responsável por criar as direções (ponteiros) para a esquerda e direita
}TREE; //Define o nome da estrutura para TREE

TREE *create_tree(){ //Função responsável por criar a árvore
   return NULL; //Retorna NULL, para a árvore informada, pois ainda está vazia
}

int descobre_maior(int x, int y) { //Responsável por verificar qual lado é omaior da árvore/subárvore, para em conjunto com outras...
    if (x > y)                     //funções, estabelecer a altura correta das árvores
        return x; //Retorna x quando este é o maior
    return y; //Retorna y quando este é o maior
}

int altura_nodo(TREE *arvore){ //Responsável por informar a altura de cada nó, pois se faz necessário em diversos lugares do programa
    if(arvore == NULL) //Se a árvore estiver vazia, ou, chegarmos no último nó...
        return 0; //Retorna 0
    return arvore->altura; //Senão, apenas retorna a altura da árvore
}

int define_altura(TREE* auxiliar) { //Responsável por definir a altura de cada nó
    auxiliar->altura = descobre_maior(altura_nodo(auxiliar->left), altura_nodo(auxiliar->right)) + 1; //Gerencia as duas funções anteriores...
//Verificando qual lado é mais alto, e definindoa altura correta aos nós
    return auxiliar->altura; //Retorna a altura do nó
}

int diferenca_altura(TREE *arvore){ //Responsável por verificar o desbalanceamento de cada subárvore/árvore
                                    //-2 equivale a desbalanceamento à esquerda, 2 equivale ao desbalanceamento à direita 
                                    //e 0 equivale ao balanceamento
                                    //Caso a diferença seja em 1 ou -1 a árvore também está balanceada;
    if(arvore == NULL) //Se a árvore estiver vazia não existe desbalanceamento          
        return 0; //Portanto, retorna-se 0
    TREE *auxiliar = arvore; //Arvore auxiliar apontando para o mesmo local que a árvore original
        int teste = altura_nodo(auxiliar->right) - altura_nodo(auxiliar->left); //Variável responsável por armazenar o valor da diferença
    if(teste == 2 || teste == -2) //Condições de desbalanceamento
        return teste; //Caso entre em alguma condição, retorna a mesma
    return teste; //Senão, retorna apena a diferença (0 ou 1 ou -1) = balanceada
}

//Em nosso programa se fez necessário duas funções para o balançeamento
//Uma para a esquerda
//Outra para a direita
//Isso ocorre pois a manipulação difere em cada lado

void altura_p_balanceamento(TREE* nodo_A, TREE* nodo_C, TREE *arvore){ //Função responsável por redefinir a altura após os balanceamentos
    nodo_C->altura = define_altura(nodo_C);
    nodo_A->altura = define_altura(nodo_A);
    arvore->altura = define_altura(arvore);
}

TREE *balanceamento_direito(TREE *arvore){ //Responsável pelo balanceamento direcionado a direita
//A função segue os parâmetros de balanceamento aprendidos em sala

    TREE *nodo_A, *nodo_B, *nodo_C; //A = menor, B = médio, C = menor
    TREE *t0; //Guarda o valor restante solto em memória após manipulação
    

//As próximas 3 linhas equivalem ao desbalanceamento em linha, exemplo:
//    5
//        6
//            7

    nodo_A = arvore; //No balanceamento para a direita, o menor nó é sempre o nó em que ocorre desbalanceamento
    nodo_B = arvore->right; //O nó direito da subárvore é o médio
    nodo_C = (arvore->right)->right; //E o último nó do desbalanceamento é o maior

    if(diferenca_altura(arvore->right) == -1 || diferenca_altura(arvore->right) == -2){ //Se houver diferença de -1 no filho da direita..

        TREE *t1; //Ponteiro auxiliar para não perder variáveis
        nodo_A = arvore; //Nodo_A vira a arvore (menor elemento)
        nodo_C = arvore->right; //Nodo_B vira o valor médio
        nodo_B = nodo_C->left; //Nodo_C vira o maior valor entre os três 
        t1 = nodo_B->right; //t1 existe caso haja algum nó, para este não ser perdido
        t0 = nodo_B->left; //t0 existe caso haja algum nó, para este não ser perdido

        arvore = nodo_B; //A raiz da sub-árvore será o nodo_B
        nodo_B->left = nodo_A; //A esquerda de B, encontra-se o nodo_A
        nodo_B->right = nodo_C; //E o nodo_C a direita de B
        nodo_C->left = t1; //t1 se encontrará a esquerda de C
        nodo_A->right = t0; //t0 se encontrará a direita de A

        altura_p_balanceamento(nodo_A, nodo_C, arvore); //Redefine a altura dos nós manipulados

        return arvore; //retorna a raiz da sub-árvore
    }

    if(diferenca_altura(arvore->left) == 1 || diferenca_altura(arvore->left) == 2){ //Se houver diferença de altura no filho da esquerda

        TREE *t1; //Ponteiro auxiliar para não perder variáveis
        nodo_C = arvore; //nodo_C recebe a raiz (maior valor)
        nodo_A = arvore->left; //nodo_A recebe o menor valor
        nodo_B = nodo_A->right; //nodo_B recebe o valor médio
        t1 = nodo_B->right; //t1 existe caso haja algum elemento, para que o mesmo não se perca 
        t0 = nodo_B->left; //t0 existe caso haja algum elemento, para que o mesmo não se perca

        arvore = nodo_B; //A raiz da sub-árvore passará a apontar então para nodo_B
        nodo_B->left = nodo_A; //A esquerda de B, se posicionará o nodo_A
        nodo_B->right = nodo_C; //E, a direita o nodo_C
        nodo_C->left = t1; //t1 se encontrará a esquerda de C
        nodo_A->right = t0; //t0 se encotrará a direita de A

        altura_p_balanceamento(nodo_A, nodo_C, arvore); //Redefine a altura dos nós manipulados

        return arvore; //Retorna a raiz da sub-árvore
    }

    if(nodo_C == NULL){ //Condição para desbalanceamentos que não ocorrem em linha, pois então, o maior nodo não será o último da linha
        TREE *t1; //variável auxiliar para organizar as folhas da subárvore em desbalanceamento
        
        nodo_C = arvore->right; //Neste caso, o nodo C se torna o maior
        nodo_B = (arvore->right)->left; //Nó B se torna o intermediário, note que só as posições se alteram
        t0 = nodo_B->left; //t0 existe caso haja algum valor que sobra em B para a direita
        t1 = nodo_B->right; //t1 existe caso haja algum valor que sobra em B para a esquerda

        arvore = nodo_B; //A "raiz" da subárvore apontará para o valor médio
        nodo_B->right = nodo_C; //O filho direito da nova raiz será o nó mais alto do desbalanceamento
        nodo_B->left = nodo_A; //O filho esquerdo da nova raiz receberá o menor valor entre os 3
        nodo_C->left = t0; //Caso não tenha nada, tanto t0 e t1, não deixa entrar em loop infinito (para testar, tente comentar esta linha do código)
        nodo_A->right = t1; //Caso tenha algum valor, tanto t0 como t1, atribui eles como folhas da nova subárvore
        
        altura_p_balanceamento(nodo_A, nodo_C, arvore); //Função responsável por redefinir a altura de cada nó alterado da árvore

        return arvore; //Retorna a árvore
    }

//Caso não entremos no desbalanceamento especial..

    t0 = nodo_B->left; //t0 recebe o valor sobrando
    arvore = nodo_B; //a "raiz" da árvore então, vira ovalor médio
    nodo_B->left = nodo_A; //O filho esquerdo da nova raiz se torna o menor valor entre os 3
    nodo_A->right = t0; //Tendo ou não algum valor, esta linha é de extrema importância pra não ocorrer um loop entre B e A
//Note que não é preciso definir que C será filho direito de B, pois isso não é alterado
    
    altura_p_balanceamento(nodo_A, nodo_C, arvore); //Novamente, redefine a altura dos nós alterados
//Embora pareça uma linha de pouca relevância, esta função foi criada apenas para reduzir linhas de código, já que é chamada em torno de 4...
//vezes nas execuções de balanceamento

    return arvore; //retorna a nova raiz
}

TREE *balanceamento_esquerdo(TREE *arvore){ //Função para a ocorrência de desbalanceamento esquerdo
    TREE *nodo_A, *nodo_B, *nodo_C; //Criação dos ponteiros do tipo arvore, para poder manipular o desbalanceamento
    TREE *t0; //Ponteiro do tipo arvore para armazenar os filhos dos nós principais
    
    nodo_A = (arvore->left)->left; //Inicialmente, nodo_A apontará para o ultimo elementoo em linha (exemplo na função anterior)
    nodo_B = arvore->left; //nodo_B receberá o valor médio
    nodo_C = arvore; //E nodo_C receberá o nodo de maior valor

    if(diferenca_altura(arvore->right) == -1 || diferenca_altura(arvore->right) == -2){ //A explicação desta condição se encontra na função...
    //... de balanceamento_direito, pois funciona da mesma maneira

        TREE *t1;
        nodo_A = arvore;
        nodo_C = arvore->right;
        nodo_B = nodo_C->left;
        t1 = nodo_B->right;
        t0 = nodo_B->left;

        arvore = nodo_B;
        nodo_B->left = nodo_A;
        nodo_B->right = nodo_C;
        nodo_C->left = t1;
        nodo_A->right = t0;

        altura_p_balanceamento(nodo_A, nodo_C, arvore);

        return arvore;
    }

    if(diferenca_altura(arvore->left) == 1 || diferenca_altura(arvore->left) == 2){ //A explicação desta condição também se encontra na...
    //... função de balanceamento_direito, pois seu funcionamento é idêntico a mesma

        TREE *t1;
        nodo_C = arvore;
        nodo_A = arvore->left;
        nodo_B = nodo_A->right;
        t1 = nodo_B->right;
        t0 = nodo_B->left;

        arvore = nodo_B;
        nodo_B->left = nodo_A;
        nodo_B->right = nodo_C;
        nodo_C->left = t1;
        nodo_A->right = t0;

        altura_p_balanceamento(nodo_A, nodo_C, arvore);

        return arvore;
    }
    if(nodo_A == NULL){ //Caso o nodo_A acabe apontando para NULL
        TREE *t1; //Criação de um novo ponteiro do tipo arvore, este armazena um dos filhos dos nós principais
        nodo_A = arvore->left; //nodo_A apontará para a esquerda da raiz da sub-árvore passada como parâmetro
        nodo_B = (arvore->left)->right; //nodo_B receberá o conteúdo de valor médio

        t0 = nodo_B->right; //t0 recebrá o conteúdo direto de B
        t1 = nodo_B->left; //t1 receberá o conteúdo esquerdo de B
        arvore = nodo_B; //A raiz passará a ser o nodo_B
        nodo_B->right = nodo_C; //Contendo em sua direita o nodo_C
        nodo_B->left = nodo_A; //E a esquerda o nodo_A
        nodo_C->left = t0; //t0 passará a ser o conteúdo esquerdo de C
        nodo_A->right = t1; //t1 passará a ser o conteúdo direito de A

        altura_p_balanceamento(nodo_A, nodo_C, arvore); //Redefine a altura dos nós manipulados

        return arvore; //Retorna a raiz da sub-árvore
    }
    //Se por ventura nenhum dos casos anteriores ocorrerem
    t0 = nodo_B->right; //t0 recebe o conteúdo a direita de B
    arvore = nodo_B; //a arvore vira o nodo_B
    nodo_B->right = nodo_C; //nodo_C se posicionará a direita de B
    nodo_C->left = t0; //t0 se posicionará a esquerda de C
    
    altura_p_balanceamento(nodo_A, nodo_C, arvore); //redefine a altura nos nós manipulados

    return arvore; //Retorna a raiz da sub-árvore
}

TREE *inserir_AVL(TREE *arvore, int dado){ //Função responsável pela inserção dos elementos da lista na árvore
    
    if(arvore == NULL){ //Se a parte da memória que está sendo manipulada for NULL
        arvore = malloc(sizeof(TREE)); //Aloca-se um espaço de memória para ela
        arvore->numero = dado; //O campo número recebe o conteúdo proveniente da lista
        arvore->left = NULL; //O ponteiro esquerdo apontará para NULL
        arvore->right = NULL; //O ponteiro direito apontará para NULL
        arvore->altura = 1; //A altura da folha será 1
        //OBS.: Trabalhamos com a altura em 1, pois, foi melhor de verificar o balanceamento
    }
    
    else{ //Caso não aponte para NULL
       TREE *auxiliar = arvore; //Cria-se um ponteiro do tipo arvore, que aponta para a raiz da arvore original
       if(dado < arvore->numero){ //Se o dado a ser inserido for menor que o contido na arvore
           arvore->left = inserir_AVL(auxiliar->left, dado); //Chama-se a função recursivamente até atingir a condição de parada e o elemento é adicionado
           auxiliar->altura = define_altura(auxiliar); //Define a altura desse novo nó e dos já presentes
           if(diferenca_altura(auxiliar) == -2){ //Verifica o desbalanceamento esquerdo
                arvore = balanceamento_esquerdo(auxiliar); //Responsável por corrigir o balanceamento em tempo de execução
            }
           if(diferenca_altura(auxiliar) == 2){ //Verifica o desbalanceamento direito
                arvore = balanceamento_direito(auxiliar); //Responsável por corrigir o balanceamento em tempo de execução
            }
        }
       else{ //Senão
           arvore->right = inserir_AVL(auxiliar->right, dado); //Chama-se a função recursiva até atingir a condição de parada
           auxiliar->altura = define_altura(auxiliar); //Define a altura desse novo nó e dos já presentes na árvore
           if(diferenca_altura(auxiliar) == 2){ //Verifica o desbalanceamento direito
                arvore = balanceamento_direito(auxiliar); //Responsável por corrigir o balanceamento em tempo de execução
            }
           if(diferenca_altura(auxiliar) == -2){ //Verifica o desbalanceamento esquerdo
                arvore = balanceamento_esquerdo(auxiliar); //Responsável por corrigir o balanceamento em tempo de execução
            }
        }
    }
   
   return arvore; //Retorna a raiz da árvore
}


//Função responsável por imprimir a estrutura da árvore, utilizada pelo professor nos problemas de laboratório
void mostra_arvore(TREE *t, int profundidade, char lado){
   int i;
   if (t != NULL){
      for (i = 0; i < profundidade*5; i++){
        if (i > profundidade*5 -5){
	        printf("-");
        } else {
	        printf(" ");
	    }
    }

    printf(">%d (%c) (%d)\n", t->numero, lado, t->altura - 1); //Apenas ajustado para mostrar a altura de cada nó
    profundidade++;
    mostra_arvore(t->left, profundidade, 'L');
    mostra_arvore(t->right, profundidade, 'R');
   }
}


//---------------------------- Espaço de código fonte para listas ------------------------------//

typedef struct lstItem{ //Estrutura padrão para uma lista encadeada
    int number; //Campo para número
    struct lstItem *next; //Ponteiro do tipo lista, para o próximo bloco de conteúdo (elemento da lista)
} lista; //Define o nome da estrutura para lista

lista *cria_lista(){ //Função responsável por criar a lista
   return NULL; //Retorna NULL, pois inicialmente a lista se encontrará vazia
}

void imprime_lista(lista *l){ //Função responsável por imprimir a lista
//Também utilizada nos problemas de laboratório, salvo a modificação da impressão final
    lista *atual = l; 
    while(atual!=NULL){
        if(atual->next == NULL){
            printf("%d", atual->number);
            break;
      } 
        printf("%d -> ", atual->number);
        atual = atual->next;
   }
}

lista* insere_no_inicio(lista *l, int informado){ //Função responsável por inserir um numero no inicio da lista
    lista* novo = malloc(sizeof(lista)); //Um ponteiro pro tipo lista aloca memória para um novo bloco da lista
    novo->number = informado; //O campo do número recebe o valor informado pelo usuário
    novo->next = l; //O ponteiro next apontará para a cabeça da lista
    l = novo; //O ponteiro que aponta para a cabeça, apontará para o novo bloco da lista
}

lista *insere_no_fim(lista *l, int informado){ //Função responsável pela inserção no fim da lista
    lista *novo = malloc(sizeof(lista)); //Um ponteiro pro tipo lista aloca memória para um novo bloco da lista
    novo->number = informado; //O campo do número recebe o valor informado pelo usuário
    novo->next = NULL; //O ponteiro para o próximo elemento da lista apontará para NULL
    if(l == NULL){ //Caso a lista esteja vazia
        l = novo; //O único elemento será este informado
    }
    else{ //Senão
        lista *ultimo = l; //Variável auxiliar do tipo lista que aponta para a cabeça da lista
        while(ultimo->next != NULL){ //Percorre a lista até cehar no fim da mesma
            ultimo = ultimo->next;
        }
        ultimo->next = novo; //Responsável por tornar o novo elemento o último da lista
    }
    return l; //Retorna a cabeça da lista
}

lista *insere_apos(lista *l, int novo_valor, int procurado){ //Função responsável por inserir um elemento em qualquer posição desejada, exceto no início
    lista *objetivo = l; //Ponteiro do tipo lista que aponta para o mesmo local que a lista
    lista *novo = malloc(sizeof(lista)); //Espaço de memória alocado para o novo elemento
    novo->number = novo_valor; //O campo número receberá o valor informado pelo usuário
    if(l == NULL){ //Caso o funcionário tente adicionar um número na lista vazia, mesmo não podendo (informação encontrada na main)
        l = novo; //A lista apontará para o novo elemento
        novo->next = NULL; //O campo next do novo elemento apontará para NULL
        return l; //A função retornará a cabeça da lista
    }
    if(objetivo->number == procurado){ //Se a posição de inserção for logo o primeiro elemento da lista
        novo->next = objetivo->next; //O campo next do novo elemento apontará para o elemento seguinte ao primeiro
        objetivo->next = novo; //E o campo next do primeiro elemento apontará para o novo
    }
    else if(objetivo->next == NULL){ //Caso o usuário queira adicionar após o ultimo elemento
        objetivo->next = novo; //O campo next dele apontará para o novo valor
        novo->next = NULL; //O campo next do novo valor apontará para NULL
    }
    else{ //Senão
        while(objetivo->number != procurado){ //Percorre-se a lista até encontrar a posição desejada
            objetivo = objetivo->next; //O objetivo vira o elemento seguinte
            if(objetivo == NULL){ //Se o elemento seguinte apontar para NULL, quer dizer que não encontramos a posição desejada
                printf("Posicao nao encontrada!\n"); //Informa ao usuário que a posição desejada não foi encontrada
                qtt_verification = 1;  //Variável auxiliar de contagem definida para 1
                return l; //Retorna a cabeça da lista
            }
        }
        novo->next = objetivo->next; //Caso a posição de inserção seja encontrada
        objetivo->next = novo; //O campo next da posição apontará para o novo valor
    }
    
    return l; //Retorna-se a cabeça da lista
}



//----------------------------- Função de execução ------------------------------//

int main(void){

    int input_to_program = 7;
    while(input_to_program != 1){
        input_to_program = cabecalho();
    }

    lista *teste = cria_lista();
    int auxiliar = 100;
    int n_informado;
    int qtt = 0;

    printf("Aqui disbonibilizamos os melhores recursos para criar uma lista a partir da sequencia de numeros que o senhor(a) quiser...\n\n");

    while(auxiliar != 0){
        printf("Especifique o comando:\n");
        printf("1 -> Imprimir lista\n");
        printf("2 -> Inserir no inicio\n");
        printf("3 -> Inserir no fim\n");
        printf("4 -> Inserir apos (apenas para listas com algum elemento)\n");
        printf("0 -> Pronto para tornar arvore?\n");
        scanf("%d" ,&auxiliar);

        if(auxiliar == 1){
            printf("\n\n"); 
            imprime_lista(teste);
            printf("\n\n");
            qtt--;
        }
            
        if(auxiliar == 2){
            printf("Entao, digite um numero: ");
            scanf("%d" ,&n_informado);
            teste = insere_no_inicio(teste, n_informado);
        }

        if(auxiliar == 3){
            printf("Entao, digite um numero: ");
            scanf("%d" ,&n_informado);
            teste = insere_no_fim(teste, n_informado);
        }

        if(auxiliar == 4){
            printf("Entao, digite um numero a ser inserido: ");
            scanf("%d" ,&n_informado);
            printf("Digite o numero que equivale ao local de armazenamento: ");
            int local;
            scanf("%d" ,&local);
            teste = insere_apos(teste, n_informado, local);
            if(qtt_verification = 1){
                qtt--;
                qtt_verification = 0;
            }
            qtt++;
        }

        if(auxiliar == 0){
            qtt--;
        }

        qtt++; 
    }
 
    TREE *arvore_gerada = create_tree();
    lista *meu_auxilio = teste;

    //As próximas 3 linhas são responsáveis por definir a complexidade do código para Nlog(N), pois o while percorre a lista toda O(n).
    //E para cada elemento da lista, é necessário a chamada da função inserção, que possui complexidade log(N).
    //Por via disto, temos as linhas gerando a seguinta equação: Nlog(N), e, como nenhuma outra função do código possui complexidade maior
    //Esta, acaba sendo a complexidade no programa elaborado por nós!
    while(meu_auxilio != NULL){
        arvore_gerada = inserir_AVL(arvore_gerada, meu_auxilio->number);
        meu_auxilio = meu_auxilio->next;
    }

    printf("\n\n\n");
    printf("*******************************************************************************************\n");
    printf("------------ TOTAL DE NUMEROS INFORMADOS: %d ------------\n\n",qtt);
    mostra_arvore(arvore_gerada, 0, 'T');
    printf("\n");
    printf("Os numeros informados foram: \n");
    imprime_lista(teste);
    printf("\n*******************************************************************************************");
    printf("\n\n\n");

    rodape();

    return 0;
    //Espero que tenha gostado!

}
