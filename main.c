#include <stdio.h>
#include <stdlib.h>

float readTemperature(char *filePath){
	FILE *tempFile;
	tempFile = fopen(filePath, "r");
	if(tempFile == NULL)
		return 1;

	double temperature;
	fscanf(tempFile, "%lf", &temperature);
	fclose(tempFile);
	temperature /= 1000;

	return temperature;	
}


int main(){
	double temperature;
       	temperature = readTemperature("./example_files/temp1");
	if(temperature != 1)
		printf("%lf \n", temperature);



}

