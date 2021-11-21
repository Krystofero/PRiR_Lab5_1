# PRiR_Lab5_1
Projekt przedstawia zadanie 1, podpunkty a oraz b z Labolatorium 5 z Programowania Równoległego i Rozproszonego.
Program napisano w języku C. Tworzy p procesów potomnych za pomocą fork()-a. Każdy z procesów 
niezależnie oblicza i wyświetla na ekranie całkę y=4*x-6*x+5 Metodą Trapezów oraz Metodą Kwadratury Gaussa Lagandre'a
w przedziale <a,b>, gdzie a oraz b są losowane w każdym procesie niezależnie oraz a jest zawsze mniejsze od b.

Najpierw załączam do projektu odpowiednie biblioteki:

	#include <stdio.h>
	#include <stdlib.h>
	#include <sys/types.h>
	#include <sys/wait.h>
	#include <unistd.h>
	#include <time.h>
	#include "err.h"

Deklaruję funkcję, dla której chcę obliczyć całkę:

	double funkcja(double x)
	{
		return 4*x-6*x+5;
	}

Funkcja przedstawiająca liczenie całki za pomocą Metody Trapezów(dzielimy nasz przedział <a,b> na n równych częsci, obliczamy odległość między częściami = h , następnie liczymy wartość funkcji w każdym przedziale):

	double MetodaTrapezow(int a, int b, int n) {
		  double calka = 0;
	    double h = (double)(b - a) / n; //przedział <a,b> podzielony na n równych części (h = odleglość między xi a xi+1)

	    int i;
	      for(i = 0; i < n; i++) {
		calka += t.funkcja(a + i * h) + t.funkcja(a + (i + 1) * h);
	    }

	    return h/2 * calka;
	}

Całkę za pomocą Kwadratury Gaussa Legendre'a liczę tylko dla parzystej liczby przedziałów(n) oraz maksymalnie rónwej 10.
Mając podane wagi w tablicach wyznaczam dla nich odpowiednie węzły.
Funkcja przedstawiająca Kwadraturę Gaussa Legendre'a:

	double Kwadratura(int a, int b, int n) {
	    double calka = 0.0;
	    double t = 0.0;
	    double h, h2;
	    int i;

	    if(n % 2 != 0) { //dodatkowe zabezpieczenie przed nieparzystym n
	      n++;
	    }

	      h = (double)(b - a) / 2; //pierwszy współczynnik
	      h2 = (double)(b + a) / 2;//drugi współczynnik

	    switch(n) { //wagi
	      case 2: {
		      double tab[][] = {1.0000000000000000,-0.5773502691896257}, {1.0000000000000000,0.5773502691896257}};
		  }break;
	      case 4: {
		      double tab[][] = {{0.6521451548625461,-0.3399810435848563}, {0.6521451548625461,0.3399810435848563},
			      {0.3478548451374538,-0.8611363115940526}, {0.3478548451374538,0.8611363115940526}};
		  }break;
	      case 6: {
		      double tab[][] = {0.3607615730481386,0.6612093864662645}, {0.3607615730481386,-0.6612093864662645},
			      {0.4679139345726910,-0.2386191860831969}, {0.4679139345726910,0.2386191860831969},
			      {0.1713244923791704,-0.9324695142031521}, {0.1713244923791704,0.9324695142031521}};
		  }break;
	      case 8: {
		      double tab[][] = {{0.3626837833783620,-0.1834346424956498}, {0.3626837833783620,0.1834346424956498},
			      {0.3137066458778873,-0.5255324099163290}, {0.3137066458778873,0.5255324099163290},
			      {0.2223810344533745,-0.7966664774136267}, {0.2223810344533745,0.7966664774136267},
			      {0.1012285362903763,-0.9602898564975363}, {0.1012285362903763,0.9602898564975363}};
		  }break;
	      case 10: {
		      double tab[][] = {{0.2955242247147529,-0.1488743389816312}, {0.2955242247147529,0.1488743389816312},
			      {0.2692667193099963,-0.4333953941292472}, {0.2692667193099963,0.4333953941292472},
			      {0.2190863625159820,-0.6794095682990244}, {0.2190863625159820,0.6794095682990244},
			      {0.1494513491505806,-0.8650633666889845}, {0.1494513491505806,0.8650633666889845},
			      {0.0666713443086881,-0.9739065285171717}, {0.0666713443086881,0.9739065285171717}};
		  }break;
	      default:
	      double tab[][];
	    }

	      for(i = 0; i < n; i++) {
		  t = tab[i][1]; //węzły
		  calka += tab[i][0] * funkcja(h * t + h2);
	      }

	      return (double)calka;
	}


W funkcji main najpierw deklaruję odpowiednie zmienne:

	 pid_t pid;
	 int i, procesy;
	 int a, b, n, seed;
	 time_t t;

Następnie wczytuję porządaną liczbę procesów:

	 printf("Podaj ilosc procesow: ");
	 scanf("%d", &procesy);
 
W pętli for dla każdego procesu sprawdzamy czy fork() jest równe 0 - wtedy ustawiamy ziarno, losujemy zakres przedziału <a,b> oraz n. Następnie wypisywane są wylosowane wartości zmiennych oraz wywoływane są funkcje o tych argumentach, liczące wartość całki za pomocą odpowiednich metod. Wypisywane są wartości całki i numery procesów potomnych. 
W pętli istnieje również możliwość wyłapania błędu w fork'u.

	for (i = 1; i <= procesy; i++){
	    switch (pid = fork()) {
		case -1:
		    perror("Error in fork\n");
		case 0:
			    seed = time(&t);
			    srand(seed + i);
			    n = rand()%50;
			    a = rand();
			    b = (a + 1) + rand();

			    printf("a = %d\nb = %d\nn = %d\n", a, b, n);
			    printf("Jestem procesem potomnym. Moj PID = %d\n", getpid());
		    printf("Wynik uzyskany za pomoca Metody Trapezow to: %f\n", MetodaTrapezow(a, b, n));

				n = 1 + rand() % 10;
				printf("a = %d\nb = %d\nn = %d\n", a, b, n);
		    printf("Wynik uzyskany za pomoca Kwadratury Gaussa Legendrea to: %f\n", Kwadratura(a, b, n));
		    return 0;
		default:
		printf("Jestem procesem macierzystym. Moj PID = %d\n", getpid());
	    } 
	 }
 
