object Form1: TForm1
  Left = 206
  Top = 139
  Width = 781
  Height = 553
  Caption = #38057#40060#23707' '#20013#22269#30340
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 80
    Top = 16
    Width = 78
    Height = 24
    Caption = 'Compare'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 336
    Top = 16
    Width = 32
    Height = 24
    Caption = 'and'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object lbl1: TLabel
    Left = 32
    Top = 88
    Width = 65
    Height = 13
    Caption = 'Problems only'
  end
  object lbl2: TLabel
    Left = 208
    Top = 88
    Width = 48
    Height = 13
    Caption = 'accepted:'
  end
  object lbl3: TLabel
    Left = 112
    Top = 84
    Width = 24
    Height = 20
    Caption = 'lbl3'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = 16744448
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object lbl4: TLabel
    Left = 32
    Top = 272
    Width = 65
    Height = 13
    Caption = 'Problems only'
  end
  object lbl5: TLabel
    Left = 216
    Top = 272
    Width = 48
    Height = 13
    Caption = 'accepted:'
  end
  object lbl6: TLabel
    Left = 112
    Top = 268
    Width = 24
    Height = 20
    Caption = 'lbl3'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = 16744448
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object lbl7: TLabel
    Left = 32
    Top = 480
    Width = 67
    Height = 13
    Caption = 'Problems both'
  end
  object lbl8: TLabel
    Left = 376
    Top = 480
    Width = 48
    Height = 13
    Caption = 'accepted:'
  end
  object lbl9: TLabel
    Left = 112
    Top = 476
    Width = 24
    Height = 20
    Caption = 'lbl3'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = 16744448
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object lbl10: TLabel
    Left = 256
    Top = 476
    Width = 24
    Height = 20
    Caption = 'lbl3'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = 16744448
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object lbl11: TLabel
    Left = 232
    Top = 480
    Width = 18
    Height = 13
    Caption = 'and'
  end
  object lbl12: TLabel
    Left = 272
    Top = 88
    Width = 22
    Height = 13
    Caption = 'lbl12'
  end
  object lbl13: TLabel
    Left = 280
    Top = 272
    Width = 22
    Height = 13
    Caption = 'lbl12'
  end
  object lbl14: TLabel
    Left = 440
    Top = 480
    Width = 22
    Height = 13
    Caption = 'lbl12'
  end
  object Edit1: TEdit
    Left = 176
    Top = 16
    Width = 145
    Height = 32
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    Text = 'hqztrue'
  end
  object Edit2: TEdit
    Left = 384
    Top = 16
    Width = 145
    Height = 32
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    Text = 'mjmjmj'
  end
  object BitBtn1: TBitBtn
    Left = 544
    Top = 16
    Width = 65
    Height = 33
    Caption = 'GO'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = BitBtn1Click
  end
  object edt3: TEdit
    Left = 48
    Top = 56
    Width = 537
    Height = 21
    TabOrder = 3
    Text = 'edt3'
  end
  object mmo1: TMemo
    Left = 40
    Top = 112
    Width = 617
    Height = 149
    Lines.Strings = (
      'mmo1')
    ScrollBars = ssVertical
    TabOrder = 4
  end
  object mmo2: TMemo
    Left = 40
    Top = 296
    Width = 617
    Height = 157
    Lines.Strings = (
      'mmo2')
    ScrollBars = ssVertical
    TabOrder = 5
  end
  object mmo3: TMemo
    Left = 40
    Top = 504
    Width = 617
    Height = 157
    Lines.Strings = (
      'mmo2')
    ScrollBars = ssVertical
    TabOrder = 6
  end
  object btn1: TButton
    Left = 664
    Top = 19
    Width = 73
    Height = 33
    Caption = #23548#20986
    TabOrder = 7
    OnClick = btn1Click
  end
  object btn2: TButton
    Left = 680
    Top = 80
    Width = 65
    Height = 25
    Caption = #23548#20837
    TabOrder = 8
    OnClick = btn2Click
  end
  object btn3: TButton
    Left = 680
    Top = 120
    Width = 65
    Height = 25
    Caption = 'Compare'
    TabOrder = 9
    OnClick = btn3Click
  end
  object btn4: TButton
    Left = 680
    Top = 160
    Width = 65
    Height = 25
    Caption = 'canAC'
    TabOrder = 10
    OnClick = btn4Click
  end
  object XPManifest1: TXPManifest
    Left = 8
  end
  object IdHTTP1: TIdHTTP
    MaxLineAction = maException
    ReadTimeout = 0
    AllowCookies = True
    ProxyParams.BasicAuthentication = False
    ProxyParams.ProxyPort = 0
    Request.ContentLength = -1
    Request.ContentRangeEnd = 0
    Request.ContentRangeStart = 0
    Request.ContentType = 'text/html'
    Request.Accept = 'text/html, */*'
    Request.BasicAuthentication = False
    Request.UserAgent = 'Mozilla/3.0 (compatible; Indy Library)'
    HTTPOptions = [hoForceEncodeParams]
    Left = 48
  end
  object dlgSave1: TSaveDialog
    Left = 8
    Top = 40
  end
end
