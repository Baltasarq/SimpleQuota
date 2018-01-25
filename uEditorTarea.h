//---------------------------------------------------------------------------

#ifndef uEditorTareaH
#define uEditorTareaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <FileCtrl.hpp>
#include <Mask.hpp>

class Tarea;

//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TPanel *Panel1;
        TEdit *edDir;
        TButton *botGuardar;
        TButton *botCancel;
        TStaticText *StaticText1;
        TDirectoryListBox *DirectoryListBox1;
        TDriveComboBox *DriveComboBox1;
        TGroupBox *GroupBox3;
        TStaticText *StaticText4;
        TEdit *edUsr;
        TStaticText *StaticText5;
        TEdit *edHost;
        TStaticText *StaticText2;
        TStaticText *StaticText3;
        TMaskEdit *edTam;
        void __fastcall botCancelClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall botGuardarClick(TObject *Sender);
        void __fastcall DirectoryListBox1Change(TObject *Sender);
        void __fastcall edDirChange(TObject *Sender);
private:	// User declarations
        unsigned int numTarea;
        bool cambiandoDesdeTexto;
public:		// User declarations
        __fastcall TForm2(unsigned int, TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif

