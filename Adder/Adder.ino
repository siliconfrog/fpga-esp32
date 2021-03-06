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

#define LED             2

#define ADDER_A         FPGA_PIN_A
#define ADDER_B         FPGA_PIN_B
#define ADDER_CIN       FPGA_PIN_C

#define SUM_IN          FPGA_PIN_12
#define COUT_IN         FPGA_PIN_E

void setup(void) {
    bool fProg = FPGAprogram(fpgaBin, sizeof(fpgaBin));
    Serial.begin(115200);
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
    pinMode(ADDER_A, OUTPUT);
    pinMode(ADDER_B, OUTPUT);
    pinMode(ADDER_CIN, OUTPUT);
    pinMode(SUM_IN, INPUT);
    pinMode(COUT_IN, INPUT);
}

uint8_t ctr = 0;

void loop(void) {
    if ((ctr & 1) > 0) {
        Serial.print("A high ");
        digitalWrite(ADDER_A, HIGH);
    } else {
        Serial.print("A low  ");
        digitalWrite(ADDER_A, LOW);
    }
    if ((ctr & 2) > 0) {
        Serial.print("B high ");
        digitalWrite(ADDER_B, HIGH);
    } else {
        Serial.print("B low  ");
        digitalWrite(ADDER_B, LOW);
    }
    if ((ctr & 4) > 0) {
        Serial.print("Cin high ");
        digitalWrite(ADDER_CIN, HIGH);
    } else {
        Serial.print("Cin low  ");
        digitalWrite(ADDER_CIN, LOW);
    }

    Serial.print("         ");

    if (digitalRead(SUM_IN) == HIGH) {
        Serial.print("SUM high  ");
    } else {
        Serial.print("SUM low   ");
    }
    if (digitalRead(COUT_IN) == HIGH) {
        Serial.print("COUT high");
    } else {
        Serial.print("COUT low ");
    }
    Serial.println("\n");
    ctr++;
    if ((ctr & 7) == 0) {
        Serial.println("\n===================================================\n");
    }
    delay(5000);
}
