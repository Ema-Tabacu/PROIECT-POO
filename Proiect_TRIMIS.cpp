#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

class Exceptie {
};

template <class T>
class Forum {
	string intrebare;
	int nrRaspunsuri;
	string* raspunsuri;
	T* utilizatori; //care au raspuns
public:
	Forum(string intrebare, int nrRaspunsuri, string* raspunsuri, T* utilizatori) {
		this->intrebare = intrebare;
		this->nrRaspunsuri = nrRaspunsuri;
		this->raspunsuri = new string[this->nrRaspunsuri];
		for (int i = 0; i < this->nrRaspunsuri; i++) {
			this->raspunsuri[i] = raspunsuri[i];
		}
		this->utilizatori = new T[nrRaspunsuri];  //presupun ca fiecare utilizator a rasp o singura data
		for (int i = 0; i < this->nrRaspunsuri; i++) {
			this->utilizatori[i] = utilizatori[i];
		}
	}

	Forum(const Forum& f) {
		this->intrebare = f.intrebare;
		this->nrRaspunsuri = f.nrRaspunsuri;
		this->raspunsuri = new string[f.nrRaspunsuri];
		for (int i = 0; i < f.nrRaspunsuri; i++) {
			this->raspunsuri[i] = f.raspunsuri[i];
		}
		this->utilizatori = new T[nrRaspunsuri];
		for (int i = 0; i < this->nrRaspunsuri; i++) {
			this->utilizatori[i] = utilizatori[i];
		}
	}
	~Forum() {
		if (this->raspunsuri != NULL) {
			delete[]this->raspunsuri;
		}
		if (this->utilizatori != NULL) {
			delete[]this->utilizatori;
		}
	}
	Forum& operator=(const Forum& f) {
		if (this->raspunsuri != NULL) {
			delete[]this->raspunsuri;
		}
		if (this->utilizatori != NULL) {
			delete[]this->utilizatori;
		}
		this->intrebare = f.intrebare;
		this->nrRaspunsuri = f.nrRaspunsuri;
		this->raspunsuri = new string[f.nrRaspunsuri];
		for (int i = 0; i < f.nrRaspunsuri; i++) {
			this->raspunsuri[i] = f.raspunsuri[i];
		}
		this->utilizatori = new T[nrRaspunsuri];
		for (int i = 0; i < this->nrRaspunsuri; i++) {
			this->utilizatori[i] = utilizatori[i];
		}
		return *this;
	}
	void setIntrebare(string intrebare) {
		if (intrebare.length() > 2) {
			this->intrebare = intrebare;
		}
	}
	string getIntrebare() {
		return this->intrebare;
	}
	void setNrRaspunsuri(int nrRasp) {
		if (nrRasp >= 0) {
			this->nrRaspunsuri = nrRasp;
		}
	}
	int getNrRaspunsuri() {
		return this->nrRaspunsuri;
	}
	void setRaspunsuri(int nrRasp, string* raspunsuri) {
		if (this->raspunsuri != NULL) {
			delete[]this->raspunsuri;
		}
		if (nrRasp > 0) {
			this->raspunsuri = new string[nrRasp];
			for (int i = 0; i < nrRasp; i++) {
				this->raspunsuri[i] = raspunsuri[i];
			}
		}

		else { throw Exceptie(); }

	}

	string* getRaspunsuri() {
		return this->raspunsuri;
	}

	void setUtilizatori(T* utilizatori, int nrRaspunsuri) {
		if (this->utilizatori != NULL) {
			delete[]this->utilizatori;
		}
		this->utilizatori = new T[nrRaspunsuri];
		for (int i = 0; i < this->nrRaspunsuri; i++) {
			this->utilizatori[i] = utilizatori[i];
		}
	}
	T* getUtilizatori() {
		return this->utilizatori;
	}

	friend istream& operator>> (istream& in, Forum<T>& forum) {
		cout << "Introduceti intrebarea: ";
		getline(in, forum.intrebare);
		cout << "Introduceti numarul de raspunsuri: ";
		in >> forum.nrRaspunsuri;

		forum.raspunsuri = new string[forum.nrRaspunsuri];

		for (int i = 0; i < forum.nrRaspunsuri; i++) {
			cout << "Introduceti raspunsul " << i + 1 << ": ";
			//in.ignore();
			getline(in, forum.raspunsuri[i]);
		}

		forum.utilizatori = new T[forum.nrRaspunsuri];
		for (int i = 0; i < forum.nrRaspunsuri; i++) {
			cout << "Introduceti utilizatorul " << i + 1 << ": ";
			in >> forum.utilizatori[i];
		}
		return in;
	}
	friend ostream& operator<< (ostream& out, const Forum<T>& forum) {
		out << "Intrebare: " << forum.intrebare << endl;
		if (forum.nrRaspunsuri > 0) {
			out << "Numar raspunsuri: " << forum.nrRaspunsuri << endl;
			for (int i = 0; i < forum.nrRaspunsuri; i++) {
				out << "Raspuns " << i + 1 << ": " << forum.raspunsuri[i] << endl;
				out << "de la utilizatorul: " << forum.utilizatori[i] << endl;
			}
		}
		else {
			cout << "Niciun raspuns la intrebare!";
		}
		return out;
	}

	bool operator~ () {
		this->nrRaspunsuri = ~nrRaspunsuri;
		return nrRaspunsuri;
	}

	Forum<T>& operator*= (int n) {
		for (int i = 0; i < nrRaspunsuri; i++) {
			raspunsuri[i] = string(n, '*') + raspunsuri[i] + string(n, '*');
		}
		return *this;
	}

	Forum<T> operator--(int) {
		this->nrRaspunsuri--;
		return *this;
	}

	string operator[](int pozitie) {
		if (pozitie >= 0 && pozitie <= this->nrRaspunsuri) {
			for (int i = 0; i < this->nrRaspunsuri; i++) {
				return this->raspunsuri[pozitie];
			}
		}
		else {
			throw "Pozitia nu exista!";
		}
	}

};

class Persoana {
	char* nume;
public:
	virtual void tipUtilizator() = 0;

	Persoana() {
		this->nume = new char[strlen("Necunoscut") + 1];
		strcpy_s(this->nume, strlen("Necunoscut") + 1, "Necunoscut");
	}
	Persoana(const char* nume) {
		this->nume = new char[strlen(nume) + 1];
		strcpy_s(this->nume, strlen(nume) + 1, nume);
	}

	virtual ~Persoana() {
		delete[]this->nume;
	}
	char* getNume() {
		return this->nume;
	}
	void setNume(const char* nume) {
		if (strlen(nume) > 0) {
			delete[]this->nume;
			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
	}

	Persoana(const Persoana& p) {
		this->nume = new char[strlen(p.nume) + 1];
		strcpy_s(this->nume, strlen(p.nume) + 1, p.nume);
	}

	Persoana& operator=(const Persoana& p) {
		if (this != &p) {
			delete[]this->nume;
			this->nume = new char[strlen(p.nume) + 1];
			strcpy_s(this->nume, strlen(p.nume) + 1, p.nume);
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Persoana& p) {
		out << p.nume;
		return out;
	}
	friend istream& operator>>(istream& inp, Persoana& p) {
		inp >> p.nume;
		return inp;
	}
	friend ofstream& operator<<(ofstream& out, const Persoana& p) {
		out << p.nume;
		return out;
	}
	friend ifstream& operator<<(ifstream& inp, Persoana& p) {
		inp >> p.nume;
		return inp;
	}
	bool operator==(const Persoana& other) const {
		return this->nume == other.nume;
	}

};

class Utilizator : public Persoana {
	const int id;
	int vitezaTastare; //wpm
	float inactivitateMouse; //secunde
	bool folosesteDiacritice;
	int nrTasteFrecvente;
	float* timpApasareTasta;  //milisec
	static int contor;
public:

	void tipUtilizator() {
		cout << "Utilizator normal" << endl;
	}

	Utilizator() :id(contor++), Persoana() {
		this->vitezaTastare = 0;
		this->inactivitateMouse = 0;
		this->folosesteDiacritice = false;
		this->nrTasteFrecvente = 0;
		this->timpApasareTasta = NULL;

	}
	Utilizator(const char* nume, int vitezaTastare, float inactivitateMouse, bool folosesteDiacritice, int nrTasteFrecvente, float* timpApasareTasta) :id(contor++), Persoana(nume) {
		this->vitezaTastare = vitezaTastare;
		this->inactivitateMouse = inactivitateMouse;
		this->folosesteDiacritice = folosesteDiacritice;
		this->nrTasteFrecvente = nrTasteFrecvente;
		this->timpApasareTasta = new float[nrTasteFrecvente];
		for (int i = 0; i < this->nrTasteFrecvente; i++) {
			this->timpApasareTasta[i] = timpApasareTasta[i];
		}
	}
	int getVitezaTastare() {
		return this->vitezaTastare;
	}
	float getInactivitateMouse() {
		return this->inactivitateMouse;
	}
	bool get_folosesteDiacritice() {
		return this->folosesteDiacritice;
	}
	int getNrTasteFrecvente() {
		return this->nrTasteFrecvente;
	}
	float* getTimpApasareTasta() {
		return this->timpApasareTasta;
	}
	int getId() {
		return this->id;
	}
	void setVitezaTastare(int vTast) {
		if (vTast > 0) {
			this->vitezaTastare = vTast;
		}
	}
	void setInactivitateMouse(float mouse) {
		if (mouse > 0) {
			this->inactivitateMouse = mouse;
		}
	}
	void setFolosireDiacritice(bool diacritice) {
		if (diacritice) {
			this->folosesteDiacritice = diacritice;
		}
	}
	void setNrTasteFrecvente(int nrTasteFrecvente) {
		if (nrTasteFrecvente > 0) {
			this->nrTasteFrecvente = nrTasteFrecvente;
		}
	}
	void setTimpApasareTasta(int nrTasteF, float* timpApasareTasta) {
		if (nrTasteF > 0) {
			if (this->timpApasareTasta != NULL) {
				delete[]this->timpApasareTasta;
			}
			this->timpApasareTasta = new float[nrTasteF];
			for (int i = 0; i < nrTasteF; i++) {
				this->timpApasareTasta[i] = timpApasareTasta[i];
			}
		}
	}
	virtual ~Utilizator() {
		if (this->timpApasareTasta != NULL) {
			delete[]this->timpApasareTasta;
		}
	}

	Utilizator(const Utilizator& p) :id(contor++), Persoana(p) {
		this->vitezaTastare = p.vitezaTastare;
		this->inactivitateMouse = p.inactivitateMouse;
		this->folosesteDiacritice = p.folosesteDiacritice;
		this->nrTasteFrecvente = p.nrTasteFrecvente;
		this->timpApasareTasta = new float[this->nrTasteFrecvente];
		for (int i = 0; i < this->nrTasteFrecvente; i++) {
			this->timpApasareTasta[i] = p.timpApasareTasta[i];
		}
	}
	Utilizator& operator=(const Utilizator& p) {
		Persoana::operator=(p);
		if (this != &p) {
			if (this->timpApasareTasta != NULL) {
				delete[]this->timpApasareTasta;
			}
			this->vitezaTastare = p.vitezaTastare;
			this->inactivitateMouse = p.inactivitateMouse;
			this->folosesteDiacritice = p.folosesteDiacritice;
			this->nrTasteFrecvente = p.nrTasteFrecvente;
			this->timpApasareTasta = new float[this->nrTasteFrecvente];
			for (int i = 0; i < this->nrTasteFrecvente; i++) {
				this->timpApasareTasta[i] = p.timpApasareTasta[i];
			}
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Utilizator& p) {
		out << endl << "Nume:" << (Persoana&)p << endl;
		out << "Viteza tastare in cuvinte pe minut: " << p.vitezaTastare << endl;
		out << "Inactivitate medie mouse in secunde:" << p.inactivitateMouse << endl;
		out << (p.folosesteDiacritice ? "Foloseste diacritice" : "Nu foloseste diacritice") << endl;
		out << "Nr taste apasate frecvent: " << p.nrTasteFrecvente << endl;
		out << "Timp de apasare pt fiecare tasta din cele frecvente:";
		for (int i = 0; i < p.nrTasteFrecvente; i++) {
			out << p.timpApasareTasta[i] << " ";
		}
		cout << endl;
		return out;
	}

	friend istream& operator>>(istream& inp, Utilizator& p) {
		cout << "Nume: ";
		inp >> (Persoana&)p;
		cout << "Viteza tastare in cuvinte pe minut: ";
		inp >> p.vitezaTastare;
		cout << "Inactivitate medie mouse in secunde:";
		inp >> p.inactivitateMouse;
		cout << "Foloseste diacritice? 0-NU, 1-DA";
		inp >> p.folosesteDiacritice;
		cout << "Nr taste apasate frecvent: ";
		inp >> p.nrTasteFrecvente;
		cout << "Timp de apasare pt fiecare tasta din cele frecvente(MILISECUNDE):";
		if (p.timpApasareTasta != NULL) {
			delete[]p.timpApasareTasta;
		}
		p.timpApasareTasta = new float[p.nrTasteFrecvente];
		for (int i = 0; i < p.nrTasteFrecvente; i++) {
			inp >> p.timpApasareTasta[i];
		}
		return inp;
	}


	friend ifstream& operator>>(ifstream& inp, Utilizator& p) {
		inp >> (Persoana&)p;
		inp >> p.vitezaTastare;
		inp >> p.inactivitateMouse;
		inp >> p.folosesteDiacritice;
		inp >> p.nrTasteFrecvente;
		if (p.timpApasareTasta != NULL) {
			delete[]p.timpApasareTasta;
		}
		p.timpApasareTasta = new float[p.nrTasteFrecvente];
		for (int i = 0; i < p.nrTasteFrecvente; i++) {
			inp >> p.timpApasareTasta[i];
		}
		return inp;
	}



	friend ofstream& operator<<(ofstream& out, const Utilizator& p) {
		out << (Persoana&)p << " ";
		out << p.vitezaTastare << " ";
		out << p.inactivitateMouse << " ";
		out << p.folosesteDiacritice << " ";
		out << p.nrTasteFrecvente << " ";
		for (int i = 0; i < p.nrTasteFrecvente; i++) {
			out << p.timpApasareTasta[i] << " ";
		}
		return out;
	}

	Utilizator* citesteUSERdinFisier(const string& filename, int nrUtilizatori, Utilizator* u) {

		ifstream fisier(filename);
		for (int i = 0; i < nrUtilizatori; i++) {
			char nume[30];
			fisier >> nume;
			//fisier.get();
			//getline(fisier, nume); 
			u[i].setNume(nume);
			int vitezaTastare;
			fisier >> vitezaTastare;
			u[i].setVitezaTastare(vitezaTastare);
			float inactivitateMouse;
			fisier >> inactivitateMouse;
			u[i].setInactivitateMouse(inactivitateMouse);
			bool folosesteDiacritice;
			fisier >> folosesteDiacritice;
			u[i].setFolosireDiacritice(folosesteDiacritice);
			int nrTasteFrecvente;
			fisier >> nrTasteFrecvente;
			u[i].setNrTasteFrecvente(nrTasteFrecvente);
			float* timpApasareTasta = new float[nrTasteFrecvente];
			for (int i = 0; i < nrTasteFrecvente; i++) {
				fisier >> timpApasareTasta[i];
			}
			u[i].setTimpApasareTasta(nrTasteFrecvente, timpApasareTasta);
		}
		fisier.close();
		return u;
	}
	virtual void adaugaUtilizator() {
		ofstream adaugaInFisier("utilizatoriCreati.txt", ios::app);
		Utilizator u;
		cin >> u;
		adaugaInFisier << u;
		adaugaInFisier.close();
	}

	void afiseazaUtilizatori() {
		int nrUtilizatori = 4;
		Utilizator* usersFisier = new Utilizator[nrUtilizatori];
		usersFisier->citesteUSERdinFisier("sesiuni.txt", nrUtilizatori, usersFisier);
		for (int i = 0; i < nrUtilizatori; i++) {
			cout << usersFisier[i];
			usersFisier[i].tipUtilizator();
			cout << usersFisier[i].calculProfilUtilizator(usersFisier[i]) << " ";
			cout << endl << "----------------------------------------------" << endl;
		}
	}

	double calculProfilUtilizator(const Utilizator& user) {
		double profil = 0;
		profil += user.vitezaTastare / 100 * 20;
		profil -= user.inactivitateMouse / 100 * 20;
		profil += (user.folosesteDiacritice ? 5 : 0);
		profil += user.nrTasteFrecvente / 100 * 10;
		double tApasareTasta = 0;
		for (int i = 0; i < user.nrTasteFrecvente; i++) {
			tApasareTasta += user.timpApasareTasta[i];
		}
		profil += tApasareTasta / 100 * 15;
		if (profil < 0) profil = 0;
		if (profil > 100) profil = 100;
		return profil;
	}


	void comparaInteractiunea(Utilizator& anterior) {
		if (vitezaTastare == anterior.getVitezaTastare() && inactivitateMouse == anterior.getInactivitateMouse() &&
			folosesteDiacritice == anterior.get_folosesteDiacritice() && nrTasteFrecvente == anterior.getNrTasteFrecvente() || id == anterior.id) {
			for (int i = 0; i < anterior.getNrTasteFrecvente(); i++) {
				if (this->timpApasareTasta[i] == anterior.getTimpApasareTasta()[i])
				{
				}
			}
			cout << "Va puteti loga!";
		}
		else cout << "Nu va puteti loga!";
	}

	void operator<(Utilizator& u) {
		if (this->vitezaTastare < u.vitezaTastare) {
			cout << "Celalalt utilizator are viteza de tastare mai mare decat a dumneavoastra!";
		}
		else cout << "Aveti viteza de tastare mai mare!";
	}
	Utilizator& operator++() {
		for (int i = 0; i < this->nrTasteFrecvente; i++) {
			this->timpApasareTasta[i]++;
		}
		return *this;
	}


	Utilizator& operator--(int) {
		Utilizator copie = *this;
		if (this->inactivitateMouse > 0) {
			this->inactivitateMouse--;
		}
		else copie.inactivitateMouse = this->inactivitateMouse;
		return *this;
	}

	Utilizator& operator--() {
		if (this->vitezaTastare > 0) {
			this->vitezaTastare--;
		}
		else cout << "Invalid";
		return *this;
	}
	Utilizator& operator+=(float val) {
		Utilizator copie = *this;
		delete[]this->timpApasareTasta;
		this->nrTasteFrecvente++;
		this->timpApasareTasta = new float[this->nrTasteFrecvente];
		for (int i = 0; i < copie.nrTasteFrecvente; i++) {
			this->timpApasareTasta[i] = copie.timpApasareTasta[i];
		}
		this->timpApasareTasta[this->nrTasteFrecvente - 1] = val;

		return *this;
	}

	void aflaUt(const string& filenameProfil, Utilizator& nec) {
		cin >> nec;
		double profilNecunoscut = nec.calculProfilUtilizator(nec);
		ifstream fisierProf(filenameProfil);
		float nr = 0;
		while (fisierProf >> nr) {
			if (nr == profilNecunoscut) {
				cout << "Profilul introdus " << nec.getNume() << " se potriveste cu un profil din fisier!";
				cout << "Profil : " << nr;
				return;
			}
			nr++;
		}
		cout << "Profil negasit: " << nr;
		fisierProf.close();
	}

};

int Utilizator::contor = 0;

class UtilizatorPremium : public Utilizator {
	float pretAbonament;
	int nrBeneficii;
	string* beneficii;
	int nrPostari;
	double* aprecieriLaPostari;
public:

	void tipUtilizator() {
		cout << "Utilizator premium" << endl;
	}
	void adaugaUtilizator() {
		ofstream adaugaInFisier("utilizatoriCreatiP.txt");
		UtilizatorPremium u;
		cin >> u;
		adaugaInFisier << u;
		adaugaInFisier.close();
	}

	UtilizatorPremium() : Utilizator() {
		this->pretAbonament = 0;
		this->nrBeneficii = 0;
		this->beneficii = new string[nrBeneficii];
		this->nrPostari = 0;
		this->aprecieriLaPostari = NULL;
	}
	UtilizatorPremium(float pretAbonament, int nrBeneficii, string* beneficii, int nrPostari, double* aprecieriLaPostari, const char* nume, int vitezaTastare,
		float inactivitateMouse, bool folosesteDiacritice, int nrTasteFrecvente, float* timpApasareTasta) :
		Utilizator(nume, vitezaTastare, inactivitateMouse, folosesteDiacritice, nrTasteFrecvente, timpApasareTasta) {

		this->pretAbonament = pretAbonament;
		this->nrBeneficii = nrBeneficii;
		this->beneficii = new string[nrBeneficii];
		for (int i = 0; i < this->nrBeneficii; i++) {
			this->beneficii[i] = beneficii[i];
		}
		this->nrPostari = nrPostari;
		this->aprecieriLaPostari = new double[nrPostari];
		for (int i = 0; i < this->nrPostari; i++) {
			this->aprecieriLaPostari[i] = aprecieriLaPostari[i];
		}

	}
	UtilizatorPremium& citesteUSERidinFisier(const string& filename, UtilizatorPremium& u) {
		ifstream fisier(filename);
		if (fisier.is_open()) {
			fisier >> (Utilizator&)u;
			float pret;
			fisier >> pret;
			u.setPretAbonament(pret);
			int nrBeneficii;
			fisier >> nrBeneficii;
			u.setNrBeneficii(nrBeneficii);
			string* beneficiiU = new string[nrBeneficii];
			for (int i = 0; i < nrBeneficii; i++) {
				fisier >> beneficiiU[i];
			}
			u.setBeneficii(beneficiiU, nrBeneficii);
			int nrPostari;
			fisier >> nrPostari;
			u.setNrPostari(nrPostari);
			double* aprecieriU = new double[nrPostari];
			for (int i = 0; i < nrPostari; i++) {
				fisier >> aprecieriU[i];
			}
			u.setAprecieriLaPostari(aprecieriU, nrPostari);

			/*delete[] beneficiiU;
			delete[] aprecieriU;*/
			fisier.close();
		}
		else {
			cerr << "Could not open file " << filename << endl;
		}
		return u;
	}


	//UtilizatorPremium& citesteUSERidinFisier(const string& filename, UtilizatorPremium& u) {
	//	ifstream fisier(filename);
	//		fisier >> (Utilizator&)u;
	//		float pret;
	//		fisier >> pret;
	//		u.setPretAbonament(pret);
	//		int nrBeneficii;
	//		fisier >> nrBeneficii;
	//		u.setNrBeneficii(nrBeneficii);
	//		string* beneficiis = new string[nrBeneficii];
	//		for (int i = 0; i < nrBeneficii; i++) {
	//			fisier >> beneficiis[i];
	//		}
	//		u.setBeneficii(beneficiis, nrBeneficii);
	//		int nrPostari;
	//		fisier >> nrPostari;
	//		u.setNrPostari(nrPostari);
	//		double* aprecieri = new double[nrPostari];
	//		for (int i = 0; i < nrPostari; i++) { //aici pusesem nrbeneficii in loc de nr postari
	//			fisier >> aprecieri[i];
	//		}
	//		u.setAprecieriLaPostari(aprecieri, nrPostari);
	//	
	//	//delete[]beneficii;
	//	//delete[]aprecieriLaPostari;
	//	fisier.close();
	//	return u;
	//	delete[]beneficiis;
	//	delete[]aprecieri;

	//}


	~UtilizatorPremium() {
		if (this->beneficii != NULL) {
			delete[]this->beneficii;
		}
		if (this->aprecieriLaPostari != NULL) {
			delete[]this->aprecieriLaPostari;
		}
	}

	float getPretAbonament() {
		return this->pretAbonament;
	}
	int getNrBeneficii() {
		return this->nrBeneficii;
	}
	string* getBeneficii() {
		return this->beneficii;
	}
	int getNrPostari() {
		return this->nrPostari;
	}
	double* getAprecieriLaPostari() {
		return this->aprecieriLaPostari;
	}
	void setPretAbonament(float pretAb) {
		if (pretAb > 0) {
			this->pretAbonament = pretAb;
		}
	}
	void setNrBeneficii(int nrBeneficii) {
		if (nrBeneficii > 0) {
			this->nrBeneficii = nrBeneficii;
		}
	}

	void setBeneficii(string* beneficii, int nrBeneficii) {
		if (nrBeneficii > 0) {
			if (this->beneficii != NULL) {
				delete[]this->beneficii;
			}
			this->nrBeneficii = nrBeneficii;
			this->beneficii = new string[nrBeneficii];
			for (int i = 0; i < nrBeneficii; i++) {
				this->beneficii[i] = beneficii[i];
			}
		}
	}
	void setNrPostari(int nrPostari) {
		if (nrPostari > 0) {
			this->nrPostari = nrPostari;
		}
	}

	void setAprecieriLaPostari(double* aprecieriLaPostari, int nrPostari) {
		if (nrPostari > 0) {
			if (this->aprecieriLaPostari != NULL) {
				delete[]this->aprecieriLaPostari;
			}
			this->nrPostari = nrPostari;
			this->aprecieriLaPostari = new double[nrPostari];
			for (int i = 0; i < nrPostari; i++) {
				this->aprecieriLaPostari[i] = aprecieriLaPostari[i];
			}
		}
		else cout << "Invalid";
	}

	UtilizatorPremium(const UtilizatorPremium& u) :Utilizator(u) {
		this->pretAbonament = u.pretAbonament;
		this->nrBeneficii = u.nrBeneficii;
		this->beneficii = new string[u.nrBeneficii];
		for (int i = 0; i < u.nrBeneficii; i++) {
			this->beneficii[i] = u.beneficii[i];
		}
		this->nrPostari = u.nrPostari;
		this->aprecieriLaPostari = new double[u.nrPostari];
		for (int i = 0; i < u.nrPostari; i++) {
			this->aprecieriLaPostari[i] = u.aprecieriLaPostari[i];
		}
	}

	UtilizatorPremium& operator=(const UtilizatorPremium& u) {
		Utilizator::operator=(u);
		if (this != &u) {
			if (this->beneficii != NULL) {
				delete[]this->beneficii;
			}
			if (this->aprecieriLaPostari != NULL) {
				delete[]this->aprecieriLaPostari;
			}
			this->pretAbonament = u.pretAbonament;
			this->nrBeneficii = u.nrBeneficii;
			this->beneficii = new string[u.nrBeneficii];
			for (int i = 0; i < u.nrBeneficii; i++) {
				this->beneficii[i] = u.beneficii[i];
			}
			this->nrPostari = u.nrPostari;
			this->aprecieriLaPostari = new double[u.nrPostari];
			for (int i = 0; i < u.nrPostari; i++) {
				this->aprecieriLaPostari[i] = u.aprecieriLaPostari[i];
			}
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, UtilizatorPremium u) {
		out << (Utilizator)u;
		out << "Pret abonament/luna: " << u.pretAbonament << endl;
		out << "Numar beneficii: " << u.nrBeneficii;
		out << " Beneficii: ";
		for (int i = 0; i < u.nrBeneficii; i++) {
			out << u.beneficii[i] << " ";
		}
		out << endl << "Numar postari pe aplicatie: " << u.nrPostari << endl;
		out << "Aprecieri la fiecare postare: ";
		for (int i = 0; i < u.nrPostari; i++) {
			out << u.aprecieriLaPostari[i] << ", ";
		}
		return out;
	}

	friend istream& operator>>(istream& cit, UtilizatorPremium& u) {
		cit >> (Utilizator&)u;
		cout << "Introduceti pretul abonamentului dvs: ";
		cit >> u.pretAbonament;
		cout << "Introduceti nr de beneficii pe care il ofera abonamentul premium: ";
		cit >> u.nrBeneficii;
		if (u.nrBeneficii > 0) {
			cout << "Introduceti beneficiile: ";
			if (u.beneficii != NULL) {
				delete[]u.beneficii;
			}
			u.beneficii = new string[u.nrBeneficii];
			for (int i = 0; i < u.nrBeneficii; i++) {
				/*	cit.getline(buffer,100);*/
				cit >> u.beneficii[i];
				/*u.beneficii[i] = buffer;
				cit.getline(buffer, 100);*/

			}
		}
		cout << "Introduceti nr de postari:";
		cit >> u.nrPostari;
		if (u.nrPostari > 0) {
			cout << "Introduceti aprecierile pt fiecare postare: ";
			if (u.aprecieriLaPostari != NULL) {
				delete[]u.aprecieriLaPostari;
			}
			u.aprecieriLaPostari = new double[u.nrPostari];
			for (int i = 0; i < u.nrPostari; i++) {
				cit >> u.aprecieriLaPostari[i];
			}
		}

		return cit;

	}
	friend ifstream& operator>>(ifstream& cit, UtilizatorPremium& u) {
		cit >> (Utilizator&)u;
		cit >> u.pretAbonament;
		cit >> u.nrBeneficii;
		if (u.beneficii != NULL) {
			delete[]u.beneficii;
		}
		u.beneficii = new string[u.nrBeneficii];
		for (int i = 0; i < u.nrBeneficii; i++) {
			//char buffer[30];
			//cit.getline(buffer, 30, ",");
			//getline(cit,u.beneficii[i]);
			/*getline(cit, u.beneficii[i]);*/
			cit >> u.beneficii[i];
		}
		cit >> u.nrPostari;
		if (u.aprecieriLaPostari != NULL) {
			delete[]u.aprecieriLaPostari;
		}
		u.aprecieriLaPostari = new double[u.nrPostari];
		for (int i = 0; i < u.nrPostari; i++) {
			cit >> u.aprecieriLaPostari[i];
		}
		return cit;
	}

	friend ofstream& operator<<(ofstream& out, UtilizatorPremium& u) {
		out << (Utilizator)u;
		out << u.pretAbonament << " ";
		out << u.nrBeneficii << " ";
		for (int i = 0; i < u.nrBeneficii; i++) {
			out << u.beneficii[i] << " ";
		}
		out << u.nrPostari << " ";
		for (int i = 0; i < u.nrPostari; i++) {
			out << u.aprecieriLaPostari[i] << " ";
		}
		return out;
	}


	UtilizatorPremium& operator++ () {
		this->pretAbonament++;
		return *this;
	}

	UtilizatorPremium& operator>(UtilizatorPremium& u) {
		if (this->pretAbonament > u.pretAbonament) {
			cout << this->pretAbonament << " e pretul mai mare dintre cele 2";
		}
		else cout << "Mai mic sau egal";
		return *this;
	}

	string& operator[](int pozitie) {
		if (pozitie >= 0 && pozitie < this->nrBeneficii) {
			return this->beneficii[pozitie];
		}
		else {
			throw "Pozitia nu exista!";
		}
	}

	UtilizatorPremium& operator-=(float val) {
		this->pretAbonament -= val;
		return *this;
	}

	UtilizatorPremium& operator-(string numeBeneficiu) {
		//sterge beneficiu
		UtilizatorPremium copie = *this;
		bool gasit = 0;
		int pozitie = 0;
		for (int i = 0; i < this->nrBeneficii; i++) {
			if (this->beneficii[i] == numeBeneficiu) {
				gasit = 1;
				pozitie = i;
			}
		}
		if (gasit == 1) {
			int pozDenumireBeneficiu = 0;
			delete[]this->beneficii;
			this->nrBeneficii--;
			this->beneficii = new string[this->nrBeneficii];
			for (int i = 0; i < copie.nrBeneficii; i++) {
				if (i != pozitie) {
					this->beneficii[pozDenumireBeneficiu] = copie.beneficii[i];
				}
			}
		}

		return *this;
	}

	float operator()(string moneda) {
		transform(moneda.begin(), moneda.end(), moneda.begin(), ::toupper);
		if (moneda == "EURO") {
			return this->pretAbonament;
		}
		else if (moneda == "DOLAR") {
			return this->pretAbonament / 0.95; //dolar in momentul actual
		}
		else if (moneda == "LIRA") {
			return this->pretAbonament / 1.13;
		}
		else {
			cout << " ' " << moneda << " ' nu este o moneda valida. Alegeti dintre EURO, DOLAR sau LIRA";
			return 0;
		}
	}

};

template<class T>
class Admin {
	T dateProcesate;
public:
	Admin() {
		this->dateProcesate = 0;
	}
	Admin(T date) {
		this->dateProcesate = date;
	}

	Admin& operator=(const Admin<T>& a) {
		this->dateProcesate = a.dateProcesate;
		return *this;

	}

	T proceseazaDate() {
		this->dateProcesate += 2;
		return this->dateProcesate;
	}
	void setDate(T informatie) {
		if (informatie != NULL) {
			dateProcesate = informatie;
		}
	}

	T getDate() {
		return this->dateProcesate;
	}
	friend ostream& operator<<(ostream& o, Admin& a) {
		o << a.dateProcesate << endl;
		return o;
	}
	~Admin() {

	}
};


void main() {

	float* mariaTastare = new float[4] {0.1, 0.2, 0.4, 0.4};
	float* leoTastare = new float[3] {0.5, 0.6, 0.4};
	float* emaTastare = new float[5] {0.9, 0.3, 0.4, 0.5, 0.2};
	float* iuliaTastare = new float[6] {0.5, 0.2, 0.7, 0.3, 0.4, 0.5};
	float* dianaTastare = new float[2] {0.2, 0.9};
	Utilizator Maria("Maria", 71, 5, 1, 4, mariaTastare);
	Utilizator Leo("Leo", 52, 12, 1, 3, leoTastare);
	Utilizator Ema("Ema", 102, 9, 0, 5, emaTastare);
	Utilizator Iulia("Iulia", 56, 19, 1, 6, iuliaTastare);
	Utilizator Diana("Diana", 80, 13, 0, 2, dianaTastare);
	ofstream sesiuni("sesiuni.txt", ios::app);
	if (sesiuni.is_open()) {
		sesiuni << Maria << Leo << Ema << Iulia << Diana;
	}
	else cout << "eroare";

	ofstream profileUseri("profileUseri.txt", ios::app);
	profileUseri << Maria.calculProfilUtilizator(Maria) << endl;
	profileUseri << Leo.calculProfilUtilizator(Leo) << endl;
	profileUseri << Ema.calculProfilUtilizator(Ema) << endl;
	profileUseri << Iulia.calculProfilUtilizator(Iulia) << endl;
	profileUseri << Diana.calculProfilUtilizator(Diana) << endl;

	string* fup1b = new string[2]{ "Reduceri_20%", "Livrare_Gratuita" };
	string* fup2b = new string[3]{ "CustomizareProfil", "SuportNonStop", "StorageNelimitat" };
	double* aprf = new double[2] {123, 54};
	double* aprf2 = new double[3] {15, 29, 44};
	UtilizatorPremium fup1(34, 2, fup1b, 2, aprf, "UPremium1", 102, 9, 0, 5, emaTastare);
	UtilizatorPremium fup2(29, 3, fup2b, 3, aprf2, "UPremium2", 56, 19, 1, 6, iuliaTastare);

	ofstream premiumUseri("sesiuniUP.txt", ios::app);
	premiumUseri << fup1 << fup2;


	////------------------------------CLASA ABSTRACTA(persoana) + FUNCTIE VIRTUALA PURA-----------------------------------------
	string* beneficiiUP3 = new string[3]{ "Reduceri_mai_mari", "VIP", "Livrare_gratis" };
	float* tasteFrecvente = new float[4] {0.9, 0.7, 0.5, 1};
	double* aprecieriPostari = new double[2] {1234, 914};
	// test functie virtuala pura prin pointeri
	Persoana* pUtilizatorPrem = new UtilizatorPremium(29, 3, beneficiiUP3, 2, aprecieriPostari, "Ionut", 77, 17, 1, 4, tasteFrecvente);
	cout << *pUtilizatorPrem << " ";
	pUtilizatorPrem->tipUtilizator();
	delete[]pUtilizatorPrem;
	//cout << endl << endl;
	int nrUsers = 2;
	Utilizator u1;
	UtilizatorPremium p1;
	Persoana** pUsers = new Persoana * [nrUsers];
	pUsers[0] = &u1;
	pUsers[1] = &p1;
	for (int i = 0; i < nrUsers; i++) {
		pUsers[i]->tipUtilizator();
	}
	delete[]pUsers;
	//
		//------------------------------SET SI GET, Operator = clasa persoana----------------------------------------
	Persoana* pu1 = new Utilizator("Leo", 78, 13, 0, 4, tasteFrecvente);
	Persoana* pu2 = new Utilizator("Neo", 77, 213, 0, 4, tasteFrecvente);
	pu2->setNume("Ionut");
	cout << pu2->getNume() << " ";
	*pu1 = *pu2;
	cout << *pu1 << " ";
	delete pu1, pu2;

	cout << endl << "--------------------------METODE CLASA UTILIZATOR------------------------------" << endl;
	Utilizator user1("User1", 99, 22, 0, 4, tasteFrecvente);

	user1.setFolosireDiacritice(1);
	cout << user1.get_folosesteDiacritice() << " ";
	user1.setInactivitateMouse(45);
	cout << user1.getInactivitateMouse() << " ";
	user1.setNrTasteFrecvente(4);
	cout << user1.getNrTasteFrecvente() << " ";
	user1.setTimpApasareTasta(user1.getNrTasteFrecvente(), tasteFrecvente);
	for (int i = 0; i < user1.getNrTasteFrecvente(); i++) {
		cout << user1.getTimpApasareTasta()[i] << " ";
	}
	user1.setNume("Emilia");
	cout << user1.getNume() << " ";
	user1.setVitezaTastare(64);
	cout << user1.getVitezaTastare() << " ";
	cout << user1.getId() << " " << endl;

	Utilizator prieten = user1;
	prieten.setNume("prieten");
	cout << "CONSTRUCTOR COPIERE UTILIZATOR - " << prieten << endl;
	Utilizator user2;
	user2 = prieten;
	user2.setNume("User2");
	cout << "OPERATOR = UTILIZATOR - " << user2;
	cout << user2.calculProfilUtilizator(user2) << endl;
	Utilizator ul;
	user2.comparaInteractiunea(ul);
	user2.operator+=(1.1); //adauga 1.1 la finalul vectorului
	user2.operator--();  //decrementeaza
	user2.operator==(user1);
	--user2.operator--();
	user2.operator++();
	cout << user2;


	cout << "--------------------METODE UTILIZATOR PREMIUM--------------------------------: " << endl;
	string* beneficiiUP = new string[2]{ "Livrare_gratuita", "Livrare_24ore" };
	double* aprecieriUP = new double[2] {13000, 9153};
	float* timpApasareUP = new float[5] {0.3, 0.5, 0.2, 0.7, 0.9};
	UtilizatorPremium premium1;
	UtilizatorPremium premium2(45, 2, beneficiiUP, 2, aprecieriUP, "PremiumUser2", 78, 34, 0, 5, timpApasareUP);

	cout << premium2.getPretAbonament() << " ";
	cout << premium2.getNrBeneficii() << " ";
	for (int i = 0; i < premium2.getNrBeneficii(); i++) {
		cout << premium2.getBeneficii()[i] << " ";
	}
	cout << premium2.getNrPostari() << " ";
	for (int i = 0; i < premium2.getNrPostari(); i++) {
		cout << premium2.getAprecieriLaPostari()[i] << " ";
	}
	cout << endl << "--------------------OPERATORI clasa PREMIUM--------------------";
	UtilizatorPremium emaPremium(29, 3, beneficiiUP3, 2, aprecieriPostari, "Ema", 99, 22, 0, 4, tasteFrecvente);
	emaPremium.operator[](2); //returneaza valoarea de pe pozita 2
	emaPremium.operator()("lira"); //returneaza pretul abonamentului in lire
	emaPremium.operator-("VIP"); //sterge beneficiul "vip"
	emaPremium.operator-=(3); //
	emaPremium.operator++(); //
	cout << emaPremium << endl;
	cout << "Profil utilizator emaPremium:" << emaPremium.calculProfilUtilizator(emaPremium) << endl;
	emaPremium.comparaInteractiunea(premium2);
	cout << endl;
	emaPremium.comparaInteractiunea(emaPremium);

	int nrUtilizatori = 4;
	Utilizator* usersFisier = new Utilizator[nrUtilizatori];
	usersFisier->citesteUSERdinFisier("sesiuni.txt", nrUtilizatori, usersFisier);
	for (int i = 0; i < nrUtilizatori; i++) {
		cout << usersFisier[i];
		usersFisier[i].tipUtilizator();
		cout << usersFisier[i].calculProfilUtilizator(usersFisier[i]) << " ";
		cout << endl << "----------------------------------------------" << endl;
	}

	//ofstream fisPrem("sesiuniUP.txt");
	//UtilizatorPremium numePremium(56, 2, beneficiiUP, 2, aprecieriPostari, "numePremium", 45, 12, 0, 2, new float[2] {0.3, 0.4});
	//fisPrem << numePremium;
	//fisPrem.close();

	//UtilizatorPremium premiumFisier;
	//premiumFisier.citesteUSERdinFisier("sesiuniUP.txt", premiumFisier);
	//cout << endl << "PREMIUM user citit din fisierul sesiuniUP:" << premiumFisier;


	cout << endl << "-------------------CLASA FORUM---------------------- " << endl;
	Utilizator* rForum = new Utilizator[3];
	rForum[0] = Utilizator("CINEVADestept", 45, 12, false, 1, new float[1] {0.2});
	rForum[1] = Utilizator("User18932793", 41, 12, true, 1, new float[1] {0.2});
	rForum[2] = UtilizatorPremium(34, 1, new string[1]{ "VIP" }, 1, new double[1] {23}, "Userr18932793", 41, 12, true, 1, new float[1] {0.2}); //face down cast

	Forum<Utilizator> adunare("Cat face 2+2?", 3, new string[3]{ "patru", "sapte", "2" }, rForum);
	cout << adunare;
	cout << adunare.getIntrebare() << " " << endl;
	cout << adunare.getNrRaspunsuri() << "raspunsuri " << endl;

	for (int i = 0; i < 3; i++) {
		cout << adunare.getRaspunsuri()[i] << " ";
		cout << adunare.getUtilizatori()[i];
		rForum[i].tipUtilizator();
	}
	//try {
	//	adunare.setRaspunsuri(-2, new string[2]{ "sd", " s" });
	//}
	//catch (Exceptie ex) {
	//	cout << "Nr de raspunsuri invalid!";
	//}

	cout << " -------------------- Operatori pt clasa template -----------------------";
	adunare *= (3);   //adauga cate 3 stelute in jurul raspunsului
	cout << adunare;
	adunare--;  //decrementeaza nr de raspunsuri
	cout << adunare;
	cout << adunare[1]; //returneaza raspunsul de pe pozitia 1
	cout << ~adunare << endl;  //nrRaspunsuri=0
	delete[]rForum;
	//

	 // cout << "-------------------Clasa Template ADMIN----------------------------------";
	Admin<int> intDate;
	intDate.setDate(3);
	cout << "int =" << intDate.proceseazaDate();

	Admin<double> doubleDate;
	doubleDate.setDate(52.1);
	cout << " float = " << doubleDate.proceseazaDate();

	Utilizator simplu("CINEVADestept", 65, 2, true, 1, new float[1] {0.8});
	Admin<Utilizator> asimplu(simplu);
	cout << asimplu;
	cout << asimplu.proceseazaDate();


	//--------------------------ALTE METODE----------------------
	Utilizator random, anonim;
	random.comparaInteractiunea(anonim);
	random.setInactivitateMouse(12);
	cout << random;
	Utilizator* useri7 = new Utilizator[2];
	useri7->citesteUSERdinFisier("sesiuni.txt", 2, useri7);
	for (int i = 0; i < 2; i++) {
		cout << useri7[i] << " ";
	}

	UtilizatorPremium randomPremium;
	randomPremium.setPretAbonament(10);
	cout << randomPremium("euro") << " "; cout << randomPremium("lira") << " "; cout << randomPremium("dolar") << " ";
	anonim.comparaInteractiunea(random);

	//random.aflaUt("profileUseri.txt", random); 
	/*randomPremium.citesteUSERidinFisier("sesiuniUP.txt", randomPremium);*/
	//cout << randomPremium;


	cout << "******MENIU PT GESTIONAREA UTILIZATORILOR******" << endl;
	cout << "===========================================" << endl;
	cout << "[1] Adauga un utilizator" << endl;
	cout << "[2] Adauga un utilizator Premium" << endl;
	cout << "[3] Afiseaza toti utilizatorii din fisierul sesiuni.txt" << endl;
	cout << "[4] Calculeaza profilul unui utilizator" << endl;
	cout << "[5] Verifica daca profilul introdus corespunde unui profil deja existent" << endl;
	cout << "[0] Iesire din program!" << endl;
	cout << "===========================================" << endl;
	cout << "Alegeti o varianta." << endl;
	while (true) {
		Utilizator c1;
		UtilizatorPremium c2;
		int tasta = 0;
		cin >> tasta;

		switch (tasta) {
		case 1:
			system("cls");
			c1.adaugaUtilizator();
			cout << "Utilizator creat!";
			break;

		case 2:
			system("cls");
			c2.adaugaUtilizator();
			cout << "Utilizator premium creat!";
			break;

		case 3:
			system("cls");
			c2.afiseazaUtilizatori();
				break;
		case 4:
			system("cls");
			cin >> c1;
			c1.calculProfilUtilizator(c1);
			cout <<"Profilul utilizatorului este: " << c1.calculProfilUtilizator(c1);
			break;
		case 5:
			system("cls");
			c1.aflaUt("profileUseri.txt", c1);
			break;

		case 0:
			system("cls");
			cout << "La revedere! Iesire din program...";
			exit(0);
			break;

		default:
			cout << "Alegere invalida! Incercati din nou.";
			break;

		}
		int opt;
		cout << endl << "[1]Meniu principal [0] Iesire";
		cin >> opt;
		switch (opt) {
		case 1:
			cout << "******MENIU PT GESTIONAREA UTILIZATORILOR******" << endl;
			cout << "===========================================" << endl;
			cout << "[1] Adauga un utilizator" << endl;
			cout << "[2] Adauga un utilizator Premium" << endl;
			cout << "[3] Afiseaza toti utilizatorii din fisierul sesiuni.txt" << endl;
			cout << "[4] Calculeaza profilul unui utilizator" << endl;
			cout << "[5] Verifica daca un utilizator se gaseste in fisier" << endl;
			cout << "[0] Iesire din program!" << endl;
			cout << "===========================================" << endl;
			cout << "Alegeti o varianta." << endl;
			break;

		case 0:
			system("cls");
			cout << "La revedere! " << endl;
			exit(0);
			break;
		default:
			continue;
		}
	}

	/*delete[]useri7;
	delete[]usersFisier;
	delete[]beneficiiUP3;
	delete[]beneficiiUP;
	delete[]aprecieriPostari;
	delete[]aprecieriUP;
	delete[]timpApasareUP;*/

	/*delete[]emaTastare, leoTastare, dianaTastare, iuliaTastare, mariaTastare;
	delete[]fup1b, fup2b;
}*/
}
