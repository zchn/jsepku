/*
  File.cpp : platform-independant represention of a path
  associated: File.h
  created: 12/21/2007, WANG Dong
*/

#include "File.h"	
// PLATFORM
#ifdef _WIN32
#include <windows.h>
#else 
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#endif

using namespace std;

File::File(const string& path) : m_path(path) {}

File::~File() {}

bool File::isDirectory() const {
#ifdef _WIN32
	WIN32_FIND_DATA fd;
    HANDLE h = FindFirstFile(
		m_path.c_str(),  // file name
		&fd);          // data buffer
	FindClose(h);
	return fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
#else 
	struct stat sbuf;
	stat(m_path.c_str(),&sbuf);		
	bool flag;		
	flag = S_ISDIR(sbuf.st_mode);   
	return flag;
#endif
}
	
vector<string> File::list() const {
#ifdef _WIN32
	string path(m_path);
	
    if (path=="\\") 
        path+="*";
    else if (isDirectory())
        path+="\\*";
	
    vector<string> result;
	
    WIN32_FIND_DATA fd;
    HANDLE h = FindFirstFile(
        path.c_str(),  // file name
        &fd);          // data buffer
    bool more = (h != INVALID_HANDLE_VALUE);
    while (more) {
        string name(fd.cFileName);
        if (name != "." && name != "..") result.push_back(name);
        more = FindNextFile(h, &fd);
    }
    FindClose(h);
    return result;
#else
    vector<string> result;	
    int len = m_path.length();
    string path1 = "";
    if (m_path[len-1] != '/')
    {
        path1  = m_path + '/';
    }
    else
    {
        path1 = m_path;
    }
	
    DIR *dp;
    struct dirent *link;
    dp = opendir (path1.c_str());
    if (dp == NULL) {
        fprintf (stderr, "Can't open dir %s.\n", path1.c_str());
        return result;
    }
    string fileName,strChildPath;
    while((link = readdir(dp)) != 0) {
        struct stat st;
        if ((strcmp(link->d_name, ".") == 0)||(strcmp(link->d_name,   "..") == 0))
            continue;
        strChildPath = path1 + link->d_name;
        stat (strChildPath.c_str(), &st);
        if (S_ISDIR(st.st_mode)) {
            strChildPath = path1 + link->d_name;
			result.push_back( (link->d_name) );
        }
        else if (S_ISREG(st.st_mode)) {
            strChildPath = path1 + link->d_name;
            result.push_back( (link->d_name) );
        }
    }
    closedir(dp);
    return result;
#endif
}
	


