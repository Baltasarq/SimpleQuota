//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <string>
#include "uAcercaDe.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TAboutBox *AboutBox;

#include "uSimpleQuota.h"

//---------------------------------------------------------------------
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
        Caption = TForm1::NombreApp.c_str();
        ProductName->Caption = TForm1::NombreApp.c_str();
        Version->Caption = TForm1::VersionApp.c_str();
        Copyright->Caption = "es freeware (c) baltasarq@yahoo.es";
        Comments->Caption =
            (
                "\nEsta herramienta controla el tamaño de unos subdirectorios "
                "en un determinado subdirectorio de un PC"
                "\nEn caso de que se exceda de la quota, le manda un e.mail "
                "al dueño de la misma."
                "\nLa información sobre el directorio a controlar se lee del "
                "archivo " + TForm1::ArchivoConf
                + ", que debe estar presente en el mismo directorio de la "
                "aplicación."
             ).c_str();
        
        Comments->Left = 8;
        Comments->Width = Panel1->Width - 16;
        Comments->Top = 64;
        Comments->Height = abs( Comments->Font->Height ) * 10;
}
//--------------------------------------------------------------------- 
