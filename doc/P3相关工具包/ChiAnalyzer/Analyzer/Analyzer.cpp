#include "Analyzer.h"
#include <io.h>
#include <string>
#include <fstream>
#include <iostream>

Analyzer::Analyzer(){}
Analyzer::~Analyzer() {}

//*****************************************************************************
//函数名称：init()
//函数功能描述：初始化分词工具，审查词典位置是否正确
//返回值：//
//函数的输入参数：//
//函数的输出参数：//
//*****************************************************************************
bool Analyzer::init() {
	m_bValid = false;
	//审查的文件名称
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
	//逐个审查文件的有效性
	for (int i = 0; sDataFiles[i][0]; i++) {//试探访问文件
		if((_access( sDataFiles[i], 0 )) == -1) {//访问失败
			return false;
			break;
		}
	}
	//所有文件审查通过 字典全部有效
	if (i == 9) return m_bValid=true;
	return false;
}




//*****************************************************************************
//函数名称：bool	isValid()
//函数功能描述：类型有效性检查
//函数调用之前的预备条件：//
//返回后的处理：//
//返回值：boolean
//函数的输入参数：
//函数的输出参数：
//*****************************************************************************
bool Analyzer::isValid() const {
	return this->m_bValid;
}

bool Analyzer::processString(const std::string &sSource, std::string &sResult) {
    if (!isValid())
		return false;
    char *sRe = new char[sSource.size() * 2];
	//分词结果错误
	if (!( m_Result.ParagraphProcessing(sSource.c_str(), sRe)))
		return false;
    sResult=sRe;
	delete[]sRe;
	//保存分析结果
    
	return true;
	
}

bool Analyzer::processFile(const std::string &sFileName, std::string &sResult) {
	if (!isValid())
		return false;
	//--------------------------------------------------
	//				文件审查部分
	//--------------------------------------------------
	ifstream input(sFileName.c_str(), ios::binary|ios::in);
	//审查文件打开情况
	if (! (input.is_open())) {
		cout<<"Cannot open file: "<<sFileName<<endl;
		return false;
	}
	//--------------------------------------------------
	//				文件内容提取部分
	//--------------------------------------------------
	//获取文件内容
	std::string sSource = "";
	{
		//临时增量
		std::string buff = "";
		do{
			input>>buff;
			sSource += buff + " ";
		}while(!input.eof());
		input.close();
	}
	//---------------------------------------------------
	//				分词及结果处理部分
	//---------------------------------------------------
	//对文件内容分词处理
	if (!(processString(sSource, sResult))) {
		//分词发生异常
		cout<<"Segment Error!: "<<sFileName<<endl;
		return false;
	}
	return true;
}

