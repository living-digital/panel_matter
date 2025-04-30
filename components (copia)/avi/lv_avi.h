
#ifndef _lv_avi_
#define _lv_avi_

#ifdef __cplusplus
extern "C" {
#endif
#include "stdint.h"

extern uint8_t cam_en, color_en, face_en;
void lv_avi_Task(void *pvParameters);
void lv_avi_play(void);


#ifdef __cplusplus
} /* extern "C" */
#endif




#endif 


