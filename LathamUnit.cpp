//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "LathamUnit.h"
//Initialize Latham

void TPSRY::InitializeLatham(void)
{
	L10.NxtW = &Y11;
	L20.NxtW = &Y21;

    L10.NxtE = &L11;
    L20.NxtE = &L21;

    P11.NxtE = &L21;
    P21.NxtE = &L31;

    L11.NxtW = &L10;
    L21.NxtW = &L20;
	L31.NxtW = &P21;

    L11.NxtE = &D10;
    L21.NxtE = &D20;
    L31.NxtE = &D20;

    LathamAborts = 0;
    CarltonAborts = 0;

    L20.Dir = P21.Dir = L21.Dir = L31.Dir = true;

//Pointer setup

	LaKr.USSCol[0].pSw = &LSw1; LaKr.USSCol[0].pFltL = &LFltL2;
    LaKr.USSCol[1].pSw = &LSw3; LaKr.USSCol[1].pSigL = &LSigL4;
    LaKr.USSCol[2].pSw = &LSw5; LaKr.USSCol[2].pSigL = &LSigL6;
    LaKr.USSCol[3].pSw = &LSw7; LaKr.USSCol[3].pSigL = &LSigL8;
    LaKr.USSCol[4].pSw = &LSw9;
    LaKr.USSCol[5].pSw = &LSw11; LaKr.USSCol[5].pFltL = &LFltL12;
    LaKr.USSCol[6].pSw = &LSw13; LaKr.USSCol[6].pSigL = &LSigL14;
    LaKr.USSCol[7].pSw = &LSw15; LaKr.USSCol[7].pSigL = &LSigL16;
    LaKr.USSCol[8].pSw = &LSw17; LaKr.USSCol[8].pSigL = &LSigL18;

//Lever setup

    LaKr.USSCol[1].Long = LaKr.USSCol[3].Long = LaKr.USSCol[5].Long =
   							LaKr.USSCol[7].Long = true;

   	LSw1.N = LSw3.N = LSw5.N = LSw7.N = LSw9.N = LSw15.N = LSw17.N = true;
   	LFltL2.N = true;
   	LSigL4.CButton = LSigL4.N = true;
   	LSigL6.CButton = LSigL6.N = true;
   	LSigL8.CButton = LSigL8.N = true;
   	LSw11.Hand = LSw11.N = true; LSw11.pBlk = &L11;
   	LFltL12.N = true;
   	LSw13.Hand = LSw13.N = true; LSw13.pBlk = &L31;
   	LSigL14.CButton = LSigL14.N = true;
   	LSigL16.CButton = LSigL16.N = LSigL16.LockL = true;
   	LSigL18.CButton = LSigL18.N = true;

   	//Enable columns

   	LaKr.USSCol[0].Enabled = true;
   	LaKr.USSCol[1].Enabled = true;
   	LaKr.USSCol[2].Enabled = true;
   	LaKr.USSCol[3].Enabled = true;
   	LaKr.USSCol[4].Enabled = true;
   	LaKr.USSCol[5].Enabled = true;
   	LaKr.USSCol[6].Enabled = true;
   	LaKr.USSCol[7].Enabled = true;
	LaKr.USSCol[8].Enabled = true;

	//Switches

	LSw1.NI = LSw3.NI = LSw5.NI = LSw7.NI = LSw9.NI = true;
	LSw11.NI = LSw13.NI = LSw15.NI = LSw17.NI = true;

	//Block IDs

	L10.BlkID = "L10";
	L11.BlkID = "L11";
	L20.BlkID = "L20";
	L21.BlkID = "L21";
	L31.BlkID = "L31";
//Loco pointers

	L10.pLoco = L11.pLoco = L20.pLoco = L21.pLoco = L31.pLoco = &DummyLoco;

}

//Latham service function-----------------------------------------------------

void TPSRY::Latham(void)
{

//Hand-operated switches at Carlton

	HandSwitch(23, 9, true, &LSw11);
   	HandSwitch(27, 15, false, &LSw13);

//Latham Jct Interlocking-------------------------------------------------------

//Fleet lever lock

	if(LSigL4.L || LSigL4.R || LSigL6.L || LSigL6.R || LSigL8.L || LSigL8.R || LFltL2.R)
   		LFltL2.L = false;
   	else
   		LFltL2.L = true;

//Clear routes and switch locks

	L10.RtE = L20.RtE = P11.RtE = P21.RtE = Nil;
	L11.RtW = L21.RtW = L31.RtW = Nil;

   	if(LSw1.Out || LSw3.Out || LSw5.Out || LSw7.Out || LSw9.Out)
      	LSw1.L = LSw3.L = LSw5.L = LSw7.L = LSw9.L = true;
	else
		LSw1.L = LSw3.L = LSw5.L = LSw7.L = LSw9.L = false;

//Switch-switch locks

	LSw5.L = LSw7.R && OSSLockOn->Checked;
   	LSw7.L = LSw5.R && OSSLockOn->Checked;
   	LSw3.L = LSw9.R && OSSLockOn->Checked;
   	LSw9.L = LSw3.R && OSSLockOn->Checked;

//set pointers, routes and switch locks in accordance with switch positions
//and OS occupancy

	if (LSw5.NI && LSw7.NI)
   	{
		L10.NxtE = &L11;								//L10 to L11
		L11.NxtW = &L10;
      	L10.RtE = Restricting;
      	L11.RtW = Main;
      	L10.OSE = L11.OSW = LOS1;
   		if(LSigL8.R || LSigL8.L || L10.OSE && OSSLock)
      		LSw5.L = LSw7.L = true;
	}

	else if (LSw5.RI && LSw7.NI && LSw9.NI)
   	{
		L10.NxtE = &L21;								//L10 to L21
		L21.NxtW = &L10;
   		L10.RtE = Restricting;
      	L21.RtW = Diverging;
      	L10.OSE = L21.OSW = LOS1 || LOS2;
      	if(LSigL8.R || LSigL6.L || L10.OSE && OSSLock)
      		LSw5.L = LSw7.L = LSw9.L = true;
	}

	else if (LSw5.RI && LSw7.NI && LSw9.RI)
   	{
		L10.NxtE = &L31;								//L10 to L31
		L31.NxtW = &L10;
   		L10.RtE = L31.RtW = Restricting;
      	L10.OSE = L31.OSW = LOS1 || LOS2 || LOS3;
      	if(LSigL8.R || LSigL4.L || L10.OSE && OSSLock)
      		LSw5.L = LSw7.L = LSw9.L = true;
	}

	if (LSw1.NI && LSw3.NI && LSw5.NI && LSw7.RI)
   	{
		L20.NxtE = &L11;								//L20 to L11
		L11.NxtW = &L20;
   		L20.RtE = L11.RtW = Restricting;
      	L20.OSE = L11.OSW = LOS2 || LOS1;
      	if(LSigL6.R || LSigL8.L || L20.OSE && OSSLock)
      		LSw1.L = LSw3.L = LSw5.L = LSw7.L = true;
	}

	else if (LSw1.NI && LSw3.NI && LSw5.NI && LSw7.NI && LSw9.NI)
   	{
		L20.NxtE = &L21;								//L20 to L21
		L21.NxtW = &L20;
   		L20.RtE = Main;
      	L21.RtW = Restricting;
      	L20.OSE = L21.OSW = LOS2;
      	if(LSigL6.R || LSigL6.L || L20.OSE && OSSLock)
      		LSw1.L = LSw3.L = LSw5.L = LSw7.L = LSw9.L = true;
	}

	else if (LSw1.NI && LSw3.NI && LSw5.NI && LSw7.NI && LSw9.RI)
   	{
		L20.NxtE = &L31;								//L20 to L31
		L31.NxtW = &L20;
      	L20.RtE = Diverging;
      	L31.RtW = Restricting;
      	L20.OSE = L31.OSW = LOS2 || LOS3;
      	if(LSigL6.R || LSigL4.L || L20.OSE && OSSLock)
      		LSw1.L = LSw3.L = LSw5.L = LSw7.L = LSw9.L = true;
	}

   	if (LSw1.RI && LSw3.NI && LSw5.NI && LSw7.RI)
   	{
		P11.NxtE = &L11;								//P11 to L11
		L11.NxtW = &P11;
      	P11.RtE = Restricting;
      	L11.RtW = Diverging;
      	P11.OSE = L11.OSW = LOS2 || LOS1;
      	if(LSigL6.R || LSigL8.L || P11.OSE && OSSLock)
      		LSw1.L = LSw3.L = LSw5.L = LSw7.L = true;
	}

	else if (LSw1.RI && LSw3.NI && LSw5.NI && LSw7.NI && LSw9.NI)
   	{
		P11.NxtE = &L21;								//P11 to L21
		L21.NxtW = &P11;
      	P11.RtE = Restricting;
      	L21.RtW = Diverging;
      	P11.OSE = L21.OSW = LOS2;
	   	if(LSigL6.R || LSigL6.L || P11.OSE && OSSLock)
      		LSw1.L = LSw3.L = LSw5.L = LSw7.L = LSw9.L = true;
	}

	else if (LSw1.RI && LSw3.NI && LSw5.NI && LSw7.NI && LSw9.RI)
   	{
		P11.NxtE = &L31;								//P11 to L31
		L31.NxtW = &P11;
      	P11.RtE = L31.RtW = Restricting;
      	P11.OSE = L31.OSW = LOS2 || LOS3;
      	if(LSigL6.R || LSigL4.L || P11.OSE && OSSLock)
       		LSw1.L = LSw3.L = LSw5.L = LSw7.L = LSw9.L = true;
	}

	if (LSw3.RI && LSw5.NI && LSw7.RI)
   	{
		P21.NxtE = &L11;								//P21 to L11
		L11.NxtW = &P21;
      	P21.RtE = L11.RtW = Restricting;
      	P21.OSE = L11.OSW = LOS3 || LOS2 || LOS1;
      	if(LSigL4.R || LSigL8.L || P21.OSE && OSSLock)
      		LSw3.L = LSw5.L = LSw7.L = true;
	}

	else if (LSw3.RI && LSw5.NI && LSw7.NI && LSw9.NI)
   	{
		P21.NxtE = &L21;								//P21 to L21
		L21.NxtW = &P21;
      	P21.RtE = Diverging;
      	L21.RtW = Restricting;
      	P21.OSE = L21.OSW = LOS3 || LOS2;
      	if(LSigL4.R || LSigL6.L || P21.OSE && OSSLock)
      		LSw3.L = LSw5.L = LSw7.L = LSw9.L = true;
	}

	else if (LSw3.NI && LSw9.NI)
   	{
		P21.NxtE = &L31;								//P21 to L31
		L31.NxtW = &P21;
      	P21.RtE = Main;
      	L31.RtW = Restricting;
      	P21.OSE = L31.OSW = LOS3;
      	if(LSigL4.R || LSigL4.L || P21.OSE && OSSLock)
      		LSw3.L = LSw9.L = true;
	}

	if(PortControl->Checked)
	   LSw3.L = LSw9.L = true;

//Interlocking Columns

 	USSColumn(&LaKr.USSCol[0]);
   	USSColumn(&LaKr.USSCol[1]);
   	USSColumn(&LaKr.USSCol[2]);
   	USSColumn(&LaKr.USSCol[3]);
 	USSColumn(&LaKr.USSCol[4]);

//Fleeting

	Fleeting(LFltL2.R, &LSigL4);
   	Fleeting(LFltL2.R, &LSigL6);
   	Fleeting(LFltL2.R, &LSigL8);

	if(PortControl->Checked)
		LSigL4.LockR = LSigL4.LockL = true;

//Control of signals 4L and 4R from PORT signal lever 32

	if(LSw3.NI && LSw9.NI && LSigL4.N)
		PortControl->Enabled = true;
	else
		PortControl->Enabled = false;
	if(!PASigL32.L && !PASigL32.R)
		DispatcherControl->Enabled = true;
	else
		DispatcherControl->Enabled = false;

	if(Sig4P != PortControl->Enabled)          //send to remote dispatcher if change
	{
		MessageToRemDis("Sig4P", BoolToStr(PortControl->Enabled));
		Sig4P = PortControl->Enabled;
	}
	if(Sig4D != DispatcherControl->Enabled)
	{
		MessageToRemDis("Sig4D", BoolToStr(DispatcherControl->Enabled));
		Sig4D = DispatcherControl->Enabled;
	}

//Signals

	if(PortControl->Checked && PASw35.NI)
	{
		Esig(PASigL32.R ,&LSigL4, &L4R, &P21, RegAspects);    //Signals controled by Port
		Wsig(PASigL32.L, &LSigL4, &L4L, &L31, RegAspects);
    }
	else
	{
		Esig(LSigL4.R ,&LSigL4, &L4R, &P21, RegAspects);    //Signals controlled by Dispatcher
		Wsig(LSigL4.L, &LSigL4, &L4L, &L31, RegAspects);
	}

   	Esig(LSigL6.R, &LSigL6, &L6RA, &L20, RegAspects);
	Esig(LSigL6.R, &LSigL6, &L6RB, &P11, RegAspects);
	Wsig(LSigL6.L, &LSigL6, &L6L, &L21, RegAspects);

	Esig(LSigL8.R, &LSigL8, &L8R, &L10, RegAspects);
	Wsig(LSigL8.L, &LSigL8, &L8L, &L11, RegAspects);

//Set signal lever locks

	LSigL4.LockR = L4R.Lock || P21.LvrW;
	LSigL4.LockL = L4L.Lock || L31.LvrE;
	LSigL6.LockR = (L6RA.Lock || L20.LvrW) && (L6RB.Lock || P11.LvrW);
	LSigL6.LockL = L6L.Lock || L21.LvrE;
	LSigL8.LockR = L8R.Lock || L10.LvrW;
	LSigL8.LockL = L8L.Lock || L11.LvrE;

//Carlton interlocking----------------------------------------------------------

//Fleet lever lock

	if(LSigL14.L || LSigL14.R || LSigL16.R || LSigL18.L || LSigL18.R || LFltL12.R)
   		LFltL12.L = false;
   	else
   		LFltL12.L = true;

//Clear routes and switch locks

	L11.RtE = L21.RtE = L31.RtE = Nil;
   	D10.RtW = D20.RtW = Nil;

   	if(LSw15.Out || LSw17.Out)
   		LSw15.L = LSw17.L = true;
   	else
   		LSw15.L = LSw17.L = false;

//set pointers, routes and switch locks in accordance with switch positions
//and OS occupancy

	if(LSw15.NI)
   	{
		L11.NxtE = &D10;				//L11 to D10
		D10.NxtW = &L11;
   		L11.RtE = Restricting;
      	D10.RtW = Main;
      	L11.OSE = D10.OSW = CAOS1;
      	if(LSigL18.R || LSigL18.L || L11.OSE && OSSLock)
      		LSw15.L = true;
	}

	if(LSw15.RI)
   	{
		L21.NxtE = &D10;				//L21 to D10
		D10.NxtW = &L21;
      	L21.RtE = Restricting;
      	D10.RtW = Diverging;
      	L21.OSE = D10.OSW = CAOS2 || CAOS1;
      	if(LSigL16.R || LSigL18.L || L21.OSE && OSSLock)
      		LSw15.L = true;
	}

  	if(LSw15.NI && LSw17.NI)
   	{
		L21.NxtE = &D20;				//L21 to D20
		D20.NxtW = &L21;
      	L21.RtE = Main;
      	D20.RtW = Restricting;
      	L21.OSE = D20.OSW = CAOS2 || CAOS3;
      	if(LSigL16.R || LSigL14.L || L21.OSE && OSSLock)
      		LSw15.L = LSw17.L = true;
	}

	if(LSw17.RI)
   	{
		L31.NxtE = &D20;				//L31 to D20
		D20.NxtW = &L31;
      	L31.RtE = Diverging;
      	D20.RtW = Restricting;
      	L31.OSE = D20.OSW = CAOS3;
      	if(LSigL14.R || LSigL14.L || L31.OSE && OSSLock)
      		LSw17.L = true;
	}

//Interlocking Columns

   	USSColumn(&LaKr.USSCol[5]);
   	USSColumn(&LaKr.USSCol[6]);
   	USSColumn(&LaKr.USSCol[7]);
	USSColumn(&LaKr.USSCol[8]);

//Fleeting

	Fleeting(LFltL12.R, &LSigL14);
   	Fleeting(LFltL12.R, &LSigL16);
   	Fleeting(LFltL12.R, &LSigL18);

//Signals

	Esig(LSigL14.R, &LSigL14, &L14R, &L31, RegAspects);
	Wsig(LSigL14.L, &LSigL14, &L14L, &D20, RegAspects);

	Esig(LSigL16.R, &LSigL16, &L16R, &L21, RegAspects);

	Esig(LSigL18.R, &LSigL18, &L18R, &L11, RegAspects);
	Wsig(LSigL18.L, &LSigL18, &L18L, &D10, AdvAspects);	//Advance approach aspect

//Set signal lever locks

	LSigL14.LockR = L14R.Lock || L31.LvrW;
	LSigL14.LockL = L14L.Lock || D20.LvrE;
	LSigL16.LockR = L16R.Lock || L21.LvrW;
	LSigL18.LockR = L18R.Lock || L11.LvrW;
	LSigL18.LockL = L18L.Lock || D10.LvrE;

//Block indications

	BlkInd(&L20);
   	BlkInd(&P21);
   	BlkInd(&L11);
   	BlkInd(&L21);
   	BlkInd(&L31);
   	BlkInd(&D10);

//Train control

	TC(&L20, &Y4RA, &L6RA);
	TC(&P21, &PA32L, &L4R);
	TC(&L11, &L8L, &L18R);
	TC(&L21, &L6L, &L16R);
	TC(&L31, &L4L, &L14R);
   	TC(&D10, &L18L, &D6RB);

   	TrainID(&L10);
   	TrainID(&L20);
   	TrainID(&P21);
   	TrainID(&L11);
   	TrainID(&L21);
   	TrainID(&L31);
   	TrainID(&D10);

//Display

//Switches

	Switch(11, 12, &LSw1, 2, 8);
	Switch(12, 14, &LSw3, 8, 6);
   	Switch(14, 12, &LSw3, 2, 8);

   	Switch(13, 10, &LSw5, 2, 9);
   	Switch(15, 12, &LSw5, 2, 10);

   	Switch(16, 12, &LSw7, 2, 11);
   	Switch(18, 10, &LSw7, 2, 8);

   	Switch(17, 12, &LSw9, 2, 9);
   	Switch(19, 14, &LSw9, 2, 10);

   	Switch(23, 10, &LSw11, 2, 11);
   	Switch(27, 14, &LSw13, 2, 8);

   	Switch(31, 12, &LSw15, 2, 11);
   	Switch(33, 10, &LSw15, 2, 8);

   	Switch(34, 12, &LSw17, 2, 8);

//Block status

 	Tracker(0, 10, &L10, DBlk);
	Tracker(0, 12, &L20, DBlk);
	Tracker(0, 14, &P11, DBlk);
   	Tracker(0, 16, &P21, DBlk);

	XTracker (8, 10, &L10, OSE, &LOS1);
	XTracker (8, 12, &L20, OSE, &LOS2);
	XTracker (8, 14, &P11, OSE, &LOS2);
	XTracker (8, 16, &P21, OSE, &LOS3);

	Tracker (21, 10, &L11, DBlk);
	Tracker (21, 12, &L21, DBlk);
	Tracker (21, 14, &L31, DBlk);

	XTracker (30, 10, &L11, OSE, &CAOS1);
	XTracker (30, 12, &L21, OSE, &CAOS2);
	XTracker (30, 14, &L31, OSE, &CAOS3);

   	Tracker (36, 10, &D10, DBlk);

//Signals

	SignalE(8, 11, &L10);	//L8R
   	SignalE(8, 13, &L20);	//L6RA
   	SignalE(8, 15, &P11);	//L6RB
   	SignalE(8, 17, &P21);	//L4R

  	SignalW(20, 9, &L11);	//L8L
   	SignalW(20, 11, &L21);	//L6L
   	SignalW(20, 13, &L31);	//L4L

  	SignalE(30, 11, &L11);	//L18R
   	SignalE(30, 13, &L21);	//L16R
   	SignalE(30, 15, &L31);	//L14R

	SignalW(35, 9, &D10);	//L18L
   	SignalW(35, 11, &D20);	//L14L
   	SignalE(46, 11, &D10);  //D6RB

//Train identification

	DisplayID(3, 10, &L10);
	DisplayID(3, 12, &L20);
	DisplayID(3, 14, &P11);
	DisplayID(3, 16, &P21);

	DisplayID(25, 10, &L11);
	DisplayID(22, 12, &L21);
	DisplayID(22, 14, &L31);

	DisplayID(38, 10, &D10);
}
//---------------------------------------------------------------------------

