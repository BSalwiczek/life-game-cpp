#include "Guarana.h"
#include "Swiat.h"

Guarana::Guarana(Swiat* swiat, wspolrzedne polozenie, int wiek, int sila): Roslina(swiat, polozenie)
{
	symbol = 'G';
	this->sila = sila == -1 ? SILA_ZWYKLYCH_ROSLIN : sila;
	this->wiek = wiek;
	kolor = KOLOR_FIOLETOWY;
	prawdopodobienstwo_rozsiania = PRAWDOPODOBIENSTWO_ROZSIANIA_GUARANY;
}

void Guarana::bonusZaZjedzenie(Organizm* zjadajacy)
{
	Zwierze* zjadajace_zwierze = dynamic_cast<Zwierze*>(zjadajacy);
	if (zjadajace_zwierze != nullptr)
	{
		zjadajace_zwierze->zwiekszSile(ZWIEKSZENIE_SILY);
	}
}

void Guarana::zapisz(std::ofstream& file)
{
	file << "Guarana " << sila << " " << wiek << " " << polozenie.x << " " << polozenie.y << endl;
}

std::string Guarana::przedstawSie()
{
	return "guana (zwiekszona sila o 5)";
}

void Guarana::nowa_roslina(wspolrzedne polozenie)
{
	swiat->dodajOrganizm(new Guarana(swiat, polozenie));
}
