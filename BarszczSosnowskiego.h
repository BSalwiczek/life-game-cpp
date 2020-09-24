#pragma once
#include "Roslina.h"

#define SILA_BARSZCZU_SOSNOWSKIEGO 10
#define PRAWDOPODOBIENSTWO_ROZSIANIA_SOSNOWSKIEGO 0.02

class BarszczSosnowskiego: public Roslina
{
public:
	BarszczSosnowskiego(Swiat* swiat, wspolrzedne polozenie, int wiek = 0, int sila = SILA_BARSZCZU_SOSNOWSKIEGO);
	void zapisz(std::ofstream& file) override;
	void nowa_roslina(wspolrzedne polozenie) override;
	void akcja() override;
	std::string przedstawSie() override;
private:
	void zabijZwierze(Organizm* organizm);
};

