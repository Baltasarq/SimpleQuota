//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "uSimpleQuota.h"
#include "uAcercaDe.h"
#include "uEditorTarea.h"
#include <cstdio>
#include <ctime>


using namespace std;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

const int MAXLINENTRADA = 8192;

const string TForm1::Separador = "============================================";
const string TForm1::MensajeAviso = "Ha sobrepasado el 90% de su cuota en el servidor";
const string TForm1::MensajePasado = "Ha sobrepasado su cuota en el servidor, "
                                     "por favor, borre algunos archivos.";
const string TForm1::NombreApp = "SimpleQuota";
const string TForm1::VersionApp = " v1.3 Serial 20060329";
const string TForm1::ArchivoConf = "simplequota.ini";
const string TForm1::ExtLog = ".log";
const string TForm1::ArchivoLog = NombreApp + ExtLog;

const string Tarea::strCompletada[] = {
        "No completada", "Sin errores", "Con avisos", "Con errores", "ERROR"
};

AnsiString TForm1::dir;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        Constraints->MinWidth = Width;
        Constraints->MinHeight = Height;
        Caption = NombreApp.c_str();
        Memo1->Perform( EM_SETLIMITTEXT, 512000, 0 );     // 500ks

        // Iniciar el componente del log
        dir = GetCurrentDir();
        if ( StringMan::mays( ParamStr( 1 ).c_str() ) == "AUTO" ) {
                _esModoAuto = true;
        }

        if ( !esModoAuto() ) {
            try {
                    Memo1->Lines->LoadFromFile( ArchivoLog.c_str() );
                    Memo1->Perform( EM_SCROLLCARET, 0, 0 );
            }
            catch(const EFOpenError &e)
            {
                    ShowMessage(
                        ( "No pudo cargarse " + ArchivoLog ) .c_str()
                    );
            }
            catch(...)
            {
                    ShowMessage( "Sin memoria cargando el log" );
            }
        }

        // Comenzar
        logFile = new LogFile( ArchivoLog );
        tareasHechas = false;
        escribe( NombreApp + VersionApp );
        escribe( "" );
        escribe( "Leyendo archivo de configuración ..." );
        correcto = leeConf();
        escribe( "Fin de lectura de configuración." );
        escribe( Separador );
        escribe( "" );
        refrescarTablaTareas( true );
        PageControl1->ActivePageIndex = 0;

        if ( !esModoAuto() ) {
                escribeConMarcaTemporal(
                        NombreApp
                        + " - Inicio de sesión interactiva"
                );
        }
}

bool TForm1::cumpleTareas()
{
        unsigned int numTareasCorrectas = 0;

        tareasHechas = true;

        if ( lt.getNumTareas() == 0 ) {
                escribe( "No hay Tareas que hacer ..." );
        }

        escribeConMarcaTemporal( NombreApp + " - Inicio de tareas\n\n" );
        for(unsigned int n = 0;n < lt.getNumTareas(); ++n)
        {
                if ( ejecutaTarea( n ) ) {
                        ++numTareasCorrectas;
                }
        }

        escribe( "" );
        escribeConMarcaTemporal( NombreApp + " - Fin de tareas\n\n" );

        SetCurrentDir( dir );
        return ( numTareasCorrectas == lt.getNumTareas() );
}

//---------------------------------------------------------------------------
void TForm1::enviaMailAviso(const string &mensaje, int numTarea)
{
        TNMSMTP *smtp = NULL;
        char usuario[MAXLINENTRADA];
        char localhost[MAXLINENTRADA];
        unsigned long int  chtam;
        string dirOrg;
        time_t hora;

        smtp = new TNMSMTP(this);

        estado( "Enviando e.mail..." );

        if ( lt[numTarea]->getHost().empty() ) {
                escribe( "No se ha introducido una dirección de e.mail" );
                goto FIN;
        }

        // Crear una dirección de origen
        chtam = MAXLINENTRADA - 1;
        GetUserName(usuario, &chtam);
        chtam = MAXLINENTRADA - 1;
        GetComputerName(localhost, &chtam);
        dirOrg  = usuario;
        dirOrg += '@';
        dirOrg += localhost;

        // Completar los datos del e.mail a mandar
        NMSMTP1->EncodeType = uuCode;
        smtp->Host   = lt[numTarea]->getHost().c_str();
        smtp->UserID = lt[numTarea]->getUsr().c_str();
        hora = time(NULL);
        smtp->PostMessage->Date = ctime(&hora);
        smtp->PostMessage->ToAddress->Append(smtp->UserID + '@' + smtp->Host);
        smtp->PostMessage->FromAddress = smtp->PostMessage->ToAddress->Strings[0];
        smtp->PostMessage->LocalProgram = NombreApp.c_str();
        smtp->PostMessage->Subject = mensaje.c_str();
        smtp->PostMessage->Body->Append(mensaje.c_str());
        smtp->PostMessage->Body->Append("Cuenta: ");
        smtp->PostMessage->Body->Append(lt[numTarea]->getDir().c_str());
        smtp->PostMessage->Body->Append(Separador.c_str());
        smtp->PostMessage->Body->Append("");
        smtp->PostMessage->Body->Append("Mensaje generado desde:");
        smtp->PostMessage->Body->Append(dirOrg.c_str());
        smtp->PostMessage->Body->Append(Separador.c_str());
        smtp->PostMessage->Body->Append(NombreApp.c_str());
        smtp->PostMessage->Body->Append("Este es un envío automático. No conteste a este mensaje.");
        smtp->PostMessage->Body->Append("");

        escribe("Mandando e.mail de aviso a");
        escribe(smtp->PostMessage->ToAddress->Strings[0].c_str());
        try {
              smtp->Connect();
              smtp->SendMail();
        } catch(...)
        {
                escribe("ERROR mandando el e.mail de aviso");
                lt[numTarea]->completa = Tarea::ConErrores;
        }

        FIN:
        escribe("Terminado envío de e.mail");
        delete smtp;
}

//---------------------------------------------------------------------------
bool TForm1::trataDir(const string &dir, int tarea)
{
        WIN32_FIND_DATA info;
        HANDLE f;
        bool seguir;
        string busquedaDirectorio(dir);
        string nombreArchivo;

        busquedaDirectorio += "\\*.*";

        estado("Tratando directorio '" + dir + '\'' );

        // Busca el directorio
        f = FindFirstFile(busquedaDirectorio.c_str(), &info);
        bool toret = ( f != INVALID_HANDLE_VALUE );

        if ( toret )
        {
                    seguir = true;

                    while(seguir)
                    {
                            Application->ProcessMessages();

                            // ¿Qué nombre de archivo vamos a copiar?
                            nombreArchivo  = dir;
                            nombreArchivo += '\\';
                            nombreArchivo += info.cFileName;


                            // Si es un directorio, llamarse recursivamente
                            if ((info.dwFileAttributes)&FILE_ATTRIBUTE_DIRECTORY
                             && (*(info.cFileName)) != '.')
                            {
                                string nuevoDir = dir;

                                // Cambiar al directorio local
                                nuevoDir += '\\';
                                nuevoDir += info.cFileName;
                                trataDir(nuevoDir, tarea);
                            }

                            // Si es un archivo normal, contabilizarlo
                            if ((!((info.dwFileAttributes)&FILE_ATTRIBUTE_DIRECTORY))
                             && (!((info.dwFileAttributes)&FILE_ATTRIBUTE_TEMPORARY)))
                            {
                                    ++numArchivos;

                                    // Contar
                                    tam += (info.nFileSizeHigh * MAXDWORD)
                                                        + info.nFileSizeLow;
                            }

                            seguir = FindNextFile(f, &info);
                    }
                    FindClose(f);
        }
        else escribe(string("ERROR accediendo al directorio '" + dir + '\'' ));

        return toret;
}

// -----------------------------------------------------------------------------
bool TForm1::leeConf()
{
        Tarea *tr;
        char linea[MAXLINENTRADA];
        vector<string> lin;
        bool toret = true;

        FILE *f = fopen(ArchivoConf.c_str(), "r");

        if (f != NULL)
        {
                // Leer los Tareas
                while(!feof(f))
                {
                        // Actualizar
                        Application->ProcessMessages();

                        // Leer la sig. línea
                        *linea = 0;
                        *(linea + 1) = 0;
                        fgets(linea, MAXLINENTRADA - 1, f);

                        // Quitar el salto de línea
                        *(linea + (strlen(linea) - 1)) = 0;

                        // Es un comentario ?
                        if (linea[0]!=';'
                         && strlen(linea) > 1)
                        {
                            lin.erase(lin.begin(), lin.end());

                            // Subdividir en las partes
                            interpretaLinea(lin, linea);

                            // Meter la nueva tarea
                            if (!(lin[0].empty()))
                            {
                                    if (lin.size() != 4)
                                    {
                                        toret = false;
                                        escribe("ERROR de formato en el fichero de configuración");
                                    }
                                    else {
                                     tr = new Tarea(lin[0], lin[1],
                                                    lin[2], lin[3]
                                     );

                                     if ( tr != NULL ) {
                                        lt.mas( tr );
                                     }
                                     else {
                                        escribe( "Sin memoria creando tarea" );
                                     }
                                    }
                            }
                        }
                }
        }
        else { escribe("ERROR Leyendo el fichero."); toret = false; }

        return toret;
}

static void skipspaces(char **w)
{
        while((**w == ' '
            || **w == '\t'
            || **w == '\n')
           && **w != 0)
                ++(*w);
}


void TForm1::interpretaLinea(vector<string> &args, char *cmd)
{
        char *w = cmd, *p;
        char buffer[1024];
        char final_char;

        while(*w)
        {
                // skip spaces -if any, which would be strange-
                skipspaces(&w);
                p = buffer;

                // is there a doble quote ?
                if (*w=='\"') {
                        final_char = '\"';
                        ++w;
                }
                else
                        final_char = ' ';

                do {
                        *(p++) = *(w++);
                } while(*w != final_char
                     && *w != 0);

                // End the string
                *p = 0;

                // Prepare next argument
                if (*w)
                        ++w;

                // Store the argument in the arg list
                args.push_back(buffer);
        }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Salir1Click(TObject *Sender)
{
        Close();
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Acercade1Click(TObject *Sender)
{
        TAboutBox * acercaDe = new TAboutBox( this );
        acercaDe->ShowModal();
        delete acercaDe;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormActivate(TObject *Sender)
{
        // Disparar la ejecución automática y salir, si es necesario
        if ( esModoAuto()
          && !tareasHechas
          && correcto )
        {
                cumpleTareas();
                uiDesactiva();
                Close();
        }

        // En cualquier caso, activar la interfaz
        uiActiva();
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Copiar1Click(TObject *Sender)
{
        Memo1->CopyToClipboard();
}

//---------------------------------------------------------------------------
void TForm1::estado(const string &msg)
{
        StatusBar1->SimpleText = msg.c_str();
}

//---------------------------------------------------------------------------
void TForm1::uiActiva()
{
        Enabled = true;
        Archivo1->Enabled = true;
        Editar1->Enabled = true;
        Ayuda1->Enabled = true;
        estado( "Preparado ..." );
}

//---------------------------------------------------------------------------
void TForm1::uiDesactiva()
{
        Enabled = false;
        Archivo1->Enabled = false;
        Editar1->Enabled = false;
        Ayuda1->Enabled = false;
}

//---------------------------------------------------------------------------
inline
void TForm1::escribe(const string &x)
{
        Memo1->Lines->Append(x.c_str());
        Memo1->Perform( EM_SCROLLCARET, 0, 0 );

        if ( logFile != NULL ) {
                logFile->escribe(x);

        }
}

//---------------------------------------------------------------------------
inline
void TForm1::escribeConMarcaTemporal(const string &x)
{
        if ( logFile != NULL ) {
                logFile->escribeConMarcaTemporal(x);
        }
}

void __fastcall TForm1::Vertareas1Click(TObject *Sender)
{
        unsigned int i = 0;
        escribe( "" );
        escribe( "Tareas registradas:" );

        for(; i < lt.getNumTareas(); ++i) {
                escribe( lt[i]->toString() );
        }
        escribe( "" );
        escribe( StringMan::toString( (int) i ) + " tarea(s)." );

        escribe( "--" );
        escribe( "" );
}

//---------------------------------------------------------------------------
void TForm1::refrescarTablaTareas(bool ponPrimera)
{
        TGridRect select = tablaTareas->Selection;
        preparaTablaTareas();

        for(unsigned int i = 0; i < lt.getNumTareas(); ++i) {
                ponTareaEnTabla( i );
        }

        if ( ponPrimera ) {
            select.Top = 1;
            select.Left = 0;
            select.Bottom = 1;
            select.Right = tablaTareas->ColCount - 1;
        }

        tablaTareas->Selection = select;
}

//---------------------------------------------------------------------------
void TForm1::preparaTablaTareas()
{
        unsigned int anchoEnPixels = abs( tablaTareas->Font->Height ) * 0.85;

        // Preparar dimensiones
        tablaTareas->RowCount  = 1;
        tablaTareas->ColCount  = 6;
        tablaTareas->FixedCols = 1;
        tablaTareas->ColWidths[0] = anchoEnPixels * 3;

        // Poner cabecera
        tablaTareas->Cells[1][0] = "";
        tablaTareas->ColWidths[1] = 32;
        tablaTareas->Cells[2][0] = "Directorio";
        tablaTareas->ColWidths[2] = anchoEnPixels * 20;
        tablaTareas->Cells[3][0] = "Quota";
        tablaTareas->Cells[4][0] = "Usuario";
        tablaTareas->Cells[5][0] = "¿Completada?";
        tablaTareas->ColWidths[5] = anchoEnPixels * Tarea::strCompletada[0].length();
        tablaTareas->ColWidths[4] = anchoEnPixels * 15;
}

//---------------------------------------------------------------------------
void TForm1::ponTareaEnTabla(unsigned int i)
{
        TGridRect select;
        unsigned int fila;
        Tarea &t = *( lt[i] );

        // Añadir una fila
        if ( tablaTareas->RowCount <= ( i + 1 ) ) {
            tablaTareas->RowCount = tablaTareas->RowCount + 1;
            fila = tablaTareas->RowCount - 1;
            tablaTareas->FixedRows = 1;
        }
        else fila = i + 1;

        //  Meter los datos
        tablaTareas->Cells[0][fila] = StringMan::toString( fila ).c_str();
        tablaTareas->Cells[2][fila] = t.getDir().c_str();
        tablaTareas->Cells[3][fila] =
                ( StringMan::toString( t.getMTam() ) + "Mb" ).c_str()
        ;
        tablaTareas->Cells[4][fila] = ( t.getUsr() + '@' + t.getHost() ).c_str();
        tablaTareas->Cells[5][fila] = t.cnvtCompletaStr( t.completa ).c_str();

        // Asegurar que se redibuje
        tablaTareas->Invalidate();
        select.Top = fila;
        select.Left = 0;
        select.Bottom = fila;
        select.Right = tablaTareas->ColCount - 1;
        tablaTareas->Selection = select;
        tablaTareas->Repaint();
}

void __fastcall TForm1::Copiartodoellog1Click(TObject *Sender)
{
        Memo1->SelStart = 0;
        Memo1->SelLength = Memo1->Text.Length();
        Memo1->CopyToClipboard();
}

//---------------------------------------------------------------------------
void __fastcall TForm1::tablaTareasDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
        int anchoPen;
        TColor colorAntes;
        TColor colorPenAntes;
        TBrushStyle estiloAntes;

        if ( ACol == 1
          && ARow > 0 )
        {
            // Comprobar que estamos bien
            if ( lt.getNumTareas() < ( ARow - 1 ) ) {
                    ShowMessage( "Error interno: dibujando StringGrid" );
                    return;
            }

            // Calcular el nuevo rectángulo
            TRect miRect;
            miRect.Left = Rect.Left + 10;
            miRect.Top = Rect.Top + 5;
            miRect.Right = Rect.Right - 10;
            miRect.Bottom = Rect.Bottom - 5;

            // Guardar los valores actuales
            colorAntes = tablaTareas->Canvas->Brush->Color;
            estiloAntes = tablaTareas->Canvas->Brush->Style;
            colorPenAntes = tablaTareas->Canvas->Pen->Color;
            anchoPen = tablaTareas->Canvas->Pen->Width;
            tablaTareas->Canvas->FillRect( Rect );

            // Dibujar el símbolo adecuado y borrar rectángulo
            if ( lt[ARow - 1]->completa == Tarea::SinErrores ) {
                tablaTareas->Canvas->Pen->Color = clGreen;
                tablaTareas->Canvas->Pen->Width = 3;
                tablaTareas->Canvas->MoveTo( miRect.Right, miRect.Top );
                tablaTareas->Canvas->LineTo( miRect.Left, miRect.Bottom );
                tablaTareas->Canvas->LineTo( miRect.Left, miRect.Bottom - 5);
            }
            else
            if ( lt[ARow - 1]->completa == Tarea::ConErrores ) {
                tablaTareas->Canvas->Pen->Color = clRed;
                tablaTareas->Canvas->Pen->Width = 3;                 
                tablaTareas->Canvas->MoveTo( miRect.Left, miRect.Top );
                tablaTareas->Canvas->LineTo( miRect.Right, miRect.Bottom );
                tablaTareas->Canvas->MoveTo( miRect.Right, miRect.Top );
                tablaTareas->Canvas->LineTo( miRect.Left, miRect.Bottom );
            }
            else
            if ( lt[ARow - 1]->completa == Tarea::ConAvisos ) {
                tablaTareas->Canvas->Pen->Color = clYellow;
                tablaTareas->Canvas->Pen->Width = 3;
                tablaTareas->Canvas->MoveTo( miRect.Right, miRect.Top );
                tablaTareas->Canvas->LineTo( miRect.Left, miRect.Bottom );
                tablaTareas->Canvas->LineTo( miRect.Left, miRect.Bottom - 5);

            }
            else
            if ( lt[ARow - 1]->completa == Tarea::NoCompleta ) {
                tablaTareas->Canvas->Brush->Color = clGray;
                tablaTareas->Canvas->FillRect( miRect );
            }

            // Restaurar valores anteriores
            tablaTareas->Canvas->Brush->Color = colorAntes;
            tablaTareas->Canvas->Brush->Style = estiloAntes;
            tablaTareas->Canvas->Pen->Color = colorPenAntes;
            tablaTareas->Canvas->Pen->Width = anchoPen;          
        }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        if ( esModoAuto() ) {
                escribe( "** Fin de sesión batch" );
        }
        else {
                escribe( "** Fin de sesión interactiva - "
                        + StringMan::toString( time( NULL ) )
                );
        }

        escribe( Separador );
        escribe( "" );
        escribe( "" );

        Action = caFree;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton5Click(TObject *Sender)
{
        Tarea * nueva = new Tarea(
                "c:\\back",
                "512",
                "anonymous",
                "quota.org"
        );

        if ( nueva != NULL ) {
                lt.mas( nueva );
                ponTareaEnTabla( lt.getNumTareas() - 1 );
                tablaTareas->Row = lt.getNumTareas();
                SpeedButton2Click( this );
        } else ShowMessage( "Sin memoria, cierre algunas aplicaciones" );
}

void __fastcall TForm1::SpeedButton4Click(TObject *Sender)
{
        if ( lt.getNumTareas() > 0 ) {
            preparaTablaTareas();
            uiDesactiva();
            cumpleTareas();
            uiActiva();
        } else ShowMessage( "No hay tareas" );
}

//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton6Click(TObject *Sender)
{
        unsigned int indiceTarea = tablaTareas->Row - 1;

        if ( lt.getNumTareas() > 0 ) {
            if ( indiceTarea > tablaTareas->RowCount ) {
                    indiceTarea = 0;
            }

            uiDesactiva();
            ejecutaTarea( indiceTarea );
            uiActiva();
        } else ShowMessage( "No hay tareas" );
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Borrartarea1Click(TObject *Sender)
{
        unsigned int indiceTarea = tablaTareas->Row - 1;

        if ( lt.getNumTareas() > 0 ) {
            if ( indiceTarea > tablaTareas->RowCount ) {
                    indiceTarea = 0;
            }

            uiDesactiva();
            lt.eliminarTarea( indiceTarea );
            refrescarTablaTareas();
            uiActiva();
        } else ShowMessage( "No hay tareas" );
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Restaurarficherodeconfiguracin1Click(
      TObject *Sender)
{
        lt.eliminarTodas();
        leeConf();
        refrescarTablaTareas( true );
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Guardarficherodeconfiguracin1Click(TObject *Sender)
{
        Tarea *tarea;
        unsigned int numTareas = lt.getNumTareas();

        // Guardar la info en el fichero
        FILE * f = fopen( ArchivoConf.c_str(), "wt" );

        if ( f != NULL ) {
                // Guardar la cab de info
                fprintf( f, "; %s\n\n", NombreApp.c_str() );
                fprintf( f, "; Este archivo sirve para indicarle a %s "
                            "qué directorios comprobar.\n"
                            "; El Separador es el espacio, en caso de incluir"
                            " nombres de archivos\n"
                            "; -o el nombre de la máquina, o lo que sea- "
                            "con espacios,\n"
                            "; deben indicarse entre comillas.\n\n"
                            ,
                            NombreApp.c_str()
                );
                fprintf( f,
                        "; Los tamaños máximos deben indicarse en Megabytes "
                );
                fprintf( f, "; La estructura es:\n\n"
                            "; <directorio> <quota>            "
                            "<usuario> <host>\n"
                            "; c:\\back        512    jbgarcia 193.356.56.1"
                            "\n\n"
                );

                for(unsigned int i = 0; i < numTareas; ++i) {
                        tarea = lt[i];
                        fprintf( f, "\"%s\" \"%s\" \"%s\" "
                                    "\"%s\"\n",
                                tarea->getDir().c_str(),
                                StringMan::toString( tarea->getMTam() ).c_str(),
                                tarea->getUsr().c_str(),
                                tarea->getHost().c_str()
                        );
                }

                fclose( f );
        }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Indice1Click(TObject *Sender)
{
        Application->HelpCommand( HELP_CONTENTS, 0 );
}

//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
        int numTarea = tablaTareas->Selection.Top - 1;

        /// Editar una tarea existente
        Form2 = new TForm2( numTarea, this );
        Form2->ShowModal();

        SetCurrentDir( dir );
}

//---------------------------------------------------------------------------
bool TForm1::ejecutaTarea(unsigned int n)
{
        NumBytes max;
        char estadistica[128];
        bool toret = false;
        numArchivos = tam = 0;

        // Lanzar la cuenta recursiva
        escribe("");
        escribe("Calculando el espacio que ocupa el directorio ...");
        escribe(lt[n]->getDir());
        escribe("");

        lt[n]->completa = Tarea::ConErrores;

        if ( trataDir(lt[n]->getDir(), n) ) {
                toret = true;

                // Presentar estadísticas
                max = lt[n]->getMTam() * 1024 * 1024;
                sprintf(estadistica, "%u ficheros contados", numArchivos);
                escribe("");
                escribe(Separador);
                escribe(estadistica);
                sprintf(estadistica, "%u bytes de tamaño de la cuenta",
                                        tam)
                ;

                escribe(estadistica);
                sprintf(estadistica, "%u bytes permitidos en esta cuenta",
                                        max)
                ;

                escribe(estadistica);
                escribe(Separador);
                escribe("");

                // Se pasa del límite ?
                if (tam > max)
                {
                        escribe("Cuota superada.");
                        lt[n]->completa = Tarea::ConAvisos;
                        enviaMailAviso(MensajePasado, n);
                }
                else
                if (((double) tam) > (((double) max) * 0.9))
                {
                        escribe("80% de cuota superada.");
                        lt[n]->completa = Tarea::ConAvisos;                        
                        enviaMailAviso(MensajeAviso, n);
                }
                else {
                        escribe( "Cuota no superada." );
                        lt[n]->completa = Tarea::SinErrores;
                }
        }

        SetCurrentDir( dir );
        ponTareaEnTabla( n );
        return toret;
}

