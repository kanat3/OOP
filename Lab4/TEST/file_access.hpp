#pragma once
#include <fstream>
#include <stdlib.h>
#include <string>

class FileAccess {
public:
	// Opens the file.
	FileAccess (int argc, char *argv[]);
	FileAccess (void) {};
	// Closes the file.
	~FileAccess (void);
	// Get the next line from the source file.
	bool GetNextLine(std::string& a_buff);
	// Put the file pointer back to the beginning of the file.
	void rewind();
	bool isEOF (void) {
		if (m_sfile.eof()) {
			return true;
		}
		return false;
	}
private:
	std::ifstream m_sfile;
};