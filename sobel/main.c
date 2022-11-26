#include <stdio.h>
#include <system.h>
#include <stdlib.h>
#include <io.h>
#include "lcd_simple.h"
#include "grayscale.h"
#include "i2c.h"
#include "camera.h"
#include "vga.h"
#include "dipswitch.h"
#include "sobel.h"
#include "sys/alt_timestamp.h" 		// include due to profiling
#include "alt_types.h" 				// include due to profiling

//extern const char gx_array[3][3];
//extern const char gy_array[3][3];
//extern short *sobel_x_result;
//extern short *sobel_y_result;
//extern int sobel_width;
//extern int sobel_height;
//
//const char * pgx_array = &gx_array;
//const char * pgy_array = &gy_array;

int main()
{
  void *buffer1,*buffer2,*buffer3,*buffer4;
  unsigned short *image;
  unsigned char *grayscale;
  unsigned char current_mode;
  unsigned char mode;

  int wait_cnt = 0; 		// wait at the end of loop so that printf shows result of current execution
  int max_wait = 100000;	// wait until wait_cnt reaches this value

  //timer values for profiling
  alt_u32 start_sobel_x = 0;
  alt_u32 end_sobel_x = 0;
  alt_u32 start_sobel_y = 0;
  alt_u32 end_sobel_y = 0;
  alt_u32 start_sobel_th = 0;
  alt_u32 end_sobel_th = 0;
  alt_u32 start_grayscale = 0;
  alt_u32 end_grayscale = 0;

  init_LCD();
  init_camera();
  vga_set_swap(VGA_QuarterScreen|VGA_Grayscale);
  printf("Hello from Nios II!\n");
  cam_get_profiling();
  buffer1 = (void *) malloc(cam_get_xsize()*cam_get_ysize());
  buffer2 = (void *) malloc(cam_get_xsize()*cam_get_ysize());
  buffer3 = (void *) malloc(cam_get_xsize()*cam_get_ysize());
  buffer4 = (void *) malloc(cam_get_xsize()*cam_get_ysize());
  cam_set_image_pointer(0,buffer1);
  cam_set_image_pointer(1,buffer2);
  cam_set_image_pointer(2,buffer3);
  cam_set_image_pointer(3,buffer4);
  enable_continues_mode();
  init_sobel_arrays(cam_get_xsize()>>1,cam_get_ysize());
  do {
	  if (new_image_available() != 0) {
		  if (current_image_valid()!=0) {
			  current_mode = DIPSW_get_value();
			  mode = current_mode&(DIPSW_SW1_MASK|DIPSW_SW3_MASK|DIPSW_SW2_MASK);
			  image = (unsigned short*)current_image_pointer();
		      switch (mode) {
		      case 0 : transfer_LCD_with_dma(&image[16520],
		                	cam_get_xsize()>>1,
		                	cam_get_ysize(),0);
		      	  	   if ((current_mode&DIPSW_SW8_MASK)!=0) {
		      	  		  vga_set_swap(VGA_QuarterScreen);
		      	  		  vga_set_pointer(image);
		      	  	   }
		      	  	   break;
		      case 1 : alt_timestamp_start();
		    	  	   start_grayscale = alt_timestamp();
		    	  	   conv_grayscale((void *)image,
		    		                  cam_get_xsize()>>1,
		    		                  cam_get_ysize());
		    	  	   end_grayscale = alt_timestamp();
		               grayscale = get_grayscale_picture();
		               transfer_LCD_with_dma(&grayscale[16520],
		      		                	cam_get_xsize()>>1,
		      		                	cam_get_ysize(),1);
		      	  	   if ((current_mode&DIPSW_SW8_MASK)!=0) {
		      	  		  vga_set_swap(VGA_QuarterScreen|VGA_Grayscale);
		      	  		  vga_set_pointer(grayscale);
		      	  	   }
		      	  	   break;
		      case 2 : alt_timestamp_start();
		    	  	   start_grayscale = alt_timestamp();
		    	  	   conv_grayscale((void *)image,
		    		                  cam_get_xsize()>>1,
		    		                  cam_get_ysize());
		    	  	   end_grayscale = alt_timestamp();
		               grayscale = get_grayscale_picture();
		               sobel_x_with_rgb(grayscale);
		               image = GetSobel_rgb();
		               transfer_LCD_with_dma(&image[16520],
		      		                	cam_get_xsize()>>1,
		      		                	cam_get_ysize(),0);
		      	  	   if ((current_mode&DIPSW_SW8_MASK)!=0) {
		      	  		  vga_set_swap(VGA_QuarterScreen);
		      	  		  vga_set_pointer(image);
		      	  	   }
		      	  	   break;
		      case 3 : alt_timestamp_start();
		    	  	   start_grayscale = alt_timestamp();
		    	  	   conv_grayscale((void *)image,
		    		                  cam_get_xsize()>>1,
		    		                  cam_get_ysize());
		    	  	   end_grayscale = alt_timestamp();
		               grayscale = get_grayscale_picture();
		               alt_timestamp_start();
		               start_sobel_x = alt_timestamp();
		               sobel_x(grayscale);
		               end_sobel_x = alt_timestamp();
		               sobel_y_with_rgb(grayscale);
		               image = GetSobel_rgb();
		               transfer_LCD_with_dma(&image[16520],
		      		                	cam_get_xsize()>>1,
		      		                	cam_get_ysize(),0);
		      	  	   if ((current_mode&DIPSW_SW8_MASK)!=0) {
		      	  		  vga_set_swap(VGA_QuarterScreen);
		      	  		  vga_set_pointer(image);
		      	  	   }
		      	  	   break;
		      default: alt_timestamp_start();
		    	  	   start_grayscale = alt_timestamp();
		    	  	   conv_grayscale((void *)image,
	                                  cam_get_xsize()>>1,
	                                  cam_get_ysize());
		    	  	   end_grayscale = alt_timestamp();
                       grayscale = get_grayscale_picture();

                       alt_timestamp_start();
                       start_sobel_x = alt_timestamp();
//                       sobel_x(grayscale);
                       sobel_complete(grayscale, 128);
                       end_sobel_x = alt_timestamp();

//                       alt_timestamp_start();
//                       start_sobel_y = alt_timestamp();
//                       sobel_y(grayscale);
//                       end_sobel_y = alt_timestamp();

//                       alt_timestamp_start();
//                       start_sobel_th = alt_timestamp();
//                       sobel_threshold(128);
//                       end_sobel_th = alt_timestamp();
                       grayscale=GetSobelResult();
		               transfer_LCD_with_dma(&grayscale[16520],
		      		                	cam_get_xsize()>>1,
		      		                	cam_get_ysize(),1);
		      	  	   if ((current_mode&DIPSW_SW8_MASK)!=0) {
		      	  		  vga_set_swap(VGA_QuarterScreen|VGA_Grayscale);
		      	  		  vga_set_pointer(grayscale);
		      	  	   }
		      	  	   break;
		      }
		      //print differences
		      printf("-- CYCLE TIME OF FUNCTIONS --\n");
		      printf("[sobel_tot] : dC = %d\n",end_sobel_x-start_sobel_x);
//		      printf("[sobel_x]   : dC = %d\n",end_sobel_x-start_sobel_x);
//		      printf("[sobel_y]   : dC = %d\n",end_sobel_y-start_sobel_y);
//		      printf("[sobel_th]  : dC = %d\n",end_sobel_th-start_sobel_th);
		      printf("[grayscale] : dC = %d\n",end_grayscale-start_grayscale);

		      //while(wait_cnt < max_wait) { wait_cnt++; }

		      // reset timervalues
		      start_sobel_x = 0;
		      end_sobel_x = 0;
			  start_sobel_y = 0;
			  end_sobel_y = 0;
			  start_sobel_th = 0;
			  end_sobel_th = 0;
			  start_grayscale = 0;
			  end_grayscale = 0;
			  wait_cnt = 0;
		  }
	  }
  } while (1);
  return 0;
}
