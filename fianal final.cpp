/*
AFFONSO HENRIQUE
ANA KETLEN
JOSÉ MANUEL
JULIANA BALLIN

IINF11A-IFAM CMC

PROFESSOR:EMMERSON SANTA RITA
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

///DECLARACAO GLOBAL
	//STRUCT DE MANUSEIO DE DADOS
	typedef struct{
		char nome[101];
		unsigned long long int matricula;
		char curso[13];
		int faltas;
		//notas[5] será o auxiliar de ordenacao
		//notas[4] será a media
		float notas[6];
	}pessoa;
	//ENUM AUXILIAR REFERENTE AS CORES DO DOS
	enum DOS_COLORS {
	    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
	    LIGHT_GRAY, DARK_GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN,
	    LIGHT_RED, LIGHT_MAGENTA, YELLOW, WHITE 
	};
	//A VARIAVEL MODO DIZ SE VOCE TRABALHARA COM O ARQUIVO REGISTRO OU ALUNO
	int modo=0;
	
//PROTOTIPOS DAS FUNCOES
	//FUNCOES SEM RETORNO
	void acharmatricula();
	void alterar();
	void bordas();
	void bordas2();
	void chamada();
	void destacar(int );
	void excluir();
	void exibir();
	void gotoxy(int ,int );
	void inicio();
	void login();
	void logout();
	void menu();
	void mudarmodo();
	void ordenar();
	void registrar();
	void textcolor(DOS_COLORS iColor);
	//FUNCOES COM RETORNO INTEIRO
	int  contaregistros();
	int  primarykey(int);
	int  repetir();
	int  SETA(int );

//FUNCAO PRINCIPAL 
main(void){
	/*ABRIMOS AQUI PARA NAO SE OBTER 
	ERROS DO TIPO :" ARQUIVO NAO CRIADO"*/
	FILE *p=fopen("ALUNO","ab");
	fclose(p);
	p=fopen("REGISTRO","ab");
	fclose(p);
	//MODIFICA O TAMANHO DA TELA
	system("mode  100,50");
	//MODIFICA TITULO
	system("title SISTEMA DE SALA-0");
	//INICIA COM UMA TELA GRAFICA
	inicio();
	//REDIRECIONA AO MENU
	menu();
	//LIMPA TELA AO TERMINAR
	system("cls");
}

//PROCURA DETERMINADO ALUNO A PARTIR DA MATRICULA
void acharmatricula(){
	pessoa Aluno;
	FILE *A;
	unsigned long long int z;
	int y=1;
	if(modo==0){
    	A=fopen("ALUNO","rb");
	}else
		A=fopen("REGISTRO","rb");
    if(A==NULL){
        printf("ERRO");
        system("pause");
        exit(1);
    }
    do{
		system("cls");
		textcolor(LIGHT_CYAN);
	    bordas();
	    gotoxy(42,5);
	    printf("BUSCA DE ALUNO.\n\n");
	    for(int x=3;x<99;x++){
	    	gotoxy(x,6);
	    	printf("\xcd");
		}
		gotoxy(2,6);
		printf("\xcc");
		gotoxy(99,6);
		printf("\xb9");
	    gotoxy(35,12);
	    printf("Digite a matricula do aluno: ");
	    fflush(stdin);
	    scanf("%lld",&z);
	
	    rewind(A);
	    while(fread(&Aluno,sizeof(pessoa),1,A)==1){
	        if(Aluno.matricula==z){
	        		textcolor(WHITE);
	                gotoxy(35,17);
	                printf("NOME   : %s\n",Aluno.nome);
	                gotoxy(35,19);
	                printf("MATRICULA   : %llu\n",Aluno.matricula);
	                gotoxy(35,21);
	                printf("CURSO    : %s\n",Aluno.curso);
	                gotoxy(35,23);
	                printf("FALTAS    : %d",Aluno.faltas);
	                gotoxy(35,25);
	                printf("MEDIA    :  %.2f\n",Aluno.notas[4]);
	                gotoxy(35,30);
	                fclose(A);
	                break;
	        }
	    }
		textcolor(LIGHT_CYAN);
	    gotoxy(30,35);
		system("pause");
	    system("cls");
	    y=repetir();
	    system("cls");
		}while(y);
    fclose(A);
}

//FUNCAO PARA ALTERAR AS NOTAS
void alterar(){
	int entrou = 0,tam=1;
	int seta=20,seta2=30,mov;
	unsigned long long int mat;
	
	system("cls");
	gotoxy(27,5);
	textcolor(LIGHT_GREEN);
	printf("DIGITE A MATRICULA DO ALUNO A MODIFICAR: ");
	textcolor(WHITE);
	gotoxy(27,6);
	scanf("%llu", &mat);
	pessoa aluno[1];
	FILE *p;
	if(modo==0){
		p = fopen("ALUNO","rb");
	}else{
		p = fopen("REGISTRO","rb");
	}
	if(p == NULL){
		printf("Erro ao abrir arquivo!");
		exit(1);
	}
	rewind(p);
	while(fread(aluno, sizeof(pessoa), 1, p) == 1){
		if(aluno->matricula == mat){
			entrou = 1;
			textcolor(LIGHT_CYAN);
			printf("nome      : %s", aluno->nome);
			printf("matricula : %llu\n", aluno->matricula);
			printf("curso     : %s",aluno->curso);
			printf("faltas    : %d\n",aluno->faltas);
			printf("media     : %.2f\n",aluno->notas[4]);
			printf("parciais  : %.2f  %.2f  %.2f  %.2f\n",aluno->notas[0],aluno->notas[1],aluno->notas[2],aluno->notas[3]);
			break;
		}
	}
	
	fclose(p); 
	if(entrou == 1){
		textcolor(LIGHT_GREEN);
		printf("\n\nREDIGITE AS INFORMACOES PARA ALTERACAO: \n\n");
		textcolor(WHITE);
		
		printf("NOME :");
		fflush(stdin);
		fgets(aluno->nome,101,stdin);
		
		printf("MATRICULA:");
		fflush(stdin);
		scanf("%llu",&aluno->matricula);
		
		printf("CURSO:");
		fflush(stdin);
		fgets(aluno->curso,13,stdin);
		
		printf("FALTAS:");
		fflush(stdin);
		scanf("%d", &aluno->faltas);
		
		printf("PARCIAIS: ");
		fflush(stdin);
		scanf("%f %f %f %f",&aluno->notas[0],&aluno->notas[1],&aluno->notas[2],&aluno->notas[3]);
		aluno->notas[4]=(aluno->notas[0]+aluno->notas[1]+aluno->notas[2]+aluno->notas[3])/4;
		system("cls");
		do{
			gotoxy(23,seta2);
			printf("   ");
			seta2=seta;
			gotoxy(23,seta);
			printf("--\x10");
			
			gotoxy(27,15);
			textcolor(LIGHT_CYAN);
			printf("DESEJA REALMENTE FAZER ESTAS ALTERACOES?");
			gotoxy(27,20);
			textcolor(LIGHT_GREEN);
			printf("SIM");
			gotoxy(27,25);
			textcolor(LIGHT_RED);
			printf("NAO");
			
			switch(mov=getch()){
				case 72:
					if(seta>20){
						seta-=5;
					}
				break;
				case 80:
					if(seta<25){
						seta+=5;
					}
				break;
			}
		}while(mov!=13);
		if(seta==25){
			return;
		}
		FILE *pAux;
		if(modo==0){
			p = fopen("ALUNO","rb");
		}else{
			p = fopen("REGISTRO","rb");
		}
		pAux = fopen("ALUNOAUX", "wb");

		pessoa alunoAux[1];

		if(p == NULL || pAux == NULL){
			printf("Erro ao abrir arquivo!");
			exit(1);
		}
		
		rewind(p);
		rewind(pAux);
		while(fread(alunoAux, sizeof(pessoa), 1, p) == 1){
			if(alunoAux->matricula == mat){
				fwrite(aluno, sizeof(pessoa), 1, pAux);
			}else{
				fwrite(alunoAux, sizeof(pessoa), 1, pAux);
			}
			tam++;
		}
		
		fclose(p);
		fclose(pAux);
		if(modo==0){
			p = fopen("ALUNO","wb");
		}else{
			p = fopen("REGISTRO","wb");
		}
		pAux=fopen("ALUNOAUX","rb");
		rewind(p);
		rewind(pAux);
		for(int x=1;x<tam;x++){
			fread(&alunoAux,sizeof(pessoa),1,pAux);
			fwrite(&alunoAux,sizeof(pessoa),1,p);
		}
		fclose(p);
		fclose(pAux);
	}
	system("pause");
}

//BORDAS DA TELA ESTILO 1
void bordas(){
	//cantinhos
	gotoxy(2,1);
	printf("\xc9");
	gotoxy(99,1);
	printf("\xbb");
	gotoxy(2,49);
	printf("\xc8");
	gotoxy(99,49);
	printf("\xbc");
	//linhas
	for(int x=2;x<49;x++){
		gotoxy(2,x);
		printf("\xba");
		gotoxy(99,x);
		printf("\xba");
	}
	//colunas
	for(int x=3;x<99;x++){
		gotoxy(x,1);
		printf("\xcd");
		gotoxy(x,49);
		printf("\xcd");
	}
}

//BORDAS DA TELA ESTILO 2
void bordas2(){
	//cima
	for(int x=3,y=3;x<=98;x++,y++){
		gotoxy(x,1);
		if(y%2==0){
			printf("\x10");
		}else
			printf("\x11");
		Sleep(5);
	}
	//direita
	for(int x=2,y=3;x<=49;x++,y++){
		gotoxy(99,x);
		if(y%2==0){
			printf("\x1f");
		}else
			printf("\x1e");
		Sleep(5);
	}
	//baixo
	for(int x=98,y=3;x>2;x--,y++){
		gotoxy(x,50);
		if(y%2==0){	
			printf("\x11");
		}else
			printf("\x10");
		Sleep(5);
	}
	//esquerda
	for(int x=49,y=3; x>1;x--,y++){
		gotoxy(2,x);
		if(y%2==0){
			printf("\x1e");
		}else
			printf("\x1f");
		Sleep(5);
	}
}

//FAZER CHAMADA DA TURMA
void chamada(){
	system("cls");
	FILE *p;
	if(modo==0){
		p=fopen("ALUNO","rb");
	}else{
		p=fopen("REGISTRO","rb");
	}
	if(p==NULL){
		printf("erro ao abrir arquivo!");
		exit(1);
	}
	
	textcolor(LIGHT_CYAN);
	bordas();
	
	pessoa *aluno;
	aluno=(pessoa*)calloc(contaregistros(),sizeof(pessoa));
	int seta=20,seta2=50,mov,tam=0;
	rewind(p);
	while((fread(&aluno[tam],sizeof(pessoa),1,p)==1)){
		do{
			gotoxy(27,15);
			textcolor(LIGHT_CYAN);
			printf("%s",aluno[tam].nome);
			gotoxy(27,16);
			printf("%llu",aluno[tam].matricula);
			
			gotoxy(27,20);
			textcolor(LIGHT_GREEN);
			printf("PRESENTE");
			gotoxy(27,25);
			textcolor(LIGHT_RED);
			printf("AUSENTE");
			
			gotoxy(23,seta2);
			printf("   ");
			seta2=seta;
			gotoxy(23,seta);
			textcolor(LIGHT_CYAN);
			printf("--\x10");
			
			switch(mov=getch()){
				case 80:
					if(seta<25){
						seta+=5;
					}else{
						seta-=5;
					}
				break;
				case 72:
					if(seta>20){
						seta-=5;
					}else{
						seta+=5;
					}
				break;	
				case 13:
				if(seta==25){
					aluno[tam].faltas+=1;
				}
			}
		}while(mov!=13);
		tam++;
	}
	
	fclose(p);
	if(modo==0){
		p=fopen("ALUNO","wb");
	}else{
		p=fopen("REGISTRO","wb");
	}
	if(p==NULL){
		printf("erro ao abrir arquivo!");
		exit(1);
	}
	rewind(p);
	for(int x=0;x<tam;x++){
		fwrite(&aluno[x],sizeof(pessoa),1,p);
	}
	fclose(p);
	free(aluno);
}

//CONTA NUMERO DE REGISTROS DO ARQUIVO
int contaregistros(){
	FILE * p;
	if(modo==0){
		p=fopen("ALUNO","rb");
	}else{
		p=fopen("REGISTRO","rb");
	}
	int cont=0;
	pessoa aux;
	while(fread(&aux,sizeof(pessoa),1,p)==1){
		cont ++;
	}
	
	fclose(p);
	return cont;
}

//DESTACA PALAVRA AO LADO DA SETA
void destacar(int x){
	textcolor(LIGHT_CYAN);
	
	if(x==14){
		gotoxy(38,14);
		printf("CADASTRAR ALUNO");
		textcolor(WHITE);
		gotoxy(38,18);
		printf("REMOVER CADASTRO");
		gotoxy(38,46);
		printf("FINALIZAR");
	}else
	if(x==18){
		gotoxy(38,18);
		printf("REMOVER CADASTRO");
		textcolor(WHITE);
		gotoxy(38,14);
		printf("CADASTRAR ALUNO");
		gotoxy(38,22);
		printf("LISTAR CADASTROS");
	}else
	if(x==22){
		gotoxy(38,22);
		printf("LISTAR CADASTROS");
		textcolor(WHITE);
		gotoxy(38,18);
		printf("REMOVER CADASTRO");
		gotoxy(38,26);
		printf("ALTERAR CADASTRO");
	}else
	if(x==26){
		gotoxy(38,26);
		printf("ALTERAR CADASTRO");
		textcolor(WHITE);
		gotoxy(38,22);
		printf("LISTAR CADASTROS");
		gotoxy(38,30);
		printf("BUSCAR CADASTRO");
	}else
	if(x==30){
		gotoxy(38,30);
		printf("BUSCAR CADASTRO");
		textcolor(WHITE);
		gotoxy(38,26);
		printf("ALTERAR CADASTRO");
		gotoxy(38,34);
		printf("FAZER CHAMADA");
	}else
	if(x==34){
		gotoxy(38,34);
		printf("FAZER CHAMADA");
		textcolor(WHITE);
		gotoxy(38,30);
		printf("BUSCAR CADASTRO");
		gotoxy(38,38);
		printf("ARQUIVAR CADASTROS");
	}else
	if(x==38){
		gotoxy(38,38);
		printf("ARQUIVAR CADASTROS");
		textcolor(WHITE);
		gotoxy(38,34);
		printf("FAZER CHAMADA");
		gotoxy(38,42);
		printf("MUDAR MODO DO SISTEMA(REGISTRO-ALUNO)");	
	}else
	if(x==42){
		gotoxy(38,42);
		printf("MUDAR MODO DO SISTEMA(REGISTRO-ALUNO)");
		textcolor(WHITE);
		gotoxy(38,38);
		printf("ARQUIVAR CADASTROS");
		gotoxy(38,46);
		printf("FINALIZAR ");
	}else
	{
		gotoxy(38,46);
		printf("FINALIZAR ");
		textcolor(WHITE);
		gotoxy(38,42);
		printf("MUDAR MODO DO SISTEMA(REGISTRO-ALUNO)");
		gotoxy(38,14);
		printf("CADASTRAR ALUNO");
	}
}

//FUNCAO DE RETIRADA DE ALUNO SISTEMA
void excluir(){
	system("cls");
	FILE *A;
	if(modo==0){
    	A=fopen("ALUNO","rb");
    }else{
    	A=fopen("REGISTRO","rb");
	}
    if(A==NULL){
        printf("ERRO NA ABERTURA DO ARQUIVO!\n");
        system("pause");
        exit(1);
    }
    
    unsigned long long int z;
    int x,a,i=0;
    pessoa *aux;
	pessoa ler;
    
    
	a=sizeof(A)/sizeof(pessoa);
	
	bordas();
	
	textcolor(LIGHT_CYAN);
    gotoxy(25,15);
    printf("MATRICULA A EXCLUIR :");
    textcolor(LIGHT_GREEN);
	fflush(stdin);
    rewind(stdin);
    gotoxy(25,16);
    scanf("%lld",&z);

    aux=(pessoa*)calloc(a,sizeof(pessoa));
          
    rewind(A);
    while(fread(&ler,sizeof(pessoa),1,A)==1){
        if(ler.matricula!=z){
            
			a=strlen(ler.nome);
            for(x=0;x<a;x++){
                aux[i].nome[x]=ler.nome[x];
            }
			
			(aux[i]).matricula=ler.matricula;

            a=strlen(ler.curso);
            for(x=0;x<a;x++){
            	aux[i].curso[x]=ler.curso[x];
            }
            (aux[i]).faltas=ler.faltas;
            i++;
            for(x=0;x<5;x++){
            	(aux[i]).notas[x]=ler.notas[x];
        	}
			i++;
		}
    }

    fclose(A);
    if(modo==0){
    	A=fopen("ALUNO","wb");
	}else{
		A=fopen("REGISTRO","wb");
	}
    	
    rewind(A);
    for(a=1;a<=i;a++){
        fwrite(&aux[a],sizeof(pessoa),1,A);
    }
    fclose(A);
    free(aux);
}

//EXIBE LISTA DE ALUNOS 
void exibir(){
	for(int x=0;x<contaregistros();x++){
		ordenar();
	}
	int z=0,y=1;
	FILE *p;
	pessoa ler;
	system("cls");
	textcolor(LIGHT_CYAN);
	bordas();
	/* Abre para  leitura  */
	if(modo==0){
		p = fopen("ALUNO","rb");
	}else{
		p = fopen("REGISTRO","rb");
	}
	//teste de erro
	if(p==NULL){
		printf("erro");
		system("pause");
		return;
	}		
	//mostra arquivo
	system("cls");
	textcolor(LIGHT_RED);
	for(int x=4;x<=96;x++){
		gotoxy(x,2);
		printf("\xcd");
		gotoxy(x,5);
		printf("\xcd");
	}
	if(modo==0){
		gotoxy(43,3);
		printf("LISTA DE ALUNOS");	
	}else{
		gotoxy(38,3);
		printf("LISTA DE REGISTROS ARQUIVADOS");
	}
	gotoxy(3,2);
	printf("\xc9");
	gotoxy(3,3);
	printf("\xba");
	gotoxy(3,4);
	printf("\xba");
	gotoxy(3,5);
	printf("\xc8");
	
	gotoxy(97,2);
	printf("\xbb");
	gotoxy(97,3);
	printf("\xba");
	gotoxy(97,4);
	printf("\xba");
	gotoxy(97,5);
	printf("\xbc");
	
	textcolor(WHITE);
	gotoxy(45,4);
	printf("parte %d\n\n",y);
	rewind(p);
	while(fread(&ler,sizeof(pessoa),1,p)==1){
		textcolor(RED);
		printf("\t\t\t");
		for(int x=0;x<50;x++){
			printf("\xcd");
		}
		printf("\n");
		
		textcolor(WHITE);
		printf("\t\t\t\t\tNOME      : %s",ler.nome);
		printf("\t\t\t\t\tMATRICULA : %llu\n",ler.matricula);
		printf("\t\t\t\t\tCURSO     : %s",ler.curso);
		printf("\t\t\t\t\tFALTAS    : %d\n",ler.faltas);
		printf("\t\t\t\t\tMEDIA     : %.2f\n\n",ler.notas[4]);
		
		textcolor(RED);
		printf("\t\t\t");
		for(int x=0;x<50;x++){
			printf("\xcd");
		}
		printf("\n");
		
		z++;
		if(z==5){
			gotoxy(2,49);
			system("pause");
			z=0;
			y++;
			system("cls");
			textcolor(LIGHT_RED);
			if(modo==0){
				gotoxy(43,3);
				printf("LISTA DE ALUNOS");	
			}else{
				gotoxy(38,3);
				printf("LISTA DE REGISTROS ARQUIVADOS");
			}
			for(int x=4;x<=96;x++){
				gotoxy(x,5);
				printf("\xcd");
				gotoxy(x,2);
				printf("\xcd");
			}
			gotoxy(3,2);
			printf("\xc9");
			gotoxy(3,3);
			printf("\xba");
			gotoxy(3,4);
			printf("\xba");
			gotoxy(3,5);
			printf("\xc8");
			
			gotoxy(97,2);
			printf("\xbb");
			gotoxy(97,3);
			printf("\xba");
			gotoxy(97,4);
			printf("\xba");
			gotoxy(97,5);
			printf("\xbc");
			textcolor(WHITE);
			gotoxy(45,4);
			printf("parte %d\n\n",y);
		}
	}
	if(z==0){
		gotoxy(39,10);
		printf("SEM ALUNOS CADASTRADOS!");
	}
	gotoxy(2,49);
    system("pause");
    system("cls");
}

//POSICIONAMENTO NA TELA
void gotoxy(int x,int y){
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

//INICIA A EXECUCAO COM UMA TELA GRAFICA
void inicio(){
	//DECLARACAO
	char vet[12]={"  IINF11A  "};
	//draw fase 0
	textcolor(LIGHT_CYAN);
	bordas2();
	//DESENHA COMPUTADOR
	textcolor(WHITE);	
	int w=10,x=14;
	gotoxy(x,w);printf("             _____________________________________________________");w++;Sleep(15);
	gotoxy(x,w);printf("            /                                                     \\");w++;
	gotoxy(x,w);printf("           |    ______________________________________________     |");w++;Sleep(15);
	gotoxy(x,w);printf("           |   |                                              |    |");w++;
	gotoxy(x,w);printf("           |   |  C:\\\\> _                                     |    |");w++;Sleep(15);
	gotoxy(x,w);printf("           |   |                                              |    |");w++;
	gotoxy(x,w);printf("           |   |                                              |    |");w++;Sleep(15);
	gotoxy(x,w);printf("           |   |                                              |    |");w++;
	gotoxy(x,w);printf("           |   |                                              |    |");w++;Sleep(15);
	gotoxy(x,w);printf("           |   |                                              |    |");w++;
	gotoxy(x,w);printf("           |   |                                              |    |");w++;Sleep(15);
	gotoxy(x,w);printf("           |   |                                              |    |");w++;
	gotoxy(x,w);printf("           |   |                                              |    |");w++;Sleep(15);
	gotoxy(x,w);printf("           |   |                                              |    |");w++;
	gotoxy(x,w);printf("           |   |                                              |    |");w++;Sleep(15);
	gotoxy(x,w);printf("           |   |                                              |    |");w++;
	gotoxy(x,w);printf("           |   |______________________________________________|    |");w++;Sleep(15);
	gotoxy(x,w);printf("           |                                                       |");w++;
	gotoxy(x,w);printf("            \\______________________________________________________/");w++;Sleep(15);
	gotoxy(x,w);printf("                   \\________________________________________/");w++;
	gotoxy(x,w);printf("                ________________________________________________");w++;Sleep(15);
	gotoxy(x,w);printf("             _-'    .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.  -- `-_");w++;
	gotoxy(x,w);printf("          _-'.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.  .-.-.`-_");w++;Sleep(15);
	gotoxy(x,w);printf("       _-'.-.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-`_.-`. .-.-.-.`-_");w++;
	gotoxy(x,w);printf("    _-'.-.-.-.-. .-----.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.---.--. .-.-.-.-.`-_");w++;Sleep(15);
	gotoxy(x,w);printf(" _-'.-.-.-.-.-. .---.-. .----------------------------.-.--.-.---. .---.-.-.-.`-_");w++;
	gotoxy(x,w);printf(":------------------------------------------------------------------------------:");w++;Sleep(15);
	gotoxy(x,w);printf("`---._.------------------------------------------------------------------._.---'");
	textcolor(LIGHT_CYAN);
	gotoxy(42,18);
	//MOSTRA O NOME DA TURMA
	for(int x=0;x<11;x++){
		printf("%c",vet[x]);
		Sleep(50);
	}
	//VISUAL DE VELOCIDADE
	for(int x=0;x<3;x++){
		printf("\xaf ");
		Sleep(200);
	}
	Sleep(500);
	gotoxy(31,18);
	system("PAUSE");
}

//CADASTRA ALUNO NO SISTEMA
void login(){
	FILE *A;
	int m,resp=1;
	pessoa aluno;

	do{
		system("cls");
		textcolor(LIGHT_CYAN);
		bordas();
		gotoxy(30,5);
		printf("CADASTRO DE ALUNO \x1");
		//NOME
		gotoxy(5,6);
		printf("NOME:");
		gotoxy(5,7);
		fflush(stdin);
		rewind(stdin);
		textcolor(LIGHT_GREEN);
		fgets(aluno.nome,100,stdin);
		//MATRICULA
		while(m!=2){
			textcolor(LIGHT_CYAN);
			gotoxy(5,8);
			printf("MATRICULA:");
			gotoxy(5,9);
			textcolor(LIGHT_GREEN);
			fflush(stdin);
			rewind(stdin);
			//USA PARAMETROS DO SCANF PARA 	NAO LER LETRAS 	
			scanf("%llu[^a-z ^A-Z ^ -`]",&aluno.matricula);
			
			m=primarykey(aluno.matricula);
			if(m==1){
				textcolor(LIGHT_RED);
				gotoxy(5,9);
				printf("MATRICULA INVALIDA!REESCREVA POR FAVOR");
				Sleep(1500);
				textcolor(LIGHT_CYAN);
				printf("\r \xba                                              \r");
				gotoxy(1,8);
			}
		}
		m=3;
		//CURSO
		textcolor(LIGHT_CYAN);
		gotoxy(5,10);
		printf("CURSO:");
		gotoxy(5,11);
		fflush(stdin);
		rewind(stdin);
		textcolor(LIGHT_GREEN);
		fgets(aluno.curso,13,stdin);
		
		//FALTAS
		aluno.faltas=0;
		//NOTAS
		for(int x=0;x<5;x++){
			aluno.notas[x]=0;
		}
		aluno.notas[5]=contaregistros();
		textcolor(LIGHT_CYAN);
       	bordas();
		int seta=20,mov,seta2=50,v;
		system("cls");
	    do{
       		bordas();
       		gotoxy(27,seta2);
       		printf("   ");
       		seta2=seta;
			gotoxy(30,15);
       		printf("VOCE DESEJA REALMENTE FAZER ESTE CADASTRO?");
       		gotoxy(32,20);
       		textcolor(LIGHT_GREEN);
     		printf("SIM");
       		gotoxy(32,25);
       		textcolor(LIGHT_RED);
       		printf("NAO");
       		textcolor(LIGHT_CYAN);
    	    gotoxy(27,seta);
		    printf("--\x10");
		    
       		//operacao do usuario
      		switch(mov=getch()){
				//cima
				case 72:
				if(seta>20){
					seta-=5;
				} 
				break;
				//baixo
				case 80:
				if(seta<25){
					seta+=5;
				}
				break;
				//enter
				case 13:
					switch(seta){
						case 25:
							v=mov+1;
						break;
						case 20:
							v=mov;
						break;
					}
			}
		}while(mov!=13);

		if(v==13){
			if(modo==0){
				A=fopen("ALUNO","ab");
			}else{
				A=fopen("REGISTRO","ab");
			}
			if(A==NULL){
				printf("erro");
				system("pause");
				exit(1);
			}
        	fwrite(&aluno,sizeof(pessoa),1,A);
        
			fclose(A);
        }
        system("cls");
        textcolor(LIGHT_CYAN);
        bordas();
		resp=repetir();
	}while(resp);
}

//RETIRA TODOS OS ALUNOS OU REDIRECIONA A EXCLUSAO UNICA
void logout(){
	int seta=20,seta2=50,mov,set2=26,set=50,aux=1;
	system("cls");
	do{
	//MENU DE LOGOUT
	gotoxy(27,seta2);
	printf("   ");
	seta2=seta;
	textcolor(LIGHT_BLUE);
	bordas();
	textcolor(LIGHT_CYAN);
	gotoxy(30,16);
	printf("EXCLUSAO DE CADASTROS");
	gotoxy(32,20);
	if(seta==20){
		textcolor(LIGHT_CYAN);
	}else{
		textcolor(WHITE);
	}
	printf("APAGAR SOMENTE UM REGISTRO?");
	gotoxy(32,25);
	
	if(seta==25){
		textcolor(LIGHT_CYAN);
	}else{
		textcolor(WHITE);
	}
	printf("APAGAR TODOS OS REGISTROS?");
	gotoxy(32,30);
	
	if(seta==30){
		textcolor(LIGHT_CYAN);
	}else{
		textcolor(WHITE);
	}
	printf("VOLTAR AO MENU");
	textcolor(LIGHT_CYAN);
	gotoxy(27,seta);
	printf("--\x10");
	//move
	switch(mov=getch()){
		case 72:
			if(seta>20){
				seta-=5;
			}else
			seta=30;
		break;
		case 80:
			if(seta<30){
				seta+=5;
			}else
			seta=20;
		break;
		case 13:
			switch(seta){
				case 20:
					excluir();
					system("cls");
				break;
				case 25:
					system("cls");
					textcolor(LIGHT_CYAN);
					bordas();
					do{
						gotoxy(27,set);
						printf("   ");
						set=set2;
						textcolor(LIGHT_CYAN);
						gotoxy(27,set2);
						printf("--\x10");
						gotoxy(23,24);
						printf("TEM CERTEZA?");
						gotoxy(30,26);
						textcolor(LIGHT_GREEN);
						printf("SIM");
						gotoxy(30,27);
						textcolor(LIGHT_RED);
						printf("NAO");
						switch(mov=getch()){
							case 72:
								if(set2==27){
									set2--;
								}
							break;
							case 80:
								if(set2==26){
									set2++;
								}
							break;
							case 13:
							if(set2==27){
								aux=0;
							}	
							break;
						}
					}while(mov!=13);
					if(aux==1){
						gotoxy(20,25);
						textcolor(LIGHT_RED);
						printf("AGUARDE UM INSTANTE...");
						FILE *p;
						if(modo==0){
							p=fopen("ALUNO","wb");
						}else{
							p=fopen("REGISTRO","wb");
						}
						fclose(p);
						aux=1;
					}
					system("cls");
			 break;
				case 30:
					return;
			}
		}
	}while(1);
}

//FUNCAO MENU DO SISTEMA
void menu(){
	int seta,x=1;
	do{
		seta=14;	
		system("cls");
		textcolor(LIGHT_BLUE);
		bordas();
		gotoxy(2,11);
		printf("\xcc");
		gotoxy(99,11);
		printf("\xb9");
		for(int y=3;y<99;y++){
			gotoxy(y,11);
			printf("\xcd");
		}
		//DESENHA MENU
			gotoxy(40,8);
			printf("MENU DA SALA");
			textcolor(LIGHT_CYAN);
			gotoxy(38,14);
			printf("CADASTRAR ALUNO");
			textcolor(WHITE);
			gotoxy(38,18);
			printf("REMOVER CADASTRO");
			gotoxy(38,22);
			printf("LISTAR CADASTROS");
			gotoxy(38,26);
			printf("ALTERAR CADASTRO ");
			gotoxy(38,30);
			printf("BUSCAR CADASTRO");
			gotoxy(38,34);
			printf("FAZER CHAMADA ");
			gotoxy(38,38);
			printf("ARQUIVAR CADASTROS");
			gotoxy(38,42);
			printf("MUDAR MODO DO SISTEMA(REGISTRO-ALUNO)");
			gotoxy(38,46);
			printf("FINALIZAR ");
			textcolor(LIGHT_CYAN);	
			gotoxy(33,seta);
			printf("--\x10");
			
		//MOVIMENTO DA SETA
			//CHAMA FUNCAO SETA 
			/*
				issso moverá uma seta virtual
				em vez de apagar e desenhar a tela
				toda iteração do do...while
				o que ocasionaria num incomodo piscar da tela
			*/
			seta+=SETA(seta);
			//REDIRECIONA A OPÇÃO ESCOLHIDA
			switch(seta){
				case 14:
				login();
				break;
				case 18:
				logout();
				break;
				case 22:
				exibir();
				break;
				case 26:
				alterar();
				break;
				case 30:
				acharmatricula();
				break;
				case 34:
				chamada();
				break;
				case 38:
				registrar();
				break;
				case 42:
				mudarmodo();
				break;
				case 46:
				x=0;
			}
	}while(x);
}

//MUDA O VALOR DA VARIAVEL MODO
void mudarmodo(){
	int seta=20,seta2=50,mov;
	system("cls");
	textcolor(LIGHT_CYAN);
	bordas();
	do{
		gotoxy(23,seta2);
		printf("   ");
		seta2=seta;
		gotoxy(23,seta);
		textcolor(LIGHT_CYAN);
		printf("--\x10");
		
		gotoxy(27,13);
		printf("ESTA FUNCAO ALTERA O ARQUIVO QUE VOCE ESTA TRABALHANDO!");
		gotoxy(27,15);
		printf("TEM CERTEZA QUE DESEJA USA-LA?");
		
		gotoxy(27,20);
		textcolor(LIGHT_GREEN);
		printf("SIM");
		
		gotoxy(27,25);
		textcolor(LIGHT_RED);
		printf("NAO");
		
		switch(mov=getch()){
			case 72:
				if(seta>20){
					seta-=5;
				}
			break;
			case 80:
				if(seta<25){
					seta+=5;
				}
			break;
			case 13:
			if(seta==25){
				return;
			}
		}
	}while(mov!=13);
	
	if(modo==0){
		modo=1;
	}else{
		modo=0;
	}
	
	bordas();
	textcolor(LIGHT_CYAN);
}

//ORDENA LISTA DE ALUNOS POR ORDEM ALFABETICA
void ordenar(){
	FILE *p;
	if(modo==0){
		p=fopen("ALUNO","rb");
	}else{
		p=fopen("REGISTRO","rb");
	}
	
	if(p==NULL){
		printf("erro na abertura de arquivo");
		exit(1);
	}
	
	int tam=contaregistros();
	
	pessoa *aluno,aluno2;
	aluno=(pessoa*)calloc(tam,sizeof(pessoa));
	
	for(int x=0;x<tam;x++){
		fread(&aluno[x],sizeof(pessoa),1,p);
	}
	
	for(int x=0;x<tam;x++){
		for(int y=x+1;y<tam;y++){
			if(strcmp(aluno[x].nome,aluno[y].nome)>0){
				aluno2.notas[5]   = aluno[x].notas[5];
				aluno[x].notas[5] = aluno[y].notas[5];
				aluno[y].notas[5] = aluno2.notas[5];
			}
		}
	}
	
	fclose(p);
	if(modo==0){
		p=fopen("ALUNO","wb");
	}else{
		p=fopen("REGISTRO","wb");
	}
	
	for(int x=0;x<tam;x++){
		for(int y=0;y<tam;y++){
			if(aluno[y].notas[5]==x){
				fwrite(&aluno[y],sizeof(pessoa),1,p);
			}
		}
	}
	fclose(p);
	free(aluno);	
}

//TESTA SE A MATRICULA JA ESTA CADASTRADA
int primarykey(int x){
	pessoa aux;
	FILE *A;
	if(modo==0){
    	A=fopen("ALUNO","rb");
    }else{
    	A=fopen("REGISTRO","rb");
	}
    if(A==NULL){
        printf("ERRO");
        system("pause");
        exit(1);
    }
    
    rewind(A);
    while(fread(&aux,sizeof(pessoa),1,A)==1){
        if(aux.matricula==x){
        	return 1;
        }
    }
    return 2;
}

/*FUNCAO REGISTRAR:

ELA TEM COMO OBJETIVO GUARDAR OS DADOS DOS
ALUNOS NO FINAL DO BIMESTRE E DEPOIS LIMPAR OS 
DADOS DOS ALUNOS PARA O PROXIMO BIMESTRE 
*/

void registrar(){
	system("cls");
	textcolor(LIGHT_CYAN);
	bordas();
	int y,seta=20,seta2=50,mov,tam=1;
	do{
		gotoxy(22,seta2);
		printf("   ");
		seta2=seta;
		textcolor(LIGHT_CYAN);
		gotoxy(22,seta);
		printf("--\x10");
		gotoxy(25,15);
		printf("TEM CERTEZA QUE DESEJA USAR A FUNCAO REGISTRAR?");
		gotoxy(27,20);
		textcolor(LIGHT_GREEN);
		printf("SIM");
		gotoxy(27,25);
		textcolor(LIGHT_RED);
		printf("NAO");
		
		switch(mov=getch()){
			case 72:
				if(seta>20){
					seta-=5;
				}
			break;
			case 80:
				if(seta<25){
					seta+=5;
				}
			break;
			case 13:
				if(seta==25){
					return;
				}
		}
	}while(mov!=13);
	
	FILE *p=fopen("ALUNO","rb");
	FILE *pAux=fopen("REGISTRO","ab");
	if(p==NULL || pAux==NULL ){
		printf("ERRO NA ABERTURA DO ARQUIVO");
		exit(1);
	}
	
	pessoa aluno;
	while(fread(&aluno,sizeof(pessoa),1,p)==1){
		fwrite(&aluno,sizeof(pessoa),1,pAux);
		tam++;
	}
	
	fclose(p);
	p=fopen("ALUNO","wb");
	/*rewind(p);
	rewind(pAux);
	for(int x=1;x<tam;x++){
		fread(&aluno,sizeof(pessoa),1,pAux);
		aluno.faltas=0;
		for(int y=0;y<5;y++){
			aluno.notas[y]=0;
		}
		fwrite(&aluno,sizeof(pessoa),1,pAux);
	}*/
	fclose(p);
	fclose(pAux);
	
	system("cls");
	gotoxy(27,20);
	textcolor(LIGHT_CYAN);
	printf("SEUS DADOS FORAM SALVOS NO ARQUIVO REGISTRO");
	system("pause");
}

//FUNCAO QUE PERGUNTA AO USUARIO SE DESEJA REPETIR A OPERACAO
int repetir(){
	system("cls");
	int seta=20,mov,seta2=50;
	bordas();
	//REPETIR OPERACAO?
	    do{
       		//menu de repeticao
       	
       		textcolor(LIGHT_CYAN);
       		gotoxy(27,seta2);
       		printf("   ");
       		seta2=seta;
			gotoxy(30,15);
       		printf("DESEJA REPETIR A OPERACAO?");
       		gotoxy(32,20);
       		textcolor(LIGHT_GREEN);
     		printf("SIM");
       		gotoxy(32,25);
       		textcolor(LIGHT_RED);
       		printf("NAO");
       		textcolor(LIGHT_CYAN);
    	    gotoxy(27,seta);
		    printf("--\x10");
		    
       		//operacao do usuario
      		switch(mov=getch()){
				//cima
				case 72:
				if(seta>20){
					seta-=5;
				} 
				break;
				//baixo
				case 80:
				if(seta<25){
					seta+=5;
				}
				break;
				//enter
				case 13:
					switch(seta){
						case 25:
							return 0;
						case 20:
							return 1;
					}
			}
		}while(mov!=13);
}

//MOVIMENTO DA SETA
int SETA(int set){
	int cont=0,mov,setadotempo=50;
	do{
		textcolor(LIGHT_GRAY);
		//DESENHO
		gotoxy(33,setadotempo);
		printf("    ");
		setadotempo=set;
		//mostra as horas e data
		gotoxy(5,45);
		system("time/t");
		gotoxy(5,46);
		system("date/t");
		textcolor(LIGHT_CYAN);
		gotoxy(33,set);
		printf("--\x10");
		//MOVIMENTO
		switch(mov=getch()){
			case 80:
			if(set<46){
				set+=4;
				cont+=4;
			}else{
			set-=32;
			cont-=32;
			}
			
			break;
			case 72:
			if(set>14){
				set-=4;
				cont-=4;
			}else
			{
			set+=32;
			cont+=32;
			}
			break;
		}
		destacar(set);
	}while(mov!=13);
	return cont;
}

//MUDA A COR CORRENTE DE ESCRITA DA TELA
void textcolor (DOS_COLORS iColor){
    HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
    bufferInfo.wAttributes &= 0x00F0;
    SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= iColor);
}


