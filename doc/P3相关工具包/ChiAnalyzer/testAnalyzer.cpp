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
			//����ɹ�
			cout<<"Proceed Analyze OK."<<endl;
			cout<<sResult<<endl;
			return;
		}
		//������̷������� ���߼�¼�ļ�������
		cout<<"Error Proceeding Analyze."<<endl;
	}
	else
		cout<<"Analyzer init error!"<<endl; 
}

void testProcessString() {
	Analyzer a;
	string sResult="";
	string input="ÿ��Դ�ļ���ͷ�ļ����������ļ��ײ���ע����ע�����������";
	if(a.init()) {
		cout<<"input String:"<<input<<endl;
		if (a.processString(input,sResult)) {
			//����ɹ�
			cout<<"Proceed Analyze OK."<<endl;
			cout<<sResult<<endl;
			return;
		}
		//������̷������� ���߼�¼�ļ�������
		cout<<"Error Proceeding Analyze."<<endl;
	}
	else
		cout<<"Analyzer init error!"<<endl;
}