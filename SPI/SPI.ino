/* Copyright (c) 2018, Silicon Frog. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
3. Neither the name of the copyright holder nor the names of its contributors
   may be used to endorse or promote products derived from this software
   without specific prior written permission.

This software is provided by the copyright holders and contributors "as is"
and any express or implied warranties, including, but not limited to, the
implied warranties of merchantability and fitness for a particular purpose
are disclaimed. In no event shall the copyright holder or contributors be
liable for any direct, indirect, incidental, special, exemplary, or
consequential damages (including, but not limited to, procurement of
substitute goods or services; loss of use, data, or profits; or business
interruption) however caused and on any theory of liability, whether in
contract, strict liability, or tort (including negligence or otherwise)
arising in any way out of the use of this software, even if advised of the
possibility of such damage.  */

#include <stdlib.h>
#include <SPI.h>
#include "FPGApins.h"
#include "fpgabin.h"

#define LED              2

static SPIClass *mySPI;

void setup(void) {
    bool fProg = FPGAprogram(fpgaBin, sizeof(fpgaBin));
    Serial.begin(115200);
    if (fProg) {
        Serial.println("Programmed");
    } else {
        Serial.println("Failed");           // Failed - flash LED quickly
        pinMode(LED, OUTPUT);
        while(1) {
            digitalWrite(LED, LOW);
            delay(50);
            digitalWrite(LED, HIGH);
            delay(50);
        }
    }

    pinMode(PIN_SS, OUTPUT);
    digitalWrite(PIN_SS, HIGH);

    const SPISettings spiSettings(4000000, MSBFIRST, SPI_MODE0);     // 4MHz speed
    mySPI = new SPIClass(VSPI);
    mySPI->begin(PIN_SCK, PIN_MOSI, PIN_MISO, PIN_SS);
}

static byte prevSend = 0;

void loop(void) {
    for (byte i = 0; i < 30; i++) {
        byte dataSend = random(0, 0xFF);
        digitalWrite(PIN_SS, LOW);
        byte dataRx = mySPI->transfer(dataSend);
        digitalWrite(PIN_SS, HIGH);

        Serial.printf("%02X%c", dataSend, (prevSend == dataRx) ? ' ' : '*');
        prevSend = dataSend;
    }
    Serial.println("");

    delay(100);
}
