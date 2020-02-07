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

#include <Arduino.h>
#include <SPI.h>
#include "FPGApins.h"

bool FPGAprogram(const unsigned char *fpgaBin, const unsigned short int fpgaBinSize) {
    const SPISettings spiSettings(4000000, MSBFIRST, SPI_MODE0);     // 4MHz speed
    SPIClass *mySPI = new SPIClass(VSPI);

    pinMode(PIN_CDONE, INPUT);
    pinMode(PIN_CRESET, OUTPUT);
    pinMode(PIN_SS, OUTPUT);
    digitalWrite(PIN_CRESET, HIGH);
    digitalWrite(PIN_SS, HIGH);

    // NB !!  Reversed MOSI/MISO, as the FPGA is a master to talk to the flash device!
    mySPI->begin(PIN_SCK, PIN_MISO, PIN_MOSI, PIN_SS);
    mySPI->beginTransaction(spiSettings);

    // Program FPGA
    digitalWrite(PIN_SS, LOW);                              // Select FPGA, SS = 0
    digitalWrite(PIN_CRESET, LOW);                          // FPGA RESET,  CRESET = 0
    delayMicroseconds(1);                                   // Wait >200ns
    digitalWrite(PIN_CRESET, HIGH);                         // Finish reset CRESET = 1
    delay(1);                                               // Wait >800us

    for (unsigned int i = 0; i < fpgaBinSize; i++) {        // Send program to FPGA
        mySPI->transfer(fpgaBin[i]);
    }
    for (unsigned int i = 0; i < 8; i++) {                  // Required extra bits
        mySPI->transfer(0);                                 // see Lattice FPGA documentation
    }
    mySPI->endTransaction();
    mySPI->end();
    return (digitalRead(PIN_CDONE) == HIGH);
}
