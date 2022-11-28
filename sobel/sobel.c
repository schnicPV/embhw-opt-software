/*
 * sobel.c
 *
 *  Created on: Sep 12, 2015
 *      Author: theo
 */

#include <stdlib.h>
#include <stdio.h>
#include "io.h"
#include "sobel.h"

const char gx_array[3][3] = {{-1,0,1},
                  {-2,0,2},
                  {-1,0,1}};
const char gy_array[3][3] = { {1, 2, 1},
                   {0, 0, 0},
                   {-1,-2,-1}};

const char * pgx_array = &(gx_array);
const char * pgy_array = &(gy_array);

void init_sobel_arrays(int width , int height) {
	int loop;
	sobel_width = width;
	sobel_height = height;
	if (sobel_x_result != NULL)
		free(sobel_x_result);
	sobel_x_result = (short *)malloc(width*height*sizeof(short));
	if (sobel_y_result != NULL)
		free(sobel_y_result);
	sobel_y_result = (short *)malloc(width*height*sizeof(short));
	if (sobel_result != NULL)
		free(sobel_result);
	sobel_result = (unsigned char *)malloc(width*height*sizeof(unsigned char));
	if (sobel_rgb565 != NULL)
		free(sobel_rgb565);
	sobel_rgb565 = (unsigned short *)malloc(width*height*sizeof(unsigned short));
	for (loop = 0 ; loop < width*height ; loop++) {
		sobel_x_result[loop] = 0;
		sobel_y_result[loop] = 0;
		sobel_result[loop] = 0;
		sobel_rgb565[loop] = 0;
	}
}

short sobel_mac( unsigned char *pixels,
                 int x,
                 int y,
                 const char *filter,
                 unsigned int width ) {
	short result = 0;

	// original code
	/*for (dy = -1 ; dy < 2 ; dy++) {
	  for (dx = -1 ; dx < 2 ; dx++) {
		 result += filter[(dy+1)*3+(dx+1)]*
				   pixels[(y+dy)*width+(x+dx)];
	  }
	}*/

	// modifs
	result += filter[0] * pixels[(y-1)*width+(x-1)];	// dy = -1, dx = -1
	result += filter[1] * pixels[(y-1)*width+x];		// dy = -1, dx = 0
	result += filter[2] * pixels[(y-1)*width+(x+1)];	// dy = -1, dx = 1
	result += filter[3] * pixels[y*width+(x-1)];		// dy = 0, dx = -1
	result += filter[4] * pixels[y*width+x];			// dy = 0, dx = 0
	result += filter[5] * pixels[y*width+(x+1)];		// dy = 0, dx = 1
	result += filter[6] * pixels[(y+1)*width+(x-1)];	// dy = 1, dx = -1
	result += filter[7] * pixels[(y+1)*width+x];		// dy = 1, dx = 0
	result += filter[8] * pixels[(y+1)*width+(x+1)];	// dy = 1, dx = 1
	return result;
}

void sobel_x( unsigned char *source ) {
   int x,y;
//   short result = 0;

   for (y = 1 ; y < (sobel_height-1) ; y++) {
      for (x = 1 ; x < (sobel_width-1) ; x++) {
         sobel_x_result[y*sobel_width+x] = sobel_mac(source,x,y,gx_array,sobel_width);
//    	  result += pgx_array[0] * source[(y-1)*sobel_width+(x-1)];
//		  result += pgx_array[1] * source[(y-1)*sobel_width+x];
//		  result += pgx_array[2] * source[(y-1)*sobel_width+(x+1)];
//		  result += pgx_array[3] * source[y*sobel_width+(x-1)];
//		  result += pgx_array[4] * source[y*sobel_width+x];
//		  result += pgx_array[5] * source[y*sobel_width+(x+1)];
//		  result += pgx_array[6] * source[(y+1)*sobel_width+(x-1)];
//		  result += pgx_array[7] * source[(y+1)*sobel_width+x];
//		  result += pgx_array[8] * source[(y+1)*sobel_width+(x+1)];
//		  sobel_x_result[(y*sobel_width)+x] = result;
      }
   }
}

void sobel_x_with_rgb( unsigned char *source ) {
   int x,y;
   short result;

   for (y = 1 ; y < (sobel_height-1) ; y++) {
      for (x = 1 ; x < (sobel_width-1) ; x++) {
    	  result = sobel_mac(source,x,y,gx_array,sobel_width);
          sobel_x_result[y*sobel_width+x] = result;
          if (result < 0) {
        	  sobel_rgb565[y*sobel_width+x] = ((-result)>>2)<<5;
          } else {
        	  sobel_rgb565[y*sobel_width+x] = ((result>>3)&0x1F)<<11;
          }
      }
   }
}

void sobel_y( unsigned char *source ) {
   int x,y;
//   short result = 0;

   for (y = 1 ; y < (sobel_height-1) ; y++) {
      for (x = 1 ; x < (sobel_width-1) ; x++) {
         sobel_y_result[y*sobel_width+x] = sobel_mac(source,x,y,gy_array,sobel_width);
//    	  result += pgy_array[0] * source[(y-1)*sobel_width+(x-1)];
//		  result += pgy_array[1] * source[(y-1)*sobel_width+x];
//		  result += pgy_array[2] * source[(y-1)*sobel_width+(x+1)];
//		  result += pgy_array[3] * source[y*sobel_width+(x-1)];
//		  result += pgy_array[4] * source[y*sobel_width+x];
//		  result += pgy_array[5] * source[y*sobel_width+(x+1)];
//		  result += pgy_array[6] * source[(y+1)*sobel_width+(x-1)];
//		  result += pgy_array[7] * source[(y+1)*sobel_width+x];
//		  result += pgy_array[8] * source[(y+1)*sobel_width+(x+1)];
//		  sobel_y_result[(y*sobel_width)+x] = result;
      }
   }
}

void sobel_y_with_rgb( unsigned char *source ) {
   int x,y;
   short result;

   for (y = 1 ; y < (sobel_height-1) ; y++) {
      for (x = 1 ; x < (sobel_width-1) ; x++) {
    	  result = sobel_mac(source,x,y,gy_array,sobel_width);
         sobel_y_result[y*sobel_width+x] = result;
         if (result < 0) {
       	  sobel_rgb565[y*sobel_width+x] = ((-result)>>2)<<5;
         } else {
       	  sobel_rgb565[y*sobel_width+x] = ((result>>3)&0x1F)<<11;
         }
      }
   }
}

void sobel_threshold(short threshold) {
	short sum,value;
	int k;
	int kmax = sobel_height*sobel_width;
	for(k = 1; k<kmax; k++)
	{
		value = sobel_x_result[k];
//		sum = (value < 0) ? -value : value;
		sum = (value + (value >> 31)) ^ (value >> 31);		// get absolute value (2 complement)
		value = sobel_y_result[k];
//		sum += (value < 0) ? -value : value;
		sum += (value + (value >> 31)) ^ (value >> 31);		// get absolute value (2 complement)
		sobel_result[k] = (sum > threshold) ? 0xFF : 0;
	}
}

void sobel_complete( unsigned char *source)//, short threshold)
{
   short result = 0;
   int x,y,arrayindex;
//   short sum,value;
   for (y = 1 ; y < (sobel_height-1) ; y++) {
	 for (x = 1 ; x < (sobel_width-1) ; x++) {
	   arrayindex = (y*sobel_width)+x;

	   // sobel_x in-lining
	   result += pgx_array[0] * source[(y-1)*sobel_width+(x-1)];
	   result += pgx_array[1] * source[(y-1)*sobel_width+x];
	   result += pgx_array[2] * source[(y-1)*sobel_width+(x+1)];
	   result += pgx_array[3] * source[y*sobel_width+(x-1)];
	   result += pgx_array[4] * source[y*sobel_width+x];
	   result += pgx_array[5] * source[y*sobel_width+(x+1)];
	   result += pgx_array[6] * source[(y+1)*sobel_width+(x-1)];
	   result += pgx_array[7] * source[(y+1)*sobel_width+x];
	   result += pgx_array[8] * source[(y+1)*sobel_width+(x+1)];
	   sobel_x_result[arrayindex] = result;
	   result = 0;

	   // sobel_y in-lining
	   result += pgy_array[0] * source[(y-1)*sobel_width+(x-1)];
	   result += pgy_array[1] * source[(y-1)*sobel_width+x];
	   result += pgy_array[2] * source[(y-1)*sobel_width+(x+1)];
	   result += pgy_array[3] * source[y*sobel_width+(x-1)];
	   result += pgy_array[4] * source[y*sobel_width+x];
	   result += pgy_array[5] * source[y*sobel_width+(x+1)];
	   result += pgy_array[6] * source[(y+1)*sobel_width+(x-1)];
	   result += pgy_array[7] * source[(y+1)*sobel_width+x];
	   result += pgy_array[8] * source[(y+1)*sobel_width+(x+1)];
	   sobel_y_result[arrayindex] = result;
	   result = 0;

//	   // sobel_threshold in-lining
//	   value = sobel_x_result[arrayindex];
//	   sum = (value < 0) ? -value : value;
//	   value = sobel_y_result[arrayindex];
//	   sum += (value < 0) ? -value : value;
//	   sobel_result[arrayindex] = (sum > threshold) ? 0xFF : 0;
	 }
   }
}

unsigned short *GetSobel_rgb() {
	return sobel_rgb565;
}

unsigned char *GetSobelResult() {
	return sobel_result;
}
