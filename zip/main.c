//Saúl Enrique Labra Cruz A01020725
//Simple Image Manipulation

#include "ppm.h"

int main(int argc, char *argv[]){

    int c=0;
    char * input_file = NULL;
    char * output_file = NULL;
    int scaleFlag = 0;
    int scaleFactor = 0;
    int invertFlag = 0;
    
    while((c=getopt(argc, argv, "i:o:ns:")) != -1)
    switch (c)
    {
        case 'i':
            input_file = optarg;
            break;
        case 'o':
            output_file = optarg;
            break;
        case 'n':
            invertFlag = 1;
            break;
        case 's':
            scaleFlag = 1;
            scaleFactor = atoi(optarg);
            break;
        case '?':
            printf("The input option is not valid!\n");
            return -1;
    }


    printf("Reading from: %s\n", input_file);
    printf("Writing to: %s\n", output_file);

    ppm img1;
    ppm img2;

    readImg(input_file, &img1);

    if(invertFlag != 0)
    {
        invertColors(&img1, &img2);
        img1 = img2;
    }

    if(scaleFlag != 0)
    {
        scaleImg(&img1, &img2, scaleFactor);
    }

    writeImg(&img2, output_file);

    freeppm(&img1);
    freeppm(&img2);

    return 0;
}