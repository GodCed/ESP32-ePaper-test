#include <Arduino.h>
#include <epd2in7b.h>
#include <epdpaint.h>
#include <sstream>
#include <iomanip>

using std::setw;
using std::setfill;

unsigned char black_image[EPD_WIDTH*EPD_HEIGHT];
unsigned char red_image[EPD_WIDTH*EPD_HEIGHT];

Epd display;
Paint black_paint(black_image, EPD_WIDTH, EPD_HEIGHT);
Paint red_paint(red_image, EPD_WIDTH, EPD_HEIGHT);

unsigned long previousMillis = 0;
unsigned long delayMillis = 1000;

void drawHello() {

    black_paint.Clear(0);
    red_paint.Clear(0);

    black_paint.DrawStringAt(8, 8, "Hello World!", &Font20, 1);
    red_paint.DrawStringAt(8, 28, "Hello World!", &Font20, 1);
}

void drawTime(unsigned long time) {

    std::stringstream uptime;
    uptime  << setfill('0') << setw(2) << (int)time/60000 << ":"
            << setfill('0') << setw(2)  << (int)(time%60000)/1000;

    red_paint.DrawStringAt(15, 55, "UPTIME", &Font12, 1);
    red_paint.DrawRectangle(15, 96, 108, 68, 1);

    black_paint.DrawStringAt(20, 73, uptime.str().c_str(), &Font24, 1);
}

void setup() {
    // put your setup code here, to run once:
    //black_paint.SetRotate(ROTATE_270);
    //red_paint.SetRotate(ROTATE_270);

    display.Init();

    drawHello();
    drawTime(millis());
    display.DisplayFrame(black_image, red_image);
}

void loop() {

    if(millis() > previousMillis + delayMillis) {
        previousMillis = millis();

        drawHello();
        drawTime(millis());

        display.DisplayFrameQuick(black_image, red_image);
    }
}
