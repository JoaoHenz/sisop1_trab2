#include "../include/t2fs.h"
#include "../include/apidisk.h"
#include "../include/bitmap2.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int is_initialized = 0;
struct t2fs_bootBlock bootBlock;
int inicio_mft;
int inicio_dados;
int tamanho_mft;
int tamanho_dados;
int tamanho_bloco;


static void init(){
	int flag;

	char *buffer_leitura = malloc(SECTOR_SIZE);
	flag = read_sector(0,(unsigned char *)buffer_leitura);

	if (flag!=0)
		printf("\nErro na leitura!")
	else{
		memcpy(&bootBlock.id, buffer_leitura, sizeof(bootBlock.id));
		memcpy(&bootBlock.version, buffer_leitura+4, sizeof(bootBlock.version));
		memcpy(&bootBlock.blockSize, buffer_leitura+6, sizeof(bootBlock.blockSize));
		memcpy(&bootBlock.MFTBlocksSize, buffer_leitura+8, sizeof(bootBlock.MFTBlocksSize));
		memcpy(&bootBlock.diskSectorSize, buffer_leitura+10, sizeof(bootBlock.diskSectorSize));

		inicio_mft = 0 + 1*blockSize*SECTOR_SIZE;
		inicio_dados = inicio_mft + MFTBlocksSize*blockSize*SECTOR_SIZE;
		tamanho_mft = MFTBlocksSize*blockSize;
		tamanho_bloco = blockSize;
		tamanho_dados = diskSectorSize - tamanho_mft - blockSize;

	}
}
int identify2 (char *name, int size){
	char *name_aux = "NicolasPessutto242284 JoaoHenz242251";
	if (is_initialized == 0){
		init();
		is_initialized = 1;
	}

	strcopy(name,name_aux);

	return 0;
}
FILE2 create2 (char *filename){  
	int blocolivre=0;
	int teste;
	int endbloco = searchBitmap2(blocolivre);
	int i=0; j=0;
	int mft_diretorio_atual = inicio_mft+2; //endereço do setor do diretorio raiz
	char buffer_aux[256]; //pega o nome dos diretórios ou arquivo a ser criado um a um
	char buffer_mft[SECTOR_SIZE *2]; //buffer para se ler um MFT
	int flag=0;
	char tamanho_este_diretorio[4];
	char end_arquivo[4];
	int end_arquivoint;
	int encontrou=0;
	if (is_initialized == 0){
		init();
		is_initialized = 1;
	}

	char *path = malloc(sizeof(filename));
	strcpy(path, filename);

	flag = read_sector(diretorio_atual,(unsigned char *)buffer_mft);
	

	i++;
	while(path[i]!='\0'){ //se der erro o laço vai dar return ERROR, a execução só sai desse laço se for válido o path
		encontrou = 0;
		if (buffer_arquivo)
			free(buffer_arquivo);
		j=0;
		while(path[i]!='/'||path[i]!='\0'){ //NO BUFFER_AUX ESTÁ O NOME A SER TESTADO
			buffer_aux[j]= path[i];
			i++; j++;
		}
		buffer_aux[j] ='\0';
		if(path[i]=='\0'){ //estamos testando um nome de arquivo || arquivo existe? sim-> retorna erro / não -> cria ele
			memcpy(tamanho_este_diretorio,buffer_mft[12],4);
			memcpy(end_arquivo,buffer_mft[8],4);
			char* buffer_arquivo = malloc(tamanho_bloco*SECTOR_SIZE*(int)tamanho_este_diretorio); //serve para ler os arquivos de diretório
			end_arquivoint = (int)end_arquivo * tamanho_bloco;
			flag = read_sector(buffer_arquivo,(unsigned char *)end_arquivoint);
			
			int cont = malloc(sizeof(int));
			cont=0;
			struct t2fs_record um_record;

			while(cont * sizeof(t2fs_record)<= sizeof(buffer_arquivo) && encontrou ==0 ){ //busca o arquivo no dir_atual
				memcpy(um_record,buffer_arquivo(cont*size_of(t2fs_record)));
				if (strcmp(um_record->name,buffer_aux)==0 && um_record->TypeVal == 0x01){
					pritnf("Arquivo já existe!");
					return ERROR;
				}
				cont++;
			}
			if (encontrou==0){//arquivo ainda nao existe, então será criado
				flag = criaArquivo(buffer_aux,mft_diretorio_atual);
				if (flag == ERROR)
					return ERROR;
				else
					return 0;
			}

		}
		else{ //estamos testando um nome de diretório || diretório existe? sim-> vai pra ele / não-> retorna erro
			memcpy(tamanho_este_diretorio,buffer_mft[12],4);
			memcpy(end_arquivo,buffer_mft[8],4);
			char* buffer_arquivo = malloc(tamanho_bloco*SECTOR_SIZE*(int)tamanho_este_diretorio); //serve para ler os arquivos de diretório
			end_arquivoint = (int)end_arquivo * tamanho_bloco;
			flag = read_sector(buffer_arquivo,(unsigned char *)end_arquivoint);
			
			int cont = malloc(sizeof(int));
			cont=0;
			struct t2fs_record um_record;

			while(cont * sizeof(t2fs_record)<= sizeof(buffer_arquivo) && encontrou ==0 ){ //busca o subdir no dir_atual
				memcpy(um_record,buffer_arquivo(cont*size_of(t2fs_record)));
				if (strcmp(um_record->name,buffer_aux)==0 && um_record->TypeVal == 0x02){
					mft_diretorio_atual = um_record->MFTNumber;
					encontrou = 1;
				}
				cont++;
			}
			if (encontrou==0)//diretório não existe
				printf("\nDiretório inexistente!");
				return ERROR;
		}


	}

}

int delete2 (char *filename){ 
	if (is_initialized == 0){
		init();
		is_initialized = 1;
	}

	while(path[i]!='\0'){ //se der erro o laço vai dar return ERROR, a execução só sai desse laço se for válido o path
		encontrou = 0;
		if (buffer_arquivo)
			free(buffer_arquivo);
		j=0;
		while(path[i]!='/'||path[i]!='\0'){ //NO BUFFER_AUX ESTÁ O NOME A SER TESTADO
			buffer_aux[j]= path[i];
			i++; j++;
		}




	return 0;
}

FILE2 open2 (char *filename){//TODO
	if (is_initialized == 0){
		init();
		is_initialized = 1;
	}

	return ERROR
}


int close2 (FILE2 handle){//TODO
	if (is_initialized == 0){
		init();
		is_initialized = 1;
	}
	return ERROR

}


int read2 (FILE2 handle, char *buffer, int size){//TODO
	if (is_initialized == 0){
		init();
		is_initialized = 1;
	}
	return ERROR
}

int write2 (FILE2 handle, char *buffer, int size){//TODO
	if (is_initialized == 0){
		init();
		is_initialized = 1;
	}
	return ERROR

}

int truncate2 (FILE2 handle){//TODO
	if (is_initialized == 0){
		init();
		is_initialized = 1;
	}
	return ERROR

}

int seek2 (FILE2 handle, DWORD offset){//TODO
	if (is_initialized == 0){
		init();
		is_initialized = 1;
	}

	return ERROR
}

int mkdir2 (char *pathname){//TODO
	if (is_initialized == 0){
		init();
		is_initialized = 1;
	}
	return ERROR

}


int rmdir2 (char *pathname){//TODO
	if (is_initialized == 0){
		init();
		is_initialized = 1;
	}
	return ERROR
}	

DIR2 opendir2 (char *pathname){//TODO
	if (is_initialized == 0){
		init();
		is_initialized = 1;
	}
	return ERROR
}


int readdir2 (DIR2 handle, DIRENT2 *dentry){//TODO
	if (is_initialized == 0){
		init();
		is_initialized = 1;
	}
	return ERROR

}


int closedir2 (DIR2 handle){//TODO
	if (is_initialized == 0){
		init();
		is_initialized = 1;
	}
	return ERROR
}


int criaArquivo(char*nome, int mft_diretorio){
	char tamanho_este_diretorio[4];
	char end_arquivo[4];
	int end_arquivoint;
	int encontrou=0;
	char buffer_mft[SECTOR_SIZE *2]; //buffer para se ler um MFT
	int encontrou = 0;
	int x=0;
	char buffer_escrita[SECTOR_SIZE];

	memcpy(tamanho_este_diretorio,buffer_mft[12],4);
	memcpy(end_arquivo,buffer_mft[8],4);
	char* buffer_arquivo = malloc(tamanho_bloco*SECTOR_SIZE*(int)tamanho_este_diretorio); //serve para ler os arquivos de diretório
	end_arquivoint = (int)end_arquivo * tamanho_bloco;
	flag = read_sector(buffer_arquivo,(unsigned char *)end_arquivoint);
	
	int cont = malloc(sizeof(int));
	cont=0;
	struct t2fs_record um_record;

	while(cont * sizeof(t2fs_record)<= sizeof(buffer_arquivo) && encontrou ==0 ){ //busca o subdir no dir_atual
		memcpy(um_record,buffer_arquivo(cont*size_of(t2fs_record)));
		if (um_record->TypeVal != 0x01 && um_record->TypeVal != 0x02){
			encontrou = 1;
		}
		cont++;
	}
	if (encontrou==0)//diretório não tem espaço para tal operação
		return ERROR;


	//cont indica em qual record está o espaço vago, cada record são 64 bytes (4 records por setor, 16 por bloco)
	um_record->TypeVal = 0x01;
	strcpy(um_record->name,nome);
	um_record->bytesFileSize = 0;
	memcpy(buffer_arquivo[cont*64],um_record,sizeof(t2fs_record)); //atualiza o buffer de arquivo com a nova entrada

	x = (1+cont)/4; //x indica qual setor do diretório deve ser modificado em disco. Buffer arquivo por ter vários blocos


	memcpy(buffer_escrita, buffer_arquivo[x*SECTOR_SIZE], SECTOR_SIZE); //passa para o buffer de escrita a parte necessaria
	flag = write_sector(end_arquivoint,(unsigned char *)buffer_escrita ); //escreve finalmente em disco o setor atualizado


}