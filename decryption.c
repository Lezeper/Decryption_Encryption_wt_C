#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>


struct firstBreak{
	char L;
	char R;
};

int main(int argc, char *argv[]){
	
	if(argc != 4) {
	        fprintf(stderr, "Format: Program Name <e or d> <Source> <Keys file>\n");
	        exit(1);
	}
	// input file
	FILE *fp = fopen(argv[2], "rb");
	// output file
	FILE *outfp = fopen("out.txt", "wb");
	// keys file
	FILE *keys = fopen(argv[3], "rb");
	
	char key1;
	char key2;

	if (fp == NULL) {
		fprintf(stderr, "Can't open %s\n", argv[2]);
		exit(1);
		
	}
	
	if (outfp == NULL){
		fprintf(stderr, "There's a problem with the output file\n");
		exit(1);	
	}
	
	if (keys == NULL){
		fprintf(stderr, "Can't open %s\n", argv[3]);
		exit(1);
	}
	
	fread(&key1, sizeof(key1), 1, keys);
	fread(&key2, sizeof(key2),1, keys);
	fread(&key2, sizeof(key2),1, keys);
	
	int size;
	fseek (fp, 0, SEEK_END);   
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    int i = 0;
	
	struct firstBreak encryption;
	
    while(1){
    	struct firstBreak combined;
		// break the input data into 16 bit chunks
		if (i = fread(&encryption, sizeof(char), 2, fp) == 2){
			// two 8 bit bytes (L and R)
			combined.R = encryption.R ^ key1;
			combined.L = encryption.L ^ key2;
			fwrite(&combined, sizeof(char), 2, outfp);
		}
		// if there is an odd number of bytes
		else if (size % 2 == 1){
			combined.L = encryption.L ^ key1 ^ key2;
			fwrite(&combined, sizeof(char), 1, outfp);
			break;
		}
		else{
			break;
		}
	}

	return 0;

}
