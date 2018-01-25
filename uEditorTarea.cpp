//---------------------------------------------------------------------------

#include <vcl.h>
#include <algorithm>
#pragma hdrstop

#include "uEditorTarea.h"
#include "uSimpleQuota.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;

using namespace std;

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(unsigned int num, TComponent* Owner)
        : TForm(Owner), numTarea(num), cambiandoDesdeTexto(false)
{
        Tarea &t = *( Form1->lt[ numTarea ] );
        
        // Preparar ventana
        Constraints->MinWidth = Width;
        Constraints->MinHeight = Height;
        Constraints->MaxWidth = Width;
        Constraints->MaxHeight = Height;
        Caption = ( TForm1::NombreApp + " - editor de tareas" ).c_str();

        // Preparar los campos
        edDir->Text = t.getDir().c_str();
        edUsr->Text = t.getUsr().c_str();
        edHost->Text = t.getHost().c_str();
        edTam->Text = IntToStr( t.getMTam() );
}

//---------------------------------------------------------------------------
void __fastcall TForm2::botCancelClick(TObject *Sender)
{
        Close();
}

//---------------------------------------------------------------------------
void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
        Action = caFree;
}

//---------------------------------------------------------------------------
void __fastcall TForm2::botGuardarClick(TObject *Sender)
{
       string tam = edTam->Text.c_str();
       replace( tam.begin(), tam.end(), ' ', '0' );

       Form1->lt[ numTarea ]->reemplazar(
              edDir->Text.c_str(),
              tam,
              edUsr->Text.c_str(),
              edHost->Text.c_str()
       );

       Form1->ponTareaEnTabla( numTarea );
       Close();
}

//---------------------------------------------------------------------------
void __fastcall TForm2::DirectoryListBox1Change(TObject *Sender)
{
        if ( !cambiandoDesdeTexto ) {
                edDir->Text = DirectoryListBox1->Directory;
        }
}

//---------------------------------------------------------------------------

void __fastcall TForm2::edDirChange(TObject *Sender)
{
        char unidad;
        AnsiString directorio;
        AnsiString archivo;

        try {
            ProcessPath( edDir->Text, unidad, directorio, archivo );

            if ( unidad != 0 ) {
                    cambiandoDesdeTexto = true;
                    DriveComboBox1->Drive = unidad;
                    DirectoryListBox1->Drive = unidad;

                    if ( !directorio.IsEmpty() ) {
                            DirectoryListBox1->Directory = directorio;
                    }
                    cambiandoDesdeTexto = false;
            }
        } catch( ... )
        {
        }
}
//---------------------------------------------------------------------------

