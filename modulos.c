/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define P 2
#define N 400

/*Estrutura para recer os dados dos alunos*/

typedef struct{
    int matricula, falta;
    char nome[N], situacao[N];
    double prova[P], listas[P], NT, NF;  
}cad;

/*Modulo cadastra alunos*/

void cadastrar(int *num){
    FILE *fp;
    cad *aluno, a;
    int i, n, cont=0, aux=0;
    char caminho[N], arq[N], nome[N];
    double mp,ml, f, par=128; //Variáveis usadas no cálculo da media final e frequencia
   /*Recebe o nome e caminho do arquivo*/
    printf("Informe o nome do arquivo\n");
    scanf(" %[^\n]", arq);
    printf("Informe o caminho na memoria\n");
    scanf(" %[^\n]", caminho);
    strcat(caminho, arq);
    /*Abre o arquivo*/
    fp=fopen(caminho, "wb");
    if(fp==NULL){
        printf("Erro ao abrir\n");
    }
    /*Aloca memoria*/
    aluno=(cad*)malloc(N*sizeof(cad));
    if(aluno==NULL){
        printf("Falta memória\n");
    }
    /* Cadastra alunos na struct cad*/
    do{
        printf("Matricula\n");
        scanf("%d", &aluno[cont].matricula);
        if(aluno[cont].matricula!=0){
            mp=0;
            ml=0;
            printf("Nome\n");
            scanf(" %[^\n]", aluno[cont].nome);
            for(i=0;i<P;i++){
                printf("Prova %d\n", i+1);
                scanf("%lf", &aluno[cont].prova[i]);
                mp=aluno[cont].prova[i]+mp;
            }
            for(i=0;i<P;i++){
                printf("Lista %d\n", i+1);
                scanf("%lf", &aluno[cont].listas[i]);
                ml=aluno[cont].listas[i]+ml;
            }
            printf("Nota trabalho\n");
            scanf("%lf", &aluno[cont].NT);
            printf("Faltas\n");
            scanf("%d", &aluno[cont].falta);
            //Calcula nota final
            aluno[cont].NF=((mp/P)*0.8)+((ml/P)*0.1)+(aluno[cont].NT*0.1);
            f=(aluno[cont].falta/par)*100;
            if(aluno[cont].NF>=6){
                if(f<25)
                    strcpy(aluno[cont].situacao, "Aprovado");
                else
                    strcpy(aluno[cont].situacao, "Reprovado por ausencia");
            }
            else if(aluno[cont].NF<6){
                if(f<25)
                    strcpy(aluno[cont].situacao, "Reprovado por nota");
                else
                    strcpy(aluno[cont].situacao, "Reprovado por ausencia e nota");
            } 
        }
        cont++;
    }while(aluno[cont-1].matricula!=0);
    cont=cont-1;
    /*Escreve os dados da struct cad no arquivo*/
    fwrite(aluno, sizeof(aluno),N, fp);
    fclose(fp);
    fp= fopen(caminho, "rb");
    while(fread(&a, sizeof(cad),1, fp)==1){
        aux++;
    }
    fclose(fp);
    if(aux==cont&&aux>0){
        *num=0;
    }
    else{
        *num=1;
    }
 
}

//Modulo consulta
void consulta(){
    char nome[N];
    cad *aluno, a;
    int mat, i, j, k, n=1;
    FILE *fp;
    aluno=(cad*)malloc(N*sizeof(cad));
    if(aluno==NULL){
        printf("Falta memória\n");
    }
    do{
        printf("Digite o nome de um arquivo de turma\n");
        scanf(" %[^\n]", nome);
        fp=fopen(nome, "rb");
    }while(fp==NULL&&strcmp(nome,"fim")!=0);
    while(fread(&a, sizeof(cad),1, fp)==1){
        n++;
    }
    fclose(fp);
    fp= fopen(nome, "rb");
    fread(aluno, sizeof(aluno), N, fp);
    fclose(fp);
    do{
        printf("Informe o numero de matricula\n");
        scanf("%d", &mat);
        if(mat!=0){
            for(i=0;i<n;i++){//olhar
                if(aluno[i].matricula==mat){
                    printf("Nome: %s\n", aluno[i].nome);
                    for(j=0;j<P;j++){
                        printf("Prova %d: %.2lf", j+1, aluno[i].prova[j]);
                    }
                    printf("\n");
                    for(j=0;j<P;j++){
                        printf("Lista %d: %.2lf ", j+1, aluno[i].listas[j]);
                    }
                    printf("\n");
                    printf("Nota do trabalho: %.2lf\n", aluno[i].NT);
                    printf("Nota final: %.2lf\n", aluno[i].NF);
                    printf("Numero de ausencias: %d\n", aluno[i].falta);
                    printf("Situacao: %s\n", aluno[i].situacao);
                }
            }
        }
        
    }while(mat!=0);   
}
//Modulo de alteração dos dados
void altera(){
    char nome[N];
    cad *aluno, a;
    int mat, i, j, k, n=1;
    double mp,ml, f, par=128;
    FILE *fp;
    aluno=(cad*)malloc(N*sizeof(cad));
    if(aluno==NULL){
        printf("Falta memória\n");
    }
    do{
        printf("Digite o nome de um arquivo de turma\n");
        scanf(" %[^\n]", nome);
        fp=fopen(nome, "rb");
    }while(fp==NULL&&strcmp(nome,"fim")!=0);
    while(fread(&a, sizeof(cad),1, fp)==1){
        n++;
    }
    fclose(fp);
    fp= fopen(nome, "rb");
    fread(aluno, sizeof(aluno), N, fp);
    fclose(fp);
    do{
        printf("Informe um numero de matricula\n");
        scanf("%d", &mat);
        if(mat!=0){
            for(i=0;i<=n;i++){
                if(aluno[i].matricula==mat){
                    if(aluno[i].matricula==mat){
                        printf("Nome: %s\n", aluno[i].nome);
                    for(j=0;j<P;j++){
                        printf("Prova %d: %.2lf", j+1, aluno[i].prova[j]);
                    }
                        printf("\n");
                    for(j=0;j<P;j++){
                        printf("Lista %d: %.2lf ", j+1, aluno[i].listas[j]);
                    }
                        printf("\n");
                        printf("Nota do trabalho: %.2lf\n", aluno[i].NT);
                        printf("Nota final: %.2lf\n", aluno[i].NF);
                        printf("Numero de ausencias: %d\n", aluno[i].falta);
                        printf("Situacao: %s\n", aluno[i].situacao);
                        printf("******Cadastrar novos dados*****\nNome\n");
                        scanf(" %[^\n]", aluno[i].nome);
                        for(j=0;j<P;j++){
                            printf("Prova %d\n", j+1);
                            scanf("%lf", &aluno[i].prova[j]);
                            mp=aluno[i].prova[j]+mp;
                        }
                        for(j=0;j<P;j++){
                            printf("Lista %d\n", j+1);
                            scanf("%lf", &aluno[i].listas[j]);
                            ml=aluno[i].listas[j]+ml;
                        }
                        printf("Nota trabalho\n");
                        scanf("%lf", &aluno[i].NT);
                        printf("Faltas\n");
                        scanf("%d", &aluno[i].falta);
                        //Calcula nota final
                        aluno[i].NF=((mp/P)*0.8)+((ml/P)*0.1)+(aluno[i].NT*0.1);
                        f=(aluno[i].falta/par)*100;
                        if(aluno[i].NF>=6){
                            if(f<25)
                                strcpy(aluno[i].situacao, "Aprovado");
                            else
                                strcpy(aluno[i].situacao, "Reprovado por ausencia");
                        }
                        else if(aluno[i].NF<6){
                            if(f<25)
                                strcpy(aluno[i].situacao, "Reprovado por nota");
                            else
                                strcpy(aluno[i].situacao, "Reprovado por ausencia e nota");
                        }
                    }
                }
            } 
            fp=fopen(nome, "wb");
            fwrite(aluno, sizeof(aluno), N, fp);
            fclose(fp);
      
        }
        
    }while(mat!=0);
}

//Modulo Listagem de alunos
/*Menu lista*/
int menulista(){
    int n;
    printf("1 - listar os alunos por ordem crescente de matricula\n");
    printf("2 - listar os alunos por ordem alfabetica de nome\n");
    printf("3 - Listar os alunos por ordem crescente de nota final\n");
    printf("4 - terminar e voltar para processar nova turma\n");
    printf("5 - terminar a execucao do modulo\n");
    scanf("%d", &n);
    return n;
}
void lista(){
    char nome[N];
    cad *aluno, a, aux;
    int mat, i, j, k, n=1, num=4;
    FILE *fp;
    aluno=(cad*)malloc(N*sizeof(cad));
    if(aluno==NULL){
        printf("Falta memória\n");
    }
    
    
    do{
        /*Ordem crescente de matricula*/
        if(num==1){
            for(i=0;i<n; i++){
                for(j=0;j<=i+1;j++){
                    if(aluno[j].matricula>aluno[i].matricula){
                        aux=aluno[i];
                        aluno[i]=aluno[j];
                        aluno[j]=aux;
                    }
                }
            }
            for(i=0;i<n;i++){
                printf("Matricula: %d\n", aluno[i].matricula);
                printf("Nome: %s\n", aluno[i].nome);
                for(j=0;j<P;j++){
                    printf("Prova %d: %.2lf", j+1, aluno[i].prova[j]);
                }
                printf("\n");
                for(j=0;j<P;j++){
                    printf("Lista %d: %.2lf ", j+1, aluno[i].listas[j]);
                }
                printf("\n");
                printf("Nota do trabalho: %.2lf\n", aluno[i].NT);
                printf("Nota final: %.2lf\n", aluno[i].NF);
                printf("Numero de ausencias: %d\n", aluno[i].falta);
                printf("Situacao: %s\n", aluno[i].situacao);
            }
        }
        /*Ordem alfabética*/
        else if(num==2){
            for(i=0;i<n; i++){
                for(j=0;j<=i+1;j++){
                    if(strcmp(aluno[j].nome,aluno[i].nome)>0){
                        aux=aluno[i];
                        aluno[i]=aluno[j];
                        aluno[j]=aux;
                    }
                }
            }
            for(i=0;i<n;i++){
                printf("Matricula: %d\n", aluno[i].matricula);
                printf("Nome: %s\n", aluno[i].nome);
                for(j=0;j<P;j++){
                    printf("Prova %d: %.2lf", j+1, aluno[i].prova[j]);
                }
                printf("\n");
                for(j=0;j<P;j++){
                    printf("Lista %d: %.2lf ", j+1, aluno[i].listas[j]);
                }
                printf("\n");
                printf("Nota do trabalho: %.2lf\n", aluno[i].NT);
                printf("Nota final: %.2lf\n", aluno[i].NF);
                printf("Numero de ausencias: %d\n", aluno[i].falta);
                printf("Situacao: %s\n", aluno[i].situacao);
            }
        }
        /*Ordem crescente de nota final*/
        else if(num==3){
            for(i=0;i<n; i++){
                for(j=0;j<=i+1;j++){
                    if(aluno[j].NF<aluno[i].NF){
                        aux=aluno[i];
                        aluno[i]=aluno[j];
                        aluno[j]=aux;
                    }
                }
            }
            for(i=0;i<n;i++){
                printf("Matricula: %d\n", aluno[i].matricula);
                printf("Nome: %s\n", aluno[i].nome);
                for(j=0;j<P;j++){
                    printf("Prova %d: %.2lf", j+1, aluno[i].prova[j]);
                }
                printf("\n");
                for(j=0;j<P;j++){
                    printf("Lista %d: %.2lf ", j+1, aluno[i].listas[j]);
                }
                printf("\n");
                printf("Nota do trabalho: %.2lf\n", aluno[i].NT);
                printf("Nota final: %.2lf\n", aluno[i].NF);
                printf("Numero de ausencias: %d\n", aluno[i].falta);
                printf("Situacao: %s\n", aluno[i].situacao);
            }
        }
        else if(num==4){
            do{
                printf("Digite o nome de um arquivo de turma\n");
                scanf(" %[^\n]", nome);
                fp=fopen(nome, "rb");
            }while(fp==NULL&&strcmp(nome,"fim")!=0);
            while(fread(&a, sizeof(cad),1, fp)==1){
                n++;
            }
            fclose(fp);
            fp= fopen(nome, "rb");
            fread(aluno, sizeof(aluno), N, fp);
            fclose(fp);
        }
        num=menulista();
        
    }while(num!=5);
}
