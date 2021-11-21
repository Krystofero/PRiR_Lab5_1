#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include "err.h"

double funkcja(double x)
{
	return 4*x-6*x+5;
}

double MetodaTrapezow(int a, int b, int n) {
	double calka = 0;
    double h = (double)(b - a) / n; //przedzia³ <a,b> podzielony na n równych czêœci (h = odlegloœæ miêdzy xi a xi+1)
    
	int i;
    for(i = 0; i < n; i++) {
    	calka += t.funkcja(a + i * h) + t.funkcja(a + (i + 1) * h);
	}

	return h/2 * calka;
}

double Kwadratura(int a, int b, int n) {
    double calka = 0.0;
    double t = 0.0;
	double h, h2;
	int i;
	
	if(n % 2 != 0) { //dodatkowe zabezpieczenie przed nieparzystym n
		n++;
	}
	
    h = (double)(b - a) / 2; //pierwszy wspó³czynnik
    h2 = (double)(b + a) / 2;//drugi wspó³czynnik
	
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
        t = tab[i][1]; //wêz³y
        calka += tab[i][0] * funkcja(h * t + h2);
    }

    return (double)calka;
}


int main ()
{
 pid_t pid;
 int i, procesy;
 int a, b, n, seed;
 time_t t;
 printf("Podaj ilosc procesow: ");
 scanf("%d", &procesy);

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
 return 0;
}
