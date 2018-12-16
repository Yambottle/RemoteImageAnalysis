object Form1: TForm1
  Left = 196
  Top = 126
  Width = 928
  Height = 481
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
  object Image1: TImage
    Left = 456
    Top = 16
    Width = 409
    Height = 393
  end
  object Button1: TButton
    Left = 304
    Top = 136
    Width = 137
    Height = 57
    Caption = #26174#31034#22270#20687
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 304
    Top = 200
    Width = 137
    Height = 65
    Caption = #32553#23567#22270#20687
    TabOrder = 1
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 304
    Top = 272
    Width = 137
    Height = 65
    Caption = #25918#22823#22270#20687
    TabOrder = 2
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 304
    Top = 72
    Width = 137
    Height = 57
    Caption = #28023#38470#20998#31163
    TabOrder = 3
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 304
    Top = 8
    Width = 137
    Height = 57
    Caption = #23548#20837#22270#20687
    TabOrder = 4
    OnClick = Button5Click
  end
  object DBGrid1: TDBGrid
    Left = 8
    Top = 40
    Width = 281
    Height = 337
    DataSource = DataSource1
    TabOrder = 5
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
  end
  object Edit1: TEdit
    Left = 8
    Top = 8
    Width = 281
    Height = 21
    TabOrder = 6
    Text = 'Edit1'
  end
  object ADOConnection1: TADOConnection
    ConnectionString = 
      'Provider=SQLOLEDB.1;Password=seaside;Persist Security Info=True;' +
      'User ID=SeaSide;Initial Catalog=SeaSide;Data Source=Yang'
    Provider = 'SQLOLEDB.1'
    Left = 104
    Top = 384
  end
  object ADOQuery1: TADOQuery
    Connection = ADOConnection1
    Parameters = <>
    Left = 72
    Top = 384
  end
  object DataSource1: TDataSource
    DataSet = ADOQuery1
    Left = 40
    Top = 384
  end
  object ADOTable1: TADOTable
    Connection = ADOConnection1
    MasterSource = DataSource1
    Left = 136
    Top = 384
  end
end
