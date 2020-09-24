#include "Antylopa.h"
#include "Swiat.h"

Antylopa::Antylopa(Swiat* swiat, wspolrzedne polozenie, int wiek, int sila): Zwierze(swiat, polozenie)
{
	this->sila = sila == -1 ? SILA_ANTYLOPY : sila;
	this->wiek = wiek;
	inicjatywa = INICJATYWA_ANTYLOPY;
	kolor = KOLOR_ZOLTY;
	symbol = 'A';
}

std::string Antylopa::przedstawSie()
{
	return "antylopa";
}

void Antylopa::zapisz(std::ofstream& file)
{
	file << "Antylopa " << sila << " " << wiek << " " << polozenie.x << " " << polozenie.y << endl;
}


Organizm* Antylopa::kolizja(Organizm* organizm, bool& powrot_na_miejsca)
{
	if (podstawoweRozmnozenie(organizm, powrot_na_miejsca))
	{
		return nullptr;
	}
	if (rand() % 2 == 1 && dynamic_cast<Zwierze*>(organizm) != nullptr)
	{
		swiat->dodajZdarzenie(this->przedstawSie() + " uciekla przed starciem z " + organizm->przedstawSie());
		this->akcja();
		powrot_na_miejsca = true;
		return NULL;
	}

	if (dynamic_cast<Zolw*>(organizm) != nullptr)
		return organizm->kolizja(this, powrot_na_miejsca);

	return podstawowaKolizja(organizm, powrot_na_miejsca);
}

bool Antylopa::rozmnozSie(Organizm* org1, Organizm* org2)
{
	if (dynamic_cast<Antylopa*>(org1) != nullptr && dynamic_cast<Antylopa*>(org2) != nullptr)
	{
		wspolrzedne polozenie_dziecka = znajdzMiejsceDlaDziecka(org1, org2);
		if (polozenie_dziecka.x != -1 && polozenie_dziecka.y != -1)
		{
			swiat->dodajOrganizm(new Antylopa(swiat, polozenie_dziecka));
			return true;
		}
		else
			return true;
	}
	return false;

}

void Antylopa::akcja()
{
	postarzejOrganizm();
	int dxy = 0;
	wspolrzedne nowe_polozenie;
	nowe_polozenie.x = polozenie.x;
	nowe_polozenie.y = polozenie.y;
	for (int i = 0; i < ILOSC_PROB_PORUSZENIA; i++)
	{
		dxy = rand() % 4 - 1;
		if (dxy <= 0)
			dxy -= 1;
		if (rand() % 2 == 1)
			nowe_polozenie.x = polozenie.x + dxy;
		else
			nowe_polozenie.y = polozenie.y + dxy;
		if (swiat->czyPolePoprawne(nowe_polozenie))
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