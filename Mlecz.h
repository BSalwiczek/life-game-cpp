#pragma once
#include "Roslina.h"

#define PRAWDOPODOBIENSTWO_ROZSIANIA_MLECZA 0.04

class Mlecz : public Roslina
{
public:
	Mlecz(Swiat* swiat, wspolrzedne polozenie, int wiek = 0, int sila = SILA_ZWYKLYCH_ROSLIN);

	void zapisz(std::ofstream& file) override;
	void nowa_roslina(wspolrzedne polozenie) override;
	void akcja() override;
	std::string przedstawSie() override;

};
