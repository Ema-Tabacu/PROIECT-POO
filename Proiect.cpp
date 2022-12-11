#include <iostream>
#include <string>
using namespace std;

//constructor implicit, cu parametri, seteri, geteri, << , >> , constr copiere, operator=, 5 operatori


//aplicatie, utilizator, profil
//Realizati o aplicatie de tip consola in C++, care sa permita gestiunea profilelor utilizatorilor unei aplicatii.
//
//Fiecare utilizator este identificat printr - un id unic.
//
//Profilul utilizatorului este deteminat pe baza anumitor caracteristici masurate pentru fiecare utilizator.
// Datele masurate pentru fiecare utilizator sunt citite din fisierul text : sesiuni.txt.
// Datele in fisier sunt organizate dupa o structura standard decisa de fiecare student in parte.
//
//Se presupune ca datele despre fiecare utilizator sunt masurate si exista in acel fisier.

class Persoana {
	char* nume;
	int varsta;
	string job;
public:
	Persoana() {
		this->nume = new char[strlen("Necunoscut") + 1];
		strcpy_s(this->nume, strlen("Necunoscut") + 1, "Necunoscut");
		this->varsta = 0;
		this->job = "";
	}
	Persoana(const char* nume, int varsta, string job) {
		this->nume = new char[strlen(nume) + 1];
		strcpy_s(this->nume, strlen(nume) + 1, nume);
		if (varsta > 0) {
			this->varsta = varsta;
		}
		this->job = job;
	}

	char* getNume() {
		return this->nume;
	}
	int getVarsta() {
		return this->varsta;
	}

	string getJob() {
		return this->job;
	}

	void setNume(const char* nume) {
		if (this->nume != NULL) {
			delete[]this->nume;
		}
		this->nume = new char[strlen(nume) + 1];
		strcpy_s(this->nume, strlen(nume) + 1, nume);
	}

	void setVarsta(int varsta) {
		if (varsta > 10) {
			this->varsta = varsta;
		}
		/*else { 
			this->varsta = varsta;
			cout << endl << "Prea mic pt a utiliza aplicatia la " << varsta << " ani" << endl;

		}*/
	}
	void setJob(string job) {
		if (job.length() > 2 && this->varsta > 18) {
			this->job = job;
		}
	/*	else cout << "Fara job" << endl;*/
	}



	~Persoana() {
		if (this->nume != NULL) {
			delete[]this->nume;
		}
	}

	Persoana(const Persoana& p) {
		this->nume= new char[strlen(p.nume) + 1];
		strcpy_s(this->nume, strlen(p.nume) + 1, p.nume);
		this->varsta = p.varsta;
		this->job = p.job;
	}
	Persoana& operator=(const Persoana& p) {
		if (this != &p) {
			if (this->nume != NULL) {
				delete[]this->nume;
			}
			this->nume = new char[strlen(p.nume) + 1];
			strcpy_s(this->nume, strlen(p.nume) + 1, p.nume);
			this->varsta = p.varsta;
			this->job = p.job;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Persoana& p) {
		out << "Nume: " << p.nume << endl;
		out << "Varsta: " << p.varsta << endl;
		out << "Job: " << p.job << endl;

		return out;
	}

	friend istream& operator<<(istream& in, Persoana &p) {
		char buffer[30];
		cout << "Introduceti numele: ";
		in >> buffer;
		delete[]p.nume;
		p.nume = new char[strlen(buffer) + 1];
		strcpy_s(p.nume, strlen(buffer) + 1, buffer);
		cout << endl << "Introduceti varsta: ";
		in >> p.varsta;
		cout << endl << "Introduceti jobul:";
		in >> p.job;
		return in;
	}



};

class Utilizator:public Persoana {
	const int id;
	static int nrUtilizatori;
	int nrAplicatiiPreferate;
	string* aplicatiiPreferate;
	float* orePetrecutePeFiecareApl;
public:
	//Utilizator():id(1) {
	//	this->nrUtilizatori++;
	//	this->nume = "";
	//	this->varsta = 0;
	//}
	//Utilizator(string nume, int varsta, int id) :id(id) {
	//	this->nrUtilizatori++;
	//	this->nume = nume;
	//	this->varsta = varsta;
	//}


};
int Utilizator::nrUtilizatori = 0;

class Aplicatie {
	string denumire;
	int anInfiintare;

};

enum ModScroll{PageDown, Mouse, Sageti};
class Profil: public Utilizator {
	ModScroll scroll;
	int vitezaTastare; //wpm
	bool folosesteCapsLock;
	int nrTaste;
	float* timpApasareTasta; //milisecunde

	//timp in care a stat pe o anumita pagina, are add block , cate add uri a vazut, medie o pers pe aplicatie, interactiuni in medie, 

};

void main() {
	Persoana p;
	cout << p << endl;
	p.setVarsta(8);
	p.setJob("Actor");
	p.setNume("Marcel");
	cout << p;
	Persoana Deea("Deea", 12, "Student");
	Deea.setVarsta(19);
	cout << Deea;
	
}