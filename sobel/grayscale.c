/*
 * grayscale.c
 *
 *  Created on: Aug 21, 2015
 *      Author: theo
 */

#include <stdlib.h>
#include <io.h>
#include <system.h>
#include <sys/alt_cache.h>

unsigned char *grayscale_array;
int grayscale_width = 0;
int grayscape_height = 0;

void conv_grayscale(void *picture,
                int width,
                int height) {
  int k,gray;
  int kmax = width*height;
  unsigned short *pixels = (unsigned short *)picture , rgb;
  grayscale_width = width;
  grayscape_height = height;
  if (grayscale_array != NULL)
    free(grayscale_array);
  grayscale_array = (unsigned char *) malloc(kmax);
  for(k = 0; k<kmax; k++)
  {
	  rgb = pixels[k];
	  gray = ((rgb>>11)<<1) + ((((rgb>>5)&0x3F)*40)>>4) + (rgb&0x1F); 	// R + G + B
	  IOWR_8DIRECT(grayscale_array,k,gray);
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


