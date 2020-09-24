#include "Trawa.h"
#include "Swiat.h"


Trawa::Trawa(Swiat* swiat, wspolrzedne polozenie, int wiek, int sila) : Roslina(swiat, polozenie)
{
	symbol = 'T';
	this->sila = sila == -1 ? SILA_ZWYKLYCH_ROSLIN : sila;
	this->wiek = wiek;
	kolor = KOLOR_JASNA_ZIELEN;
	prawdopodobienstwo_rozsiania = PRAWDOPODOBIENSTWO_ROZSIANIA_TRAWY;
}

std::string Trawa::przedstawSie()
{
	return "trawa";
}

void Trawa::zapisz(std::ofstream& file)
{
	file << "Trawa " << sila << " " << wiek << " " << polozenie.x << " " << polozenie.y << endl;
}


void Trawa::nowa_roslina(wspolrzedne polozenie)
{
	swiat->dodajOrganizm(new Trawa(swiat, polozenie));
}