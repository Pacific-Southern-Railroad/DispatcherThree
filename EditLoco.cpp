//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "EditLoco.h"
#include "PSRYUnit.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TEditLocos *EditLocos;
//---------------------------------------------------------------------------
__fastcall TEditLocos::TEditLocos(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TEditLocos::LocoNoKeyPress(TObject *Sender, char &Key)
{
	if (!(Key >= '0' && Key <= '9'))
	Key = 0;
}
//---------------------------------------------------------------------------

void __fastcall TEditLocos::AddClick(TObject *Sender)
{
	if(LocoNo->Text != "")
	{
		String N = LocoNo->Text;
		int Num = StrToInt(N);
		bool In = inLocoList(N);
		if(!In)
		{
			String L = AnsiString::StringOfChar(' ', 60);
			L.Insert(LocoNo->Text, 1);
			L.Insert(Start->Text, 8);
			L.Insert(Approach->Text, 16);
			L.Insert(Medium->Text, 24);
			L.Insert(Normal->Text, 32);
			L.Insert(Accel->Text, 40);
			L.Insert(Decel->Text, 46);
			L = L.TrimRight();
			LocoList->Items->Append(L);
            PSRY->LocosEdited = true;
			LoadLocoList();
			LocoNo->Text = "";
			LocoNo->SetFocus();
			Message->Caption = "";
			SetDefaults();
			LocosEdited = true;
		}
			else
				Application->MessageBox(L"Loco already in list", L"Pacific Southern", MB_OK);
	}
}
//---------------------------------------------------------------------------

void __fastcall TEditLocos::UpDownStartClick(TObject *Sender, TUDBtnType Button)
{
	Adjust();
}
//---------------------------------------------------------------------------

void __fastcall TEditLocos::UpDownApproachClick(TObject *Sender, TUDBtnType Button)
{
	Adjust();
}
//---------------------------------------------------------------------------

void __fastcall TEditLocos::UpDownNormalClick(TObject *Sender, TUDBtnType Button)
{
	Adjust();
}
//---------------------------------------------------------------------------

bool TEditLocos::inLocoList(String S)
{
	int N = LocoList->Items->Count;

	for(int i = 0; i < N; i++)
	{
		String F = LocoList->Items->Strings[i];
		String SubF = F.SubString(1, 4).Trim();
		if(SubF == S) return true;
	}
	return false;
}
//---------------------------------------------------------------------------

void TEditLocos::SetDefaults(void)
{
	UpDownStart->Position = 0;
	UpDownApproach->Position = 10;
	UpDownNormal->Position = 80;
	UpDownAccel->Position = 1;
	UpDownDecel->Position = 1;
	LocoNo->Text = "";
	Adjust();
}
//---------------------------------------------------------------------------

void TEditLocos::Adjust()
{
	UpDownStart->Max = UpDownApproach->Position - 5;
	UpDownApproach->Min = UpDownStart->Position + 5;
	UpDownApproach->Max = UpDownNormal->Position - 10;
 	UpDownMedium->Min = UpDownApproach->Position + 5;
	UpDownMedium->Position = UpDownApproach->Position +
		0.7 * (UpDownNormal->Position - UpDownApproach->Position);
	UpDownMedium->Max = UpDownNormal->Position -5;
	UpDownNormal->Min = UpDownApproach->Position + 10;
}
//---------------------------------------------------------------------------

String TEditLocos::GetLocoData(String Loco)
{
 	int N = LocoList->Items->Count;

	for(int i = 0; i < N; i++)
	{
		String F = LocoList->Items->Strings[i];
		String SubF = F.SubString(1, 4).Trim();
		if(SubF == Loco) return F;
	}
	return "";
}
//---------------------------------------------------------------------------

void TEditLocos::LoadLocoList(void)
{
	if(LocoList->Items->Count != 0)
	{
		PSRY->LocoList->Clear();
        PSRY->LocoList->Items->Append("");
		int N = LocoList->Items->Count;
		for(int i = 0; i < N; i++)
		{
			String E = LocoList->Items->Strings[i];
			String SubE = E.SubString(1,4).Trim();
			PSRY->LocoList->Items->Append(SubE);
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TEditLocos::DeleteClick(TObject *Sender)
{
	if(LocoList->ItemIndex != -1)
	{
		int A = Application->MessageBox(L"Do you want to delete the selected loco.", L"Pacific Southern", MB_YESNO);
		if(A == 6)
		{
			LocosEdited = true;
			LocoList->Items->Delete(LocoList->ItemIndex);
			LoadLocoList();
			LocoNo->SetFocus();
			SetDefaults();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TEditLocos::FormActivate(TObject *Sender)
{
	SetDefaults();
}
//---------------------------------------------------------------------------
void __fastcall TEditLocos::LocoListClick(TObject *Sender)
{
	String E = LocoList->Items->Strings[LocoList->ItemIndex];
	LocoNo->Text = StrToInt(E.SubString(1,4).Trim());
	UpDownApproach->Position = StrToInt(E.SubString(16, 3).Trim());
	UpDownNormal->Position = StrToInt(E.SubString(32, 3).Trim());
	Adjust();
	UpDownStart->Position = StrToInt(E.SubString(8, 3).Trim());
	UpDownMedium->Position = StrToInt(E.SubString(24, 3).Trim());
	UpDownAccel->Position = StrToInt(E.SubString(40, 2).Trim());
	UpDownDecel->Position = StrToInt(E.SubString(46, 2).Trim());
	Replace->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TEditLocos::ReplaceClick(TObject *Sender)
{
	if(LocoList->ItemIndex != -1)
	{
		LocoList->Items->Delete(LocoList->ItemIndex);
		AddClick(this);
 		Replace->Enabled = false;
		LocoList->ItemIndex = -1;
		LocosEdited = true;
		SetDefaults();
	}
}
//---------------------------------------------------------------------------

void __fastcall TEditLocos::FormCreate(TObject *Sender)
{
	LocoList->Items->LoadFromFile("C:/DispatcherTextFiles/Locos.txt");
	LoadLocoList();
}
//---------------------------------------------------------------------------

void __fastcall TEditLocos::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(LocosEdited)
	{
		LocosEdited = false;
		int A = Application->MessageBox(L"Save changes to loco list?", L"", MB_YESNO);
		if(A == 6)
		{
			LocoList->Items->SaveToFile("C:/DispatcherTextFiles/Locos.txt");
		}
	}
}
//---------------------------------------------------------------------------










