#include <stdio.h>

int main(){
	FILE *fp;
	fp = fopen("input.txt", "w");




	char buf;
	buf = '4';
	fwrite(&buf, 1, sizeof(char), fp);
	buf = '\n';
	fwrite(&buf, 1, sizeof(char), fp);
	char buf2[9] = "100000000";
	fwrite(buf2, 1, 9 * sizeof(char), fp);
	buf = '\n';
	fwrite(&buf, 1, sizeof(char), fp);

	for(int i = 0; i < 10000000; i++){
		buf = '0';
		fwrite(&buf, 1, sizeof(char), fp);
		buf = '1';
		fwrite(&buf, 1, sizeof(char), fp);
		buf = '2';
		fwrite(&buf, 1, sizeof(char), fp);
		buf = '3';
		fwrite(&buf, 1, sizeof(char), fp);
		buf = '4';
		fwrite(&buf, 1, sizeof(char), fp);
		buf = '5';
		fwrite(&buf, 1, sizeof(char), fp);
		buf = '6';
		fwrite(&buf, 1, sizeof(char), fp);
		buf = '7';
		fwrite(&buf, 1, sizeof(char), fp);
		buf = '8';
		fwrite(&buf, 1, sizeof(char), fp);
		buf = '9';
		fwrite(&buf, 1, sizeof(char), fp);
	}

	fclose(fp);
	return 0;
}