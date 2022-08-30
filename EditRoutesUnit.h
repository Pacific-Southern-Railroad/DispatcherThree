//---------------------------------------------------------------------------

#ifndef EditRoutesUnitH
#define EditRoutesUnitH
#include "PSRYUnit.h"
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TEditRoutes : public TForm
{
__published:	// IDE-managed Components
	TListBox *RouteList;
	TPanel *DellShoreRoutes;
	TRadioButton *WBLatham;
	TRadioButton *WBHyde;
	TRadioButton *EBHyde;
	TRadioButton *EBKrulish;
	TButton *DSAdd;
	TLabel *Label1;
	TEdit *Train;
	TLabel *Label2;
	TButton *Delete;
	TLabel *Label3;
	TLabel *Label4;
	TRadioButton *EBPort;
	TPanel *HydeInboundRoutes;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TRadioButton *WBH30;
	TRadioButton *WBH32;
	TRadioButton *WBH33;
	TRadioButton *WBH34;
	TRadioButton *WBH12;
	TButton *HYAdd;
	TRadioButton *EBH22;
	TRadioButton *EBH43;
	TRadioButton *EBH42;
	TRadioButton *EBH41;
	TRadioButton *EBH40;
	TRadioButton *WBH31;
	TPanel *NassauRoutes;
	TLabel *Label8;
	TRadioButton *WBN31R10;
	TRadioButton *WBN32B10;
	TRadioButton *WBN12B10;
	TRadioButton *EBN22B20;
	TRadioButton *EBN41;
	TRadioButton *EBN42;
	TLabel *Label9;
	TLabel *Label10;
	TButton *NAAdd;
	TRadioButton *WBN31B10;
	TRadioButton *EBN41R10;
	TRadioButton *EBN41B20;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall DSAddClick(TObject *Sender);
	void __fastcall DeleteClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall HYAddClick(TObject *Sender);
	void __fastcall NAAddClick(TObject *Sender);
private:	// User declarations

	bool InRouteList(String Train, String Tower);

public:		// User declarations
    bool RoutesEdited;
	__fastcall TEditRoutes(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEditRoutes *EditRoutes;
//---------------------------------------------------------------------------
#endif
