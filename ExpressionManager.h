#ifndef EXPMANAGER_H
#define	EXPMANAGER_H

#include "Expression.h"
#include "MuscleManager.h"
#include "SPoint3D.h"

#define NEXPRESSIONS 5
//NONE �s l'�ltim element ja que l'array arriba a l'element N-1.
//NONE �s per definir una expressi� quan no hi ha cap expressi� seleccionada.


enum TypeExpression {TRIST, ALEGRE, ENFADAT, SERIOS, SORPRES, NONE_EXPRESSION};


class ExpressionManager
{
private:
	
	Expression**	Expressions;
	int				numExpressions;

public:
	
	ExpressionManager(MuscleManager* MMan);
	~ExpressionManager();
	
	//Posa tots els muscles de l'expressi� sense moviment
	void			resetExpression			( TypeExpression nameExpression );

	//Modifica el moviment d'un muscle que pertany a una expressi� concreta
	void			modifyMuscleExpression	( TypeExpression nameExpression, TypeMuscle nameMuscle, SPoint3D movement );
	
	// Mou els muscles de l'expressi� desitjada
	void			RenderExpression		( TypeExpression nameExpression );

	Expression**	getExpressionList		( void );
	int				getNumExpressions		( void );

};

#endif