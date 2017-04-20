
#include <string>
#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

void ShowHelp() {
	std::cout << "SplitMod.exe {inputfile} {mod}" << std::endl;
}

std::string buildOutFile(std::string baseFile, int counter) {
	std::stringstream strm;
	strm << baseFile << ".part_" << counter;
	return strm.str();
}

int main(int argc, char* argv[]) {

	if (argc > 2) {
		int i = 0;
		unsigned char c;

		//read command line parameters
		std::string file = argv[1];
		int modCount = atoi(argv[2]);

		//debugging
		std::cout << "Input File: " << file << std::endl;
		std::cout << "Mod Count : " << modCount << std::endl;

		//create output streams
		std::vector<std::ofstream> outs(modCount);
		for (std::vector<std::ofstream>::iterator it = outs.begin(); it != outs.end(); ++it) {
			std::string outFile = buildOutFile(file, i);
			std::cout << "Opening output file : " << outFile << std::endl;
			it->open(outFile, std::ofstream::out | std::ofstream::binary);
			i++;
		}

		//create input stream
		std::ifstream ins;
		ins.open(file, std::ifstream::in | std::ifstream::binary);
		
		//read input stream
		i = 0;
		while (ins.good()) {
			//read byte
			c = ins.get();
			if (ins.good()) {
				//determine which output stream it should go to
				//write to correct output stream
				outs[i % modCount] << c;
				i++;
			}

		}
		//close input stream
		ins.close();

		//close output streams
		for (std::vector<std::ofstream>::iterator it = outs.begin(); it != outs.end(); ++it) {			
			it->close();
		}
		std::cout << "Completed!" << std::endl;
	}
	else {
		ShowHelp();
	}
	return 0;
}