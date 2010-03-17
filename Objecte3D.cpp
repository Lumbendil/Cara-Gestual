#include "Objecte3D.h"
#inculde <stdio.h>

Objecte3D::Objecte3D(const char[] filename, int tipus) {
	switch (tipus) {
		case 1: this->Objecte3DDeOBJ(filename);
			break;
		case 2: this->Objecte3DDe3DS(filename);
			break;
		default: printf("Tipus invalid\n");
	}
}
Objecte3D::Objecte3DDe3DS(const char[] filename) {

}
