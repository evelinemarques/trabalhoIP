#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define N 400
#define P 2
typedef struct{
    int matricula, falta;
    char nome[N], situacao[N];
    double prova[P], listas[P], NT, NF;  
}cad;

void cadastrar(int *num){
    FILE *fp;
    cad aluno[N], a[N];
    int i, n, cont=0;
    char caminho[N], arq[N], nome[N];
    double mp,ml, f, par=128; //variável temporária para calculo da Nota Final e porcentagemd e faltas
    
    //Entra com o nome do arquivo e o caminho na memoria
    scanf(" %[^\n]", arq);
    scanf(" %[^\n]", caminho);
    strcat(caminho, arq);
    fp= fopen(caminho, "wb");
    if(fp==NULL){
        printf("Erro ao abrir\n");
    }
    //Cadastra informações do aluno
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
    *num=cont;
    fwrite(&aluno, sizeof(aluno),1, fp);
    fclose(fp);
    /*fp= fopen(caminho, "rb");
    //Escreve todos os dados no arquivo
    fread(&a, sizeof(a), 1, fp);
    fclose(fp);
    for(i=0;i<cont-1;i++){
        printf("%s\n", a[i].situacao);
    }*/

    
}
//Modulo de consulta a partir de um número de matrícula informado
void consulta(int num){
    char nome[N], ende[N];
    cad aluno[N];
    int mat, i, j, k;
    FILE *fp;
    do{
        printf("Digite o nome de um arquivo de turma\n");
        scanf(" %[^\n]", nome);
        fp=fopen(nome, "rb");

    }while(fp==NULL&&strcmp(nome,"fim")!=0);
    size_t result = fread(&aluno, sizeof(aluno), 1, fp);
    printf("%d\n", result);
    fclose(fp);
    do{
        printf("Informe o numero de matricula\n");
        scanf("%d", &mat);
        if(mat!=0){
            for(i=0;i<=num;i++){
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

void altera(int num){
    char nome[N], ende[N];
    cad aluno[N];
    int mat, i, j, n, f;
    double mp, ml, par=128;
    FILE *fp;
    do{
        printf("Digite o nome de um arquivo de turma\n");
        scanf(" %[^\n]", nome);
        fp=fopen(nome, "rb"); //Alteração para abertura para ler

    }while(fp==NULL&&strcmp(nome,"fim")!=0);
    fread(&aluno, sizeof(aluno), 1, fp);
    fseek(fp,n, SEEK_SET); 
    fclose(fp);
    do{
        printf("Informe um numero de matricula\n");
        scanf("%d", &mat);
        if(mat!=0){
            for(i=0;i<num;i++){
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
            fopen(nome,"wb"); //abertura para escrita
            fwrite(&aluno, sizeof(aluno), 1, fp);
            n = n + sizeof(cad);
            fclose(fp);//Fechar arquivo
        } 
    }while(mat!=0);
    
}

