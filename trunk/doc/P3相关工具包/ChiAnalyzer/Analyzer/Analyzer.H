#ifndef _ANALYZER_H_
#define _ANALYZER_H_

#include "../Result/Result.cpp"
#include "../Unknown/UnknowWord.cpp"
#include "../Tag/Span.cpp"
#include"../Utility/Dictionary.cpp"
#include"../Segment/Segment.cpp"
#include"../Segment/Queue.cpp"
#include"../Segment/SegGraph.cpp"
#include"../Segment/DynamicArray.cpp"
#include"../Segment/NShortPath.cpp"
#include"../Utility/ContextStat.cpp"
#include"../Utility/Utility.cpp"

#include <string>

//*****************************************************************************
//类名称：Analyzer
//定义该类的目的：完成中文分词功能
//类属性：功能类
//*****************************************************************************
class Analyzer{
private:
	bool m_bValid;
	//Segment Class
	CResult m_Result;
	
	bool isValid() const;
public:
	//constructor
	Analyzer();
	
	//destructor
	virtual ~Analyzer();
	
	//return true if the analyzer is ready, should be invoked first.
	bool init();
	
	//the input is a std::string to be processed, sSource; 
	//the output is saved in sResult
    bool processString(const std::string &sSource, std::string &sResult);
    	
    //the input is the path of the file to be processed, sFilePath;
    //the output is saved in sResult
    bool processFile(const std::string &sFilePath, std::string &sResult);
};       

#endif