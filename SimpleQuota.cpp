//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("SimpleQuota.res");
USEFORM("uSimpleQuota.cpp", Form1);
USEUNIT("..\MyLib\logfile.cpp");
USEUNIT("..\MyLib\stringman.cpp");
USEFORM("uAcercaDe.cpp", AboutBox);
USEFORM("uEditorTarea.cpp", Form2);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "SimpleQuota";
                 Application->HelpFile = "simplequota.hlp";
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
