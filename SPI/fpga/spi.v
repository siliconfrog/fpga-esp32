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

/*
     _____                              ________
SS        |____________________________|
            _   _   _   _   _   _   _ 
SCK  ______| |_| |_| |_| |_| |_| |_| |_____

Data       I O I O I O I O I O I O I O            MISO I   MOSI O

Reflect the incoming data received (from MOSI) back to MISO on the next transfer
*/
module spi_slave( clk, ss, mosi, sck, miso);
    input clk, ss, mosi, sck;
    output miso;

    reg [2:0] spi_bit;                                  // Bit counter
    reg [7:0] dataIn;
    reg [7:0] dataOut;
    reg prevSS = 1;
    reg [1:0] SCK_sync = 0;                             // Sync SCK edge to clk

    always @(posedge clk) begin
        if (ss == 0 && prevSS == 0) begin               // Is active (SS low for >= 2 clks)
            SCK_sync <= { SCK_sync[0], sck };           // Shift in sck
            if (SCK_sync == 2'b01) begin                // SCK rising edge
                dataIn[spi_bit] = mosi;                 // Sample data in
                spi_bit <= spi_bit - 1;                 // MSBFIRST bitcounter
                miso = dataOut[spi_bit];                // Prepare next bit to send out
            end else if (SCK_sync == 2'b10) begin       // SCK falling edge
                if (spi_bit == 3'b111) begin            // End of byte complete - setup data
                    dataOut = dataIn;                   // Reflect the data on next transfer
                end
            end
        end else begin
            spi_bit = 3'b111;
            SCK_sync = 0;
            prevSS = ss;
        end
    end
endmodule
