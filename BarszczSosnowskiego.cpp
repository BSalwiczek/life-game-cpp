#include "BarszczSosnowskiego.h"
#include "Swiat.h"

BarszczSosnowskiego::BarszczSosnowskiego(Swiat* swiat, wspolrzedne polozenie, int wiek, int sila): Roslina(swiat, polozenie)
{
	this->sila = sila == -1 ? SILA_BARSZCZU_SOSNOWSKIEGO : sila;
	this->wiek = wiek;
	symbol = 'B';
	kolor = KOLOR_FIOLETOWY;
	prawdopodobienstwo_rozsiania = PRAWDOPODOBIENSTWO_ROZSIANIA_SOSNOWSKIEGO;
}
void BarszczSosnowskiego::nowa_roslina(wspolrzedne polozenie)
{
	swiat->dodajOrganizm(new BarszczSosnowskiego(swiat, polozenie));
}

std::string BarszczSosnowskiego::przedstawSie()
{
	return "barszcz sosnowskiego";
}

void BarszczSosnowskiego::zapisz(std::ofstream& file)
{
	file << "BarszczSosnowskiego " << sila << " " << wiek << " " << polozenie.x << " " << polozenie.y << endl;
}


void BarszczSosnowskiego::akcja()
{
	postarzejOrganizm();
	rozsiejSie();

	//zabij zwierzeta w okolicy
	zabijZwierze(swiat->zwrocOrgnizmNaPolu({ polozenie.x + 1,polozenie.y }));
	zabijZwierze(swiat->zwrocOrgnizmNaPolu({ polozenie.x - 1,polozenie.y }));
	zabijZwierze(swiat->zwrocOrgnizmNaPolu({ polozenie.x,polozenie.y + 1 }));
	zabijZwierze(swiat->zwrocOrgnizmNaPolu({ polozenie.x,polozenie.y - 1 }));
}

void BarszczSosnowskiego::zabijZwierze(Organizm* organizm)
{
	if (organizm != nullptr && dynamic_cast<Zwierze*>(organizm) != nullptr)
	{
		swiat->dodajZdarzenie("Barszcz sosnowskiego zatrul zwierze "+organizm->przedstawSie());
		swiat->usunOrganizm(organizm);
	}
}