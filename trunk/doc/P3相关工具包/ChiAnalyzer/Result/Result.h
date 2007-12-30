//////////////////////////////////////////////////////////////////////
//
//Result.h: interface for the CResult class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESULT_H__DEB31BCA_0410_4D5E_97EA_78F9B16B8938__INCLUDED_)
#define AFX_RESULT_H__DEB31BCA_0410_4D5E_97EA_78F9B16B8938__INCLUDED_

#include "..\UTILITY\Dictionary.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "..\\Utility\\Dictionary.h"
#include "..\\Segment\\Segment.h"
#include "..\\Tag\\Span.h"
#include "..\\Unknown\\UnknowWord.h"
#define _ICT_DEBUG 0

class CResult  
{
private:
	//Segment class
	CSegment m_Seg;
	//Core dictionary, bigram dictionary
	CDictionary m_dictCore, m_dictBigram;
	//POS tagger
	CSpan m_POSTagger;
	//Person recognition
	CUnknowWord m_uPerson, m_uTransPerson, m_uPlace;

public:
	//Options: SmoothPara
	double m_dSmoothingPara;

	//Different result by different method
	int m_nResultCount;

	//0:Only Segment;1: First Tag; 2:Second Type
	int m_nOperateType;
	//0:PKU criterion;1:973 criterion; 2: XML criterion
	int m_nOutputFormat;

	PWORD_RESULT *m_pResult;

	ELEMENT_TYPE m_dResultPossibility[MAX_SEGMENT_NUM];

public:

	CResult();
	virtual ~CResult();

protected:
	bool Sort();

	//tag POS in PKU mode
	bool PKU2973POS(int nHandle,char *sPOS973);

	bool Adjust(PWORD_RESULT pItem,PWORD_RESULT pItemRet);

	ELEMENT_TYPE ComputePossibility(PWORD_RESULT pItem);

	bool ChineseNameSplit(char *sPersonName,char *sSurname, char *sSurname2,char *sGivenName,CDictionary &personDict);

public:

	bool Processing(char *sSentence, unsigned int nCount);

	bool ParagraphProcessing(const char *sParagraph, char *sResult);

//	bool FileProcessing(char *sFilename, char *sResultFile);
	//The buffer which store the segment and POS result
	//and They stored order by its possibility
	bool Output(PWORD_RESULT pItem, char *sResult, bool bFirstWordIgnore = false);

};

#endif // !defined(AFX_RESULT_H__DEB31BCA_0410_4D5E_97EA_78F9B16B8938__INCLUDED_)