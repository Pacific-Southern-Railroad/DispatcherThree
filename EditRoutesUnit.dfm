object EditRoutes: TEditRoutes
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Edit Routes'
  ClientHeight = 595
  ClientWidth = 654
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnActivate = FormActivate
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label2: TLabel
    Left = 249
    Top = 8
    Width = 24
    Height = 13
    Caption = 'Train'
  end
  object RouteList: TListBox
    Left = 33
    Top = 367
    Width = 257
    Height = 189
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Courier New'
    Font.Style = []
    ItemHeight = 14
    ParentFont = False
    Sorted = True
    TabOrder = 0
  end
  object DellShoreRoutes: TPanel
    Left = 0
    Top = 42
    Width = 326
    Height = 103
    BevelKind = bkTile
    TabOrder = 1
    object Label1: TLabel
      Left = 118
      Top = 0
      Width = 86
      Height = 13
      Caption = 'Dell/Shore Routes'
    end
    object Label3: TLabel
      Left = 24
      Top = 13
      Width = 55
      Height = 13
      Caption = 'Westbound'
    end
    object Label4: TLabel
      Left = 247
      Top = 13
      Width = 51
      Height = 13
      Caption = 'Eastbound'
    end
    object WBLatham: TRadioButton
      Left = 30
      Top = 55
      Width = 73
      Height = 17
      Caption = 'Latham'
      TabOrder = 0
    end
    object WBHyde: TRadioButton
      Left = 30
      Top = 32
      Width = 57
      Height = 17
      Caption = 'Hyde'
      TabOrder = 1
    end
    object EBHyde: TRadioButton
      Left = 247
      Top = 32
      Width = 58
      Height = 25
      Caption = 'Hyde'
      TabOrder = 2
    end
    object EBKrulish: TRadioButton
      Left = 247
      Top = 79
      Width = 58
      Height = 17
      Caption = 'Krulish'
      TabOrder = 3
    end
    object DSAdd: TButton
      Left = 120
      Top = 38
      Width = 75
      Height = 25
      Caption = 'Add Route'
      TabOrder = 4
      OnClick = DSAddClick
    end
    object EBPort: TRadioButton
      Left = 247
      Top = 56
      Width = 113
      Height = 17
      Caption = 'Port'
      TabOrder = 5
    end
  end
  object Train: TEdit
    Left = 290
    Top = 8
    Width = 72
    Height = 28
    BevelKind = bkTile
    CharCase = ecUpperCase
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    MaxLength = 6
    ParentFont = False
    TabOrder = 2
  end
  object Delete: TButton
    Left = 88
    Top = 562
    Width = 131
    Height = 25
    Caption = 'Delete Selected Route'
    TabOrder = 3
    OnClick = DeleteClick
  end
  object HydeInboundRoutes: TPanel
    Left = 0
    Top = 158
    Width = 326
    Height = 203
    BevelKind = bkTile
    TabOrder = 4
    object Label5: TLabel
      Left = 104
      Top = 16
      Width = 105
      Height = 13
      Caption = 'Hyde Inbound Routes'
    end
    object Label6: TLabel
      Left = 24
      Top = 32
      Width = 55
      Height = 13
      Caption = 'Westbound'
    end
    object Label7: TLabel
      Left = 238
      Top = 32
      Width = 51
      Height = 13
      Caption = 'Eastbound'
    end
    object WBH30: TRadioButton
      Left = 30
      Top = 60
      Width = 55
      Height = 17
      Caption = 'H30'
      TabOrder = 0
    end
    object WBH32: TRadioButton
      Left = 30
      Top = 106
      Width = 63
      Height = 17
      Caption = 'H32'
      TabOrder = 1
    end
    object WBH33: TRadioButton
      Left = 30
      Top = 129
      Width = 55
      Height = 17
      Caption = 'H33'
      TabOrder = 2
    end
    object WBH34: TRadioButton
      Left = 30
      Top = 152
      Width = 55
      Height = 17
      Caption = 'H34'
      TabOrder = 3
    end
    object WBH12: TRadioButton
      Left = 30
      Top = 175
      Width = 65
      Height = 17
      Caption = 'H12'
      TabOrder = 4
    end
    object HYAdd: TButton
      Left = 118
      Top = 96
      Width = 75
      Height = 25
      Caption = 'Add Route'
      TabOrder = 5
      OnClick = HYAddClick
    end
    object EBH22: TRadioButton
      Left = 240
      Top = 59
      Width = 50
      Height = 17
      Caption = 'H22'
      TabOrder = 6
    end
    object EBH43: TRadioButton
      Left = 240
      Top = 82
      Width = 44
      Height = 17
      Caption = 'H43'
      TabOrder = 7
    end
    object EBH42: TRadioButton
      Left = 240
      Top = 105
      Width = 58
      Height = 17
      Caption = 'H42'
      TabOrder = 8
    end
    object EBH41: TRadioButton
      Left = 238
      Top = 128
      Width = 113
      Height = 17
      Caption = 'H41'
      TabOrder = 9
    end
    object EBH40: TRadioButton
      Left = 238
      Top = 151
      Width = 50
      Height = 17
      Caption = 'H40'
      TabOrder = 10
    end
    object WBH31: TRadioButton
      Left = 30
      Top = 83
      Width = 52
      Height = 17
      Caption = 'H31'
      TabOrder = 11
    end
  end
  object NassauRoutes: TPanel
    Left = 332
    Top = 42
    Width = 326
    Height = 163
    BevelKind = bkTile
    TabOrder = 5
    object Label8: TLabel
      Left = 120
      Top = 0
      Width = 72
      Height = 13
      Caption = 'Nassau Routes'
    end
    object Label9: TLabel
      Left = 16
      Top = 14
      Width = 55
      Height = 13
      Caption = 'Westbound'
    end
    object Label10: TLabel
      Left = 232
      Top = 14
      Width = 51
      Height = 13
      Caption = 'Eastbound'
    end
    object WBN31R10: TRadioButton
      Left = 26
      Top = 59
      Width = 71
      Height = 17
      Caption = 'N31, R10'
      TabOrder = 0
    end
    object WBN32B10: TRadioButton
      Left = 26
      Top = 36
      Width = 80
      Height = 17
      Caption = 'N32, B10'
      TabOrder = 1
    end
    object WBN12B10: TRadioButton
      Left = 26
      Top = 107
      Width = 65
      Height = 17
      Caption = 'N12, B10'
      TabOrder = 2
    end
    object EBN22B20: TRadioButton
      Left = 240
      Top = 33
      Width = 65
      Height = 17
      Caption = 'N22, B20'
      TabOrder = 3
    end
    object EBN41: TRadioButton
      Left = 240
      Top = 56
      Width = 50
      Height = 17
      Caption = 'N41'
      TabOrder = 4
    end
    object EBN42: TRadioButton
      Left = 240
      Top = 125
      Width = 50
      Height = 17
      Caption = 'N42'
      TabOrder = 5
    end
    object NAAdd: TButton
      Left = 120
      Top = 56
      Width = 75
      Height = 25
      Caption = 'Add Route'
      TabOrder = 6
      OnClick = NAAddClick
    end
    object WBN31B10: TRadioButton
      Left = 26
      Top = 82
      Width = 73
      Height = 17
      Caption = 'N31, B10'
      TabOrder = 7
    end
    object EBN41R10: TRadioButton
      Left = 240
      Top = 79
      Width = 65
      Height = 17
      Caption = 'N41, R10'
      TabOrder = 8
    end
    object EBN41B20: TRadioButton
      Left = 240
      Top = 102
      Width = 65
      Height = 17
      Caption = 'N41, B20'
      TabOrder = 9
    end
  end
end
