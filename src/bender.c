#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0x08, 0xD1, 0x15, 0x60, 0x6A, 0xB1, 0x45, 0xBA, 0x9E, 0x4C, 0x85, 0xBD, 0xE3, 0x13, 0x12, 0x07 }
PBL_APP_INFO(MY_UUID,
             "Kiss my Shiny Metal", "JRD",
             1, 1, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;
RotBmpPairContainer image_background;
BmpContainer image_planetexpress;
BmpContainer image_eyes;

TextLayer time_display_textlayer;
TextLayer time_display_textlayer_h1;
TextLayer time_display_textlayer_h2;
TextLayer time_display_textlayer_m1;
TextLayer time_display_textlayer_m2;

TextLayer time_display_textlayer_M1;
TextLayer time_display_textlayer_M2;
TextLayer time_display_textlayer_d1;
TextLayer time_display_textlayer_d2;

#define TEXTLABELWIDTH 	20;
#define TEXTLABELHEIGHT 19;
#define POSITION_1 90;
#define POSITION_2 109;
#define POSITION_3 128;
#define POSITION_4 147;

#define POSITION_X1 2;
#define POSITION_X2 120;


#define AUXTEXT_H 20
#define AUXTEXT_FONT FONT_KEY_GOTHIC_18_BOLD


#define TIME_STR_BUFFER_BYTES 20
char time_str_buffer[TIME_STR_BUFFER_BYTES];
char time_str_buffer_h1[1];
char time_str_buffer_h2[1];
char time_str_buffer_m1[1];
char time_str_buffer_m2[1];

char time_str_buffer_d1[1];
char time_str_buffer_d2[1];
char time_str_buffer_M1[1];
char time_str_buffer_M2[1];

double currentSecond;
double currentPosition;
double eyeposition;

void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Window Name");
  //window_set_background_color(&window, GColorWhite);
  window_stack_push(&window, true /* Animated */);
  resource_init_current_app(&VERSION);



  bmp_init_container(RESOURCE_ID_PLANETEXPRESS, &image_planetexpress);
  image_planetexpress.layer.layer.frame.origin.y = 18;
  //image_planetexpress.layer.layer.frame.origin.x = -56;
  layer_add_child(&window.layer, &image_planetexpress.layer.layer);


  bmp_init_container(RESOURCE_ID_EYES, &image_eyes);
  image_eyes.layer.layer.frame.origin.y = 45;
  image_eyes.layer.layer.frame.origin.x = 56;
  layer_add_child(&window.layer, &image_eyes.layer.layer);


  rotbmp_pair_init_container(RESOURCE_ID_BACKGROUND_WHITE,RESOURCE_ID_BACKGROUND_BLACK, &image_background);
  image_background.layer.layer.frame.origin.y = -26;
  image_background.layer.layer.frame.origin.x = -38;

  layer_add_child(&window.layer, &image_background.layer.layer);




  GRect tf = window.layer.frame;
  // - vertically centered rectangle for time
  tf.origin.y = POSITION_1;
  tf.origin.x = POSITION_X1;
  tf.size.h = TEXTLABELHEIGHT;
  tf.size.w = TEXTLABELWIDTH;

  tf.origin.y = POSITION_1;
  tf.origin.x = POSITION_X1;
  text_layer_init(&time_display_textlayer_h1, tf);
  	  text_layer_set_text_alignment(&time_display_textlayer_h1, GTextAlignmentCenter); // centered
  	  text_layer_set_background_color(&time_display_textlayer_h1, GColorBlack); // black background
  	  text_layer_set_font(&time_display_textlayer_h1, fonts_get_system_font(AUXTEXT_FONT)); // font
  	  text_layer_set_text_color(&time_display_textlayer_h1, GColorWhite); // white text
  	  text_layer_set_text(&time_display_textlayer_h1, "");
  	  layer_add_child(&window.layer, &time_display_textlayer_h1.layer);

  tf.origin.y = POSITION_2;
  text_layer_init(&time_display_textlayer_h2, tf);
	  text_layer_set_text_alignment(&time_display_textlayer_h2, GTextAlignmentCenter); // centered
	  text_layer_set_background_color(&time_display_textlayer_h2, GColorBlack); // black background
	  text_layer_set_font(&time_display_textlayer_h2, fonts_get_system_font(AUXTEXT_FONT)); // font
	  text_layer_set_text_color(&time_display_textlayer_h2, GColorWhite); // white text
	  text_layer_set_text(&time_display_textlayer_h2, "");
	  layer_add_child(&window.layer, &time_display_textlayer_h2.layer);

  tf.origin.y = POSITION_3;
  text_layer_init(&time_display_textlayer_m1, tf);
	  text_layer_set_text_alignment(&time_display_textlayer_m1, GTextAlignmentCenter); // centered
	  text_layer_set_background_color(&time_display_textlayer_m1, GColorBlack); // black background
	  text_layer_set_font(&time_display_textlayer_m1, fonts_get_system_font(AUXTEXT_FONT)); // font
	  text_layer_set_text_color(&time_display_textlayer_m1, GColorWhite); // white text
	  text_layer_set_text(&time_display_textlayer_m1, "");
	  layer_add_child(&window.layer, &time_display_textlayer_m1.layer);

  tf.origin.y = POSITION_4;
  text_layer_init(&time_display_textlayer_m2, tf);
	  text_layer_set_text_alignment(&time_display_textlayer_m2, GTextAlignmentCenter); // centered
	  text_layer_set_background_color(&time_display_textlayer_m2, GColorBlack); // black background
	  text_layer_set_font(&time_display_textlayer_m2, fonts_get_system_font(AUXTEXT_FONT)); // font
	  text_layer_set_text_color(&time_display_textlayer_m2, GColorWhite); // white text
	  text_layer_set_text(&time_display_textlayer_m2, "");
	  layer_add_child(&window.layer, &time_display_textlayer_m2.layer);


  tf.origin.x = POSITION_X2;
  tf.origin.y = POSITION_1;
  text_layer_init(&time_display_textlayer_M1, tf);
	  text_layer_set_text_alignment(&time_display_textlayer_M1, GTextAlignmentCenter); // centered
	  text_layer_set_background_color(&time_display_textlayer_M1, GColorBlack); // black background
	  text_layer_set_font(&time_display_textlayer_M1, fonts_get_system_font(AUXTEXT_FONT)); // font
	  text_layer_set_text_color(&time_display_textlayer_M1, GColorWhite); // white text
	  text_layer_set_text(&time_display_textlayer_M1, "");
	  layer_add_child(&window.layer, &time_display_textlayer_M1.layer);

  tf.origin.y = POSITION_2;
  text_layer_init(&time_display_textlayer_M2, tf);
	  text_layer_set_text_alignment(&time_display_textlayer_M2, GTextAlignmentCenter); // centered
	  text_layer_set_background_color(&time_display_textlayer_M2, GColorBlack); // black background
	  text_layer_set_font(&time_display_textlayer_M2, fonts_get_system_font(AUXTEXT_FONT)); // font
	  text_layer_set_text_color(&time_display_textlayer_M2, GColorWhite); // white text
	  text_layer_set_text(&time_display_textlayer_M2, "");
	  layer_add_child(&window.layer, &time_display_textlayer_M2.layer);

  tf.origin.y = POSITION_3;
  text_layer_init(&time_display_textlayer_d1, tf);
	  text_layer_set_text_alignment(&time_display_textlayer_d1, GTextAlignmentCenter); // centered
	  text_layer_set_background_color(&time_display_textlayer_d1, GColorBlack); // black background
	  text_layer_set_font(&time_display_textlayer_d1, fonts_get_system_font(AUXTEXT_FONT)); // font
	  text_layer_set_text_color(&time_display_textlayer_d1, GColorWhite); // white text
	  text_layer_set_text(&time_display_textlayer_d1, "");
	  layer_add_child(&window.layer, &time_display_textlayer_d1.layer);

  tf.origin.y = POSITION_4;
  text_layer_init(&time_display_textlayer_d2, tf);
	  text_layer_set_text_alignment(&time_display_textlayer_d2, GTextAlignmentCenter); // centered
	  text_layer_set_background_color(&time_display_textlayer_d2, GColorBlack); // black background
	  text_layer_set_font(&time_display_textlayer_d2, fonts_get_system_font(AUXTEXT_FONT)); // font
	  text_layer_set_text_color(&time_display_textlayer_d2, GColorWhite); // white text
	  text_layer_set_text(&time_display_textlayer_d2, "");
	  layer_add_child(&window.layer, &time_display_textlayer_d2.layer);

	//  tf.origin.y = 0;
	//  tf.origin.x = 0;
	//  tf.size.h = 20;
	//  tf.size.w = 144;

//text_layer_init(&time_display_textlayer, tf);
//layer_add_child(&window.layer, &time_display_textlayer.layer);

}
void handle_deinit(AppContextRef ctx) {
  (void)ctx;

  // Note: Failure to de-init this here will result in instability and
  //       unable to allocate memory errors.
  rotbmp_pair_deinit_container(&image_background);
  bmp_deinit_container(&image_planetexpress);

}

void handle_minute_tick(AppContextRef ctx, PebbleTickEvent *event)
{
  currentSecond = (double)event->tick_time->tm_sec;
  currentPosition = -56 + ((144 +56) * (currentSecond/60));

  eyeposition = 56.0 + (5.0 * (currentSecond/60));

  image_eyes.layer.layer.frame.origin.x = (int)eyeposition;


  image_planetexpress.layer.layer.frame.origin.x = (int)currentPosition;

  if (clock_is_24h_style()) {
	  string_format_time(time_str_buffer, TIME_STR_BUFFER_BYTES, "%H%M%S%m%d", event->tick_time);
    } else {
      string_format_time(time_str_buffer, TIME_STR_BUFFER_BYTES, "%I%M%S%m%d", event->tick_time);
    }


  time_str_buffer_h1[0] = time_str_buffer[0];
  time_str_buffer_h2[0] = time_str_buffer[1];
  time_str_buffer_m1[0] = time_str_buffer[2];
  time_str_buffer_m2[0] = time_str_buffer[3];

  time_str_buffer_M1[0] = time_str_buffer[6];
  time_str_buffer_M2[0] = time_str_buffer[7];
  time_str_buffer_d1[0] = time_str_buffer[8];
  time_str_buffer_d2[0] = time_str_buffer[9];

  text_layer_set_text(&time_display_textlayer_h1, time_str_buffer_h1);
  text_layer_set_text(&time_display_textlayer_h2, time_str_buffer_h2);
  text_layer_set_text(&time_display_textlayer_m1, time_str_buffer_m1);
  text_layer_set_text(&time_display_textlayer_m2, time_str_buffer_m2);

  text_layer_set_text(&time_display_textlayer_M1, time_str_buffer_M1);
  text_layer_set_text(&time_display_textlayer_M2, time_str_buffer_M2);
  text_layer_set_text(&time_display_textlayer_d1, time_str_buffer_d1);
  text_layer_set_text(&time_display_textlayer_d2, time_str_buffer_d2);

  layer_mark_dirty(&image_planetexpress.layer.layer);
  layer_mark_dirty(&image_eyes.layer.layer);

  if ((int)currentSecond == 0){
	  layer_mark_dirty(&time_display_textlayer_h1.layer);
	  layer_mark_dirty(&time_display_textlayer_h2.layer);
	  layer_mark_dirty(&time_display_textlayer_m1.layer);
	  layer_mark_dirty(&time_display_textlayer_m2.layer);
  }
}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .deinit_handler = &handle_deinit,
    .tick_info = {
          .tick_handler = &handle_minute_tick,
          .tick_units = SECOND_UNIT
        },
  };
  app_event_loop(params, &handlers);
}
