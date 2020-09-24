#pragma once
#include "Zwierze.h"

#define SILA_LISA 3
#define INICJATYWA_LISA 7

class Lis: public Zwierze
{
public:
	Lis(Swiat* swiat, wspolrzedne polozenie, int wiek = 0, int sila = SILA_LISA);

	void zapisz(std::ofstream& file) override;
	std::string przedstawSie() override;
	void akcja() override;
protected:
	bool rozmnozSie(Organizm* org1, Organizm* org2) override;
};

