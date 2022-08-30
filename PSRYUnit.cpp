//-----------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PSRYUnit.h"
#include "EditLoco.h"
#include "EditRoutesUnit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPSRY *PSRY;
//---------------------------------------------------------------------------
__fastcall TPSRY::TPSRY(TComponent* Owner)
   : TForm(Owner)
{
}
void __fastcall TPSRY::FormCreate(TObject *Sender)
{
//Load tile bitmaps

	LoadTile("blank.bmp");		//0
	LoadTile("crossingX.bmp");	//1
	LoadTile("trackH.bmp");		//2
	LoadTile("trackV.bmp");		//3
	LoadTile("blockHR.bmp");	//4
	LoadTile("blockHL.bmp");	//5
	LoadTile("diagonalDU.bmp");	//6
	LoadTile("diagonalUD.bmp");	//7
	LoadTile("angleDL.bmp");	//8
	LoadTile("angleDR.bmp");	//9
	LoadTile("angleUL.bmp");	//10
	LoadTile("angleUR.bmp");	//11
	LoadTile("angleVUR.bmp");	//12
	LoadTile("angleVUL.bmp");	//13
	LoadTile("angleVDR.bmp");	//14
	LoadTile("angleVDL.bmp");	//15
	LoadTile("hsignalR.bmp");	//16
	LoadTile("hsignalL.bmp");	//17
	LoadTile("dsignalR.bmp");	//18
	LoadTile("dsignalL.bmp");	//19
	LoadTile("switchMKR.bmp");	//20
	LoadTile("trackRHL.bmp");	//21
	LoadTile("trackRHR.bmp");	//22
	LoadTile("stopR.bmp");		//23
	LoadTile("buttonUP.bmp");  	//24
	LoadTile("buttonDN.bmp");  	//25
	LoadTile("hSwUW.bmp");		//26
	LoadTile("hSwUR.bmp");		//27
	LoadTile("hSwDW.bmp");		//28
	LoadTile("hSwDR.bmp");		//29
	LoadTile("blank.bmp");		//30
	LoadTile("trackYD.bmp");		//31
	LoadTile("trackRH.bmp");		//32
	LoadTile("trackRV.bmp");		//33
	LoadTile("blockRHR.bmp");		//34
	LoadTile("blockRHL.bmp");		//35
	LoadTile("diagonalRDU.bmp");	//36
	LoadTile("diagonalRUD.bmp");	//37
	LoadTile("angleRDL.bmp");		//38
	LoadTile("angleRDR.bmp");		//39
	LoadTile("angleRUL.bmp");		//40
	LoadTile("angleRUR.bmp");		//41
	LoadTile("angleRVUR.bmp");		//42
	LoadTile("angleRVUL.bmp");		//43
	LoadTile("angleRVDR.bmp");		//44
	LoadTile("angleRVDL.bmp");		//45
	LoadTile("hsignalRG.bmp");		//46
	LoadTile("hsignalLG.bmp");		//47
	LoadTile("dsignalRY.bmp");		//48
	LoadTile("dsignalLY.bmp");		//49
	LoadTile("trackGHL.bmp");		//50
	LoadTile("trackGHR.bmp");		//51
	LoadTile("trackYD.bmp");       	//52
	LoadTile("blank.bmp");          //53
	LoadTile("blank.bmp");          //54
	LoadTile("blank.bmp");          //55
	LoadTile("hsignalRW.bmp");      //56
	LoadTile("hsignalLW.bmp");		//57
	LoadTile("dsignalRW.bmp");		//58
	LoadTile("dsignalLW.bmp");		//59
	LoadTile("blank.bmp");          //60
	LoadTile("trackRYD.bmp");     	//61
	LoadTile("trackGH.bmp");		//62
	LoadTile("trackGV.bmp");		//63
	LoadTile("blockGHR.bmp");		//64
	LoadTile("blockGHL.bmp");		//65
	LoadTile("diagonalGDU.bmp");	//66
	LoadTile("diagonalGUD.bmp");	//67
	LoadTile("angleGDL.bmp");		//68
	LoadTile("angleGDR.bmp");		//69
	LoadTile("angleGUL.bmp");		//70
	LoadTile("angleGUR.bmp");		//71
	LoadTile("angleGVUR.bmp");		//72
	LoadTile("angleGVUL.bmp");		//73
	LoadTile("angleGVDR.bmp");		//74
	LoadTile("angleGVDL.bmp");		//75
	LoadTile("hsignalRC.bmp");		//76
	LoadTile("hsignalLC.bmp");		//77
	LoadTile("fleetL.bmp");			//78
	LoadTile("fleetR.bmp");			//79
	LoadTile("stopA.bmp");			//80
	LoadTile("stopL.bmp");			//81
	LoadTile("indicatorR.bmp");		//82
	LoadTile("indicatorG.bmp");		//83
	LoadTile("indicatorOut.bmp");	//84
	LoadTile("resetL.bmp");			//85
	LoadTile("resetR.bmp");			//86
	for(int i=0; i<4; i++)			//87-90
	{
		LoadTile("blank.bmp");
	}
	LoadTile("trackGYD.bmp");     	//91

//Load USS Machine images

	LoadShortLevers("LvrShBL.bmp");	//0
	LoadShortLevers("LvrShBM.bmp");	//1
	LoadShortLevers("LvrShBR.bmp");	//2
	LoadShortLevers("LvrShTL.bmp");	//3
	LoadShortLevers("LvrShTR.bmp");	//4

	LoadLongLevers("LvrLgBL.bmp");	//0
	LoadLongLevers("LvrLgBM.bmp");	//1
	LoadLongLevers("LvrLgBR.bmp");	//2
	LoadLongLevers("LvrLgTL.bmp");	//3
	LoadLongLevers("LvrLgTR.bmp");	//4

	LoadUSSLamps("USSLampOut.bmp");     //0
	LoadUSSLamps("USSLampS.bmp");		//1
	LoadUSSLamps("USSLampL.bmp");		//2
	LoadUSSLamps("USSLampR.bmp");		//3
	LoadUSSLamps("USSButtonUp.bmp");	//4
	LoadUSSLamps("USSButtonDn.bmp");	//5
	LoadUSSLamps("USSLampK.bmp");		//6
	LoadUSSLamps("USSLampF.bmp");		//7
	LoadUSSLamps("USSLampGreen.bmp");	//8

//Load cab signals

	LoadCabSignals("ClearSignal.bmp");   		//0
	LoadCabSignals("ApproachMediumSignal.bmp"); //1
	LoadCabSignals("ApproachSignal.bmp");    	//2
	LoadCabSignals("StopSignal.bmp");    		//3
	LoadCabSignals("PRRClear.bmp");         	//4
	LoadCabSignals("PRRApproachMedium.bmp");    //5
	LoadCabSignals("PRRApproach.bmp");          //6
	LoadCabSignals("PRRRestricting.bmp");       //7

//Load diagrams

	ImageHyYdPt->Picture->LoadFromFile("../Bitmaps/Diagrams/HydeYardPort2021.bmp");
	ImageHyYdPt->Canvas->Font->Color = clRed;
	ImageHyYdPt->Canvas->Font->Size = 8;
	HyYdPt.Image = ImageHyYdPt;

	ImageLaKr->Picture->LoadFromFile("../Bitmaps/Diagrams/LathamKrulish2019.bmp");


	ImageLaKr->Canvas->Font->Color = clRed;
	ImageLaKr->Canvas->Font->Size = 8;
	LaKr.Image = ImageLaKr;

	ImageNaCf->Picture->LoadFromFile("../Bitmaps/Diagrams/NassauCliff2019.bmp");
	ImageNaCf->Canvas->Font->Color = clRed;
    ImageNaCf->Canvas->Font->Size = 8;
	NaCf.Image = ImageNaCf;

//Set display pointers and load Source arrays

	TMemoryStream* Stream = new TMemoryStream;
	int ptr;
	char temp;

	Stream->Clear();
	Stream->LoadFromFile("../Arrays/HydeYardPortArray2021.arr");
	Stream->Read(strArray, 10000);

	ptr = 0;

	for(int j=0; j<Rows; j++)
	{
		for(int i=0; i<Cols; i++)
		{
			temp = char(strArray[ptr]-48);
			HyYdPt.Source[i*Rows + j] = temp;
			HyYdPt.Display[i*Rows + j] = temp;
			ptr++;
		}
	}

	Stream->Clear();
	Stream->LoadFromFile("../Arrays/LathamKrulishArray2019.arr");
	Stream->Read(strArray, 10000);

	ptr = 0;

	for(int j=0; j<Rows; j++)
	{
		for(int i=0; i<Cols; i++)
		{
			temp = char(strArray[ptr]-48);
			LaKr.Source[i*Rows + j] = temp;
			LaKr.Display[i*Rows + j] = temp;
			ptr++;
		}
	}

	Stream->Clear();
	Stream->LoadFromFile("../Arrays/NassauCliffArray2019.arr");
	Stream->Read(strArray, 10000);

	ptr = 0;

	for(int j=0; j<Rows; j++)
	{
		for(int i=0; i<Cols; i++)
		{
			temp = char(strArray[ptr]-48);
			NaCf.Source[i*Rows + j] = temp;
			NaCf.Display[i*Rows + j] = temp;
			ptr++;
		}
	}

  delete Stream;

//Load Block/Loco list

	LocoBlockList->Items->LoadFromFile("C:/DispatcherTextFiles/LocoBlockList.txt");

//Set current IDs

	CurrentIDs->Lines->LoadFromFile("C:/DispatcherTextFiles/CurrentIDs.txt");
	if(CurrentIDs->Text == "IDListA")
		IDListA->Checked = true;
	else if(CurrentIDs->Text == "IDListB")
		IDListB->Checked = true;
	else if(CurrentIDs->Text == "IDListC")
		IDListC->Checked = true;

//Image names

	HyYdPt.ImageName = "HyYdPt";
	LaKr.ImageName = "LaKr";
	NaCf.ImageName = "NaCf";

//Origins for track diagrams to correct for offset of tile arrays

	HyYdPt.DiaXOrigin = -20;
	HyYdPt.DiaYOrigin = 20;
	LaKr.DiaXOrigin = 0;
	LaKr.DiaYOrigin = 20;
	NaCf.DiaXOrigin = 0;
	NaCf.DiaYOrigin = 20;

//Origins for USS panels

	HyYdPt.XOrigin = 363;
	HyYdPt.YOrigin = 514;
	LaKr.XOrigin = 46;
	LaKr.YOrigin = 514;
	NaCf.XOrigin = 113;
	NaCf.YOrigin = 514;

 //Initialize columns for Latham-Krulish

	for(int i = 0; i < 40; i++)
	{
		LaKr.USSCol[i].pImage = ImageLaKr;
		LaKr.USSCol[i].pCol = &LaKr.USSCol[i];
		LaKr.USSCol[i].XOR = LaKr.XOrigin + i*64;
		LaKr.USSCol[i].YOR = LaKr.YOrigin;
		LaKr.USSCol[i].pSw = 0;
		LaKr.USSCol[i].pSigL = 0;
		LaKr.USSCol[i].pFltL = 0;
	}

//Initialize columns for Nassau-Cliff

	for(int i = 0; i < 30; i++)
	{
		NaCf.USSCol[i].pImage = ImageNaCf;
		NaCf.USSCol[i].pCol = &NaCf.USSCol[i];
		NaCf.USSCol[i].XOR = NaCf.XOrigin + i*64;
		NaCf.USSCol[i].YOR = NaCf.YOrigin;
		NaCf.USSCol[i].pSw = 0;
		NaCf.USSCol[i].pSigL = 0;
		NaCf.USSCol[i].pFltL = 0;
	}

//Activate sockets

	RemoteDisplaySocket->Active = true;
	RemoteThrottleSocket->Active = true;
	RemoteDispatcherSocket->Active = true;

//Open serial port for railroad connection via USB & Edgeport box (COM5)

	RRcomHandle = CreateFile(L"COM5", GENERIC_READ|GENERIC_WRITE, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	GetCommState(RRcomHandle, &RRdcb);

	RRdcb.BaudRate = 19200;
	RRdcb.ByteSize = 8;
	RRdcb.Parity = NOPARITY;
	RRdcb.StopBits = ONESTOPBIT;

	SetCommState(RRcomHandle, &RRdcb);

	RRtimeouts.ReadIntervalTimeout = MAXDWORD;
	RRtimeouts.ReadTotalTimeoutMultiplier = 0;
	RRtimeouts.ReadTotalTimeoutConstant = 0;
	RRtimeouts.WriteTotalTimeoutMultiplier = 0;
	RRtimeouts.WriteTotalTimeoutConstant = 0;
	SetCommTimeouts(RRcomHandle, &RRtimeouts);


//Open serial port for link to NCE command station via USB & Edgeport box (COM6)


	DCCcomHandle = CreateFile(L"COM6", GENERIC_READ|GENERIC_WRITE, 0, 0,
									OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	GetCommState(DCCcomHandle, &DCCdcb);

	DCCdcb.BaudRate = 9600;
	DCCdcb.ByteSize = 8;
	DCCdcb.Parity = NOPARITY;
	DCCdcb.StopBits = ONESTOPBIT;

	SetCommState(DCCcomHandle, &DCCdcb);

	DCCtimeouts.ReadIntervalTimeout = MAXDWORD;
	DCCtimeouts.ReadTotalTimeoutMultiplier = 0;
	DCCtimeouts.ReadTotalTimeoutConstant = 0;
	DCCtimeouts.WriteTotalTimeoutMultiplier = 0;
	DCCtimeouts.WriteTotalTimeoutConstant = 0;
	SetCommTimeouts(DCCcomHandle, &DCCtimeouts);

//Serial port for link to DCCServer for track speeds

	TScomHandle = CreateFile(L"COM4", GENERIC_READ|GENERIC_WRITE, 0, 0,
									OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	GetCommState(TScomHandle, &TSdcb);

	TSdcb.BaudRate = 115200;
	TSdcb.ByteSize = 8;
	TSdcb.Parity = NOPARITY;
	TSdcb.StopBits = ONESTOPBIT;

	SetCommState(TScomHandle, &TSdcb);

	TStimeouts.ReadIntervalTimeout = MAXDWORD;
	TStimeouts.ReadTotalTimeoutMultiplier = 0;
	TStimeouts.ReadTotalTimeoutConstant = 0;
	TStimeouts.WriteTotalTimeoutMultiplier = 0;
	TStimeouts.WriteTotalTimeoutConstant = 0;
	SetCommTimeouts(TScomHandle, &TStimeouts);

//Initialize decrementing flags

	Starting = 10;

//Initialize OSS Lock

	OSSLock = true;

//Initialize Units

	InitializeYard();
	InitializePort();
	InitializeLatham();
	InitializeDell();
	InitializeHyde();
	InitializeShore();
	InitializeKrulish();
	InitializeNassau();
	InitializeBank();
	InitializeCliveden();
	InitializeCliff();

	Invalidate = false;      //Images
	LocosAssigned = false;
	LocoListChange = false;
	DCCPowerOff = false;
	PSHours = 12;
	pSelectedLoco = &DummyLoco;
	SelectedLocoNo = "";
	RunTrains = false;
	ClientIDNo = 1000;
}
//End of PSRY constructor----------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------

//Button functions




void __fastcall TPSRY::StartClick(TObject *Sender)
{
	TestModeOn->Enabled = false;
	TestModeOff->Enabled = false;
	Stop->Enabled = true;
	Stop2->Enabled = true;
	Start->Enabled = false;
	Train->ReadOnly = false;
	RunTrains = false;
	NumAborts = 0;
	Aborts->Caption = "0";
}
//---------------------------------------------------------------------------
void __fastcall TPSRY::StopClick(TObject *Sender)
{
    CheckBoxes->Visible = false;
	TestModeOn->Enabled = true;
	TestModeOff->Enabled = true;
	TestModeOff->Checked = true;
	Stop->Enabled = false;
	Start->Enabled = true;
	Start2->Enabled = true;
	Train->ReadOnly = true;
	Aborts->Caption = "ST";
	Starting = 8;
}
//----------------------------------------------------------------------------
void __fastcall TPSRY::DataClick(TObject *Sender)
{
	if(DataPanel->Visible)
		DataPanel->Visible = false;
	else
		DataPanel->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TPSRY::ImageLaKrMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y)
{
	LaMDn(Button, X, Y);
}
//---------------------------------------------------------------------------
void TPSRY::LaMDn(TMouseButton Button, int X, int Y) //called from here or remote
{
	Screen = &LaKr;
	int DX = X - LaKr.DiaXOrigin;
	int DY = Y - LaKr.DiaYOrigin;

	LaKr.MouseX = DX;
	LaKr.MouseY = DY;
	LaKr.MouseCol = (DX - DX%HtWd)/HtWd;
	LaKr.MouseRow = (DY - DY%HtWd)/HtWd;
	Col->Text = LaKr.MouseCol;
	Row->Text = LaKr.MouseRow;

	if(Button == mbLeft)
	{
		if(Y > 380)
			USSMouseDown(X, Y);         // in USS levers
		else
			LaKr.MouseLeft = true;
	}
	if(Button == mbRight)
		LaKr.MouseRight = true;
}
//---------------------------------------------------------------------------
void __fastcall TPSRY::ImageLaKrMouseUp(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y)
{
	if(LaKr.ButtonDown)
	{
		LaKr.ButtonDown = false;
		Screen = &LaKr;
		USSMouseUp();
	}
}
//---------------------------------------------------------------------------
void __fastcall TPSRY::ImageNaCfMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y)
{
	NaMDn(Button, X, Y);
}
//---------------------------------------------------------------------------
void TPSRY::NaMDn(TMouseButton Button, int X, int Y) //called from here or remote
{
	Screen = &NaCf;

	int DX = X - NaCf.DiaXOrigin;         //corrects for offset of tile array
	int DY = Y - NaCf.DiaYOrigin;

	NaCf.MouseX = DX;
	NaCf.MouseY = DY;
	NaCf.MouseCol = (DX - DX%HtWd)/HtWd;
	NaCf.MouseRow = (DY - DY%HtWd)/HtWd;
	Col->Text = NaCf.MouseCol;
	Row->Text = NaCf.MouseRow;

	if(Button == mbLeft)
	{
		if(Y > 380 && X < 1840)        //area of USS levers
			USSMouseDown(X, Y);
		else
			NaCf.MouseLeft = true;
	}
	if(Button == mbRight)
		NaCf.MouseRight = true;
}
//---------------------------------------------------------------------------
void __fastcall TPSRY::ImageNaCfMouseUp(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y)
{
	if(NaCf.ButtonDown)
	{
		NaCf.ButtonDown = false;
		Screen = &NaCf;
		USSMouseUp();
	}
}
//---------------------------------------------------------------------------
void __fastcall TPSRY::ImageHyYdPtMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y)
{
	HyMDn(Button, X, Y);
}
//---------------------------------------------------------------------------

void TPSRY::HyMDn(TMouseButton Button, int X, int Y)
//can be called by clicks here or on remote screen
{
	Screen == &HyYdPt;
	int DX = X - HyYdPt.DiaXOrigin;
	int DY = Y - HyYdPt.DiaYOrigin;

	HyYdPt.MouseX = DX;
	HyYdPt.MouseY = DY;
	HyYdPt.MouseCol = (DX-DX%HtWd)/HtWd;
	HyYdPt.MouseRow = (DY-DY%HtWd)/HtWd;
	Col->Text = HyYdPt.MouseCol;
	Row->Text = HyYdPt.MouseRow;

	if(Button == mbLeft)
		HyYdPt.MouseLeft = true;
	if(Button == mbRight)
		HyYdPt.MouseRight = true;
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::ImageHyYdPtMouseUp(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y)
{
	if(HyYdPt.ButtonDown)
	{
		HyYdPt.ButtonDown = false;
		Screen = &HyYdPt;
		USSMouseUp();
	}
}
//---------------------------------------------------------------------------
void __fastcall TPSRY::TrainClick(TObject *Sender)
{
	Train->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TPSRY::LocoBlockListClick(TObject *Sender)
{
	String Line = LocoBlockList->Items->Strings[LocoBlockList->ItemIndex];
	String Block = Line.SubString(1, 5).Trim();
	BLOCK* pBlk = GetBlkPtr(Block);
	SetLoco(pBlk->BlkID);           //Set block list & selected loco to loco
	SelectedLocoNo = pBlk->Loco;
	RemDisSelectLocoMessage(pBlk);
}
//---------------------------------------------------------------------------
void __fastcall TPSRY::FormClose(TObject *Sender, TCloseAction &Action)
{
	RemoteDisplaySocket->Active = false;
	RemoteDispatcherSocket->Active = false;
	RemoteThrottleSocket->Active = false;
	if(LocoListChange &&!InTestMode)
	{
		int A = Application->MessageBox(L"Save changes to locos?", L"Pacific Southern", MB_YESNOCANCEL);
		if(A == 6)
		{
			LocoBlockList->Items->SaveToFile("C:/DispatcherTextFiles/LocoBlockList.txt");
			StopClick(this);
			CloseHandle(RRcomHandle);
			CloseHandle(DCCcomHandle);
		}
		else if(A == 7)
		{
			StopClick(this);
			CloseHandle(RRcomHandle);
			CloseHandle(DCCcomHandle);
		}
		else if(A == 2)
			Action = caNone;
	}
	if(IDListA->Checked)
		CurrentIDs->Text = "IDListA";
	else if(IDListB->Checked)
		CurrentIDs->Text = "IDListB";
	else if(IDListC->Checked)
		CurrentIDs->Text = "IDListC";
	CurrentIDs->Lines->SaveToFile("C:/DispatcherTextFiles/CurrentIDs.txt");
 //	TestBuffer->Lines->SaveToFile("C:/DispatcherTextFiles/TesLines.txt");
}
//---------------------------------------------------------------------------
void __fastcall TPSRY::OSSLockOnClick(TObject *Sender)
{
	OSSLock = true;
	MessageToRemDis("OSLOn", "True");
}
//---------------------------------------------------------------------------
void __fastcall TPSRY::OSSLockOffClick(TObject *Sender)
{
	OSSLock = false;
	MessageToRemDis("OSLOff", "True");
}
//---------------------------------------------------------------------------
void __fastcall TPSRY::BkClOnClick(TObject *Sender)
{
	MessageToRemDis("BkClOn", "True");
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::BkClOffClick(TObject *Sender)
{
	MessageToRemDis("BkClOff", "True");
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::Start2Click(TObject *Sender)
{
	StartClick(this);
}
//---------------------------------------------------------------------------
void __fastcall TPSRY::RemoteDisplaySocketClientConnect(TObject *Sender,
	  TCustomWinSocket *Socket)
{
	NewRemote = true;    //New remote has connected
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::RemoteDisplaySocketClientRead(TObject *Sender,
	  TCustomWinSocket *Socket)

//Used when train ID assigned to block from remote

{
	String Type;
	String ImageName;
	String Message = "";

	SCREEN* TempScreen = Screen;
	Message = Socket->ReceiveText();
	Type = Message.SubString(1, 8).TrimRight();
	ImageName = Message.SubString(10, 8).TrimRight();
	if(ImageName == "HyYdPt")
		Screen = &HyYdPt;    //Set pointer to image
	else if(ImageName == "LaKr")
		Screen = &LaKr;
	else
		Screen = &NaCf;
	Screen->MouseCol = StrToInt(Message.SubString(20, 4).TrimRight());
	Screen->MouseRow = StrToInt(Message.SubString(25, 4 ).TrimRight());
	if(Type == "TrainID")
	{
		Screen->RemoteMouseLeft = true;
		RemoteTrain = Message.SubString(30,6).TrimRight();
	}
	else if(Type == "RtClick")
		Screen->RemoteMouseRight = true;
	else if(Type == "Refresh")
		RefreshScreenClick(this);
	Screen = TempScreen;
}
//---------------------------------------------------------------------------
void __fastcall TPSRY::RemoteDispatcherSocketClientConnect(TObject *Sender, TCustomWinSocket *Socket)
{
	if(RemDisOn)                         //handshake
		MessageToRemDis("YYYY", "");     //kills second attempt to connect
	else
	{
		MessageToRemDis("XXXX", "");
		NewRemDis = true;    //Remote dispatcher has connected
	}
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::RemoteDispatcherSocketClientRead(TObject *Sender, TCustomWinSocket *Socket)

{
	String Type;
	String Param;
	String Message = "";
	int XCoord, YCoord;

	SCREEN* TempScreen = Screen;

	Message = Socket->ReceiveText();
	Type = Message.SubString(1, 8).TrimRight();
	Param = Message.SubString(10, 8).TrimRight();
	if(Param == "HyYdPt")
		Screen = &HyYdPt;    //Set pointer to image
	else if(Param == "LaKr")
		Screen = &LaKr;
	else
		Screen = &NaCf;
	XCoord = StrToInt(Message.SubString(20, 4).TrimRight());     //Col and Row for
	YCoord = StrToInt(Message.SubString(25, 4).TrimRight());
	if(Type == "rdID")
		RemoteTrain = Message.SubString(30, 6).TrimRight();
	else if(Type == "rdLoco")
	{
		RemoteLoco = Message.SubString(30, 4).TrimRight();
		RemoteLocoDir = Message.SubString(34, 3).TrimRight();
	}
	if(Type == "rdLClk" && Param == "HyYdPt")     //left click from remote dispatcher
		HyMDn(mbLeft, XCoord, YCoord);                      //XCoord and YCoord are X and Y
	else if(Type == "rdLClk" && Param == "LaKr")
		LaMDn(mbLeft, XCoord, YCoord);
	else if(Type == "rdLClk" && Param == "NaCf")
		NaMDn(mbLeft, XCoord, YCoord);

	else if(Type == "rdID" && Param == "HyYdPt")     //Train ID from remote dispatcher
		HyMDn(mbLeft, XCoord, YCoord);                   //XCoord and YCoord are Col and Row
	else if(Type == "rdID" && Param == "LaKr")
		LaMDn(mbLeft, XCoord, YCoord);
	else if(Type == "rdID" && Param == "NaCf")
		NaMDn(mbLeft, XCoord, YCoord);

	else if(Type == "rdLoco" && Param == "HyYdPt")     //Loco ID from remote dispatcher
		HyMDn(mbLeft, XCoord, YCoord);                   //XCoord and YCoord are Col and Row
	else if(Type == "rdLoco" && Param == "LaKr")
		LaMDn(mbLeft, XCoord, YCoord);
	else if(Type == "rdLoco" && Param == "NaCf")
		NaMDn(mbLeft, XCoord, YCoord);

	else if(Type == "rdRClk" && Param == "HyYdPt")     //Right click from remote dispatcher
		HyMDn(mbRight, XCoord, YCoord);                    //XCoord and YCoord are Col and Row
	else if(Type == "rdRClk" && Param == "LaKr")
		LaMDn(mbRight, XCoord, YCoord);
	else if(Type == "rdRClk" && Param == "NaCf")
		NaMDn(mbRight, XCoord, YCoord);
	else if(Type == "MouseUp")                          //Mouse up for buttons
	{
		if(HyYdPt.ButtonDown)
		{
			Screen = &HyYdPt;
			USSMouseUp();
		}
		else if(LaKr.ButtonDown)
		{
			Screen = &LaKr;
			USSMouseUp();
		}
		else if(NaCf.ButtonDown)
		{
			Screen = &NaCf;
			USSMouseUp();
		}
	}
	else if(Type == "LoadIDs")                      //Train IDs
		LoadIDsClick(this);
	else if(Type == "ClearIDs")
		ClearIDsClick(this);
	else if(Type == "SaveIDs")
		SaveIDsClick(this);

	else if(Type == "DeleteID")
		DeleteIDClick(this);
	else if(Type == "DelLoco")
	{
		RemDisDelete = true;
		DeleteButtonClick(this);
	}
	else if(Type == "CfmDel")                      //selected loco
        DeleteLoco();
	else if(Type == "ATCOn")
		ATCBtnClick(this);
	else if(Type == "cbActive")                    //active list
		CBActive->Checked = StrToBool(Param);
	else if(Type == "cbATC")
		CBATC->Checked = StrToBool(Param);
	else if(Type == "cbRTC")
		cbRTC->Checked = StrToBool(Param);
	else if(Type == "ShowLst")
	{
		if(Param == "False")
			ActiveList->Visible = false;
		else if(Param == "True")
		{
			ActiveList->Visible = true;
			UpdateActiveList();
		}
	}
	else if(Type == "KillATC")                      //ATC
		KillATCClick(this);
	else if(Type == "StStp")
		StartStopButtonClick(this);
	else if(Type == "ATCDir")
		DirClick(this);
	else if(Type == "COffBtn")
	   OffBtnClick(this);

	else if(Type == "HdLght")
		HeadlightClick(this);
	else if(Type == "HornDn")
	{
		pSelectedLoco->FTwo = true;
		TransmitFunction(pSelectedLoco);
	}
	else if(Type == "HornUp")
	{
		pSelectedLoco->FTwo = false;
		TransmitFunction(pSelectedLoco);
	}
	else if(Type == "MonOn")
		MonitorBtnClick(this);
	else if(Type == "ATCOn")
		ATCBtnClick(this);
	else if(Type == "OffBtn")
		OffBtnClick(this);

	else if(Type == "DisCtrl")                      //Signals 4 at Latham
		DispatcherControl->Checked = true;
	else if(Type == "PtCtrl")
		PortControl->Checked = true;
	else if(Type == "NaAll")                       //Nassau control
		RBNassau->Checked = true;
	else if(Type == "DMain")
		RBNDispatcherMain->Checked = true;
	else if(Type == "DAll")
		RBNDispatcherAll->Checked = true;
	else if(Type == "HyFltOn")                     //Hyde fleet
		HydeFleetOn->Checked = StrToBool(Param);
	else if(Type == "OSLOff")
		OSSLockOff->Checked = true;                //OS lock
	else if(Type == "OSLOn")
		OSSLockOn->Checked = true;
	else if(Type == "Cliff")                       //Cliff control
		RBCliff->Checked = true;
	else if(Type == "DBaCl")
		RBDispatcherBkCl->Checked = true;
	else if(Type == "DBaClCf")
		RBDispatcherAll->Checked = true;
	else if(Type == "BkClOn")                     //Cliff auto routes
		BkClOn->Checked = StrToBool(Param);
	else if(Type == "BkClOff")
		BkClOff->Checked = StrToBool(Param);
	else if(Type == "C31Incl")
        C31Incl->Checked = StrToBool(Param);
	else if(Type == "rbYard")                       //Yard control
		RBYard->Checked = true;
	else if(Type == "rbYDis")
		RBYDispatcher->Checked = true;
	else if(Type == "YdFltOn")                      //Fleets
		YardFleetOn->Checked = StrToBool(Param);
	else if(Type == "PtFltOn")
		PortFleetOn->Checked = StrToBool(Param);
	else if(Type == "CfFltOn")
		CliffFleetOn->Checked = StrToBool(Param);
	else if(Type == "HyOn")
		HyInOn->Checked = StrToBool(Param);         //Hyde auto routing
	else if(Type == "HyOff")
		HyInOff->Checked = StrToBool(Param);
	else if(Type == "H30Incl")                       //Dell/Shore auto routing
		H30Incl->Checked = StrToBool(Param);
	else if(Type == "F11Incl")
		F11Incl->Checked = StrToBool(Param);
	else if(Type == "P32Incl")
		P32Incl->Checked = StrToBool(Param);
	else if(Type == "DSROn")
		DSROn->Checked = StrToBool(Param);
	else if(Type == "DSROff")
		DSROff->Checked = StrToBool(Param);         //Nassau auto routing
	else if(Type == "NaOn")
		NaOn->Checked = StrToBool(Param);
	else if(Type == "NaOff")
		NaOff->Checked = StrToBool(Param);
	else if(Type == "Reset")                        //reinitialize remote dispatcher
		InitializeRemDis();
	else if(Type == "IDListA")
		IDListA->Checked = StrToBool(Param);        //select ID list
	else if(Type == "IDListB")
		IDListB->Checked = StrToBool(Param);
	else if(Type == "IDListC")
		IDListC->Checked = StrToBool(Param);
	else if(Type == "Refresh")
		RefreshScreenClick(this);

	Screen = TempScreen;
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::RemoteThrottleSocketClientConnect(TObject *Sender, TCustomWinSocket *Socket)
{
	NewRemThrottle = true;
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::RemoteThrottleSocketClientRead(TObject *Sender, TCustomWinSocket *Socket)
{
	String InMessage = Socket->ReceiveText();
	String ClientID = InMessage.SubString(1, 9).TrimRight();
	String Name = InMessage.SubString(10, 9).TrimRight();
	String Type = InMessage.SubString(20, 9).TrimRight();
	String A = InMessage.SubString(30, 9).TrimRight();
	String B = InMessage.SubString(40, 9).TrimRight();

	if(ClientID == "XXXX")     //assign client ID
	{
		WriteThrottles("XXXX", "", "ID" + IntToStr(ClientIDNo), "");
		ClientIDNo++;
	}
	else if(Type == "Loco")            //A will be loco number
	{
		int N = LocoBlockList->GetCount();
		if(N > 0)
		{
			for(int i = 0; i < N; i++)
			{
				String Line = LocoBlockList->Items->Strings[i];
				String Loco = Line.SubString(6, 6).TrimRight();

				if(A == Loco)                         //loco is present
				{
					String Block = Line.SubString(1, 5).TrimRight();
					BLOCK* pBlk = GetBlkPtr(Block);
					if(!pBlk->pLoco->ATC && !pBlk->pLoco->RTC &!pBlk->pLoco->Mon)
					{
						RemoteThrottleConnect(pBlk, Name, ClientID);
						WriteThrottles(ClientID, "Connect", Block, pBlk->Train);
						break;
					}
				}
			}
			WriteThrottles(ClientID, "NoLoco", "", "");
		}
		else
			WriteThrottles(ClientID, "NoLoco", "", "");
	}
	else if(Type == "Speed")    //A is block ID, B is speed
	{
		BLOCK* pBlk = GetBlkPtr(A);
		pBlk->pLoco->RemoteSpeed = StrToInt(B);
	}
	else if(Type == "Dir")      //A is block ID, B is direction
	{
		BLOCK* pBlk = GetBlkPtr(A);
		pBlk->pLoco->RemoteDir = B;
		pBlk->DirTxt = B;
		if(B == "For")
			pBlk->pLoco->DCCDir = true;
		else
			pBlk->pLoco->DCCDir = false;
	}
	else if(Type == "Drop")     //A is block ID
	{
		BLOCK* pBlk = GetBlkPtr(A);
		RemoteThrottleDisconnect(pBlk);
	}
	else if(Type == "HornDn")
	{
		BLOCK* pBlk = GetBlkPtr(A);
		pBlk->pLoco->FTwo = true;
		TransmitFunction(pBlk->pLoco);
	}
	else if(Type == "HornUp")          //Horn and headlight
	{
		BLOCK* pBlk = GetBlkPtr(A);
		pBlk->pLoco->FTwo = false;
		TransmitFunction(pBlk->pLoco);

	}
	else if(Type == "HeadLt")
	{
		BLOCK* pBlk = GetBlkPtr(A);
		if(pBlk->pLoco->FZero)
			pBlk->pLoco->FZero = false;
		else
		pBlk->pLoco->FZero = true;
		TransmitFunction(pBlk->pLoco);
	}
	else if(Type == "Bell")
	{
		BLOCK* pBlk = GetBlkPtr(A);
		if(pBlk->pLoco->FOne)
			pBlk->pLoco->FOne = false;
		else
		pBlk->pLoco->FOne = true;
		TransmitFunction(pBlk->pLoco);
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------

//Main control loop triggered by CycleTimer

//----------------------------------------------------------------------------
void __fastcall TPSRY::CycleTimer(TObject *Sender)
{
	if(Stop->Enabled)
	{
		if(Starting > 0)              //Decrement starting flag
			Starting--;
		if(Starting == 2 && !LocosAssigned)
		{
			AssignLocos();         //Assign locos in locolist to blocks
			LocosAssigned = true;
		}
		if(Starting == 5)          //Initiate USS lever positions
		{
			HyYdPt.LeverInit = true;
			LaKr.LeverInit = true;
			NaCf.LeverInit = true;
		}
        if(Starting == 3)
		{
			HyYdPt.LeverInit = false;
			LaKr.LeverInit = false;
			NaCf.LeverInit = false;
		}
		if(Starting == 0)
			RunTrains = true;

		if(NumAborts < 500)      //Stop cycles if I/O aborts exceed 500
		{
			NumDisplays = RemoteDisplaySocket->Socket->ActiveConnections;
			NumThrottles = RemoteThrottleSocket->Socket->ActiveConnections;
			RemoteDisplays->Caption = NumDisplays; //Show number of remote displays
			RemoteThrottles->Caption = NumThrottles;    //Show number of remote throttles

			if(NumDisplays > 0)
				RemoteOn = true;
			else
				RemoteOn = false;
			if(RemoteDispatcherSocket->Socket->ActiveConnections > 0)
			{
				RemoteDispatcherOn->Visible = true;
				RemDisOn = true;
			}
			else
			{
				RemoteDispatcherOn->Visible = false;
				RemDisOn = false;
			}

			if(NewRemote)            //Initialize remotes & remote dispatcher
			{
				NewRemote = false;
				InitializeTiles = true;
			}
			if(NewRemDis)
			{
                NewRemDis = false;
				InitializeTiles = true;
				InitializeRemDis();
			}

			if(RunTrains)            //Run trains after starting sequence
				RailroadRunTrains();
			SetArrays();

			Screen = &HyYdPt;
			Hyde();
			Yard();
			Port();
        	UpdateImage(Screen);

			Screen = &LaKr;
			Latham();
			Dell();
			Shore();
			Krulish();
			UpdateImage(Screen);

			Screen = &NaCf;
			Nassau();
			Bank();
			Cliveden();
			Cliff();
			UpdateImage(Screen);

			Breakers();

			if(InitializeIDs)
				InitializeIDs = false;
			if(InitializeTiles)
			{
				InitializeTiles = false;
				InitializeIDs = true;
			}

			Flash = !Flash;       //fast flash cycle
			if(Flash)
			{
				SFlash = !SFlash;    //slow flash cycle
				if(PSClock->Enabled)
					DisplayTime();
			}

			if(!InTestMode)
				RailroadInOut();
			else
				Testing();

			UpdateData();
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------


//Function to load tile images into image list

void TPSRY::LoadTile(String Name)
{
	Tiles->FileLoad(rtBitmap,("../Bitmaps/BlackScreenTiles\\" + Name), clWhite);
}
//------------------------------------------------------------------------------

//Functions to load USS machine images

void TPSRY::LoadShortLevers(String Name)
{
	ShortLevers->FileLoad(rtBitmap, ("../Bitmaps/USSTiles\\" + Name), clWhite);
}
//------------------------------------------------------------------------------

void TPSRY::LoadLongLevers(String Name)
{
	LongLevers->FileLoad(rtBitmap, ("../Bitmaps/USSTiles\\" + Name), clWhite);
}
//------------------------------------------------------------------------------

void TPSRY::LoadUSSLamps(String Name)
{
	USSLamps->FileLoad(rtBitmap, ("../Bitmaps/USSTiles\\" + Name), clWhite);
}

//------------------------------------------------------------------------------

//Function to load cab signal images

void TPSRY::LoadCabSignals(String Name)
{
	CabSignals->FileLoad(rtBitmap,("../Bitmaps/BlackScreenTiles\\" + Name), clWhite);
}
//------------------------------------------------------------------------------

//Display-related functions

//Function to set work arrays in correspondence with source arrays

void TPSRY::SetArrays()
{
	int ptr;

	for(int j=0; j<Rows; j++)
	{
		for(int i=0; i<Cols; i++)
		{
			ptr = i*Rows + j;
			HyYdPt.Work[ptr] = HyYdPt.Source[ptr];
			LaKr.Work[ptr] = LaKr.Source[ptr];
			NaCf.Work[ptr] = NaCf.Source[ptr];
		}
	}
}
//Function to update image and display grid--------------------------------------

void TPSRY::UpdateImage(SCREEN* Screen)
{
	int X = Screen->DiaXOrigin;
	int Y = Screen->DiaYOrigin;

	int ptr;

	for (int j=0; j<Rows; j++)
	{
		for(int i=0; i<Cols; i++)              //Draw tiles
		{
			ptr = i*Rows + j;

			if(Screen->Work[ptr] != 0 && Screen->Refresh)       //Refresh diagrams and remotes
			{
				Screen->Display[ptr] = Screen->Work[ptr];
				Tiles->Draw(Screen->Image->Canvas, X, Y, Screen->Work[ptr], true);
				if(RemoteOn || RemDisOn)
					DrawRemotes("Tile",Screen->ImageName, X/HtWd, Y/HtWd, Screen->Work[ptr], "");
				Screen->Invalidate = true;
			}

			else if(Screen->Display[ptr] != Screen->Work[ptr])     //Redraw changes only
			{
				Screen->Display[ptr] = Screen->Work[ptr];
				Tiles->Draw(Screen->Image->Canvas, X, Y, Screen->Work[ptr], true);  //Draw tile on screen here
				if(!InitializeTiles && (RemoteOn || RemDisOn))
					DrawRemotes("Tile",Screen->ImageName, X/HtWd, Y/HtWd, Screen->Work[ptr], "");  //Draw tile on remotes
				Screen->Invalidate = true;
			}

			if(InitializeTiles && Screen->Display[ptr] != Screen->Source[ptr])
				DrawRemotes("Tile",Screen->ImageName, X/HtWd, Y/HtWd, Screen->Display[ptr], "");  //Initialize tile on remotes

			X += HtWd;
		}
		X = Screen->DiaXOrigin;
	Y += HtWd;
	}

	if(Screen->RefreshIDs)
		Screen->RefreshIDs = false;

	if(Screen->Refresh)
	{
		Screen->Refresh = false;
		Screen->RefreshIDs = true;
	}

	if(Screen->Invalidate && Screen->Image->Visible)
	{
		Screen->Image->Repaint();
		Screen->Invalidate = false;
	}
}
//Function to update data screen------------------------------------------------

void TPSRY::UpdateData(void)
{
	String Header = "\n\n Node         Aborts  Address              Data Out/Data In\n";
//	if(Display == HYYDPT)
	{
		DataBytesHyCf->Caption = Header + "\n" + HText + "\n" + YDText + "\n" +
			YSWText + "\n" + KAText + "\n" + EJText + "\n" + CJText + "\n" +
				PJText + "\n" + PAText + "\n" + PBText;                           //added text for YARDSW
	}

//	else if(Display == LAKR)
	{
		DataBytesLaKr->Caption = Header + "\n" + LAText + "\n" + CAText + "\n" +
			DLText + "\n" + MFText + "\n" + SHText + "\n" +
				HJctText + "\n" + KRText;
	}

//	else if(Display == NACF)
	{
		DataBytesNaCf->Caption = Header + "\n" + NWText + "\n" + NEText + "\n" +
			NXText + "\n" + BKText + "\n" + CVText + "\n" + GMText + "\n" +
				CFText + "\n" + SFText;
	}

	RouteStateText->Caption =  DWState + "\n" + DEState + "\n\n" +
		SWState + "\n" + SEState + "\n\n" + HWState + "\n" + HEState + "\n\n" +
			NWState + "\n" + NEState + "\n\n" + BCState;


}

//Packet functions-------------------------------------------------------------

//Create message for remote displays and store in buffer

void TPSRY::DrawRemotes(String Type, String ImageName, int Col, int Row, char Tile, String Train)
{
	String Message = AnsiString::StringOfChar(' ', 41);
	Message.Insert(Type, 1);
	Message.Insert(ImageName, 10);
	Message.Insert(Col, 20);
	Message.Insert(Row, 25);
	if(Type == "Tile")
		Message.Insert((int)Tile, 30);
	else
		Message.Insert(Train, 30);
	Message.Insert("##", 40);
	Message = Message.TrimRight();
	MessageBuffer->Lines->Add(Message);                  //send to remote displays
	RemDisMessageBuffer->Lines->Add(Message);            //send to remote dispatcher
}
//------------------------------------------------------------------------------

void TPSRY::InitializeRemDis()
{
	//Initialize loco list

	int Num = LocoList->GetCount();

	for(int i = 1; i < Num; i++)
	{
		String Loco = LocoList->Items->Strings[i];
		MessageToRemDis("Locos", Loco);
	}

	//Initialize top and bottom panels

	MessageToRemDis("OSLOn", BoolToStr(OSSLockOn->Checked));
	MessageToRemDis("OSLOff", BoolToStr(OSSLockOff->Checked));
	MessageToRemDis("cbActive", BoolToStr(CBActive->Checked));
	MessageToRemDis("cbATC", BoolToStr(CBATC->Checked));
	MessageToRemDis("cbRTC", BoolToStr(cbRTC->Checked));
	MessageToRemDis("DisCtrl", BoolToStr(DispatcherControl->Checked));
	MessageToRemDis("Sig4D", BoolToStr(DispatcherControl->Enabled));
	MessageToRemDis("PtCtrl", BoolToStr(PortControl->Checked));
	MessageToRemDis("Sig4P", BoolToStr(PortControl->Enabled));
	MessageToRemDis("NaAll", BoolToStr(RBNassau->Checked));
	MessageToRemDis("DMain", BoolToStr(RBNDispatcherMain->Checked));
	MessageToRemDis("DAll", BoolToStr(RBNDispatcherAll->Checked));
	MessageToRemDis("NaEn", BoolToStr(RBNassau->Enabled));              /////
	MessageToRemDis("NaMnEn", BoolToStr(RBNDispatcherMain->Enabled));
	MessageToRemDis("NaAllEn", BoolToStr(RBNDispatcherAll->Enabled));
	MessageToRemDis("HyFltOn", BoolToStr(HydeFleetOn->Checked));
	MessageToRemDis("Cliff", BoolToStr(RBCliff->Checked));
	MessageToRemDis("DBaCl", BoolToStr(RBDispatcherBkCl->Checked));
	MessageToRemDis("DBaClCf", BoolToStr(RBDispatcherAll->Checked));
	MessageToRemDis("rbYard", BoolToStr(RBYard->Checked));
	MessageToRemDis("rbYDis", BoolToStr(RBYDispatcher->Checked));
	MessageToRemDis("YdFltOn", BoolToStr(YardFleetOn->Checked));
	MessageToRemDis("PtFltOn", BoolToStr(PortFleetOn->Checked));
	MessageToRemDis("ClFltOn", BoolToStr(CliffFleetOn->Checked));
	MessageToRemDis("CfEn", BoolToStr(RBCliff->Enabled));
	MessageToRemDis("BaClEn", BoolToStr(RBDispatcherBkCl->Enabled));
	MessageToRemDis("AllEn", BoolToStr(RBDispatcherAll->Enabled));
	MessageToRemDis("BkClOn", BoolToStr(BkClOn->Checked));
	MessageToRemDis("BkClOff", BoolToStr(BkClOff->Checked));
	MessageToRemDis("C31En", BoolToStr(C31Incl->Enabled));
	MessageToRemDis("C31Incl", BoolToStr(C31Incl->Checked));
	MessageToRemDis("StSpCap", StartStopButton->Caption);
	MessageToRemDis("HdltCap", Headlight->Caption);
	MessageToRemDis("ATCVis", BoolToStr(ATCPanel->Visible));
	MessageToRemDis("KillVis", BoolToStr(KillATC->Visible));
	MessageToRemDis("TrkSpd", TrackSpeed->Text);
	MessageToRemDis("SigSpd", SigSpeed->Text);
	MessageToRemDis("HyInOn", BoolToStr(HyInOn->Checked));
	MessageToRemDis("HyInOff", BoolToStr(HyInOff->Checked));
	MessageToRemDis("DSROn", BoolToStr(DSROn->Checked));
	MessageToRemDis("DSROff", BoolToStr(DSROff->Checked));
	MessageToRemDis("H30Incl", BoolToStr(H30Incl->Checked));
	MessageToRemDis("F11Incl", BoolToStr(F11Incl->Checked));
	MessageToRemDis("P32Incl", BoolToStr(P32Incl->Checked));
	MessageToRemDis("H30En", BoolToStr(H30Incl->Enabled));
	MessageToRemDis("F11En", BoolToStr(F11Incl->Enabled));
	MessageToRemDis("DSROnE", BoolToStr(DSROn->Enabled));
	MessageToRemDis("NaOn", BoolToStr(NaOn->Checked));
	MessageToRemDis("NaOff", BoolToStr(NaOff->Checked));
	MessageToRemDis("IDListA", BoolToStr(IDListA->Checked));
	MessageToRemDis("IDListB", BoolToStr(IDListB->Checked));
	MessageToRemDis("IDListC", BoolToStr(IDListC->Checked));


	//Initialize USS machines

	SCREEN* TempScreen = Screen;
	Screen = &LaKr;
	for(int i = 0; i < 40; i++)
	{
		InitRemDisCol(&LaKr.USSCol[i]);
    }
	Screen = &NaCf;
	for(int i=0; i < 30; i++)
	{
		InitRemDisCol(&NaCf.USSCol[i]);
	}
	Screen = TempScreen;
}

//------------------------------------------------------------------------------
void TPSRY::MessageToRemDis(String Type, String Message)
{
	String M = AnsiString::StringOfChar(' ', 41);
	M.Insert(Type, 1);
	M.Insert(Message, 10);
	M.Insert("##", 40);
	M = M.TrimRight();
	RemDisMessageBuffer->Lines->Add(M);
}
//------------------------------------------------------------------------------

void TPSRY::RemDisSelectLocoMessage(BLOCK* pBlk)
{
	String Message = AnsiString::StringOfChar(' ', 41);
	Message.Insert("SelLoco", 1);
	Message.Insert(pBlk->Train, 10);
	Message.Insert(pBlk->Loco, 20);
	Message.Insert(pBlk->BlkID, 30);
	Message.Insert("##", 40);
	Message = Message.TrimRight();
	RemDisMessageBuffer->Lines->Add(Message);
	MessageToRemDis("CabSig", pBlk->Signal);
}

//------------------------------------------------------------------------------

void TPSRY::DrawRemoteUSS(String Type, String ImageName, int X, int Y, char Tile)
{
	String Message = AnsiString::StringOfChar(' ', 41);
	Message.Insert(Type, 1);
	Message.Insert(ImageName, 10);
	Message.Insert(X, 20);
	Message.Insert(Y, 25);
	Message.Insert((int)Tile, 30);
	Message.Insert("##", 40);
	Message = Message.TrimRight();
	RemDisMessageBuffer->Lines->Add(Message);           //send to remote dispatcher only
}

//------------------------------------------------------------------------------

void TPSRY::MessageToRemotes(String Type, String Message)
{
	String M = AnsiString::StringOfChar(' ', 41);
	M.Insert(Type, 1);
	M.Insert(Message, 10);
	M.Insert("##", 40);
	M = M.TrimRight();
	MessageBuffer->Lines->Add(M);
}
//------------------------------------------------------------------------------

void TPSRY::MessageToTrainTkr(String Type, String A, String B, String C, String D)
{
	String M = AnsiString::StringOfChar(' ', 41);
	M.Insert(Type, 1);
	M.Insert(A, 10);
	M.Insert(B, 18);
	M.Insert(C, 26);
	M.Insert(D, 34);
	M.Insert("##", 40);
	M = M.TrimRight();
	MessageBuffer->Lines->Add(M);
}
//------------------------------------------------------------------------------

//Send breaker messages to remotes and remote dispatcher

void TPSRY::RemoteBkrMessage(String BkrMessage)
{
	if(BkrMessage != LastBkrMessage)
	{
		LastBkrMessage = BkrMessage;
		MessageToRemotes("CktBkr", BkrMessage);
		MessageToRemDis("CktBkr", BkrMessage);
	}
}
//------------------------------------------------------------------------------

void TPSRY::WriteRemotes()
{
	int C = MessageBuffer->Lines->Count;
	int N = RemoteDisplaySocket->Socket->ActiveConnections;
	if(N > 0 && C > 0)
	{
		for(int i = 0; i < N; i++)    //send messages to N active clients
		{
			RemoteDisplaySocket->Socket->Connections[i]->SendText(MessageBuffer->Lines->Text);
		}
	}
	MessageBuffer->Clear();
}
//------------------------------------------------------------------------------


void TPSRY::WriteThrottles(String A, String B, String C, String D)
{
	String Message = AnsiString::StringOfChar(' ', 41);
	Message.Insert(A, 1);
	Message.Insert(B, 10);
	Message.Insert(C, 20);
	Message.Insert(D, 30);
	Message.Insert("##", 40);
	Message = Message.TrimRight();

	int N = RemoteThrottleSocket->Socket->ActiveConnections;
	if(N > 0)
	for (int i = 0; i < N; i++)     //send to N active throttles
	{
		RemoteThrottleSocket->Socket->Connections[i]->SendText(Message);
	}
}
//------------------------------------------------------------------------------

void TPSRY::WriteRemoteDispatcher()
{
	int C = RemDisMessageBuffer->Lines->Count;
	int N = RemoteDispatcherSocket->Socket->ActiveConnections;
	if(N > 0 && C > 0)
	{
		for(int i = 0; i < N; i++)    //send messages to N active clients
		{
			RemoteDispatcherSocket->Socket->Connections[i]->SendText(RemDisMessageBuffer->Lines->Text);
		}
	}
	RemDisMessageBuffer->Clear();
}
//------------------------------------------------------------------------------

//Auto routing

String TPSRY::GetDest(String Train, String Location)
{
	int N = EditRoutes->RouteList->Items->Count;
	String L, Dest, Loc, ID;

	for(int i = 0; i < N; i++)
	{
		L = EditRoutes->RouteList->Items->Strings[i];
		ID = L.SubString(1, 6).TrimRight();
		Loc = L.SubString(8, 12).TrimRight();
		if(Train == ID && Location == Loc)
		{
			Dest = L.SubString(25, 10).TrimRight();
			return Dest;
		}
	}
	return "None";
}
//------------------------------------------------------------------------------

//Railroad input/output


void TPSRY::RailroadInOut(void)
{
	YardInOut();          //YARD, YARDSW, KALE, EASTJCT, CORNELL
	PortInOut();          //PARSONS, PORTA, PORTB
	LathamInOut();        //LATHAM, CARLTON
	DellInOut();          //DELL, FOSS
	HydeInOut();          //HYDE
	ShoreInOut();         //SHORE, HYDEJCT
	KrulishInOut();       //KRULISH
	NassauInOut();        //NASSAUW, NASSAUNX, NASSAUE
	BankInOut();          //BANK
	ClivedenInOut();      //CLIVEDEN
	CliffInOut();         //GREENMTN, CLIFF, SHEFFIELD
}
//-----------------------------------------------------------------------------
//Packet to railroad

void TPSRY::SendPacket(int Address, int* NodeAborts, IOBYTE *In,
				  IOBYTE *Old, IOBYTE *Out, int Count, bool Swap)
{
	char TransData[15];
	int PCount;
	IOBYTE Temp;
	int NAborts = *NodeAborts;
	bool InOK;

//TransData is for bytes transmitted; OutData for bytes displayed.  If Swap
//is true, data is transmitted in reverse order so that connections can be
//made from top to bottom on I/O panels as written in the code

	TransData[0] = OutData[0] = Address;

	int j = Count;

	for (int i=0; i<Count; i++)
	{
		if(Swap)
		{
			Temp.bit.b0 = Out[i].bit.b7;
			Temp.bit.b1 = Out[i].bit.b6;
			Temp.bit.b2 = Out[i].bit.b5;
			Temp.bit.b3 = Out[i].bit.b4;
			Temp.bit.b4 = Out[i].bit.b3;
			Temp.bit.b5 = Out[i].bit.b2;
			Temp.bit.b6 = Out[i].bit.b1;
			Temp.bit.b7 = Out[i].bit.b0;
			OutData[i+1] = Temp.byte;
		}
		else
		{
			OutData[i+1] = Out[i].byte;
		}
		TransData[j] = Out[i].byte;
		j--;
	}
	PCount = Count;

	InOK = Send(&TransData[0], &InData[0], PCount);     //Send to railroad serial port

	if(InOK)
	{
		Match = true;
		if(Swap)
		{
			for(int i=0; i<Count; i++)
			{
				if(InData[i] == Old[i].byte)        //byte the same
				{
					Temp.byte = InData[i];
					In[i].bit.b0 = Temp.bit.b7;
					In[i].bit.b1 = Temp.bit.b6;
					In[i].bit.b2 = Temp.bit.b5;
					In[i].bit.b3 = Temp.bit.b4;
					In[i].bit.b4 = Temp.bit.b3;
					In[i].bit.b5 = Temp.bit.b2;
					In[i].bit.b6 = Temp.bit.b1;
					In[i].bit.b7 = Temp.bit.b0;
				}
				else                               //record change
					RecordChange(Address, i, Old[i].byte, InData[i]);

				Old[i].byte = InData[i];
			}
		}
		else
		{
			for(int i=0; i<Count; i++)
			{
				In[i].byte = InData[i];
			}
		}
	}
	if(!Match)
	{
		NumAborts++;
		Aborts->Caption = NumAborts;
		NAborts = *NodeAborts;
		NAborts++;
		*NodeAborts = NAborts;
	}

	TXText = "\t" + IntToStr(NAborts) + "\t" + Hex(OutData, 0, 1) + "\t" +
			Binary(OutData, 1, Count) + "\n";
	RXText = "\t\t\t\t" + Binary(InData, 0, Count) + "\n";
	if(Match)
		OutText = TXText + RXText + "\n";
	else
		OutText = TXText + "\t\t\t\t\t  No Response  \n";
}
//-----------------------------------------------------------------------------


bool TPSRY::Send(char * OutBuff, char * InBuff, unsigned Count)
{
	DWORD numWrite, numRead;

	PurgeComm(RRcomHandle, PURGE_RXCLEAR);
	WriteFile(RRcomHandle, OutBuff, Count+1, &numWrite, 0);

	for(int i = 0; i < 5; i++)
	{
		ReadFile(RRcomHandle, InBuff, Count, &numRead, 0);
		if(numRead == Count)
			return true;
		else
			Sleep(1);
	}
	return false;
}

//-----------------------------------------------------------------------------

//Conversion function to display hex characters

String TPSRY::Hex(char InStr[],int Fst, int Num)
{
	String Buffer = "";
	int tmp;
	for(int i=Fst; i<Fst + Num; i++)
	{
		tmp = (InStr[i]>>4) & 0x0f;
		if(tmp>=0xa && tmp<=0xf)
			tmp = (tmp - 9) | 0x40;
		else
			tmp = tmp | 0x30;
		Buffer = Buffer + char(tmp);
		tmp = InStr[i] & 0x0f;
		if(tmp>=0xa && tmp<=0xf)
			tmp = (tmp - 9) | 0x40;
		else
			tmp = tmp | 0x30;
		Buffer = Buffer + char(tmp) + ' ';
	}
	return Buffer.TrimRight();
}
//---------------------------------------------------------------------------

//Conversion function to display binary characters ----------------------------

String TPSRY::Binary(char InStr[], int Fst, int Num)    //String of binary characters
{
	String Buffer = "";

	for(int j=Fst; j<Fst + Num; j++)
	{
		Buffer = Buffer + BinaryByte(InStr[j]);
		Buffer = Buffer + ' ';
	}
	return Buffer.TrimRight();
}
//---------------------------------------------------------------------------

String TPSRY::BinaryByte(char Byte)                    //Single binary character
{
 	IOBYTE Temp;
	String Buffer = "";

		Temp.byte = Byte;
		Buffer = Buffer + char(Temp.bit.b7 | 0x30);
		Buffer = Buffer + char(Temp.bit.b6 | 0x30);
		Buffer = Buffer + char(Temp.bit.b5 | 0x30);
		Buffer = Buffer + char(Temp.bit.b4 | 0x30);
		Buffer = Buffer + char(Temp.bit.b3 | 0x30);
		Buffer = Buffer + char(Temp.bit.b2 | 0x30);
		Buffer = Buffer + char(Temp.bit.b1 | 0x30);
		Buffer = Buffer + char(Temp.bit.b0 | 0x30);

	return Buffer.TrimRight();
}
//---------------------------------------------------------------------------

String TPSRY::BoolToStr(bool X)
{
	if(X)
		return "True";
	else
		return "False";
}
//---------------------------------------------------------------------------
bool TPSRY::StrToBool(String X)
{
	if(X == "True")
		return true;
	else if(X == "False")
		return false;
}


//------------------------------------------------------------------------------
//------------------------USS INTERLOCKING BOARD--------------------------------
//------------------------------------------------------------------------------
//Functions for USS column

void TPSRY::USSColumn(COLUMN* pCol)
{
	if(pCol->Enabled)
	{
		USSSwitches(pCol);
	}
	USSIndicators(pCol, false);
	Screen->Invalidate = true;
}
//------------------------------------------------------------------------------

//Initialize remote dispatcher USS column

void TPSRY::InitRemDisCol(COLUMN* pCol)
{
	if(pCol->Enabled)
	{
		if(pCol->pSw && pCol->pSw->R)
			USSSwReverse(pCol);
		if(pCol->pSigL && pCol->pSigL->R)
			USSSigRight(pCol);
		else if(pCol->pSigL && pCol->pSigL->L)
			USSSigLeft(pCol);
		if(pCol->pFltL && pCol->pFltL->R)
			USSFltReverse(pCol);
	}
	USSIndicators(pCol, true);

}
//------------------------------------------------------------------------------

//Function for mouse down on USS machines

void TPSRY::USSMouseDown(int MouseX, int MouseY)
{
	int i, X, Shift;
	COLUMN *pCol;
	LeverX = Screen->XOrigin;
	LeverY = Screen->YOrigin;

	//Find column pointer

	if(MouseY < LeverY + 70)
	{
		Shift = LeverX;
		i = (MouseX - Shift - (MouseX - Shift)%64)/64;	//get column pointer
		pCol = Screen->USSCol[i].pCol;
		X = Screen->USSCol[i].XOR;
	}
	else
	{
		Shift = LeverX + 32;
		i = (MouseX - Shift - (MouseX - Shift)%64)/64;	//get column pointer
		pCol = Screen->USSCol[i].pCol;
		X = Screen->USSCol[i].XOR + 32;
	}

	if(pCol->Enabled)
	{
		if(pCol->pSw) 						//Switch or lock lever
		{
			if(MouseY > LeverY && MouseY < LeverY + 50)
			{
				if(pCol->pSw->R && MouseX > X && MouseX < X + 50)
					USSSwNormal(pCol);		//Switch lever to normal
				else if(pCol->pSw->N && MouseX > X + 10 && MouseX < X + 61)
					USSSwReverse(pCol);	//Switch lever to reverse
			}
		}

		if(pCol->pSigL)                //Signal lever
		{
			if(MouseY > LeverY + 84 && MouseY < LeverY + 134)
			{
				if(pCol->pSigL->N && MouseX > X && MouseX < X + 30)
					USSSigLeft(pCol);		//Signal lever to left
				else if(pCol->pSigL->L && MouseX > X + 15 && MouseX < X + 60 ||
						pCol->pSigL->R && MouseX > X && MouseX < X + 50)
					USSSigNormal(pCol);	//Signal lever normal
				else if(pCol->pSigL->N && MouseX > X + 34 && MouseX < X + 60)
					USSSigRight(pCol);	//Signal lever to right
			}

			else if(pCol->pSigL->CButton && MouseX > X + 22 && MouseX < X + 42 &&
					MouseY > LeverY + 130 && MouseY < LeverY + 150)
			{
				USSLamps->Draw(pCol->pImage->Canvas, X + 23, LeverY + 131, 5, true);	//Button down
				DrawRemoteUSS("USSlmp", Screen->ImageName, X + 23, LeverY + 131, 5);  //Draw on remote dispatcher
				pCol->pSigL->Callon = true;
				ButtonCol = pCol;
				Screen->ButtonDown = true;
			}
		}
		if(pCol->pFltL)      //Fleet lever
		{
			if(MouseY > LeverY + 84 && MouseY < LeverY + 134)
			{
				if(pCol->pFltL->R && MouseX > X && MouseX < X + 50)
					USSFltNormal(pCol);
				else if(pCol->pFltL->N && MouseX > X + 10 && MouseX < X + 60)
					USSFltReverse(pCol);
			}
		}
	}
}
//------------------------------------------------------------------------------

//Function for switch lever normal

void TPSRY::USSSwNormal(COLUMN* pCol)
{
 	if(!pCol->pSw->L)
	{
		int X = pCol->XOR;

		ShortLevers->Draw(pCol->pImage->Canvas, X + 10, LeverY + 23, 3, true); //Lever to normal
		DrawRemoteUSS("USSsh", Screen->ImageName, X + 10, LeverY + 23, 3);  //Draw on remote dispatcher
		if(pCol->Long)
		{
			LongLevers->Draw(pCol->pImage->Canvas, X + 3, LeverY + 7, 3, true);
			DrawRemoteUSS("USSlg", Screen->ImageName, X + 3, LeverY + 7, 3);
		}
		pCol->pSw->N = true;
		pCol->pSw->R = false;
	}
}
//------------------------------------------------------------------------------

//Function for switch lever reverse

void TPSRY::USSSwReverse(COLUMN* pCol)
{
	if(!pCol->pSw->L)
	{
		int X = pCol->XOR;

		ShortLevers->Draw(pCol->pImage->Canvas, X + 10, LeverY + 23, 4, true); //Lever to reverse
		DrawRemoteUSS("USSsh",  Screen->ImageName, X + 10, LeverY + 23, 4);  //Draw on remote dispatcher
		if(pCol->Long)
		{
			LongLevers->Draw(pCol->pImage->Canvas, X + 3, LeverY + 7, 4, true);
			DrawRemoteUSS("USSlg",  Screen->ImageName, X + 3, LeverY + 7, 4);
		}
		pCol->pSw->N = false;
		pCol->pSw->R = true;
	}
}
//------------------------------------------------------------------------------

//Function for signal lever left

void TPSRY::USSSigLeft(COLUMN* pCol)
{
	if(!pCol->pSigL->LockL)
	{
	int X = pCol->XOR + 32;

	ShortLevers->Draw(pCol->pImage->Canvas, X + 10, LeverY + 72, 0, true); //Lever to left
	DrawRemoteUSS("USSsh",  Screen->ImageName, X + 10, LeverY + 72, 0);  //Draw on remote dispatcher
	if(pCol->Long)
	{
		LongLevers->Draw(pCol->pImage->Canvas, X + 3, LeverY + 91, 0, true);
		DrawRemoteUSS("USSlg",  Screen->ImageName, X + 3, LeverY + 91, 0);  //Draw on remote dispatcher
	}
  	pCol->pSigL->L = true;
  	pCol->pSigL->N = false;
	pCol->pSigL->R = false;
	}
}
//------------------------------------------------------------------------------

//Function for signal lever normal

void TPSRY::USSSigNormal(COLUMN* pCol)
{
	if(!pCol->pSigL->LockN)
	{
	int X = pCol->XOR + 32;

	ShortLevers->Draw(pCol->pImage->Canvas, X + 10, LeverY + 72, 1, true); //Lever normal
	DrawRemoteUSS("USSsh",  Screen->ImageName, X + 10, LeverY + 72, 1);  //Draw on remote dispatcher
  	if(pCol->Long)
  	{
		LongLevers->Draw(pCol->pImage->Canvas, X + 3, LeverY + 91, 1, true);
		DrawRemoteUSS("USSlg",  Screen->ImageName, X + 3, LeverY + 91, 1);  //Draw on remote dispatcher
	}
	pCol->pSigL->L = false;
  	pCol->pSigL->N = true;
	pCol->pSigL->R = false;
	}
}
//------------------------------------------------------------------------------

//Function for signal lever right

void TPSRY::USSSigRight(COLUMN* pCol)
{
	if(!pCol->pSigL->LockR)
	{
	int X = pCol->XOR + 32;

	ShortLevers->Draw(pCol->pImage->Canvas, X + 10, LeverY + 72, 2, true); //Lever to right
	DrawRemoteUSS("USSsh",  Screen->ImageName, X + 10, LeverY + 72, 2);  //Draw on remote dispatcher
	if(pCol->Long)
	{
		LongLevers->Draw(pCol->pImage->Canvas, X + 3, LeverY + 91, 2, true);
		DrawRemoteUSS("USSlg",  Screen->ImageName, X + 3, LeverY + 91, 2);  //Draw on remote dispatcher
	}
	pCol->pSigL->L = false;
	pCol->pSigL->N = false;
	pCol->pSigL->R = true;
	}
}
//------------------------------------------------------------------------------

//Function for fleet lever normal

void TPSRY::USSFltNormal(COLUMN* pCol)
{
	int X = pCol->XOR + 32;

	ShortLevers->Draw(pCol->pImage->Canvas, X + 10, LeverY + 72, 0, true); //Lever to normal
	DrawRemoteUSS("USSsh",  Screen->ImageName, X + 10, LeverY + 72, 0);  //Draw on remote dispatcher
	if(pCol->Long)
 	{
		LongLevers->Draw(pCol->pImage->Canvas, X + 3, LeverY + 91, 0, true);
		DrawRemoteUSS("USSlg",  Screen->ImageName, X + 3, LeverY + 91, 0);  //Draw on remote dispatcher
	}
  	pCol->pFltL->N = true;
  	pCol->pFltL->R = false;
}
//------------------------------------------------------------------------------

//Function for fleet lever reversed

void TPSRY::USSFltReverse(COLUMN* pCol)
{
	int X = pCol->XOR + 32;
	if(!pCol->pFltL->L)
	{
		ShortLevers->Draw(pCol->pImage->Canvas, X + 10, LeverY + 72, 2, true); //Lever to reverse
		DrawRemoteUSS("USSsh",  Screen->ImageName, X + 10, LeverY + 72, 2);  //Draw on remote dispatcher
		if(pCol->Long)
		{
			LongLevers->Draw(pCol->pImage->Canvas, X + 3, LeverY + 91, 2, true);
			DrawRemoteUSS("USSlg",  Screen->ImageName, X + 3, LeverY + 91, 2);  //Draw on remote dispatcher
		}
		pCol->pFltL->N = false;
		pCol->pFltL->R = true;
	}
}
//------------------------------------------------------------------------------

//Function for mouse up

void TPSRY::USSMouseUp(void)
{
	Screen->ButtonDown = false;
	if(ButtonCol->Enabled)
	{
		int X = ButtonCol->XOR + 32;

		USSLamps->Draw(Screen->Image->Canvas, X + 23, LeverY + 131, 4, true);	//Button up
		DrawRemoteUSS("USSlmp",  Screen->ImageName, X + 23, LeverY + 131, 4);  //Draw on remote dispatcher
		ButtonCol->pSigL->Callon = false;
		Screen->Invalidate = true;
	}
}
//------------------------------------------------------------------------------

//Indicator Lights

void TPSRY::USSIndicators(COLUMN *pCol, bool Init)
{
	int X = pCol->XOR;
	int Y = pCol->YOR;
	char Indicator, IndicatorL, IndicatorR;

//Switch Lever

	if(pCol->pSw && !pCol->pSw->Hand)
	{
		if(!pCol->pSw->L && pCol->Enabled)
			Indicator = 1;      //released
		else
			Indicator = 0;      //locked
		if(pCol->pSw->Indicator != Indicator || Init)
		{
			USSLamps->Draw(Screen->Image->Canvas, X + 23, Y + 177, Indicator, true);
			DrawRemoteUSS("USSlmp", Screen->ImageName, X + 23, Y + 177, Indicator);  //Draw on remote dispatcher
			pCol->pSw->Indicator = Indicator;
		}
		if(pCol->pSw->N && !pCol->pSw->NI ||
				pCol->pSw->R && !pCol->pSw->RI)
			pCol->pSw->Out = true; 	 //Lever and indication out of correspondence
		else
			pCol->pSw->Out = false;
	}

//Hand-switch lock lever

	if(pCol->pSw && pCol->pSw->Hand)
	{
		if(!pCol->pSw->L && pCol->Enabled)
			Indicator = 6;      //released
		else
			Indicator = 0;      //locked
		if(pCol->pSw->Indicator != Indicator || Init)
		{
			USSLamps->Draw(Screen->Image->Canvas, X + 23, Y + 177, Indicator, true);
			DrawRemoteUSS("USSlmp", Screen->ImageName, X + 23, Y + 177, Indicator);  //Draw on remote dispatcher
			pCol->pSw->Indicator = Indicator;
		}
	}

//Signal lever

	if(pCol->pSigL)
	{
		if(!pCol->pSigL->LockL && pCol->pSigL->N && pCol->Enabled)       	//Left indicator
			IndicatorL = 2;
		else
			IndicatorL = 0;
		if(pCol->pSigL->IndicatorL != IndicatorL || Init)
		{
			USSLamps->Draw(Screen->Image->Canvas, X + 55, Y + 158, IndicatorL, true);
			DrawRemoteUSS("USSlmp", Screen->ImageName, X + 55, Y + 158, IndicatorL);  //Draw on remote dispatcher
			pCol->pSigL->IndicatorL = IndicatorL;
		}
		if(!pCol->pSigL->LockR && pCol->pSigL->N && pCol->Enabled)         //Right indicator
			IndicatorR = 3;
		else
			IndicatorR = 0;
		if(pCol->pSigL->IndicatorR != IndicatorR || Init)
		{
			USSLamps->Draw(Screen->Image->Canvas, X + 55, Y + 177, IndicatorR, true);
			DrawRemoteUSS("USSlmp", Screen->ImageName, X + 55, Y + 177, IndicatorR);  //Draw on remote dispatcher
			pCol->pSigL->IndicatorR = IndicatorR;
		}
	}

	//Fleet lever

	if(pCol->pFltL)
	{
		if(!pCol->pFltL->L && pCol->Enabled)
			Indicator = 7;      //released
		else
			Indicator = 0;      //locked
		if(pCol->pFltL->Indicator != Indicator || Init)
		{
			USSLamps->Draw(Screen->Image->Canvas, X + 55, Y + 177, Indicator, true);
			DrawRemoteUSS("USSlmp", Screen->ImageName, X + 55, Y + 177, Indicator);  //Draw on remote dispatcher
			pCol->pFltL->Indicator = Indicator;
		}
	}
}
 //-----------------------------------------------------------------------------

 //Switches

void TPSRY::USSSwitches(COLUMN* pCol)  //Interlocked switch control
{
	int X = pCol->XOR;
	int Y = pCol->YOR;

	if(pCol->pSw && !pCol->pSw->Hand)
	{
		if(Screen->LeverInit)	//Initialize lever position
		{
			if(pCol->pSw->RI)
			{
				ShortLevers->Draw(Screen->Image->Canvas, X + 10, Y + 23, 4, true); //Lever to reverse
				if(pCol->Long)
				{
					LongLevers->Draw(Screen->Image->Canvas, X + 3, Y + 7, 4, true);
				}
				pCol->pSw->R = true;
				pCol->pSw->N = false;
			}
			if(pCol->pSw->NI)
			{
				ShortLevers->Draw(Screen->Image->Canvas, X + 10, Y + 23, 3, true); //Lever to normal
				if(pCol->Long)
				{
					LongLevers->Draw(Screen->Image->Canvas, X + 3, Y + 7, 3, true);
				}
				pCol->pSw->R = false;
				pCol->pSw->N = true;
			}
		}
		if(Starting == 0)							//Set switch to lever position
		{
			if(pCol->pSw->N && !pCol->pSw->NI && !pCol->pSw->NO)
				pCol->pSw->NO = 2;
			else if(pCol->pSw->NO)
				pCol->pSw->NO--;
			else if(pCol->pSw->R && !pCol->pSw->RI && !pCol->pSw->RO)
				pCol->pSw->RO = 2;
			else if(pCol->pSw->RO)
				pCol->pSw->RO--;
			else
				pCol->pSw->NO = pCol->pSw->RO = 0;
		}
	}

 	if(pCol->pSw && pCol->pSw->Hand)   //Hand switch lever lock
	{
		pCol->pSw->L = !pCol->pSw->NI || pCol->pSw->NI &&
				(pCol->pSw->pBlk->AsstW || pCol->pSw->pBlk->AsstE);

		pCol->pSw->UnlockReq = pCol->pSw->R;  //Set unlock request
	}
}
//------------------------------------------------------------------------------
//Hand-operated switch

void TPSRY::HandSwitch(int Col, int Row, bool Up, SWITCH *pSw)
{
	int ptr = Col*Rows + Row;

	if(pSw->UnlockReq && !pSw->pBlk->AsstW && !pSw->pBlk->AsstE)
		pSw->Locked = false;
	else if(!pSw->UnlockReq)
		pSw->Locked = true;
	pSw->pBlk->Switch = !pSw->Locked || !pSw->NI;

	if(!pSw->Locked && Up)
		Screen->Work[ptr] = char(27);
	else if(!pSw->Locked && !Up)
		Screen->Work[ptr] = char(29);
	else if(pSw->Locked && Up)
		Screen->Work[ptr] = char(26);
	else if(pSw->Locked && !Up)
		Screen->Work[ptr] = char(28);
}

//For additional hand switch controlled by same lever

void TPSRY::HandAdditional(int Col, int Row, bool Up, SWITCH *pSw)
{
	int ptr = Col*Rows + Row;

	if(!pSw->Locked && Up)
		Screen->Work[ptr] = char(27);
	else if(!pSw->Locked && !Up)
		Screen->Work[ptr] = char(29);
	else if(pSw->Locked && Up)
		Screen->Work[ptr] = char(26);
	else if(pSw->Locked && !Up)
		Screen->Work[ptr] = char(28);
}
//------------------------------------------------------------------------------
//Function for switch button (Hyde && Cliff)

int TPSRY::SwitchButton(int Col, int Row, int* Time)
{
	int T = *Time;
	int ptr = Col*Rows + Row;

	if(Screen->MouseCol == Col && Screen->MouseRow == Row)
	{
		if(Screen->MouseLeft)
		{
			Screen->Work[ptr] = char(25);        //button down
			Screen->MouseLeft = false;
			T = 4;
			Screen->Invalidate = true;
		}
		if(T)
			T--;
	}
	return T;
}

//NX button for Nassau and Yard

int TPSRY::NXBtn(int Col, int Row, int A, int B, bool* Btn)
{
	if(Screen->MouseLeft && Row == Screen->MouseRow && Col == Screen->MouseCol)
	{
		if(A != B)
			A = B;
		else
			A = 0;
		Screen->MouseLeft = Screen->MouseRight = false;
		Screen->MouseCol = Screen->MouseRow = 0;
	}
	if(A == B)
	{
		Screen->Work[Col*Rows + Row] = 25;  //button down
		*Btn = true;
		Screen->Invalidate = true;
	}
	else
		*Btn = false;
	return A;
}

//------------------------------------------------------------------------------

 //Functions for controlling signals with mouse clicks on signal tiles


 void TPSRY::ClickSignalE(int Col, int Row, LEVER Lvr, SIGLVR *pSigL, BLOCK *pBlk)
{
	int ptr = Col*Rows + Row;

	char temp = Screen->Work[ptr];   //Show signal white if it needs resetting
	if((pSigL->R && Lvr == R || pSigL->L && Lvr == L) && pBlk->RtE != Nil && !pBlk->ClrE && !pBlk->RstrE)
		Screen->Work[ptr] = temp + 40;

	if((Screen->MouseLeft || Screen->MouseRight) && Row == Screen->MouseRow && Col == Screen->MouseCol)
	{
		if(Screen->MouseRight && (pSigL->L || pSigL->R) && !pBlk->ClrE)
			pSigL->Callon = true;
		else if(Screen->MouseLeft && pSigL->N && Lvr == L && !pSigL->LockL && pBlk->RtE != Nil)
		{
			pSigL->L = true;
			pSigL->N = false;
			pSigL->R = false;
		}
		else if(Screen->MouseLeft && pSigL->N && Lvr == R && !pSigL->LockR && pBlk->RtE != Nil)
		{
			pSigL->L = false;
			pSigL->N = false;
			pSigL->R = true;
		}
		else if(Screen->MouseLeft && pSigL->R || pSigL->L)
		{
			pSigL->L = false;
			pSigL->N = true;
			pSigL->R = false;
			pSigL->Callon = false;
		}
		Screen->MouseLeft = Screen->MouseRight = false;
		Screen->MouseCol = Screen->MouseRow = 0;
	}
}
//-------------------------------------------------------------------------------
void TPSRY::ClickSignalW(int Col, int Row, LEVER Lvr, SIGLVR *pSigL, BLOCK *pBlk)
{
	int ptr = Col*Rows + Row;

	char temp = Screen->Work[ptr]; //Show signal white if it needs resetting
	if((pSigL->R && Lvr == R || pSigL->L && Lvr == L) && pBlk->RtW != Nil && !pBlk->ClrW && !pBlk->RstrW)
	Screen->Work[ptr] = temp + 40;

	if((Screen->MouseLeft || Screen->MouseRight) && Row == Screen->MouseRow && Col == Screen->MouseCol)
	{
		if(Screen->MouseRight && (pSigL->L || pSigL->R) && !pBlk->ClrW)
			pSigL->Callon = true;
		else if(Screen->MouseLeft && pSigL->N && Lvr == L && !pSigL->LockL && pBlk->RtW != Nil)
		{
			pSigL->L = true;
			pSigL->N = false;
			pSigL->R = false;
		}
		else if(Screen->MouseLeft && pSigL->N && Lvr == R && !pSigL->LockR && pBlk->RtW != Nil)
		{
			pSigL->L = false;
			pSigL->N = false;
			pSigL->R = true;
		}
		else if(Screen->MouseLeft && pSigL->R || pSigL->L)
		{
			pSigL->L = false;
			pSigL->N = true;
			pSigL->R = false;
			pSigL->Callon = false;
		}

		Screen->MouseLeft = Screen->MouseRight = false;
		Screen->MouseCol = Screen->MouseRow = 0;
	}
}
//-------------------------------------------------------------------------------

//Display diagrams
//Functions to set positions of track switches in display grid

void TPSRY::Switch(int Col, int Row, SWITCH * Switch, char nDis, char rDis)
{
	int ptr = Col*Rows + Row;

	if(Switch->NI)
		Screen->Work[ptr] = nDis;      //Set tile
	else if(Switch->RI)
		Screen->Work[ptr] = rDis;
	else
		Screen->Work[ptr] = 30;
}

void TPSRY::DSSwitch(int Col, int Row, SWITCH *Switch1, SWITCH *Switch2,
		char nnDis, char rnDis, char rrDis, char nrDis)
{
	int ptr = Col*Rows + Row;

	if(Switch1->NI && Switch2->NI)
	{
		Screen->Work[ptr] = nnDis;
	}
	else if (Switch1->RI && Switch2->NI)
	{
		Screen->Work[ptr] = rnDis;
	}
	else if (Switch1->NI && Switch2->RI)
	{
		Screen->Work[ptr] = nrDis;
	}
	else if (Switch1->RI && Switch2->RI)
	{
		Screen->Work[ptr] = rrDis;
	}
	else
	{
		Screen->Work[ptr] = 30;
	}
}

//-----------------------------------------------------------------------

void TPSRY::Scissors(int Col, int Row, SWITCH *Switch1, SWITCH *Switch2)
{
	int ptr = Col*Rows + Row;

	if(Switch1->RI)
	{
		Screen->Work[ptr] = 6;
	}
	else if(Switch2->RI)
	{
		Screen->Work[ptr] = 7;
	}
	else if(Switch1->NI && Switch2->NI)
	{
		Screen->Work[ptr] = 1;
	}
	else
		Screen->Work[ptr] =  30;
}
//------------------------------------------------------------------------------

//Functions to set display state of blocks

void TPSRY::Tracker(int Col, int Row, BLOCK* pBlk, BTYPE Type)
{
	bool* Input = &pBlk->M;
	XTracker(Col, Row, pBlk, Type, Input);
}

void TPSRY::XTracker(int Col, int Row, BLOCK* pBlk, BTYPE Type, bool* Input)
{
	int ptr = Col*Rows + Row;
	char temp = Screen->Work[ptr];    //get first tile
	char ntemp;

	while(Row > 0 && Row < Rows && Col < Cols)
	{
		if(temp == 0)
			break;

		if((temp == 24 || temp == 25) && !ButtonJump)   //up and down buttons
			break;

		if((Type == Blk || Type == DBlk || Type == RDBlk || Type == OSE || Type == OSW) && InTestMode)
		{
			if(Col == Screen->MouseCol && Row == Screen->MouseRow && Screen->MouseRight)  //Mouse handler for block clicks
			{
				Screen->MouseRight = false;                            //Toggle
				if(*Input && (Type == OSE || Type == OSW))
					*Input = false;
				else if(*Input && Type != OSE && Type != OSW && pBlk->Loco == "")
					*Input = false;
				else if(*Input && pBlk->Loco != "")
				{
					pBlk->MouseR = true;
					RailroadBlockClick(pBlk);
				}
				else
					*Input = true;
			}
		}

		if(Type == Blk || Type == DBlk || Type == RDBlk ||
			Type == AnnunE || Type == AnnunW || Type == Yd)
		{
			if(Col == Screen->MouseCol && Row == Screen->MouseRow)  //Mouse handler for block clicks
			{
				if(Screen->MouseLeft || Screen->RemoteMouseLeft)
					pBlk->MouseL = true;
				if(Screen->MouseRight || Screen->RemoteMouseRight)
					pBlk->MouseR = true;
				Screen->MouseLeft = Screen->MouseRight =
					Screen->RemoteMouseLeft = Screen->RemoteMouseRight = false;
				Screen->MouseCol = Screen->MouseRow = 0;
				RailroadBlockClick(pBlk);
			}
			if(pBlk->Blk)
			{
				if(Type != Blk && temp == 2 && Col%2)
				{
					if((Type == DBlk || Type == AnnunE || Type == AnnunW) && pBlk->Dir ||
							Type == RDBlk && !pBlk->Dir)
						Screen->Work[ptr] = 22;   	//Red block, arrows to right
					else
						Screen->Work[ptr] = 21;      //Red block, arrows to left
				}
				else
					Screen->Work[ptr] = char(temp + 30);  //Red block

			 /*	if(Type == AnnunE && pBlk->Dir && pBlk->Train == "")
				{
					pBlk->Train = "New EB";
					MessageBeep(MB_ICONASTERISK);
				}
				if(Type == AnnunW && !pBlk->Dir && pBlk->Train == "")
				{
					pBlk->Train = "New WB";
					MessageBeep(MB_ICONASTERISK);
				}
			 */
			}
        	else if(pBlk->GnBlk)
			{
				if(Type != Blk && temp == 2 && Col%2)	//Even-numbered columns with trackH
				{
					if((Type == DBlk || Type == AnnunE || Type == AnnunW) && pBlk->Dir ||
							Type == RDBlk && !pBlk->Dir)
						Screen->Work[ptr] = 51;  		//Green block, arrows to right
					else
						Screen->Work[ptr] = 50;		//Green block, arrows to left
				}
				else
        			Screen->Work[ptr] = char(temp + 60);  //Green
			}
		}
		else if(Type == OSE && pBlk->OSE && temp != 24 && temp != 25)
     	{
			Screen->Work[ptr] = char(temp + 30);		 //Red OS
     	}
		else if(Type == OSE && pBlk->GnOSE && temp != 24 && temp != 25)
     	{
     		Screen->Work[ptr] = char(temp + 60);         //Green OS
     	}
		else if(Type == OSW && pBlk->OSW && temp != 24 && temp != 25)
     	{
        	Screen->Work[ptr] = char(temp + 30);		 //Red OS
     	}
		else if(Type == OSW && pBlk->GnOSW && temp != 24 && temp != 25)
		{
     		Screen->Work[ptr] = char(temp + 60);         //Green OS
     	}

		if(temp == 3)					  //Point to next tile
     	{
  			ntemp = Screen->Work[ptr+1];
        	if(ntemp == 3 || ntemp == 14)
				Row++;
        	else
        		break;
     	}
		else if(temp == 13)
     	{
     		Row++;
     	}
     	else if(temp == 6 || temp == 11 || temp == 12)
		{
        	Col++;
        	Row--;
		}
		else if(temp == 7 || temp == 9 || temp == 14)
		{
        	Col++;
        	Row++;
		}
		else if(temp == 2 || temp ==5 || temp == 8 || temp == 10 || temp == 31)
			Col++;
		else if(ButtonJump && (temp == 24 || temp == 25))
		{
			ButtonJump = false;                //button jump here
			Col++;
        }
		else
			break;
		ptr = Col*Rows + Row;
		temp = Screen->Work[ptr];
 		if(temp == 5)
        	break;
	}
  	if(Type == OSE && pBlk->GnOSE)
  		pBlk->GnOSE--;
	if(Type == OSW && pBlk->GnOSW)
    	pBlk->GnOSW--;
  	else if((Type == Blk || Type == DBlk || Type == RDBlk ||
			Type == AnnunE || Type == AnnunW || Type == Yd) && pBlk->GnBlk)
  		pBlk->GnBlk--;
}
//------------------------------------------------------------------------------

//Function to display approach indication, used for hidden tracks at Shore

void TPSRY::Approach(int Col, int Row, BLOCK * pBlk, bool Section)
{
	if(pBlk->M && !Section)
	{
		for(int i=0; i<3; i++)   //Set 3 tiles at white
		{
			Screen->Work[Col*Rows + Row] = char(2);
			Col++;
		}
	}
}
//------------------------------------------------------------------------------

//Function to display eastbound signal and stop indications

void TPSRY::SignalE(int Col, int Row, BLOCK* pBlk)
{
   //Display signal
	int ptr = Col*Rows + Row;
	char temp = Screen->Work[ptr];
	if(pBlk->ClrE)
		Screen->Work[ptr] = char(temp + 30);
	else if(pBlk->RstrE)
	{
		if(temp != 18)						//dwarf signal
			Screen->Work[ptr] = char(76);
		else
			Screen->Work[ptr] = char(48);
	}
	else
		Screen->Work[ptr] = temp;

	//Set stop indicator

	ptr = (Col-1)*Rows + (Row-1);

	if(pBlk->Dir && pBlk->Srel)
		Screen->Work[ptr] = char(23); //Display "R"
	else if(pBlk->Dir && pBlk->SDCC)
		Screen->Work[ptr] = char(80); //Display "A"

  //Display fleeting or reclear state

	ptr = (Col+1)*Rows + Row;

	if(pBlk->Efleet)
		Screen->Work[ptr] = char(78); //F
	else if(pBlk->Ereclear)
		Screen->Work[ptr] = char(85); //R
	else
		Screen->Work[ptr] = char(0);  //Blank
}

//Function to display westbound signal and stop indications

void TPSRY::SignalW(int Col, int Row, BLOCK* pBlk)
{
   //Set signal
	int ptr = Col*Rows + Row;
	char temp = Screen->Work[ptr];
	if(pBlk->ClrW)
		Screen->Work[ptr] = char(temp + 30);
	else if(pBlk->RstrW)
	{										//dwarf signal
		if(temp != 19)
			Screen->Work[ptr] = char(77);
		else
			Screen->Work[ptr] = char(49);
	}
	else
		Screen->Work[ptr] = temp;

	//Set stop indicator

	ptr = (Col+1)*Rows + (Row+1);

	if(!pBlk->Dir && pBlk->Srel)
		Screen->Work[ptr] = char(23); //Display "R"
	else if(!pBlk->Dir && pBlk->SDCC)
		Screen->Work[ptr] = char(80); //Display "A"

   //Display fleeting or reclear state

	ptr = (Col-1)*Rows + Row;

	if(pBlk->Wfleet)
		Screen->Work[ptr] = char(79);
	else if(pBlk->Wreclear)
		Screen->Work[ptr] = char(86);
	else
		Screen->Work[ptr] = char(0);
}

//Function to display west facing signal at east end of block

void TPSRY::SignalWE(int Col, int Row, BLOCK* pBlk)
{
   //Set signal
	int ptr = Col*Rows + Row;
	char temp = Screen->Work[ptr];
	if(pBlk->ClrE)
		Screen->Work[ptr] = char(temp + 30);
	else if(pBlk->RstrE)
	{										//dwarf signal
		if(temp != 19)
			Screen->Work[ptr] = char(77);
		else
			Screen->Work[ptr] = char(49);
	}
	else
		Screen->Work[ptr] = temp;

//Set stop indicator

	ptr = (Col+1)*Rows + (Row+1);

	if(pBlk->Dir && pBlk->Srel)
		Screen->Work[ptr] = char(23); //Display "R"
	else if(pBlk->Dir && pBlk->SDCC)
		Screen->Work[ptr] = char(80); //Display "A"

//Display fleeting or reclear state

	ptr = (Col-1)*Rows + Row;

	if(pBlk->Efleet)
		Screen->Work[ptr] = char(79);
	else if(pBlk->Ereclear)
		Screen->Work[ptr] = char(86);
	else
		Screen->Work[ptr] = char(0);
}

//Function to display east-facing signal at west end of block

void TPSRY::SignalEW(int Col, int Row, BLOCK* pBlk)
{
   //Display signal
	int ptr = Col*Rows + Row;
	char temp = Screen->Work[ptr];
	if(pBlk->ClrW)
		Screen->Work[ptr] = char(temp + 30);
	else if(pBlk->RstrW)
	{
		if(temp != 18)						//dwarf signal
			Screen->Work[ptr] = char(76);
		else
			Screen->Work[ptr] = char(48);
	}
	else
		Screen->Work[ptr] = temp;

	//Set stop indicator

	ptr = (Col-1)*Rows + (Row-1);

	if(!pBlk->Dir && pBlk->Srel)
		Screen->Work[ptr] = char(23); //Display "R"
	else if(!pBlk->Dir && pBlk->SDCC)
		Screen->Work[ptr] = char(80); //Display "A"

	//Display fleeting or reclear state

	ptr = (Col+1)*Rows + Row;

	if(pBlk->Wfleet)
		Screen->Work[ptr] = char(78);
	else if(pBlk->Wreclear)
		Screen->Work[ptr] = char(85);
	else
		Screen->Work[ptr] = char(0);
}
//------------------------------------------------------------------------------

//Function to display indicator lamp

void TPSRY::Indicator(int Col, int Row, int Indication)
{
	int ptr = Col*Rows + Row;

	Screen->Work[ptr] = char(Indication);
}
//------------------------------------------------------------------------------
//Train control and ID display
//------------------------------------------------------------------------------

//Functions to display train and loco numbers for occupied blocks, propagate
//info from block to block and assign trains to blocks

//Main line blocks
void TPSRY::TrainID(BLOCK* pBlk)
{
//ID State machine

	if(pBlk->IDState == Clearing)
		pBlk->IDState = Cleared;
	else if(pBlk->IDState == Cleared)
	{
		if(pBlk->Train != "" || pBlk->Loco != "")
			pBlk->IDState = Writing;
		else
		{
			pBlk->IDState = Off;
            pBlk->DisplayLine = "";
		}
	}
	else if(pBlk->IDState == Writing && pBlk->Blk)
		pBlk->IDState = On;
	else if(pBlk->IDState == Writing && !pBlk->Blk)
		pBlk->IDState = Preview;

	if(pBlk->ResetID)
	{
		pBlk->ResetID = false;
		pBlk->IDState = Clearing;
    }

//Turn on ID when train enters block

	if(pBlk->IDState == Off && (pBlk->OSE || pBlk->OSW) && (pBlk->Train != "" || pBlk->Loco != ""))
		pBlk->ResetID = true;                 //Clear before writing

	 else if(pBlk->IDState == Preview && pBlk->Blk)
		pBlk->ResetID = true;

 //	if(pBlk->Blk && pBlk->DropProtect)
 //		pBlk->ResetID = true;

//Create display line

	if(pBlk->IDState == Writing)
	{
		if(!pBlk->pLoco->ATC && !pBlk->pLoco->RTC && !pBlk->pLoco->Mon)
		{
			if(pBlk->Displayed == sTrain)
				pBlk->DisplayLine = pBlk->Train;
			else if(pBlk->Displayed == sLoco && pBlk->Loco != "")
				pBlk->DisplayLine = "# " + pBlk->Loco;
		}
		else if(pBlk->pLoco->ATC)
		{
			if(pBlk->Displayed == sTrain)
				pBlk->DisplayLine = "a " +  pBlk->Train;
			else if(pBlk->Displayed == sLoco)
				pBlk->DisplayLine = "a# " + pBlk->Loco;
		}
		else if(pBlk->pLoco->RTC)
		{
			if(pBlk->Displayed == sTrain)
				pBlk->DisplayLine = "r " +  pBlk->Train;
			else if(pBlk->Displayed == sLoco)
				pBlk->DisplayLine = "r# " + pBlk->Loco;
		}
		else if(pBlk->pLoco->Mon)
		{
			if(pBlk->Displayed == sTrain)
				pBlk->DisplayLine = "m " +  pBlk->Train;
			else if(pBlk->Displayed == sLoco)
				pBlk->DisplayLine = "m# " + pBlk->Loco;
		}
	}
//Send initial message to Train Tracker

	if(InitializeIDs && (pBlk->Blk || pBlk->RstrE || pBlk->RstrW) && pBlk->DisplayLine != "")
	{
		MessageToTrainTkr("TrnTkr", pBlk->Loco, pBlk->Train, pBlk->BlkID, "");
	}

//Propagate ID when block occupied

	if(pBlk->Blk)
	{
		pBlk->DropProtect = 0;
		if((pBlk->ClrE || pBlk->RstrE) && pBlk->Dir)  	//Propagate eastbound
		{
			pBlk->NxtE->Train = pBlk->Train;
			if(pBlk->Train != "")
				pBlk->NxtE->Displayed = sTrain;
			else if(pBlk->Loco != "")
				pBlk->NxtE->Displayed = sLoco;
		}
		if((pBlk->ClrW || pBlk->RstrW) && !pBlk->Dir) 	//Propagate westbound
		{
			pBlk->NxtW->Train = pBlk->Train;
			if(pBlk->Train != "")
				pBlk->NxtW->Displayed = sTrain;
			else if(pBlk->Loco != "")
				pBlk->NxtW->Displayed = sLoco;
		}
	}

//Turn off ID when train leaves block

	else if(pBlk->Dir && !pBlk->Blk && !pBlk->OSW ||           //Wait before dropping if no detection
		!pBlk->Dir && !pBlk->Blk && !pBlk->OSE)
	{
		if(pBlk->DropProtect)
			pBlk->DropProtect --;
		else
			pBlk->DropProtect = 10;
	}

	if(pBlk->IDState != Off && pBlk->DropProtect == 1)  //drop ID
	{
		pBlk->DropProtect = 0;
		pBlk->Train = "";
		pBlk->DisplayLine = "";
		pBlk->IDState = Off;
	}
}
//------------------------------------------------------------------------------

//Respond to mouse clicks on blocks

void TPSRY::RailroadBlockClick(BLOCK* pBlk)
{
	if(pBlk->MouseL)             //left click on block
	{
		pBlk->MouseL = false;

		if(pBlk->Blk)
		{
			if(LocoList->ItemIndex != -1 && LocoList->Text != "")      //Add loco
			{
				AddLoco(pBlk);
				pBlk->Displayed = sLoco;
			}
			else if(RemoteLoco != "")
			{
				RemDisAdd = true;
				SetLocoList(RemoteLoco, RemoteLocoDir);
				AddLoco(pBlk);
				RemoteLoco = "";
				pBlk->Displayed = sLoco;
			}
			else if(Train->Text != "")          //Assign train ID to block
			{
				pBlk->Train = Train->Text;
				Train->Text = "";
				pBlk->Displayed = sTrain;
			}
			else if(RemoteTrain != "")            //Assign train ID from remote
			{
				pBlk->Train = RemoteTrain;
				RemoteTrain = "";
				pBlk->Displayed = sTrain;
			}
			else if(pBlk->Loco != "" && !Starting)
			{
				SetLoco(pBlk->BlkID);           //Set block list & selected loco to loco
				SelectedLocoNo = pBlk->Loco;
				RemDisSelectLocoMessage(pBlk);
			}
			else if(pBlk->Displayed == sTrain && !TestModeOn->Checked)   //Delete train
			{
				pBlk->Train = "";
			}
			Train->SetFocus();
			pBlk->ResetID = true;
			UpdateActiveList();
		}
	}
	else if(pBlk->MouseR)	//Right click on block, turn off ATC or toggle between ID and loco
	{
		pBlk->MouseR = false;
		if(pBlk->pLoco->ATC)
		{
			ATCMonOff(pBlk);
		}
        else if(pBlk->Displayed == sTrain && pBlk->Loco != "")
		{
			pBlk->Displayed = sLoco;
			pBlk->ResetID = true;
		}
		else if(pBlk->Displayed == sLoco && pBlk->Train != "")
		{
			pBlk->Displayed = sTrain;
            pBlk->ResetID = true;
        }
	}
    Train->SetFocus();
}
//------------------------------------------------------------------------------

void TPSRY::DisplayID(int Col, int Row, BLOCK* pBlk)
{
	int X = Col*HtWd + Screen->DiaXOrigin;
	int Y = Row*HtWd + Screen->DiaYOrigin;
	String DisplayLine;

	if(pBlk->IDState == Clearing)
	{
		for(int i=0; i<5; i++)     //Blank out 3 tiles
		{
			Screen->Display[Col*Rows + Row] = char(99);
			Col++;
		}
	}
	else if(pBlk->IDState == Writing || Screen->RefreshIDs)
	{
		Screen->Image->Canvas->TextOut(X + 2, Y, pBlk->DisplayLine);  //Write display line on diagram
		Screen->Invalidate = true;
		if((!InitializeTiles && (RemoteOn || RemDisOn) || Screen->RefreshIDs) && pBlk->DisplayLine != "")
			DrawRemotes("TrainID", Screen->ImageName, Col, Row, 0, pBlk->DisplayLine);  //Write on remotes
	}
	if(InitializeIDs && (pBlk->Blk || pBlk->RstrE || pBlk->RstrW) && pBlk->DisplayLine != "")
	{
		DrawRemotes("TrainID", Screen->ImageName, Col, Row, 0, pBlk->DisplayLine);  //Initialize ID on remotes
	}
}
//------------------------------------------------------------------------------

void TPSRY::EraseID(int Col, int Row, BLOCK * pBlk, int N)   //Needed when ID not all in track
{
	if(!pBlk->Blk)
	{
		for(int i=0; i<N; i++)     //Blank out N tiles
		{
			Screen->Work[Col*Rows + Row] = char(30);
			Col++;
		}
	}
}
//------------------------------------------------------------------------------

//Function to set direction and combine block indications

void TPSRY::BlkInd(BLOCK* pBlk)
{
	if(!DCCPowerOff)                //Combine block indications if DCC power OK
	{
		pBlk->Blk = pBlk->W || pBlk->M || pBlk->E;
	}

	if(!pBlk->Blk)					//Change signal direction in accordance with signal setting
									//Eastbound is true
	{
		if(pBlk->AsstW)
			pBlk->Dir = false;    	//Direction is Westbound
		if(pBlk->AsstE)
			pBlk->Dir = true;     	//Direction is Eastbound
	}
	else							//Block occupied
	{
		if(pBlk->Dir && (pBlk->ClrW || pBlk->RstrW))
		{
			pBlk->Dir = false;		//Change direction to Westbound on signal change
			pBlk->ResetID = true;  //Rewrite ID
		}
		else if(!pBlk->Dir && (pBlk->ClrE || pBlk->RstrE))
		{
			pBlk->Dir = true;		//Change direction to Eastbound on Signal change
			pBlk->ResetID = true;  //Rewrite ID
		}
	}
}
//------------------------------------------------------------------------------

//Train control for stopping sections

void TPSRY::TC(BLOCK* pBlk, SIGNAL* Wsig, SIGNAL* Esig)
{
   if(pBlk->Dir && pBlk->E && !Esig->Proceed ||
			!pBlk->Dir && pBlk->W && !Wsig->Proceed)
   {
		if(pBlk->pLoco->ATC || pBlk->pLoco->RTC ||pBlk->pLoco->Mon)
			pBlk->SDCC = true;   //DCC stop
		else
			pBlk->Srel  = true;   //relay stop
   }
   else
   {
		pBlk->Srel = pBlk->SDCC = false;  //no stop
   }
}
//------------------------------------------------------------------------------

//Signal and interlocking control-----------------------------------------------

//Eastbound signal control function

void TPSRY::Esig(bool Lvr, SIGLVR *pSigL,  SIGNAL *pSignal, BLOCK *pBlk, ASPECT Aspects)
{
	pBlk->LvrE = false;
	if(pBlk->RtE && !pBlk->AsstW && !pBlk->NxtE->AsstW) //USS lever lock
	{
		pSignal->Lock = false;
		if(pSigL->Fleet)
			pBlk->Efleet = true;
		else
			pBlk->Efleet = false;
	}
	else
		pSignal->Lock = true;

	if(Lvr)     //Lever reversed
	{
		if(!pSignal->Lock && !pBlk->LvrW)  //Signal not locked
		{
			pBlk->LvrE = true;
			if(pSigL->Ereclear)
			{
				pBlk->Ereclear = true;
				pSigL->Ereclear = false;
			}
			pBlk->NxtE->AsstE = 2;   //Assert direction
			if(!pBlk->OSE && !pBlk->NxtE->OSW && !pSigL->Stick)
			{
				if(!pBlk->NxtE->Blk && !pBlk->NxtE->Switch && !pBlk->NxtE->OSE)
				{
					pBlk->Ereclear = false;
					pSigL->ClnFlg = false;
					pSigL->Clear = true;
					pBlk->NxtE->GnBlk = 2;        //turn display green
					pBlk->GnOSE = 2;
					pBlk->NxtE->GnOSW = 2;
					Clear = true;
					Rte = pBlk->RtE;
					NxtClr = pBlk->NxtE->ClrE;
					if(NxtClr)
						NxtClrAd = pBlk->NxtE->NxtE->ClrE;
					NxtRte = pBlk->NxtE->RtE;
				}
	        	else if(pSigL->Callon || pSigL->ClnFlg)
	        	{
					pSigL->ClnFlg = true;
					pSigL->Clear = true;
					Call = true;
					Rstrct = true;
				}
			}
			else if (!pSigL->Fleet || pBlk->RtE == Restricting || pBlk->RtE == Slow)
				pSigL->Stick = true;
		 else
			pSigL->ClnFlg = false;
		}
	}
   else
   {
		pBlk->Ereclear = false;
		if(!pBlk->OSE && !pBlk->NxtE->OSW && pBlk->NxtE->Blk)
			pSigL->Ereclear = true;
		else
			pSigL->Ereclear = false;
   }
   if(pBlk->AsstW)
		pBlk->AsstW--;

   if(pBlk->ClrE)
		pBlk->ClrE--;

   if(pBlk->RstrE)
		pBlk->RstrE--;

   if(Clear)
   {
		if(pBlk->RtE == Restricting)
			pBlk->RstrE = 2;
		else
			pBlk->ClrE = 2;
   }
   else if(Call)
		pBlk->RstrE = 2;

   Setsig(pSigL, pSignal, pBlk->Blk, Aspects);
}
//------------------------------------------------------------------------------

//Westbound signal control functions

void TPSRY::Wsig(bool Lvr, SIGLVR *pSigL,  SIGNAL *pSignal, BLOCK *pBlk, ASPECT Aspects)
{
	pBlk->LvrW = false;
	if(pBlk->RtW && !pBlk->AsstE && !pBlk->NxtW->AsstE)
	{
		pSignal->Lock = false;
		if(pSigL->Fleet)
			pBlk->Wfleet = true;
		else
			pBlk->Wfleet = false;
	}
	else
		pSignal->Lock = true;

	if(Lvr)
	{
		if (!pSignal->Lock && !pBlk->LvrE)
		{
			pBlk->LvrW = true;
			if(pSigL->Wreclear)
			{
				pBlk->Wreclear = true;
				pSigL->Wreclear = false;
			}
			pBlk->NxtW->AsstW = 2;
			if (!pBlk->OSW && !pBlk->NxtW->OSE && !pSigL->Stick)
			{
				if (!pBlk->NxtW->Blk && !pBlk->NxtW->Switch && !pBlk->NxtW->OSW)
				{
					pBlk->Wreclear = false;
					pSigL->ClnFlg = false;
					pSigL->Clear = true;
					Clear = true;
					pBlk->NxtW->GnBlk = 2;
					pBlk->GnOSW = 2;
					pBlk->NxtW->GnOSE = 2;
					Rte = pBlk->RtW;
					NxtClr = pBlk->NxtW->ClrW;
					if(NxtClr)
						NxtClrAd = pBlk->NxtW->NxtW->ClrW;
					NxtRte = pBlk->NxtW->RtW;
				}
				else if(pSigL->Callon || pSigL->ClnFlg)
				{
					pSigL->ClnFlg = true;
					Call = true;
					Rstrct = true;
					pSigL->Clear = true;
				}
			}
			else if (!pSigL->Fleet || pBlk->RtW == Restricting || pBlk->RtW == Slow)
				pSigL->Stick = true;

			else
				pSigL->ClnFlg = false;
		}
	}
	else
	{
		pBlk->Wreclear = false;
		if(!pBlk->OSW && !pBlk->NxtW->OSE && pBlk->NxtW->Blk)
			pSigL->Wreclear = true;
		else
			pSigL->Wreclear = false;
	}
	if(pBlk->AsstE)
		pBlk->AsstE --;

	if(pBlk->ClrW)
		pBlk->ClrW--;

	if(pBlk->RstrW)
		pBlk->RstrW--;

	if(Clear)
	{
		if(pBlk->RtW == Restricting)
			pBlk->RstrW = 2;
		else
			pBlk->ClrW = 2;
	}
	else if(Call)
		pBlk->RstrW = 2;
	Setsig(pSigL, pSignal, pBlk->Blk, Aspects);
}
//------------------------------------------------------------------------------

//Eastbound signal into westbound block

void TPSRY::EWsig(bool Lvr, SIGLVR *pSigL,  SIGNAL *pSignal, BLOCK *pBlk, ASPECT Aspects)
{
	pBlk->LvrE = false;
	if(pBlk->RtE && !pBlk->AsstW && !pBlk->NxtE->AsstE)
	{
		pSignal->Lock = false;
		if(pSigL->Fleet)
			pBlk->Efleet = true;
		else
			pBlk->Efleet = false;
	}
	else
		pSignal->Lock = true;
	if(Lvr)
	{
		if(!pSignal->Lock && !pBlk->LvrW)
		{
			pBlk->LvrE= true;
			if(pSigL->Wreclear)
			{
				pBlk->Wreclear = true;
				pSigL->Wreclear = false;
			}
			pBlk->NxtE->AsstW = 2;
			if (!pBlk->OSE && !pBlk->NxtE->OSE && !pSigL->Stick)
			{
				if(!pBlk->NxtE->Blk && !pBlk->NxtE->Switch && !pBlk->NxtE->OSW)
				{
					pBlk->Wreclear = false;
					pSigL->ClnFlg = false;
					pSigL->Clear = true;
					Clear = true;
					pBlk->NxtE->GnBlk = 2;
					pBlk->NxtE->GnOSE = 2;
					pBlk->GnOSE = 2;
					Rte = pBlk->RtE;
					NxtClr = pBlk->NxtE->ClrW;
					NxtRte = pBlk->NxtE->RtW;
				}
				else if(pSigL->Callon || pSigL->ClnFlg)
				{
					pSigL->ClnFlg = true;
					Call = true;
					Rstrct = true;
					pSigL->Clear = true;
				}
			}
			else if (!pSigL->Fleet || pBlk->RtE == Restricting || pBlk->RtE == Slow)
				pSigL->Stick = true;
			else
				pSigL->ClnFlg = false;
		}
	}
	else
	{
		pBlk->Wreclear = false;
		if(!pBlk->OSW && !pBlk->NxtW->OSE && pBlk->NxtW->Blk)
			pSigL->Wreclear = true;
		else
			pSigL->Wreclear = false;
	}
	if(pBlk->AsstW)
		pBlk->AsstW--;

   if(pBlk->ClrE)
		pBlk->ClrE--;

   if(pBlk->RstrE)
		pBlk->RstrE--;

   if(Clear)
   {
		if(pBlk->RtE == Restricting)
			pBlk->RstrE = 2;
		else
			pBlk->ClrE = 2;
   }
   else if(Call)
		pBlk->RstrE = 2;

	Setsig(pSigL, pSignal, pBlk->Blk, Aspects);
}
//------------------------------------------------------------------------------

//Westbound signal into eastbound block

void TPSRY::WEsig(bool Lvr, SIGLVR *pSigL,  SIGNAL *pSignal, BLOCK *pBlk, ASPECT Aspects)
{
	pBlk->LvrW = false;
	if(pBlk->RtW && !pBlk->AsstE && !pBlk->NxtW->AsstW)
	{
		pSignal->Lock = false;
		if(pSigL->Fleet)
			pBlk->Wfleet = true;
		else
			pBlk->Wfleet = false;
	}
	else
		pSignal->Lock = true;

	if(Lvr)
	{
		if (!pSignal->Lock && !pBlk->LvrE)
		{
			pBlk->LvrW= true;
			if(pSigL->Ereclear)
			{
				pBlk->Ereclear = true;
				pSigL->Ereclear = false;
			}
			pBlk->NxtW->AsstE = 2;
			if (!pBlk->OSW && !pBlk->NxtW->OSW && !pSigL->Stick)
			{
				if (!pBlk->NxtW->Blk && !pBlk->NxtW->Switch && !pBlk->NxtW->OSE)
				{
					pBlk->Ereclear = false;
					pSigL->ClnFlg = false;
					pSigL->Clear = true;
					pBlk->NxtW->GnBlk = 4;
					pBlk->NxtW->GnOSW = 2;
					pBlk->GnOSW = 2;
					Clear = true;
					Rte = pBlk->RtW;
					NxtClr = pBlk->NxtW->ClrE;
					NxtRte = pBlk->NxtW->RtE;
				}
				else if(pSigL->Callon || pSigL->ClnFlg)
				{
					pSigL->ClnFlg = true;
					Call = true;
					Rstrct = true;
					pSigL->Clear = true;
				}
			}
			else if (!pSigL->Fleet || pBlk->RtW == Restricting || pBlk->RtW == Slow)
        		pSigL->Stick = true;

        	else
        		pSigL->ClnFlg = false;
     	}
  	}
	else
	{
		pBlk->Ereclear = false;
		if(!pBlk->OSE && !pBlk->NxtE->OSW && pBlk->NxtE->Blk)
        	pSigL->Ereclear = true;
		else
        	pSigL->Ereclear = false;
	}

	if(pBlk->AsstE > 0)
    	pBlk->AsstE --;

	if(pBlk->ClrW)
		pBlk->ClrW--;

	if(pBlk->RstrW)
		pBlk->RstrW--;

	if(Clear)
	{
		if(pBlk->RtW == Restricting)
			pBlk->RstrW = 2;
		else
			pBlk->ClrW = 2;
	}
	else if(Call)
		pBlk->RstrW = 2;

  	Setsig(pSigL, pSignal, pBlk->Blk, Aspects);
}
//------------------------------------------------------------------------------

//Fleeting

void TPSRY::Fleeting(bool FltLvr, SIGLVR *pSigL)
{
	if(FltLvr)
  	{
  		if((pSigL->R || pSigL->L) && !pSigL->NoFleet)
		  	pSigL->Fleet = true;
     	else
     		pSigL->NoFleet = true;
  	}
  	else
     	pSigL->Fleet = pSigL->NoFleet = false;

  	if(!pSigL->L && !pSigL->R)
  		pSigL->Fleet = false;
}
//------------------------------------------------------------------------------

//Set interlocking signal

void TPSRY::Setsig(SIGLVR *pSigL, SIGNAL *pSignal, bool Blk, ASPECT Aspects)
{
	if(Aspects == RegAspects)
	{
		if (Clear && Rte == Main && NxtClr && NxtRte == Main)
		{
			pSignal->Aspect[0] = false;	//Clear
			pSignal->Aspect[1] = true;
			pSignal->Aspect[2] = true;
		}
		else if (Clear && Rte == Main && NxtClr && NxtRte == Diverging)
		{
			pSignal->Aspect[0] = false;  //Approach Medium
			pSignal->Aspect[1] = true;
			pSignal->Aspect[2] = false;
		}
		else if (Clear && Rte == Diverging && NxtClr && NxtRte == Main)
		{
			pSignal->Aspect[0] = true;   //Medium Clear
			pSignal->Aspect[1] = true;
			pSignal->Aspect[2] = true;
		}
		else if (Clear && (Rte == Main || Rte == Diverging) && NxtClr && NxtRte == Slow)
		{
			pSignal->Aspect[0] = true;   //Approach Slow
			pSignal->Aspect[1] = true;
			pSignal->Aspect[2] = false;
		}
		else if (Clear && Rte == Main && (!NxtClr || NxtClr && NxtRte == Restricting))
		{
			pSignal->Aspect[0] = false;  //Approach
			pSignal->Aspect[1] = false;
			pSignal->Aspect[2] = true;
		}
		else if (Clear && Rte == Diverging && !NxtClr || NxtClr&& NxtRte != Main)
		{
			pSignal->Aspect[0] = true;   //Medium Approach
			pSignal->Aspect[1] = false;
			pSignal->Aspect[2] = true;
		}
		else if (Clear && Rte == Restricting || Rstrct)
		{
			pSignal->Aspect[0] = true;   //Restricting
			pSignal->Aspect[1] = false;
			pSignal->Aspect[2] = false;
		}
		else
		{
			pSignal->Aspect[0] = false;  //Stop Signal
			pSignal->Aspect[1] = false;
			pSignal->Aspect[2] = false;
		}
   }
	else if(Aspects == RegSloAspects)
	{
		if (Clear && Rte == Main && NxtClr)
		{
			pSignal->Aspect[0] = false;	//Clear
			pSignal->Aspect[1] = true;
			pSignal->Aspect[2] = true;
		}
		else if (Clear && Rte == Slow && NxtClr)
		{
			pSignal->Aspect[0] = true;   //Slow Clear
			pSignal->Aspect[1] = true;
			pSignal->Aspect[2] = true;
		}
		else if (Clear && Rte == Main && !NxtClr)
		{
			pSignal->Aspect[0] = false;  //Approach
			pSignal->Aspect[1] = false;
			pSignal->Aspect[2] = true;
		}
		else if (Clear && Rte == Slow && !NxtClr)
		{
			pSignal->Aspect[0] = true;   //Slow Approach
			pSignal->Aspect[1] = false;
			pSignal->Aspect[2] = true;
		}
		else if (Clear && Rte == Restricting || Rstrct)
		{
			pSignal->Aspect[0] = true;   //Restricting
			pSignal->Aspect[1] = false;
			pSignal->Aspect[2] = false;
		}
		else
		{
			pSignal->Aspect[0] = false;  //Stop
			pSignal->Aspect[1] = false;
			pSignal->Aspect[2] = false;
		}
	}
	else if(Aspects == AdvAspects)
	{
     	if (Clear && Rte == Main && NxtClr && NxtRte == Main && NxtClrAd)
		{
			pSignal->Aspect[0] = false;	//Clear
			pSignal->Aspect[1] = true;
			pSignal->Aspect[2] = true;
		}
	   	else if (Clear && Rte == Main && NxtClr && NxtRte == Diverging)
	  	{
			pSignal->Aspect[0] = false;  //Approach Medium
			pSignal->Aspect[1] = true;
			pSignal->Aspect[2] = false;
		}
	   	else if (Clear && Rte == Diverging && NxtClr && NxtRte == Main)
	  	{
			pSignal->Aspect[0] = true;   //Medium Clear
			pSignal->Aspect[1] = true;
			pSignal->Aspect[2] = true;
	  	}
	   	else if (Clear && Rte == Main && NxtClr && NxtRte == Main && !NxtClrAd)
	  	{
	  		pSignal->Aspect[0] = true;   //Advance Approach
	     	pSignal->Aspect[1] = true;
	     	pSignal->Aspect[2] = false;
	  	}
	  	else if (Clear && Rte == Main && (!NxtClr || NxtClr && NxtRte == Restricting))
	  	{
			pSignal->Aspect[0] = false;  //Approach
			pSignal->Aspect[1] = false;
			pSignal->Aspect[2] = true;
		}
	  	else if (Clear && Rte == Diverging && !NxtClr || NxtClr&& NxtRte != Main)
	  	{
			pSignal->Aspect[0] = true;   //Medium Approach
			pSignal->Aspect[1] = false;
			pSignal->Aspect[2] = true;
	  	}
		else if (Clear && Rte == Restricting || Rstrct)
	  	{
			pSignal->Aspect[0] = true;   //Restricting
			pSignal->Aspect[1] = false;
			pSignal->Aspect[2] = false;
		}
		else
	  	{
			pSignal->Aspect[0] = false;  //Stop Signal
			pSignal->Aspect[1] = false;
			pSignal->Aspect[2] = false;
		}
	}
	else if(Aspects == SloAspects)
	{
		if(Clear && NxtClr && Rte == Slow || Rte == Diverging)
		{
        	pSignal->Aspect[0] = false;	//Slow clear
			pSignal->Aspect[1] = true;
		}
		else if(Clear && !NxtClr && Rte == Slow)
		{
			pSignal->Aspect[0] = true;	//Slow approach
			pSignal->Aspect[1] = true;
		}
		else if(Clear && Rte == Restricting || Rstrct)
		{
        	pSignal->Aspect[0] = true;	//Restricting
			pSignal->Aspect[1] = false;
		}
		else
		{
        	pSignal->Aspect[0] = false;	//Stop Signal
			pSignal->Aspect[1] = false;
		}
	}
	pSigL->Stick = pSigL->Stick && !pSigL->Fleet && (pSigL->L || pSigL->R); //hold stick

	pSigL->ClnFlg = pSigL->ClnFlg && (pSigL->L || pSigL->R); //hold callon flag

   //hold Proceed flag when clear or restricting indication, callon button
   //pressed or approach block occupied

	pSignal->Proceed = Clear || Rstrct || pSigL->Callon ||
		pSignal->Proceed && Blk && (pSigL->L || pSigL->R);

	Clear = NxtClr = NxtClrAd = Rstrct = Call = false;
}
//------------------------------------------------------------------------------

//Signal lever indications on tower panels

void TPSRY::SigInd(SIGLVR *pSigL)
{
	if(pSigL->ClnFlg)
	{
		pSigL->LI = false;
		pSigL->NI = SFlash;
		pSigL->RI = false;
	}
	else if(pSigL->Clear && pSigL->L)
	{
		pSigL->LI = true;
		pSigL->NI = false;
		pSigL->RI = false;
	}
	else if(pSigL->Fleet && !pSigL->Clear && pSigL->L)
	{
		pSigL->LI = SFlash;
		pSigL->NI = true;
		pSigL->RI = false;
	}
	else if(pSigL->Clear && pSigL->R)
	{
		pSigL->LI = false;
		pSigL->NI = false;
		pSigL->RI = true;
	}
	else if(pSigL->Fleet && !pSigL->Clear && pSigL->R)
	{
		pSigL->LI = false;
		pSigL->NI = true;
		pSigL->RI = SFlash;
	}
	else
	{
		pSigL->LI = false;
		pSigL->NI = true;
		pSigL->RI = false;
	}
	pSigL->Clear = false;
}
//------------------------------------------------------------------------------

//function to control eastbound block signal

void TPSRY::EBkcon(bool Dir, SIGNAL *pSignal, BLOCK* pBlk, ASPECT Aspects)
{
	if(Dir && !pBlk->OSE && !pBlk->NxtE->Blk &&
		!pBlk->NxtE->Switch && !pBlk->NxtE->OSE)
	{
		Clear = true;
		pBlk->NxtE->GnBlk = 2;
		NxtClr = pBlk->NxtE->ClrE;
		NxtRte = pBlk->NxtE->RtE;
		if(NxtClr)
			NxtClrAd = pBlk->NxtE->NxtE->ClrE;
		pBlk->ClrE = 2;
		pBlk->NxtE->ClrW = 0;
	}
	else if(pBlk->ClrE)
        pBlk->ClrE--;

	SetBsig (pSignal, pBlk->Blk, Aspects);
}
//------------------------------------------------------------------------------

//function to control westbound block signal

void TPSRY::WBkcon(bool Dir, SIGNAL *pSignal, BLOCK* pBlk, ASPECT Aspects)
{
	if(!Dir && !pBlk->OSW && !pBlk->NxtW->Blk &&
		!pBlk->NxtW->Switch && !pBlk->NxtW->OSW)
	{
		Clear = true;
		pBlk->NxtW->GnBlk = 2;
		NxtClr = pBlk->NxtW->ClrW;
		NxtRte = pBlk->NxtW->RtW;
		if(NxtClr)
			NxtClrAd = pBlk->NxtW->NxtW->ClrW;
		pBlk->ClrW = 2;
		pBlk->NxtW->ClrE = false;
	}
	else if(pBlk->ClrW)
		pBlk->ClrW--;

	SetBsig (pSignal, pBlk->Blk, Aspects);
}
//------------------------------------------------------------------------------

//function to set block signal aspects

void TPSRY::SetBsig(SIGNAL* pSignal, bool Blk, ASPECT Aspects)
{
	if(Aspects == RegAspects)
	{
		if (Clear && NxtClr && NxtRte == Main)
		{
			pSignal->Aspect[0] = false;	//clear
			pSignal->Aspect[1] = true;
			pSignal->Aspect[2] = true;
		}
		else if (Clear && NxtClr && NxtRte == Diverging)
		{
			pSignal->Aspect[0] = false;	//approach medium
			pSignal->Aspect[1] = true;
			pSignal->Aspect[2] = false;
		}
		else if (Clear && NxtClr && NxtRte == Slow)
		{
			pSignal->Aspect[0] = true;		//approach slow
			pSignal->Aspect[1] = true;
			pSignal->Aspect[2] = false;
		}
		else if (Clear && !NxtClr)
		{
			pSignal->Aspect[0] = false;	//approach
			pSignal->Aspect[1] = false;
			pSignal->Aspect[2] = true;
		}
		else
		{
			pSignal->Aspect[0] = false;	//stop
			pSignal->Aspect[1] = false;
			pSignal->Aspect[2] = false;
		}
	}
	else if(Aspects == AdvAspects)
	{
		if (Clear && NxtClr && NxtRte == Main && NxtClrAd)
		{
			pSignal->Aspect[0] = false;	//clear
			pSignal->Aspect[1] = true;
			pSignal->Aspect[2] = true;
		}
		else if(Clear && NxtClr && NxtRte == Main && !NxtClrAd)
		{
			pSignal->Aspect[0] = true;	//advance approach
			pSignal->Aspect[1] = true;
			pSignal->Aspect[2] = false;
		}
		else if (Clear && NxtClr && NxtRte == Diverging)
		{
			pSignal->Aspect[0] = false;	//approach medium
			pSignal->Aspect[1] = true;
			pSignal->Aspect[2] = false;
		}
		else if (Clear && !NxtClr)
		{
			pSignal->Aspect[0] = false;	//approach
			pSignal->Aspect[1] = false;
			pSignal->Aspect[2] = true;
		}
		else
		{
			pSignal->Aspect[0] = false;	//stop
			pSignal->Aspect[1] = false;
			pSignal->Aspect[2] = false;
		}
	}
	pSignal->Proceed = Clear || pSignal->Proceed && Blk;
	Clear = NxtClr = NxtClrAd = false;
}
//------------------------------------------------------------------------------

//Messages for DCC breakers

String TPSRY::GetMessage(int i)
{
	String Message;
	switch(i)
	{
		case 0:		Message = "North:   Green Mountain Station";	//from Cliveden node
					break;
		case 1:		Message = "North:   Sheffield A";
					break;
		case 2:		Message = "North:   Green Mountain Yard";
					break;
		case 3:		Message = "North:   Hyde Jct.";
					break;
		case 4:		Message = "North:   Hyde West";
					break;
		case 5:		Message = "North:   Hyde East";
					break;
		case 6:		Message = "North:   Southport Jct.";
					break;
		case 7:     Message = "North:   Carlton";
					break;
		case 8:		Message = "North:   Reverser C22/C23";
					break;
		case 9:     Message = "South:   Bank";							//from Bank node
					break;
		case 10:    Message = "South:   Kale";
					break;
		case 11:    Message = "South:   Waterman";
					break;
		case 12:    Message = "South:   Engine Yard";
					break;
		case 13:    Message = "South:   East End Jct";
					break;
		case 14:    Message = "South:   Shore";
					break;
		case 15:    Message = "South:   Rocky Hill";
					break;
		case 16:    Message = "South:   Harper's Ferry";
					break;
		case 17:    Message = "South:   Reverser Y30";
					break;
		case 18:    Message = "South:   Reverser Y81";
					break;
		case 19:	Message = "East:   Krulish Yard";				//from NassauW node
					break;
		case 20:    Message = "East:   Thomas Yard";
					break;
		case 21:    Message = "East:   Wilson City";
					break;
		case 22:    Message = "East:   Krulish";
					break;
		case 23:    Message = "East:   Nassau West";
					break;
		case 24:    Message = "East:   Nassau East";
					break;
		case 25:	Message = "East:   Foss";
					break;
		case 26:    Message = "East:   Dell";
					break;
		case 27:    Message = "West:   Cliveden";       			//from Latham node
					break;
		case 28:    Message = "West:   Latham";
					break;
		case 29:    Message = "West:   Cornell Jct";
					break;
		case 30:    Message = "West:   Parsons Jct";
					break;
		case 31:    Message = "West:   South Jct";
					break;
		case 32:    Message = "West:   Circus Jct";
					break;
		case 33:    Message = "West:   Southport";
					break;
		case 34:    Message = "West:   Lavin Yard";
					break;
		case 35:    Message = "West:   Reverser P31";
					break;
		case 36:    Message = "West:   Reverser P41";
					break;
		case 37:  	Message = "West:   Reverser P50";
					break;
		case 38:    Message = "North:  Sheffield B";
	}
	return Message;
}
//------------------------------------------------------------------------------
//DCC Circuit Breaker Indications

void TPSRY::Breakers(void)
{
	int i;

	Tripped = NotTripped = false;

	for(i = 0; i < 39; i++)				//Find tripped breakers
	{
		if(CktBkr[i])
			Tripped = true;
		else
			NotTripped = true;
	}
	if(Tripped && NotTripped)                     //Display messages sequentially
	{
		DCCBreakers->Color = clRed;
        DCCPowerOff = false;
		if(Timer>0)
			Timer--;

		else
		{
			Timer = 5;
			for(i = Top; i < 40; i++)
			{
				if(CktBkr[i])
				{
					String Message = GetMessage(i);
					DCCBreakers->Text = Message;
					RemoteBkrMessage(Message);           //Display on remotes
					Top = i + 1;
					break;
				}
			}
			if(i >= 38)
				Top = 0;
		}
	}
	else if(Tripped && !NotTripped)
	{
		DCCBreakers->Color = clNavy;
;       DCCPowerOff = true;
		DCCBreakers->Text = "DCC Power Off";
		RemoteBkrMessage("DCC Power Off");
	}
	else
	{
		DCCBreakers->Color = clGreen;
		DCCPowerOff = false;
		DCCBreakers->Text = "          All OK";
		RemoteBkrMessage("All OK");
	}
	if(InitializeTiles)
	{
		MessageToRemotes("CktBkr", DCCBreakers->Text.Trim());
	 	MessageToRemDis("CktBkr", DCCBreakers->Text.Trim());
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//DCC Automatic Train Control, loco handling and remote throttles

void __fastcall TPSRY::EditLocosButtonClick(TObject *Sender)
{
	EditLocos->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::EditRoutesButtonClick(TObject *Sender)
{
    EditRoutes->ShowModal();
}
//---------------------------------------------------------------------------

void TPSRY::SetLocoList(String Loco, String Dir)
{
	int N = LocoList->GetCount();

	if(N > 0)
	{
		for(int i = 0; i < N; i++)
		{
			String Line = LocoList->Items->Strings[i];
			if(Line == Loco)
			{
				LocoList->ItemIndex = i;
				if(Dir == "For")
					rbForward->Checked = true;
				else
					rbReverse->Checked = true;
				return;
			}
		}
	}
}
//---------------------------------------------------------------------------

void TPSRY::AddLoco(BLOCK* pBlk)
{
	String Loco = LocoList->Items->Strings[LocoList->ItemIndex];
	String X = InLocoBlockList(pBlk->BlkID, Loco);
	if(RemDisAdd && X != "OK")             //loco being added by remote dispatcher
	{
		RemDisAdd = false;
		MessageToRemDis("NoAdd", X);
	}
	else
	{
		if(X == "BlAssgn")
			Application->MessageBox(L"Block already assigned!", L"Pacific Southern", MB_OK);
		else if(X == "LoAssgn")
			Application->MessageBox(L"Loco already assigned!", L"Pacific Southern", MB_OK);
		else if(X == "OK")
		{
			pBlk->Loco = Loco;
			 TCLOCO* pLoco = new TCLOCO;         //Set up data for loco
			GetDCCData(pBlk, pLoco);
			pLoco->Block = pBlk->BlkID;
			pBlk->pLoco = pLoco;       //Initialize loco data pointer
			pBlk->HeadEnd = true;
			if(rbForward->Checked)
			{
				pLoco->DirText = "For";
				pLoco->DCCDir = true;
			}
			else
			{
				pLoco->DirText = "Rev";
				pLoco->DCCDir = false;
			}
			pLoco->SignalSpeed = 0;
			pLoco->ATC = pLoco->RTC = pLoco->Mon = false;
			pLoco->TrackSpeed = 0;
			pLoco->ActiveCnt = 0;
			pLoco->RefreshCnt = 0;
			pBlk->LocoLine = CreateLocoLine(pBlk);
			LocoBlockList->Items->Add(pBlk->LocoLine);
			pBlk->Displayed = sLoco;
			pBlk->ResetID = true;  //Clear and write ID
			rbForward->Checked = true;
			LocoListChange = true;
		}
	}
	LocoList->ItemIndex = -1;
}
//---------------------------------------------------------------------------
String TPSRY::InLocoBlockList(String B, String L)
{
	int N = LocoBlockList->GetCount();

	if(N > 0)
	{
		for(int i = 0; i < N; i++)
		{
			String Line = LocoBlockList->Items->Strings[i];
			String Block = Line.SubString(1, 5).Trim();
			String Loco = Line.SubString(6, 6).Trim();
			if(Block == B && Loco == L)
			{
				LocoBlockList->ItemIndex = i;
				return "OK";
			}
			else if(Loco == L)
			{
				MessageToRemDis("LocoBlk", Line.SubString(1, 16).Trim());
				LocoBlockList->ItemIndex = i;
				return "LoAssgn";
			}
			else if(Block == B)
			{
				MessageToRemDis("LocoBlk", Line.SubString(1, 16).Trim());
				LocoBlockList->ItemIndex = i;
				return "BlAssgn";
			}
		}
		return "OK";
	}
    return "OK";
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::DeleteButtonClick(TObject *Sender)
{
	if(SelectedLoco->Text != "")
	{
		if(RemDisDelete)
		{
			RemDisDelete = false;
			MessageToRemDis("CfmDel", SelectedLoco->Text);
		}
		else
		{
			int N = Application->MessageBox(L"You are about to delete the selected loco", L"Pacific Southern", MB_OKCANCEL);
			if(N == 1)
			   DeleteLoco();
		}
	}
}
//---------------------------------------------------------------------------

void TPSRY::DeleteLoco()
{
	LocoBlockList->ItemIndex = -1;
	int Num = LocoBlockList->GetCount();  //Set LocoBlockList index
	if(Num > 0)
	{
		for(int i = 0; i < Num; i++)
		{
			String Line = LocoBlockList->Items->Strings[i];
			String Loco = Line.SubString(6, 6).Trim();
			if(Loco == SelectedLocoNo)
			{
				LocoBlockList->ItemIndex = i;       //Entry found
				break;
			}
		}
	}
	if(LocoBlockList->ItemIndex != -1)
	{
		String Line = LocoBlockList->Items->Strings[LocoBlockList->ItemIndex];
		String Block = Line.SubString(1, 5).Trim();
		BLOCK* pBlk = GetBlkPtr(Block);
		if(pBlk->pLoco->RTC)
		{
			WriteThrottles(pBlk->pLoco->ClientID, "Drop", "", "");
		}
		if(pBlk->pLoco->ATC || pBlk->pLoco->RTC || pBlk->pLoco->Mon)
		{
			pBlk->pLoco->SetSpeed = 0;           //Stop loco
			TransmitSpeed(pBlk->pLoco);
			delete(pBlk->pLoco);                 //Delete data for loco
			pBlk->pLoco = &DummyLoco;
		}
		if(pBlk->Loco == SelectedLocoNo)
		{
			SelectedLocoNo = "";
			SelectedTrain->Text = "";
			SelectedLoco->Text = "";
			BlockID->Text = "";
			CabSignalAspect = "Stop";
			if(PRRCabSignals)
				CabSignals->Draw(CabSignal->Canvas, 0, 0, 7, true);
			else
				CabSignals->Draw(CabSignal->Canvas, 0, 0, 3, true);
			CabSignal->Repaint();
		}
		LocoBlockList->DeleteSelected();         //Delete loco in list
		pBlk->pLoco->ATC = pBlk->pLoco->RTC = pBlk->pLoco->Mon = false;
		pBlk->pLoco->ActiveCnt = 0;
		 pBlk->Loco = "";
		 pBlk->pLoco = &DummyLoco;
		if(pBlk->Train != "")
			pBlk->Displayed = sTrain;
		else
			pBlk->Displayed = sNone;
		pBlk->ResetID = true;
		LocoListChange = true;
		UpdateActiveList();
		LocoBlockList->ItemIndex = -1;
		LocoBlockList->Repaint();
	}
}
//---------------------------------------------------------------------------
void TPSRY::RailroadRunTrains(void)     //Function to handle loco numbers and ATC each cycle
{
	ROUTE FrontRoute, RearRoute;
	bool Clr, AdvClr, Rstr, RearOS;
	int Num = LocoBlockList->GetCount();
	String Line, Block, Loco;
	int SignalSpeed = 0;

	if(Num > 0)                           //Cycle through LocoBlockList
	{
		for(int i = 0; i < Num; i++)
		{
			Line = LocoBlockList->Items->Strings[i];
			Block = Line.SubString(1, 5).Trim();
			Loco = Line.SubString(6, 6).Trim();
			BLOCK* pBlk = GetBlkPtr(Block);
			TCLOCO* pLoco = pBlk->pLoco;

			//Drop loco from list if no detection and ID being dropped
			if(pBlk->DropProtect == 1 && !DCCPowerOff || Loco == "")
			{
				pBlk->DropProtect = 0;
				if(pBlk->Loco == SelectedLocoNo)
				{
					SelectedLocoNo = "";
					SelectedTrain->Text = "";
					SelectedLoco->Text = "";
					BlockID->Text = "";
					CabSignalAspect = "Stop";
					if(PRRCabSignals)
						CabSignals->Draw(CabSignal->Canvas, 0, 0, 7, true);
					else
						CabSignals->Draw(CabSignal->Canvas, 0, 0, 3, true);
					CabSignal->Repaint();
				}

				pBlk->Loco = "";
				pLoco = &DummyLoco;
				pBlk->HeadEnd = false;
				pLoco->ActiveCnt = false;
				pBlk->ResetID = true;  		//Clear and rewrite ID
				LocoBlockList->Items->Delete(i);
				LocoBlockList->ItemIndex = -1;
				LocoBlockList->Repaint();
				LocoListChange = true;
				ActiveListChange = 2;
				Num--;
				i--;
				continue;			}

			//Get next block when loco reaches next OS in direction of travel

			if(pBlk->Onward && pBlk->Dir && pBlk->OSE ||
				pBlk->Onward && !pBlk->Dir && pBlk->OSW)
			{
				pBlk->Onward = false;
				BLOCK* pNewBlk;
				if(pBlk->Dir)
					pNewBlk = pBlk->NxtE;           //Get pointer to next block Eastbound
				else
					pNewBlk = pBlk->NxtW;           // else Westbound
				String X = InLocoBlockList(pNewBlk->BlkID, "xxxx");     //Make sure next block not already in list
				if(X == "OK")
				{
					pLoco->BlockChange = true;
					pNewBlk->Train = pBlk->Train;
					pNewBlk->Loco = pBlk->Loco;
					pNewBlk->pLoco = pLoco;               //pointer to loco data
					pNewBlk->pLoco->Block = pNewBlk->BlkID;     //new block ID in loco data
					if(pLoco->RTC)                        //if under remote throttle control
					{
						WriteThrottles(pLoco->ClientID, "Block", pNewBlk->BlkID, pBlk->Train); //send new block ID to remote throttle
					}
					pNewBlk->HeadEnd = true;
					pBlk->HeadEnd = false;
					pNewBlk->DirTxt = pBlk->DirTxt;
					pBlk->Loco = "";
					pNewBlk->DropProtect = 0;
					pBlk->DropProtect = 1;           //drop loco from old block on next cycle
					pNewBlk->LocoLine = CreateLocoLine(pNewBlk);
					LocoBlockList->Items->Add(pNewBlk->LocoLine);
					LocoListChange = true;
					ActiveListChange = 2;
				}
			}
			else if(pBlk->HeadEnd && pBlk->Dir && (pBlk->ClrE || pBlk->RstrE) ||
				pBlk->HeadEnd && !pBlk->Dir && (pBlk->ClrW || pBlk->RstrW))
			{
				pBlk->Onward = true;
			}

			if(pBlk->HeadEnd)    //get track speed and set cab signal aspect
			{
				if(pLoco->ActiveCnt)
				{
					if(pLoco->Mon)
						GetTrackSpeed(pLoco);
					else if(!pLoco->RefreshCnt)
					{
						GetTrackSpeed(pLoco);
						pLoco->RefreshCnt = 5;
					}
					else
						pLoco->RefreshCnt--;
				}
				if(pBlk->Dir)   	   //Eastbound signal controls
				{
					RearRoute = pBlk->NxtW->RtE;
					FrontRoute = pBlk->RtE;
					Clr =  pBlk->ClrE;
					AdvClr = pBlk->NxtE->ClrE;
					RearOS = pBlk->OSW;
				}
				else if(!pBlk->Dir)   //Westbound signal controls
				{
					RearRoute = pBlk->NxtE->RtW;
					FrontRoute = pBlk->RtW;
					Clr = pBlk->ClrW;
					AdvClr = pBlk->NxtW->ClrW;
					RearOS = pBlk->OSE;
				}

				if(pBlk->SDCC || pBlk->Srel)       //Set cab signal by front route and rear route
				   pBlk->Signal = "Stop";
				else if(Clr && RearOS)
				{
					if(RearRoute == Diverging || FrontRoute == Diverging)
					   pBlk->Signal = "AppMed";
					else if(RearRoute == Slow || FrontRoute == Slow)
						pBlk->Signal = "AppMed";
					else if(FrontRoute == Main && !AdvClr)
						pBlk->Signal = "AppMed";
					else if(FrontRoute == Main && AdvClr)
						pBlk->Signal = "Clear";
					else
						pBlk->Signal = "Apprch";
				}
				else if(Clr && !RearOS)
				{
					if(FrontRoute == Diverging)
						pBlk->Signal = "AppMed";
					else if(FrontRoute == Slow)
						pBlk->Signal = "AppMed";
					else if(FrontRoute == Main && !AdvClr)    //2 clear blocks ahead for ClearSignal
						pBlk->Signal = "AppMed";
					else if(FrontRoute == Main && AdvClr)
						pBlk->Signal = "Clear";
					else
						pBlk->Signal = "Apprch";
				}
				else
					pBlk->Signal = "Apprch";


				if(pBlk->Signal == "Clear")              //Set signal speed
				   SignalSpeed = pLoco->Normal;
				else if(pBlk->Signal == "AppMed")
				   SignalSpeed = pLoco->Medium;
				else if(pBlk->Signal == "Apprch")
				   SignalSpeed = pLoco->Approach;
				else if(pBlk->Signal == "Stop")
				   SignalSpeed = 0;


				if(pLoco->BlockChange)            //Block change
				{
					MessageToTrainTkr("TrnTkr", pBlk->Loco, pBlk->Train, pBlk->BlkID, pLoco->TrackSpeed);
				}
				if(pLoco->SignalSpeed != SignalSpeed)    //Signal speed change
				{
					pLoco->SignalSpeed = SignalSpeed;
					MessageToTrainTkr("TrnSig",pBlk->Loco, pBlk->Signal, IntToStr(pLoco->SignalSpeed), pLoco->TrackSpeed);
				}
				pLoco->BlockChange = false;

				if(pLoco->RTC && pLoco->CabSignal != pBlk->Signal)    //Cab signal change on remote throttles
				{
					pLoco->CabSignal = pBlk->Signal;
                	WriteThrottles(pLoco->ClientID, "Signal", pBlk->Signal, pLoco->SignalSpeed);
				}

				if(!pLoco->ActiveCnt && !pLoco->ATC && !pLoco->RTC &&
					(pBlk->Dir && pBlk->ClrE || pBlk->Dir && pBlk->RstrE ||
						!pBlk->Dir && pBlk->ClrW || !pBlk->Dir && pBlk->RstrW))   //Set loco active when clear signal ahead
				{
					pLoco->ActiveCnt = 20;
					ActiveListChange = 2;
				}
				else if(pLoco->ActiveCnt && !pLoco->TrackSpeed)
					pLoco->ActiveCnt--;
			}
			if(pBlk->HeadEnd && pBlk->Loco == SelectedLocoNo)        //Set selected loco display
			{
				if(pLoco->ATC || pLoco->RTC)
					TrackSpeed->Text = pLoco->SetSpeed;
				else
					TrackSpeed->Text = pLoco->TrackSpeed;
				SelectedLoco->Text = pBlk->Loco;
				pSelectedLoco = pLoco;
				SelectedTrain->Text = pBlk->Train;
				BlockID->Text = pBlk->BlkID;
				SigSpeed->Text = pLoco->SignalSpeed;
				if(pLoco->ATC)                       //set up control buttons for monitor and ATC
				{
					MonitorBtn->Enabled = false;
					ATCBtn->Enabled = false;
				   OffBtn->Enabled = true;
					ATCPanel->Visible = true;
				}
				else if(pLoco->Mon)
				{
					MonitorBtn->Enabled = false;
					ATCBtn->Enabled = false;
					OffBtn->Enabled = true;
					ATCPanel->Visible = false;
				}
				else
				{
					ATCBtn->Enabled = true;
					MonitorBtn->Enabled = true;
					OffBtn->Enabled = false;
					ATCPanel->Visible = false;
				}
				if(CabSignalAspect != pBlk->Signal && PRRCabSignals)
				{
					CabSignalAspect = pBlk->Signal;
					if(CabSignalAspect == "Clear")
						CabSignals->Draw(CabSignal->Canvas, 0, 0, 4, true);
					else if(CabSignalAspect == "AppMed")
						CabSignals->Draw(CabSignal->Canvas, 0, 0, 5, true);
					else if(CabSignalAspect == "Apprch")
						CabSignals->Draw(CabSignal->Canvas, 0, 0, 6, true);
					else if(CabSignalAspect == "Stop")
						CabSignals->Draw(CabSignal->Canvas, 0, 0, 7, true);
					CabSignal->Repaint();
					ActiveListChange = 2;
				}
				else if(CabSignalAspect != pBlk->Signal && !PRRCabSignals)
				{
					CabSignalAspect = pBlk->Signal;
					if(CabSignalAspect == "Clear")
						CabSignals->Draw(CabSignal->Canvas, 0, 0, 0, true);
					else if(CabSignalAspect == "AppMed")
						CabSignals->Draw(CabSignal->Canvas, 0, 0, 1, true);
					else if(CabSignalAspect == "Apprch")
						CabSignals->Draw(CabSignal->Canvas, 0, 0, 2, true);
					else if(CabSignalAspect == "Stop")
						CabSignals->Draw(CabSignal->Canvas, 0, 0, 3, true);
					CabSignal->Repaint();
					ActiveListChange = 2;
				}
				RemDisSelectLocoMessage(pBlk);
			}

			if(pBlk->HeadEnd && (pLoco->ATC || pLoco->Mon))       //Do if loco under ATC or Mon control
			{
				int Speed, TargetSpeed;		 //Set speed by cab signal and loco data

				if(pBlk->Signal == "Stop" || pLoco->StopButton)
					TargetSpeed = 0;
				else if(pBlk->Signal == "Clear")
					TargetSpeed = pLoco->Normal;
				else if(pBlk->Signal == "AppMed")
					TargetSpeed = pLoco->Medium;
				else if(pBlk->Signal == "Apprch")
				{
					if(RearOS && RearRoute == Slow)   //modification to speed up slow routes under ATC
					{
						if(Clr && (FrontRoute == Slow || FrontRoute == Diverging || FrontRoute == Main))
							TargetSpeed = pLoco->Medium;
						else
							TargetSpeed = pLoco->Approach;
					}
					else if(Clr && FrontRoute == Slow)
						TargetSpeed = pLoco->Medium;
					else
						TargetSpeed = pLoco->Approach;				}

				if(pLoco->ATC)
				{
					if(pBlk->Signal != "Stop" && pLoco->StopButton &&
						pLoco->SetSpeed < pLoco->Start)

						Speed = pLoco->Start;
					else
						Speed = pLoco->SetSpeed;
				}
				else if(pLoco->Mon)
				{
					Speed = pLoco->TrackSpeed;
					pLoco->SetSpeed = pLoco->TrackSpeed;
				}

				if(pLoco->ATC)             //ATC speed control
				{
					if(Speed < TargetSpeed)
					{
						if(pLoco->ADFlg > 0)      //Accelerate
							pLoco->ADFlg--;
						else
						{
							Speed++;
							pLoco->ADFlg = pLoco->Accel;
						}
					}

					else if(Speed > TargetSpeed)
					{
						if(TargetSpeed == 0)         //Stop
						{
							if(Speed > 5)
								Speed = Speed - 5;
							else
								Speed = 0;
						}
						else if(pLoco->ADFlg > 0)    //Decelerate
							pLoco->ADFlg--;
						else
						{
							Speed--;
							pLoco->ADFlg = pLoco->Decel;
						}
					}

					if(pLoco->SetSpeed < Speed || pLoco->SetSpeed > Speed ||
							pLoco->SetDir != pLoco->DCCDir)
					{
						pLoco->SetSpeed = Speed;
						pLoco->SetDir = pLoco->DCCDir;
						TransmitSpeed(pLoco);
						ActiveListChange = 2;
					}
				}

				if(pLoco->Mon)             //Monitor speed control
				{
					if(Speed > TargetSpeed)
					{
						if(TargetSpeed == 0)         //Stop
						{
							if(Speed > 5)
								Speed = Speed - 5;
							else
								Speed = 0;
						}
						else if(pLoco->ADFlg > 0)    //Decelerate
							pLoco->ADFlg--;
						else
						{
							Speed--;
							pLoco->ADFlg = pLoco->Decel;
						}
					}

					if(pLoco->SetSpeed > Speed || pLoco->SetDir != pLoco->DCCDir)
					{
						pLoco->SetSpeed = Speed;
						pLoco->SetDir = pLoco->DCCDir;
						TransmitSpeed(pLoco);
						ActiveListChange = 2;
					}
				}

				if(pLoco->ATC && pBlk->Loco == SelectedLoco->Text)       //Service ATC controls
				{
					if(pSelectedLoco->StopButton)
						StartStopButton->Caption = "Start";
					else
						StartStopButton->Caption = "Stop";
					MessageToRemDis("StSpCap", StartStopButton->Caption);

					if(pSelectedLoco->FZero)
						Headlight->Caption = "Headlight Off";
					else
						Headlight->Caption = "Headlight On";
					MessageToRemDis("HdltCap", Headlight->Caption);
    			}
			}

			if(pBlk->HeadEnd && pLoco->RTC)      //do if loco controlled by remote throttle
			{
				if(pLoco->SetSpeed != pLoco->RemoteSpeed)
				{
					pLoco->SetSpeed = pLoco->RemoteSpeed;
					TransmitSpeed(pLoco);
                    ActiveListChange = 2;
				}
			}
		}

		 if(MonEn != MonitorBtn->Enabled)           //update remote dispatcher
		 {
			MessageToRemDis("MonEn", BoolToStr(MonitorBtn->Enabled));
			MonEn = MonitorBtn->Enabled;
		 }
		 if(ATCEn != ATCBtn->Enabled)
		 {
			MessageToRemDis("ATCEn", BoolToStr(ATCBtn->Enabled));
			ATCEn = ATCBtn->Enabled;
		 }
		 if(OffEn != OffBtn->Enabled)
		 {
			MessageToRemDis("OffEn", BoolToStr(OffBtn->Enabled));
			OffEn = OffBtn->Enabled;
		 }
		 if(TrkSpd != TrackSpeed->Text)
		 {
			MessageToRemDis("TrkSpd", TrackSpeed->Text);
			TrkSpd = TrackSpeed->Text;
		 }
		 if(SigSpd != SigSpeed->Text)
		 {
			MessageToRemDis("SigSpd", SigSpeed->Text);
			TrkSpd = SigSpeed->Text;
		 }

		if(ActiveList->Visible)
		{
			if(ActiveListChange)
			{
				ActiveListChange--;
				if(ActiveListChange == 1)
					UpdateActiveList();
			}
		}
	}

	if(ATCVis != ATCPanel->Visible)     //message to remote dispatcher if change
	{
		MessageToRemDis("ATCVis", BoolToStr(ATCPanel->Visible));
		ATCVis = ATCPanel->Visible;
	}
	if(KillVis != KillATC->Visible)
	{
		MessageToRemDis("KillVis", BoolToStr(KillATC->Visible));
		KillVis = KillATC->Visible;
	}
}
//---------------------------------------------------------------------------

void TPSRY::TransmitSpeed(TCLOCO* pLoco)        //Transmit speed setting to command station
{
	DCCData[0] = 0xA2;
	DCCData[1] = pLoco->hiByte;
	DCCData[2] = pLoco->loByte;
	if(pLoco->DCCDir)
	{
		DCCData[3] = 0x04;        //Forward
	}
	else
	{
		DCCData[3] = 0x03;        //Reverse
	}
	if(pLoco->SetSpeed > 4)
		DCCData[4] = char(pLoco->SetSpeed);
	else
		DCCData[4] = 0;
	SendDCCPacket(5, 1);    //Send 5 bytes, receive 1
}
//---------------------------------------------------------------------------

void TPSRY::TransmitFunction(TCLOCO* pLoco)    //Transmit function to command station
{
	IOBYTE Func;
	Func.bit.b0 = pLoco->FOne;
	Func.bit.b1 = pLoco->FTwo;
	Func.bit.b2 = pLoco->FThree;
	Func.bit.b3 = pLoco->FFour;
	Func.bit.b4 = pLoco->FZero;
	DCCData[0] = 0xA2;
	DCCData[1] = pLoco->hiByte;
	DCCData[2] = pLoco->loByte;
	DCCData[3] = 0x07;
	DCCData[4] = Func.byte;
	SendDCCPacket(5, 1);      //Send 5 bytes, receive 1
}
//---------------------------------------------------------------------------

void TPSRY::SendDCCPacket(int WCount, int RCount)    //Send speed or function packet to command station
{
	DWORD numWrite, numRead;

	WriteFile(DCCcomHandle, DCCData, WCount, &numWrite, 0);

	bool response = false;
	PurgeComm(DCCcomHandle, PURGE_RXCLEAR);
	for(int i=0; i<10; i++)
	{
		ReadFile(DCCcomHandle, Buffer, RCount, &numRead, 0);
		if(numRead > 0)
		{
			response = true;
			break;
		}
		else
		Sleep(3);
	}

	if(!response)
	{
		NumDCCAborts ++;
		DCCAborts->Caption = NumDCCAborts;
	}
}
//---------------------------------------------------------------------------

String TPSRY::CreateLocoLine(BLOCK* pBlk)
{
	String C = AnsiString::StringOfChar(' ', 40);
	C.Insert(pBlk->BlkID, 1);
	C.Insert(pBlk->Loco, 6);
	C.Insert(pBlk->DirTxt, 12);
	if(pBlk->pLoco->ATC || pBlk->pLoco->RTC || pBlk->pLoco->Mon)
		C.Insert(pBlk->pLoco->SetSpeed, 17);
	if(pBlk->pLoco->ATC)
		C.Insert("a", 21);
	else if(pBlk->pLoco->RTC)
		C.Insert("r", 21);
	else if(pBlk->pLoco->Mon)
		C.Insert('m', 21);
	if(pBlk->SDCC)
		C.Insert("A", 23);
	else if(pBlk->Srel)
		C.Insert("R", 23);
	if(pBlk->Dir)
		C.Insert("East", 25);
	else
		C.Insert("West", 25);
	C.TrimRight();
	return C;
}
//---------------------------------------------------------------------------

void TPSRY::UpdateActiveList()
{
	ActiveList->Clear();
	if(RemDisOn)
		MessageToRemDis("ClrLst", "");

	int Num = LocoBlockList->GetCount();
	if(Num > 0)                           //Cycle through LocoBlockList
	{
		for(int i = 0; i < Num; i++)
		{
			String Line = LocoBlockList->Items->Strings[i];
			String Block = Line.SubString(1, 5).Trim();
			BLOCK* pBlk = GetBlkPtr(Block);
			if(pBlk->HeadEnd && (CBActive->Checked && pBlk->pLoco->ActiveCnt ||
				CBATC->Checked && pBlk->pLoco->ATC || cbRTC->Checked && pBlk->pLoco->RTC))
			{
				String L = AnsiString::StringOfChar(' ', 50);
				L.Insert(pBlk->Train, 1);
				L.Insert(CreateLocoLine(pBlk), 8);
				if(pBlk->pLoco->RTC)
					L.Insert(pBlk->pLoco->Name, 38);
				ActiveList->Items->Add(L);

				if(RemDisOn)
				{
				MessageToRemDis("ListA", L.SubString(1, 30));
				MessageToRemDis("ListB", L.SubString(31, 20));
				}
            }
		}
	}
}
//---------------------------------------------------------------------------

void TPSRY::RemoteThrottleConnect(BLOCK* pBlk, String Name, String ClientID)
{
	if(pBlk->HeadEnd && !pBlk->pLoco->ATC && !pBlk->pLoco->RTC && !pBlk->pLoco->Mon)
	{
		pBlk->pLoco->RemoteSpeed = 0;
		pBlk->pLoco->Name = Name;
		pBlk->pLoco->ClientID = ClientID;
		pBlk->pLoco->RTC = true;
		pBlk->pLoco->CabSignal = "Stop";
		pBlk->ResetID = true;  		//Clear and write ID
		UpdateActiveList();
	}
	else if(pBlk->pLoco->ATC || pBlk->pLoco->Mon)
		WriteThrottles(ClientID, "NoLoco", "", "");
}
//---------------------------------------------------------------------------

void TPSRY::RemoteThrottleDisconnect(BLOCK* pBlk)
{
	pBlk->pLoco->SetSpeed = 0;    //Stop loco
	TransmitSpeed(pBlk->pLoco);
	pBlk->pLoco->RTC = false;
	pBlk->pLoco->ActiveCnt = 0;
	pBlk->pLoco = &DummyLoco;
	pBlk->ResetID = true;  		//Clear and write ID
	UpdateActiveList();
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::MonitorBtnClick(TObject *Sender)
{
	if(BlockID->Text != "")
	{
		BLOCK* pBlk = GetBlkPtr(BlockID->Text);

		if(pBlk->HeadEnd && !pBlk->pLoco->ATC && !pBlk->pLoco->RTC && !pBlk->pLoco->Mon)
		{
			pBlk->pLoco->Mon = true;
			pBlk->pLoco->ADFlg = 0;
			pBlk->pLoco->StopButton = false;
			pBlk->ResetID = true;  		//Clear and write ID
			UpdateActiveList();
			Train->SetFocus();
			CabSignal->Repaint();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::ATCBtnClick(TObject *Sender)
{
	if(BlockID->Text != "")
	{
		BLOCK* pBlk = GetBlkPtr(BlockID->Text);

		if(pBlk->HeadEnd && !pBlk->pLoco->ATC && !pBlk->pLoco->RTC && !pBlk->pLoco->Mon)
		{
			pBlk->pLoco->ATC = true;
			pBlk->pLoco->ADFlg = 0;
			pBlk->pLoco->StopButton = true;
			pBlk->ResetID = true;  		//Clear and write ID
			UpdateActiveList();
			Train->SetFocus();
			CabSignal->Repaint();
		}
	}
}
//---------------------------------------------------------------------------

void TPSRY::ATCMonOff(BLOCK* pBlk)
{
	if(pBlk->pLoco->ATC)
	{
		pSelectedLoco->SetSpeed = 0;    //Stop selected Loco
		TransmitSpeed(pSelectedLoco);
	}
	pBlk->pLoco->ATC = false;
	pBlk->pLoco->Mon = false;
	pBlk->ResetID = true;  		//Clear and write ID
	UpdateActiveList();
}
//---------------------------------------------------------------------------

void TPSRY::GetDCCData(BLOCK* pBlk, TCLOCO* pLoco)       //Get data from Edit Locos
{
	pBlk->pLoco = pLoco;
	pLoco->Loco = pBlk->Loco;
	pLoco->DirText = pBlk->DirTxt;
	String D = EditLocos->GetLocoData(pBlk->Loco);
	pLoco->Start = StrToInt(D.SubString(8, 3).Trim());
	pLoco->Approach = StrToInt(D.SubString(16, 3).Trim());
	pLoco->Medium = StrToInt(D.SubString(24, 3).Trim());
	pLoco->Normal = StrToInt(D.SubString(32, 3).Trim());
	pLoco->Accel = StrToInt(D.SubString(40, 2).Trim());
	pLoco->Decel = StrToInt(D.SubString(46, 2).Trim());
	pLoco->FZero = pLoco->FOne = pLoco->FTwo =
		pLoco->FThree = pLoco->FFour = false;
	IONUM Num;
	Num.hlBytes = StrToInt(pBlk->Loco);
	pLoco->hiByte = Num.byte.c1 | 0xC0;   //high byte for long address
	pLoco->loByte = Num.byte.c0;    //low byte
	if(pBlk->DirTxt == "For")
		pLoco->DCCDir = true;
	else
		pLoco->DCCDir = false;
	pLoco->SetSpeed = 0;                  //Stop loco
	TransmitSpeed(pLoco);
}
//---------------------------------------------------------------------------

void TPSRY::GetTrackSpeed(TCLOCO* pLoco)   //Get track speed from DCC server
{
	DWORD numWrite, numRead;
	bool response = false;
	String Speed;

	AnsiString Loco = pLoco->Loco;
	int L = Loco.Length();
	if(L == 4)
	{
		TSOut[0] = Loco[1];
		TSOut[1] = Loco[2];
		TSOut[2] = Loco[3];
		TSOut[3] = Loco[4];
		TSOut[4] = '\n';
	}
	else if(L == 3)
	{
		TSOut[0] = Loco[1];
		TSOut[1] = Loco[2];
		TSOut[2] = Loco[3];
		TSOut[3] = '\n';
	}
	else if(L == 2)
	{
		TSOut[0] = Loco[1];
		TSOut[1] = Loco[2];
		TSOut[2] = '\n';
	}
	else if(L == 1)
	{
		TSOut[0] = Loco[1];
		TSOut[1] = '\n';
	}
	WriteFile(TScomHandle, TSOut, L + 1, &numWrite, 0);

	PurgeComm(TScomHandle, PURGE_RXCLEAR);
	for (int i = 0; i < 5; i++)
	{
		ReadFile(TScomHandle, TSIn,5, &numRead, 0);
		if(numRead >4)
		{
			response = true;
			break;
		}
		else
		   Sleep(1);
	}
	if(!response)
	{
		NumTSAborts ++;
		TSAborts->Caption = NumTSAborts;
		pLoco->TrackSpeed = 0;
	}
	else
	{
		if(TSIn[0] == '?')		       //no speed from server
		{
			pLoco->TrackSpeed = 0;
		}
		else if(TSIn[4] == 'R')
		{
			pLoco->DirText = "Rev";
			pLoco->DCCDir = false;
			TSIn[4] = ' ';
			 Speed = TSIn;
			Speed = Speed.TrimRight();
			pLoco->TrackSpeed = StrToInt(Speed);
		}
		else
		{
			pLoco->DirText = "For";
			pLoco->DCCDir = true;
			TSIn[4] = ' ';
			 Speed = TSIn;
			Speed = Speed.TrimRight();
			pLoco->TrackSpeed = StrToInt(Speed);
		}
	}
}
//---------------------------------------------------------------------------


void TPSRY::ERearATC(BLOCK* pBlk, SIGNAL* Esig)
{       //If no proceed signal, stop eastbound train when hind end OS section clears

	if(pBlk->Blk && pBlk->Dir && (pBlk->pLoco->ATC || pBlk->pLoco->RTC || pBlk->pLoco->Mon) &&
		!Esig->Proceed && !pBlk->OSW && !pBlk->W && !pBlk->NxtW->Blk)
	{
		pBlk->E = true;   //DCC stop
		pBlk->SDCC = true;
	}
	else
	{
		pBlk->E = false;  //no stop
		pBlk->SDCC = false;
	}
}
//---------------------------------------------------------------------------
void TPSRY::WRearATC(BLOCK* pBlk, SIGNAL* Wsig)
{
        //Westbound train
	if(pBlk->Blk && !pBlk->Dir && (pBlk->pLoco->ATC || pBlk->pLoco->RTC || pBlk->pLoco->Mon) &&
		!Wsig->Proceed && !pBlk->OSE && !pBlk->E && !pBlk->NxtE->Blk)
	{
		pBlk->W  = true;   //DCC stop
		pBlk->SDCC = true;
	}
	else
	{
		pBlk->W = false;  //no stop
		pBlk->SDCC = false;
	}
}
//---------------------------------------------------------------------------
void TPSRY::EStubATC(BLOCK* pBlk, SIGNAL* Wsig)              //use when no EB signal ahead
{   //Stop eastbound train when hind end clears OS
	if(pBlk->M && (pBlk->pLoco->ATC || pBlk->pLoco->RTC || pBlk->pLoco->Mon) &&
		pBlk->Dir && !pBlk->OSW && !pBlk->NxtW->Blk)
	{
		pBlk->E = true;   //DCC stop
		pBlk->SDCC = true;
	}
	else
	{
		pBlk->E = false;  //no stop
		pBlk->SDCC = false;
	}
}
//---------------------------------------------------------------------------
void TPSRY::WStubATC(BLOCK* pBlk, SIGNAL* Esig)              //use when no WB signal ahead
{   //Stop westbound train when hind end clears OS
	if(pBlk->M && (pBlk->pLoco->ATC || pBlk->pLoco->RTC ||pBlk->pLoco->Mon) &&
		!pBlk->Dir && !pBlk->OSE && !pBlk->NxtE->Blk)
	{
		pBlk->W = true;   //DCC stop
		pBlk->SDCC = true;
	}
	else
	{
		pBlk->W = false;  //no stop
		pBlk->SDCC = false;
	}
}
//---------------------------------------------------------------------------

void TPSRY::AssignLocos(void)  //Assign locos from saved file to blocks at startup
{
	String Block;
	String Loco;
	int Num = LocoBlockList->Items->Count;
	String Line;
	String BlkDir;
	String DirTxt;

	if(Num > 0)
	{
		for(int i = 0; i < Num; i++)
		{
			Line = LocoBlockList->Items->Strings[i];
			Block = Line.SubString(1, 5).Trim();
			Loco = Line.SubString(6, 6).Trim();
			BlkDir = Line.SubString(25, 4).Trim();
			DirTxt = Line.SubString(12, 4).Trim();
			BLOCK* pBlk = GetBlkPtr(Block);    //get pointer to block
			if(InTestMode)
			{
				pBlk->M = true;     //set block occupied if in test mode
				pBlk->Blk = true;
			}
			if(pBlk->Blk)			//is this block still occupied?
			{
				if(BlkDir == "East")
					pBlk->Dir = true;
				else
					pBlk->Dir = false;
				pBlk->Loco = Loco;

				TCLOCO* pLoco = new TCLOCO;         //Set up data for loco
				GetDCCData(pBlk, pLoco);
				pLoco->Block = Block;
				pLoco->DCCDir = true;
				pLoco->SignalSpeed = 0;
				pLoco->TrackSpeed = 0;
				pLoco->ActiveCnt = 0;
				pLoco->RefreshCnt = 0;
        		pLoco->ATC = pLoco->RTC = pLoco->Mon = false;
                pBlk->Displayed = sLoco;
				pBlk->DirTxt = DirTxt;
				pBlk->pLoco = pLoco;
				pBlk->HeadEnd = true;
				pBlk->pLoco->ATC = false;
				pBlk->ResetID = true;  		//Clear and write ID
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::CabSignalClick(TObject *Sender)
{
	if(PRRCabSignals)
		PRRCabSignals = false;
	else
		PRRCabSignals = true;
	CabSignalAspect = Nil;
	CabSignal->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::HeadlightClick(TObject *Sender)
{
	if(pSelectedLoco->FZero)
		pSelectedLoco->FZero = false;
	else
		pSelectedLoco->FZero = true;
	TransmitFunction(pSelectedLoco);
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::HornMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	pSelectedLoco->FTwo = true;
	TransmitFunction(pSelectedLoco);
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::HornMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	pSelectedLoco->FTwo = false;
	TransmitFunction(pSelectedLoco);
}
//---------------------------------------------------------------------------

BLOCK* TPSRY::GetBlkPtr(String T)    //Lookup table for block pointer from text
{
	if(T == "Y10")                   //Yard
		return &Y10;
	else if(T == "Y11")
		return &Y11;
	else if(T == "Y20")
		return &Y20;
	else if(T == "Y21")
		return &Y21;
	else if(T == "Y30")
		return &Y30;
	else if(T == "Y50")
		return &Y50;
	else if(T == "Y51")
		return &Y51;
	else if(T == "Y52")
		return &Y52;
	else if(T == "Y53")
		return &Y53;
	else if(T == "Y70")
		return &Y70;
	else if(T == "Y81")
		return &Y81;
	else if(T == "Y82")
		return &Y82;
	else if(T == "Y83")
		return &Y83;
	else if(T == "Y84")
		return &Y84;
	else if(T == "Y87")
		return &Y87;
	else if(T == "P1")              //Port
		return &P1;
	else if(T == "P2")
		return &P2;
	else if(T == "P3")
		return &P3;
	else if(T == "P4")
		return &P4;
	else if(T == "P5")
		return &P5;
	else if(T == "P6")
		return &P6;
	else if(T == "P7")
		return &P7;
	else if(T == "P10")
		return &P10;
	else if(T == "P11")
		return &P11;
	else if(T == "P20")
		return &P20;
	else if(T == "P21")
		return &P21;
	else if(T == "P30")
		return &P30;
	else if(T == "P31")
		return &P31;
	else if(T == "P32")
		return &P32;
	else if(T == "P40")
		return &P40;
	else if(T == "P41")
		return &P41;
	else if(T == "P42")
		return &P42;
	else if(T == "P50")
		return &P50;
	else if(T == "P60")
		return &P60;
	else if(T == "P61")
		return &P61;
	else if(T == "P62")
		return &P62;
	else if(T == "P63")
		return &P63;
	else if(T == "V10")
		return &V10;
	else if(T == "V11")
		return &V11;
	else if(T == "L10")     //Latham
		return &L10;
	else if(T == "L11")
		return &L11;
	else if(T == "L20")
		return &L20;
	else if(T == "L21")
		return &L21;
	else if(T == "L31")
		return &L31;
	else if(T == "D10")     //Dell
		return &D10;
	else if(T == "D11")
		return &D11;
	else if(T == "D20")
		return &D20;
	else if(T == "D21")
		return &D21;
	else if(T == "S10")     //Shore
		return &S10;
	else if(T == "S11")
		return &S11;
	else if(T == "S20")
		return &S20;
	else if(T == "S21")
		return &S21;
	else if(T == "F10")     //Harpers
		return &F10;
	else if(T == "F11")
		return &F11;
	else if(T == "H10")     //Hyde
		return &H10;
	else if(T == "H11")
		return &H11;
	else if(T == "H12")
		return &H12;
	else if(T == "H13")
		return &H13;
	else if(T == "H20")
		return &H20;
	else if(T == "H21")
		return &H21;
	else if(T == "H22")
		return &H22;
	else if(T == "H23")
		return &H23;
	else if(T == "H30")
		return &H30;
	else if(T == "H31")
		return &H31;
	else if(T == "H32")
		return &H32;
	else if(T == "H33")
		return &H33;
	else if(T == "H34")
		return &H34;
	else if(T == "H40")
		return &H40;
	else if(T == "H41")
		return &H41;
	else if(T == "H42")
		return &H42;
	else if(T == "H43")
		return &H43;
	else if(T == "N10")     //Nassau
		return &N10;
	else if(T == "N11")
		return &N11;
	else if(T == "N12")
		return &N12;
	else if(T == "N20")
		return &N20;
	else if(T == "N21")
		return &N21;
	else if(T == "N22")
		return &N22;
	else if(T == "N25")
		return &N25;
	else if(T == "N31")
		return &N31;
	else if(T == "N32")
		return &N32;
	else if(T == "N41")
		return &N41;
	else if(T == "N42")
        return &N42;
	else if(T == "N60A")
		return &N60A;
	else if(T == "N60B")
		return &N60B;
	else if(T == "N60C")
		return &N60C;
	else if(T == "N60D")
		return &N60D;
	else if(T == "K10")
		return &K10;
	else if(T == "T12")
		return &T12;
	else if(T == "W10")
		return &W10;
	else if(T == "W11")
		return &W11;
	else if(T == "W20")
		return &W20;
	else if(T == "R10")     //Rocky Hill
		return &R10;
	else if(T == "B10")     //Bank
		return &B10;
	else if(T == "B11")
		return &B11;
	else if(T == "B20")
		return &B20;
	else if(T == "B21")
		return &B21;        //Cliff
	else if(T == "C10")
		return &C10;
	else if(T == "C11")
		return &C11;
	else if(T == "C12")
		return &C12;
	else if(T == "C13")
		return &C13;
	else if(T == "C20")
		return &C20;
	else if(T == "C21")
		return &C21;
	else if(T == "C22")
		return &C22;
	else if(T == "C23")
		return &C23;
	else if(T == "C30")
		return &C30;
	else if(T == "C31")
		return &C31;
	else if(T == "C40")
		return &C40;
	else if(T == "C41")
		return &C41;
	else if(T == "C42")
		return &C42;
	else if(T == "C43")
		return &C43;
	else if(T == "C44")
		return &C44;
	else if(T == "C50")
		return &C50;
	else if(T == "C51")
		return &C51;
	else if(T == "C52")
		return &C52;
	else if(T == "C53")
		return &C53;
	else if(T == "C54")
		return &C54;
	else if(T == "G10")
		return &G10;
	else if(T == "G12")
		return &G12;
	else if(T == "G21")
		return &G21;
	else
		return &DummyBlock;
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::KillATCClick(TObject *Sender)
{
	int Num = LocoBlockList->GetCount();
	String Line;
	String Block;
	String Loco;

	if(Num > 0)                           //Cycle through LocoBlockList
	{
		for(int i = 0; i < Num; i++)
		{
			Line = LocoBlockList->Items->Strings[i];
			Block = Line.SubString(1, 5).Trim();
			Loco = Line.SubString(6, 6).Trim();
			BLOCK* pBlk = GetBlkPtr(Block);
			if(pBlk->pLoco->ATC)
			{
				pBlk->pLoco->SetSpeed = 0;    //Stop Loco
				TransmitSpeed(pBlk->pLoco);
				pBlk->pLoco->ATC = false;
				pBlk->ResetID = true;  		//Clear and write ID
			}
		}
		SelectedLocoNo = "";
		UpdateActiveList();
	}
}
//---------------------------------------------------------------------------
void __fastcall TPSRY::ActiveListBtnClick(TObject *Sender)
{
	if(ActiveList->Visible)
	{
		ActiveList->Visible = false;
		MessageToRemDis("ShowLst", "False");
	}
	else
	{
		ActiveList->Visible = true;
		MessageToRemDis("ShowLst", "True");
		UpdateActiveList();
	}
	Train->SetFocus();
}
//---------------------------------------------------------------------------



void __fastcall TPSRY::ActiveListMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if(ActiveList->ItemIndex != -1)
	{
		String S = ActiveList->Items->Strings[ActiveList->ItemIndex];
		String Block = S.SubString(8, 5).TrimRight();
		BLOCK* pBlk = GetBlkPtr(Block);
		SetLoco(pBlk->Loco);
		SelectedLocoNo = pBlk->Loco;
		SelectedLoco->Text = pBlk->Loco;
		SelectedTrain->Text = pBlk->Train;
		BlockID->Text = pBlk->BlkID;
	}

}
//---------------------------------------------------------------------------

void TPSRY::SetLoco(String BlkID)          //called by click on block or active list
										   //finds entry in LocoBlockList
{
	int Num = LocoBlockList->GetCount();
	String Line;
	String Block;

	if(Num > 0)
	{
		for(int i = 0; i < Num; i++)
		{
			Line = LocoBlockList->Items->Strings[i];
			Block = Line.SubString(1, 5).Trim();

			if(Block == BlkID)
			{
				LocoBlockList->ItemIndex = i;
				MessageToRemDis("LocoBlk", Line.SubString(1, 16).Trim());
				break;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::StartStopButtonClick(TObject *Sender)
{
	if(pSelectedLoco->StopButton)
		pSelectedLoco->StopButton = false;
	else
		pSelectedLoco->StopButton = true;
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::DeleteIDClick(TObject *Sender)
{
	if(LocoBlockList->ItemIndex != -1)  //Loco is selected
	{
		String Line = LocoBlockList->Items->Strings[LocoBlockList->ItemIndex];
		String Block = Line.SubString(1, 5).Trim();
		BLOCK* pBlk = GetBlkPtr(Block);
		pBlk->Train = "";
		if(pBlk->Loco != "")
			pBlk->Displayed = sLoco;
		pBlk->ResetID = true;  		//Clear and write ID
		Train->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::DirClick(TObject *Sender)
{
	if(pSelectedLoco->StopButton)
	{
		pSelectedLoco->DCCDir = !pSelectedLoco->DCCDir;
		BLOCK* pBlk = GetBlkPtr(pSelectedLoco->Block);
		if(pSelectedLoco->DCCDir)
			pBlk->DirTxt = "For";
		else
			pBlk->DirTxt = "Rev";
	}
}
//---------------------------------------------------------------------------

//Show display tile column and row coordinates as mouse moves

void __fastcall TPSRY::ImageHyYdPtMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
	int DX = X - HyYdPt.DiaXOrigin;
	int DY = Y - HyYdPt.DiaYOrigin;

	Col->Text = (DX-DX%HtWd)/HtWd;
	Row->Text = (DY-DY%HtWd)/HtWd;

}
//---------------------------------------------------------------------------

//Display column and row point to by mouse

void __fastcall TPSRY::ImageLaKrMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
	int DX = X - LaKr.DiaXOrigin;
	int DY = Y - LaKr.DiaYOrigin;

	Col->Text = (DX-DX%HtWd)/HtWd;
	Row->Text = (DY-DY%HtWd)/HtWd;

}
//---------------------------------------------------------------------------


void __fastcall TPSRY::ImageNaCfMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
	int DX = X - NaCf.DiaXOrigin;
	int DY = Y - NaCf.DiaYOrigin;

	Col->Text = (DX-DX%HtWd)/HtWd;
	Row->Text = (DY-DY%HtWd)/HtWd;

}
//---------------------------------------------------------------------------

//Train ID setting

void __fastcall TPSRY::ClearIDsClick(TObject *Sender)
{
	ClearID(&H30);   //Hyde
	ClearID(&H31);
	ClearID(&H32);
	ClearID(&H33);
	ClearID(&H34);
	ClearID(&H12);
	ClearID(&H22);
	ClearID(&H43);
	ClearID(&H42);
	ClearID(&H41);
	ClearID(&H40);

	ClearID(&Y53);   //Yard
	ClearID(&Y52);
	ClearID(&Y51);
	ClearID(&Y50);
	ClearID(&Y81);
	ClearID(&Y82);
	ClearID(&Y83);
	ClearID(&Y84);

	ClearID(&P7);    //Port
	ClearID(&P6);
	ClearID(&P5);
	ClearID(&P4);
	ClearID(&P3);
	ClearID(&P2);
	ClearID(&P1);
	ClearID(&P32);

	ClearID(&N31);   //Nassau
	ClearID(&N32);
	ClearID(&N41);
	ClearID(&N42);

	ClearID(&C44);   //Cliff
	ClearID(&C43);
	ClearID(&C42);
	ClearID(&C41);
	ClearID(&C40);
	ClearID(&C50);
	ClearID(&C51);
	ClearID(&C52);
	ClearID(&C53);
	ClearID(&C54);
	ClearID(&C30);
	ClearID(&C31);
}
//---------------------------------------------------------------------------

void TPSRY::ClearID(BLOCK* pBlk)
{
	pBlk->Train = "";
	if(pBlk->Loco != "")
		pBlk->Displayed = sLoco;
	pBlk->ResetID = true;  		//Clear and write ID
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::SaveIDsClick(TObject *Sender)
{
	SavedTrainIDs->Clear();

	int N = Application->MessageBox(L"Do you want to save the current train IDs?", L"Pacific Southern", MB_YESNO);
	if(N == 6)
	{
		SaveID(&H30);   //Hyde
		SaveID(&H31);
		SaveID(&H32);
		SaveID(&H33);
		SaveID(&H34);
		SaveID(&H12);
		SaveID(&H22);
		SaveID(&H43);
		SaveID(&H42);
		SaveID(&H41);
		SaveID(&H40);

		SaveID(&Y53);   //Yard
		SaveID(&Y52);
		SaveID(&Y51);
		SaveID(&Y50);
		SaveID(&Y81);
		SaveID(&Y82);
		SaveID(&Y83);
		SaveID(&Y84);

		SaveID(&P7);    //Port
		SaveID(&P6);
		SaveID(&P5);
		SaveID(&P4);
		SaveID(&P3);
		SaveID(&P2);
		SaveID(&P1);
		SaveID(&P32);

		SaveID(&N31);   //Nassau
		SaveID(&N32);
		SaveID(&N41);
		SaveID(&N42);

		SaveID(&C44);   //Cliff
		SaveID(&C43);
		SaveID(&C42);
		SaveID(&C41);
		SaveID(&C40);
		SaveID(&C50);
		SaveID(&C51);
		SaveID(&C52);
		SaveID(&C53);
		SaveID(&C54);
		SaveID(&C30);
		SaveID(&C31);

		if(IDListA->Checked)
			SavedTrainIDs->Items->SaveToFile("C:/DispatcherTextFiles/TrainIDsA.txt");
		else if(IDListB->Checked)
			SavedTrainIDs->Items->SaveToFile("C:/DispatcherTextFiles/TrainIDsB.txt");
		else if(IDListC->Checked)
			SavedTrainIDs->Items->SaveToFile("C:/DispatcherTextFiles/TrainIDsC.txt");
	}
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::LoadIDsClick(TObject *Sender)
{
	ClearIDsClick(this);

	if(IDListA->Checked)
	{
		SavedTrainIDs->Items->LoadFromFile("C:/DispatcherTextFiles/TrainIDsA.txt");
		EditRoutes->RouteList->Items->LoadFromFile("C:/DispatcherTextFiles/RoutesA.txt");
	}
	else if(IDListB->Checked)
	{
		SavedTrainIDs->Items->LoadFromFile("C:/DispatcherTextFiles/TrainIDsB.txt");
		EditRoutes->RouteList->Items->LoadFromFile("C:/DispatcherTextFiles/RoutesB.txt");
	}
	else if(IDListC->Checked)
	{
		SavedTrainIDs->Items->LoadFromFile("C:/DispatcherTextFiles/TrainIDsC.txt");
		EditRoutes->RouteList->Items->LoadFromFile("C:/DispatcherTextFiles/RoutesC.txt");
	}

	int Num = SavedTrainIDs->GetCount();
	String L;
	String Block;
	String Train;
	BLOCK* pBlk;

	if(Num > 0)
	{
		for(int i = 0; i < Num; i++)
		{
			L = SavedTrainIDs->Items->Strings[i];
			Block = L.SubString(1, 6).TrimRight();
			Train = L.SubString(10, 7).TrimRight();
			pBlk = GetBlkPtr(Block);
			if(pBlk->Blk)
			{
				pBlk->Train = Train;
                pBlk->Displayed = sTrain;
				pBlk->ResetID = true;  		//Clear and write ID
			}
		}
	}
}
//---------------------------------------------------------------------------

void TPSRY::SaveID(BLOCK* pBlk)    //Save train IDs to file
{
	if(pBlk->Train != "")
	{
		String L = AnsiString::StringOfChar(' ', 20);
		L.Insert(pBlk->BlkID, 1);
		L.Insert(pBlk->Train, 10);
		SavedTrainIDs->Items->Append(L);
	}
}
//---------------------------------------------------------------------------

//Pacific Southern time clock

void __fastcall TPSRY::RealTimeClick(TObject *Sender)
{
	PSTime->Color = clWhite;
	RunStandbyButton->Enabled = false;
	SetButton->Enabled = false;
	DisplayTime();
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::PSRYTimeClick(TObject *Sender)
{
	PSTime->Color = clSilver;
	RunStandbyButton->Enabled = true;
	SetButton->Enabled = true;
	DisplayTime();
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::SetButtonClick(TObject *Sender)
{
	if(PSRYTime->Checked)
	{
	PSHours = StrToInt(Hours->Text);
	PSMinutes = StrToInt(Minutes->Text);
	DisplayTime();         //Here and on remotes
	}
}

//---------------------------------------------------------------------------

void __fastcall TPSRY::RunStandbyButtonClick(TObject *Sender)
{
	if(PSRYTime->Checked)
	{
		PSRYRun = !PSRYRun;
		if(PSRYRun)
			RunStandbyButton->Caption = "Stop";
		else
			RunStandbyButton->Caption = "Run";
	}
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::PSClockTimer(TObject *Sender)
{
	Colon = !Colon;

	if(PSRYRun)
	{
		if(PShsec == 60)
		{
			PShsec = 0;
			PSMinutes++;
			if(PSMinutes == 60)
			{
				PSMinutes = 0;
				PSHours++;
			}
			if(PSHours == 13)
			{
				PSHours = 1;
			}
		}
		else
		PShsec++;
	}
	if(PSRYTime->Checked)
	{
		DisplayHours = PSHours;
		DisplayMinutes = PSMinutes;
	}
	else if(RealTime->Checked)
	{
		char timebuf[9];
		_strtime(timebuf);
		String Time = timebuf;
		String Hours = Time.SubString(1, 2);
		String Minutes = Time.SubString(4, 2);
		DisplayHours = StrToInt(Hours);
		DisplayMinutes = StrToInt(Minutes);
		if(DisplayHours > 12)
		DisplayHours = DisplayHours - 12;
	}
	DisplayTime();

}
//---------------------------------------------------------------------------

void TPSRY :: DisplayTime(void)
{
	String HoursText;
	String MinutesText;

	if(DisplayHours > 9)
		HoursText = IntToStr(DisplayHours);
	else
		HoursText = " " + IntToStr(DisplayHours);
	if(DisplayMinutes > 9)
		MinutesText = IntToStr(DisplayMinutes);
	else
		MinutesText = "0" + IntToStr(DisplayMinutes);
	if(Colon)
		PSTime->Text = HoursText + " " + MinutesText;
	else
		PSTime->Text = HoursText + ":" + MinutesText;
	//Send to remotes
	String Message = AnsiString::StringOfChar(' ', 41);
	Message.Insert("PSClock", 1);
	Message.Insert(PSTime->Text, 10);
	Message.Insert("##", 40);
	Message = Message.TrimRight();
	MessageBuffer->Lines->Add(Message);
	RemDisMessageBuffer->Lines->Add(Message);
	WriteRemotes();
	WriteRemoteDispatcher();
}
//---------------------------------------------------------------------------

//Record I/O input changes for troubleshooting changes from glitches

void TPSRY::RecordChange(int Address, int ByteNo, char Old, char New)
{
	if(Changes->GetCount() > 100000)
		Changes->Clear();
	String L = AnsiString::StringOfChar(' ', 55);
	TDateTime* CTime = new TDateTime(Now());  // Store the current date and time.
	String T = CTime->FormatString("mm-d h:mm:ss:zzz AM/PM");   // Convert the time to a string.
	delete CTime;
	String A = NodeName(Address);   //Get name of node
	String OldByte = BinaryByte(Old);
	String NewByte = BinaryByte(New);
	L.Insert(A, 1);
	L.Insert(T, 18);
	L.Insert(ByteNo, 39);
	L.Insert(OldByte, 42);
	Changes->Items->Add("");
	Changes->Items->Add(L);
	L = AnsiString::StringOfChar(' ', 55);
	L.Insert(NewByte, 42);
	Changes->Items->Add(L);
}
//---------------------------------------------------------------------------

//Table for looking up I/O node names

String TPSRY::NodeName(int Address)
{
	if(Address == 0x11)
		return "11 Yard";
	else if(Address == 0x12)
		return "12 Kale";
	else if(Address == 0x13)
		return "13 East Jct";
	else if(Address == 0x14)
		return "14 Cornell Jct";
	else if(Address == 0x15)
		return "15 Yard Switches";
	else if(Address == 0x21)
		return "21 Parsons Jct";
	else if(Address == 0x22)
		return "22 Port A";
	else if(Address == 0x023)
		return "23 Port B";
	else if(Address == 0x31)
		return "31 Latham";
	else if(Address == 0x32)
		return "32 Carlton";
	else if(Address == 0x41)
		return "41 Dell";
	else if(Address == 0x42)
		return "42 Foss";
	else if(Address == 0x51)
		return "51 Hyde Jct";
	else if(Address == 0x52)
		return "52 Hyde";
	else if(Address == 0x61)
		return "61 Shore";
	else if(Address == 0x71)
		return "71 Krulish";
	else if(Address == 0x72)
		return "72 Nassau West";
	else if(Address == 0x73)
		return "73 Nassau East";
	else if(Address == 0x74)
		return "74 Nassau NX";
	else if(Address == 0x81)
		return "81 Bank";
	else if(Address == 0x91)
		return "91 Cliveden";
	else if(Address == 0x92)
		return "92 Green Mtn";
	else if(Address == 0x93)
		return "93 Cliff";
	else if(Address == 0x95)
		return "95 Sheffield";
	else
		return "XX Fault";
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::IOChangesClick(TObject *Sender)
{
	if(Changes->Visible)
		Changes->Visible = false;
	else
		Changes->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::ChangesClick(TObject *Sender)
{
	int N = Application->MessageBox(L"Do you want to clear the Changes list?", L"Pacific Southern", MB_YESNO);
	if(N == 6)
		Changes->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::RefreshScreenClick(TObject *Sender)
{
	HyYdPt.Refresh = true;
	LaKr.Refresh = true;
	NaCf.Refresh = true;
}
//---------------------------------------------------------------------------
void TPSRY::TimeLog(int Num)
{
	TDateTime* CTime = new TDateTime(Now());  // Store the current date and time.
	String T = CTime->FormatString("mm-d h:mm:ss:zzz AM/PM");   // Convert the time to a string.
	delete CTime;
	Changes->Items->Add("");
	Changes->Items->Add(T + " " + IntToStr(Num));
}
//---------------------------------------------------------------------------

//Sending click info to remote dispatcher

void __fastcall TPSRY::CBActiveClick(TObject *Sender)                //Active list
{
	MessageToRemDis("cbActive", BoolToStr(CBActive->Checked));
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::CBATCClick(TObject *Sender)
{
	MessageToRemDis("cbATC", BoolToStr(CBATC->Checked));
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::cbRTCClick(TObject *Sender)
{
	MessageToRemDis("cbRTC", BoolToStr(cbRTC->Checked));
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::DispatcherControlClick(TObject *Sender)      //Signals 4 at Latham
{
	MessageToRemDis("DisCtrl", "True");
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::PortControlClick(TObject *Sender)
{
	MessageToRemDis("PtCtrl", "True");
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::RBNassauClick(TObject *Sender)               //Nassau control
{
	MessageToRemDis("NaAll", "True");
											  //set signals normal
	USSFltNormal(NaCf.USSCol[0].pCol);      //fleet 12
	USSSigNormal(NaCf.USSCol[1].pCol);      //signal 14
	USSSigNormal(NaCf.USSCol[2].pCol);      //signal 16
	USSSigNormal(NaCf.USSCol[3].pCol);      //signal 18
	USSSigNormal(NaCf.USSCol[4].pCol);      //signal 29
	USSSigNormal(NaCf.USSCol[6].pCol);      //signal 24
	USSSigNormal(NaCf.USSCol[7].pCol);      //signal 26
	USSSigNormal(NaCf.USSCol[8].pCol);      //signal 28

}
//---------------------------------------------------------------------------

void __fastcall TPSRY::RBNDispatcherMainClick(TObject *Sender)
{
	MessageToRemDis("DMain", "True");
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::RBNDispatcherAllClick(TObject *Sender)
{
	MessageToRemDis("DAll", "True");
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::HydeFleetOnClick(TObject *Sender)
{
	MessageToRemDis("HyFltOn", BoolToStr(HydeFleetOn->Checked));
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::RBCliffClick(TObject *Sender)     //Cliff control
{                                                        //Auto routes in ClivedenUnit.cpp
	MessageToRemDis("Cliff", "True");
											//set levers normal
	USSSigNormal(NaCf.USSCol[13].pCol);      //signal 24
	CSw23.L = false;
	USSSwNormal(NaCf.USSCol[14].pCol);      //switch 23
	USSSigNormal(NaCf.USSCol[14].pCol);      //signal 22
	USSSwNormal(NaCf.USSCol[15].pCol);      //switch 21
	USSSwNormal(NaCf.USSCol[16].pCol);      //switch 19
	USSSigNormal(NaCf.USSCol[16].pCol);      //signal 18
	CSw17.L = false;
	USSSwNormal(NaCf.USSCol[17].pCol);      //switch 17
	USSFltNormal(NaCf.USSCol[17].pCol);      //fleet 16
	USSSwNormal(NaCf.USSCol[18].pCol);      //switch 15
	USSSigNormal(NaCf.USSCol[18].pCol);      //signal 14
	CSw13.L = false;
	USSSwNormal(NaCf.USSCol[19].pCol);      //switch 13
	USSSigNormal(NaCf.USSCol[19].pCol);      //signal 12
	USSSwNormal(NaCf.USSCol[20].pCol);      //switch 11
	USSSigNormal(NaCf.USSCol[20].pCol);      //signal 10
	CSw9.L = false;
	USSSwNormal(NaCf.USSCol[21].pCol);      //switch 9
	USSSigNormal(NaCf.USSCol[21].pCol);      //signal 8
	USSSigNormal(NaCf.USSCol[22].pCol);      //signal 6
	USSSigNormal(NaCf.USSCol[23].pCol);      //signal 4
	USSSwNormal(NaCf.USSCol[24].pCol);      //switch 3
	USSSigNormal(NaCf.USSCol[24].pCol);      //signal 2
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::RBDispatcherBkClClick(TObject *Sender)
{
	MessageToRemDis("DBaCl", "True");
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::RBDispatcherAllClick(TObject *Sender)
{
	MessageToRemDis("DBaClCf", "True");
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::RBYardClick(TObject *Sender)            //Yard control
{
	MessageToRemDis("rbYard", "True");
	YSigL2.N = YSigL4.N = true;
	YSigL2.L = YSigL2.R = YSigL4.L = YSigL4.R = false;
	YSigL8.N = YSigL10.N = true;
	YSigL8.L = YSigL8.R = YSigL10.L = YSigL10.R = false;
	YSigL22.N = YSigL24.N = YSigL26.N = true;
	YSigL22.L = YSigL22.R = YSigL24.L = YSigL24.R = YSigL26.L = YSigL26.R = false;
	YSigL34.N = YSigL40.N = YSigL42.N = true;
    YSigL34.L = YSigL34.R = YSigL40.L = YSigL40.R = YSigL42.L = YSigL42.R = false;
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::RBYDispatcherClick(TObject *Sender)
{
	MessageToRemDis("rbYDis", "True");
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::YardFleetOnClick(TObject *Sender)
{
	MessageToRemDis("YdFlt", BoolToStr(YardFleetOn->Checked));
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::PortFleetOnClick(TObject *Sender)
{
	MessageToRemDis("PtFlt", BoolToStr(PortFleetOn->Checked));
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::CliffFleetOnClick(TObject *Sender)
{
	MessageToRemDis("ClFlt", BoolToStr(CliffFleetOn->Checked));
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::HyInOnClick(TObject *Sender)
{
	MessageToRemDis("HyInOn", "True");
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::HyInOffClick(TObject *Sender)
{
	MessageToRemDis("HyInOff", "True");
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::DSROnClick(TObject *Sender)
{
	MessageToRemDis("DSROn", "True");
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::DSROffClick(TObject *Sender)
{
	MessageToRemDis("DSROff", "True");
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::H30InclClick(TObject *Sender)
{
	MessageToRemDis("H30Incl", BoolToStr(H30Incl->Checked));
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::NaOnClick(TObject *Sender)
{
	MessageToRemDis("NaOn", BoolToStr(NaOn->Checked));
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::NaOffClick(TObject *Sender)
{
	MessageToRemDis("NaOff", BoolToStr(NaOff->Checked));
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::C31InclClick(TObject *Sender)
{
	MessageToRemDis("C31Incl", BoolToStr(C31Incl->Checked));
}
//---------------------------------------------------------------------------

void TPSRY::Testing(void)
{
	CheckBoxes->Visible = true;   //check boxes for testing

	// = CB1->Checked;
	// = CB2->Checked;
	// = CB3->Checked;
	// = CB4->Checked;
	// = CB5->Checked;


//--------------------------------------------------------------------------------

//Switch positions

	YSw33.NI = YSw33.N; YSw33.RI = YSw33.R;  //Kale west

	YSw17.NI = YSw17.N; YSw17.RI = YSw17.R;  //Kale
	YSw19.NI = YSw19.N; YSw19.RI = YSw19.R;
	YSw21.NI = YSw21.N; YSw21.RI = YSw21.R;
	YSw23.NI = YSw23.N; YSw23.RI = YSw23.R;
	YSw25.NI = YSw25.N; YSw25.RI = YSw25.R;
	YSw27.NI = YSw27.N; YSw27.RI = YSw27.R;
	YSw29.NI = YSw29.N; YSw29.RI = YSw29.R;

	if(SBY81W) {Y81W = true; Y82W = Y83W = Y84W = false;}    //Waterman west
	else if(SBY82W) {Y82W = true; Y81W = Y83W = Y84W = false;}
	else if(SBY83W) {Y83W = true; Y81W = Y82W = Y84W = false;}
	else if(SBY84W) {Y84W = true; Y81W = Y82W = Y83W = false;}
	WOS1Norm = true;

	if(SBY81E) {Y81E = true; Y82E = Y83E = Y84E = false;}    //Waterman east
	else if(SBY82E) {Y82E = true; Y81E = Y83E = Y84E = false;}
	else if(SBY83E) {Y83E = true; Y81E = Y82E = Y84E = false;}
	else if(SBY84E) {Y84E = true; Y81E = Y82E = Y83E = false;}

	YSw7.NI = YSw7.N; YSw7.RI = YSw7.R;  //East End Jct
	YSw9.NI = YSw9.N; YSw9.RI = YSw9.R;
	YSw11.NI = YSw11.N; YSw11.RI = YSw11.R;

	YSw1.NI = YSw1.N; YSw1.RI = YSw1.R;  // Cornell Jct
	YSw3.NI = YSw3.N; YSw3.RI = YSw3.R;

	LSw1.NI = LSw1.N,  LSw1.RI = LSw1.R;  // Latham Jct
	LSw3.NI = LSw3.N,  LSw3.RI = LSw3.R;
	LSw5.NI = LSw5.N,  LSw5.RI = LSw5.R;
	LSw7.NI = LSw7.N,  LSw7.RI = LSw7.R;
	LSw9.NI = LSw9.N,  LSw9.RI = LSw9.R;

	LSw15.NI = LSw15.N,  LSw15.RI = LSw15.R;     //Carlton
	LSw17.NI = LSw17.N,  LSw17.RI = LSw17.R;

	DSw1.NI = DSw1.N;  DSw1.RI = DSw1.R;          // Valley Jct.
	DSw3.NI = DSw3.N;  DSw3.RI = DSw3.R;
	DSw5.NI = DSw5.N;  DSw5.RI = DSw5.R;
	DSw7.NI = DSw7.N;  DSw7.RI = DSw7.R;

	DSw11.NI = DSw11.N;  DSw11.RI = DSw11.R;    //Foss

	SSw3.NI = SSw3.N;  SSw3.RI = SSw3.R;       //River Jct.
	SSw5.NI = SSw5.N;  SSw5.RI = SSw5.R;
	SSw7.NI = SSw7.N;  SSw7.RI = SSw7.R;
	SSw9.NI = SSw9.N;  SSw9.RI = SSw9.R;
	SSw11.NI = SSw11.N;  SSw11.RI = SSw11.R;
	SSw13.NI = SSw13.N;  SSw13.RI = SSw13.R;

	SSw15.NI = SSw15.N;  SSw15.RI = SSw15.R;   //Hyde Jct.
	SSw17.NI = SSw17.N;  SSw17.RI = SSw17.R;
	SSw19.NI = SSw19.N;  SSw19.RI = SSw19.R;

	KSw1.NI = KSw1.N;  KSw1.RI = KSw1.R;       //Krulish Jct.
	KSw3.NI = KSw3.N;  KSw3.RI = KSw3.R;
	KSw5.NI = KSw5.N;  KSw5.RI = KSw5.R;
	KSw7.NI = KSw7.N;  KSw7.RI = KSw7.R;

	if(SBH31E) {H31E = true; H32E = H33E = H34E = H12E = false;}  //Hyde
	else if(SBH32E) {H32E = true; H31E = H33E = H34E = H12E = false;}
	else if(SBH33E) {H33E = true; H31E = H32E = H34E = H12E = false;}
	else if(SBH34E) {H34E = true; H31E = H32E = H33E = H12E = false;}
	else if(SBH12E) {H12E = true; H31E = H32E = H33E = H34E = false;}

	if(SBH22E) {H22E = true; H40E = H41E = H42E = H43E = false;}
	else if(SBH40E) {H40E = true; H22E = H41E = H42E = H43E = false;}
	else if(SBH41E) {H41E = true; H22E = H40E = H42E = H43E = false;}
	else if(SBH42E) {H42E = true; H22E = H40E = H41E = H43E = false;}
	else if(SBH43E) {H43E = true; H22E = H40E = H41E = H42E = false;}

	if(SBH22W) {H22W = true; H41W = H42W = H43W = false;}
	else if(SBH41W) {H41W = true; H22W = H42W = H43W = false;}
	else if(SBH42W) {H42W = true; H22W = H41W = H43W = false;}
	else if(SBH43W) {H43W = true; H22W = H41W = H42W = false;}

	if(SBH31W) {H31W = true; H30E = H32W = H33W = H34W = H12W = false;}
	else if(SBH32W) {H32W = H30E = true; H31W = H33W = H34W = H12W = false;}
	else if(SBH33W) {H33W = true; H31W = H32W = H34W = H12W = false;}
	else if(SBH34W) {H34W = true; H31W = H32W = H33W = H12W = false;}
	else if(SBH12W) {H12W = true; H31W = H32W = H33W = H34W = false;}
	else if(SBH30E) {H30E = H32W = true; H31W = false;}


	if(NXBtnT12 && NXBtnW10 && !NWSL1) {NSw25.NI = true; NSw25.RI = false;}       //Nassau West

	if(NXBtnN60 && NXBtnW10 && !NWSL1 && !NWSL2){
		NSw27.NI = NSw21.NI = NSw23.RI = NSw25.RI = true;
		NSw27.RI = NSw21.RI = NSw23.NI = NSw25.NI = false;}
	else if(NXBtnN60 && NXBtnN32W && !NWSL2)
		{NSw27.NI = NSw21.NI = NSw23.RI = NSw25.NI = true;
		 NSw27.RI = NSw21.RI = NSw23.NI = NSw25.RI = false;}
	else if(NXBtnN60 && NXBtnN31W && !NWSL2)
		{NSw27.NI = NSw21.NI = NSw23.NI = true;
			NSw27.RI = NSw21.RI = NSw23.RI = false;}
	else if(NXBtnN60 && NXBtnN12W && !NWSL2 && !NWSL3)
		{NSw27.RI = NSw29.NI = NSw21.NI = true;
			NSw27.NI = NSw29.RI = NSw21.RI = false;}
	else if(NXBtnN60 && NXBtnN22W && !NWSL2 && !NWSL3 && !NWSL4)
		{NSw27.RI = NSw29.RI = NSw31.NI = true;
			NSw27.NI = NSw29.NI = NSw31.RI = false;}
	else if(NXBtnN60 && NXBtnN41W && !NWSL2 && !NWSL3 && !NWSL4)
		{NSw27.RI = NSw29.RI = NSw31.RI = NSw33.RI = true;
			NSw27.NI = NSw29.NI = NSw31.NI = NSw33.NI = false;}
	else if(NXBtnN60 && NXBtnN42W && !NWSL2 && !NWSL3 && !NWSL4)
		{NSw27.RI = NSw29.RI = NSw31.RI = NSw33.NI = NSw35.RI = true;
			NSw27.NI = NSw29.NI = NSw31.NI = NSw33.RI = NSw35.NI = false;}
	else if(NXBtnN60 && NXBtnW20W && !NWSL2 && !NWSL3 && !NWSL4)
		{NSw27.RI = NSw29.RI = NSw31.RI = NSw33.NI = NSw35.NI = true;
			NSw27.NI = NSw29.NI = NSw31.NI = NSw33.RI = NSw35.RI = false;}

	if(NXBtnN11 && NXBtnW10 && !NWSL1 && !NWSL2 && !NWSL3)
		{NSw19.NI = NSw27.NI = NSw29.NI = NSw21.RI = NSw23.RI = NSw25.RI = true;
			NSw19.RI = NSw27.RI = NSw29.RI = NSw21.NI = NSw23.NI = NSw25.NI = false;}
	else if(NXBtnN11 && NXBtnN32W && !NWSL2 && !NWSL3)
		{NSw19.NI = NSw27.NI = NSw29.NI = NSw21.RI = NSw23.RI = NSw25.NI = true;
			NSw19.RI = NSw27.RI = NSw29.RI = NSw21.NI = NSw23.NI = NSw25.RI = false;}
	else if(NXBtnN11 && NXBtnN31W && !NWSL2 && !NWSL3)
		{NSw19.NI = NSw27.NI = NSw29.NI = NSw21.RI = NSw23.NI = true;
			NSw19.RI = NSw27.RI = NSw29.RI = NSw21.NI = NSw23.RI = false;}
	else if(NXBtnN11 && NXBtnN12W && !NWSL3)
		{NSw19.NI = NSw27.NI = NSw29.NI = NSw21.NI = true;
			NSw19.RI = NSw27.RI = NSw29.RI = NSw21.RI = false;}
	else if(NXBtnN11 && NXBtnN22W && !NWSL3 && !NWSL4)
		{NSw19.NI = NSw27.NI = NSw29.RI = NSw31.NI = true;
			NSw19.RI = NSw27.RI = NSw29.NI = NSw31.RI = false;}
	else if(NXBtnN11 && NXBtnN41W && !NWSL3 && !NWSL4)
		{NSw19.NI = NSw27.NI = NSw29.RI = NSw31.RI = NSw33.RI = true;
			NSw19.RI = NSw27.RI = NSw29.NI = NSw31.NI = NSw33.NI = false;}
	else if(NXBtnN11 && NXBtnN42W && !NWSL3 && !NWSL4)
		{NSw19.NI = NSw27.NI = NSw29.RI = NSw31.RI = NSw33.NI = NSw35.RI = true;
			NSw19.RI = NSw27.RI = NSw29.NI = NSw31.NI = NSw33.RI = NSw35.NI = false;}
	else if(NXBtnN11 && NXBtnW20W && !NWSL3 && !NWSL4)
		{NSw19.NI = NSw27.NI = NSw29.RI = NSw31.RI = NSw33.NI = NSw35.NI = true;
			NSw19.RI = NSw27.RI = NSw29.NI = NSw31.NI = NSw33.RI = NSw35.RI = false;}

	if(NXBtnN21 && NXBtnW10 && !NWSL1 && !NWSL2 && !NWSL3 && !NWSL4)
		{NSw19.RI = NSw27.NI = NSw29.NI = NSw21.RI = NSw23.RI = NSw25.RI = true;
			NSw19.NI = NSw27.RI = NSw29.RI = NSw21.NI = NSw23.NI = NSw25.NI = false;}
	else if(NXBtnN21 && NXBtnN32W && !NWSL2 && !NWSL3 && !NWSL4)
		{NSw19.RI = NSw27.NI = NSw29.NI = NSw21.RI = NSw23.RI = NSw25.NI = true;
			NSw19.NI = NSw27.RI = NSw29.RI = NSw21.NI = NSw23.NI = NSw25.RI = false;}
	else if(NXBtnN21 && NXBtnN31W && !NWSL2 && !NWSL3 && !NWSL4)
		{NSw19.RI = NSw27.NI = NSw29.NI = NSw21.RI = NSw23.NI = true;
			NSw19.NI = NSw27.RI = NSw29.RI = NSw21.NI = NSw23.RI = false;}
	else if(NXBtnN21 && NXBtnN12W && !NWSL3 && !NWSL4)
		{NSw19.RI = NSw27.NI = NSw29.NI = NSw21.NI = true;
			NSw19.NI = NSw27.RI = NSw29.RI = NSw21.RI = false;}
	else if(NXBtnN21 && NXBtnN22W && !NWSL4)
		{NSw19.NI = NSw29.NI = NSw31.NI = true;
			NSw19.RI = NSw29.RI = NSw31.RI = false;}
	else if(NXBtnN21 && NXBtnN41W && !NWSL4)
		{NSw19.NI = NSw29.NI = NSw31.RI = NSw33.RI = true;
			NSw19.RI = NSw29.RI = NSw31.NI = NSw33.NI = false;}
	else if(NXBtnN21 && NXBtnN42W && !NWSL4)
		{NSw19.NI = NSw29.NI = NSw31.RI = NSw33.NI = NSw35.RI = true;
			NSw19.RI = NSw29.RI = NSw31.NI = NSw33.RI = NSw35.NI = false;}
	else if(NXBtnN21 && NXBtnW20W && !NWSL4)
		{NSw19.NI = NSw29.NI = NSw31.RI = NSw33.NI = NSw35.NI = true;
			NSw19.RI = NSw29.RI = NSw31.NI = NSw33.RI = NSw35.RI = false;}

	if(NXBtnW11 && NXBtnR10 && !NESL1){         //Nassau East
		NSw55.NI = NSw47.NI = true;
		NSw55.RI = NSw47.RI = false;}
	else if(NXBtnW11 && NXBtnB10 && !NESL1 && !NESL2){
		NSw55.RI = NSw45.NI = NSw47.NI = NSw57.NI = true;
		NSw55.NI = NSw45.RI = NSw47.RI = NSw57.RI = false;}
	else if(NXBtnW11 && NXBtnB20 && !NESL1 && !NESL2 && !NESL3){
		NSw55.RI = NSw45.NI = NSw47.NI = NSw57.RI = true;
		NSw55.NI = NSw45.RI = NSw47.RI = NSw57.NI = false;}

	if(NXBtnN32E && NXBtnR10 && !NESL1 && !NESL2){
		NSw51.NI = NSw53.RI = NSw55.NI = NSw45.NI = NSw47.RI = true;
		NSw51.RI = NSw53.NI = NSw55.RI = NSw45.RI = NSw47.NI = false;}
	else if(NXBtnN32E && NXBtnB10 && !NESL2){
		NSw51.NI = NSw53.RI = NSw55.NI = NSw45.NI = NSw47.NI = NSw57.NI = true;
		NSw51.RI = NSw53.NI = NSw55.RI = NSw45.RI = NSw47.RI = NSw57.RI = false;}
	else if(NXBtnN32E && NXBtnB20 && !NESL2  && !NESL3){
		NSw51.NI = NSw53.RI = NSw55.NI = NSw45.NI = NSw47.NI = NSw57.RI = true;
		NSw51.RI = NSw53.NI = NSw55.RI = NSw45.RI = NSw47.RI = NSw57.NI = false;}

	if(NXBtnN31E && NXBtnR10 && !NESL1 && !NESL2){
		NSw51.RI = NSw53.RI = NSw55.NI = NSw45.NI = NSw47.RI = true;
		NSw51.NI = NSw53.NI = NSw55.RI = NSw45.RI = NSw47.NI = false;}
	else if(NXBtnN31E && NXBtnB10 && !NESL2){
		NSw51.RI = NSw53.RI = NSw55.NI = NSw45.NI = NSw47.NI = NSw57.NI = true;
		NSw51.NI = NSw53.NI = NSw55.RI = NSw45.RI = NSw47.RI = NSw57.RI = false;}
	else if(NXBtnN31E && NXBtnB20 && !NESL2 && !NESL3){
		NSw51.RI = NSw53.RI = NSw55.NI = NSw45.NI = NSw47.NI = NSw57.RI = true;
		NSw51.NI = NSw53.NI = NSw55.RI = NSw45.RI = NSw47.RI = NSw57.NI = false;}

	if(NXBtnN12E && NXBtnR10 && !NESL1 && !NESL2){
		NSw53.NI = NSw55.NI = NSw45.NI = NSw47.RI = true;
		NSw53.RI = NSw55.RI = NSw45.RI = NSw47.NI = false;}
	else if(NXBtnN12E && NXBtnB10 && !NESL2){
		NSw53.NI = NSw55.NI = NSw45.NI = NSw47.NI = NSw57.NI = true;
		NSw53.RI = NSw55.RI = NSw45.RI = NSw47.RI = NSw57.RI = false;}
	else if(NXBtnN12E && NXBtnB20 && !NESL2 && !NESL3){
		NSw53.NI = NSw55.NI = NSw45.NI = NSw47.NI = NSw57.RI = true;
		NSw53.RI = NSw55.RI = NSw45.RI = NSw47.RI = NSw57.NI = false;}

	if(NXBtnN22E && NXBtnR10 && !NESL1 && !NESL2 && !NESL3){
		NSw43.NI = NSw45.RI = NSw47.RI = true;
		NSw43.RI = NSw45.NI = NSw47.NI = false;}
	else if(NXBtnN22E && NXBtnB10 && !NESL2 && !NESL3){
		NSw43.NI = NSw45.RI = NSw47.NI = NSw57.NI = true;
		NSw43.RI = NSw45.NI = NSw47.RI = NSw57.RI = false;}
	else if(NXBtnN22E && NXBtnB20 && !NESL3){
		NSw43.NI = NSw45.NI = NSw57.NI = true;
		NSw43.RI = NSw45.RI = NSw57.RI = false;}

	if(NXBtnN41E && NXBtnR10 && !NESL1 && !NESL2 && !NESL3){
		NSw41.RI = NSw43.RI = NSw45.RI = NSw47.RI = true;
		NSw41.NI = NSw43.NI = NSw45.NI = NSw47.NI = false;}
	else if(NXBtnN41E && NXBtnB10 && !NESL2 && !NESL3){
		NSw41.RI = NSw43.RI = NSw45.RI = NSw47.NI = NSw57.NI = true;
		NSw41.NI = NSw43.NI = NSw45.NI = NSw47.RI = NSw57.RI = false;}
	else if(NXBtnN41E && NXBtnB20 && !NESL3){
		NSw41.RI = NSw43.RI = NSw45.NI = NSw57.NI = true;
		NSw41.NI = NSw43.NI = NSw45.RI = NSw57.RI = false;}

	if(NXBtnN42E && NXBtnR10 && !NESL1 && !NESL2 && !NESL3){
		NSw39.RI = NSw41.NI = NSw43.RI = NSw45.RI = NSw47.RI = true;
		NSw39.NI = NSw41.RI = NSw43.NI = NSw45.NI = NSw47.NI = false;}
	else if(NXBtnN42E && NXBtnB10 && !NESL2 && !NESL3){
		NSw39.RI = NSw41.NI = NSw43.RI = NSw45.RI = NSw47.NI = NSw57.NI = true;
		NSw39.NI = NSw41.RI = NSw43.NI = NSw45.NI = NSw47.RI = NSw57.RI = false;}
	else if(NXBtnN42E && NXBtnB20 && !NESL3){
		NSw39.RI = NSw41.NI = NSw43.RI = NSw45.NI = NSw57.NI = true;
		NSw39.NI = NSw41.RI = NSw43.NI = NSw45.RI = NSw57.RI = false;}

	if(NXBtnW20E && NXBtnR10 && !NESL1 && !NESL2 && !NESL3){
		NSw39.NI = NSw41.NI = NSw43.RI = NSw45.RI = NSw47.RI = true;
		NSw39.RI = NSw41.RI = NSw43.NI = NSw45.NI = NSw47.NI = false;}
	else if(NXBtnW20E && NXBtnB10 && !NESL2 && !NESL3){
		NSw39.NI = NSw41.NI = NSw43.RI = NSw45.RI = NSw47.NI = NSw57.NI = true;
		NSw39.RI = NSw41.RI = NSw43.NI = NSw45.NI = NSw47.RI = NSw57.RI = false;}
	else if(NXBtnW20E && NXBtnB20 && !NESL3){
 		NSw39.NI = NSw41.NI = NSw43.RI = NSw45.NI = NSw57.NI = true;
		NSw39.RI = NSw41.RI = NSw43.NI = NSw45.RI = NSw57.RI = false;}

	if(RBDispatcherBkCl->Checked || RBDispatcherAll->Checked)
	{
		CSw23.NI = CSw23.N;  CSw23.RI = CSw23.R;   //Bank/Cliveden
		CSw17.NI = CSw17.N;  CSw17.RI = CSw17.R;
		CSw13.NI = CSw13.N;  CSw13.RI = CSw13.R;
		CSw9.NI = CSw9.N;  CSw9.RI = CSw9.R;
	}
	if(RBDispatcherAll->Checked)
	{
		if(SBG21W) {G21W = true; C10W = C30W = C31W = false;}   //GM West
		else if(SBC10W) {C10W = true; G21W = C30W = C31W = false;}
		else if(SBC30W) {C30W = true; G21W = C10W = C31W = false;}
		else if(SBC31W) {C31W = true; G21W = C10W = C30W = false;}

		if(SBG12E) {G12E = true; G10E = C10E = C30E = false;}   //GM East
		else if(SBG10E) {G10E = true; G12E = C10E = C30E = false;}
		else if(SBC10E) {C10E = true; G12E = G10E = C30E = false;}
		else if(SBC30E) {C30E = true; G12E = G10E = C10E = false;}
																		//Sheffield West
		if(SBC44E) {C44W = true; C43W = C42W = C41W = C40W = C21W = C50W = C51W = C52W = C53W = C54W = false;}
		else if(SBC43E) {C43W = true; C44W = C42W = C41W = C40W = C21W = C50W = C51W = C52W = C53W = C54W = false;}
		else if(SBC42E) {C42W = true; C44W = C43W = C41W = C40W = C21W = C50W = C51W = C52W = C53W = C54W = false;}
		else if(SBC41E) {C41W = true; C44W = C43W = C42W = C40W = C21W = C50W = C51W = C52W = C53W = C54W = false;}
		else if(SBC40E) {C40W = true; C44W = C43W = C42W = C41W = C21W = C50W = C51W = C52W = C53W = C54W = false;}
		else if(SBC21E) {C21W = true; C44W = C43W = C42W = C41W = C40W = C50W = C51W = C52W = C53W = C54W = false;}
		else if(SBC50E) {C50W = true; C44W = C43W = C42W = C41W = C40W = C21W = C51W = C52W = C53W = C54W = false;}
		else if(SBC51E) {C51W = true; C44W = C43W = C42W = C41W = C40W = C21W = C50W = C52W = C53W = C54W = false;}
		else if(SBC52E) {C52W = true; C44W = C43W = C42W = C41W = C40W = C21W = C50W = C51W = C53W = C54W = false;}
		else if(SBC53E) {C53W = true; C44W = C43W = C42W = C41W = C40W = C21W = C50W = C51W = C52W = C54W = false;}
		else if(SBC54E) {C54W = true; C44W = C43W = C42W = C41W = C40W = C21W = C50W = C51W = C52W = C53W = false;}

															//Sheffield East
		if(SBC44W) {C44E = true; C43E = C42E = C41E = C40E = C21E = C50E = C51E = C52E = C53E = C54E = false;}
		else if(SBC43W) {C43E = true; C44E = C42E = C41E = C40E = C21E = C50E = C51E = C52E = C53E = C54E = false;}
		else if(SBC42W) {C42E = true; C44E = C43E = C41E = C40E = C21E = C50E = C51E = C52E = C53E = C54E = false;}
		else if(SBC41W) {C41E = true; C44E = C43E = C42E = C40E = C21E = C50E = C51E = C52E = C53E = C54E = false;}
		else if(SBC40W) {C40E = true; C44E = C43E = C42E = C41E = C21E = C50E = C51E = C52E = C53E = C54E = false;}
		else if(SBC21W) {C21E = true; C44E = C43E = C42E = C41E = C40E = C50E = C51E = C52E = C53E = C54E = false;}
		else if(SBC50W) {C50E = true; C44E = C43E = C42E = C41E = C40E = C21E = C51E = C52E = C53E = C54E = false;}
		else if(SBC51W) {C51E = true; C44E = C43E = C42E = C41E = C40E = C21E = C50E = C52E = C53E = C54E = false;}
		else if(SBC52W) {C52E = true; C44E = C43E = C42E = C41E = C40E = C21E = C50E = C51E = C53E = C54E = false;}
		else if(SBC53W) {C53E = true; C44E = C43E = C42E = C41E = C40E = C21E = C50E = C51E = C52E = C54E = false;}
		else if(SBC54W) {C54E = true; C44E = C43E = C42E = C41E = C40E = C21E = C50E = C51E = C52E = C53E = false;}
	}

}
//---------------------------------------------------------------------------

 String TPSRY::GetRouteState(STATE State)
 {
	if(State == Idle)
		return "Idle";
	else if(State == SigsNormal)
		return "Signals Normal";
	else if(State == Pause)
		return "Pause";
	else if(State == Setting)
		return "Setting Route";
	else if(State == SigsCleared)
		return "Signals Cleared";
	else if(State == Running)
		return "Running";
	else if(State == RunningX)
		return "Still Running";
 }
 //---------------------------------------------------------------------------

void __fastcall TPSRY::TestModeOnClick(TObject *Sender)
{
	int X = Application->MessageBox(L"Start in Test Mode?", L"Pacific Southern", MB_YESNO);
	if(X == 6)
	{
		InTestMode = true;
		StartClick(this);
	}
	else
	{
		InTestMode = false;
		TestModeOff->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::TestModeOffClick(TObject *Sender)
{
	InTestMode = false;
}

//---------------------------------------------------------------------------

void __fastcall TPSRY::RouteStatesClick(TObject *Sender)
{
	if(RouteData->Visible)
		RouteData->Visible = false;
	else
        RouteData->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::F11InclClick(TObject *Sender)
{
	MessageToRemDis("F11Incl", BoolToStr(F11Incl->Checked));
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::IDListAClick(TObject *Sender)
{
	MessageToRemDis("IDListA", BoolToStr(IDListA->Checked));
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::IDListBClick(TObject *Sender)
{
	MessageToRemDis("IDListB", BoolToStr(IDListB->Checked));
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::IDListCClick(TObject *Sender)
{
	MessageToRemDis("IDListC", BoolToStr(IDListC->Checked));
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::OffBtnClick(TObject *Sender)
{
	BLOCK* pBlk = GetBlkPtr(BlockID->Text);
	ATCMonOff(pBlk);
	Train->SetFocus();
}
//---------------------------------------------------------------------------




void __fastcall TPSRY::rbForClick(TObject *Sender)
{
	if(pSelectedLoco->StopButton)
	{
		pSelectedLoco->DCCDir = true;
		BLOCK* pBlk = GetBlkPtr(pSelectedLoco->Block);
		pBlk->DirTxt = "For";
		pSelectedLoco->DirText = "For";
	}
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::fbRevClick(TObject *Sender)
{
	if(pSelectedLoco->StopButton)
	{
		pSelectedLoco->DCCDir = false;
		BLOCK* pBlk = GetBlkPtr(pSelectedLoco->Block);
		pBlk->DirTxt = "Rev";
		pSelectedLoco->DirText = "Rev";
	}
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::P32InclClick(TObject *Sender)
{
	MessageToRemDis("P32Incl", BoolToStr(P32Incl->Checked));
}
//---------------------------------------------------------------------------





void __fastcall TPSRY::bnLeftClick(TObject *Sender)
{
	PSRY->Left = -8;
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::bnRightClick(TObject *Sender)
{
    PSRY->Left = -5128;
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::lfCenterClick(TObject *Sender)
{
    PSRY->Left = -2567;
}
//---------------------------------------------------------------------------

void __fastcall TPSRY::rtCenterClick(TObject *Sender)
{
    PSRY->Left = -2568;
}
//---------------------------------------------------------------------------

