#define MAXPILHA 30

struct TpPilhaM2{

    int TOPO[MAXPILHA], BASE[MAXPILHA];
    int PILHA[MAXPILHA];
};

//Operacoes Associadas

void Inicializar(TpPilhaM2 &PM, int QtdePILHAS){

    int QtdeElem = MAXPILHA / QtdePILHAS;
    
    for(int i = 0; i <= QtdePILHAS; i++){

        PM.TOPO[i] = i * QtdeElem - 1;
		PM.BASE[i] = i * QtdeElem;
    }
}

char PMCheia(TpPilhaM2 PM, int NP){
    return PM.TOPO[NP - 1] == PM.BASE[NP] - 1;
}

char PMVazia(TpPilhaM2 PM, int NP){
    return PM.TOPO[NP - 1] < PM.BASE[NP - 1];
}

void PUSH(TpPilhaM2 &PM, int Elemento, int NP){
    PM.PILHA[++PM.TOPO[NP - 1]] = Elemento;
}

char POP(TpPilhaM2 &PM, int NP){
    return PM.PILHA[PM.TOPO[NP - 1]--];
}

char ElementoTopo(TpPilhaM2 &PM, int NP){
    return PM.PILHA[PM.TOPO[NP - 1]];
}

void ExibirPilha(TpPilhaM2 PM, int NP){
	
    while(!PMVazia(PM, NP))
		printf("\n%d", POP(PM, NP));
}

// MOLDURA PARA O JOGO

void Moldura(int CI, int LI, int CF, int LF, int Frente){
	
	textcolor(Frente);
	//textbackground(Fundo);
	
	gotoxy(CI,LI);
	printf("%c", 201);
	gotoxy(CF,LI);
	printf("%c", 187);
	gotoxy(CI,LF);
	printf("%c", 200);
	gotoxy(CF,LF);
	printf("%c", 188);
	
	for(int a=CI+1; a<CF; a++){
		gotoxy(a, LI);
		printf("%c", 205);
		gotoxy(a, LF);
		printf("%c", 205);
	}
	
	for(int a=LI+1; a<LF; a++){
		gotoxy(CI, a);
		printf("%c", 186);
		gotoxy(CF, a);
		printf("%c", 186);
	}
	
	textcolor(7);
	//textbackground(0);
}

void FormPrincipal(void){
	
	system("cls");
	
	Moldura(38, 3, 75, 30, 15); // moldura externa
	
	Moldura(39, 4, 74, 6, 5); // moldura do titulo
	
	gotoxy(45, 5);
	printf("~~~~ TORRE DE HANOI ~~~~");
	
	Moldura(39, 7, 74, 29, 3); // moldura do menu/jogo
}

////////////////// TORRE DE HANOI MANUAL //////////////////

void printa_torres(TpPilhaM2 PM, int num_discos){
    
    FormPrincipal();
    int movimentos = pow(2, num_discos) - 1;
    gotoxy(44, 8);
    printf("Movimentos necessarios: %d", movimentos);
    
    int y, x, t = 1;
	
	y = 10;
	
    // Imprimir as torres linha por linha
    for(int i = num_discos; i > 0;i--){
    	
    	x = 50;
    	
    	for(int t = 0; t < 3; t++){
    		
    		if(i <= PM.TOPO[t] - PM.BASE[t] + 1){
	        	gotoxy(x, y);
	        	printf("%d", POP(PM, t + 1));
	        }
	            
	        else{
	        	gotoxy(x, y);
	        	printf("|");
	        }
	        
	        x += 7;
    	}
        
        y++;
    }
    
	y = num_discos + 9;
	
	gotoxy(49, ++y);
	printf("-----------------");
	gotoxy(50, ++y);
    printf("1      2      3");
}

bool Ganhou (TpPilhaM2 PM, int jogadas){
	
	if(PMVazia(PM, 1) && PMVazia(PM, 2) || PMVazia(PM, 1) && PMVazia(PM, 3)){
		gotoxy(41, 20);
		printf("Voce precisou de %d movimentos!", jogadas);
		MessageBox(NULL, "Olá, Jogador!\nParabéns pela conquista, você venceu o nosso jogo!", "YOU WIN", MB_OK);
	}
}

void Jogar (TpPilhaM2 PM, int num_discos){
	
	char op;
	int torre, cont = 0, aux, Elem;
	
	do{
		
		int y = 23;
		printa_torres(PM, num_discos);
		
		gotoxy(41, y++);
		printf("Retirar disco de (1-2-3): ");
		fflush(stdin);
		scanf("%d", &torre);
			
		while(torre > 3 || torre < 1){
			
			gotoxy(41, y++);
			printf("Torre invalida!");
			
			gotoxy(41, y++);
			printf("Retirar disco de (1-2-3): ");
			fflush(stdin);
			scanf("%d", &torre);
		}
		
		aux = torre;
		Elem = ElementoTopo(PM, torre);
		POP(PM, torre);
		
		gotoxy(41, y++);
		printf("Colocar disco em (1-2-3): ");
		fflush(stdin);
		scanf("%d", &torre);
			
		while(torre > 3 || torre < 1){
			
			gotoxy(41, y++);
			printf("Torre invalida!");
			
			gotoxy(41, y++);
			printf("Colocar disco em (1-2-3): ");
			fflush(stdin);
			scanf("%d", &torre);
		}
		
		if(PMVazia(PM, torre))
			PUSH(PM, Elem, torre);
			
		else if(!PMCheia(PM, torre)&& Elem < ElementoTopo(PM, torre))
			PUSH(PM, Elem, torre);
		
		else{
			
			gotoxy(41, y++);
			printf("Jogada invalida!");
			gotoxy(41, y++);
			printf("Tente colocar em outra torre: ");
			fflush(stdin);
			scanf("%d", &torre);
			
			while(!PMVazia(PM, torre) && Elem > ElementoTopo(PM, torre)){
				
				gotoxy(41, y++);
				printf("Jogada invalida!");
				gotoxy(41, y++);
				printf("Tente colocar em outra torre: ");
				fflush(stdin);
				scanf("%d", &torre);
			}
			
			PUSH(PM, Elem, torre);
		}
		
		if(aux != torre)
			cont++;
		
		printa_torres(PM, num_discos);
		gotoxy(41, 23);
		printf("Disco movido!");
		if(Ganhou(PM, cont))
			return;
		
		gotoxy(41, 24);
		printf("Pressione ENTER para continuar!");
		gotoxy(41, 25);
		printf("Pressione ESC para sair do jogo!");
		op = getch();
		
	}while(op != 27);
}

void TorreDeHanoi(int discos){
	
    TpPilhaM2 PM;
	
    Inicializar(PM, 3);
    
    for(int i = discos; i > 0; i--)
    	PUSH(PM, i, 1);
    
    Jogar(PM, discos);
}

////////////////// TORRE DE HANOI AUTOMATICA //////////////////

void moverDisco(TpPilhaM2 PM, int origem, int destino, int discos){
	printa_torres(PM, discos);
	gotoxy(46, 23);
    printf("Mover disco de %d --> %d", origem, destino);
    Sleep(1500);
}

void moverEntreTorres(TpPilhaM2 &PM, int origem, int destino, int discos){
	
    int topoOrigem = ElementoTopo(PM, origem);
    int topoDestino = ElementoTopo(PM, destino);
    
	// Origem está vazia
    if(PMVazia(PM, origem)){
    	PUSH(PM, POP(PM, destino), origem);
        moverDisco(PM, destino, origem, discos);
    }
    
    // Destino está vazio
    else if(PMVazia(PM, destino)){
    	PUSH(PM, POP(PM, origem), destino);
        moverDisco(PM, origem, destino, discos);
    }
    
    // Disco da origem é menor
    else if(topoOrigem < topoDestino){
    	PUSH(PM, POP(PM, origem), destino);
        moverDisco(PM, origem, destino, discos);
    }
    
    // Disco do destino é menor
    else{
    	PUSH(PM, POP(PM, destino), origem);
        moverDisco(PM, destino, origem, discos);
    }
}

void TorreDeHanoiAutomatica(int discos, int origem, int destino, int auxiliar, TpPilhaM2 &PM){
	
	FormPrincipal();
    
    if(discos == 1){
    	
        // Mover o disco 1 da origem para o destino
        moverDisco(PM, origem, destino, discos);
        PUSH(PM, POP(PM, origem), destino);
        return;
    }
    
    // Se o número de discos for par, troque o destino e o auxiliar
    if (discos % 2 == 0){
        int temp = destino;
        destino = auxiliar;
        auxiliar = temp;
    }
    
    for(int i = discos; i > 0; i--)
    	PUSH(PM, i, 1);
    
    int movimentos = pow(2, discos) - 1;
    
    for (int i = 1; i <= movimentos; i++){
    	
    	if(i % 3 == 0)
            moverEntreTorres(PM, auxiliar, destino, discos); 
    	
        else if(i % 3 == 1)
            moverEntreTorres(PM, origem, destino, discos);
        
		else if(i % 3 == 2)
            moverEntreTorres(PM, origem, auxiliar, discos);
        
		else if(i % 3 == 3)
            moverEntreTorres(PM, auxiliar, destino, discos);
    }
    
    gotoxy(43, 24);
    printf("Torre concluida com sucesso!");
    printf("\n\n\n\n");
}
