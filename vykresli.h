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

	public:
	Cvykresli();//konstruktor
	Cvektory v;
	Cmy m;

	void vykresli_vektory(TCanvas *canv);
	void vykresli_rectangle(TCanvas *canv, Cvektory::TObjekt *ukaz);
	void vykresli_grid(TCanvas *canv, int size_grid=10);
	void vykresli_graf_rezervy(TCanvas *canv);//m�d graf rezerv
	void vykresli_casove_osy(TCanvas *canv);//celkov� vykreslen� m�du �asov� osy
	void vykresli_Xosy(TCanvas *canv);//vykresl� statick� svislice na �asov� osy
	void vykresli_casovou_osu(TCanvas *canv, AnsiString shortname, TColor color, int X1, int X2,int Y, short KrokY);
	void vykresli_svislici_na_casove_osy(TCanvas *canv,int X);//vykresl� pohyblivou svislici na �asov� osy dle um�st�n� kurzoru my�i
	void vykresli_simulaci(TCanvas *canv);//zaji��uje vykreslen� simulace
	void vykresli_linku(TCanvas *canv);//zaji��uje vykreslen� osy linky
	void umisti_vozik(TCanvas *canv,Cvektory::TVozik *ukaz);//zaji��uje um�st�n� voz�ku na lince
	void vykresli_vozik(TCanvas *canv,Cvektory::TVozik *ukaz,long X,long Y,bool NEW);//zaji��uje vykreslen� voz�ku p�i simulaci, pokud je NEW==1, tak se vykresl� nov�, p�i 0 se sma�e star�
	void priprav_palce();//p�id� nov� palec do seznamu PALCE s um�st�n�m p��mo na linku dle stanoven� rozte�e
	void umisti_palec(TCanvas *canv,Cvektory::TPalec *ukaz);//zaji��uje aktu�ln� um�st�n� voz�ku na lince v��i animaci
	void vykresli_palec(TCanvas *canv,double X,double Y,bool NEW);//zaji��uje samotn� vykreslen� voz�ku (rotovan� obdeln�k)
	void rotace_textu(TCanvas *canv, long rotace);//�hel rotace je desetin�ch stupn�
	void set_pen(TCanvas *canv, TColor color, int width, int style=PS_ENDCAP_FLAT);//vr�t� HANDLE na nastaven� pera,//pop�.PS_ENDCAP_FLAT PS_ENDCAP_ROUND, PS_ENDCAP_SQUERE viz Matou�ek III str. 179
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
	int WidthCanvasCasoveOsy,HeightCanvasCasoveOsy;

	protected:



};
#endif
