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
// NShortPath.h: interface for the CNShortPath class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NSHORTPATH_H__817D57F2_F3D8_40C8_A57E_20570862BCB3__INCLUDED_)
#define AFX_NSHORTPATH_H__817D57F2_F3D8_40C8_A57E_20570862BCB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DynamicArray.h"
#include "queue.h"
#include <stdio.h>

class CNShortPath  
{
private:
	CDynamicArray *m_apCost;
	//The number of value kinds
    unsigned int m_nValueKind;
	//The number of vertex in the graph
    unsigned int m_nVertex;
	//The 2-dimension array for the nodes
	CQueue   **m_pParent;
	//The weight of node
	ELEMENT_TYPE **m_pWeight;

public:
	int m_nResultCount;

private:
	void GetPaths(unsigned int nNode,unsigned int nIndex,int **nResult=0,bool bBest=false);

public:
	CNShortPath(CDynamicArray *aCost,unsigned int nValueKind=1);
	virtual ~CNShortPath();

public:
	int Output(int **nResult,bool bBest,int *npCount);
	int ShortPath();

};

#endif // !defined(AFX_NSHORTPATH_H__817D57F2_F3D8_40C8_A57E_20570862BCB3__INCLUDED_)
