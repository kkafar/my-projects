/* 
	MERGE SORT 		WERSJA 2, bardziej przejrzysta i prostsza
	Sortowanie przez scalanie
	O(n * logn)
*/
#include <iostream>
#include <time.h>
#include <iomanip>
using namespace std;

int licznik_wywolan;

void error(const string& s)
{
	cout << s << "\n";
}

/* ALGORYTM REALIZUJĄCY SCALANIE DWÓCH ZBIORÓW */
/// ================================================
// operujemy na podzbiorach sortowanej tablicy, zatem funkcja jako argumenty przyjmuje 
// indeksy granic scalanych przedziałów: 
// i_lewy_początek - indeks pierwszego elementu lewego przedziału (tego o indeksach mniejszych)
// i_prawy_poczatek  - indeks pierwszego elemntu prawego przedziału (tego o indeksach większych)
// i_prawy_koniec - indeks ostatniego elementu prawego przedziału
// i_lewy_koniec - nie pobieramy, bo to przecież (i_prawy_poczatek - 1);
void merge(int T[], int i_lewy_poczatek, int i_prawy_poczatek, int i_prawy_koniec)
{
	cout << "Scalane zbiory: [ ";
	for (int i = i_lewy_poczatek; i < i_prawy_poczatek; ++i)
		cout << T[i] << " ";
	cout << "] i [ ";
	for (int i = i_prawy_poczatek; i <= i_prawy_koniec; ++i)
		cout << T[i] << " ";
	cout << "]";
	// tworzymy sobie kopie pobranych indeksów, bo będziemy potrzebować zmieniać ich wartości jednocześnie
	// pamiętając ich wartości początkowe
	// i1 - będziemy się za jego pomocą poruszać po lewej części przedziału
	// i2 - będziemy sie za jego pomocą poruszać po prawej części przedziału
	int i1 = i_lewy_poczatek, i2 = i_prawy_poczatek;
	// iterator służący do śledzenia miejsca wpisywania do tablicy pomocniczej P[]
	register int i = 0;

	// tworzymy tablicę pomocniczą, przechowującą tymczasowo scalony zbiór (na końcu przepiszemy jej zawartość do 
	// wejściowej tablicy)
	int * P = new int[i_prawy_koniec - i_lewy_poczatek + 1];

	// dopóki iteratory nie wyjdą poza przedziały na które mają wskazywać
	while (i1 < i_prawy_poczatek && i2 <= i_prawy_koniec)
	{
		// jeżeli pierwszy element prawej części talicy jest mniejszy, to jego wpisujemy do tablicy pomocniczej P[]
		if (T[i1] > T[i2])
		{
			// przypisujemy, a następnie inkrementujemy i2;
			P[i] = T[i2++];
		}
		// w wypadku gdy wartości są równe, bądź to pierwsza liczba w lewej części tablicy jest mniejsza
		else
		{
			P[i] = T[i1++];
		}

		// zwiększamy iterator i;
		++i;
	}

	// skoro wyszliśmy już za tą pętlę, to znaczy, że któraś częśc tablicy się już wyczerpała, więc resztę z drugiej części
	// przepisujemy do tablicy pomocniczej P[]
	while (i1 < i_prawy_poczatek)
	{
		P[i++] = T[i1++];
	}
	while (i2 <= i_prawy_koniec)
	{
		P[i++] = T[i2++];
	}

	// na koniec pozostaje przepisać zawartość tablicy pomocniczej P[] do tablicy T[]
	// tablice P[], uzupełnialiśmy od indeksu 0 (zawsze), więc trzeba przeliczyć indeksy. 
	for (int j = i_lewy_poczatek; j <= i_prawy_koniec; ++j)
		T[j] = P[j - i_lewy_poczatek];

	cout << " ==> scalony zbior: [";
	for (int i = 0; i < i_prawy_koniec - i_lewy_poczatek + 1; ++i)
		cout << P[i] << " ";
	cout << "]\n";


	delete[] P;
}
/// ================================================


/* ALGORYTM SORTUJĄCY */ 
/// ================================================
// wykorzystujemy rekrurencję
// jako argumenty przyjmujemy indeksy graniczne sortowanego zbioru: 
// i_lewy_poczatek - indeks pierwszego elementu z lewej strony sortowanego zbioru
// i_prawy_koniec - indeks ostatniego elementu w prawej strony sortowanego zbioru
// przy pierwszym wywołaniu funkcji, powinniśmy podać granice zbioru który chcemy posortować
// czyli najczęściej 0 i (l_elementow - 1)
void merge_sort(int T[], int i_lewy_poczatek, int i_prawy_koniec)
{
	const int ID = licznik_wywolan++;
	cout << "ID f() wywolujacej merge_sort() " << ID << "\n";

	// zmienna w której będziemy przechowywać indeks pierwszego elementu w prawym podzbiorze
	// jako że korzystamy z rekurencji to będziemy sobie ją na bieżąco obliczać za każdym wywołaniem funkcji
	// od razu ustawiamy się na środku rozpatrywanego zbioru 
	// w nawiasie z sumą mamy jeszcze + 1
	int i_prawy_poczatek = (i_lewy_poczatek + i_prawy_koniec + 1) / 2;

	cout << "dane wywolania: ilp:" << i_lewy_poczatek << " ipp:" << i_prawy_poczatek << " ipk:" << i_prawy_koniec << "\n";
	cout << "stan T[]: [ ";
	for (int i = i_lewy_poczatek; i <= i_prawy_koniec; ++i)
		cout << T[i] << " ";
	cout << "]\n";
	// dzielimy zbiór, aż dojedziemy do singletonów

	// stoimy pośrodku zbioru [i_lewy_poczatek ; i_prawy_koniec]
	// jeżeli zbiór po naszej lewej jest więcej niż 1 elementowy, to wywołujemy się na nim rekurencyjnie
	// warunek: jeżeli (i_prawy_poczatek - 1 - i_lewy_poczatek > 0) <==> i_prawy_poczatek - i_lewy_poczatek > 1
	if (i_prawy_poczatek - i_lewy_poczatek > 1)
	{
		cout << "ID f() wywolujacej (L): " << ID << "\n";
		merge_sort(T, i_lewy_poczatek, i_prawy_poczatek - 1);
	}

	// jeżeli zbiór po naszej prawej jest więcej niż 1 elementowy to wywpłujemy sie na nim rekurencyjnie
	if (i_prawy_koniec - i_prawy_poczatek > 0)
	{
		cout << "ID f() wywolujacej (P): " << ID << "\n";
		merge_sort(T, i_prawy_poczatek, i_prawy_koniec);
	}

	cout << "ID f() wywolujacej merge(): " << ID << "\n";
	merge(T, i_lewy_poczatek, i_prawy_poczatek, i_prawy_koniec);
}
/// ================================================




template<class C>
void wyswietl_tablice(C T[], int rozmiar, const string& s)
{
	register int licznik = 0; 
	cout << setw(4);
	cout << s << "\n";
	for (int i = 0; i < rozmiar; ++i, ++licznik)
	{
		if (licznik == 20)
		{
			cout << "\n";
			licznik = 0; 
		}

		cout << T[i] << " ";
	}
	cout << "\n\n";
}

int main()
{
	srand(time(NULL));

	int l_elementow;

	cin >> l_elementow;

	int * T = new int[l_elementow];

	for (int i = 0; i < l_elementow; ++i)
		T[i] = rand() % 1000;

	wyswietl_tablice(T, l_elementow, "tablica T[] przed posortowaniem");

	merge_sort(T, 0, l_elementow - 1);

	wyswietl_tablice(T, l_elementow, "tablica T[] po posortowaniu");

	delete[] T;

	return 0;
}
