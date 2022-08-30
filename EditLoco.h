//---------------------------------------------------------------------------
#ifndef EditLocoH
#define EditLocoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TEditLocos : public TForm
{
__published:	// IDE-managed Components
	TListBox *LocoList;
	TEdit *LocoNo;
	TLabel *Label1;
	TButton *Add;
	TButton *Delete;
	TEdit *Start;
	TEdit *Approach;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TUpDown *UpDownNormal;
	TUpDown *UpDownApproach;
	TLabel *Message;
	TEdit *Accel;
	TEdit *Decel;
	TUpDown *UpDownAccel;
	TUpDown *UpDownDecel;
	TButton *Replace;
	TLabel *Label2;
	TLabel *Label6;
	TUpDown *UpDownStart;
	TLabel *Label7;
	TEdit *Medium;
	TUpDown *UpDownMedium;
	TEdit *Normal;
	void __fastcall LocoNoKeyPress(TObject *Sender, char &Key);
	
	
	void __fastcall AddClick(TObject *Sender);
	void __fastcall DeleteClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	
	void __fastcall LocoListClick(TObject *Sender);
	void __fastcall ReplaceClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall UpDownNormalClick(TObject *Sender, TUDBtnType Button);
	void __fastcall UpDownApproachClick(TObject *Sender, TUDBtnType Button);
	void __fastcall UpDownStartClick(TObject *Sender, TUDBtnType Button);
private:	// User declarations

	bool inLocoList(String S);
	bool LocosEdited;
	void SetDefaults(void);
	void Adjust();

public:		// User declarations

   String GetLocoData(String Loco);
   void LoadLocoList(void);


	__fastcall TEditLocos(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TEditLocos *EditLocos;
//---------------------------------------------------------------------------
#endif
