#include "lvgl.h"
#include "../hal_MeowKit.h"
#include <Arduino.h>
#include "../hal_config.h"

#define MY_DISP_HOR_RES 320
#define MY_DISP_VER_RES 240
#define LV_VER_RES_MAX  320

#define LVGL_USE_PSRAM 1

/*********************
 *      DEFINES
 *********************/
#ifndef MY_DISP_HOR_RES
    #warning Please define or replace the macro MY_DISP_HOR_RES with the actual screen width, default value 320 is used for now.
    #define MY_DISP_HOR_RES    320
#endif

#ifndef MY_DISP_VER_RES
    #warning Please define or replace the macro MY_DISP_HOR_RES with the actual screen height, default value 240 is used for now.
    #define MY_DISP_VER_RES    240
#endif

class LGFX_MeowKit : public lgfx::LGFX_Device
{
    lgfx::Panel_ST7789 _panel_instance;
    lgfx::Bus_SPI _bus_instance;
    lgfx::Light_PWM _light_instance;

public:
    LGFX_MeowKit(void)
    {
        {
            auto cfg = _bus_instance.config();

            cfg.spi_host = SPI2_HOST;
            cfg.spi_mode = 0;
            cfg.freq_write = 80000000;
            cfg.freq_read  = 16000000;
            cfg.spi_3wire  = false; 
            cfg.use_lock   = true;
            cfg.dma_channel = SPI_DMA_CH_AUTO;
            cfg.pin_mosi = HAL_PIN_LCD_MOSI;
            cfg.pin_miso = HAL_PIN_SD_MISO;
            cfg.pin_sclk = HAL_PIN_LCD_SCLK;
            cfg.pin_dc = HAL_PIN_LCD_DC;

            _bus_instance.config(cfg);
            _panel_instance.setBus(&_bus_instance);
        }
        {
            auto cfg = _panel_instance.config();

            cfg.pin_cs = HAL_PIN_LCD_CS;
            cfg.pin_rst = HAL_PIN_LCD_RST;
            cfg.pin_busy = HAL_PIN_LCD_BUSY;
            cfg.panel_width = 240;
            cfg.panel_height = 320;
            cfg.offset_x = 0;
            cfg.offset_y = 0;
            cfg.offset_rotation  =     3;
            cfg.dummy_read_pixel =     8;
            cfg.dummy_read_bits  =     1;
            cfg.readable         =  false;
            cfg.invert           = true;
            cfg.rgb_order        = false;
            cfg.dlen_16bit       = false;
            cfg.bus_shared       = false;

            _panel_instance.config(cfg);
        }
        {
            auto cfg = _light_instance.config();

            cfg.pin_bl = HAL_PIN_LCD_BL;
            cfg.invert = false;
            cfg.freq = 44100;
            cfg.pwm_channel = 7;

            _light_instance.config(cfg);
            _panel_instance.setLight(&_light_instance);
        }

        setPanel(&_panel_instance);
    }
};

static LGFX_MeowKit _display;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void)
{
    
}

static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);
//static void gpu_fill(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,
//        const lv_area_t * fill_area, lv_color_t color);


void HAL_MeowKit::_disp_init()
{
    printf("display init");
    disp_init();
    #if LVGL_USE_PSRAM

    /* Example for 3) also set disp_drv.full_refresh = 1 below*/
    static lv_disp_draw_buf_t draw_buf_dsc_3;
    // static lv_color_t buf_3_1[MY_DISP_HOR_RES * MY_DISP_VER_RES];            /*A screen sized buffer*/
    // static lv_color_t buf_3_2[MY_DISP_HOR_RES * MY_DISP_VER_RES];            /*Another screen sized buffer*/
    

    /* Try to get buffer from PSRAM */
    lv_color_t * buf_3_1 = (lv_color_t *)ps_malloc(MY_DISP_HOR_RES * MY_DISP_VER_RES * sizeof(lv_color_t));
    lv_color_t * buf_3_2 = (lv_color_t *)ps_malloc(MY_DISP_HOR_RES * MY_DISP_VER_RES * sizeof(lv_color_t));

    /* If something wrong */
    if ((buf_3_1 == NULL) || (buf_3_2 == NULL)) {
        Serial0.printf("[LVGL] malloc buffer from PSRAM error\r\n");
        while (1)
            delay(1000);
    } else {
        Serial0.printf("[LVGL] malloc buffer from PSRAM successful\r\n");
        Serial0.printf("[LVGL] free PSRAM: %d\r\n", ESP.getFreePsram());
    }
    
    lv_disp_draw_buf_init(&draw_buf_dsc_3, buf_3_1, buf_3_2,
                          MY_DISP_VER_RES * LV_VER_RES_MAX);   /*Initialize the display buffer*/

    #else

    static lv_disp_draw_buf_t draw_buf_dsc_2;
    static lv_color_t buf_2_1[MY_DISP_HOR_RES * 24];                        /*A buffer for 10 rows*/
    static lv_color_t buf_2_2[MY_DISP_HOR_RES * 24];                        /*An other buffer for 10 rows*/
    lv_disp_draw_buf_init(&draw_buf_dsc_2, buf_2_1, buf_2_2, MY_DISP_HOR_RES * 24);   /*Initialize the display buffer*/

    #endif


    /*-----------------------------------
     * Register the display in LVGL
     *----------------------------------*/

    static lv_disp_drv_t disp_drv;                         /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv);                    /*Basic initialization*/

    /*Set up the functions to access to your display*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = MY_DISP_HOR_RES;
    disp_drv.ver_res = MY_DISP_VER_RES;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = disp_flush;

    /*Set a display buffer*/
    // disp_drv.draw_buf = &draw_buf_dsc_1;
    // disp_drv.draw_buf = &draw_buf_dsc_2;

    #if LVGL_USE_PSRAM
    disp_drv.draw_buf = &draw_buf_dsc_3;
    #else
    disp_drv.draw_buf = &draw_buf_dsc_2;
    #endif
    
    /*Required for Example 3)*/
    disp_drv.full_refresh = 1;


    /* Set LVGL software rotation */
    // #if CHAPPIE_CORE_LVGL_DIS_PORTRAIT != 1
    // // disp_drv.sw_rotate = 1;
    // disp_drv.rotated = LV_DISP_ROT_90;
    // #endif

    /* Fill a memory array with a color if you have GPU.
     * Note that, in lv_conf.h you can enable GPUs that has built-in support in LVGL.
     * But if you have a different GPU you can use with this callback.*/
    //disp_drv.gpu_fill_cb = gpu_fill;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}



volatile bool disp_flush_enabled = true;

/* Enable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_enable_update(void)
{
    disp_flush_enabled = true;
}

/* Disable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_disable_update(void)
{
    disp_flush_enabled = false;
}

/*Flush the content of the internal buffer the specific area on the display
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_disp_flush_ready()' has to be called when finished.*/
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    // if(disp_flush_enabled) {
        /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one*/

        // int32_t x;
        // int32_t y;
        // for(y = area->y1; y <= area->y2; y++) {
        //     for(x = area->x1; x <= area->x2; x++) {
        //         /*Put a pixel to the display. For example:*/
        //         /*put_px(x, y, *color_p)*/
        //         color_p++;
        //     }
        // }

        uint32_t w = ( area->x2 - area->x1 + 1 );
        uint32_t h = ( area->y2 - area->y1 + 1 );

        _display.startWrite();
        _display.setAddrWindow( area->x1, area->y1, w, h );
        //tft.pushPixels( ( uint16_t * )&color_p->full, w * h, true );
        _display.writePixels((lgfx::rgb565_t *)&color_p->full, w * h);
        _display.endWrite();
    // }

    /*IMPORTANT!!!
     *Inform the graphics library that you are ready with the flushing*/
    lv_disp_flush_ready(disp_drv);
}