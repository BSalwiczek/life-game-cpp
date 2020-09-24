#include "Wilk.h"
#include "Swiat.h"

Wilk::Wilk(Swiat* swiat, wspolrzedne polozenie, int wiek, int sila): Zwierze(swiat, polozenie)
{
	this->sila = sila == -1 ? SILA_WILKA : sila;
	this->wiek = wiek;
	inicjatywa = INICJATYWA_WILKA;
	kolor = KOLOR_JASNO_CZERWONY;
	symbol = 'W';
}

std::string Wilk::przedstawSie()
{
	return "wilk";
}

void Wilk::zapisz(std::ofstream& file)
{
	file << "Wilk " << sila << " " << wiek << " " << polozenie.x << " " << polozenie.y << endl;
}

bool Wilk::rozmnozSie(Organizm* org1, Organizm* org2)
{
	if (dynamic_cast<Wilk*>(org1) != nullptr && dynamic_cast<Wilk*>(org2) != nullptr)
	{
		wspolrzedne polozenie_dziecka = znajdzMiejsceDlaDziecka(org1, org2);
		if (polozenie_dziecka.x != -1 && polozenie_dziecka.y != -1)
		{
			swiat->dodajOrganizm(new Wilk(swiat, polozenie_dziecka));
			return true;
		}
		else
			return true;
	}
	return false;
}