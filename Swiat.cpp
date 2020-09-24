#include <time.h>
#include "Swiat.h"

Swiat::Swiat()
{
	srand(time(NULL));

	N = pobierzWymiarOdUzytkownika();
	M = pobierzWymiarOdUzytkownika();

	tura = 0;
	save = false;
	inicjujMapeNazwOrganizmow();
	inicjujPola();
	inicjujOrganizmy();

	system("CLS");
}

int Swiat::pobierzWymiarOdUzytkownika()
{
	bool error = false;
	int x;
	do
	{
		error = false;
		string wejscie;
		std::cin >> wejscie;
		try {
			x = stoi(wejscie);
			if (x < MINIMALNY_WYMIAR)
				throw std::invalid_argument("Wymiar powinien byc >= "+to_string((int)MINIMALNY_WYMIAR));
		}
		catch (const std::invalid_argument & ia)
		{
			error = true;
			cerr << "Nieprawidlowe dane wejsciowe (" << ia.what() << ")" << endl;
		}
	} while (error);
	return x;
}

Swiat::~Swiat()
{
	usuniecieOrganizmow();
	usunieciePol();
}

void Swiat::inicjujPola()
{
	pola = new Organizm** [N];
	for (int i = 0; i < N; i++)
	{
		pola[i] = new Organizm*[M];
		for (int j = 0; j < M; j++)
		{
			pola[i][j] = nullptr;
		}
	}
}

void Swiat::usunieciePol()
{
	for (int i = 0; i < N; i++)
	{
		delete[] pola[i];
	}
	delete[] pola;
}

void Swiat::usuniecieOrganizmow()
{
	for (Organizm* x : organizmy)
	{
		usunOrganizm(x);
	}
	organizmy.clear();
}

void Swiat::czekajNaTure()
{
	char x =_getch();
	if (x == 's')
	{
		save = true;
		dodajZdarzenie("Swiat zostal zapisany!");
	}
	if (x == 'l')
	{
		system("CLS");
		usuniecieOrganizmow();
		usunieciePol();
		wczytajSwiat();
		opis_zdarzen.clear();
		dodajZdarzenie("Wczytano poprzednio zapisany swiat");
	}
}

void Swiat::inicjujOrganizmy()
{
	dodajOrganizm(new Czlowiek(this, { rand()%M,rand()%N }));
	for (const auto& p : mapa_nazw_organizmow)
	{
		if (p.first != "Czlowiek")
		{
			int n = rand() % (int)(min(N,M)/4) + 1;

			for (int i = 0; i < n; i++)
			{
				int x = rand() % M;
				int y = rand() % N;
				if (!czyPoleZajete({ x,y }))
				{
					dodajOrganizm(p.second(this, { x,y },0,-1));
				}
			}


		}
	}
}

void Swiat::zapiszSwiat()
{
	ofstream file;
	file.open(NAZWA_PLIKU_DO_ZAPISU, ofstream::out | ofstream::trunc);
	file << N << endl;
	file << M << endl;
	file << tura << endl;
	for (Organizm* o : organizmy)
	{
		if(o != nullptr)
			o->zapisz(file);
	}
	file.close();
}


void Swiat::inicjujMapeNazwOrganizmow()
{
	mapa_nazw_organizmow["Wilk"] = &createInstance<Wilk>;
	mapa_nazw_organizmow["Czlowiek"] = &createInstance<Czlowiek>;
	mapa_nazw_organizmow["Trawa"] = &createInstance<Trawa>;
	mapa_nazw_organizmow["Mlecz"] = &createInstance<Mlecz>;
	mapa_nazw_organizmow["Guarana"] = &createInstance<Guarana>;
	mapa_nazw_organizmow["WilczeJagody"] = &createInstance<WilczeJagody>;
	mapa_nazw_organizmow["Owca"] = &createInstance<Owca>;
	mapa_nazw_organizmow["BarszczSosnowskiego"] = &createInstance<BarszczSosnowskiego>;
	mapa_nazw_organizmow["Lis"] = &createInstance<Lis>;
	mapa_nazw_organizmow["Zolw"] = &createInstance<Zolw>;
	mapa_nazw_organizmow["Antylopa"] = &createInstance<Antylopa>;
}

bool Swiat::wczytajSwiat()
{
	std::ifstream infile(NAZWA_PLIKU_DO_ZAPISU);
	if(infile.good())
	{
		infile >> N;
		infile >> M;
		inicjujPola();
		infile >> tura;

		string in;
		int sila, wiek, x, y;

		while (infile >> in >> sila >> wiek >> x >> y)
		{
			dodajOrganizm(mapa_nazw_organizmow[in](this, { x,y }, wiek, sila));
		}
		return true;
	}
	else
		return false;
}

void Swiat::uporzadkujOrganizmy()
{
	for (int i = organizmy.size() - 1; i >= 0; i--)
	{
		if (organizmy[i] == nullptr)
		{
			organizmy.erase(organizmy.begin() + i);
		}
	}
	std::sort(organizmy.begin(), organizmy.end(), porownajOrganizmy());
}

void Swiat::wykonajTure()
{
	tura++;
	uporzadkujOrganizmy();
	for (int i = 0; i < organizmy.size(); i++)
	{
		if (dynamic_cast<Czlowiek*>(organizmy[i]) != nullptr)
		{
			rysujSwiat();
		}
		if (organizmy[i] != nullptr)
		{
			organizmy[i]->akcja();
		}
	}

	if (save)
	{
		save = false;
		zapiszSwiat();
	}
}

Organizm* Swiat::zwrocOrgnizmNaPolu(wspolrzedne polozenie)
{
	if(czyPolePoprawne(polozenie))
		return pola[polozenie.y][polozenie.x];
	return nullptr;
}

void Swiat::dodajZdarzenie(string tresc)
{
	opis_zdarzen.push_front(tresc);
	if (opis_zdarzen.size() > ILOSC_WYPISYWANYCH_OSTATNICH_ZDARZEN)
		opis_zdarzen.pop_back();
}

bool Swiat::przesunOrganizm(wspolrzedne skad, wspolrzedne dokad)
{
	Organizm* pierwszy_organizm = pola[skad.y][skad.x];

	if (pola[dokad.y][dokad.x] != nullptr) //kolizja
	{
		Organizm* drugi_organizm = pola[dokad.y][dokad.x];
		bool powrot_na_miejsca = false;
		Organizm* wygrany = pierwszy_organizm->kolizja(drugi_organizm, powrot_na_miejsca);
		if (wygrany == nullptr && !powrot_na_miejsca) // oba organizmy zginely - nalezy je usunac
		{
			usunOrganizm(pierwszy_organizm);
			usunOrganizm(drugi_organizm);
		}
		else if (wygrany == nullptr && powrot_na_miejsca) // nikt nie wygral = powrot na miejsca (nic nie rob)
		{
			return false;
		}
		else if (wygrany == pierwszy_organizm) // atakujacy organizm wygrywa - przesun go na miejsce ofiary i usun ofiare
		{
			usunOrganizm(drugi_organizm);
			pola[dokad.y][dokad.x] = pierwszy_organizm;
			pola[skad.y][skad.x] = nullptr;
			return true;
		}else // atakujacy przegrywa - usun go
			usunOrganizm(pierwszy_organizm);

		pola[skad.y][skad.x] = nullptr;
		return false;
	}
	else { // bez kolizji - normalne przesuniecie
		pola[dokad.y][dokad.x] = pierwszy_organizm;
		pola[skad.y][skad.x] = nullptr;
		return true;
	}
}

void Swiat::usunOrganizm(Organizm* organizm)
{
	if (organizm == nullptr)
		return;
	for (int i = 0; i < organizmy.size(); i++)
	{
		if (organizmy[i] == organizm)
		{
			organizmy[i] = nullptr;
			break;
		}
	}
	int x = organizm->getPolozenie().x;
	int y = organizm->getPolozenie().y;
	delete pola[y][x];
	pola[y][x] = nullptr;
}


void Swiat::dodajOrganizm(Organizm* nowy_organizm)
{
	organizmy.push_back(nowy_organizm);
	pola[nowy_organizm->getPolozenie().y][nowy_organizm->getPolozenie().x] = nowy_organizm;
}

bool Swiat::czyPolePoprawne(wspolrzedne polozenie)
{
	return polozenie.x >= 0 && polozenie.y >= 0 && polozenie.x < M && polozenie.y < N;
}

bool Swiat::czyPoleZajete(wspolrzedne polozenie)
{
	if (czyPolePoprawne(polozenie) && pola[polozenie.y][polozenie.x] == nullptr)
		return false;
	return true;
}

void Swiat::wypiszZdarzenia()
{
	cout << endl;
	for (int n = 0; n < ILOSC_WYPISYWANYCH_OSTATNICH_ZDARZEN; n++){
		for(int i=0;i<MAX_DLUGOSC_LINI;i++)
			printf(" ");
		printf("\n");
	}

	ustawKursor(0, N+8);

	for (string zdarzenie : opis_zdarzen)
	{
		cout << "\r" << zdarzenie << endl;
	}
}

void Swiat::ustawKursor(int X, int Y)
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = X;
	Position.Y = Y;
	SetConsoleCursorPosition(hOut, Position);
}

void Swiat::rysujSwiat()
{
	ustawKursor(0, 0);

	cout << "Autor: Bartosz Salwiczek, indeks 180312" << endl;
	cout << "Specjalna umiejetnosc czlowieka: szybkosc antylopy. Aktywacja klawiszem 'a' w rundzie gracza" << endl;
	cout << "Dowolny przycisk przelacza ture" << endl;
	cout << "'s' - zapisz aktualny stan gry, 'l' - wczytaj poprzednio zapisany stan gry (aktywacja przy przelaczaniu tury)" << endl;
	cout << "Tura: " << tura << endl;

	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i <= M; i++)
	{
		cout << "--";
	}
	cout << endl;
	for (int i = 0; i < N; i++)
	{
		cout << "|";
		for (int j = 0; j < M; j++)
		{
			if (pola[i][j] == nullptr)
				cout << "  ";
			else
				pola[i][j]->rysowanie(color);

			SetConsoleTextAttribute(color, KOLOR_BIALY);
		}
		cout << "|"<< endl;
	}
	for (int i = 0; i <= M; i++)
	{
		cout << "--";
	}
	cout << endl;

	wypiszZdarzenia();
}
