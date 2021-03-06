
/*
	Quicksort!  
*/


#include <iostream>
#include <time.h>
using namespace std;

/* ALGORYTM SORTUJĄCY */
/// ============================== 
// w naszym podejściu jako pivot wybieramy element środkowy zbioru
// może to być dowolna inna wartość, mediana, element losowy itd. 
template<class C>
void quicksort(C T[], int ilp, int ipk)
{
	// w naszym podejściu jako pivot wybieramy element środkowy zbioru
	// może to być dowolna inna wartość, mediana, element losowy itd. 
	int i_pivot = (ilp + ipk) / 2; 
	
	// zamieniamy miejscami pivot z ostatnim elementem sortowanej tablicy
	C buffer; 
	buffer = T[ipk]; 
	T[ipk] = T[i_pivot];
	T[i_pivot] = buffer;

	// dzielimy nasz zbiór na 2 partycje 
	// elementy mniejsze do pivotu umieszczamy po lewej stronie środka zbioru
	// elementy większe od pivotu umieszczamy po prawej stronie środka zbioru
	// pozycja elementów równych pivotowi nie musi być zmieniana
	// i to bieżący iterator lecący przez zbiór. Warunek kończący 
	// j jest iteratorem pilnującym element który będziemy zamieniać. 
	// i < ipk bo T[ipk] to teraz pivot, więc nie ma sensu go porównywać z samym sobą. 
	// robimy to pętlą while, bo potrzebujemy mieć zapamiętane wartości iteratorów na później
	// do rekurencyjnego wywoływania się na partycjach
	register int i = ilp, j = ilp; 
	while (i < ipk)
	{
		// jeżeli przeglądająć tablicę znaleźliśmy element mniejszy od pivotu, to chcemy umieścić go
		// po lewej stronie środka zbioru,
		// pamiętajmy, że T[ipk] przechowuje w sobie wartość piwotu 
		if  (T[i] < T[ipk])
		{
			buffer = T[j]; 
			T[j] = T[i]; 
			T[i] = buffer;
			++j; 
		}
		++i;
	}
	// brak dalszych elementów do przeglądania, teraz pivot, wymieniamy z elementem na pozycji j-tej (bo pivot < T[j] -- gdyby było inaczej
	// to nasz algorytm by zmienił pozycję T[j] gdy był tam iterator i (chyba jasne xD))
	// btw. jest to kluczowe, aby zamienić te elementy, bo na lewo od iteratora j mamy elementy mniejsze równe
	// od pivotu, a na prawo od niego, elementy większe od pivotu, więc pomiędzy (dokładnie na indeks j)
	// należy wstawić pivot
	buffer = T[j]; 
	T[j] = T[ipk];
	T[ipk] = buffer;

	// po wykonaniu tej pętli powinniśmy mieć tablicę podzieiloną na dwie partycje, wszystkie elementy 
	// mniejsze od pivotu powinny znaleźć się na indeksach mniejszych od j. 

	// teraz wywołujemy się rekurencyjnie na lewej i na prawej partycji
	// jeżeli lewa partycja jest co najmniej 2 elementowa to wywołujemy się na niej
	if (ilp < j)
		quicksort(T, ilp, j - 1);		

	// analogicznie dla prawej partycji 
	// jeżeli prawa partycja jest co najmniej 2 elementowa to się na niej wywołujemy 
	if (j + 1 < ipk)
		quicksort(T, j + 1, ipk);
	
}
/// ============================== 

template<class C>
void wyswietl_tablice(C T[], int l_elementow, const string& s)
{
	int licznik = 0;
	cout << s << "\n";
	for (int i = 0; i < l_elementow; ++i, ++licznik)
	{
		if (licznik == 15)
		{
			cout << "\n"; 
			licznik = 0; 
		}

		cout << T[i] << " ";
	}
	cout << "\n";
}

int main()
{
	srand(time(NULL));

	int l_elementow;

	cin >> l_elementow;

	int * T = new int[l_elementow];

	for (int i = 0; i < l_elementow; ++i)
		T[i] = rand() % 1000;

	wyswietl_tablice(T, l_elementow, "T[] przed sortowaniem");

	// sortowanie
	quicksort(T, 0, l_elementow - 1);

	wyswietl_tablice(T, l_elementow, "T[] po sortowaniu");



	delete[] T;
	return 0; 
}
