//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "EditRoutesUnit.h"
#include "PSRYUnit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEditRoutes *EditRoutes;
//---------------------------------------------------------------------------
__fastcall TEditRoutes::TEditRoutes(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TEditRoutes::FormActivate(TObject *Sender)
{
	Train->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TEditRoutes::DSAddClick(TObject *Sender)
{
	if(Train->Text != "" && (WBHyde->Checked || WBLatham->Checked))  //Westbound
	{
		bool InList = InRouteList(Train->Text, "Dell/ShoreW");

		if(!InList)
		{
			String L = AnsiString::StringOfChar(' ', 40);
			L.Insert(Train->Text, 1);
			L.Insert("Dell/ShoreW", 8);
			if(WBHyde->Checked)
				L.Insert("Hyde", 25);
			else if(WBLatham->Checked)
				L.Insert("Latham", 25);
			L = L.TrimRight();
			RouteList->Items->Append(L);
			RoutesEdited = true;
		}
		else
			Application->MessageBox(L"Route already in list", L"Pacific Southern", MB_OK);
		Train->Text = "";
		Train->SetFocus();
		WBHyde->Checked = false;
		WBLatham->Checked = false;
	}
	else if(Train->Text != "" && (EBHyde->Checked || EBPort->Checked || EBKrulish->Checked)) //Eastbound
	{
		bool InList = InRouteList(Train->Text, "Dell/ShoreE");

		if(!InList)
		{
			String L = AnsiString::StringOfChar(' ', 40);
			L.Insert(Train->Text, 1);
			L.Insert("Dell/ShoreE", 8);
			if(EBHyde->Checked)
				L.Insert("Hyde", 25);
			else if(EBPort->Checked)
				L.Insert("Port", 25);
			else if(EBKrulish->Checked)
				L.Insert("Krulish", 25);
			L = L.TrimRight();
			RouteList->Items->Append(L);
			RoutesEdited = true;
		}
		else
			Application->MessageBox(L"Route already in list", L"Pacific Southern", MB_OK);
		Train->Text = "";
		Train->SetFocus();
		EBHyde->Checked = false;
		EBPort->Checked = false;
		EBKrulish->Checked = false;
	}
}
//---------------------------------------------------------------------------

bool TEditRoutes::InRouteList(String Train, String Tower)
{
	int N = RouteList->Items->Count;

	for(int i = 0; i < N; i++)
	{
		String F = RouteList->Items->Strings[i];
		String X = F.SubString(1, 6).Trim();
		String Y = F.SubString(8, 15).Trim();
		if(X == Train && Y == Tower)
		{
			RouteList->ItemIndex = i;
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------

void __fastcall TEditRoutes::DeleteClick(TObject *Sender)
{
	if(RouteList->ItemIndex != -1)
	{
		Application->MessageBox(L"You are about to delete the selected route.", L"Pacific Southern", MB_OK);

		{
			RoutesEdited = true;
			RouteList->Items->Delete(RouteList->ItemIndex);
			Train->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TEditRoutes::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(RoutesEdited)
	{
		RoutesEdited = false;
		Application->MessageBox(L"Save changes to Route List?", L"", MB_YESNO);
		{
		if(PSRY->IDListA->Checked)
			RouteList->Items->SaveToFile("C:/DispatcherTextFiles/RoutesA.txt");
		else if(PSRY->IDListB->Checked)
			RouteList->Items->SaveToFile("C:/DispatcherTextFiles/RoutesB.txt");
		else if(PSRY->IDListC->Checked)
			RouteList->Items->SaveToFile("C:/DispatcherTextFiles/RoutesC.txt");
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TEditRoutes::FormCreate(TObject *Sender)
{
	if(PSRY->IDListA->Checked)
		RouteList->Items->LoadFromFile("C:/DispatcherTextFiles/RoutesA.txt");
	else if(PSRY->IDListB->Checked)
		RouteList->Items->LoadFromFile("C:/DispatcherTextFiles/RoutesB.txt");
	else if(PSRY->IDListC->Checked)
		RouteList->Items->LoadFromFile("C:/DispatcherTextFiles/RoutesC.txt");
}
//---------------------------------------------------------------------------

void __fastcall TEditRoutes::HYAddClick(TObject *Sender)
{
	if(Train->Text != "" && (WBH34->Checked || WBH30->Checked || WBH31->Checked ||
		WBH32->Checked || WBH33->Checked || WBH12->Checked))
	{
		bool InList = InRouteList(Train->Text, "HydeInW");

		if(!InList)
		{
			String L = AnsiString::StringOfChar(' ', 40);
			L.Insert(Train->Text, 1);
			L.Insert("HydeInW", 8);
			if(WBH30->Checked)
				L.Insert("H30", 25);
			else if(WBH31->Checked)
				L.Insert("H31", 25);
			else if(WBH32->Checked)
				L.Insert("H32", 25);
			else if(WBH33->Checked)
				L.Insert("H33", 25);
			else if(WBH34->Checked)
				L.Insert("H34", 25);
			else if(WBH12->Checked)
				L.Insert("H12", 25);
			L = L.TrimRight();
			RouteList->Items->Append(L);
			RoutesEdited = true;
		}
		else
			Application->MessageBox(L"Route already in list", L"Pacific Southern", MB_OK);
		Train->Text = "";
		Train->SetFocus();
		WBH30->Checked = false;
		WBH31->Checked = false; WBH32->Checked = false;
		WBH33->Checked = false; WBH34->Checked = false;
		WBH12->Checked = false;
	}
	else if(Train->Text != "" && (EBH22->Checked || EBH43->Checked ||
		EBH42->Checked || EBH41->Checked || EBH40->Checked))
	{
		bool InList = InRouteList(Train->Text, "HydeInE");

		if(!InList)
		{
			String L = AnsiString::StringOfChar(' ', 40);
			L.Insert(Train->Text, 1);
			L.Insert("HydeInE", 8);
			if(EBH22->Checked)
				L.Insert("H22", 25);
			else if(EBH43->Checked)
				L.Insert("H43", 25);
			else if(EBH42->Checked)
				L.Insert("H42", 25);
			else if(EBH41->Checked)
				L.Insert("H41", 25);
			else if(EBH40->Checked)
				L.Insert("H40", 25);
			L = L.TrimRight();
			RouteList->Items->Append(L);
			RoutesEdited = true;
		}
		else
			Application->MessageBox(L"Route already in list", L"Pacific Southern", MB_OK);
		Train->Text = "";
		Train->SetFocus();
		EBH22->Checked = false; EBH43->Checked = false; EBH42->Checked = false;
		EBH41->Checked = false; EBH40->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TEditRoutes::NAAddClick(TObject *Sender)
{
	if(Train->Text != "" && (EBN22B20->Checked || EBN41->Checked ||
		EBN41R10->Checked || EBN41B20->Checked || EBN42->Checked))
	{
		bool InList = InRouteList(Train->Text, "NassauE");
		if(!InList)
		{
			String L = AnsiString::StringOfChar(' ', 40);
			L.Insert(Train->Text, 1);
			L.Insert("NassauE", 8);
			if(EBN22B20->Checked)
				L.Insert("N22B20", 25);
			else if(EBN41->Checked)
				L.Insert("N41", 25);
			else if(EBN41R10->Checked)
				L.Insert("N41R10", 25);
			else if(EBN41B20->Checked)
				L.Insert("N41B20", 25);
			else if(EBN42->Checked)
				L.Insert("N42", 25);
			L = L.TrimRight();
			RouteList->Items->Append(L);
			RoutesEdited = true;
		}
		else
			Application->MessageBox(L"Route already in list", L"Pacific Southern", MB_OK);
		Train->Text = "";
		Train->SetFocus();
		EBN22B20->Checked = false;	EBN41->Checked = false; EBN41R10->Checked = false;
		EBN41B20->Checked = false;  EBN42->Checked = false;
	}
	else if(Train->Text != "" && (WBN32B10->Checked ||
		WBN31R10->Checked || WBN31B10->Checked || WBN12B10->Checked))
	{
		bool InList = InRouteList(Train->Text, "NassauW");
		if(!InList)
		{
			String L = AnsiString::StringOfChar(' ', 40);
			L.Insert(Train->Text, 1);
			L.Insert("NassauW", 8);
			if(WBN32B10->Checked)
				L.Insert("N32B10", 25);
			else if(WBN31R10->Checked)
				L.Insert("N31R10", 25);
			else if(WBN31B10->Checked)
				L.Insert("N31B10", 25);
			else if(WBN12B10->Checked)
				L.Insert("N12B10", 25);
			L = L.TrimRight();
			RouteList->Items->Append(L);
			RoutesEdited = true;
		}
		else
			Application->MessageBox(L"Route already in list", L"Pacific Southern", MB_OK);
		Train->Text = "";
		Train->SetFocus();
		WBN32B10->Checked = false; WBN31R10->Checked = false;
		WBN31B10->Checked = false; WBN12B10->Checked = false;
	}
}
//---------------------------------------------------------------------------

