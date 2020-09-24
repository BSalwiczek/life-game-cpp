#pragma once
#include "Zwierze.h"

#define SILA_WILKA 9
#define INICJATYWA_WILKA 5

class Wilk: public Zwierze
{
public:
	Wilk(Swiat* swiat, wspolrzedne polozenie, int wiek = 0, int sila = SILA_WILKA);

	std::string przedstawSie() override;
	void zapisz(std::ofstream& file) override;

protected:
	bool rozmnozSie(Organizm* org1, Organizm* org2) override;
};

