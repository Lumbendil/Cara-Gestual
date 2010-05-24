#ifndef XMLREADER_H
#define XMLREADER_H
#include "../Expresions/ExpressionManager.h"
#include "../Muscles/MuscleManager.h"
#include "../SPoint3D.h"
#include <stdio.h>
#include <stdlib.h> 
#include <windows.h>
#include <string>

class XMLReader {
public:
	XMLReader(char* path, ExpressionManager* EManager, MuscleManager* MManager);
	~XMLReader();
	void	Read();

private:
	SPoint3D			punt;
	ExpressionManager*	EManager;
	MuscleManager*		MManager;
	FILE				*fitxer;
	
	char				num		[4];
	char				c1;


	void				ReadAtribut();
	void				ReadWord();
	void				ReadChar();
	TypeMuscle			ConvertirNomMuscles();
	TypeExpression		ConvertirNomExpressions();
	void				GuardarNums();
	float				ConvertirNum();
	void				ReadExpressions();
	void				ReadMuscles();
};

#endif