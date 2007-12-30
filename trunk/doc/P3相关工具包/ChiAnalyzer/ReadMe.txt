在此感谢03级蒋竞同学以及中科院计算所的张华平和刘群！

//////////////////////////////////////////////////
//////////////////Analyzer切词包//////////////////
//////////////////////////////////////////////////

1.功能描述:
   主要功能是切词：输入一个字符串或一个文件名，输出一个结果字符串，这个字符串中每个中文词之间用空格分隔。

2.接口描述：

所在文件：./Analyzer/Analyzer.h

//*****************************************************************************
//类名称：Analyzer
//定义该类的目的：完成中文分词功能
//类属性：功能类
//*****************************************************************************
class Analyzer{
public:
	//return true if the analyzer is ready, should be invoked first.
	bool init();

	//the input is a std::string to be processed, sSource; 
	//the output is saved in sResult
    	bool processString(const std::string &sSource, std::string &sResult);

    	//the input is the path of the file to be processed, sFilePath;
    	//the output is saved in sResult
    	bool processFile(const std::string &sFilePath, std::string &sResult);
}; 

3.用法

使用前请将以下目录拷贝到自己的源代码目录
//对分词核心的包装，供方便使用
Analyzer
//以下是中科院提供的分词核心的源代码
Data
Result
Segment
Tag
Unknown
Utility

接口使用前请包含如下文件
#include "./Analyzer/Analyzer.h"
#include "./Analyzer/Analyzer.cpp"

调用例子详见testAnalyzer.cpp
