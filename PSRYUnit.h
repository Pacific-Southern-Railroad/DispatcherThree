//---------------------------------------------------------------------------

#ifndef PSRYUnitH
#define PSRYUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <System.ImageList.hpp>
#include <System.Win.ScktComp.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>

//Global declarations--------------------------------------------------------

const int YARD = 0x11;
const int KALE = 0x12;
const int EASTJCT = 0x13;
const int CORNELL = 0x14;
const int YARDSW = 0x15;
const int PARSONS = 0x21;
const int PORTA = 0x22;
const int PORTB = 0x23;
const int LATHAM = 0x31;
const int CARLTON = 0x32;
const int DELL = 0x41;
const int FOSS = 0x42;
const int HYDEJCT = 0x51;
const int HYDE = 0x52;
const int SHORE = 0x61;
const int KRULISH = 0x71;
const int NASSAUW = 0x72;
const int NASSAUE = 0x73;
const int NASSAUNX = 0x74;
const int BANK = 0x81;
const int CLIVEDEN = 0x91;
const int GREENMTN = 0x92;
const int CLIFF = 0x93;
const int SHEFFIELD = 0x95;

const int Cols = 160;
const int Rows = 39;
const int HtWd = 16;

const int Pulses = 240;

//Structure and union for bits in I/O bytes

struct BITS
{
	unsigned int b0 : 1;
	unsigned int b1 : 1;
	unsigned int b2 : 1;
	unsigned int b3 : 1;
	unsigned int b4 : 1;
	unsigned int b5 : 1;
	unsigned int b6 : 1;
	unsigned int b7 : 1;
};

union IOBYTE
{
	BITS bit;
	char byte;
};

struct BYTES
{
   char c0;
   char c1;
};

union IONUM
{
   int hlBytes;
   BYTES byte;
};

//Enumerations

enum IDSTATE {Off, Clearing, Cleared, Writing, Preview, On};              //ID States
enum IDSHOW {sTrain, sLoco, sNone};                                      //Shown on ID
enum BTYPE {Blk, DBlk, RDBlk, AnnunE, AnnunW, OSE, OSW, Yd};             //Block types
enum ROUTE {Nil, Restricting, Slow, Diverging, Main};                    //Route types
//enum DISPLAY {HYYDPT, LAKR, NACF};                                       //Screen displayed
enum STATE {Idle, Blocked, SigsNormal, Setting, SetFleet, Pause, SigsCleared, Running, RunningX};  //Automatic routing
enum ASPECT {RegAspects, SloAspects, RegSloAspects, AdvAspects};         //Sets of signal aspects
enum LEVER{L, N, R};                                                     //USS lever positions

//Data structures for blocks, cabs and controllers

struct TCLOCO    //Data for loco under automatic train control or remote throttle control
{
	String Loco;    //Loco number
	String Block;   //Current block
	String Name;    //Name of remote throttle operator
	String ClientID;    //ID of remote throttle operator
	int RemoteSpeed;    //Speed from remote throttle
	String RemoteDir;   //direction from remote throttle
	String DirText;	//DCC direction text
	bool DCCDir;	//Direction, forward true, reverse false
	int TrackSpeed; //present track speed from command station
	int SetSpeed; 	//Last speed transmitted to command station
	int SignalSpeed; //Max speed for loco from signal indication
	int RefreshCnt; //count to refresh track speed
	int ActiveCnt; //count to maintain loco active
	String CabSignal; //Cab signal aspect
   	bool SetDir;	//Last direction transmitted to command station
	int ADFlg;		//Incrementing/decrementing flag for accel/decel
	int Normal, Medium, Approach, Start; //Loco speeds for ATC
	int Accel, Decel;	//Acceleration and deceleration rates for ATC
	char hiByte; //High byte of hex loco number
	char loByte;  //Low byte
	bool Stop;      //Stop loco
	bool FZero, FOne, FTwo, FThree, FFour; //DCC functions
	bool StopButton;  //Stop button pressed for loco
	bool BlockChange; //true indicates loco in new block
	bool ATC, RTC, Mon;  //loco control state
};

struct BLOCK
{
    bool Onward;    //can move to next block
  	bool MouseL;	//left mouse button pressed on block
	bool MouseR;	//right mouse button pressed on block
	IDSTATE IDState;	//ID display state
	String DisplayLine; //Line to be displayed
	IDSHOW Displayed;   //sTrain, sLoco or sEngineer
	bool ResetID;   //Clear ID and rewrite if needed
	bool Dir;		//signalled direction in block (eastbound is true)
	bool Srel;		//stop by relay
	bool SDCC;      //stop by DCC
	int DropProtect;   //for ATC
	bool OSW;		//occupancy of west OS section
  	bool OSE;		//occupancy of east OS section
  	int GnOSW;		//display OSW green (decrementing flag)
	int GnOSE;		//display OSE green (decrementing flag)
  	bool W;			//occupancy of west stop section
	bool M;			//occupancy of mid block
  	bool E;			//occupancy of east stop section
	bool Blk;      	//occupancy of either W, M or E, controlled by BlkInd()
  	int GnBlk;		//display block green (decrementing flag)
  	int AsstE;		//assert eastbound (decrementing flag)
	int AsstW;		//assert westbound (decrementing flag)
  	bool Efleet;	//fleeting on eastbound signal
	bool Wfleet;	//fleeting on westbound signal
	bool Ereclear;	//reclear on eastbound signal
	bool Wreclear;  //reclear on westbound signal
  	bool Switch;   	//hand switch unlocked or open in block
	int ClrW;     	//west signal clear
	int ClrE;     	//east signal clear
	int RstrW;		//west signal restricting
  	int RstrE;    	//east signal restricting
	ROUTE RtW;	   	//west signal route
	ROUTE RtE;	   	//east signal route
	bool LvrE;      //lever east out of block
	bool LvrW;      //lever west out of block
  	BLOCK* NxtE;	//pointer to next block east
	BLOCK* NxtW;   	//pointer to next block west
	char* BlkID;	//Block ID text
	bool HeadEnd;   //Head end of train in this block
	String Train;	//train ID
	String Loco;    //Loco number
 	String DirTxt;  //DCC direction in text
	String LocoLine; //Text line for lists
	TCLOCO* pLoco; //pointer to loco info
	String Signal;  //Cab signal aspect
 //	bool Active;    //loco moving or on active list
};
struct SWITCH
{
	bool NI, RI;	//Indications from switch
	int NO, RO;		//Timeout flags, outputs to switch
	bool N, R;		//Lever position
	bool Out;		//Out of correspondence
	bool L;			//Lock for lever and interlocking switch
	bool UnlockReq;	//Unlock request for hand-operated switch
	bool Locked;	//Lock for hand-operated switch
	bool Hand;		//Switch is hand-operated when true
	BLOCK* pBlk;	//Block pointer for hand-operated switch
	char Indicator;  //Indicator light
};

struct SIGLVR
{
	bool CButton;	//Callon button present
	bool LockR, LockL, LockN; //Lever locks
	bool L, N, R;	//Lever position
	bool Callon;	//Callon button pressed
	bool Fleet;		//Fleeting activated
	bool NoFleet;	//Inhibit fleeting
	bool Stick;		//Prevent reclearing
	bool Ereclear, Wreclear;  //Reclear indicators
	bool ClnFlg;	//Callon flag
	bool Clear;		//Signal clear
	bool LI, NI, RI;	//CTC indications
	char IndicatorL, IndicatorR;	//Indicator lights
};

struct SIGNAL
{
	bool Aspect[3];		//Signal aspect
	bool Proceed;		//Proceed when true
	bool Lock;
};

struct FLTLVR
{
	bool N, R;		//Lever position
	char Indicator;	//Indicator light
	bool L;			//Lock
};

struct COLUMN
{
	TImage* pImage;	//image containing column
	COLUMN* pCol;	//column pointer
	int XOR;		//X origin of column in display
	int YOR;		//Y origin of column in display
	SWITCH* pSw;	//Switch pointer
	SIGLVR* pSigL;	//Signal lever pointer
	FLTLVR* pFltL; 	//Fleet lever pointer
	bool Enabled;	//true for dispatcher control
	bool Long;		//true if long USS machine lever
};

struct SCREEN
{
	TImage* Image;
	COLUMN USSCol[50];              //USS columns
	char* ImageName;
	char Source[Cols*Rows];               //Source array loaded from file
	char Work[Cols*Rows];                 //Array generated as system operates
	char Display[Cols*Rows];              //Array being displayed
	int MouseX, MouseY, MouseCol, MouseRow;
	bool MouseLeft, MouseRight, RemoteMouseLeft, RemoteMouseRight;
	int DiaXOrigin, DiaYOrigin;     //for track diagram, origin of arrays
	int XOrigin, YOrigin;	//For USS elements, origin of USS frame on diagram
	bool LeverInit;         //Initialize switch levers to switch positions at startup
	bool Invalidate;        //something changed, screen needs refreshing
	bool Refresh, RefreshIDs;     //used if Refresh Screen clicked
	bool DataChange;
    bool ButtonDown;
};

//---------------------------------------------------------------------------
class TPSRY : public TForm
{
__published:	// IDE-managed Components
	TSpeedButton *Start;
	TSpeedButton *Stop;
	TPanel *TopPanel;
	TLabel *DataBytesHyCf;
	TImageList *Tiles;
	TPanel *BottomPanel;
	TTimer *Cycle;
	TImageList *ShortLevers;
	TImageList *LongLevers;
	TImageList *USSLamps;
	TPanel *DiagramPanel;
	TImage *ImageLaKr;
	TImage *ImageNaCf;
	TPanel *BankClivedenCliff;
	TRadioButton *RBCliff;
	TRadioButton *RBDispatcherBkCl;
	TSpeedButton *Stop2;
	TPanel *OSSLocks;
	TLabel *Label7;
	TRadioButton *OSSLockOn;
	TRadioButton *OSSLockOff;
	TMemo *MessageBuffer;
	TEdit *Col;
	TEdit *Row;
	TLabel *Label4;
	TLabel *Label5;
	TImage *ImageHyYdPt;
	TPanel *RailroadControls;
	TEdit *DCCBreakers;
	TLabel *Label10;
	TLabel *Label6;
	TEdit *Train;
	TLabel *Label3;
	TLabel *Aborts;
	TLabel *Label1;
	TButton *Start2;
	TServerSocket *RemoteDisplaySocket;
	TComboBox *LocoList;
	TButton *EditLocosButton;
	TLabel *Label14;
	TComboBox *LocoBlockList;
	TLabel *Label15;
	TButton *ATCBtn;
	TButton *DeleteButton;
	TPanel *DCCDirection;
	TRadioButton *rbForward;
	TRadioButton *rbReverse;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *DCCAborts;
	TImageList *CabSignals;
	TImage *CabSignal;
	TButton *DeleteID;
	TListBox *ActiveList;
	TLabel *NumberOfTrains;
	TUpDown *UpDownHours;
	TUpDown *UpDownMinutes;
	TEdit *Hours;
	TEdit *Minutes;
	TEdit *PSTime;
	TButton *RunStandbyButton;
	TButton *SetButton;
	TTimer *PSClock;
	TPanel *NassauDispatcher;
	TRadioButton *RBNDispatcherMain;
	TRadioButton *RBNassau;
	TListBox *SavedTrainIDs;
	TPanel *LASignals4;
	TRadioButton *PortControl;
	TLabel *Label18;
	TRadioButton *DispatcherControl;
	TLabel *RemoteDisplays;
	TButton *ActiveListBtn;
	TButton *ClearIDs;
	TButton *LoadIDs;
	TButton *SaveIDs;
	TEdit *SelectedTrain;
	TEdit *SelectedLoco;
	TLabel *Label2;
	TEdit *BlockID;
	TPanel *ATCPanel;
	TButton *StartStopButton;
	TButton *Horn;
	TButton *Headlight;
	TButton *KillATC;
	TLabel *Label11;
	TLabel *CliffLabel;
	TCheckBox *CBATC;
	TCheckBox *CBActive;
	TButton *IOChanges;
	TListBox *Changes;
	TButton *RefreshScreen;
	TRadioButton *RBNDispatcherAll;
	TRadioButton *RBDispatcherAll;
	TButton *Data;
	TPanel *DataPanel;
	TCheckBox *CB1;
	TCheckBox *CB2;
	TCheckBox *CB3;
	TLabel *Label21;
	TPanel *BkClRoutes;
	TRadioButton *BkClOn;
	TRadioButton *BkClOff;
	TPanel *YardControl;
	TRadioButton *RBYard;
	TRadioButton *RBYDispatcher;
	TPanel *CheckBoxes;
	TCheckBox *CB4;
	TCheckBox *CB5;
	TPanel *TimeSelect;
	TRadioButton *RealTime;
	TRadioButton *PSRYTime;
	TServerSocket *RemoteThrottleSocket;
	TCheckBox *cbRTC;
	TLabel *RemoteThrottles;
	TLabel *Label22;
	TMemo *RemDisMessageBuffer;
	TLabel *RemoteDispatcherOn;
	TCheckBox *HydeFleetOn;
	TCheckBox *YardFleetOn;
	TCheckBox *PortFleetOn;
	TCheckBox *CliffFleetOn;
	TButton *EditRoutesButton;
	TPanel *DellShoreRoutes;
	TRadioButton *DSROn;
	TRadioButton *DSROff;
	TLabel *Label8;
	TCheckBox *H30Incl;
	TPanel *HydeInRoutes;
	TLabel *Label9;
	TRadioButton *HyInOn;
	TRadioButton *HyInOff;
	TPanel *NassauRoutes;
	TLabel *Label12;
	TRadioButton *NaOn;
	TRadioButton *NaOff;
	TLabel *Label13;
	TCheckBox *C31Incl;
	TServerSocket *RemoteDispatcherSocket;
	TPanel *TestControl;
	TRadioButton *TestModeOn;
	TRadioButton *TestModeOff;
	TLabel *Label19;
	TButton *RouteStates;
	TPanel *RouteData;
	TLabel *RouteStateText;
	TLabel *Label23;
	TCheckBox *F11Incl;
	TPanel *IDSets;
	TRadioButton *IDListA;
	TRadioButton *IDListB;
	TRadioButton *IDListC;
	TLabel *Label24;
	TMemo *CurrentIDs;
	TButton *MonitorBtn;
	TLabel *Label26;
	TButton *OffBtn;
	TRadioButton *rbFor;
	TRadioButton *fbRev;
	TGroupBox *Speeds;
	TEdit *TrackSpeed;
	TEdit *SigSpeed;
	TLabel *Label25;
	TLabel *Label27;
	TLabel *TSAborts;
	TLabel *Label28;
	TLabel *DataBytesLaKr;
	TLabel *DataBytesNaCf;
	TCheckBox *P32Incl;
	TButton *rtCenter;
	TButton *bnLeft;
	TButton *bnRight;
	TButton *lfCenter;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall StopClick(TObject *Sender);
	void __fastcall StartClick(TObject *Sender);
	void __fastcall DataClick(TObject *Sender);
	void __fastcall ImageLaKrMouseDown(TObject *Sender, TMouseButton Button,
		TShiftState Shift, int X, int Y);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall TrainClick(TObject *Sender);

	void __fastcall ImageLaKrMouseUp(TObject *Sender, TMouseButton Button,
		TShiftState Shift, int X, int Y);
	void __fastcall CycleTimer(TObject *Sender);
	void __fastcall ImageNaCfMouseDown(TObject *Sender, TMouseButton Button,
		TShiftState Shift, int X, int Y);
	void __fastcall ImageNaCfMouseUp(TObject *Sender, TMouseButton Button,
		TShiftState Shift, int X, int Y);
	void __fastcall OSSLockOnClick(TObject *Sender);
	void __fastcall OSSLockOffClick(TObject *Sender);
	void __fastcall ImageHyYdPtMouseDown(TObject *Sender, TMouseButton Button,
		TShiftState Shift, int X, int Y);
	void __fastcall ImageHyYdPtMouseUp(TObject *Sender, TMouseButton Button,
		TShiftState Shift, int X, int Y);
	void __fastcall RemoteDisplaySocketClientConnect(TObject *Sender,
		  TCustomWinSocket *Socket);
	void __fastcall RemoteDisplaySocketClientRead(TObject *Sender,
		  TCustomWinSocket *Socket);
	void __fastcall Start2Click(TObject *Sender);
	void __fastcall EditLocosButtonClick(TObject *Sender);
	void __fastcall DeleteButtonClick(TObject *Sender);
	void __fastcall ATCBtnClick(TObject *Sender);
	void __fastcall CabSignalClick(TObject *Sender);
	void __fastcall KillATCClick(TObject *Sender);
	void __fastcall StartStopButtonClick(TObject *Sender);
	void __fastcall DeleteIDClick(TObject *Sender);
	void __fastcall SetButtonClick(TObject *Sender);
	void __fastcall RunStandbyButtonClick(TObject *Sender);
	void __fastcall PSClockTimer(TObject *Sender);
	void __fastcall HeadlightClick(TObject *Sender);
	void __fastcall HornMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall HornMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall DirClick(TObject *Sender);
	void __fastcall ImageHyYdPtMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y);
	void __fastcall ImageLaKrMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall ImageNaCfMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall ClearIDsClick(TObject *Sender);
	void __fastcall SaveIDsClick(TObject *Sender);
	void __fastcall LoadIDsClick(TObject *Sender);
	void __fastcall ActiveListBtnClick(TObject *Sender);
	void __fastcall ActiveListMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall IOChangesClick(TObject *Sender);
	void __fastcall ChangesClick(TObject *Sender);
	void __fastcall RefreshScreenClick(TObject *Sender);
	void __fastcall BkClOnClick(TObject *Sender);
	void __fastcall BkClOffClick(TObject *Sender);
	void __fastcall RealTimeClick(TObject *Sender);
	void __fastcall PSRYTimeClick(TObject *Sender);
	void __fastcall RemoteThrottleSocketClientConnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall RemoteThrottleSocketClientRead(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall RemoteDispatcherSocketClientConnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall RemoteDispatcherSocketClientRead(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall CBActiveClick(TObject *Sender);
	void __fastcall CBATCClick(TObject *Sender);
	void __fastcall cbRTCClick(TObject *Sender);
	void __fastcall DispatcherControlClick(TObject *Sender);
	void __fastcall PortControlClick(TObject *Sender);
	void __fastcall RBNassauClick(TObject *Sender);
	void __fastcall RBNDispatcherMainClick(TObject *Sender);
	void __fastcall RBNDispatcherAllClick(TObject *Sender);
	void __fastcall HydeFleetOnClick(TObject *Sender);
	void __fastcall RBCliffClick(TObject *Sender);
	void __fastcall RBDispatcherBkClClick(TObject *Sender);
	void __fastcall RBDispatcherAllClick(TObject *Sender);
	void __fastcall RBYardClick(TObject *Sender);
	void __fastcall RBYDispatcherClick(TObject *Sender);
	void __fastcall YardFleetOnClick(TObject *Sender);
	void __fastcall PortFleetOnClick(TObject *Sender);
	void __fastcall CliffFleetOnClick(TObject *Sender);
	void __fastcall EditRoutesButtonClick(TObject *Sender);
	void __fastcall HyInOnClick(TObject *Sender);
	void __fastcall HyInOffClick(TObject *Sender);
	void __fastcall DSROnClick(TObject *Sender);
	void __fastcall DSROffClick(TObject *Sender);
	void __fastcall H30InclClick(TObject *Sender);
	void __fastcall NaOnClick(TObject *Sender);
	void __fastcall NaOffClick(TObject *Sender);
	void __fastcall LocoBlockListClick(TObject *Sender);
	void __fastcall C31InclClick(TObject *Sender);
	void __fastcall TestModeOnClick(TObject *Sender);
	void __fastcall TestModeOffClick(TObject *Sender);
	void __fastcall RouteStatesClick(TObject *Sender);
	void __fastcall F11InclClick(TObject *Sender);
	void __fastcall IDListAClick(TObject *Sender);
	void __fastcall IDListBClick(TObject *Sender);
	void __fastcall IDListCClick(TObject *Sender);
	void __fastcall OffBtnClick(TObject *Sender);
	void __fastcall MonitorBtnClick(TObject *Sender);
	void __fastcall rbForClick(TObject *Sender);
	void __fastcall fbRevClick(TObject *Sender);
	void __fastcall P32InclClick(TObject *Sender);
	void __fastcall bnLeftClick(TObject *Sender);
	void __fastcall bnRightClick(TObject *Sender);
	void __fastcall lfCenterClick(TObject *Sender);
	void __fastcall rtCenterClick(TObject *Sender);


private:	// User declarations

//Use functions---------------------------------------------------------------------

   __fastcall TPSRY(TComponent* Owner);

	void LoadTile(String Name);
	void LoadShortLevers(String Name);
	void LoadLongLevers(String Name);
	void LoadUSSLamps(String Name);
	void LoadCabSignals(String Name);

	void RailroadInOut();
	bool Send(char * OutBuff, char * InBuff, unsigned Count);

	void UpdateImage(SCREEN * Screen);
	void UpdateData(void);
	void SendPacket(int Address, int* NodeAborts, IOBYTE *In,
		IOBYTE *Old, IOBYTE *Out, int Count, bool Swap);

	void DrawRemotes(String Type, String ImageName, int Col, int Row, char Tile, String Train);
   	void DrawRemoteUSS(String Type, String ImageName, int X, int Y, char Tile);
    void RemDisSelectLocoMessage(BLOCK* pBlk);
	void WriteRemotes(void);
	void WriteRemoteDispatcher();
	void MessageToRemDis(String Type, String Message);
	void InitializeRemDis();
    void InitRemDisCol(COLUMN* pCol);

	void SetLocoList(String Loco, String Dir);
	void MessageToRemotes(String Type, String Message);
	void TPSRY::RemoteBkrMessage(String BkrMessage);
    void DeleteLoco();
	String BoolToStr(bool X);
	bool StrToBool(String X);

	String Hex(char InStr[], int Fst, int Num);
	String Binary(char InStr[], int Fst, int Num);

	void USSMouseDown(int X, int Y);
	void USSSwNormal(COLUMN* pCol);
	void USSSwReverse(COLUMN* pCol);
	void USSSigLeft(COLUMN* pCol);
	void USSSigNormal(COLUMN* pCol);
	void USSSigRight(COLUMN* pCol);
	void USSFltNormal(COLUMN* pCol);
	void USSFltReverse(COLUMN* pCol);
	void USSMouseUp(void);
	void USSColumn(COLUMN *pCol);
	void USSIndicators(COLUMN *pCol, bool Init);
	void USSSwitches(COLUMN *pCol);

	void HandSwitch(int Col, int Row, bool Up, SWITCH *pSw);
	void HandAdditional(int Col, int Row, bool Up, SWITCH *pSw);
	void Fleeting(bool FltLvr, SIGLVR *pSigL);
	void ScreenSwap(void);
	void SetArrays(void);
	void BlkInd(BLOCK *pBlk);
	void TC(BLOCK *pBlk, SIGNAL *Wsig, SIGNAL *Esig);
	void Tracker(int Col, int Row, BLOCK *pBlk, BTYPE Type);
    void XTracker(int Col, int Row, BLOCK* pBlk, BTYPE Type, bool* Input);

	void Approach(int Col, int Row, BLOCK *pBlk, bool Section);
	void Switch(int Col, int Row, SWITCH * Switch, char nDis, char rDis);
	void DSSwitch(int Col, int Row, SWITCH *Switch1, SWITCH *Switch2,
		char nnDis, char rnDis, char rrDis, char nrDis);
	void Scissors(int Col, int Row, SWITCH *Switch1, SWITCH *Switch2);
	void SignalE(int Col, int Row, BLOCK* pBlk);
	void SignalW(int Col, int Row, BLOCK* pBlk);
	void SignalWE(int Col, int Row, BLOCK* pBlk);
	void SignalEW(int Col, int Row, BLOCK* pBlk);
	int SwitchButton(int Col, int Row, int* Time);
	void ClickSignalE(int Col, int Row, LEVER Lvr, SIGLVR *pSigL, BLOCK *pBlk);
	void ClickSignalW(int Col, int Row, LEVER Lvr, SIGLVR *pSigL, BLOCK *pBlk);
	int NXBtn(int Col, int Row, int A, int B, bool* Btn);
	void Indicator(int Col, int Row, int Indication);
	void TrainID(BLOCK* pBlk);
    void RailroadBlockClick(BLOCK* pBlk);
	void DisplayID(int Col, int Row, BLOCK * pBlk);
	void EraseID(intCol, int Row, BLOCK * pBlk, int N);
	void Esig(bool Lvr, SIGLVR *pSigL, SIGNAL *pSignal, BLOCK *Pblk, ASPECT Aspects);
	void Wsig(bool Lvr, SIGLVR *pSigL, SIGNAL *pSignal, BLOCK *Pblk, ASPECT Aspects);
	void EWsig(bool Lvr, SIGLVR *pSigL,SIGNAL *pSignal, BLOCK *Pblk, ASPECT Aspects);
	void WEsig(bool Lvr, SIGLVR *pSigL,SIGNAL *pSignal, BLOCK *Pblk, ASPECT Aspects);
	void Setsig(SIGLVR *pSigL, SIGNAL *pSignal, bool Blk, ASPECT Aspects);
	void SigInd(SIGLVR *pSigL);
	void EBkcon(bool Dir, SIGNAL *pSignal, BLOCK* Pblk, ASPECT Aspects);
	void WBkcon(bool Dir, SIGNAL *pSignal, BLOCK* Pblk, ASPECT Aspects);
	void SetBsig(SIGNAL *pSignal, bool Blk, ASPECT Aspects);
	BLOCK* GetBlkPtr(String TrainBlk);
	void AddLoco(BLOCK* pBlk);
	String InLocoBlockList(String B, String L);
	void RailroadRunTrains(void);
	void ParseLocoLine(String Line, BLOCK* L);
	String CreateLocoLine(BLOCK* L);
	void TransmitSpeed(TCLOCO* pLoco);
	void TransmitFunction(TCLOCO* pLoco);
	void SendDCCPacket(int WCount, int RCount);
	void GetDCCData(BLOCK* pBlk, TCLOCO* pLoco);
	void AssignLocos(void);
    void ATCMonOff(BLOCK* pBlk);
	void ERearATC(BLOCK* pBlk, SIGNAL* Esig);
	void WRearATC(BLOCK* pBlk, SIGNAL* Wsig);
	void EStubATC(BLOCK* pBlk, SIGNAL* Wsig);
	void WStubATC(BLOCK* pBlk, SIGNAL* Esig);
	void SetTrainInBlock(String TrainID, BLOCK* pBlk, String Dir);
	void SetLoco(String BlkID);
	void UpdateActiveList();
	void DisplayTime(void);
	void SaveID(BLOCK* pBlk);
    void ClearID(BLOCK* pBlk);
	void RecordChange(int Address, int ByteNo, char Old, char New);
	String BinaryByte(char Byte);
	String NodeName(int Address);
	void TimeLog(int Num);
	void HyMDn(TMouseButton Button, int X, int Y);
	void LaMDn(TMouseButton Button, int X, int Y);
	void NaMDn(TMouseButton Button, int X, int Y);
	void RemoteThrottleConnect(BLOCK* pBlk, String Name, String ClientID);
	void RemoteThrottleDisconnect(BLOCK* pBlk);
	void WriteThrottles(String Name, String Type, String Block, String Train);
	String GetDest(String Train, String Location);
	void Testing(void);
	String GetRouteState(STATE State);
	void MessageToTrainTkr(String Type, String A, String B, String C, String D);
	void GetTrackSpeed(TCLOCO* pLoco);


public: //User functions

	String GetMessage(int i);
	void Breakers(void);

	void InitializeYard(void);
	void Yard(void);
	void YardInOut(void);

	void InitializePort(void);
	void Port(void);
	void PortInOut(void);

	void InitializeLatham(void);
	void Latham(void);
	void LathamInOut(void);

	void InitializeDell(void);
	void Dell(void);
	void DellInOut(void);

	void InitializeHyde(void);
	void Hyde(void);
	void HydeInOut(void);

	void InitializeShore(void);
	void Shore(void);
	void ShoreInOut(void);

	void InitializeKrulish(void);
	void Krulish(void);
	void KrulishInOut(void);

	void InitializeNassau(void);
	void Nassau(void);
	void NassauInOut(void);

	void InitializeBank(void);
	void Bank(void);
	void BankInOut(void);

	void InitializeCliveden(void);
	void Cliveden(void);
	void ClivedenInOut(void);

	void InitializeCliff(void);
	void Cliff(void);
	void CliffInOut(void);

	bool LocosEdited, RoutesEdited;
//===============================================================================================================================================================================================

private: //User declarations
//Variables---------------------------------------------------------------------

	bool LocosAssigned;
	int ATCCheck;
	String CabSignalAspect;
	String SelectedLocoNo;
	bool PRRCabSignals;
	bool LocoListChange;
	int ActiveListChange;   //Decrementing flag
	int PSHours, PSMinutes, PShsec;     //for Pacific Southern time clock
	int RealHours, RealMinutes;         ////
	int DisplayHours, DisplayMinutes;   ////
	bool Colon, PSRYRun;                 		////
	bool RunTrains;
    bool InTestMode;

//Serial I/O to railroad

	HANDLE RRcomHandle;
	COMMTIMEOUTS RRtimeouts;
	DCB RRdcb;

	int NumAborts;
	char Buffer[16];
	char OutData[15];
	char InData[15];
	bool Match;

//Serial I/O to DCC Command Station

	HANDLE DCCcomHandle;
	COMMTIMEOUTS DCCtimeouts;
	DCB DCCdcb;
	int NumDCCAborts;

//Serial I/O to DCC server for track speeds

	HANDLE TScomHandle;
	COMMTIMEOUTS TStimeouts;
	DCB TSdcb;
	int NumTSAborts;
   char TSOut[10];
   char TSIn[10];

//decrementing flsg for initialization

	int Starting;

//For interlocking and signal functions

	bool OSSLock;
	bool Clear,  NxtClr, NxtClrAd, Rstrct, Call;
	ROUTE Rte, NxtRte;
	bool Flash, SFlash;

//Display

	SCREEN HyYdPt, LaKr, NaCf;
	SCREEN* Screen;
	bool Invalidate;
    bool ButtonJump;   //used in Tracker() to jump NX buttons
	bool SwapRequest;  //flag to cause swap
	int Refresh;

//Remote Displays, remote throttle, remote dispatcher

	bool NewRemote, InitializeTiles, InitializeIDs, RemoteOn;
	bool NewRemDis, InitializeRemDisIDs, RemDisOn;
	bool RemDisDelete, RemDisAdd;
	bool CfEn, BkClEn, AllEn, NaEn, NaMnEn, NaAllEn, NaRtVis, Sig4P, Sig4D;
	bool H30En, C31En, ATCVis, KillVis;
	bool MonEn, ATCEn, OffEn;
    String TrkSpd, SigSpd;

	int NumDisplays, NumThrottles, ClientIDNo;
	bool NewRemThrottle;
	String LastBkrMessage;
	String RemoteTrain;
	String RemoteLoco;
	String RemoteLocoDir;
	int WatchdogTime;

//DCC Command station

	char DCCData[10];

//USS boards

	int LeverX, LeverY;
	COLUMN* ButtonCol;
	long VertPos, HorzPos;
	char strArray[25000];  //for loading array strings

 // 	DISPLAY Display;
	String TXText, RXText, OutText;

//Dummy block and locoblock

	TCLOCO* pSelectedLoco;
	TCLOCO DummyLoco;
	BLOCK DummyBlock;

//Dummy bytes for unused inputs and outputs

	IOBYTE DMIn[15], DMOut[15];

//Declarations for DCC circuit breakers-----------------------------------------------

	String BkrMessage[40];
	bool CktBkr[40];
	bool Tripped, NotTripped, OK, DCCPowerOff;
	int Top, Timer;
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------

//Declarations for Yard--------------------------------------------------------

//I/O Bytes

	IOBYTE YDIn[10], YDOld[10], YDOut[10];
	IOBYTE KAIn[4], KAOld[4], KAOut[4];
	IOBYTE EJIn[2], EJOld[2], EJOut[2];
	IOBYTE CJIn[2], CJOld[2], CJOut[2];
	IOBYTE YSWIn[5], YSWOld[5], YSWOut[5];

	String YDText, KAText, EJText, CJText, YSWText;

	int YardAborts, KaleAborts, EJuncAborts, CornellAborts, YardSWAborts;

//Blocks

	BLOCK Y10, Y11, Y20, Y21, Y30;
	BLOCK Y50, Y51, Y52, Y53, Y60, Y70;
	BLOCK Y71, Y81, Y82, Y83, Y84, Y87;

//OS Sections

	bool KAOS1, KAOS2, KAOS3, KAOS4;
	bool EJOS1, EJOS2;
	bool CJOS1, CJOS2;
	bool WOS1, WOS2;

//Signals

	SIGNAL Y2L, Y2R;
	SIGNAL Y4L, Y4RA, Y4RB;

	SIGNAL Y8LA, Y8LB, Y8LC, Y8R;
	SIGNAL Y10L, Y10R;

	SIGNAL Y22L, Y22R;
	SIGNAL Y24LA, Y24LB, Y24LC;
	SIGNAL Y26LA, Y26LB, Y26LC, Y26R;

	SIGNAL Y34L, Y34RA, Y34RB;

	SIGNAL Y40R, Y40LA, Y40LB, Y40LC, Y40LD;
	SIGNAL Y42L, Y42RA, Y42RB, Y42RC, Y42RD;

	bool Y20H, Y20D;	//Outbound semaphore
	bool Y22Ra, Y22Rb;  //Inbound semaphore

//Switches

	SWITCH YSw1, YSw3, YSw7, YSw9, YSw11;
	SWITCH YSw17, YSw19, YSw21, YSw23, YSw25, YSw27, YSw29;
	SWITCH YSw33;
	SWITCH YSw113, YSw115, YSw116, YSw131, YSw132, YSw134;

	bool Y81ESw, Y81WSw, Y71WSw, WatermanThru;    //Waterman through route

	bool PJSwL1, PJSwL2;

	SIGLVR YSigL2, YSigL4, YSigL8, YSigL10;
	SIGLVR YSigL22, YSigL24, YSigL26;
	SIGLVR YSigL34;
	SIGLVR YSigL40, YSigL42;                  //moved with the rest

	FLTLVR YFlt;

	bool YRelease;

//Switch buttons

	bool NXBtnY11E, NXBtnL10W, NXBtnY21E, NXBtnL20W, NXBtnP50W;
	bool NXBtnY30E, NXBtnY87E, NXBtnY10E, NXBtnY20E, NXBtnY11W, NXBtnY21W;

	int SBY81E, SBY81W, SBY82E, SBY82W, SBY83E, SBY83W, SBY84E, SBY84W;
	bool NXBtnY60E, NXBtnY53E, NXBtnY52E, NXBtnY70W, NXBtnY51E, NXBtnY50E;
	bool NXBtnY10W, NXBtnY20W;

	int SBY50W, SBY51W;

//Route Indications for Waterman;

	bool WOS1Norm;
	bool Y81E, Y82E, Y83E, Y84E;
	bool Y81W, Y82W, Y83W, Y84W;

//Circuit breaker indicators

	bool CBKale, CBEastEnd, CBCornell, CBWaterman, CBEngineYard;

//Declarations for Port--------------------------------------------------------

//IO Bytes

	IOBYTE PAIn[10], PAOld[10], PAOut[10];
	IOBYTE PJIn[5], PJOld[5], PJOut[5];
	IOBYTE PBIn[10], PBOld[10], PBOut[10];

	String PAText, PBText, PJText;

//Aborts

	int PortAAborts, ParsonsAborts, PortBAborts;

//Blocks

	BLOCK P1, P2, P3, P4, P5, P6, P7;
	BLOCK P10, P11, P20, P21, P30, P31, P32, P40, P41, P42, P50;
	BLOCK V10, V11, P60, P61, P62, P63, P64;

//OS Sections

	bool PAOS1, PAOS2, PAOS3, PAOS4, PAOS5;
	bool PJOS1, PJOS2, PBOS1, PBOS2, PBOS3, PBOS4;

//Signals

	SIGNAL PA4RA, PA4RB, PA6R, PA8R, PA10RA, PA10RB, PA12R;
	SIGNAL PA4L, PA6LA, PA6LB, PA6LC, PA8L, PA10L, PA12LA, PA12LB, PA12LC;
	SIGNAL PA32RA, PA32RB, PA34RA, PA34RB, PA34RC, PA34RD;
	SIGNAL PA32L, PA34LA, PA34LB;
	SIGNAL PB2R, PB4R, PB2L, PB4L;
	SIGNAL PB12R, PB14R, PB12L, PB14L;

	FLTLVR PFlt;
	bool PA10La, PA10Lb, PA4La, PA4Lb;

//Crossing signal

	bool PBE, PBW, PBXO;

//Switches

	SWITCH PASw1, PASw3, PASw5, PASw7, PASw9, PASw11, PASw13, PASw15, PASw17;
	SWITCH PASw19, PASw21, PASw23, PASw27, PASw29, PASw31, PASw33, PASw35, PASw37;
	SWITCH PBSw1, PBSw3, PBSw5, PBSw11, PBSw13, PBSw15, PBSw15A, PBSw15B;

	bool PARelease, PBRelease;

//Switch locks

	bool SPL2, SPL3, SPL4, SPL5, SPL6, SPL7;

//Signal and fleet levers

	SIGLVR PASigL4, PASigL6, PASigL8, PASigL10, PASigL12, PASigL32, PASigL34;
	SIGLVR PBSigL2, PBSigL4, PBSigL12, PBSigL14;
	FLTLVR PAFltL30, PBFltL10;

//DCC circuit breakers

	bool CBSouthport, CBParsons, CBCircusJct, CBSouthJct, CBLavin;

//Declarations for Latham------------------------------------------------------

//IO Bytes

	IOBYTE LIn[5], LOld[5], LOut[5];
	IOBYTE CAIn[5], CAOld[5], CAOut[5];
	String LAText, CAText;

//Aborts

	int LathamAborts, CarltonAborts;

//Blocks

	BLOCK L10, L11, L20, L21, L31;

//OS sections

	bool LOS1, LOS2, LOS3, CAOS1, CAOS2, CAOS3;

//Signals

	SIGNAL L4R, L4L, L6RA, L6RB, L6L, L8R, L8L;
	SIGNAL L14R, L14L, L16R, L18R, L18L;

//Switches & locks

	SWITCH LSw1, LSw3, LSw5, LSw7, LSw9;
	SWITCH LSw11, LSw13, LSw15, LSw17;

//Signal & fleet levers

	SIGLVR LSigL4, LSigL6, LSigL8, LSigL14, LSigL16, LSigL18;
	FLTLVR LFltL2, LFltL12;

//DCC Circuit breakers

	bool LathamCB, CarltonCB;

//Declarations for Dell------------------------------------------------------

//IO Bytes

	IOBYTE DIn[7], DOld[7], DOut[7];
	IOBYTE MFIn[4], MFOld[4], MFOut[4];
	String DLText, MFText;

//Aborts

	int DellAborts;
	int FossAborts;

//Blocks

	BLOCK D10, D11, D20, D21;

//OS Sections

	bool DOS1, DOS2, MFOS1, MFOS2;

//Switches & locks

	SWITCH DSw1, DSw3, DSw5, DSw7, DSw9, DSw11;
	bool DSwOut;

//Signal and fleet levers

	SIGLVR DSigL4, DSigL6, DSigL10, DSigL12;
	FLTLVR DFltL2, DFltL8;

//Signals

	SIGNAL D4RA, D4RB, D4L, D6RA, D6RB, D6L, D10R, D10L, D12R, D12L;

//Laporte grade crossing

	bool D11A, D11B, D21A, D21B, DXO, D1E, D1W, D2E, D2W;

//DCC circuit breakers

	bool DellCB, FossCB;

//Auto routing

	STATE DellEState, DellWState;
	String DellERoute, DellWRoute, DEState, DWState;

//Declarations for Shore-------------------------------------------------------

//IO Bytes

	IOBYTE SIn[10], SOld[10], SOut[10];
	String SHText;

//Aborts

	int ShoreAborts;

//Power Control

	bool H30Power;

//Blocks

	BLOCK S10, S11, S20, S21;

//OS Sections

	bool SOS1, SOS2, SOS3;

//Switches, signals & signal levers

	SWITCH SSw1, SSw3, SSw5, SSw7, SSw9, SSw11, SSw13, SSw15, SSw17, SSw19,
		SSwBX;

	SIGNAL S4R, S4LA, S4LB, S4LC;
	SIGNAL F10W, S8R, S8L, F11E;
	SIGNAL S12R, S12LA, S12LB, S12LC;
	SIGNAL S16R, S18R, S20R;
	SIGNAL S16L, S18LB, S18LA, S20L;
	SIGNAL S11E, S21E;  //Block signal

	bool F10H, F10D;	//Branch line semaphores

	SIGLVR SSigL4, SSigL8, SSigL12, SSigL16, SSigL18, SSigL20;
	FLTLVR SFltL2, SFltL14;

	bool S10A, S10B, S10C, S20A, S20B, S20C;   //Bortell crossing gate
	bool SXO, SXL, SXL1, SXL2, SXG, SXON, SXT, S1E, S1W, S2E, S2W;
	int SXTime;

	bool S11A, S11B, H30A, H30B, H10A, H10B;  //Cut sections

	bool MX;	//main asserted at diamond crossing
	bool BX;	//branch asserted at diamond crossing
	int BXT;	//timer for release of crossing

	bool ShoreCB, HarpersCB;	//Circuit breakers

	//Auto routing

	STATE ShoreEState, ShoreWState;
	String ShoreERoute, ShoreWRoute, SEState, SWState;

//Declarations for Hyde--------------------------------------------------------

	IOBYTE HDIn[15], HDOld[15], HDOut[15];


	IOBYTE HIn[6], HOld[6], HOut[6];
	IOBYTE HJIn[4], HJOld[4], HJOut[4];
	String HJctText;
	String HText, HDText;

//Aborts

	int HydeJctAborts, HydeAborts, HydeDiaAborts;
	bool HydeIDsOK;

//Power control

	bool HydeEastPower, HydeWestPower;
	int PBH30, PBHydeWest, PBHydeEast;
	bool lastH30, lastHydeWest, lastHydeEast;

//Blocks

	BLOCK H10, H20, H30;
	BLOCK H11, H21;
	BLOCK H31, H32, H33, H34, H12, H22, H43, H42, H41, H40;
	BLOCK H13, H23;

//OS Sections

	bool HOS1, HOS2, HOS3, HOS4, HOS5, HOS6, HOS7, HOS8;

//Switches

	SWITCH HSw1, HSw3, HSw5, HSw7, HSw9, HSw11, HSw13;
	SWITCH HSw15, HSw17, HSw19, HSw21, HSw23, HSw25, HSw27, HSw29;

//Switch indications

	bool H30E, H31W, H32W, H33W, H34W, H12W, H22W, H43W, H42W, H41W;
	bool H31E, H32E, H33E, H34E, H12E, H22E, H43E, H42E, H41E, H40E;

//Switch buttons

	int SBH30E, SBH31W, SBH31E, SBH32W, SBH32E, SBH33W, SBH33E, SBH34W, SBH34E;
	int SBH12W, SBH12E, SBH22W, SBH22E, SBH40E, SBH41W, SBH41E, SBH42W, SBH42E;
	int SBH43W, SBH43E;

//Signals

	SIGNAL H4R, H4LA, H4LB, H4LC, H4LD;
	SIGNAL H6R, H6LA, H6LB, H6LC, H6LD;
	SIGNAL H8R, H8L;

	SIGNAL H10RA, H10RB, H10RC, H10RD, H10RE, H10L;
	SIGNAL H12RA, H12RB, H12RC, H12RD, H12RE, H12L;

//Signal & fleet levers

	SIGLVR HSigL4, HSigL6, HSigL8, HSigL10, HSigL12;
	FLTLVR HFltL2;

//Circuit breakers

	bool CBHydeJct, CBHydeWest, CBHydeEast;

//Auto routing

	STATE HydeEState, HydeWState;
	String HydeERoute, HydeWRoute, HEState, HWState;

//Declarations for Krulish------------------------------------------------------

//IO Bytes

	IOBYTE KIn[3], KOld[3], KOut[3];
	String KRText;

//Aborts

	int KrulishAborts;

	BLOCK N10, N20, N25;

	bool KOS1, KOS2, KOS3;

//Directions  SHORE to KRULISH

	bool SKD1, SKD2;

//Switches

	SWITCH KSw1, KSw3, KSw5, KSw7;
	bool KSwOut;

//Signals

	SIGNAL K2R, K2L;
	SIGNAL K4R;
	SIGNAL K8R, K8LA, K8LB;

 //Block signals

	SIGNAL N10W, N20W;

//Signal & fleet levers

	SIGLVR KSigL2, KSigL4, KSigL8;
	FLTLVR KFltL6;

//Circuit breaker

	bool CBKrulishYard;

//Declarations for Nassau------------------------------------------------------

	IOBYTE NWIn[10], NWOld[10], NWOut[10];
	IOBYTE NEIn[5], NEOld[5], NEOut[5];
	IOBYTE NXIn[3], NXOld[3], NXOut[3];
//Aborts

	int  NassauWAborts, NassauEAborts, NassauNXAborts;

	String NWText, NEText, NXText;

//Blocks

	BLOCK N11, N21, N12, N22;
	BLOCK N31, N32, N41, N42;
	BLOCK N60, N60A, N60B, N60C, N60D, K10, T12, W10, W11, W20;

	bool NWOS1, NWOS2, NWOS3, NWOS4;   //OS Sections
	bool NEOS1, NEOS2, NEOS3;

//Switches

	SWITCH NSw13, NSw15, NSw17;
	SWITCH NSw19, NSw21, NSw23, NSw25, NSw27, NSw29, NSw31, NSw33;
	SWITCH NSw41, NSw43, NSw45, NSw47, NSw51, NSw53, NSw55, NSw57;
	SWITCH NSw35, NSw39;

	bool NWSL1, NWSL2, NWSL3, NWSL4, NESL1, NESL2, NESL3;        //Locks

	bool NSw60A, NSw60B, NSw60C, NSw60D;

	bool NRelease;

//Signals

	SIGNAL N11W, N21W, B20E;

	SIGNAL N14R, N14LA, N14LB, N14LC, N14LD, N16R, N16L, N18R, N18LA, N18LB, N20R,
		 N20L;
	SIGNAL N18RA, N18RB, N18RC, N18RD, N18LX;
	SIGNAL N24RA, N24RB, N24RC, N24RD, N24L, N26RA, N26RB, N26RC, N26L, N28R, N28L;

	SIGLVR NSigL14, NSigL16, NSigL18, NSigL20;
	SIGLVR NSigL24, NSigL26, NSigL28;

	FLTLVR NFltL12;

//Dispatcher control of Nassau

	int NWLeft, NWRight, NELeft, NERight;
    int PulseTime, MaxTime;
	bool NXBtnT12, NXBtnN60, NXBtnN11, NXBtnN21;
	bool NXBtnW10, NXBtnN32W, NXBtnN31W, NXBtnN12W, NXBtnN22W, NXBtnN41W, NXBtnN42W, NXBtnW20W;
	bool NXBtnW11, NXBtnN32E, NXBtnN31E, NXBtnN12E, NXBtnN22E, NXBtnN41E, NXBtnN42E, NXBtnW20E;
	bool NXBtnR10, NXBtnB10, NXBtnB20;

// DCC Circuit breakers

	bool CBSptJct, CBKrulish, CBNassauW, CBNassauE, CBThomas, CBWilson;

// Auto Routing

	STATE NassauEState, NassauWState;
    String NassauERoute, NassauWRoute, NEState, NWState;

//---------------------------------------------------------------------------


//Declarations for Bank---------------------------------------------------------

	IOBYTE BKIn[5], BKOld[5], BKOut[5];
	String BKText;

	int BankAborts;

//Blocks

	BLOCK B10, B20, B11, B21;

	bool BKOS1, BKOS2, BKOS3;

//Switches

	SWITCH CSw23, CSw21, CSw21A, CSw21B, CSw19, CSw17;

//Signals

	SIGNAL C24L, C24R, C22L, C22R, C18RA, C18RB, C18L;

	SIGLVR CSigL24, CSigL22, CSigL18;
	FLTLVR CFltL16;

//South Booster DCC Circuit breaker outputs

	bool SBkrBank, SBkrKale, SBkrWaterman, SBkrEngine;
	bool SBkrEastEnd, SBkrShore, SBkrRocky, SBkrHarpers;
	bool SBkrY30, SBkrY81;

//Declarations for Cliveden ----------------------------------------------------

	IOBYTE CVIn[5], CVOld[5], CVOut[5];
	String CVText;

	int ClivedenAborts;

//Blocks

	BLOCK C13, C23, C22;

	bool CVOS1, CVOS2, CVOS3;

//Switches

	SWITCH CSw15, CSw13, CSw11, CSw9;

//Signals

	SIGNAL C14R, C14LA, C14LB, C10R, C10L, C12R, C12L;

	SIGLVR CSigL14, CSigL12, CSigL10;

//Auto routing

	STATE BkClState;
	String BkClRoute, BCState;

	int NumTrains;
	bool Full;

//Declarations for Cliff

	IOBYTE GMIn[3], GMOld[3], GMOut[3];
	String GMText;
	int GMAborts;

	IOBYTE CFIn[10], CFOld[10], CFOut[10];
	String CFText, CDText;
	int CFAborts;
	bool CliffIDsOK;

	IOBYTE SHIn[4], SHOld[4], SHOut[4];
	String SFText;
	int SHAborts;

//Blocks

	BLOCK C10, C11, C12, C20, C21, C30, C31, C40, C41, C42, C43, C44,
	C50, C51, C52, C53, C54, G21, G10, G12;

	bool COS1, COS2, COS3, COS4;

//Switches

	SWITCH CSw3, CSw31, CSw33, CSw35, CSw37, CSw39, CSw41;
	SWITCH CSw43, CSw45, CSw47, CSw53, CSw55, CSw61;
	SWITCH CSw63, CSw65, CSw67, CSw69, CSw75, CSw77, CSw79;
	bool CRelease;

//Routes

	bool G21W, C10W, C30W, C31W;
	bool G12E, G10E, C10E, C30E;
	bool C44W, C43W, C42W, C41W, C40W, C21W;
	bool C50W, C51W, C52W, C53W, C54W;
	bool C44E, C43E, C42E, C41E, C40E, C21E;
	bool C50E, C51E, C52E, C53E, C54E;

//Switch buttons

	int SBC44E, SBC44W, SBC43E, SBC43W, SBC42E, SBC42W, SBC41E, SBC41W;
	int SBC40E, SBC40W, SBC21E, SBC21W, SBC50E, SBC50W, SBC51E, SBC51W;
	int SBC52E, SBC52W, SBC53E, SBC53W, SBC54E, SBC54W;
	int SBG21W, SBG12E, SBG10E, SBC10W, SBC10E, SBC30E, SBC30W, SBC31W;

//Signals

	SIGNAL C2R, C2LA, C2LB, C2LC, C2LD, C4L, C4RA, C4RB, C4RC, C4RD;
	SIGNAL C6R, C6LA, C6LB, C6LC, C6LD, C6LE, C6LF, C6LG, C6LH, C6LJ, C6LK, C6LL;
	SIGNAL C8RA, C8RB, C8RC, C8RD, C8RE, C8RF, C8RG, C8RH, C8RJ, C8RK, C8RL, C8L;

	SIGLVR CSigL2, CSigL4, CSigL6, CSigL8;

//DCC circuit breaker indicators

	bool CBBank, CBCliveden, CBGreenMountain, CBSheffield, CBReverser;

//Annunciator bell

	bool CliffBell;

//Declarations for Rocky Hill

	BLOCK R10, R11, R12;

	BLOCK* pR10; BLOCK* pR11; BLOCK* pR12;

	SIGNAL R10W, R10E;

	bool R10A, R10B, R10C;       //Crossing signal

	bool RXE, RXW, RXO, RXL, RXR;

//Declarations for Harpers Ferry-----------------------------------------------

//Blocks

	BLOCK F10, F11;
};
//---------------------------------------------------------------------------
extern PACKAGE TPSRY *PSRY;
//---------------------------------------------------------------------------
#endif
