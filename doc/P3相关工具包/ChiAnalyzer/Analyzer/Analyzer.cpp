#include "Analyzer.h"
#include <io.h>
#include <string>
#include <fstream>
#include <iostream>

Analyzer::Analyzer(){}
Analyzer::~Analyzer() {}

//*****************************************************************************
//�������ƣ�init()
//����������������ʼ���ִʹ��ߣ����ʵ�λ���Ƿ���ȷ
//����ֵ��//
//���������������//
//���������������//
//*****************************************************************************
bool Analyzer::init() {
	m_bValid = false;
	//�����ļ�����
	char sDataFiles[][40]={"data\\BigramDict.dct",	//BigGram Dict
		                   "data\\coreDict.dct",	//Core Dict
						   "data\\lexical.ctx",
		                   "data\\nr.dct",
						   "data\\nr.ctx",
		                   "data\\ns.dct",
						   "data\\ns.ctx",
		                   "data\\tr.dct",
						   "data\\tr.ctx",
						   ""
	};
	//�������ļ�����Ч��
	for (int i = 0; sDataFiles[i][0]; i++) {//��̽�����ļ�
		if((_access( sDataFiles[i], 0 )) == -1) {//����ʧ��
			return false;
			break;
		}
	}
	//�����ļ����ͨ�� �ֵ�ȫ����Ч
	if (i == 9) return m_bValid=true;
	return false;
}




//*****************************************************************************
//�������ƣ�bool	isValid()
//��������������������Ч�Լ��
//��������֮ǰ��Ԥ��������//
//���غ�Ĵ���//
//����ֵ��boolean
//���������������
//���������������
//*****************************************************************************
bool Analyzer::isValid() const {
	return this->m_bValid;
}

bool Analyzer::processString(const std::string &sSource, std::string &sResult) {
    if (!isValid())
		return false;
    char *sRe = new char[sSource.size() * 2];
	//�ִʽ������
	if (!( m_Result.ParagraphProcessing(sSource.c_str(), sRe)))
		return false;
    sResult=sRe;
	delete[]sRe;
	//����������
    
	return true;
	
}

bool Analyzer::processFile(const std::string &sFileName, std::string &sResult) {
	if (!isValid())
		return false;
	//--------------------------------------------------
	//				�ļ���鲿��
	//--------------------------------------------------
	ifstream input(sFileName.c_str(), ios::binary|ios::in);
	//����ļ������
	if (! (input.is_open())) {
		cout<<"Cannot open file: "<<sFileName<<endl;
		return false;
	}
	//--------------------------------------------------
	//				�ļ�������ȡ����
	//--------------------------------------------------
	//��ȡ�ļ�����
	std::string sSource = "";
	{
		//��ʱ����
		std::string buff = "";
		do{
			input>>buff;
			sSource += buff + " ";
		}while(!input.eof());
		input.close();
	}
	//---------------------------------------------------
	//				�ִʼ����������
	//---------------------------------------------------
	//���ļ����ݷִʴ���
	if (!(processString(sSource, sResult))) {
		//�ִʷ����쳣
		cout<<"Segment Error!: "<<sFileName<<endl;
		return false;
	}
	return true;
}

