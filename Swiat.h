#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>

#include "Organizm.h"
#include "Czlowiek.h"
#include "Trawa.h"
#include "Mlecz.h"
#include "Wilk.h"
#include "Guarana.h"
#include "WilczeJagody.h"
#include "Owca.h"
#include "BarszczSosnowskiego.h"
#include "Lis.h"
#include "Zolw.h"
#include "Antylopa.h"

#define ILOSC_WYPISYWANYCH_OSTATNICH_ZDARZEN 6
#define NAZWA_PLIKU_DO_ZAPISU "save.txt"
#define MAX_DLUGOSC_LINI 100
#define MINIMALNY_WYMIAR 5

using namespace std;

template<typename T> Organizm* createInstance(Swiat* swiat, wspolrzedne polozenie, int wiek, int sila) { return new T(swiat, polozenie, wiek, sila); }

class Swiat
{
public:
	Swiat();
	void wykonajTure();
	void rysujSwiat();
	void czekajNaTure();

	void dodajOrganizm(Organizm* nowy_organizm);
	bool czyPolePoprawne(wspolrzedne polozenie);
	bool czyPoleZajete(wspolrzedne polozenie);
	Organizm* zwrocOrgnizmNaPolu(wspolrzedne polozenie);

	void usunOrganizm(Organizm* organizm);
	void dodajZdarzenie(string tresc);
	bool przesunOrganizm(wspolrzedne skad, wspolrzedne dokad); // zwraca true jesli przesuniecie sie powiodlo

	~Swiat();
private:
	void zapiszSwiat();
	bool wczytajSwiat();
	void ustawKursor(int X, int Y);
	void inicjujPola();
	void inicjujOrganizmy();
	void usunieciePol();
	void usuniecieOrganizmow();
	void wypiszZdarzenia();
	void uporzadkujOrganizmy();
	void inicjujMapeNazwOrganizmow();
	int pobierzWymiarOdUzytkownika();

	int tura;
	int N, M;
	bool save;
	Organizm*** pola;

	std::map<std::string, Organizm * (*)(Swiat*, wspolrzedne, int, int)> mapa_nazw_organizmow;

	vector<Organizm*> organizmy; //posortowane inicjatywa
	deque<string> opis_zdarzen;
};