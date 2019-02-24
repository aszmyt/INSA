#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <string>
#include <climits>
#include <ctime>
#define MAX 99999999

using namespace std;




    // =================== //
    //     KONSTRUKTOR    //
    // =================== //

class klasaI
{
	public:
	int numer;
	int czas;

	klasaI(int numerek, int czasik)
	{
		numer=numerek;
		czas=czasik;
	}
};




    // =================== //
    //      KLASA 2        //
    // =================== //

class INSA
{
	public:

		int ilosc_zadan;  //ilosc elementow
		int ilosc_maszyn; //ilosc maszyn
		int tablica[20001][10];    //tablica statyczna
		int tablica_I[101][101];            // tablica tablica_I
		vector <klasaI> sort_po_czasie;   //sort vectora
        int cmax;                         //liczenie Cmaxa
		INSA(){}                          //deklaracja funkcji INSA

    // =================== //
    //      ZEROWANIE1     //
    // =================== //
	void zerowanie1()
	{
		for(int i=0; i <=ilosc_zadan ; i++)
			for(int j=0 ; j<=ilosc_maszyn ; j++)
				tablica_I[i][j]=0;            //zerujemy tablica_I
	}

    // =================== //
    //      ZEROWANIE2     //
    // =================== //

	void zerowanie2()
	{
		for(int i=0; i <=ilosc_maszyn*ilosc_zadan ; i++)
			for(int j=0 ; j<10 ; j++)
				tablica[i][j]=0;
	}



    // =================== //
    //      R i Q          //
    // =================== //
	int sort_po_Q(int i)
	{
		int nast_kol=0;
		int nast_masz=0;
		if(tablica[i][9]!=0) return tablica[i][9];
		else
		{
			if(tablica[i][3]==0&&tablica[i][5]==0)
				return tablica[i][9]=tablica[i][2];
			else
			{
                if(tablica[i][5]!=0)
					nast_masz=sort_po_Q(tablica[i][5]);
				if(tablica[i][3]!=0)
					nast_kol=sort_po_Q(tablica[i][3]);
				return tablica[i][9]= nast_masz>nast_kol ? nast_masz+tablica[i][2] : nast_kol+tablica[i][2];
			}
		}
	}
	int sort_po_R(int i)
	{
		int pop_kol=0;
		int pop_masz=0;
		if(tablica[i][8]!=0)
			return tablica[i][8];
		else
		{
			if(tablica[i][4]==0&&tablica[i][6]==0)
				return tablica[i][8]=tablica[i][2];
			else
			{
				if(tablica[i][4]!=0)
					pop_kol=sort_po_R(tablica[i][4]);
				if(tablica[i][6]!=0)
					pop_masz=sort_po_R(tablica[i][6]);
				return tablica[i][8]= (pop_masz>pop_kol) ? pop_masz+tablica[i][2] : pop_kol+tablica[i][2];
			}
		}
	}
	int max(int a, int b)
	{
	    if(a<b)
            return b;
        else
            return a;
        }




    // =================== //
    //      tablica_I        //
    // =================== //
	void tablica_dane()
	{
		int numer = 0;
		for(int i =tablica_I[0][0] ; i<=ilosc_maszyn*ilosc_zadan; i++)
		{
			numer=sort_po_czasie[i].numer;
			int maszyna=tablica[numer][1];
			tablica_I[maszyna][++tablica_I[maszyna][0]] = numer;
			tablica_I[0][0]++;
			int rozmiar=tablica_I[tablica[numer][1]][0];
			int min_czas=0;
			int czas=0;
			int min_i=0;

			if(rozmiar>1)
			{
				min_czas=ustaw_kolejke(0,numer,tablica_I[maszyna][1]);
				min_i=0;
				for(int i = 1; i<rozmiar-1;i++)
				{
					czas=ustaw_kolejke(tablica_I[maszyna][i],numer,tablica_I[maszyna][i+1]);
					if(czas<min_czas)
					{
						min_czas=czas;
						min_i=i;
					}
				}
				czas=ustaw_kolejke(tablica_I[maszyna][rozmiar-1],numer,0);
				if(czas<min_czas)
				{
					min_czas=czas;
					min_i=rozmiar-1;
				}
                CMax(min_czas);
				if(min_i==0)
					kolejka(0,numer,tablica_I[maszyna][min_i+1]);
				else if(min_i==rozmiar-1)
					kolejka(tablica_I[maszyna][min_i],numer,0);
				else
					kolejka(tablica_I[maszyna][min_i],numer,tablica_I[maszyna][min_i+1]);
				//ustawienie poprawnej kolejnosci
				int temp=0;
				for(int i = min_i+1 ; i<rozmiar ; i++)
				{
					temp=tablica_I[maszyna][i];
					tablica_I[maszyna][i]=numer;
					numer=temp;
				}
				tablica_I[maszyna][rozmiar]=numer;
				return;
			}
		}
	}







    // ============================== //
    //      NAST_POPRZ_KOLEJ          //
    // ============================== //
	void kolejka(int l, int sr, int pr)
	{
		if(l) tablica[l][5]=sr;
		tablica[sr][5]=pr;
		tablica[sr][6]=l;
		if(pr) tablica[pr][6]=sr;
	}


    // =================== //
    //      ustaw_kolejke         //
    // =================== //
	int ustaw_kolejke(int poprzednik_kolejn, int srodek, int nastepnik_kolejn)
	{
		int czas = tablica[srodek][2];
		czas+= (tablica[poprzednik_kolejn][8]>tablica[tablica[srodek][4]][8]) ? tablica[poprzednik_kolejn][8] : tablica[tablica[srodek][4]][8];
		czas+= (tablica[nastepnik_kolejn][9]>tablica[tablica[srodek][3]][9]) ? tablica[nastepnik_kolejn][9] : tablica[tablica[srodek][3]][9];
		return czas;
	}



    // =================== //
    //      C MAX          //
    // =================== //
    void CMax(int di)
    {
        cmax = max (cmax, di);
	}

};











// =================== //
//      M A I N        //
// =================== //

int main()
{
    cout<<"ALGORYTM INSA: "<<endl;
    int w;
    double counter = 0;
	INSA obiekt;
    fstream plik;
	fstream wyj;
	//unsigned int i, j;
    int temp_numer, temp_czas;


    // --------------------- //
	// ------  ODCZYT ------ //
    // --------------------- //
    plik.open("data000.txt",ios::in);
	wyj.open("dane_wyjsciowe.txt",ios::out);


	for(int i=0 ; i<=80 ; i++)
	{
   // clock_t start = clock();
     // Wczytywanie instancji z pliku
     obiekt.cmax=0;
	 obiekt.sort_po_czasie.clear();

	 obiekt.zerowanie2();
	 obiekt.zerowanie1();
	 char znak;
	 plik>>znak>>znak>>znak>>znak;
	 plik>>obiekt.ilosc_zadan;
	 plik>>obiekt.ilosc_maszyn;
     for(int i=1; i<=obiekt.ilosc_zadan*obiekt.ilosc_maszyn; i++)
	 {
	  obiekt.tablica[i][0]=i;
	  plik>>obiekt.tablica[i][1]>>obiekt.tablica[i][2];
	  obiekt.sort_po_czasie.push_back(klasaI(i,obiekt.tablica[i][2]));
     }
     plik.clear();
     //

	 for(int i=0; i <=obiekt.ilosc_maszyn*obiekt.ilosc_zadan ; i++)
	 {
 	  if(i%obiekt.ilosc_maszyn!=0) obiekt.tablica[i][3]=i+1; //nastepnik
	  if(i%obiekt.ilosc_maszyn!=1) obiekt.tablica[i][4]=i-1; //poprzednik z kol z indexem 4
	 }

	 for(int i = obiekt.ilosc_maszyn*obiekt.ilosc_zadan ; i>0 ; i--)
	 {
	  obiekt.sort_po_R(i);
	  obiekt.sort_po_Q(obiekt.ilosc_maszyn*obiekt.ilosc_zadan+1-i);
     }

     for (int i = 0; i<obiekt.sort_po_czasie.size(); i++)
      for (int j=0; j<obiekt.sort_po_czasie.size()-1; j++)
      {
       if (obiekt.sort_po_czasie[j].czas < obiekt.sort_po_czasie[j+1].czas)
        {
         temp_numer = obiekt.sort_po_czasie[j+1].numer;
         temp_czas = obiekt.sort_po_czasie[j+1].czas;
         obiekt.sort_po_czasie[j+1].numer = obiekt.sort_po_czasie[j].numer;
         obiekt.sort_po_czasie[j+1].czas = obiekt.sort_po_czasie[j].czas;
         obiekt.sort_po_czasie[j].czas=temp_czas;
         obiekt.sort_po_czasie[j].numer=temp_numer;
        }
       }

		while(obiekt.tablica_I[0][0]<obiekt.ilosc_maszyn*obiekt.ilosc_zadan)
		{
		 obiekt.tablica_dane();
		 // Zerowanie RQ
		 for(int i = 1 ; i < obiekt.ilosc_maszyn*obiekt.ilosc_zadan+1 ; i++)
		 {
		  obiekt.tablica[i][8]=0;
		  obiekt.tablica[i][9]=0;
		 }
         //Wyliczanie RQ
         for(int i = obiekt.ilosc_maszyn*obiekt.ilosc_zadan ; i>0 ; i--)
	     {
	      obiekt.sort_po_R(i);
	      obiekt.sort_po_Q(obiekt.ilosc_maszyn*obiekt.ilosc_zadan+1-i);
         }
		}

	 // Zapisywanie do pliku
	 for(int i = 1; i<=obiekt.ilosc_maszyn; i++)
	 {
	  for(int j=1 ; j<=obiekt.ilosc_zadan; j++)
	   cout<<obiekt.tablica_I[i][j]<<" ";
	  cout<<endl;
	 }
	 cout<<"cmax="<<obiekt.cmax;
	 cout<<endl;

	}

	//cout << "Czas dzia³ania " << counter/1000 << "s\n";
	system("pause");
	return 0;
}
