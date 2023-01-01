/*
 * ZernikeSymExpr.h
 * 
 * Copyright 2022 Hong-Yan ZHANG <hongyan@hainnu.edu.cn>
 * 
 * 
 */
 
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


typedef int Type;  // In this work, the "Type" is "int"

typedef unsigned int SingleIndex; // Noll/ZEMAX single index j
typedef struct{ 
	unsigned int n;
	int m;	
}DoubleIndex;                     // BHO double indices (n,m)

Type Abs(Type x);

typedef struct{
	int   ncols;
	char* alignctrl;
	char* caption;
	char* attribname[];	
}TableInfor;

/* If your use sprintf instead of fprintf, please use the array 
 * attribdata to store "$j$", "$n$", "$m$", "$N^m_n$", and
 * "$\Zern_j(\\rho, \\theta)$". In otherwords, you can set
 * attribdata[0] = "$j$", ..., attribdata[4] = "$\Zern_j(\\rho, \\theta)$"
 * Then, the implementation of the procedure GenLaTeXTableLine will be
 * easy with a loop.
 */ 
typedef struct{
	int   ncols;
	char* attribdata[];
}DataInfor; 
	

typedef struct{
	char* orient; // orientation: "portrait" or "landscape"
	char* left;   // "2cm"
	char* right;  // "2cm"
	char* top;    // "2cm"
	char* bottom; // "2cm"
}LayoutInfor;


/******************************************************************** **
 * Procedures for the parameters of Zernike Polynomials
 * ************** BEGIN ********************************************* */
int  CvtNM2K(DoubleIndex pair);
SingleIndex CvtNM2J(DoubleIndex pair);
DoubleIndex CvtJ2NM(SingleIndex j);
double  CalcBinomCoef(double x, unsigned int i);
void CalcRadiPolynomPowerCoef(int* power, int* coef, DoubleIndex pair);
void CalcRadiPolynomPower(int* power,  DoubleIndex pair);
void CalcRadiPolynomCoef(int* coef,  DoubleIndex pair);
/***************** END ********************************************* **/


/***********************************************************************
 * Fundamental procedures for general symbolic polynomials 
 ************   BEGIN  ************************************************/ 

void GenSexprCatSign(FILE*fp, Type coef, int i);
void GenSexprUsgnGeneralTerm(FILE*fp, char* var, char* op, Type coef, int power);
void GenSexprGeneralTerm(FILE*fp, int i, char* var, char* op, Type coef, int power);
void GenSexprPolynom(FILE*fp, char* var, char* op, int* coef, int* power, int size);
/************   END    ************************************************/


/***********************************************************************
 *  Procedures for symbolic Zernike Circular Polynomials 
 * ************* BEGIN ************************************************/ 
void GenSexprRadiPolynom(FILE*fp, DoubleIndex pair, char* var, char* op);
void GenSexprRadiNormCoef(FILE*fp, DoubleIndex pair);
void GenSexprAnguFun(FILE*fp, DoubleIndex pair);
void GenSexprZernikePolynomNM(FILE*fp, DoubleIndex pair);
void GenSexprZernikePolynomJ(FILE*fp, SingleIndex j);
/************   END  **************************************************/


/***********************************************************************
 * Procedures for LaTeX long table environment        
 * ************** BEGIN ***********************************************/
void SetLtabNewline(FILE*fp);
void SetLtabHline(FILE*fp);
void SetLtabBeginCenter(FILE*fp);
void SetLtabBeginLtable(FILE*fp, TableInfor* ptr2tab);
void SetLtabCaption(FILE*fp, TableInfor* ptr2tab);
void SetLtabCaptionContinue(FILE*fp, TableInfor* ptr2tab);
void SetLtabTableHead(FILE* fp, TableInfor* ptr2tab);
void SetLtabEndFirstHead(FILE*fp);
void SetLtabEndHead(FILE*fp);
void SetLtabEndFoot(FILE*fp);
void SetLtabEndLastFoot(FILE*fp);
void SetLtabEndLtable(FILE*fp);  
void SetLtabEndCenter(FILE*fp);
void SetLtabGenLaTeXTableLine(FILE*fp, int rowidx);
void SetLtabGenLaTeXLtable(FILE*fp, int rowbegin, int rowend);
void GenLaTeXLtable(FILE* fp, TableInfor* ptr2tab, int rowbegin, int rowiend);
//void GenLaTeXTableLine(FILE*fp, unsigned int rowidx, DataInfor* ptr2data);
void GenLaTeXTableLine(FILE*fp, SingleIndex j);	// 

/*****************END**************************************************/

/***********************************************************************
 *  Procedures for LaTeX source file 
 * ***************BIGIN************************************************/
void SetLaTeXDocCalss(FILE* fp);
void SetLaTeXDocPreamble(FILE* fp, LayoutInfor *ptr2layout);
void GenKeyContentsInTeXFile(FILE* fp, TableInfor* ptr2tab, int rowbegin, int rowiend);
int  CalcFilenameLength(char* prefix, char* str4jmin, char* str4jmax);
void GenLaTeXFileName(char* filename, char* prefix, char* str4jmin, char* str4jmax);
void GenLaTeXFile(char* filename, TableInfor* ptr2tab, LayoutInfor*ptr2layout, int rowbegin, int rowend);
/******************END*************************************************/
