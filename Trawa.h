#pragma once
#include "Roslina.h"

#define PRAWDOPODOBIENSTWO_ROZSIANIA_TRAWY 0.05

class Trawa: public Roslina
{
public:
	Trawa(Swiat* swiat, wspolrzedne polozenie, int wiek = 0, int sila = SILA_ZWYKLYCH_ROSLIN);

	void zapisz(std::ofstream& file) override;
	void nowa_roslina(wspolrzedne polozenie) override;
	std::string przedstawSie() override;
};

