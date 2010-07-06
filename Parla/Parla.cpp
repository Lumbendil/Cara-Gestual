#include "../stdafx.h"
#include "Parla.h"
#include "Subtitles.h"
#include "../PracticaView.h"
#include "../Timer/Timer.h"


CParla::CParla(Animation* an)
{
	animacio = an;
	text = "Hola a tothom!";
	parlant = false;
	index = 0;
	transitionTime = 1.f;
	totalTime = 0.02f;
}

CParla::~CParla()
{
}

void CParla::SetTextToTalk(char *text)
{
	this->text = text;
}

void CParla::SetVelocity(float transitionT, float totalT)
{
	transitionTime = transitionT;
	totalTime = totalT;
}

void CParla::StartTalk()
{
	TypeExpression expressio;
	index = 0;

	parlant = true;

	//Posa una expressió inicial
	animacio->SetTime(transitionTime, totalTime);
	animacio->StartAnimation(NEUTRE);
	animacio->FinalizeAnimation();

	if (text != NULL)
	{	
		do
		{
			expressio = ParseCharacter(text[index]);
			++index;
		}while (expressio == NONE_EXPRESSION && text[index] != NULL);

		if (text[index] != NULL)
		{
			animacio->SetTime(transitionTime, totalTime);
			animacio->StartAnimation(expressio);
		}
	}
}

void CParla::NextTalk()
{
	TypeExpression expressio;

	parlant = true;
	if (text[index] != NULL)
	{	
		do
		{
			expressio = ParseCharacter(text[index]);
			++index;
		}while (expressio == NONE_EXPRESSION && text[index] != NULL);

		if (text[index] != NULL)
		{
			animacio->SetTime(transitionTime, totalTime);
			animacio->StartAnimation(expressio);
		}
		else
		{
			if (text[index] == NULL && text[index -1] != NULL)
			{
				animacio->SetTime(transitionTime, totalTime);
				animacio->StartAnimation(NEUTRE);
			}
			else
			{
				FinalizeTalk();
			}
		}
	}
	else
	{
		FinalizeTalk();
	}
}

void CParla::FinalizeTalk()
{
	index = 0;
	parlant = false;
}

TypeExpression CParla::ParseCharacter(const char c)
{
	if (strncmp(&c,"a",1)==0 || strncmp(&c,"A",1)==0)
	{
		return A;
	} 
	else if (strncmp(&c,"e",1)==0 || strncmp(&c,"E",1)==0)
	{
		return E;
	}
	else if (strncmp(&c,"i",1)==0 || strncmp(&c,"I",1)==0)
	{
		return I;
	}
	else if (strncmp(&c,"o",1)==0 || strncmp(&c,"O",1)==0)
	{
		return O;
	}
	else if (strncmp(&c,"u",1)==0 || strncmp(&c,"U",1)==0)
	{
		return U;
	}
	else if (strncmp(&c,"m",1)==0 || strncmp(&c,"M",1)==0 || 
			 strncmp(&c,"b",1)==0 || strncmp(&c,"B",1)==0 ||
			 strncmp(&c,"p",1)==0 || strncmp(&c,"P",1)==0 )
	{
		return BILABIAL;
	}
	else if (strncmp(&c,"t",1)==0 || strncmp(&c,"T",1)==0)
	{
		return NEUTRE;
	}
	else
	{
		return NONE_EXPRESSION;
	}
}

bool CParla::IsTalking()
{
	return parlant;
}

void CParla::TalkElapsed()
{
	TypeExpression expressio;
	index = 0;
	float time;
	float StopTime;

	parlant = true;
	if (text != NULL)
	{	
		do
		{
			time = 0.f;
			StopTime = 0.f;
			Timer::GetInstance()->ResetTimer();
			do
			{
				expressio = ParseCharacter(text[index]);
				++index;
				StopTime += 0.2f;
			}while (expressio == NONE_EXPRESSION && text[index] != NULL);

			if (text[index] != NULL)
			{
				if (StopTime > 0.2f)
					animacio->SetTime(transitionTime, totalTime*2);
				else
					animacio->SetTime(transitionTime, totalTime);

				animacio->StartAnimation(expressio);
			}
			while (time < StopTime)
			{
				time += Timer::GetInstance()->GetElapsedTime();
			}
			
		}while (text[index] != NULL);
	}
	FinalizeTalk();
}