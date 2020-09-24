#include "Mlecz.h"
#include "Swiat.h"


Mlecz::Mlecz(Swiat* swiat, wspolrzedne polozenie, int wiek, int sila) : Roslina(swiat, polozenie)
{
	symbol = 'M';
	kolor = KOLOR_ZOLTY;
	this->sila = sila == -1 ? SILA_ZWYKLYCH_ROSLIN : sila;
	this->wiek = wiek;
	prawdopodobienstwo_rozsiania = PRAWDOPODOBIENSTWO_ROZSIANIA_MLECZA;
}

void Mlecz::nowa_roslina(wspolrzedne polozenie)
{
	swiat->dodajOrganizm(new Mlecz(swiat, polozenie));
}

void Mlecz::zapisz(std::ofstream& file)
{
	file << "Mlecz " << sila << " " << wiek << " " << polozenie.x << " " << polozenie.y << endl;
}

std::string Mlecz::przedstawSie()
{
	return "mlecz";
}

void Mlecz::akcja()
{
	postarzejOrganizm();
	rozsiejSie();
	rozsiejSie();
	rozsiejSie();
}
