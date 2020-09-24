#include "Owca.h"
#include "Swiat.h"

Owca::Owca(Swiat* swiat, wspolrzedne polozenie, int wiek, int sila) : Zwierze(swiat, polozenie)
{
	this->sila = sila == -1 ? SILA_OWCY : sila;
	this->wiek = wiek;
	inicjatywa = INICJATYWA_OWCY;
	kolor = KOLOR_BIALY;
	symbol = 'O';
}

std::string Owca::przedstawSie()
{
	return "owca";
}

void Owca::zapisz(std::ofstream& file)
{
	file << "Owca " << sila << " " << wiek << " " << polozenie.x << " " << polozenie.y << endl;
}


bool Owca::rozmnozSie(Organizm* org1, Organizm* org2)
{
	if (dynamic_cast<Owca*>(org1) != nullptr && dynamic_cast<Owca*>(org2) != nullptr)
	{
		wspolrzedne polozenie_dziecka = znajdzMiejsceDlaDziecka(org1, org2);
		if (polozenie_dziecka.x != -1 && polozenie_dziecka.y != -1)
		{
			swiat->dodajOrganizm(new Owca(swiat, polozenie_dziecka));
			return true;
		}
		else
			return true;
	}
	return false;

}