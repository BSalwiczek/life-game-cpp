#pragma once
#include <cstdlib>
#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>

#define KOLOR_DOMYSLNY 0
#define KOLOR_ZIELONY 2
#define KOLOR_AQUA 3
#define KOLOR_CZERWONY 4
#define KOLOR_FIOLETOWY 5
#define KOLOR_ZOLTY 6
#define KOLOR_BIALY 7
#define KOLOR_JASNA_ZIELEN 10
#define KOLOR_JASNO_CZERWONY 12
#define KOLOR_JASNO_FIOLETOWY 13
#define KOLOR_JASNO_ZOLTY 14

class Swiat;


typedef struct
{
	int x;
	int y;
} wspolrzedne;

class Organizm
{
public:
	virtual void akcja() = 0;
	virtual Organizm* kolizja(Organizm* organizm, bool& powrot_na_miejsca) = 0; //zwraca wskaznik na organizm ktory wygral, NULL jesli oba umieraja lub dojdzie do rozmnozenia
	virtual void rysowanie(HANDLE color) = 0;
	virtual bool czyOdbilAtak(Organizm* organizm) = 0;
	virtual std::string przedstawSie() = 0;
	virtual void zapisz(std::ofstream& file) = 0;
	virtual void bonusZaZjedzenie(Organizm* zjadany) = 0;

	wspolrzedne getPolozenie();
	int getSila();
	int getInicjatywa();
	int getWiek();

protected:
	virtual void postarzejOrganizm() = 0;

	int inicjatywa, wiek, sila, kolor;
	char symbol;
	wspolrzedne polozenie, poprzednie_polozenie;

	Swiat* swiat;
};

struct porownajOrganizmy
{
	bool operator()(Organizm* o1, Organizm* o2)
	{
		if (o1 == nullptr || o2 == nullptr)
			return false;
		// o1 < o2
		if (o1->getInicjatywa() > o2->getInicjatywa())
			return true;
		else if (o1->getInicjatywa() < o2->getInicjatywa())
			return false;
		else
		{
			if (o1->getWiek() > o2->getWiek())
				return true;
			else
				return false;
		}
	}
};