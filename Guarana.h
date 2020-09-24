#pragma once
#include "Roslina.h"

#define ZWIEKSZENIE_SILY 3
#define PRAWDOPODOBIENSTWO_ROZSIANIA_GUARANY 0.03

class Guarana:public Roslina
{
public:
	Guarana(Swiat* swiat, wspolrzedne polozenie, int wiek = 0, int sila = SILA_ZWYKLYCH_ROSLIN);

	void zapisz(std::ofstream& file) override;
	void nowa_roslina(wspolrzedne polozenie) override;
	void bonusZaZjedzenie(Organizm* zjadajacy) override;
	std::string przedstawSie() override;
};

