#include "file_access.hpp"
#include <iostream>

FileAccess::FileAccess(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: ./<*.exe> <file>" << std::endl;
		exit(1);
	}
	m_sfile.open(argv[1], std::ios::in);
	std::cout << "Opening file....  " << argv[1] << std::endl;
	// If the open failed, report the error and terminate.
	if (!m_sfile) {
		std::cerr << "Source file could not be opened, assembler terminated."
			<< std::endl;
		exit(1);
	}
}

FileAccess::~FileAccess() {
	m_sfile.close();
}


bool FileAccess::GetNextLine(std::string &a_buff) {
	if (m_sfile.eof()) return false;
	getline(m_sfile, a_buff);
	// Return indicating success.
	return true;
}


void FileAccess::rewind() {
	// Clean the end of file flag and go back to the beginning of the file.
	m_sfile.clear();
	m_sfile.seekg(0, std::ios::beg);
}