object Form2: TForm2
  Left = 267
  Top = 223
  BorderStyle = bsDialog
  Caption = 'Form2'
  ClientHeight = 309
  ClientWidth = 349
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 349
    Height = 185
    Align = alTop
    Caption = 'Tarea'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object edDir: TEdit
      Left = 72
      Top = 16
      Width = 265
      Height = 21
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      Text = 'edDir'
      OnChange = edDirChange
    end
    object StaticText1: TStaticText
      Left = 8
      Top = 16
      Width = 52
      Height = 17
      Caption = 'Directorio:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object DirectoryListBox1: TDirectoryListBox
      Left = 120
      Top = 48
      Width = 217
      Height = 89
      ItemHeight = 16
      TabOrder = 2
      OnChange = DirectoryListBox1Change
    end
    object DriveComboBox1: TDriveComboBox
      Left = 8
      Top = 48
      Width = 105
      Height = 19
      DirList = DirectoryListBox1
      TabOrder = 1
    end
    object StaticText2: TStaticText
      Left = 168
      Top = 154
      Width = 36
      Height = 17
      Caption = 'Quota:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
    end
    object StaticText3: TStaticText
      Left = 296
      Top = 154
      Width = 38
      Height = 17
      Caption = 'Mbytes'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
    end
    object edTam: TMaskEdit
      Left = 248
      Top = 152
      Width = 41
      Height = 21
      EditMask = '!99999;0;0'
      MaxLength = 5
      TabOrder = 6
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 268
    Width = 349
    Height = 41
    Align = alBottom
    TabOrder = 2
    object botGuardar: TButton
      Left = 24
      Top = 8
      Width = 75
      Height = 25
      Caption = '&Guardar'
      Default = True
      TabOrder = 0
      OnClick = botGuardarClick
    end
    object botCancel: TButton
      Left = 248
      Top = 8
      Width = 75
      Height = 25
      Cancel = True
      Caption = '&Descartar'
      TabOrder = 1
      OnClick = botCancelClick
    end
  end
  object GroupBox3: TGroupBox
    Left = 0
    Top = 185
    Width = 349
    Height = 83
    Align = alClient
    Caption = 'Identificación de máquina remota (para envío de e.mail)'
    TabOrder = 1
    object StaticText4: TStaticText
      Left = 8
      Top = 17
      Width = 43
      Height = 17
      Caption = 'Usuario:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object edUsr: TEdit
      Left = 80
      Top = 13
      Width = 257
      Height = 21
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      Text = 'edUsr'
    end
    object StaticText5: TStaticText
      Left = 8
      Top = 49
      Width = 26
      Height = 17
      Caption = 'Host'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object edHost: TEdit
      Left = 80
      Top = 45
      Width = 257
      Height = 21
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      Text = 'edHost'
    end
  end
end
