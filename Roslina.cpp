#include "Roslina.h"
#include "Swiat.h"

Roslina::Roslina(Swiat* swiat, wspolrzedne polozenie)
{
	this->swiat = swiat;
	this->polozenie = polozenie;
	inicjatywa = 0;
	poprzednie_polozenie = polozenie;
}

void Roslina::rysowanie(HANDLE color)
{
	SetConsoleTextAttribute(color, kolor);
	cout << symbol << " ";
}

bool Roslina::czyOdbilAtak(Organizm* atakujacy)
{
	return sila > atakujacy->getSila();
}

void Roslina::bonusZaZjedzenie(Organizm* zjadajacy) {}

std::string Roslina::przedstawSie()
{
	return "nieznana roslina";
}

void Roslina::postarzejOrganizm()
{
	wiek++;
}

void Roslina::zapisz(std::ofstream& file) {}

void Roslina::akcja()
{
	postarzejOrganizm();
	rozsiejSie();
}

void Roslina::rozsiejSie()
{
	int x = rand() % 100;
	if (x < prawdopodobienstwo_rozsiania * 100)
	{
		int dxy = 0;
		wspolrzedne nowe_polozenie = polozenie;
		for (int i = 0; i < ILOSC_PROB_ZNALEZIENIA_DOBREGO_POLA; i++)
		{
			dxy = (rand() % 2) == 1 ? 1 : -1;
			if (rand() % 2 == 1)
				nowe_polozenie.x = polozenie.x + dxy;
			else
				nowe_polozenie.y = polozenie.y + dxy;

			if (swiat->czyPolePoprawne(nowe_polozenie) && !swiat->czyPoleZajete(nowe_polozenie))
			{
				nowa_roslina(nowe_polozenie);
				return;
			}

			nowe_polozenie = polozenie;
		}
	}
}

Organizm* Roslina::kolizja(Organizm* organizm, bool& powrot_na_miejsca)
{
	return NULL;
}