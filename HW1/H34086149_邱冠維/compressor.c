#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

int main(int argc, char** argv){
	char opt;
	FILE* fp;
	char str[10000];
	int arr[100000]; //bool
	char ch;
	char table[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; 
	int p = 0;
	while((opt = getopt(argc,argv,"i:o:")) != -1){
		switch(opt){
			case 'i':
				fp = fopen(optarg,"r");
				while(fgets(str,10000,fp) != NULL){
					int byte = 0;
					for(int i = 0; str[i] != '\0' && str[i] != '\n'; i += 2, ++byte){
						ch = 0;
						if('A' <= str[i] && str[i] <= 'F')
							ch += (str[i] - 'A' + 10) * 16;
						else
							ch += (str[i] - '0') * 16;
						if('A' <= str[i+1] && str[i+1] <= 'F')
							ch += str[i+1] - 'A' + 10;
						else
							ch += str[i+1] - '0';
						for(int j = 0; j < 8; ++j){
							arr[p] = ((ch & (1 << (7 - j))) >> (7 - j));
							++p;
						}
					}
					arr[p++] = -1;
					arr[p++] = byte;
				}
				fclose(fp);
				break;
			case 'o':
				fp = fopen(optarg,"w");
				int endl = 0;
				int byte;
				for(int i = 0; i < p; i += 6){
					int key = 0;
					for(int j = 0; j < 6; ++j){
						if(arr[i+j] == -1){
							endl = 1;
							byte = arr[i+j+1];
							i = i + j + 2 - 6;
							break;
						}
						key += (arr[i+j] << (5-j));
					}
					fprintf(fp, "%c", table[key]);
					if(endl){
						if(byte % 3)
							for(int k = 0; k < 3 - byte % 3; ++k)
								fprintf(fp, "%c", '=');
						fprintf(fp, "%c", '\n');
						byte = 0;
						endl = 0;
					}
				}
				fclose(fp);
				break;
		}
	}
	return 0;
}