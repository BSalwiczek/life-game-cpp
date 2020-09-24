#pragma once
#include "Zwierze.h"

#define SILA_ANTYLOPY 4
#define INICJATYWA_ANTYLOPY 4

class Antylopa: public Zwierze
{
public:
	Antylopa(Swiat* swiat, wspolrzedne polozenie, int wiek = 0, int sila = SILA_ANTYLOPY);
	void zapisz(std::ofstream& file) override;
	std::string przedstawSie() override;
	Organizm* kolizja(Organizm* organizm, bool& powrot_na_miejsca) override;
	void akcja() override;
protected:
	bool rozmnozSie(Organizm* org1, Organizm* org2) override;
};

