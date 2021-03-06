//---------------------------------------------------------------------------
#ifndef vykresliH
#define vykresliH
#include <vcl.h>
#include "vektory.h"
#include "my.h"
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class Cvykresli
{
	private:
	bool lezi_v_pasmu(TCanvas *c,long X,long Y,long x1,long y1,long x2,long y2,long x3,long y3,long x4,long y4);
	void SG(Cvektory::TVozik *ukaz);//zaji�tuje z�kladn� funkcionalitu technologick�ho objektu v re�imu S&G p�i vykreslov�n� simulaci
	void STOPKA(Cvektory::TVozik *ukaz);//zaji�tuje z�kladn� funkcionalitu technologick�ho objektu STOPKA p�i vykreslov�n� simulaci
	bool KOLIZE(Cvektory::TVozik *V1,Cvektory::TVozik *V2);//vrac� logickou hodnotu zda do�lo �i nedo�lo ke kolizi s jin�m voz�kem
	void vykresli_proces(TCanvas *canv, AnsiString shortname, TColor color,short typ, long X1, long X2,long Y);//vykresl� jeden d�l�� �asov� proces (obdeln��ek procesu objektu) pro jeden voz�k, vyta�eno pouze kv�li p�ehlednosti
	void vypis_mezivozikovy_takt(TCanvas *canv,Cvektory::TVozik *vozik, double X,long Y,bool index=false);//pouze pro zp�ehledn�n� zapisu, textov� v�pis a k�ta mezivoz�kov�ho taktu
	void vytizenost_procesu(TCanvas *canv, Cvektory::TProces *P,double X,int Y);
	void vykresli_Xosy(TCanvas *canv);//vykresl� statick� svislice na �asov� osy

	public:
	Cvykresli();//konstruktor
	Cvektory v;
	Cmy m;

	//--prom�nn� k ��elu filtrace
	struct TTP
	{
		double K;//Krok po kolika minutach se bude zobrazovat
		double OD;//od kter� min se proces za�ne vypisovat
		double DO;//do ktere se bude vypisovat
		double KZ;//kosntatn� konec zakazky v min
		unsigned int Nod;//rozmez� jak� se vyp�e vozik,
		unsigned int Ndo;//rozmez� jak� se vyp�e vozik, pokud bude 0 vypisuj� se v�echny
		bool A;//animace true nebo false
	};TTP TP;//nastaven� modu technologick� procesy

	void vykresli_vektory(TCanvas *canv);
	void vykresli_rectangle(TCanvas *canv, Cvektory::TObjekt *ukaz);
	void prislusnost_cesty(TCanvas *canv,TColor Color,int X,int Y,float A,short N);
	void vykresli_grid(TCanvas *canv, int size_grid=10);
	void vykresli_graf_rezervy(TCanvas *canv);//m�d graf rezerv
	void vykresli_casove_osy(TCanvas *canv);//MARO metoda, celkov� vykreslen� m�du �asov� osy
	void vykresli_vytizenost_objektu(TCanvas *canv);

	double proces(TCanvas *canv, unsigned int n, double X_predchozi, double X, int Y, Cvektory::TCesta *C, Cvektory::TVozik *vozik);
	void vykresli_svislici_na_casove_osy(TCanvas *canv,int X,int Y);//vykresl� pohyblivou svislici yna �asov� osy dle um�st�n� kurzoru my�i
	void zobrazit_label_zamerovac(int X,int Y);//vypi�e labal zam��ova�
	void vykresli_technologicke_procesy(TCanvas *canv);//ROMA metoda, vykresl� graf technologick�ch proces� v��i jednotliv�m t-objekt�m v �ase
	void vykresli_simulaci(TCanvas *canv);//zaji��uje vykreslen� simulace
	void vykresli_linku(TCanvas *canv);//zaji��uje vykreslen� osy linky
	void umisti_vozik(TCanvas *canv,Cvektory::TVozik *ukaz);//zaji��uje um�st�n� voz�ku na lince
	void vykresli_vozik(TCanvas *canv,Cvektory::TVozik *ukaz,long X,long Y,bool NEW);//zaji��uje vykreslen� voz�ku p�i simulaci, pokud je NEW==1, tak se vykresl� nov�, p�i 0 se sma�e star�
	void priprav_palce();//p�id� nov� palec do seznamu PALCE s um�st�n�m p��mo na linku dle stanoven� rozte�e
	void umisti_palec(TCanvas *canv,Cvektory::TPalec *ukaz);//zaji��uje aktu�ln� um�st�n� voz�ku na lince v��i animaci
	void vykresli_palec(TCanvas *canv,double X,double Y,bool NEW);//zaji��uje samotn� vykreslen� voz�ku (rotovan� obdeln�k)
	void rotace_textu(TCanvas *canv, long rotace);//�hel rotace je desetin�ch stupn�
	void set_pen(TCanvas *canv, TColor color, int width, int style=PS_ENDCAP_SQUARE);//vr�t� HANDLE na nastaven� pera,//pop�.PS_ENDCAP_FLAT PS_ENDCAP_ROUND, PS_ENDCAP_SQUARE viz Matou�ek III str. 179 �i http://www.zive.cz/clanky/geometricka-pera/sc-3-a-103079
	void set_color(TCanvas *canv, double time);
	void drawRectText(TCanvas *canv,TRect Rect, UnicodeString Text);
	void editacni_okno(TCanvas *canv, unsigned int X1, unsigned int Y1,unsigned  int X2,unsigned  int Y2, unsigned short int size=1, COLORREF color=clBlack);//nakresl� editacni_okno
	void editacni_okno(TCanvas *canv, TPoint LH, TPoint PD, unsigned short int size=1, COLORREF color=clBlack);//nakresl� editacni_okno
	void sipka(TCanvas *canv,int X, int Y,float azimut,bool bez_vyplne=false, unsigned short int size=3,COLORREF color=clBlack,COLORREF color_brush=clGray,TPenMode=pmCopy);//zajist� vykreslen� �ipky - orientace spojovac� linie
	void odznac_oznac_objekt(TCanvas *canv, Cvektory::TObjekt *p,int posunX=0, int posunY=0, COLORREF color=clBlack);
	void odznac_oznac_objekt_novy(TCanvas *canv, int X, int Y,Cvektory::TObjekt *p);
	void odznac_oznac_objekt_novy_posledni(TCanvas *canv, int X, int Y);
	bool lezi_v_pasmu(TCanvas *c,long X,long Y,Cvektory::TObjekt *p);
	bool lezi_v_pasmu_poslednim(TCanvas *c,long X,long Y);
	void sound();



	short O_width,O_height;//logick� parametry, nezoomovat
	unsigned long cas;//ms
	double PX2MIN;//m���tko PX na MIN
	short KrokY;//rozte� na �asov�ch os�ch
	int WidthCanvasCasoveOsy,HeightCanvasCasoveOsy;
	TPointD PosunT; //v�choz� posunut� obrazu Posunu
	bool mod_vytizenost_objektu;
	short NOLIEX;//NO - 0, LINEAR - 1, EXPO - 2
	bool PROZATIM;//prozatimn� �e�en� aby se zbyte�n� a opakovan� neukl�dalo do PROCES� pokud to nen� treba

	protected:



};
#endif
