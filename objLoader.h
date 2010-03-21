// OBJModel.h: Inteface of the class COBJModel.
//
//////////////////////////////////////////////////////////////////////

#ifndef OBJLOADER_H
#define OBJLOADER_H

#define OBJLOADER_CLASS_DECL     __declspec(dllexport)

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glu.h>


// Needed structures

struct Vector3D
{
	float fX;
	float fY;
	float fZ;
};

struct Vector2D
{
	float fX;
	float fY;
};

struct OBJFileInfo
{
	unsigned int iVertexCount;
	unsigned int iTexCoordCount;
	unsigned int iNormalCount;
	unsigned int iFaceCount;
	unsigned int iMaterialCount;
};

struct Face
{
	unsigned int	iNumVertices;
	unsigned int	iMaterialIndex;
	Vector3D		*pVertices;
	Vector3D		*pNormals;
	Vector2D		*pTexCoords;
};

struct Material
{
  char	szName[1024];		 // Name of the material
  char	szTexture[_MAX_PATH];// Filename of the texture
  int	iTextureID;			 // OpenGL name of the texture
  float fDiffuse[3];		 // Diffuse component
  float fAmbient[3];		 // Ambient component
  float fSpecular[3];		 // Specular component
  float fEmmissive[3];		 // Emmissive component
  float fShininess;			 // Specular exponent
};

struct ModelOBJ
{
	OBJFileInfo		*		info;
	Vector3D		*		pVertices;
	Vector3D		*		pNormals;
	Vector2D		*		pTexCoords;
	Face			*		pFaces;
	Material		*		pMaterials;
};


class OBJLOADER_CLASS_DECL COBJModel  
{
  public:
	  void _stdcall DrawModel();
	  bool _stdcall LoadModel(const char szFileName[],unsigned int iDisplayList);
	  _stdcall COBJModel();
	  virtual _stdcall ~COBJModel();
	  void _stdcall COBJModel::EliminaLlista(unsigned int iDisplayList);

	  // Mètodes nous
	  void				COBJModel::FreeMemory				( void );
	  ModelOBJ			COBJModel::GetModel					( void );
	  unsigned int		COBJModel::GetNumVertices			( void );
	  unsigned int		COBJModel::GetNumFaces				( void );
	  unsigned int		COBJModel::GetNumTexCoords			( void );
	  unsigned int		COBJModel::GetNumNormals			( void );
	  unsigned int		COBJModel::GetNumMaterials			( void );
	  bool				COBJModel::ExistModelInMemory		( void );


  private:
	  void _stdcall ReadNextString(char szString[], FILE *hStream);
	  int _stdcall LoadTexture(const char szFileName[_MAX_PATH]);
	  int _stdcall LoadTexture2(const char szFileName[_MAX_PATH]);
	  void _stdcall UseMaterial(const Material *pMaterial);
	  void _stdcall GetTokenParameter(char szString[], const unsigned int iStrSize, FILE *hFile);
	  void _stdcall MakePath(char szFileAndPath[]);
	  bool _stdcall LoadMaterialLib(const char szFileName[], Material *pMaterials,
		  unsigned int *iCurMaterialIndex, char szBasePath[]);
	  void _stdcall RenderToDisplayList(const Face *pFaces, const unsigned int iFaceCount,
		  const Material *pMaterials);
	  void _stdcall GetFaceNormal(float fNormalOut[3], const Face *pFace);
	  void _stdcall ParseFaceString(char szFaceString[], Face *FaceOut, const Vector3D *pVertices,
		  const Vector3D *pNormals, const Vector2D *pTexCoords, const unsigned int iMaterialIndex);
	  void _stdcall GetFileInfo(FILE *hStream, OBJFileInfo *Stat, const char szConstBasePath[]);
 	  void _stdcall GenTexCoords();

	  unsigned int m_iDisplayList;

	  ModelOBJ	  Model;		  // General informations about the model
};


// Callback function for comparing two faces with qsort
static int CompareFaceByMaterial(const void *Arg1, const void *Arg2);

//Returns a newly created COBJModel object. 
OBJLOADER_CLASS_DECL COBJModel* _stdcall InitObject();

//Destroys a COBJModel object
OBJLOADER_CLASS_DECL void _stdcall UnInitObject(COBJModel *obj);

#endif // !defined(AFX_OBJMODEL_H__32C5F722_AD3D_11D1_8F4D_E0B57CC10800__INCLUDED_)
