#pragma once
#include <iostream>
#include <stdio.h>
#include <conio.h> 
#include "Zwierze.h"

class Swiat;
class Zwierze;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ARROW_CHAR1 224

#define NORMALNA_WIELKOSC_KROKU 1
#define WIELKOSC_KROKU_PO_UZYCIU_UMIEJETNOSCI 2
#define SILA_CZLOWIEKA 5
#define INICJATYWA_CZLOWIEKA 4


using namespace std;

class Czlowiek: public Zwierze
{
public:
	Czlowiek(Swiat* swiat, wspolrzedne polozenie, int wiek = 0, int sila = SILA_CZLOWIEKA);

	void zapisz(std::ofstream& file) override;
	void akcja() override;
	std::string przedstawSie() override;
	bool rozmnozSie(Organizm* org1, Organizm* org2) override;
private:
	int wielkosc_kroku;
	int ile_rund_aktywna_umiejetnosc;
	void setWiekoscKroku(int nowa_wielkosc);
	void sprobujAktywowacUmiejetnosc();
	void obslugaUmiejetnosci();
};

