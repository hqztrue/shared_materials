object Form1: TForm1
  Left = 212
  Top = 115
  Width = 870
  Height = 640
  Caption = 'Form1'
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
  object Button1: TButton
    Left = 352
    Top = 144
    Width = 169
    Height = 57
    Caption = 'Button1'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Memo1: TMemo
    Left = 72
    Top = 72
    Width = 169
    Height = 313
    Lines.Strings = (
      'Memo1')
    TabOrder = 1
  end
  object Button2: TButton
    Left = 424
    Top = 328
    Width = 129
    Height = 65
    Caption = 'Button2'
    TabOrder = 2
    OnClick = Button2Click
  end
end
