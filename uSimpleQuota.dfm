object Form1: TForm1
  Left = 280
  Top = 246
  Width = 582
  Height = 387
  Caption = 'App'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnActivate = FormActivate
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar1: TStatusBar
    Left = 0
    Top = 314
    Width = 574
    Height = 19
    Panels = <>
    SimplePanel = False
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 49
    Width = 574
    Height = 265
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = '&Tareas'
      object tablaTareas: TStringGrid
        Left = 0
        Top = 0
        Width = 566
        Height = 237
        Align = alClient
        ColCount = 1
        FixedCols = 0
        RowCount = 1
        FixedRows = 0
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
        PopupMenu = PopupMenu1
        TabOrder = 0
        OnDrawCell = tablaTareasDrawCell
      end
    end
    object TabSheet2: TTabSheet
      Caption = '&Log'
      ImageIndex = 1
      object Memo1: TRichEdit
        Left = 0
        Top = 0
        Width = 566
        Height = 237
        Align = alClient
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        PlainText = True
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
      end
    end
  end
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 574
    Height = 49
    ButtonHeight = 39
    Caption = 'ToolBar1'
    TabOrder = 2
    object SpeedButton3: TSpeedButton
      Left = 0
      Top = 2
      Width = 121
      Height = 39
      Hint = 
        'Guarda el fichero de configuración, salvaguardando las nuevas ta' +
        'reas'
      Caption = 'Guardar configuración'
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        333333FFFFFFFFFFFFF33000077777770033377777777777773F000007888888
        00037F3337F3FF37F37F00000780088800037F3337F77F37F37F000007800888
        00037F3337F77FF7F37F00000788888800037F3337777777337F000000000000
        00037F3FFFFFFFFFFF7F00000000000000037F77777777777F7F000FFFFFFFFF
        00037F7F333333337F7F000FFFFFFFFF00037F7F333333337F7F000FFFFFFFFF
        00037F7F333333337F7F000FFFFFFFFF00037F7F333333337F7F000FFFFFFFFF
        00037F7F333333337F7F000FFFFFFFFF07037F7F33333333777F000FFFFFFFFF
        0003737FFFFFFFFF7F7330099999999900333777777777777733}
      Layout = blGlyphTop
      NumGlyphs = 2
      ParentShowHint = False
      ShowHint = True
      OnClick = Guardarficherodeconfiguracin1Click
    end
    object Splitter1: TSplitter
      Left = 121
      Top = 2
      Width = 3
      Height = 39
      Cursor = crHSplit
    end
    object SpeedButton5: TSpeedButton
      Left = 124
      Top = 2
      Width = 65
      Height = 39
      Hint = 'Crea una nueva tarea de copia que podrá configurar'
      Caption = 'Crear tarea'
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000130B0000130B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF0033333333B333
        333B33FF33337F3333F73BB3777BB7777BB3377FFFF77FFFF77333B000000000
        0B3333777777777777333330FFFFFFFF07333337F33333337F333330FFFFFFFF
        07333337F33333337F333330FFFFFFFF07333337F33333337F333330FFFFFFFF
        07333FF7F33333337FFFBBB0FFFFFFFF0BB37777F3333333777F3BB0FFFFFFFF
        0BBB3777F3333FFF77773330FFFF000003333337F333777773333330FFFF0FF0
        33333337F3337F37F3333330FFFF0F0B33333337F3337F77FF333330FFFF003B
        B3333337FFFF77377FF333B000000333BB33337777777F3377FF3BB3333BB333
        3BB33773333773333773B333333B3333333B7333333733333337}
      Layout = blGlyphTop
      NumGlyphs = 2
      ParentShowHint = False
      ShowHint = True
      OnClick = SpeedButton5Click
    end
    object SpeedButton2: TSpeedButton
      Left = 189
      Top = 2
      Width = 65
      Height = 39
      Hint = 'Modifica la tarea que está seleccionada en la tabla'
      Caption = 'Editar tarea'
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333000000
        000033333377777777773333330FFFFFFFF03FF3FF7FF33F3FF700300000FF0F
        00F077F777773F737737E00BFBFB0FFFFFF07773333F7F3333F7E0BFBF000FFF
        F0F077F3337773F3F737E0FBFBFBF0F00FF077F3333FF7F77F37E0BFBF00000B
        0FF077F3337777737337E0FBFBFBFBF0FFF077F33FFFFFF73337E0BF0000000F
        FFF077FF777777733FF7000BFB00B0FF00F07773FF77373377373330000B0FFF
        FFF03337777373333FF7333330B0FFFF00003333373733FF777733330B0FF00F
        0FF03333737F37737F373330B00FFFFF0F033337F77F33337F733309030FFFFF
        00333377737FFFFF773333303300000003333337337777777333}
      Layout = blGlyphTop
      NumGlyphs = 2
      ParentShowHint = False
      ShowHint = True
      OnClick = SpeedButton2Click
    end
    object SpeedButton6: TSpeedButton
      Left = 254
      Top = 2
      Width = 79
      Height = 39
      Hint = 'Ejecuta la tarea seleccionada en la tabla'
      Caption = 'Ejecutar tarea'
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00370777033333
        3330337F3F7F33333F3787070003333707303F737773333373F7007703333330
        700077337F3333373777887007333337007733F773F333337733700070333333
        077037773733333F7F37703707333300080737F373333377737F003333333307
        78087733FFF3337FFF7F33300033330008073F3777F33F777F73073070370733
        078073F7F7FF73F37FF7700070007037007837773777F73377FF007777700730
        70007733FFF77F37377707700077033707307F37773F7FFF7337080777070003
        3330737F3F7F777F333778080707770333333F7F737F3F7F3333080787070003
        33337F73FF737773333307800077033333337337773373333333}
      Layout = blGlyphTop
      NumGlyphs = 2
      ParentShowHint = False
      ShowHint = True
      OnClick = SpeedButton6Click
    end
    object SpeedButton4: TSpeedButton
      Left = 333
      Top = 2
      Width = 79
      Height = 39
      Hint = 'Ejecuta todas las tareas de la tabla'
      Caption = 'Ejecutar todo'
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000130B0000130B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        33333333333333333333EEEEEEEEEEEEEEE333FFFFFFFFFFFFF3E00000000000
        00E337777777777777F3E0F77777777770E337F33333333337F3E0F333333333
        70E337F3333F333337F3E0F33303333370E337F3337FF33337F3E0F333003333
        70E337F33377FF3337F3E0F33300033370E337F333777FF337F3E0F333000033
        70E337F33377773337F3E0F33300033370E337F33377733337F3E0F333003333
        70E337F33377333337F3E0F33303333370E337F33373333337F3E0F333333333
        70E337F33333333337F3E0FFFFFFFFFFF0E337FFFFFFFFFFF7F3E00000000000
        00E33777777777777733EEEEEEEEEEEEEEE33333333333333333}
      Layout = blGlyphTop
      NumGlyphs = 2
      ParentShowHint = False
      ShowHint = True
      OnClick = SpeedButton4Click
    end
    object Splitter2: TSplitter
      Left = 412
      Top = 2
      Width = 3
      Height = 39
      Cursor = crHSplit
    end
    object SpeedButton1: TSpeedButton
      Left = 415
      Top = 2
      Width = 65
      Height = 39
      Hint = 'Muestra la ayuda'
      Caption = 'Ayuda'
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF0033333CCCCC33
        33333FFFF77777FFFFFFCCCCCC808CCCCCC3777777F7F777777F008888070888
        8003777777777777777F0F0770F7F0770F0373F33337F333337370FFFFF7FFFF
        F07337F33337F33337F370FFFB99FBFFF07337F33377F33337F330FFBF99BFBF
        F033373F337733333733370BFBF7FBFB0733337F333FF3337F33370FBF98BFBF
        0733337F3377FF337F333B0BFB990BFB03333373FF777FFF73333FB000B99000
        B33333377737777733333BFBFBFB99FBF33333333FF377F333333FBF99BF99BF
        B333333377F377F3333333FB99FB99FB3333333377FF77333333333FB9999FB3
        333333333777733333333333FBFBFB3333333333333333333333}
      Layout = blGlyphTop
      NumGlyphs = 2
      ParentShowHint = False
      ShowHint = True
      OnClick = Indice1Click
    end
  end
  object MainMenu1: TMainMenu
    Left = 456
    Top = 40
    object Archivo1: TMenuItem
      Caption = '&Archivo'
      object Restaurarficherodeconfiguracin1: TMenuItem
        Caption = '&Restaurar fichero de configuración'
        OnClick = Restaurarficherodeconfiguracin1Click
      end
      object Guardarficherodeconfiguracin1: TMenuItem
        Caption = '&Guardar fichero de configuración'
        OnClick = Guardarficherodeconfiguracin1Click
      end
      object Salir1: TMenuItem
        Caption = '&Salir'
        ShortCut = 32883
        OnClick = Salir1Click
      end
    end
    object Editar1: TMenuItem
      Caption = '&Editar'
      object Copiar1: TMenuItem
        Caption = '&Copiar'
        ShortCut = 16451
        OnClick = Copiar1Click
      end
      object Copiartodoellog1: TMenuItem
        Caption = 'Copiar &todo el log'
      end
      object Vertareas1: TMenuItem
        Caption = '&Ver tareas en log'
        OnClick = Vertareas1Click
      end
      object Editartarea1: TMenuItem
        Caption = '&Editar tarea'
        OnClick = SpeedButton2Click
      end
      object Borrartarea1: TMenuItem
        Caption = '&Borrar tarea'
        OnClick = Borrartarea1Click
      end
    end
    object Herramientas1: TMenuItem
      Caption = '&Herramientas'
      object Ejecutartarea1: TMenuItem
        Caption = '&Ejecutar tarea'
        OnClick = SpeedButton6Click
      end
      object Ejecutartodaslastareas1: TMenuItem
        Caption = 'Ejecutar &todas las tareas'
        OnClick = SpeedButton4Click
      end
    end
    object Ayuda1: TMenuItem
      Caption = '&Ayuda'
      object Indice1: TMenuItem
        Caption = '&Indice'
        ShortCut = 112
        OnClick = Indice1Click
      end
      object Acercade1: TMenuItem
        Caption = '&Acerca de ...'
        OnClick = Acercade1Click
      end
    end
  end
  object NMSMTP1: TNMSMTP
    Port = 25
    ReportLevel = 0
    EncodeType = uuMime
    ClearParams = True
    SubType = mtPlain
    Charset = 'us-ascii'
    Left = 424
    Top = 40
  end
  object PopupMenu1: TPopupMenu
    Left = 496
    Top = 40
    object Creartarea1: TMenuItem
      Caption = '&Crear tarea'
      OnClick = SpeedButton5Click
    end
    object Editartarea2: TMenuItem
      Caption = 'E&ditar tarea'
      OnClick = SpeedButton2Click
    end
    object Borrartarea2: TMenuItem
      Caption = '&Borrar tarea'
      ShortCut = 46
      OnClick = Borrartarea1Click
    end
    object Ejecutartarea2: TMenuItem
      Caption = '&Ejecutar tarea'
      OnClick = SpeedButton6Click
    end
    object Ejecutartodo1: TMenuItem
      Caption = 'Ejecutar &todo'
      OnClick = SpeedButton4Click
    end
  end
end
