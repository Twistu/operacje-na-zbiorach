#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Zbiory {
	char nazwa;
	string elementy;
};

void PrintSets(vector<Zbiory> &zbiory) {
	for (auto zmienna : zbiory) {
		cout << "Zbior: " << zmienna.nazwa << " z elementami: " << zmienna.elementy << "\n";
	}
}

void PrintSet_z_plikiem(string plik) {
	fstream plikt;
	string wiersze;
	plikt.open(plik, ios::in);
	if (plikt.good() != true)
	{
		cout << "Nie ma takiego pliku lub nie udalo sie go otworzyc!" << endl;
	}
	else {
		while (getline(plikt, wiersze)) {
			cout << wiersze << endl;
		}
	}

	plikt.close();
}

void ReadAll(string plik, vector<Zbiory> &zbiory) {
	fstream plik1;
	string elementy = "\0";
	string wiersz;
	Zbiory tymczasowyZbior;
	plik1.open(plik, std::ios::in | std::ios::out);

	if (plik1.good() != true)
	{
		cout << "Nie ma takiego pliku lub nie udalo sie go otworzyc!" << endl;
	}
	else {
		while (getline(plik1, wiersz)) {		// pętla w której wypełniamy odpowiednio strukture
			tymczasowyZbior.nazwa = wiersz[0];
			for (int j = 5; j < wiersz.length(); j++) {
				if (wiersz[j] == '}') {
					break;
				}
				else if (wiersz[j] == ',') {
					elementy += ' ';
				}
				else if (wiersz[j] == ' ') {
				}
				else {
					elementy += wiersz[j];
				}
			}
			tymczasowyZbior.elementy = elementy;
			elementy = "\0";
			zbiory.push_back(tymczasowyZbior);

		}
	}
	plik1.close();
}

void ReadSet(string nazwa_pliku, char a, vector<Zbiory> &zbiory) {
	fstream plik1;
	string elementy = "\0";
	string wiersz;
	Zbiory tymczasowyZbior;

	plik1.open(nazwa_pliku, std::ios::in | std::ios::out);

	if (plik1.good() != true)
	{
		cout << "Nie ma takiego pliku lub nie udalo sie go otworzyc!" << endl;
	}
	else {
		while (getline(plik1, wiersz)) {		// pętla w której wypełniamy odpowiednio strukture
			if (wiersz[0] == a) {
				tymczasowyZbior.nazwa = wiersz[0];
				for (int j = 5; j < wiersz.length(); j++) {
					if (wiersz[j] == '}') {
						break;
					}
					else if (wiersz[j] == ',') {
						elementy += ' ';
					}
					else if (wiersz[j] == ' ') {
					}
					else {
						elementy += wiersz[j];
					}
				}
				tymczasowyZbior.elementy = elementy;
				elementy = "\0";
				zbiory.push_back(tymczasowyZbior);
			}
		}
	}
	plik1.close();
}

void Delete(char a, vector<Zbiory> &zbiory) {
	for (int i = 0; i < zbiory.size(); i++) {
		if (zbiory[i].nazwa == a) {
			zbiory.erase(zbiory.begin() + i);
		}
	}
}

void Save(vector<Zbiory> &zbiory, string nazwa) {
	fstream plikz;
	char a = ' ';
	char b = '=';
	char c = '{';
	char d = ',';
	char e = '}';

	plikz.open(nazwa, std::ios::out);

	if (plikz.good() != true)
	{
		cout << "Nie udalo sie utworzyc pliku!" << endl;
	}
	else {
		for (auto zmienna : zbiory) {
			plikz << zmienna.nazwa << a << b << a << c;


			for (int j = 0; j < zmienna.elementy.length(); j++) {
				if (zmienna.elementy[j] == ' ') {
					plikz << d << a;
				}
				else {
					plikz << zmienna.elementy[j];
				}
			}
			plikz << e << endl;
		}
	}
	plikz.close();
}

void Operacje(vector<Zbiory> &zbiory, string rownanie) {
	Zbiory zbior1;
	Zbiory zbior2;
	Zbiory str_pom;
	Zbiory pomc;
	str_pom.nazwa = rownanie[0];
	for (auto zmienna : zbiory) {
		for (int j = 0; j < zmienna.elementy.length(); j++) {
			if (rownanie[4] == zmienna.nazwa) {
				zbior1 = zmienna;
				break;
			}
		}
	}
	for (auto zmienna : zbiory) {
		for (int k = 0; k < zmienna.elementy.length(); k++) {
			if (rownanie[8] == zmienna.nazwa) {
				zbior2 = zmienna;
				break;
			}
		}
	}
	string element1 = "\0";
	string element2 = "\0";
	char ppp = rownanie[6];

	zbior1.elementy += ' ';
	zbior2.elementy += ' ';
	if (ppp == '+') {
		for (int i = 0; i < zbior1.elementy.length(); i++) {				// dodanie piewrszego zbioru
			if (zbior1.elementy[i] != ' ') {
				element1 += zbior1.elementy[i];
			}
			else {
				if (str_pom.elementy.length() == 0) {
					str_pom.elementy += element1;
					str_pom.elementy += ' ';
					element1 = "\0";
				}
				else
				{
					for (int j = 0; j < str_pom.elementy.length(); j++) {
						if (str_pom.elementy[j] != ' ') {
							element2 += str_pom.elementy[j];
						}
						else {
							if (strcmp(element1.c_str(), element2.c_str()) == 0) {
								break;
							}
							else {
								if (element1 == "\0") {
									break;
								}
								else {
									str_pom.elementy += element1;
									str_pom.elementy += ' ';
									element1 = "\0";
									element2 = "\0";
								}
							}
						}
					}
				}
			}
		}

		element1 = "\0";
		element2 = "\0";
		for (int i = 0; i < zbior2.elementy.length(); i++) {
			if (zbior2.elementy[i] != ' ') {
				element1 += zbior2.elementy[i];
			}
			else {
				for (int j = 0; j < str_pom.elementy.length(); j++) {
					if (str_pom.elementy[j] != ' ') {
						element2 += str_pom.elementy[j];
					}
					else {
						if (strcmp(element1.c_str(), element2.c_str()) == 0) {
							element1 = "\0";
							element2 = "\0";
							break;
						}
						else {
							if (element1 == "\0") {

							}
							else {
								str_pom.elementy += element1;
								str_pom.elementy += ' ';
								element1 = "\0";
								element2 = "\0";
							}
						}
					}
				}
			}
		}
	}

	element1 = "\0";
	element2 = "\0";
	for (int i = 0; i < str_pom.elementy.length(); i++) {			// usuwa powtorzenia
		if (str_pom.elementy[i] != ' ') {
			element1 += str_pom.elementy[i];
		}
		else {
			for (int j = i + 1; j < str_pom.elementy.length(); j++) {
				if (str_pom.elementy[j] != ' ') {
					element2 += str_pom.elementy[j];
				}
				else {
					if (strcmp(element1.c_str(), element2.c_str()) == 0) {
						str_pom.elementy[j - 1] = ' ';
						str_pom.elementy[j - 1] = '\b';
					}
					element2 = "\0";
				}
			}
			element1 = "\0";
		}
	}





	if (ppp == '-') {
		str_pom.elementy = zbior1.elementy;
		for (int i = 0; i < str_pom.elementy.length(); i++) {
			if (str_pom.elementy[i] != ' ') {
				element1 += str_pom.elementy[i];
			}
			else {
				for (int j = 0; j < zbior2.elementy.length(); j++) {
					if (zbior2.elementy[j] != ' ') {
						element2 += zbior2.elementy[j];
					}
					else {
						if (strcmp(element1.c_str(), element2.c_str()) == 0) {
							str_pom.elementy[i - 1] = ' ';
							str_pom.elementy[i - 1] = '\b';

						}
						element2 = "\0";
					}
				}
				element1 = "\0";
			}
		}
	}
	if (ppp == '*') {
		for (int i = 0; i < zbior1.elementy.length(); i++) {				// dodanie piewrszego zbioru
			if (zbior1.elementy[i] != ' ') {
				element1 += zbior1.elementy[i];
			}
			else {
				for (int j = 0; j < zbior2.elementy.length(); j++) {
					if (zbior2.elementy[j] != ' ') {
						element2 += zbior2.elementy[j];
					}
					else {
						if (strcmp(element1.c_str(), element2.c_str()) == 0) {
							str_pom.elementy += element1;
							str_pom.elementy += ' ';
							element1 = "\0";
							element2 = "\0";
						}
						element2 = "\0";
					}
				}
				element1 = "\0";
			}
		}
	}
	if (ppp == '/') {
		str_pom.elementy += zbior1.elementy;
		str_pom.elementy += zbior2.elementy;

		for (int i = 0; i < zbior1.elementy.length(); i++) {				// elementy wspolne
			if (zbior1.elementy[i] != ' ') {
				element1 += zbior1.elementy[i];
			}
			else {
				for (int j = 0; j < zbior2.elementy.length(); j++) {
					if (zbior2.elementy[j] != ' ') {
						element2 += zbior2.elementy[j];
					}
					else {
						if (strcmp(element1.c_str(), element2.c_str()) == 0) {
							pomc.elementy += element1;
							pomc.elementy += ' ';
							element1 = "\0";
							element2 = "\0";
						}
						element2 = "\0";
					}
				}
				element1 = "\0";
			}
		}
		element1 = "\0";
		element2 = "\0";
		for (int i = 0; i < str_pom.elementy.length(); i++) {
			if (str_pom.elementy[i] != ' ') {
				element1 += str_pom.elementy[i];
			}
			else {
				for (int j = 0; j < pomc.elementy.length(); j++) {
					if (pomc.elementy[j] != ' ') {
						element2 += pomc.elementy[j];
					}
					else {
						if (strcmp(element1.c_str(), element2.c_str()) == 0) {
							str_pom.elementy[i - 1] = ' ';
							str_pom.elementy[i - 1] = '\b';

						}
						element2 = "\0";
					}
				}
				element1 = "\0";
			}
		}


	}

	zbiory.push_back(str_pom);
	//	cout << "Nazwa zbioru= " << str_pom.nazwa << " elementy: "<<str_pom.elementy <<endl;

}

void Polecenia(string pol, vector<Zbiory> &zbiory) {
	int pomocnicza = 0;
	string pomocnicza1 = "\0";
	if (pol == "PrintSets") {
		cout << "Komenda PrintSet bez pliku\n";
		PrintSets(zbiory);
	}
	else {
		for (int i = 0; i < pol.length(); i++) {
			if (pol[i] == ' ') {
				pomocnicza = i;
				break;
			}
		}

		if (pol[2] == '=') {
			cout << "Wykonuje rownanie\n";
			Operacje(zbiory, pol);
		}

		else if (pomocnicza == 4) {
			cout << "Komenda Save\n";
			pomocnicza1 = "\0";
			for (int w = 5; w < pol.length(); w++) {
				pomocnicza1 += pol[w];
			}
			Save(zbiory, pomocnicza1);
		}

		else if (pomocnicza == 6 && pol[0] == 'D') {
			cout << "Komenda Delete\n";
			char pomocnicza2 = pol[7];
			Delete(pomocnicza2, zbiory);
		}

		else if (pomocnicza == 7 && pol[4] == 'A') {
			cout << "Komenda ReadAll\n";
			pomocnicza1 = "\0";
			for (int w = 8; w < pol.length(); w++) {
				pomocnicza1 += pol[w];
			}
			ReadAll(pomocnicza1, zbiory);
		}

		else if (pomocnicza == 7 && pol[4] == 'S') {
			cout << "Komenda ReadSet\n";
			pomocnicza1 = "\0";
			string nazwa_pliku = "\0";
			char a;
			for (int w = 8; w < pol.length(); w++) {
				pomocnicza1 += pol[w];
			}
			for (int wi = 0; wi < pomocnicza1.length(); wi++) {
				if (pomocnicza1[wi] == ' ') {
					a = pomocnicza1[wi + 1];
					break;
				}
				else {
					nazwa_pliku += pomocnicza1[wi];
				}
			}
			ReadSet(nazwa_pliku, a, zbiory);
		}

		else if (pol.length()>9) {
			cout << "Komenda PrintSet z plikiem\n";
			pomocnicza1 = "\0";
			for (int w = 10; w < pol.length(); w++) {
				pomocnicza1 += pol[w];
			}
			PrintSet_z_plikiem(pomocnicza1);

		}

		else if (pol == "exit" || pol == "Exit") {
			cout << "Komenda wyjscia\n";
		}

		else {
			cout << "Nie znana komenda\n";
		}
	}
}



int main() {
	fstream plikr;
	vector<Zbiory>zbiory;
	string polecenie;
	string wiersz;
	bool exit = true;
	string pomocnicza = "\0";

	while (exit) {
		cout << "Wpisz polecenie do wykonania\n";
		getline(std::cin, polecenie);

		if (polecenie[3] == ' '&& polecenie[0] == 'R'&& polecenie[1] == 'u'&& polecenie[2] == 'n') {
			cout << "Komenda Run\n";
			pomocnicza = "\0";
			for (int w = 4; w < polecenie.length(); w++) {
				pomocnicza += polecenie[w];
			}
			plikr.open(pomocnicza, std::ios::in);
			if (plikr.good() != true)
			{
				cout << "Nie udalo sie utworzyc pliku!" << endl;
			}
			else {
				while (getline(plikr, polecenie)) {
					Polecenia(polecenie, zbiory);
				}
			}
		}

		if (polecenie == "exit" || polecenie == "Exit") {
			exit = false;
		}
		Polecenia(polecenie, zbiory);

	}

	plikr.close();
	//system("PAUSE");
	return 0;
}
