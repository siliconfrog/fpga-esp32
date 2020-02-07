PRJ=adder

all: fpgaprog fpgabin.h fpga.bin


fpga.bin:
	yosys -q -p "read_verilog $(PRJ).v; synth_ice40 -blif fpga.blif"
	arachne-pnr -q -d 384 -P qn32 -c /usr/local/share/arachne-pnr/chipdb-384.bin -p ice40-384_$(PRJ).pcf -o fpga.txt fpga.blif
	/usr/local/bin/icepack fpga.txt fpga.bin
#gcc -Wall fpga-384.cpp -lstdc++ -o fpga-384

fpgaprog: fpgaprog.cpp
	gcc -Wall -Werror -std=c++11 fpgaprog.cpp -o fpgaprog -lstdc++

fpgabin.h: fpga.bin
	fpgaprog fpga.bin >../fpgabin.h

clean:
	rm -f fpgaprog fpga.bin fpga.txt fpga.blif
