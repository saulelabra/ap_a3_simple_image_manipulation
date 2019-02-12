//Saúl Enrique Labra Cruz A01020725
//Simple Image Manipulation

#ifndef PPM_H
#define PPM_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "unistd.h"

typedef struct RGB{
    unsigned char rgb[3];
}RGB;

typedef struct ppm{
    int graysOrColor, binOrAscii, numRows, numCols, numLevels;
    char magicNum[2];
    RGB ** imgArr;
}ppm;

void copySpecs(ppm *img1, ppm *img2);

void allocateMem(ppm * img);

void asciiRead (ppm * img, FILE * source);

void binaryRead(ppm * img, FILE * source);//por componer

void readImg(char * imgFilePath, ppm * outImg);

void writeAscii(ppm * img, char * path, FILE * file);

void writeBinary(ppm * img, char * path, FILE * file);//Por hacer

void writeImg(ppm * inImg, char * path);

void invertColors(ppm * inImg, ppm  * outImg);

void scaleImg(ppm * inImg, ppm * outImg, int scalePer);//error de memoria

void freeppm(ppm * img);

#endif