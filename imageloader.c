/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	FILE *fp = fopen("filename", "r");

	if(fp != NULL) {
		Image *img = (Image *)malloc(sizeof(Image));
		if (img == NULL) {
        printf("Failed to allocate memory for the Image struct.\n");
        fclose(fp);
        return NULL;
    	}

		char buf[3];
		int maxValue = 0;
		fscanf(fp, "%s", buf); // read the p3
		if (strcmp(buf, "P3") != 0) {
        printf("Invalid PPM file format. Expected P3 magic number.\n");
        fclose(fp);
        free(img);
        return NULL;
    	}


		fscanf(fp, "%d", &img->cols); // read image in cols
		fscanf(fp, "%d", &img->rows);
		fscanf(fp, "%d", &maxValue);

		img->image = (Color **)malloc(img->rows * sizeof(Color *));
		if (img->image == NULL) {
			printf("Failed to allocate memory for the image data.\n");
			fclose(fp);
			free(img);
			return NULL;
		}

		for (uint32_t i = 0; i < img->rows; i++) {
        	for (uint32_t j = 0; j < img->cols; j++) {
				Color *color = &(img->image[i][j]);
				fscanf(fp, "%hhu", &(color->R));
				fscanf(fp, "%hhu", &(color->G));
				fscanf(fp, "%hhu", &(color->B));
        	}
    	}
    
		fclose(fp);
		return img;

	}

}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	printf("P3\n%d %d\n255\n", image->cols, image->rows);

	for(int i = 0; i < image->rows; i++){
		for(int j = 0; j < image->cols; j++){
			Color *color = &(image->image[i][j]);
            printf("%d %d %d ", color->R, color->G, color->B);
        }
        printf("\n");
	}

}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	for (uint32_t i = 0; i < image->rows; i++) {
        free(image->image[i]);
    }
    free(image->image);
    free(image);
}