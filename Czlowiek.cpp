#include "Czlowiek.h"
#include "Swiat.h"


Czlowiek::Czlowiek(Swiat* swiat, wspolrzedne polozenie, int wiek, int sila): Zwierze(swiat, polozenie)
{
	symbol = 'C';
	inicjatywa = INICJATYWA_CZLOWIEKA;
	this->sila = sila == -1 ? SILA_CZLOWIEKA : sila;
	this->wiek = wiek;
	ile_rund_aktywna_umiejetnosc = -1;
	setWiekoscKroku(NORMALNA_WIELKOSC_KROKU);
	kolor = KOLOR_AQUA;
	this->polozenie = polozenie;
	poprzednie_polozenie = polozenie;
}

std::string Czlowiek::przedstawSie()
{
	return "czlowiek";
}

void Czlowiek::zapisz(std::ofstream& file)
{
	file << "Czlowiek " << sila << " " << wiek << " " << polozenie.x << " " << polozenie.y << endl;
}


bool Czlowiek::rozmnozSie(Organizm* org1, Organizm* org2)
{
	return false;
}

void Czlowiek::setWiekoscKroku(int nowa_wielkosc)
{
	wielkosc_kroku = nowa_wielkosc;
}

void Czlowiek::sprobujAktywowacUmiejetnosc()
{
	if (ile_rund_aktywna_umiejetnosc == 0)
	{
		setWiekoscKroku(WIELKOSC_KROKU_PO_UZYCIU_UMIEJETNOSCI);
		swiat->dodajZdarzenie("Czlowiek aktywowal umiejetnosc (szybkosc antylopy)");
		ile_rund_aktywna_umiejetnosc = 1;
	}
}

void Czlowiek::obslugaUmiejetnosci()
{
	if (ile_rund_aktywna_umiejetnosc == 4 || ile_rund_aktywna_umiejetnosc == 5)
	{
		if (rand() % 2)
			wielkosc_kroku = NORMALNA_WIELKOSC_KROKU;
		else
			wielkosc_kroku = WIELKOSC_KROKU_PO_UZYCIU_UMIEJETNOSCI;
	}
	if (ile_rund_aktywna_umiejetnosc == 6)
	{
		swiat->dodajZdarzenie("Umiejetnosc czlowieka (szybkosc antylopy) dezaktywowana");
		wielkosc_kroku = NORMALNA_WIELKOSC_KROKU;
		ile_rund_aktywna_umiejetnosc = -6;
	}

	if (ile_rund_aktywna_umiejetnosc != 0)
		ile_rund_aktywna_umiejetnosc++;
}


void Czlowiek::akcja()
{
	obslugaUmiejetnosci();
	postarzejOrganizm();
	unsigned char ch1 = _getch();
	wspolrzedne nowe_polozenie;
	nowe_polozenie.x = polozenie.x;
	nowe_polozenie.y = polozenie.y;
	if (ch1 == KEY_ARROW_CHAR1)
	{
		switch (_getch()) {
		case KEY_UP:
			nowe_polozenie.y-=wielkosc_kroku;
			break;
		case KEY_DOWN:
			nowe_polozenie.y+=wielkosc_kroku;
			break;
		case KEY_LEFT:
			nowe_polozenie.x-=wielkosc_kroku;
			break;
		case KEY_RIGHT:
			nowe_polozenie.x+=wielkosc_kroku;
			break;
		}

		if (swiat->czyPolePoprawne(nowe_polozenie))
		{
			if (swiat->przesunOrganizm(polozenie, nowe_polozenie))
			{
				poprzednie_polozenie = polozenie;
				polozenie = nowe_polozenie;
			}
		}
	}
	else if (ch1 == 'a')
	{
		sprobujAktywowacUmiejetnosc();
	}
	
}