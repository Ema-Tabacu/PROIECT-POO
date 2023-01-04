#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//29.12.2022 updates - am modificat constructorul cu toti param de la UPremium in asa fel incat sa creeze un profil
//pt fiecare utilizator creat
//ma gandesc ca ma complic la citirea din fisier
//mai bn las constructorul asa cum e, nu mai modific clasa UPremium
//01.01.2023 - am sters atributele de la profil din constructorul UPrem, ma concentrez pe clasa profil s o termin
//MODIFICARI 02.01.2023 - AM scris eu fisierul txt cu sesiuni, nu inteleg cum sa pun id ul
// --UTILIzator combinat cu profil
	//sa vad cum implementez functia de adaugare atribute noi daca acelasi id a mai avut interactiuni
//MODIF 03.01.2023 ->  am modificat la cin la UPremium sa afiseze si ce e in Utilizator, afiseaza bine
//am facut functie virtuala pura si clasa abstracta-- imi mai trb functie virtuala

class TipUtilizator {
public:
	virtual void tipUtilizator() = 0;
};

class Utilizator :public TipUtilizator {
	const int id;
	int vitezaTastare; //wpm
	float inactivitateMouse; //secunde
	bool folosesteDiacritice;
	int nrTasteFrecvente;
	float* timpApasareTasta;  //milisec
	static int contor;
public:
	void tipUtilizator() {
		cout << "Utilizator normal";
	}
	Utilizator() :id(contor++) {
		this->vitezaTastare = 0;
		this->inactivitateMouse = 0;
		this->folosesteDiacritice = false;
		this->nrTasteFrecvente = 0;
		this->timpApasareTasta = NULL;

	}
	Utilizator(int vitezaTastare, float inactivitateMouse, bool folosesteDiacritice, int nrTasteFrecvente, float* timpApasareTasta) :id(contor++) {
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
	~Utilizator() {
		if (this->timpApasareTasta != NULL) {
			delete[]this->timpApasareTasta;
		}
	}

	Utilizator(const Utilizator& p) :id(contor++) {
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
		out << p.vitezaTastare << " ";
		out << p.inactivitateMouse << " ";
		out << p.folosesteDiacritice << " ";
		out << p.nrTasteFrecvente << " ";
		for (int i = 0; i < p.nrTasteFrecvente; i++) {
			out << p.timpApasareTasta[i] << " ";
		}
		//cout << endl;
		return out;
	}

	//calcul profil utilizator
	float calculProfilUtilizator(Utilizator& u) {
		float timpTotal = 0;
		int nrErori = 0;

		for (int i = 0; i < u.nrTasteFrecvente; i++) {
			timpTotal += u.timpApasareTasta[i];
		}
		nrErori += u.vitezaTastare / 80; 
		nrErori += u.inactivitateMouse / 10;
		if (u.folosesteDiacritice) {
			nrErori += 0.1 * u.nrTasteFrecvente; 
		}
		float rataErorii = 0;
		rataErorii = nrErori / timpTotal;
		//returnezza ca procent
		if (rataErorii > 0) {
			return 100 - rataErorii * 100;
		}
		else cout << "Introduceti alte valori";

	}

	void comparaInteractiunea(Utilizator& anterior) {
		if (vitezaTastare == anterior.getVitezaTastare() && inactivitateMouse == anterior.getInactivitateMouse() &&
			folosesteDiacritice == anterior.get_folosesteDiacritice() && nrTasteFrecvente == anterior.getNrTasteFrecvente() || id == anterior.id) {
			for (int i = 0; i < anterior.getNrTasteFrecvente(); i++) {
				if (this->timpApasareTasta[i] == anterior.getTimpApasareTasta()[i])
				{
				}
			}
			cout << "Va puteti loga";
		}
		else cout << "Nu va puteti loga";
	}

	//Utilizator& operator+(Utilizator& u) {
	//	Utilizator copie = *this;
	//	delete[]copie.timpApasareTasta;
	//	//copie.nrTasteFrecvente = u.nrTasteFrecvente;
	//	copie.vitezaTastare += u.vitezaTastare;
	//	copie.inactivitateMouse += u.inactivitateMouse;
	//	copie.folosesteDiacritice += u.folosesteDiacritice;
	//	copie.timpApasareTasta = new float[copie.nrTasteFrecvente];
	//	for (int i = 0; i < this->nrTasteFrecvente; i++) {
	//		copie.timpApasareTasta[i] = this->timpApasareTasta[i];
	//	}
	//	for (int i = this->nrTasteFrecvente; i < copie.nrTasteFrecvente; i++) {
	//		copie.timpApasareTasta[i] = u.timpApasareTasta[i - this->nrTasteFrecvente];
	//	}
	//	return copie;
	//}
	///*void comparaInteractiuneaModel(Utilizator& anterior) {
	//	if (this->calculProfilUtilizator(*this) == anterior.calculProfilUtilizator(anterior) || this->id == anterior.id) {
	//		cout << "Va puteti loga";
	//	}
	//	else cout << "Nu va puteti loga.";
	//}*/
	void operator<(Utilizator& u) {
		if (this->vitezaTastare < u.vitezaTastare) {
			cout << "Celalalt utilizator are viteza de tastare mai mare decat a dumneavoastra!";
		}
		else cout << "Aveti viteza de tastare mai mare!";
	}
};

int Utilizator::contor = 0;

class UtilizatorPremium : public Utilizator, public TipUtilizator {
	float pretAbonament;
	int nrBeneficii;
	string* beneficii;
	int nrPostari;
	double* aprecieriLaPostari;
public:

	void tipUtilizator() {
		cout << "Utilizator premium";
	}
	UtilizatorPremium() : Utilizator() {
		this->pretAbonament = 0;
		this->nrBeneficii = 0;
		this->beneficii = new string[nrBeneficii];
		this->nrPostari = 0;
		this->aprecieriLaPostari = NULL;
	}
	UtilizatorPremium(float pretAbonament, int nrBeneficii, string* beneficii, int nrPostari, double* aprecieriLaPostari, int vitezaTastare, //wpm
		float inactivitateMouse, bool folosesteDiacritice, int nrTasteFrecvente, float* timpApasareTasta) :
		Utilizator(vitezaTastare, inactivitateMouse, folosesteDiacritice, nrTasteFrecvente, timpApasareTasta) {
		/*, int vitezaTastare, float inactivMouse,
		bool diacritice, int nrTasteFrecvente, float* timpApasareTasta*/
		this->pretAbonament = pretAbonament;
		this->nrBeneficii = nrBeneficii;
		this->beneficii = new string[nrBeneficii]; //aloc memorie pt ptr
		for (int i = 0; i < this->nrBeneficii; i++) {
			this->beneficii[i] = beneficii[i];
		}
		this->nrPostari = nrPostari;
		this->aprecieriLaPostari = new double[nrPostari];
		for (int i = 0; i < this->nrPostari; i++) {
			this->aprecieriLaPostari[i] = aprecieriLaPostari[i];
		}

	}

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

	//constr copiere
	UtilizatorPremium(const UtilizatorPremium& u) :Utilizator(u) {
		//trebuie apelat const din clasa de baza
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

	//operator =
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
		out << (Utilizator)u;
		return out;
	}

	//istream
	friend istream& operator>>(istream& cit, UtilizatorPremium& u) {
		/*cit >> (Utilizator)u;*/
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
				cit >> u.beneficii[i];
				/*string ben = u.beneficii[i];
				cit >> ben;
				getline(cit, ben);*/
				//cit.get(u.beneficii[i], ",");
				//cit >> u.beneficii[i];
				//getline(cit, u.beneficii[i]);
				//getline(cit, u.beneficii[i]);
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
		cit >> (Utilizator&)u; //-------------------------------------------------------IMPORTANT
		//cit >> (Utilizator)u;
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

	//preincrementare
	//operator + care creste pretul abon
	//RECAPITULARE SUPRAINCARCARE OPERATORI
	UtilizatorPremium& operator++ () {
		this->pretAbonament++;
		return *this;
	}
	// >= pret abonament
	UtilizatorPremium& operator>(UtilizatorPremium& u) {
		if (this->pretAbonament > u.pretAbonament) {
			cout << this->pretAbonament << " e pretul mai mare dintre cele 2";
		}
		else cout << "Mai mic sau egal";
		return *this;
	}
	//operator index
	string& operator[](int pozitie) {
		if (pozitie >= 0 && pozitie < this->nrBeneficii) {
			return this->beneficii[pozitie];
		}
		else {
			string mesaj = "Pozitia nu exista";
			return mesaj;
		}
	}

};

template<typename Tip>
class Gestiune {
	int nr;
	float f;
	Tip obiect;
public:
	Gestiune() {
		this->nr = 0;
		this->f = 0;
		this->obiect = 0;
	}
	Gestiune(int nr, float f, Tip obiect) {
		this->nr = nr;
		this->f = f;
		this->obiect = obiect;
	}

};


void main() {
	Utilizator tmp(48, 17, 1, 1, new float[1] {0.9});
	Gestiune<Utilizator> intFloatsiUser(3, 4.4, tmp);

	//03.01.2023 
	
	//MODIFICARI 02.01.2023 - AM scris eu fisierul txt cu sesiuni, nu inteleg cum sa pun id ul
	//sa vad cum implementez functia de adaugare atribute noi daca acelasi id a mai avut interactiuni
	Utilizator u1, u2, u3, u4, u5;
	float* tasteFrecventeOp = new float[4] {0.9, 0.7, 0.5, 1};
	Utilizator u6(45, 13, 1, 4, tasteFrecventeOp);
	Utilizator u7(40, 17, 0, 2, new float[2] {0.2, 0.6});
	u1 < u7;
	//cout << u6 + u7;
	//ifstream citire("Sesiuni.txt", ios::in);
	//citire >> u1 >> u2 >> u1 >> u4 >> u5;
	////cout << u1 << u2 << u3 << u4 << u5;
	////cout << u5;
	////cout << u1.calculProfilUtilizator(u1) << " ";
	////cout << u2.calculProfilUtilizator(u2)<< " ";
	////cout << u3.calculProfilUtilizator(u3) << " ";
	////cout << u4.calculProfilUtilizator(u4) << " ";
	////cout << u5.calculProfilUtilizator(u5) << " ";
	////u1.comparaInteractiunea(u1);
	//u1.comparaInteractiunea(u2);
	////cout << u1.getId() << u2.getId() << u3.getId();
	string* beneficiiUP = new string[3]{ "Reduceri_mai_mari", "VIP", "Livrare_gratis" };
	float* tasteFrecvente = new float[4] {0.9, 0.7, 0.5, 1};
	double* aprecieriPostari = new double[2] {1234, 914};
	//UtilizatorPremium u(99, 3, beneficiiUP, 2, aprecieriPostari, 145, 45, 1, 3, tasteFrecvente);
	////cout << u;

	//citire.close();
	//TipUtilizator* utilizator = new Utilizator;
	//utilizator->tipUtilizator();
	//TipUtilizator* uPremium = new UtilizatorPremium;
	//uPremium->tipUtilizator();

	UtilizatorPremium upremFis(99, 3, beneficiiUP, 2, aprecieriPostari, 112, 2, 1, 3, tasteFrecvente);
	cout <<endl<< upremFis.operator[](2);
	//ofstream fisierUP("UPrem.txt", ios::app);
	////fisierUP << upremFis;
	//cout << upremFis.calculProfilUtilizator(upremFis);
	//ifstream afisareUP("UPrem.txt", ios::app);
	//UtilizatorPremium utilSimpluIFSTREAM;
	//afisareUP >> utilSimpluIFSTREAM;
	//cout << utilSimpluIFSTREAM;

	//upremFis.comparaInteractiunea(u);
	//fisierUP.close();


	string* beneficii = new string[2]{ "No_ads", "Early_access" };
	double* aprecieri = new double[3] {1000, 423, 9021};




	
	delete[]beneficii;
	delete[]aprecieri;
}