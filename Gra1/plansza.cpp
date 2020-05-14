#include "plansza.h"

int main()
{
	cout << "Podaj ilosc bomb\n";
	cin >> ilosc_bomb;

	genruj_plansze(); 
	losuj_bomby(ilosc_bomb);

	while (wygrana == 0)
	{
		Sleep(90);
		poruszanie();
		if (czy_wygrana() == true){
			wygrana = 1;
		}
	}

	if (wygrana == 1) {
		cout << "\n Rozbroiles wszystkie bomby. Gratulacje :)";
	}
	if (wygrana == 2){
		cout << "\n Saper myli sie tylko raz. Przegrales :(\n";
	}

	system("pause");
	return 0;
}