/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: eveli
 *
 * Created on 09 de Dezembro de 2017, 07:46
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int menu(){
    int n;
    printf("1- Cadastrar turma\n");
    printf("2- Consultar um aluno\n");
    printf("3- Alterar dados de um aluno\n");
    printf("4- Listar dados de uma turma\n");
    printf("5- Terminar a execucao\n");
    scanf("%d", &n);
    return n;

}
int main(int argc, char** argv) {
    int n, num;
    do{
        n=menu();
        if(n==1){
            cadastrar(&num);
            if(num==0){
                printf("Cadastro realizado com sucesso\n");
            }
            else{
                printf("Cadastro não foi realizado");
            }
        }
        else if(n==2){
            consulta();

        }
        else if(n==3){
            altera();
        }
        else if(n==4){
            lista();
        }

    }while(n!=5);


    return (EXIT_SUCCESS);
}

