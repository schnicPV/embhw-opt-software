/*
 * sobel.h
 *
 *  Created on: Sep 12, 2015
 *      Author: theo
 */

#ifndef SOBEL_H_
#define SOBEL_H_


void init_sobel_arrays(int width , int height);
void sobel_x( unsigned char *source );
void sobel_x_with_rgb( unsigned char *source );
void sobel_y( unsigned char *source );
void sobel_y_with_rgb( unsigned char *source );
void sobel_threshold(short threshold);
void sobel_complete( unsigned char *source);//, short threshold);
unsigned short *GetSobel_rgb();
unsigned char *GetSobelResult();

/* moved variables to .h file*/
const char gx_array[3][3];
const char gy_array[3][3];
short *sobel_x_result;
short *sobel_y_result;
unsigned short *sobel_rgb565;
unsigned char *sobel_result;
int sobel_width;
int sobel_height;

#endif /* SOBEL_H_ */
