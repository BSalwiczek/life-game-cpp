#include "Lis.h"
#include "Swiat.h"

Lis::Lis(Swiat* swiat, wspolrzedne polozenie, int wiek, int sila): Zwierze(swiat, polozenie)
{
	this->sila = sila == -1 ? SILA_LISA : sila;
	this->wiek = wiek;
	inicjatywa = INICJATYWA_LISA;
	kolor = KOLOR_JASNO_ZOLTY;
	symbol = 'L';
}

std::string Lis::przedstawSie()
{
	return "lis";
}

void Lis::zapisz(std::ofstream& file)
{
	file << "Lis " << sila << " " << wiek << " " << polozenie.x << " " << polozenie.y << endl;
}


bool Lis::rozmnozSie(Organizm* org1, Organizm* org2)
{
	if (dynamic_cast<Lis*>(org1) != nullptr && dynamic_cast<Lis*>(org2) != nullptr)
	{
		wspolrzedne polozenie_dziecka = znajdzMiejsceDlaDziecka(org1, org2);
		if (polozenie_dziecka.x != -1 && polozenie_dziecka.y != -1)
		{
			swiat->dodajOrganizm(new Lis(swiat, polozenie_dziecka));
			return true;
		}
		else
			return true;
	}
	return false;

}

void Lis::akcja()
{
	postarzejOrganizm();
	int dxy = 0;
	wspolrzedne nowe_polozenie;
	nowe_polozenie.x = polozenie.x;
	nowe_polozenie.y = polozenie.y;
	for (int i = 0; i < ILOSC_PROB_PORUSZENIA; i++)
	{
		dxy = (rand() % 2) == 1 ? 1 : -1;
		if (rand() % 2 == 1)
			nowe_polozenie.x = polozenie.x + dxy;
		else
			nowe_polozenie.y = polozenie.y + dxy;
		if (swiat->czyPolePoprawne(nowe_polozenie) && czyOdbilAtak(swiat->zwrocOrgnizmNaPolu(nowe_polozenie)))
		{
			if (swiat->przesunOrganizm(polozenie, nowe_polozenie))
			{
				poprzednie_polozenie = polozenie;
				polozenie = nowe_polozenie;
			}
			return;
		}
	}
}