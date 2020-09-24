#pragma once
#include "Organizm.h"
//#include "Swiat.h"
#define ILOSC_PROB_PORUSZENIA 10
#define ILOSC_PROB_ZNALEZIENIA_MIEJSCA_DLA_DZIECKA 50
class Swiat;

class Zwierze: public Organizm
{
public:
	Zwierze(Swiat* swiat, wspolrzedne polozenie);

	void akcja() override;
	Organizm* kolizja(Organizm* organizm, bool& powrot_na_miejsca) override;
	void zapisz(std::ofstream& file) override;
	void rysowanie(HANDLE color) override;
	void bonusZaZjedzenie(Organizm* zjadany) override;
	bool czyOdbilAtak(Organizm* atakujacy) override;
	std::string przedstawSie() override;

	void zwiekszSile(int ilosc);
	wspolrzedne znajdzMiejsceDlaDziecka(Organizm* org1, Organizm* org2); // zwraca {-1,-1} w przypadku niepowodzenia

protected:

	Organizm* podstawowaKolizja(Organizm* organizm, bool& powrot_na_miejsca);
	bool podstawoweRozmnozenie(Organizm* organizm, bool& powrot_na_miejsca);
	virtual bool rozmnozSie(Organizm* org1, Organizm* org2) = 0;
	void ruch();

	void postarzejOrganizm() override;
};

