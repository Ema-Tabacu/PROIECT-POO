#include <iostream>
#include <string>
using namespace std;

//clasa abstracta tipUtilizator -return tipUtilizator
//utilizator, utilizatorPremium - derivata, admin, profil + model matematic eficienta 
class Utilizator { //clasa abstracta
	const int id;
	char* username;
	int varsta;
	string email;
	//sau nr postari si nr like uri la postari
public:
	Utilizator() : id(1) {
		this->username = new char[strlen("Necunoscut") + 1];
		strcpy_s(this->username, strlen("Necunoscut") + 1, "Necunoscut");
		this->varsta = 0;
		this->email = "";
	}
	Utilizator(const char* username, int varsta, string email, int newId) :id(newId) {
		this->username = new char[strlen(username) + 1];
		strcpy_s(this->username, strlen(username) + 1, username);
		this->varsta = varsta;
		this->email = email;
	}

	char* getUsername() {
		return this->username;
	}
	int getVarsta() {
		return this->varsta;
	}
	string getEmail() {
		return this->email;
	}
	void setUsername(const char* username) {
		if (strlen(username) > 2) {
			if (this->username != NULL) {
				delete[]this->username;
			}
			this->username = new char[strlen(username) + 1];
			strcpy_s(this->username, strlen(username) + 1, username);
		}
	}
	void setVarsta(int varsta) {
		if (this->varsta > 0) {
			this->varsta = varsta;
		}
	}
	void setEmail(string email) {
		if (this->email.length() > 5) {
			this->email = email;
		}
	}

	/*virtual*/ ~Utilizator() { //virtual pt late binding
		if (this->username != NULL) {
			delete[]this->username;
		}
	}

	friend ostream& operator<<(ostream& out, Utilizator u) {
		out << endl << "Username-ul utilizatorului este: " << u.username << endl;
		out << "Email-ul este: " << u.email << endl;
		out << "Varsta este:" << u.varsta << endl;
		return out;
	}
	friend istream& operator>>(istream& cit, Utilizator u) {
		
		cout << "Username-ul: ";
		if (u.username != NULL) {
			delete[]u.username;
		}
		char buffer[30];
		cit >> buffer;
		u.username = new char[strlen(buffer) + 1];
		strcpy_s(u.username, strlen(buffer) + 1, buffer);
		cout << "Email-ul: ";
		cit >> u.email;
		cout << "Varsta: ";
		cit >> u.varsta;
		return cit;
	}


	//virtual string TipulUtilizatorului() = 0; //functie virtuala 

	//char* getUsername() {
	//	return this->username;
	//}
};

class UtilizatorPremium : public Utilizator {
	float pretAbonament;
	int nrBeneficii;
	string* beneficii;
	int nrPostari;
	double* aprecieriLaPostari;
public:
	UtilizatorPremium(): Utilizator() {
		this->pretAbonament = 0;
		this->nrBeneficii = 0;
		this->beneficii = new string[nrBeneficii];
		this->nrPostari = 0;
		this->aprecieriLaPostari = NULL;
	}
	UtilizatorPremium(float pretAbonament, int nrBeneficii, string* beneficii, int nrPostari, double* aprecieriLaPostari,
		const char* username, int varsta, string email, int newId):Utilizator(username, varsta, email, newId) {
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
	UtilizatorPremium(const UtilizatorPremium& u) {
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

	friend ostream& operator<<(ostream& out, const UtilizatorPremium& u) {
	   // out << (Utilizator)u;
		out << "Pret abonament/luna: " << u.pretAbonament;
		out << "Numar beneficii: " << u.nrBeneficii;
		out << "Beneficii: ";
		for (int i = 0; i < u.nrBeneficii; i++) {
			out << u.beneficii[i] << ", " ;
		}
		out << "Numar postari pe aplicatie:" << u.nrPostari;
		out << "Aprecieri la fiecare postare: ";
		for (int i = 0; i < u.nrPostari; i++) {
			out << u.aprecieriLaPostari[i] << ", ";
		}
		/*	if (i == 1) {
				out << u.aprecieriLaPostari[i] << " la prima postare, ";
			}
			out << u.aprecieriLaPostari[i] << "la a " << i+1 << " postare, ";
		}*/
		return out;
	}

	//istream
	friend istream& operator>>(istream& cit, UtilizatorPremium& u) {
		cout << "Introduceti pretul abonamentului dvs: ";
		cit >> u.pretAbonament;
		cout << "Introduceti nr de beneficii pe care il ofera abonamentul premium: ";
		cit >> u.nrBeneficii;
		cout << "Introduceti beneficiile: ";
		if (u.beneficii != NULL) {
			delete[]u.beneficii;
		}
		u.beneficii = new string[u.nrBeneficii];
		for (int i = 0; i < u.nrBeneficii; i++) {
			cit >> u.beneficii[i];
		}
		cout << "Introduceti nr de postari:";
		cit >> u.nrPostari;
		cout << "Introduceti aprecierile pt fiecare postare: ";
		if (u.aprecieriLaPostari != NULL) {
			delete[]u.aprecieriLaPostari;
		}
		u.aprecieriLaPostari = new double[u.nrPostari];
		for (int i = 0; i < u.nrPostari; i++) {
			cit >> u.aprecieriLaPostari[i];
		}
		
		return cit;
		
	}


	string TipulUtilizatorului() {
		return "Utilizator Premiumm";
	}
	//sau sa fac direct utilizator premium si admin?

};


	//pretPeLuna;
	//enum/ string* beneficii


void main() {
	/*Utilizator* uti = new UtilizatorPremium;
	cout << uti->TipulUtilizatorului();
	cout << uti;
	*/
	/*Utilizator u("Ana", 23, "email@gmail.com", 2);
	cout << u;*/
	
	string* beneficii = new string[2]{ "No ads", "Early access" };
	double* aprecieri = new double[3] {1000, 423, 9021};
	UtilizatorPremium p(99, 2, beneficii, 3, aprecieri, "IoanaPrem", 23, "prem@gmail.com", 4);
	////////////////--------------------------------CE COMENTEZ INSEAMNA CA MERGE DAR NU VREAU SA MI AFISEZE MULT---------------
	//cout << p;
	//UtilizatorPremium p;
	//merg ambele
	//for (int i = 0; i < p.getNrPostari(); i++) {
	//	cout << p.getAprecieriLaPostari()[i] << " ";
	//}
	//for (int i = 0; i < p.getNrBeneficii(); i++) {
	//	cout << p.getBeneficii()[i] << " ";
	//} 
	/*UtilizatorPremium pr;
	pr.setAprecieriLaPostari(aprecieri, -8);
	for (int i = 0; i < pr.getNrPostari(); i++) {
		cout << pr.getAprecieriLaPostari()[i] << " ";
	}*/
	/*UtilizatorPremium uCopie = p;
	cout << uCopie;*/
	UtilizatorPremium a;
	cin >> a;
	cout << a;
	delete[]beneficii;
	delete[]aprecieri;
}