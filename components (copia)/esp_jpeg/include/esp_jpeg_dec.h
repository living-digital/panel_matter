// Copyright 2021 Espressif Systems (Shanghai) CO., LTD
// All rights reserved.

#ifndef ESP_JPEG_DEC_H
#define ESP_JPEG_DEC_H

/**
 * @file esp_jpeg_dec.h
 * @brief Create an JPEG decoder.
 *        Currently, support functions as follows:
 *             - Support variety of width and height to decoder
 *             - Support RGB888 RGB565(big end) RGB565(little end) raw data to output
 *             - Support 0, 90 180 270 degree clockwise rotation, under width and height are multiply of 8.
 *        The encoder do ASM optimization in ESP32S3. The encoder frame rate performs better than the others chips.
 * @version 1.0.0
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_jpeg_common.h"
#include "usb_cam.h"
extern void camera_frame_cb(uvc_frame_t *frame, void *ptr);
#define DEFAULT_JPEG_DEC_CONFIG() {                           \
    .output_type               = JPEG_RAW_TYPE_RGB565_LE,     \
    .rotate                    = JPEG_ROTATE_0D,              \
}

#define JPEG_DEC_MAX_MARKER_CHECK_LEN (1024)

typedef void* jpeg_dec_handle_t;

/* Jpeg dec user need to config */
typedef struct {
    jpeg_raw_type_t output_type; /*!< jpeg_dec_out_type 1:rgb888 0:rgb565 */
    jpeg_rotate_t rotate;        /*!< Supports 0, 90 180 270 degree clockwise rotation.
                                      Under width % 8 == 0. height % 8 = 0 conditions, rotation enabled. Otherwise unsupported */
} jpeg_dec_config_t;

/* Jpeg dec out info */
typedef struct {
    int width;                      /* Number of pixels in the horizontal direction */
    int height;                     /* Number of pixels in the vertical direction */
    int component_num;              /* Number of color component*/
    uint8_t component_id[3];        /* ID of color component*/
    uint8_t x_factory[3];           /* Size factory in the x direction*/
    uint8_t y_factory[3];           /* Size factory in the y direction*/
    uint8_t huffbits[2][2][16];     /* Huffman bit distribution tables [id][dcac] */
    uint16_t huffdata[2][2][256];   /* Huffman decoded data tables [id][dcac] */
    uint8_t qtid[3];                /* Quantization table ID of each component */
    int16_t qt_tbl[4][64];          /* De-quantizer tables [id] */
} jpeg_dec_header_info_t;

/* Jpeg dec io control */
typedef struct {
    unsigned char *inbuf;           /* The input buffer pointer */
    int inbuf_len;                  /* The number of the input buffer */
    int inbuf_remain;               /* Not used number of the in buffer */
    unsigned char *outbuf;          /* The decoded data is placed.The buffer must be aligned 16 byte. */
} jpeg_dec_io_t;

/**
 * @brief      Create a Jpeg decode handle, set user config info to decode handle
 *
 * @param[in]      config        The configuration information
 *
 * @return     other values: The JPEG decoder handle
 *             NULL: failed
 */
jpeg_dec_handle_t *jpeg_dec_open(jpeg_dec_config_t *config);

/**
 * @brief      Parse picture data header, and out put info to user
 *
 * @param[in]      jpeg_dec        jpeg decoder handle
 *
 * @param[in]      io              struct of jpeg_dec_io_t
 *
 * @param[out]     out_info        output info struct to user
 *
 * @return     jpeg_error_t
 *             - JPEG_ERR_OK: on success
 *             - Others: error occurs
 */
jpeg_error_t jpeg_dec_parse_header(jpeg_dec_handle_t *jpeg_dec, jpeg_dec_io_t *io, jpeg_dec_header_info_t *out_info);

/**
 * @brief      Decode one Jpeg picture
 *
 * @param[in]      jpeg_dec    jpeg decoder handle
 *
 * @param[in]      io          struct of jpeg_dec_io_t
 *
 * @return     jpeg_error_t
 *             - JPEG_ERR_OK: on success
 *             - Others: error occurs
 */
jpeg_error_t jpeg_dec_process(jpeg_dec_handle_t *jpeg_dec, jpeg_dec_io_t *io);

/**
 * @brief      Deinitialize Jpeg decode handle
 *
 * @param[in]      jpeg_dec    jpeg decoder handle
 *
 * @return     jpeg_error_t
 *             - JPEG_ERR_OK: on success
 *             - Others: error occurs
 */
jpeg_error_t jpeg_dec_close(jpeg_dec_handle_t *jpeg_dec);
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "esp_err.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_rgb.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "usb_stream.h"
#include "esp_timer.h"
void usbcam_to_lcd(void);
int esp_jpeg_decoder_one_picture(uint8_t *input_buf, int len, uint8_t *output_buf);

#ifdef __cplusplus
}
#endif

#endif
