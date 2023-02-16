/*
 * detectionFunctions.c
 *
 *  Created on: Feb 14, 2023
 *      Author: kkh19
 */

#include "detectionFunctions.h"
#include <stdio.h>
#include <stdlib.h>

#define ESC 0x1B
#define SIZE_OF_FIELD 8U
#define ZONES_PER_ROW 4U

int8_t threshold;

RANGING_SENSOR_Result_t *plastval, *pval, lastval, val;

void initDetectionFunction(int8_t res){

	threshold = res;

}

void fillDataInStructs(){

	int8_t i;
	plastval = &lastval;
	pval = &val;

	for(i = 0; i < ZONES_PER_ROW*ZONES_PER_ROW; i++){
		lastval.ZoneResult[i].Distance[0] = 1000;
	}
}

void alterData(){

	int8_t i, numberOfChanges = 3, temp;

	printStatement();


	for(i = 0; i < ZONES_PER_ROW*ZONES_PER_ROW; i++){
		val.ZoneResult[i].Distance[0] = 1000;
		lastval.ZoneResult[i].Distance[0] = 1000;
	}
	for(i = 0; i < numberOfChanges; i++){
		temp = rand()%15;
		lastval.ZoneResult[temp].Distance[0] = 500;
	}

	HAL_Delay(2000);

}

void gotoxy(int8_t r, int8_t c){
	printf("%c[%d;%dH",ESC,c,r);
}

void clrscr(){
	printf("%c[2J",ESC);
}

void checkEvent(){

	int8_t i;


	for(i = 0; i < ZONES_PER_ROW*ZONES_PER_ROW; i++){

		if((pval->ZoneResult[i].Distance[0])-(plastval->ZoneResult[i].Distance[0]) > threshold){

			printChange(i);

		}

	}

	//Change this in order to change the data
	HAL_Delay(2000);

}

void printChange(int8_t zone){

	int8_t i;

	if(zone < 4){
		for(i = 0; i < SIZE_OF_FIELD - 1; i++){
			gotoxy(zone*23+1, i);
			printf("OOOOOOOOOOOOOOOOOOOO");
		}

	}else if(zone >= 4 && zone < 8){
		for(i = 0; i < SIZE_OF_FIELD - 1; i++){
			gotoxy((zone%4)*23+1, i + SIZE_OF_FIELD);
			printf("OOOOOOOOOOOOOOOOOOOO");
		}

	}else if(zone >= 8 && zone < 12){
		for(i = 0; i < SIZE_OF_FIELD - 1; i++){
			gotoxy((zone%4)*23+1, i + SIZE_OF_FIELD*2);
			printf("OOOOOOOOOOOOOOOOOOOO");
		}

	}else{
		for(i = 0; i < SIZE_OF_FIELD - 1; i++){
			gotoxy((zone%4)*23+1, i + SIZE_OF_FIELD*3);
			printf("OOOOOOOOOOOOOOOOOOOO");
		}
	}
}

void printStatement(){

	int8_t i, j;

	for(j = 0; j < ZONES_PER_ROW; j++){
		for(i = 0; i < SIZE_OF_FIELD; i++){
			gotoxy(0, j*SIZE_OF_FIELD+i);
			if(i != SIZE_OF_FIELD-1)
				printf("XXXXXXXXXXXXXXXXXXXX   XXXXXXXXXXXXXXXXXXXX   XXXXXXXXXXXXXXXXXXXX   XXXXXXXXXXXXXXXXXXXX");
		}

	}
	fflush(stdout);
}
