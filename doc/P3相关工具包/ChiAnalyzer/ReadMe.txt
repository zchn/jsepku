�ڴ˸�л03������ͬѧ�Լ��п�Ժ���������Ż�ƽ����Ⱥ��

//////////////////////////////////////////////////
//////////////////Analyzer�дʰ�//////////////////
//////////////////////////////////////////////////

1.��������:
   ��Ҫ�������дʣ�����һ���ַ�����һ���ļ��������һ������ַ���������ַ�����ÿ�����Ĵ�֮���ÿո�ָ���

2.�ӿ�������

�����ļ���./Analyzer/Analyzer.h

//*****************************************************************************
//�����ƣ�Analyzer
//��������Ŀ�ģ�������ķִʹ���
//�����ԣ�������
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

3.�÷�

ʹ��ǰ�뽫����Ŀ¼�������Լ���Դ����Ŀ¼
//�Էִʺ��ĵİ�װ��������ʹ��
Analyzer
//�������п�Ժ�ṩ�ķִʺ��ĵ�Դ����
Data
Result
Segment
Tag
Unknown
Utility

�ӿ�ʹ��ǰ����������ļ�
#include "./Analyzer/Analyzer.h"
#include "./Analyzer/Analyzer.cpp"

�����������testAnalyzer.cpp
