#include "../include/t2fs.h"
#include "../include/apidisk.h"
#include "../include/bitmap2.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int identify2 (char *name, int size){
	char *name_aux = "NicolasPessutto242284 JoaoHenz242251";
	strcopy(name,name_aux);

	return 0;
}


FILE2 create2 (char *filename){  // estou bastante confuso 
	int blocolivre=0;
	int teste;
	int endbloco = searchBitmap2(blocolivre);
	

		if(endbloco=<0)
			return -1;
		else{

			teste =write_sector(endbloco, filename);
			if(teste ==0)
				return 0; 
			else
				return -1;

		}
}

int delete2 (char *filename){ //TODO



}

FILE2 open2 (char *filename){//TODO


}


int close2 (FILE2 handle){//TODO


}


int read2 (FILE2 handle, char *buffer, int size){//TODO

}

int write2 (FILE2 handle, char *buffer, int size){//TODO


}

int truncate2 (FILE2 handle){//TODO


}

int seek2 (FILE2 handle, DWORD offset){//TODO


}

int mkdir2 (char *pathname){//TODO


}


int rmdir2 (char *pathname){//TODO

}

DIR2 opendir2 (char *pathname){//TODO

}


int readdir2 (DIR2 handle, DIRENT2 *dentry){//TODO


}


int closedir2 (DIR2 handle){//TODO

}