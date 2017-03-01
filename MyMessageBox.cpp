//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MyMessageBox.h"
#include "unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMyMessageBox *MyMessageBox;
//---------------------------------------------------------------------------
__fastcall TMyMessageBox::TMyMessageBox(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMyMessageBox::FormShow(TObject *Sender)
{
	dynamicka_velikost_formulare();//vol�n� nastaven� dynamick� velikost formul��e podle p�sma
}
//---------------------------------------------------------------------------
void TMyMessageBox::dynamicka_velikost_formulare()
{
	if(Label1->Width+Label1->Left>CheckBox_pamatovat->Left+CheckBox_pamatovat->Width)
	{
		MyMessageBox->Width=Label1->Width+8+8;
		Label1->Left=6;//vycentruje - logick� vypl�v� ze z�pisu o ��dek v��e 8,ale 6 je OK
	}
	else //v tomto p��pad� nech�v� popisek vlevo
	MyMessageBox->Width=(CheckBox_pamatovat->Left+CheckBox_pamatovat->Width+5);

	Button_OK->Left=MyMessageBox->Width/2-Button_OK->Width/2;//vycentruje
}
//---------------------------------------------------------------------------
int TMyMessageBox::ShowMyMessageBox(long Left,long Top,UnicodeString Caption_text, UnicodeString Label1_text)
{
	MyMessageBox->Caption=Caption_text;
	MyMessageBox->Left=Left;
	MyMessageBox->Top=Top;
	Label1->Caption=Label1_text;
	return ShowModal();
}
//---------------------------------------------------------------------------




