#ifndef XMLWRITER_H
#define XMLWRITER_H
#include "../Expresions/ExpressionManager.h"
#include "../Muscles/MuscleManager.h"
#include "../SPoint3D.h"
#include <stdio.h>
#include <stdlib.h> 
#include <windows.h>
#include <string>

class XMLWriter {
public:
	XMLWriter(char* path, ExpressionManager* EManager, MuscleManager* MManager, int i);
	~XMLWriter();
	void	Guardar( void );

private:
	ExpressionManager*	EManager;
	MuscleManager*		MManager;
	FILE				*fitxer;
	int					x;
	TypeExpression ConvertirTypeExpression(int i);
	TypeMuscle ConvertirTypeMuscle(int i);


	void				GuardarMuscles		( void );
	void				GuardarExpresions	( void );	
	char*				ConvertirMuscle		( int i );
	char*				ConvertirExpression	( int i );
};

#endif