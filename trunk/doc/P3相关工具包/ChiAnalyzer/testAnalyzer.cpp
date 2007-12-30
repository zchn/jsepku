#include "./Analyzer/Analyzer.h"
#include "./Analyzer/Analyzer.cpp"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void testProcessFile();
void testProcessString();

void main() {
	cout<<"***************testProcessString()***************"<<endl;
	testProcessString();
	cout<<"***************testProcessFile()****************"<<endl;
	testProcessFile();

}

void testProcessFile() {
	Analyzer a;
	string sResult="";
	string sFileName;
	sFileName="in.txt";

	if(a.init()) {
		cout<<"input File:"<<sFileName<<endl;
		if (a.processFile(sFileName,sResult)) {
			//处理成功
			cout<<"Proceed Analyze OK."<<endl;
			cout<<sResult<<endl;
			return;
		}
		//处理过程发生问题 或者记录文件不存在
		cout<<"Error Proceeding Analyze."<<endl;
	}
	else
		cout<<"Analyzer init error!"<<endl; 
}

void testProcessString() {
	Analyzer a;
	string sResult="";
	string input="每个源文件和头文件都必须在文件首部的注释中注明设计者姓名";
	if(a.init()) {
		cout<<"input String:"<<input<<endl;
		if (a.processString(input,sResult)) {
			//处理成功
			cout<<"Proceed Analyze OK."<<endl;
			cout<<sResult<<endl;
			return;
		}
		//处理过程发生问题 或者记录文件不存在
		cout<<"Error Proceeding Analyze."<<endl;
	}
	else
		cout<<"Analyzer init error!"<<endl;
}