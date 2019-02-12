//Saúl Enrique Labra Cruz A01020725
//Simple Image Manipulation

#include "ppm.h"

void copySpecs(ppm *img1, ppm *img2) {
    img2->binOrAscii = img1->binOrAscii;
    img2->graysOrColor = img1->graysOrColor;
    strcpy(img2->magicNum, img1->magicNum);
    img2->numCols = img1->numCols;
    img2->numRows = img1->numRows;
    img2->numLevels = img1->numLevels;
}

void allocateMem(ppm * img) {
    img->imgArr = (RGB**) malloc(img->numRows * sizeof(RGB*));

    for(int i=0; i<img->numRows; i++)
    {
        img->imgArr[i] = (RGB*)malloc(img->numCols * sizeof(RGB));
    }
}

void asciiRead (ppm * img, FILE * source) {
    int numTmp;
    for(int i=0; i<img->numRows; i++)
    {
        for(int j=0; j<img->numCols; j++)
        {
            fscanf(source, "%d", &numTmp);
            img->imgArr[i][j].rgb[0] = (char) numTmp;
            fscanf(source, "%d", &numTmp);
            img->imgArr[i][j].rgb[1] = (char) numTmp;
            fscanf(source, "%d", &numTmp);
            img->imgArr[i][j].rgb[2] = (char) numTmp;
        }
    }
}

void binaryRead(ppm * img, FILE * source) {
    //Reading ppm contents
    fread(img->imgArr[0], sizeof(RGB), img->numRows*img->numCols, source);
    printf("stored in memory\n");

    for(int i=0; i<img->numRows; i++)
    {
        for(int j=0; j<img->numCols; j++)
        {
            printf("[%d][%d][0]: %c %x\n", i, j, img->imgArr[i][j].rgb[0], img->imgArr[i][j].rgb[0]);
            printf("[%d][%d][1]: %c %x\n", i, j, img->imgArr[i][j].rgb[1], img->imgArr[i][j].rgb[1]);
            printf("[%d][%d][2]: %c %x\n", i, j, img->imgArr[i][j].rgb[2], img->imgArr[i][j].rgb[2]);
        }
    }
}

void readImg(char * imgFilePath, ppm * outImg)
{
    FILE * ppmFile;
    char tmpString[10];

    //Opening ppm file
    ppmFile=fopen(imgFilePath, "r");

    //Scanning magicNumber, dimensions and numLevels
    fscanf(ppmFile, "%s", tmpString);
    strcpy(outImg->magicNum, tmpString);
    switch (tmpString[1])
    {
        case '6':
            outImg->graysOrColor = 1;
            outImg->binOrAscii = 0;
            break;
        case '3':
            outImg->graysOrColor = 1;
            outImg->binOrAscii = 1;
            break;
        case '5':
            outImg->graysOrColor = 0;
            outImg->binOrAscii = 0;
            break;
        case '2':
            outImg->graysOrColor = 0;
            outImg->binOrAscii = 1;
            break;
    }
    fscanf(ppmFile, "%s", tmpString);
    outImg->numCols = atoi(tmpString);
    fscanf(ppmFile, "%s", tmpString);
    outImg->numRows = atoi(tmpString);
    fscanf(ppmFile, "%s", tmpString);
    outImg->numLevels = atoi(tmpString);

    //Skips the first new line char
    fgetc(ppmFile);

    //Allocating memory
    allocateMem(outImg);

    //Reading array contents
    if(outImg->binOrAscii == 0)
    {
        binaryRead(outImg, ppmFile);
    }else{
        asciiRead(outImg, ppmFile);
    }

    //closing file
    fclose(ppmFile);
}

void writeAscii(ppm * img, char * path, FILE * file)
{
    for(int i=0; i<img->numRows; i++)
    {
        for(int j=0; j<img->numCols; j++)
        {
            fprintf(file, "%d\t", img->imgArr[i][j].rgb[0]);
            fprintf(file, "%d\t", img->imgArr[i][j].rgb[1]);
            fprintf(file, "%d\t", img->imgArr[i][j].rgb[2]);
        }
        fprintf(file, "\n");
    }
}

void writeBinary(ppm * img, char * path, FILE * file) {
    fwrite(img->imgArr[0],  sizeof(RGB), img->numRows*img->numCols, file);
}

void writeImg(ppm * inImg, char * path) {
    FILE * toWrite;

    //creating file
    toWrite = fopen(path, "w");

    //Writing file specifications
    fprintf(toWrite, "%c%c\n", inImg->magicNum[0], inImg->magicNum[1]);
    fprintf(toWrite, "%d %d\n", inImg->numCols, inImg->numRows);
    fprintf(toWrite, "%d\n", inImg->numLevels);

    if(inImg->binOrAscii == 0)
    {
        writeBinary(inImg, path, toWrite);
    }else{
        writeAscii(inImg, path, toWrite);
    }

    //closing file
    fclose(toWrite);
}

void invertColors(ppm * inImg, ppm  * outImg) {
    
    copySpecs(inImg, outImg);    
    allocateMem(outImg);

    for(int i=0; i<inImg->numRows; i++)
    {
        for(int j=0; j<inImg->numCols; j++)
        {
            outImg->imgArr[i][j].rgb[0] = inImg->numLevels - inImg->imgArr[i][j].rgb[0];
            outImg->imgArr[i][j].rgb[1] = inImg->numLevels - inImg->imgArr[i][j].rgb[1];
            outImg->imgArr[i][j].rgb[2] = inImg->numLevels - inImg->imgArr[i][j].rgb[2];
        }
    }
}

void scaleImg(ppm * inImg, ppm * outImg, int scalePer) {

    int numRowsNew, numColsNew;

    if(scalePer >= 100)
    {
        numRowsNew = inImg->numRows*(scalePer/100);
        numColsNew = inImg->numCols*(scalePer/100);
    }else{
        numRowsNew = (int)round(inImg->numRows*scalePer/100);
        numColsNew = (int)round(inImg->numCols*scalePer/100);
    }
    
    printf("numRowsNew: %d\n", numRowsNew);
    printf("numColsNew: %d\n", numColsNew);
        
    //Copying specifications
    copySpecs(inImg, outImg);

    outImg->numCols = numColsNew;
    outImg->numRows = numRowsNew;
    //Allocating memory
    allocateMem(outImg);

    //Fill new imgArray
    for(int i=0; i<outImg->numRows; i++)
    {
        for(int j=0; j<outImg->numCols; j++)
        {
            outImg->imgArr[i][j] = inImg->imgArr[(int)round(i*(inImg->numRows)/outImg->numRows)][(int)round(j*(inImg->numCols)/outImg->numCols)];
        }
    }
}

void freeppm(ppm * img)
{
    for(int i=0; i<img->numRows; i++)
    {
        free(img->imgArr[i]);
    }

    free(img->imgArr);
}