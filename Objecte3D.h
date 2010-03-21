#define TIPUS_OBJ 1
#define TIPUS_3DS 2

typedef struct Point {
	float x,y,z;
};

// Les cares es considera que son triangles.
// Es guarda la ID relacionada a cada punt.
typedef struct Face {
	int punts[3];
};

class Objecte3D {
	public:
		/*
		Constructor.
		El tipus seria 1 per a OBJ i 2 per a 3DS. 
		Així seria extensible a mes tipus.
		*/
		Objecte3D(const char[] file, const int tipus);
		/*
		El destructor, que alliberaria tota la memoria
		*/
		~Objecte3D();
		/*
		Retorna l'identificador del punt de l'objecte mes proxim al
		punt p.
		*/
		int PuntMesProxim(Point p) const; 
		/*
		Dibuixa la funció
		*/
		void Dibuixar(); 
		/*
		Retorna la cara amb index n 
		*/
		Face getCara(int n) const; 
		/*
		Retorna el punt amb index n
		*/
		Point getPunt(int n) const;
		/*
		Canvia el punt n per el nouPunt
		*/
		void editarPunt(int n, Point nouPunt);
	private:
		Face *cares;
		Point *punts;
		int nombreCares, nombrePunts;
		void Objecte3DDeOBJ(const char[] filename);
		void Objecte3DDe3DS(const char[] filename);
};

