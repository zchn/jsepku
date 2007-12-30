//此部分代码使用 计算所汉语词法分析系统 ICTCLAS
//
//此部分代码为免费使用 版权保护
//
//特在此特别申明
//
//
//Author:   Kevin Zhang (张华平); Qun Liu(刘群)
//
//Inst. of Computing Tech., Chinese Academy of Sciences
//
//Email:    zhanghp@software.ict.ac.cn 
//
//Tel:      +86-10-88455001/5/7 to 714
//////////////////////////////////////////////////////////////////////
//
// SegGraph.h: interface for the CSegGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEGGRAPH_H__E051AD07_F18C_4171_94D6_39742104EB62__INCLUDED_)
#define AFX_SEGGRAPH_H__E051AD07_F18C_4171_94D6_39742104EB62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\\Utility\\Dictionary.h"//Dictionary
#include "DynamicArray.h"//Dynamic array

#define MAX_FREQUENCE   2079997//7528283+329805  //1993123+86874 
#define MAX_SENTENCE_LEN 2000

class CSegGraph  
{
public:
	bool GenerateWordNet(char *sSentence,CDictionary &dictCore,bool	bOriginalFreq=false);
	//Generate the segmentation word net according the original sentence
	//sSentence: the sentence
	//dictCore: core dictionary
	//bool	bOriginalFreq=false: output original frequency
	CSegGraph();
	virtual ~CSegGraph();
	char m_sAtom[MAX_SENTENCE_LEN][WORD_MAXLENGTH];//pAtoms: the buffer for returned segmented atoms
						// Such as a Chinese Char, digit, single byte, or delimiters
	int m_nAtomLength[MAX_SENTENCE_LEN];//Save the individual length of atom in the array
	int m_nAtomPOS[MAX_SENTENCE_LEN];//pAtoms: the POS property 
	unsigned int m_nAtomCount;//The count of atoms

	CDynamicArray m_segGraph;	
	//segGraph: The segmentation word graph
	//Row first array
protected:
	bool AtomSegment(char *sSentence);
	//Segment the atomic members from the original sentence
	//sSentence: the sentence
	//pAtoms: the buffer for returned segmented atoms
	//        Such as a Chinese Char, digit, single byte, or delimiters
};

#endif // !defined(AFX_SEGGRAPH_H__E051AD07_F18C_4171_94D6_39742104EB62__INCLUDED_)
