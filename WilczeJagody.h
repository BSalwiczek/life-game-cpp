#pragma once
#include "Roslina.h"

#define SILA_WILCZYCH_JAGOD 99
#define SZANSA_ROZSIANIA_WILCZYCH_JAGOD 0.03

class WilczeJagody: public Roslina
{
public:
	WilczeJagody(Swiat* swiat, wspolrzedne polozenie, int wiek = 0, int sila = SILA_WILCZYCH_JAGOD);

	void zapisz(std::ofstream& file) override;
	void nowa_roslina(wspolrzedne polozenie) override;
	std::string przedstawSie() override;
};

