#include "Zwierze.h"
#include "Swiat.h"

Zwierze::Zwierze(Swiat* swiat, wspolrzedne polozenie)
{
	this->swiat = swiat;
	this->polozenie = polozenie;
}

void Zwierze::akcja()
{
	postarzejOrganizm();
	ruch();
}

std::string Zwierze::przedstawSie()
{
	return "nieznane zwierze";
}

void Zwierze::zwiekszSile(int ilosc)
{
	sila += ilosc;
}

bool Zwierze::czyOdbilAtak(Organizm* atakujacy)
{
	if (atakujacy == NULL)
		return true;
	return sila > atakujacy->getSila();
}

void Zwierze::bonusZaZjedzenie(Organizm* zjadany) {}

void Zwierze::zapisz(std::ofstream& file) {}

wspolrzedne Zwierze::znajdzMiejsceDlaDziecka(Organizm* org1, Organizm* org2)
{
	wspolrzedne ws1 = org1->getPolozenie();
	wspolrzedne ws2 = org2->getPolozenie();
	wspolrzedne nowe_polozenie = ws1;
	int dxy;
	for (int i = 0; i < ILOSC_PROB_ZNALEZIENIA_MIEJSCA_DLA_DZIECKA; i++)
	{
		dxy = (rand() % 2) == 1 ? 1 : -1;
		if (rand() % 2 == 1) //wybrano ws1
		{
			nowe_polozenie = ws1;
			if (rand() % 2 == 1)
				nowe_polozenie.x = ws1.x + dxy;
			else
				nowe_polozenie.y = ws1.y + dxy;
		}
		else
		{
			nowe_polozenie = ws2;
			if (rand() % 2 == 1)
				nowe_polozenie.x = ws2.x + dxy;
			else
				nowe_polozenie.y = ws2.y + dxy;
		}
		if (!swiat->czyPoleZajete(nowe_polozenie))
		{
			return nowe_polozenie;
		}
	}
	return { -1,-1 };
}

void Zwierze::ruch()
{
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

void Zwierze::postarzejOrganizm()
{
	wiek++;
}

Organizm* Zwierze::podstawowaKolizja(Organizm* organizm, bool& powrot_na_miejsca)
{
	organizm->bonusZaZjedzenie(this);
	if (organizm->czyOdbilAtak(this))
	{
		if (dynamic_cast<Roslina*>(organizm) != nullptr)
		{
			swiat->dodajZdarzenie(this->przedstawSie() + " zjadl rosline " + organizm->przedstawSie() + " i zginal");
			return nullptr;
		}
		swiat->dodajZdarzenie(this->przedstawSie() + " przegral w pojedynku z " + organizm->przedstawSie() + " i zginal");
		return organizm;
	}
	else
	{
		if (dynamic_cast<Roslina*>(organizm) != nullptr)
		{
			swiat->dodajZdarzenie(this->przedstawSie() + " zjadl rosline " + organizm->przedstawSie());
		}
		else
			swiat->dodajZdarzenie(this->przedstawSie() + " wygral w pojedynku z " + organizm->przedstawSie());

		return this;
	}
}

bool Zwierze::podstawoweRozmnozenie(Organizm* organizm, bool& powrot_na_miejsca)
{
	if (rozmnozSie(this, organizm))
	{
		swiat->dodajZdarzenie("Doszlo do rozmnozenia! Powstalo mlode zwierze " + this->przedstawSie());
		powrot_na_miejsca = true;
		return true;
	}
	return false;
}

Organizm* Zwierze::kolizja(Organizm* organizm, bool& powrot_na_miejsca)
{
	if (podstawoweRozmnozenie(organizm, powrot_na_miejsca))
	{
		return nullptr;
	}

	if (dynamic_cast<Zolw*>(organizm) != nullptr)
	{
		if (organizm->czyOdbilAtak(this))
		{
			powrot_na_miejsca = true;
			swiat->dodajZdarzenie(organizm->przedstawSie() + " odparl atak " + this->przedstawSie());
			return nullptr;
		}
	}
	if (dynamic_cast<Antylopa*>(organizm) != nullptr)
		return organizm->kolizja(this, powrot_na_miejsca);

	return podstawowaKolizja(organizm, powrot_na_miejsca);
}

void Zwierze::rysowanie(HANDLE color)
{
	SetConsoleTextAttribute(color, kolor);
	cout << symbol << " ";
}