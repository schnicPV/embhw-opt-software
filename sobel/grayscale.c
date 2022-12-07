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

void conv_grayscale(void *picture,
                int width,
                int height) {
  int k,gray;
  int kmax = (width*height)>>2;	// x>>2 <=> x/4
  unsigned int *pixels = (unsigned int *)picture;// , rgb;
  grayscale_width = width;
  grayscape_height = height;
  if (grayscale_array != NULL)
    free(grayscale_array);
  grayscale_array = (unsigned char *) malloc(kmax);
  for(k = 0; k<kmax; k++)
  {
	  gray = ALT_CI_CUSTOM_GRAY_0(pixels[k*2], pixels[k*2+1]);
	  IOWR_32DIRECT(grayscale_array, k*4, gray);
  }
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


