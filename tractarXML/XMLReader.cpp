#include "../stdafx.h"
#include "XMLReader.h"

char paraula [20];
char atribut [20];

XMLReader::XMLReader(char* path, ExpressionManager* EManager, MuscleManager* MManager) {
	errno_t err;

	if( (err  = fopen_s(&fitxer,path,"r")) !=0 )
	  printf( "The file %s was not opened\n",path );
	else
	  printf( "The file %s was opened\n",path );
	this->EManager = EManager;
	this->MManager = MManager;
}

XMLReader::~XMLReader() {
	//fclose(fitxer);
}

void XMLReader::ReadWord() {
	char c;
	int i=0;
	
	fscanf(fitxer, "%c", &c);
	while(((int) c <47)||((int) c > 122))
	{
		fscanf(fitxer, "%c", &c);
	}

	while((c!='\n')&&(c!=' ')&&(i<=19)&&(c!='\0'))
	{
		memcpy(&paraula[i],&c,1);
		i++;
		fscanf_s(fitxer, "%c", &c);
	}
	//char caracter1 = paraula[0];
	//if (strcmp(&caracter1,"/")==0)
	//{
	//	strcpy(paraula,"/>");
	//	++i;
	//}
	paraula[i] = '\0';
}

void XMLReader::Read() {
	ReadWord();
	if(strncmp(paraula,"<expressions>",11)==0)
	{
		ReadExpressions();
	}
	else if(strncmp(paraula,"<muscles>",9)==0)
	{
		ReadMuscles();
	}
	fclose(fitxer);
}
TypeExpression XMLReader::ConvertirNomExpressions() {
	//{TRIST, ALEGRE, ENFADAT, SERIOS, SORPRES, NONE_EXPRESSION}
	if(strncmp(atribut,"TRIST",5)==0) return TypeExpression(0);
	else if (strncmp(atribut,"ALEGRE",6)==0) return TypeExpression(1);
	else if (strncmp(atribut,"ENFADAT",7)==0) return TypeExpression(2);
	else if (strncmp(atribut,"SERIOS",6)==0) return TypeExpression(3);
	else if (strncmp(atribut,"SORPRES",7)==0) return TypeExpression(4);
	else if (strncmp(atribut,"A",1)==0) return TypeExpression(5);
	else if (strncmp(atribut,"E",1)==0) return TypeExpression(6);
	else if (strncmp(atribut,"I",1)==0) return TypeExpression(7);
	else if (strncmp(atribut,"O",1)==0) return TypeExpression(8);
	else if (strncmp(atribut,"U",1)==0) return TypeExpression(9);
	else if (strncmp(atribut,"BILABIAL",8)==0) return TypeExpression(10);
	else if (strncmp(atribut,"NEUTRE",6)==0) return TypeExpression(11);
	else return TypeExpression(12);
}

TypeMuscle XMLReader::ConvertirNomMuscles() {
	//{ECELLA, DCELLA, INFBOCA, EBOCA, DBOCA, EPARPELLA, DPARPELLA, EGALTA, DGALTA, NONE_MUSCLE}
	if(strncmp(atribut,"ECELLA",6)==0) return TypeMuscle(0);
	else if (strncmp(atribut,"DCELLA",6)==0) return TypeMuscle(1);
	else if (strncmp(atribut,"INFBOCA",7)==0) return TypeMuscle(2);
	else if (strncmp(atribut,"EBOCA",5)==0) return TypeMuscle(3);
	else if (strncmp(atribut,"DBOCA",5)==0) return TypeMuscle(4);
	else if (strncmp(atribut,"EPARPELLA",9)==0) return TypeMuscle(5);
	else if (strncmp(atribut,"DPARPELLA",9)==0) return TypeMuscle(6);
	else if (strncmp(atribut,"EGALTA",6)==0) return TypeMuscle(7);
	else if (strncmp(atribut,"DGALTA",6)==0) return TypeMuscle(8);
	else if (strncmp(atribut,"SUPBOCA",6)==0) return TypeMuscle(9);
	else if (strncmp(atribut,"LATEBOCA",8)==0) return TypeMuscle(10);
	else if (strncmp(atribut,"LATDBOCA",8)==0) return TypeMuscle(11);
	else return TypeMuscle(12);
}

void XMLReader::GuardarNums() {	
	
	int i=0,j,n=0;
	char num[3][20];
	float convertit[3];
	
	while(n < 3) {
		j=0;
		while((atribut[i]!=',')&&(atribut[i]!='\0')) {
			num[n][j] = atribut[i];
			i++;
			j++;
		}
		num[n][j]='\0';
		convertit[n] = atof(num[n]);
		n++;
		i++;
	}

	punt = SPoint3D(convertit[0], convertit[1], convertit[2]);
}

void XMLReader::ReadChar() {
	
	fscanf_s(fitxer, "%c", &c1);
}

void XMLReader::ReadAtribut() {
	char c;
	int i=0;

	//Trobar on comen�a l'atribut
	fscanf_s(fitxer, "%c", &c);
	while(c!='"')
		fscanf_s(fitxer, "%c", &c);
	fscanf_s(fitxer, "%c", &c);
	while(c!='"')
	{
		memcpy(&atribut[i],&c,1);
		i++;
		fscanf_s(fitxer, "%c", &c);
	}
	atribut[i] = '\0';
}

float XMLReader::ConvertirNum() {
	return atof(atribut);
}

void XMLReader::ReadExpressions() {

	char c;
	TypeMuscle numMuscle;
	TypeExpression numExpressio;

	do
	{
		ReadWord();
		//Bucle d'expressions
		while((strncmp(paraula,"</expressio>",12)!=0)&&(strncmp(paraula,"</expressions>",14)!=0)) {

			ReadAtribut(); //Legim el nom de la expressi�
			numExpressio = ConvertirNomExpressions(); //Convertim el nom de la expressio a TypeExpression

			fscanf_s(fitxer, "%c", &c); //Llegim final de tag (>)

			ReadWord();
			//Bucle d'una expressi� concreta
			while(strncmp(paraula,"<muscle",7)==0)
			{
				ReadAtribut(); //Llegim el nom del muscle
				numMuscle = ConvertirNomMuscles(); //Convertim el nom del muscle a TypeMuscle

				ReadAtribut(); //Llegim el vector
				GuardarNums(); //Guardem els punts en la variable punt

				EManager->modifyMuscleExpression(numExpressio, numMuscle, punt);

				ReadWord(); //Llegim final del tag (/>)

				ReadWord(); //Llegim el seg�ent atribut o b� el final de l'expressi�
			}
		}
	}
	while(strncmp(paraula,"</expressions>",14)!=0);
}

void XMLReader::ReadMuscles() {
	char c;
	unsigned int vertex;
	float delta;
	int tamany = 3;
	TypeMuscle numMuscle;

	do
	{
		ReadWord();
		//Bucle de muscles
		while((strncmp(paraula,"</muscle>",9)!=0)&&(strncmp(paraula,"</muscles>",10)!=0)) {

			ReadAtribut(); //Legim el nom del muscle
			numMuscle = ConvertirNomMuscles(); //Convertim el nom de del muscle a TypeMuscle

			fscanf_s(fitxer, "%c", &c); //Llegim final de tag (>)

			ReadWord();
			//Bucle d'un muscle concret
			while(strncmp(paraula,"<param",6)==0)
			{
				ReadAtribut(); //Llegim l'index del vertex
				vertex = (unsigned int) ConvertirNum();

				ReadAtribut(); //Llegim la delta
				delta = ConvertirNum();

				MManager->addVertexMuscle(numMuscle,vertex,delta);

				ReadWord(); //Llegim final del tag (/>)

				ReadWord(); //Llegim el seg�ent atribut o b� el final de l'expressi�
			}
		}
	}
	while(strncmp(paraula,"</muscles>",10)!=0);
}