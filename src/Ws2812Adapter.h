//
// Created by Ben Hencke on 2/10/17.
//

#ifndef WS2812ADAPTER_HPP
#define WS2812ADAPTER_HPP

#include <Arduino.h>
#include <functional>

extern "C"
{
#include "eagle_soc.h"
#include "uart_register.h"
}

//borrowed from Adafruit
// Color-order flag for LED pixels (optional extra parameter to constructor):
// Bits 0,1 = R index (0-2), bits 2,3 = G index, bits 4,5 = B index
#define WS2812_RGB (0 | (1 << 2) | (2 << 4))
#define WS2812_RBG (0 | (2 << 2) | (1 << 4))
#define WS2812_GRB (1 | (0 << 2) | (2 << 4))
#define WS2812_GBR (2 | (0 << 2) | (1 << 4))
#define WS2812_BRG (1 | (2 << 2) | (0 << 4))
#define WS2812_BGR (2 | (1 << 2) | (0 << 4))

typedef std::function<void(uint16_t index, uint8_t rgb[])> Ws2812PixelFunction;



//2.5m 8n1
//const uint8_t bits[4] = {
//  0b11011111,
//  0b00011111,
//  0b11011100,
//  0b00011100,
//};


class Ws2812Adapter {
public:
    Ws2812Adapter(uint8_t o = WS2812_BGR);

    ~Ws2812Adapter();

    void begin();

    void end();

    void setColorOrder(uint8_t o);

    void show(uint16_t numPixels, Ws2812PixelFunction cb);

private:

    void writeRgb(uint8_t rgb[]);
    unsigned long timer;
    uint8_t
            rOffset,                                // Index of red in 3-byte pixel
            gOffset,                                // Index of green byte
            bOffset;                                // Index of blue byte
};


#endif //WS2812ADAPTER_HPP
