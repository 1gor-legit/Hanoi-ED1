#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <conio2.h>
#include <math.h>

#include "TAD.h"

int main(){
	
	int discos, op, y = 10;
	TpPilhaM2 PM;
	
	Inicializar(PM, 3);
	
	FormPrincipal();
	
	gotoxy(45, 8);
	printf("-> Como deseja jogar? <-");
	gotoxy(41, y);
	printf("Manual(1) | Automatico(2): ");
	scanf("%d", &op);
	
	while(op > 2 || op < 1){
		gotoxy(41, ++y);
		printf("Opcao invalida, tente");
		gotoxy(41, ++y);
		printf("novamente!: ");
		scanf("%d", &op);
	}
	
	FormPrincipal();
	
	y = 10;
	
	gotoxy(45, 8);
	printf("-> Como deseja jogar? <-");
	
	gotoxy(41, y);
    printf("Escolha com quantos discos");
	gotoxy(41, ++y);
	printf("deseja jogar(3-10): ");
    scanf("%d", &discos);
    
    while(discos > 10 || discos < 3){
		gotoxy(41, ++y);
		printf("Quantidade indisponivel");
		gotoxy(41, ++y);
		printf("tente novamente: ");
		scanf("%d", &discos);
	}
	
	switch(op){
		
		case 1: TorreDeHanoi(discos);
				break;
				
		case 2: TorreDeHanoiAutomatica(discos, 1, 3, 2, PM);	
	}
	
    return 0;
}
