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

// Connections         ESP32 -> FPGA Connections:  Don't forget: 3v3 and GND!
#define PIN_SCK         5   // to "A" (SCK)
#define PIN_MOSI       18   // to "B" (MOSI)
#define PIN_MISO       19   // to "C" (MISO)
#define PIN_CRESET     21   // to "D" (CRESET)
#define PIN_SS         22   // to "12" (SS/CE0)
#define PIN_CDONE      23   // to "11" (CDONE)

#define FLASH_CS       15   // to "13" (CE1)  Only to be used if programming the flash device

// Convenience definitions
#define FPGA_PIN_A      PIN_SCK
#define FPGA_PIN_B      PIN_MOSI
#define FPGA_PIN_C      PIN_MISO
#define FPGA_PIN_12     PIN_SS

#define FPGA_PIN_E      4   // to "E", used in projects

bool FPGAprogram(const unsigned char *fpgaBin, const unsigned short int fpgaBinSize);
