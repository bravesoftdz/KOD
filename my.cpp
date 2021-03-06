//---------------------------------------------------------------------------
#pragma hdrstop
#include "my.h"
#include "Unit1.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
/////////////////////////////////////////////////////////////////////////////
//fce pro zaokrouhlen� realn�ho ��sla na nejbl힚� cel� ��slo
long Cmy::round(double number)
{
	if(number>0)
	return (long)(number+0.5);//pro kladn� hodnoty
	else
	return (long)(number-0.5);//pro z�porn� hodnoty
}
/////////////////////////////////////////////////////////////////////////////
//zaokrouhl� na po�et desetinn�ch m�st dle precison
double Cmy::round2double(double number,unsigned short precision)
{
	return number=round(number*pow(10.0,precision))/pow(10.0,precision);
}
/////////////////////////////////////////////////////////////////////////////
//ov���, zda dan� ��slo je cel� ��slo
bool Cmy::cele_cislo(double number)
{
	 return number==floor(number);
}
/////////////////////////////////////////////////////////////////////////////
//modulo pro double hodnoty
double Cmy::mod_d(double number1,double number2)
{
	 //nedota�en�: return number1-floor(number1/number2)*number2;
	 return fmod(number1,number2);//toto ale tak� nefunguje pro druhou re�lnou hodnotu dob�e
}
/////////////////////////////////////////////////////////////////////////////
//P�evede logick� sou�adnice na fyzick� (displej za��zen�) , vraci fyzick� sou�adnice
TPoint Cmy::L2P(double logickaX, double logickaY)
{
	return TPoint(L2Px(logickaX),L2Py(logickaY));
}
TPoint Cmy::L2P(TPointD logicke)
{
	return L2P(logicke.x,logicke.y);
}
long Cmy::L2Px(double logicka)
{
	//return round(Form1->Posun.X+logicka*Form1->Zoom);
	return round(Form1->Zoom*(logicka/Form1->m2px-Form1->Posun.x));
}
long Cmy::L2Py(double logicka)
{
	//return round(Form1->Posun.Y+logicka*Form1->Zoom);
	return round(Form1->Zoom*(-1*logicka/Form1->m2px-Form1->Posun.y));
}
/////////////////////////////////////////////////////////////////////////////
//P�evede  fyzick� na logick� sou�adnice (displej za��zen�) , vraci logick� sou�adnice
TPointD Cmy::P2L(TPoint fyzicke)
{
		TPointD logicke;logicke.x=P2Lx(fyzicke.X);logicke.y=P2Ly(fyzicke.Y);
		return logicke;
}
TPointD Cmy::P2L(long fyzickaX,long fyzickaY)
{
		TPointD logicke;logicke.x=P2Lx(fyzickaX);logicke.y=P2Ly(fyzickaY);
		return logicke;
}
double Cmy::P2Lx(long fyzicka)
{
		try{
			return (fyzicka/Form1->Zoom+Form1->Posun.x)*Form1->m2px;
		}
		catch(...)
		{return 0;}
}
double Cmy::P2Ly(long fyzicka)
{
		try{
		return -1.0*(fyzicka/Form1->Zoom+Form1->Posun.y)*Form1->m2px;
    }
		catch(...)
		{return 0;}
}
/////////////////////////////////////////////////////////////////////////////
double Cmy::delka(double X1,double Y1,double X2,double Y2)
{
		return sqrt(pow(X2-X1,2)+ pow(Y2-Y1,2));
}
/////////////////////////////////////////////////////////////////////////////
double Cmy::azimut(double X1,double Y1,double X2,double Y2)
{
		try{
			if(delka(X1,Y1,X2,Y2)!=0)
			{
				float A=acos((Y2-Y1)/(delka(X1,Y1,X2,Y2)*1.0))*180/M_PI;
				if(X2<X1)A=360-A;
				return A;
			}
			else return 0;
		}
		catch(...)
		{return 0;}
}
double Cmy::uhel(double X1,double Y1,double X2,double Y2)
{
		try{
			if(delka(X1,Y1,X2,Y2)!=0)
			{
				return acos((Y2-Y1)/(delka(X1,Y1,X2,Y2)*1.0))*180/M_PI;
			}
			else return 0;
		}
		catch(...)
		{return 0;}
}
/////////////////////////////////////////////////////////////////////////////
//rotace
TPointD Cmy::rotace(double delka, double akt_uhel, double rotace)
{
		double Uhel=fmod(akt_uhel+rotace,360.0);// v�etn� o�et�en� p�ete�en� p�es 360 stup��
		if(Uhel<0){Uhel+=360;}//pro z�porn� hodnoty

		short ZnamenkoX,ZnamenkoY;

		if (Uhel>=0 && Uhel< 90)
    {
			ZnamenkoX=1;ZnamenkoY=-1;
    }
		if (Uhel>=90 && Uhel<= 180)
		{
			Uhel=180-Uhel;
    	ZnamenkoX=1;ZnamenkoY=1;
    }
		if (Uhel>180 && Uhel<= 270)
    {
			Uhel=Uhel-180;
    	ZnamenkoX=-1;ZnamenkoY=1;
    }
		if (Uhel>270 && Uhel<= 360)
    {
			Uhel=360-Uhel;
    	ZnamenkoX=-1;ZnamenkoY=-1;
    }

    Uhel=Uhel*(M_PI/180);//pro prevod ze stupnu na radiany
		TPointD ret;
		ret.x=sin(Uhel)*delka*ZnamenkoX;//posun na Xove ose
		ret.y=cos(Uhel)*delka*ZnamenkoY;//posun na Yove ose

	return ret;
}
/////////////////////////////////////////////////////////////////////////////
long Cmy::LeziVblizkostiUsecky(double x, double y, double X1, double Y1, double X2, double Y2)
{
	double a=Y2-Y1;
	double b=X1-X2;
	double c=-a*X1-b*Y1;

  if(X2==X1)//pokud jsou v jedn� "linii" tj. je abs. svisl�
  {
	if((Y1<=y && y<=Y2 && Y1<Y2) || (Y2<=y && y<=Y1 && Y2<Y1))
		return round(fabs((a*x + b*y + c) / sqrt(fabs(a*a + b*b))));
    else
	  return 2147483647;//vrac� nesmysln� vysok� ��slo jako ne�sp�ch (z�ejm� le�� na p��mce ale ne na �se�ce)
  }
  else//pro ostatn� situace
  {
	if(((X1<=x && x<=X2 && X1<X2) || (X2<=x && x<=X1 && X2<X1)) && ((Y1<=y && y<=Y2 && Y1<Y2) || (Y2<=y && y<=Y1 && Y2<Y1)))
		return round(fabs((a*x + b*y + c) / sqrt(fabs(a*a + b*b))));
	else
		return 2147483647;//vrac� nesmysln� vysok� ��slo jako ne�sp�ch (z�ejm� le�� na p��mce ale ne na �se�ce)
	}
}
/////////////////////////////////////////////////////////////////////////////
TPointDbool Cmy::zkratit_polygon_na_roztec(double d, double r,double xp, double yp, double x0, double y0, double x1, double y1)//d - delka linky,r - roztec palcuxp, yp - souradnice oznaceneho bodu x0, y0, x1, y1- souradnice sousedu k oznacenemu bodu
{
		TPointDbool RET;
		// zkratit linku o z, d je delka linky, r je roztec zubu
		double z=fmod(d,r);

		// kontrola vhodnosti vybraneho bodu
		double d0=sqrt(pow((x0-xp),2)+pow((y0-yp),2));
		double d1=sqrt(pow((x1-xp),2)+pow((y1-yp),2));
		double dt=sqrt(pow((x0-x1),2)+pow((y0-y1),2));
		double sq=d0+d1-dt-z;

		if (sq<0)
			RET.b=false; //pokud nebude splnena trojuhelnikova nerovnost, nemuze se dany bod pouzit
		else
		{
			double d0n=((d0+d1-z)*d0)/(d0+d1); // prepocitani ocekavanych delek
			double d1n=((d0+d1-z)*d1)/(d0+d1);

			double m=((pow(d0n,2)-pow(d1n,2))/2*dt)+(dt/2); // prusecik pocitan metodikou popsanou na wikibooks(prusecik dvou kruznic)
			ShowMessage(pow(d0n,2)); ShowMessage(pow(m,2));
			double v=sqrt(fabs(pow(d0n,2)-pow(m,2)));// dela se to trojuhelnikama  <--DOPLN�NA ABSOLUTN� HODNOTA PRO RE�LN� ��SLA

			double xs=x0+(m/dt)*(x1-x0); // vypocet pruseciku spojnice bodu s osou
			double ys=y0+(m/dt)*(y1-y0);

			double xn1=xs-(v/dt)*(y0-y1); // mozne souradnice novych bodu
			double yn1=ys+(v/dt)*(x0-x1);
			double xn2=xs+(v/dt)*(y0-y1);
			double yn2=ys-(v/dt)*(x0-x1);

			double dist1=sqrt(pow((xn1-xp),2)+pow((yn1-yp),2)); // nalezeni blizsiho bodu
			double dist2=sqrt(pow((xn2-xp),2)+pow((yn2-yp),2));

      double xn,yn;

			if (dist1<dist2)
			{
				xn=xn1;
				yn=yn1;
			}
			else
			{
				xn=xn2;
				yn=yn2;
      }

			RET.b=true; RET.x=xn; RET.y=yn;
		}

		return RET;
}
/////////////////////////////////////////////////////////////////////////////
double Cmy::cekani_na_palec(double cas, double roztec_palcu,double rychlost_dopravniku,int funkce)//vr�t� dobu �ek�n� na palec v min, rozte�e je v mm resp. v m za z minu u rychlosti dopravniku
{

		//if(zohlednit && rezim!=1)//pokud se jedn� o kontinu�ln� re�im ne�e�� se, p�edpokl�d� se, �e jede na stejn�m dopravn�ku
		{
			//exaktn� v�po�et je pou�iteln� jenom v p��pad zn�me goemetrie, nav�c obsahuje chybu
			//double cas_presunu_mezi_palci=(60*roztec_palcu)/(rychlost_dopravniku*100);  //to 100 je p�evod na cm z m
			//nn, necelo��seln� zbyte double zbytek_po_deleni=(cas*60/cas_presunu_mezi_palci)-floor(cas*60/cas_presunu_mezi_palci);//tzn. kde se nach�z�
			//return cas_presunu_mezi_palci*zbytek_po_deleni;
			//jako st�edn� hodnota vypl�vaj�c� z norm�ln�ho pravd�podonostn�ho rozd�len� hodnot
			//(cas_presunu_mezi_palci-0)/2 resp. (max-min)/2
			//return (roztec_palcu/(rychlost_dopravniku*1000.0))/2.0; //vr�t� dobu �ek�n� na palec v min, rozte�e je v mm resp. v m za z minu u rychlosti dopravniku
		}
		//else return 0;

		//vr�t� dobu �ek�n� na palec v min, rozte�e je v mm resp. v m za z minu u rychlosti dopravniku
		double RET=0.0;
		double MIN=0.0;double MAX=roztec_palcu/(rychlost_dopravniku*1000.0);
		double ZOI=0.001;//korekce pro zaji�t�n� zprava otev�en�ho intervalu (nem��e b�t uzav�en�, proto�e to nen� re�ln�, doch�z� v takov� situaci je�t� k uchopen� p�vodn�m palcem), ��d kokekce zvolen neexaktn�, pouze dle �vahy
		switch(funkce)
		{
				case 0:RET=MIN;break;//nic resp minimum=0, ne�ek� na palec v�bec bu� vy�el p�esn� nebo se nezohled�uje
				case 1:RET=(MAX-ZOI+MIN)/2;break;//st�edn� hodnota (v tomto p��pad� i pr�m�r) dle norm�ln�ho rozd�len� pro hodnoty <0,max)
				case 2:RET=fmod(rand(),MAX*1000)/1000.0+MIN;break;//n�hodn� hodnota v rozmez� <0,max) �ek�n� na palce, zde ZOI nen� nutn� zohled�ovat, proto�e ji� vypl�v� z pou�it�ho algoritmu
				case 3:RET=MAX-ZOI;break;//max.mo�n� hodnota �ek�n� na pale
				case 4:/*RET=tady bude exaktn� v�po�et pro geometrii*/break;
		}
		return RET;

}
/////////////////////////////////////////////////////////////////////////////
double Cmy::prejezd_voziku(double delka, double rychlost_dopravniku)
{
	return delka/rychlost_dopravniku;
}
/////////////////////////////////////////////////////////////////////////////
//zesv�tl� barvu
TColor Cmy::clIntensive(TColor C,short A)//+A - m�ra zesv�tlen�,-A m�ra ztmaven�
{
	BYTE R=GetRValue(C); BYTE G=GetGValue(C); BYTE B=GetBValue(C);
	if(A>0)//zesv�tlen�
	{
		if(A>255-R)R=255;else R+=A;
		if(A>255-G)G=255;else G+=A;
		if(A>255-B)B=255;else B+=A;
	}
	if(A<0)//ztmaven�
	{
		if((-1)*A>R)R=0;else R+=A;
		if((-1)*A>G)G=0;else G+=A;
		if((-1)*A>B)B=0;else B+=A;
	}
	return (TColor)RGB(R,G,B);
}
/////////////////////////////////////////////////////////////////////////////
