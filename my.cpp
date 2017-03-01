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
		return (fyzicka/Form1->Zoom+Form1->Posun.x)*Form1->m2px;
}
double Cmy::P2Ly(long fyzicka)
{
		return -1.0*(fyzicka/Form1->Zoom+Form1->Posun.y)*Form1->m2px;
}
/////////////////////////////////////////////////////////////////////////////
float Cmy::delka(double X1,double Y1,double X2,double Y2)
{
		return sqrt(pow(X2-X1,2)+ pow(Y2-Y1,2));
}
/////////////////////////////////////////////////////////////////////////////
float Cmy::azimut(double X1,double Y1,double X2,double Y2)
{
		try{
			float A=acos((Y2-Y1)/(delka(X1,Y1,X2,Y2)*1.0))*180/M_PI;
			if(X2<X1)A=360-A;
			return A;
		}
		catch(...)
		{return 0;}
}
float Cmy::uhel(double X1,double Y1,double X2,double Y2)
{
		try{
			return acos((Y2-Y1)/(delka(X1,Y1,X2,Y2)*1.0))*180/M_PI;
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


