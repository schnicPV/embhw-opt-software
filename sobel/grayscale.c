/*
 * grayscale.c
 *
 *  Created on: Aug 21, 2015
 *      Author: theo
 */

#include <stdlib.h>
#include <io.h>
#include <system.h>

unsigned char *grayscale_array;
int grayscale_width = 0;
int grayscape_height = 0;

unsigned char* conv_grayscale(void *picture,
                int width,
                int height) {
  unsigned int k,gray;
  unsigned int kmax = width*height;
  unsigned int *pixels = (unsigned int *)picture;// , rgb;
  grayscale_width = width;
  grayscape_height = height;
  if (grayscale_array != NULL)
    free(grayscale_array);
  grayscale_array = (unsigned char *) malloc(kmax);
  for(k = 0; k < (kmax>>2); k++)								// x>>2 <=> x/4
  {
	  gray = ALT_CI_CUSTOM_GRAY_0(pixels[k*2], pixels[k*2+1]);
	  IOWR_32DIRECT(grayscale_array, k*4, gray);
  }
  return grayscale_array;
}


int get_grayscale_width() {
	return grayscale_width;
}

int get_grayscale_height() {
	return grayscape_height;
}

unsigned char *get_grayscale_picture() {
	return grayscale_array;
}


