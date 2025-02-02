// Copyright 2023 Zack Scholl.
//
// Author: Zack Scholl (zack.scholl@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// See http://creativecommons.org/licenses/MIT/ for more information.

#ifndef WS2812_H
#define WS2812_H

#include "WS2812.pio.h"

typedef struct WS2812 {
  uint pin;
  PIO pio;
  uint sm;
  uint8_t bytes[4];
  uint32_t data;
} WS2812;

WS2812 *WS2812_new(uint pin, PIO pio, uint sm) {
  WS2812 *ws;
  ws = malloc(sizeof(WS2812));
  ws->pin = pin;
  ws->pio = pio;
  ws->sm = sm;
  ws->data = 0;
  ws->bytes[0] = 0;
  ws->bytes[1] = 2;
  ws->bytes[2] = 1;
  ws->bytes[3] = 3;
  uint offset = pio_add_program(pio, &ws2812_program);
  uint bits = 24;
  ws2812_program_init(pio, sm, offset, pin, 800000, bits);
  return ws;
}

void WS2812_fill(WS2812 *ws, uint8_t red, uint8_t green, uint8_t blue) {
  uint32_t rgbw =
      (uint32_t)(blue) << 16 | (uint32_t)(green) << 8 | (uint32_t)(red);
  uint32_t result = 0;
  for (uint b = 0; b < 4; b++) {
    switch (ws->bytes[b]) {
      case 1:
        result |= (rgbw & 0xFF);
        break;
      case 2:
        result |= (rgbw & 0xFF00) >> 8;
        break;
      case 3:
        result |= (rgbw & 0xFF0000) >> 16;
        break;
      case 4:
        result |= (rgbw & 0xFF000000) >> 24;
        break;
    }
    result <<= 8;
  }
  ws->data = result;
  return;
}

void WS2812_show(WS2812 *ws) {
  pio_sm_put_blocking(ws->pio, ws->sm, ws->data);
  return;
}

#endif