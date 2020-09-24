#include "WilczeJagody.h"
#include "Swiat.h"

WilczeJagody::WilczeJagody(Swiat* swiat, wspolrzedne polozenie, int wiek, int sila): Roslina(swiat, polozenie)
{
	symbol = 'J';
	kolor = KOLOR_CZERWONY;
	this->sila = sila == -1 ? SILA_WILCZYCH_JAGOD : sila;
	this->wiek = wiek;
	prawdopodobienstwo_rozsiania = SZANSA_ROZSIANIA_WILCZYCH_JAGOD;
}

std::string WilczeJagody::przedstawSie()
{
	return "wilcze jagody";
}

void WilczeJagody::zapisz(std::ofstream& file)
{
	file << "WilczeJagody " << sila << " " << wiek << " " << polozenie.x << " " << polozenie.y << endl;
}

void WilczeJagody::nowa_roslina(wspolrzedne polozenie)
{
	swiat->dodajOrganizm(new WilczeJagody(swiat, polozenie));
}