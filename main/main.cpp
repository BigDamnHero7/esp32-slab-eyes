#include <cstdio>
#include "ssd1306.h"
#include "driver/i2c_master.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_random.h"
#include "esp_log.h"
#include "mood.hpp"


bool blinking =false;
int64_t blinkstart= 0;
int64_t nextblinkat= 0;

void drawfilledcircle(ssd1306_handle_t disp,int xc, int yc, int r){
    for(int y=-r;y<=r;y++){
        for(int x=-r;x<=r;x++){
            if(x*x+y*y<=r*r){
                ssd1306_draw_pixel(disp, xc+x,yc+y,false);
            }
        }
    }
}


void drawEyeShape(ssd1306_handle_t disp, int x, int y, int w, int h,float blink,float pupilX= 0.0f, float pupilY= 0.0f){
    int actualH= (int)(h*(1.0f-blink));
    if(actualH<2){
        actualH=2;
    }
    int topY = y + (h - actualH);   // top edge moves down as blink increases
    int bottomY = y + h;            // bottom edge stays fixed
    if (actualH < 5) {
        int lineY = bottomY - 2;         // 2px up from bottom edge
        ssd1306_draw_rect(disp, x, lineY, w, 2, true);
        return;
    }
    int radius = w / 2;
    if (radius > actualH / 2){
        radius = actualH / 2;
    }

    ssd1306_draw_rect(disp, x, topY + radius, w, actualH - 2 * radius, true);
    ssd1306_draw_circle(disp, x + radius, topY + radius, radius, true);
    ssd1306_draw_circle(disp, x + radius, bottomY - radius, radius, true);

    if (actualH > 10) {
        int pupilRadius = 6;
        int maxShiftX = 3;
        int maxShiftY = 8;
        int pupilCenterX = x + radius + (int)(pupilX * maxShiftX);
        int pupilCenterY = topY + actualH / 2 + (int)(pupilY * maxShiftY);
        drawfilledcircle(disp, pupilCenterX, pupilCenterY, pupilRadius);
    }
}

void drawmouth(ssd1306_handle_t disp,int x, int y, int w,int h){
    ssd1306_draw_rect(disp,x,y,w,h,true);
}

static Idlemood idlemood;
static Happymood happymood;
static Suprisedmood suprised;
static Sleepymood sleepy;

static Mood* currentmood = &sleepy;

extern "C" void app_main(void)
{
    ESP_LOGI("mood","Starting in mood: %s", currentmood->name());

    i2c_master_bus_config_t bus_cfg = {};
    bus_cfg.i2c_port = I2C_NUM_0;
    bus_cfg.sda_io_num = GPIO_NUM_32;
    bus_cfg.scl_io_num = GPIO_NUM_33;
    bus_cfg.clk_source = I2C_CLK_SRC_DEFAULT;
    bus_cfg.glitch_ignore_cnt = 7;
    bus_cfg.flags.enable_internal_pullup = true;
    i2c_master_bus_handle_t bus;
    i2c_new_master_bus(&bus_cfg, &bus);

    ssd1306_config_t cfg = {};
    cfg.bus = SSD1306_I2C;
    cfg.width = 128;
    cfg.height = 64;
    cfg.iface.i2c.addr = 0x3C;
    ssd1306_handle_t disp;
    ssd1306_new_i2c(&cfg, &disp);

    //3. Fill the whole screen
    // ssd1306_clear(disp);
    // drawEyeShape(disp,30,17,20,30,0.5f,0.0f); // filled white
    // ssd1306_display(disp);
    float pupilx=0.0f, pupily=0.0f;
    float targetx=0.0f, targety=0.0f;
    int64_t nextglanceat=0;
    while (true) {
        int64_t now= esp_timer_get_time()/1000;

        if(!blinking && now> nextblinkat){
            blinking = true;
            blinkstart= now;
            nextblinkat= now+currentmood->blinkInterval();
        }

        float blink=0.0f;
        if(blinking){
            float u = (now-blinkstart)/300.0f;
            if(u>=1.0f){
                blinking= false;
            }else if(u<0.5f){
                blink= u*2.0f;
            }else{
                blink=(1.0f-u)*2.0f;
            }
        }
        float blinkright= blink-0.01f;
        if(blinkright<0.0f) blinkright= 0.0f;

        if(now>nextglanceat){
            targetx= ((int)(esp_random()%201)-100)/100.0f;
            targety= ((int)(esp_random()%201)-100)/100.0f*currentmood->pupilRange()+currentmood->pupilbias();
            nextglanceat= now+1000+(esp_random()%2000);
        }
        pupilx+=(targetx-pupilx)*0.08f;
        pupily+=(targety-pupily)*0.08f;

        ssd1306_clear(disp);
        drawEyeShape(disp, 30, 17, 20, 30, blink, pupilx, pupily);
        drawEyeShape(disp, 78, 17, 20, 30, blinkright, pupilx, pupily);
        drawmouth(disp,54,55,25,6);
        ssd1306_display(disp);

        vTaskDelay(pdMS_TO_TICKS(16));
    }
    

    while (true) vTaskDelay(pdMS_TO_TICKS(1000));

}
