//---------------------------------------------------------------------------

#ifndef uSimpleQUOTAH
#define uSimpleQUOTAH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <NMFtp.hpp>
#include <Psock.hpp>
#include <Menus.hpp>
#include <NMsmtp.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>

#include <string>
#include <vector>
#include <iterator>

#include "logfile.h"
#include "stringman.h"

//---------------------------------------------------------------------------

class Tarea {
public:
        enum Completada { NoCompleta, SinErrores, ConAvisos, ConErrores };
        static const string strCompletada[];
private:
        std::string dir;
        unsigned int maxtam;
        std::string usuario;
        std::string host;
public:
        Completada completa;

        Tarea(const std::string &d, const std::string &t, const std::string &u,
                const std::string &h): dir(d), usuario(u), host(h)
        {
                maxtam = atoi(t.c_str());
                completa = NoCompleta;
        }

        void reemplazar(const std::string &d, const std::string &t, const std::string &u,
                        const std::string &h)
        {
                maxtam = atoi( t.c_str() );
                dir = d;
                usuario = u;
                host = h;
        }
        const std::string &getDir()  const { return dir; }
        const std::string &getUsr()  const { return usuario; }
        const std::string &getHost() const { return host; }
        unsigned int getMTam()  const { return maxtam; }
        std::string toString() const
        {
                return std::string ( '\'' + dir + '\'' + ": " + usuario
                                + '@' + host + ", max: "
                                + StringMan::toString( (int)maxtam )
                );
        }

        static std::string cnvtCompletaStr(Completada c)
        {
                unsigned int pos = (unsigned int) c;

                if ( pos > ConErrores ) {
                        pos = ConErrores + 1;
                }

                return strCompletada[ pos ];
        }
};

class ListaTareas {
private:
        std::vector<Tarea *> vTareas;
public:
        ListaTareas() { }
        ~ListaTareas()
           { for(unsigned int n=0;n<vTareas.size();++n) { delete vTareas[n]; }}

        void eliminarTodas()
            { for(unsigned int i = 0; i < getNumTareas(); ++i) {
                delete vTareas[i];
              }
              vTareas.clear();
            }

        Tarea *operator[](unsigned int n)
                { if (n<getNumTareas())
                       return vTareas[n];
                  else return NULL;
                }

        void mas(Tarea *t)
                { vTareas.push_back(t); }

        unsigned int getNumTareas() const
                { return vTareas.size(); }

        void eliminarTarea(unsigned int i)
            {
              std::vector<Tarea *>::iterator it = vTareas.begin();
              std::advance( it, i );
              delete vTareas[i];
              vTareas.erase( it );
            }

        std::string toString() const
            {
                std::string toret;

                for(unsigned int i = 0; i < getNumTareas(); ++i) {
                        toret += vTareas[i]->toString();
                        toret += '\n';
                }

                return toret;
            }
};

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *Archivo1;
        TMenuItem *Salir1;
        TMenuItem *Ayuda1;
        TMenuItem *Acercade1;
        TNMSMTP *NMSMTP1;
        TMenuItem *Editar1;
        TMenuItem *Copiar1;
        TStatusBar *StatusBar1;
        TMenuItem *Vertareas1;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TRichEdit *Memo1;
        TStringGrid *tablaTareas;
        TToolBar *ToolBar1;
        TSpeedButton *SpeedButton3;
        TSplitter *Splitter1;
        TSpeedButton *SpeedButton5;
        TSpeedButton *SpeedButton2;
        TSpeedButton *SpeedButton6;
        TSpeedButton *SpeedButton4;
        TSplitter *Splitter2;
        TSpeedButton *SpeedButton1;
        TMenuItem *Copiartodoellog1;
        TMenuItem *Borrartarea1;
        TMenuItem *Restaurarficherodeconfiguracin1;
        TMenuItem *Guardarficherodeconfiguracin1;
        TMenuItem *Indice1;
        TMenuItem *Editartarea1;
        TMenuItem *Herramientas1;
        TMenuItem *Ejecutartarea1;
        TMenuItem *Ejecutartodaslastareas1;
        TPopupMenu *PopupMenu1;
        TMenuItem *Borrartarea2;
        TMenuItem *Ejecutartarea2;
        TMenuItem *Ejecutartodo1;
        TMenuItem *Creartarea1;
        TMenuItem *Editartarea2;
        void __fastcall Salir1Click(TObject *Sender);
        void __fastcall Acercade1Click(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall Copiar1Click(TObject *Sender);
        void __fastcall Copiartodoellog1Click(TObject *Sender);
        void __fastcall Vertareas1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall tablaTareasDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall SpeedButton5Click(TObject *Sender);
        void __fastcall SpeedButton4Click(TObject *Sender);
        void __fastcall SpeedButton6Click(TObject *Sender);
        void __fastcall Borrartarea1Click(TObject *Sender);
        void __fastcall Restaurarficherodeconfiguracin1Click(
          TObject *Sender);
        void __fastcall Guardarficherodeconfiguracin1Click(
          TObject *Sender);
        void __fastcall Indice1Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
public:
        typedef unsigned long int NumBytes;
private:	// User declarations
        LogFile * logFile;
        bool tareasHechas;
        bool correcto;
        bool _esModoAuto;
        NumBytes numArchivos;
        NumBytes tam;

        void uiActiva();
        void uiDesactiva();
        void estado(const std::string &);

        void escribe(const std::string &);
        void escribeConMarcaTemporal(const std::string &);
        bool leeConf(void);
        bool trataDir(const std::string &d, int tarea);
        void enviaMailAviso(const std::string &, int);
        void interpretaLinea(std::vector<std::string> &args, char *cmd);
        void preparaTablaTareas(void);

public:		// User declarations
        static AnsiString dir;
        bool esModoAuto()
                { return _esModoAuto; }

        static const std::string Separador;
        static const std::string NombreApp;
        static const std::string VersionApp;
        static const std::string ArchivoConf;
        static const std::string ArchivoLog;
        static const std::string ExtLog;
        static const std::string MensajeAviso;
        static const std::string MensajePasado;

        __fastcall TForm1(TComponent* Owner);
        bool cumpleTareas(void);
        bool ejecutaTarea(unsigned int i);

        void refrescarTablaTareas(bool = false);
        void ponTareaEnTabla(unsigned int i);
        ListaTareas lt;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
