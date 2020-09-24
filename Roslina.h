#pragma once
#include "Organizm.h"
#define ILOSC_PROB_ZNALEZIENIA_DOBREGO_POLA 10
#define SILA_ZWYKLYCH_ROSLIN 0

class Roslina: public Organizm
{
public:
	Roslina(Swiat* swiat, wspolrzedne polozenie);
	void akcja() override;
	Organizm* kolizja(Organizm* organizm, bool& powrot_na_miejsca) override;
	void rysowanie(HANDLE color) override;
	bool czyOdbilAtak(Organizm* atakujacy) override;
	void bonusZaZjedzenie(Organizm* zjadany) override;
	std::string przedstawSie() override;
	void zapisz(std::ofstream& file) override;

protected:
	double prawdopodobienstwo_rozsiania;

	void rozsiejSie();
	virtual void nowa_roslina(wspolrzedne polozenie) = 0;
	void postarzejOrganizm() override;
};

