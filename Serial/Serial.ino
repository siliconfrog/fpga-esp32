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

#include <SPI.h>
#include "FPGApins.h"
#include "fpgabin.h"

#include <HardwareSerial.h>

#define LED             2

void setup(void) {
    bool fProg = FPGAprogram(fpgaBin, sizeof(fpgaBin));
    Serial.begin(115200);
              //  Baud      Mode       Rx Pin      Tx Pin
    Serial1.begin(115200, SERIAL_8N1, FPGA_PIN_C, FPGA_PIN_B);
    pinMode(LED, OUTPUT);

    if (fProg) {
        Serial.println("Programmed");
    } else {
        Serial.println("Failed");           // Failed - flash arduino LED
        while(1) {
            digitalWrite(LED, LOW);
            delay(50);
            digitalWrite(LED, HIGH);
            delay(50);
        }
    }
}

void loop(void) {
    if (Serial.available()) {
        Serial1.write(Serial.read());
    }
    if (Serial1.available()) {
        Serial.write(Serial1.read());
    }
}