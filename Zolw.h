#pragma once
#include "Zwierze.h"

#define SZANSA_NA_RUCH_ZOLWIA 25
#define SILA_ODPIERAJACA_ATAK 5
#define SILA_W_WALCE 2
#define INICJATYWA_ZOLWIA 1


class Zolw: public Zwierze
{
public:
	Zolw(Swiat* swiat, wspolrzedne polozenie, int wiek = 0, int sila = SILA_W_WALCE);

	std::string przedstawSie() override;
	void zapisz(std::ofstream& file) override;
	bool czyOdbilAtak(Organizm* atakujacy) override;
	void akcja() override;

protected:
	bool rozmnozSie(Organizm* org1, Organizm* org2) override;

};

