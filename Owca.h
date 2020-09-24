#pragma once
#include "Zwierze.h"

#define SILA_OWCY 4
#define INICJATYWA_OWCY 4

class Owca: public Zwierze
{
public:
	Owca(Swiat* swiat, wspolrzedne polozenie, int wiek = 0, int sila = 4);

	void zapisz(std::ofstream& file) override;
	std::string przedstawSie() override;
protected:
	bool rozmnozSie(Organizm* org1, Organizm* org2) override;
};

