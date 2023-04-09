#ifndef _GUI_H_
#define _GUI_H_

#include <stdint.h>

//line0 memory buffer max length
#define LINE0_LEN_MAX 128
#define MAPBIAS_MAX LINE0_LEN_MAX-16

typedef struct
{
		//x coor of line0 cursor(real cursor position shown on display,
		//namely the string lenth on the left side of cursor)
		uint8_t dispCursor_pos;
		//editing position of line0_memoryCursor(operating position in line0_memoryCursor buffer,invisible)
		uint8_t memoryCursor_pos;
		//line0 cursor displaying switch
		uint8_t cursor_displaying_flag;
		//start address of line0 interception
		uint8_t intercept_pos;
	
}gui_cursor_t;

extern gui_cursor_t line0_cursor;



void gui_init(void);
void gui_line0Updt_from_keypad(uint8_t key_val, uint8_t* key_update);
void gui_updtCursor_tim10_500ms(void);
void gui_disp_all_clear(void);
static void gui_updtCursor(uint8_t en, uint8_t pos);
static void gui_displayStr_malloc(void);
static void gui_line0_displayUpdt(void);
static void line0Cursor_scroll(uint8_t dir, uint8_t mode);
static uint8_t line0Buf_intercept(uint8_t start_pos);



#endif