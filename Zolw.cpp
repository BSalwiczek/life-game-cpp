#include "Zolw.h"
#include "Swiat.h"

Zolw::Zolw(Swiat* swiat, wspolrzedne polozenie, int wiek, int sila): Zwierze(swiat, polozenie)
{
	this->sila = sila==-1 ? SILA_W_WALCE :sila;
	this->wiek = wiek;
	inicjatywa = INICJATYWA_ZOLWIA;
	kolor = KOLOR_ZIELONY;
	symbol = 'Z';
}

std::string Zolw::przedstawSie()
{
	return "zolw";
}

void Zolw::zapisz(std::ofstream& file)
{
	file << "Zolw " << sila << " " << wiek << " " << polozenie.x << " " << polozenie.y << endl;
}

bool Zolw::rozmnozSie(Organizm* org1, Organizm* org2)
{
	if (dynamic_cast<Zolw*>(org1) != nullptr && dynamic_cast<Zolw*>(org2) != nullptr)
	{
		wspolrzedne polozenie_dziecka = znajdzMiejsceDlaDziecka(org1, org2);
		if (polozenie_dziecka.x != -1 && polozenie_dziecka.y != -1)
		{
			swiat->dodajOrganizm(new Zolw(swiat, polozenie_dziecka));
			return true;
		}else
			return true;
	}
	return false;

}

bool Zolw::czyOdbilAtak(Organizm* atakujacy)
{
	return atakujacy->getSila() < SILA_ODPIERAJACA_ATAK;
}

void Zolw::akcja()
{
	postarzejOrganizm();
	if (rand() % 100 <= SZANSA_NA_RUCH_ZOLWIA)
	{
		ruch();
	}
}