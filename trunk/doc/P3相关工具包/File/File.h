/*
  File.h : platform-independant represention of a path
  associated: File.cpp
  created: 12/21/2007, WANG Dong
*/

#ifndef  _FILE_H_
#define _FILE_H_

#include <vector>
#include <string>

class File {
public:
	File(const std::string& path);
	virtual ~File();

	//return the path in std::string format
	const std::string& getPath() const { return m_path; }

	//if this is a directory, return true; otherwise, return false.
	bool isDirectory() const;

	//if this is a directory, list all files under it;
	//if not, list itself lazily.
	std::vector<std::string> list() const;

private:
	std::string m_path;
}; 

#endif
