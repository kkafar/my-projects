#include <iostream>
#include <vector>
#include <queue>
#include <stack>

// w rozwianiu zdecydowalem sie na zastosowanie cos ala macieerzy sasiedztwa do przechowywania wag krawedzi

#define INF 10000


using namespace std;

void wyswietl_macierz(int ** macierz, int rozmiar)
{
	cout << "MACIERZ WAG\n============\n";
	for (int i = 0; i < rozmiar; ++i)
	{
		for (int j = 0; j < rozmiar; ++j)
			cout << macierz[i][j] << " ";

		cout << "\n";
	}
	cout << "=============\n";
}

void wyswietl_graf(vector<int> * graf, int l_wierzcholkow)
{
	cout << "GRAF\n";
	for (int i = 0; i < l_wierzcholkow; ++i)
	{
		cout << i << ": ";
		for (auto j = graf[i].begin(); j != graf[i].end(); ++j)
		{
			cout << *j << " ";
		}
		cout << "\n";
	}
}

// wyswietl tablice
void wyswietl_tablice(int T[], int rozmiar)
{
	cout << "TABLICA\n";
	for (int i = 0; i < rozmiar; ++i)
		cout << T[i] << " ";
	
	cout << "\n";
}

//  (graf do przejrzenia; wierzcholek startowy; kolejka, tablica odwiedzin, tablica drog, tablica poprzednikow
void znajdz_droge(vector<int> * graf, int w, queue<int> * q, int d[], int ** waga_krawedzi, int sciezka[])
{
	q->push(w);
	d[w] = 0;
	sciezka[w] = w; 

	while (!q->empty())
	{
		// pobieram pierwszy w kolejce element
		w = q->front();
		q->pop();
		
		for (auto i = graf[w].begin(); i != graf[w].end(); ++i)
		{
			// jezeli nie patrze na ten z ktorego przyjechalem
			if ((*i) != w)
			{
				// jezeli droga z aktualnie przegladanego wierzcholka w, do jego sasiada jest krotsza niz aktualna najkrotsza droga do sasiada, to podmien
				if (d[w] + waga_krawedzi[w][*i] < d[*i])
				{
					d[*i] = d[w] + waga_krawedzi[w][*i];
					// skoro podmieniamy to do sasiada (*i) przychodzimy z wierzcholka w
					sciezka[*i] = w;
				}

				// dodaj sasiada do kolejki
				q->push(*i);
			}

		}
	}
}

void wyswietl_sciezke(int w_startowy, int w_koncowy, int sciezka[])
{
	cout << "SZIEZKA: \n";
	stack<int> s;
	int w = w_koncowy; 
	s.push(w);
	while (w != w_startowy)
	{
		w = sciezka[w];
		s.push(w);
	}
	
	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}
	cout << "\n";
}

int main()
{
	queue<int> q;
	int l_wierzcholkow, l_krawedzi, w_startowy, w_koncowy, waga;

	cout << "podaj liczbe wierzcholkow oraz liczbe krawedzi grafu: ";
	cin >> l_wierzcholkow >> l_krawedzi;

	vector<int> * graf = new vector<int>[l_wierzcholkow];

	// dynamiczne tworzenie tablicy 2D do przechowywania wag krawedzi;
	// =================================== 
	int ** waga_krawedzi = new int*[l_wierzcholkow];

	for (int i = 0; i < l_wierzcholkow; ++i)
	{
		// tworzenie wierszy
		waga_krawedzi[i] = new int[l_wierzcholkow];

		// tablice uzupelniamy wartosciami 0
		for (int j = 0; j < l_wierzcholkow; ++j)
			waga_krawedzi[i][j] = 0;
	}
	// ===================================

	// droga_do[i] - najkrotsza dotychczas znana droga z wierzcholka startowego do wiercholka w_i
	int * droga_do = new int[l_wierzcholkow];

	for (int i = 0; i < l_wierzcholkow; ++i)
		droga_do[i] = INF;


	// s[i] - przechowuje index wierzcholka z którego przechodzimy na w_i
	int * sciezka = new int[l_wierzcholkow];

	for (int i = 0; i < l_wierzcholkow; ++i)
		sciezka[i] = -1; 

	// wczytywanie krawedzi grafu wraz z ich wagami
	cout << "podaj kolejne krawedzie grafu wraz z wagami krawedzi:\n";
	for (int i = 0; i < l_krawedzi; ++i)
	{
		cin >> w_startowy >> w_koncowy >> waga;
		graf[w_startowy].push_back(w_koncowy);
		waga_krawedzi[w_startowy][w_koncowy] = waga;
	}
	cout << "\npodaj wierzcholek startowy: ";
	cin >> w_startowy;
	cout << "podaj wierzcholek koncowy: ";
	cin >> w_koncowy;
	// wyswietlanie wszsytkiego do debugowania
	wyswietl_macierz(waga_krawedzi, l_wierzcholkow);

	wyswietl_graf(graf, l_wierzcholkow);

	znajdz_droge(graf, w_startowy, &q, droga_do, waga_krawedzi, sciezka);

	wyswietl_tablice(droga_do, l_wierzcholkow);

	cout << "DROGA: " << droga_do[w_koncowy] << "\n";

	//wyswietl_tablice(sciezka, l_wierzcholkow);

	wyswietl_sciezke(w_startowy, w_koncowy, sciezka);

	// zwalnianie zarezerwowanej pamieci operacyjnej
	for (int i = 0; i < l_wierzcholkow; ++i)
		delete[] waga_krawedzi[i];

	delete[] graf;
	delete[] droga_do;
	delete[] sciezka;
	return 0;
}
