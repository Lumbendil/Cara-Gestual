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
		Objecte3D(const char[] file, const int tipus); //Constructor. El tipus seria 1 per a OBJ i 2 per a 3DS. Així seria extensible a mes tipus.
		~Objecte3D(); //El destructor, que alliberaria tota la memoria
		int PuntMesProxim(Point p) const; //Retorna l'identificador del punt de l'objecte mes proxim al punt p.
		void Dibuixar(); //Dibuixa la funció
		Face getCara(int n) const; // Retorna la cara amb index n
		Point getPunt(int n) const; // Retorna el punt amb index n

	private:
		Face *cares;
		Point *punts;
		int nombreCares, nombrePunts;
};

