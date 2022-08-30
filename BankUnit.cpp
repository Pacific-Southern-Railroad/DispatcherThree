//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "BankUnit.h"
//---------------------------------------------------------------------------

//Initialize Bank

void TPSRY::InitializeBank(void)
{
	B10.NxtE = &B11;
	B10.NxtW = &N12;
	B20.NxtE = &B21;
	B20.NxtW = &N22;
	B11.NxtE = &C13;
	B11.NxtW = &B10;
	B21.NxtE = &C13;
	B21.NxtW = &B20;

	BankAborts = 0;

	B20.Dir = B21.Dir = true;

//Pointer setup

	NaCf.USSCol[13].pSigL = &CSigL24;                           	//Signal 24
	NaCf.USSCol[14].pSw = &CSw23; NaCf.USSCol[14].pSigL = &CSigL22;   //Switch 23, Signal 22
	NaCf.USSCol[15].pSw = &CSw21;                               	//Switch 21
	NaCf.USSCol[16].pSw = &CSw19; NaCf.USSCol[16].pSigL = &CSigL18;   //Switch 19, Signal 18
	NaCf.USSCol[17].pSw = &CSw17; 								//Switch 17

//Lever setup

	NaCf.USSCol[14].Long = NaCf.USSCol[16].Long = true;
	CSw23.N = true;
	CSigL24.CButton = CSigL24.N = true;
	CSw21.Hand = CSw21.N = true; CSw21.pBlk = &B11;
	CSigL22.CButton = CSigL22.N = true;
	CSw19.Hand = CSw19.N = true; CSw19.pBlk = &B21;
	CFltL16.N = true;
	CSw17.N = true;
	CSigL18.CButton = CSigL18.N = true;

	//Switches

	CSw23.NI = CSw19.NI = CSw17.NI = true;
	CSw21.NI = CSw21A.NI = CSw21B.NI = true;

    //Block ID

	B10.BlkID = "B10";
	B20.BlkID = "B20";
	B11.BlkID = "B11";
	B21.BlkID = "B21";

	//Loco pointers

    B10.pLoco = B20.pLoco = B11.pLoco = B21.pLoco = &DummyLoco;
}

//Bank service function

void TPSRY::Bank(void)
{
//Interlocking at Bank West

//Fleet lever lock for Bank and Cliveden signals

	if(CSigL24.L || CSigL24.R || CSigL22.L || CSigL22.R || CSigL18.L || CSigL18.R ||
			CSigL14.L || CSigL14.R || CSigL12.L || CSigL12.R || CSigL10.L || CSigL10.R ||
				CFltL16.R)
		CFltL16.L = false;
   else
		CFltL16.L = true;

//Clear routes & switch locks

	B10.RtE = B11.RtW = B20.RtE = B21.RtW = Nil;

	CSw23.L = CSw17.L = false;

//set pointers, routes and switch locks in accordance with switch positions and
//OS occupancy

	if(CSw23.NI)
	{
		B10.NxtE = &B11;		//B10 to B11
		B11.NxtW = &B10;
		B10.RtE = Restricting;
		B11.RtW = Main;
		B10.OSE = B11.OSW = BKOS1;
		if(CSigL22.R || CSigL22.L || B10.OSE && OSSLock)
			CSw23.L = true;
	}

	if(CSw23.RI)
	{
		B10.NxtE = &B21;		//B10 to B21
		B21.NxtW = &B10;
		B10.RtE = Restricting;
		B21.RtW = Diverging;
		B10.OSE = B21.OSW = BKOS1 || BKOS2;
		if(CSigL22.R || CSigL24.L || B10.OSE && OSSLock)
			CSw23.L = true;
	}

	if(CSw23.NI)
	{
		B20.NxtE = &B21;		//B20 to B21
		B21.NxtW = &B20;
		B20.RtE = Main;
		B21.RtW = Restricting;
		B20.OSE = B21.OSW = BKOS2;
		if(CSigL24.R || CSigL24.L || B20.OSE && OSSLock)
			CSw23.L = true;
	}

//Hand-operated switches

	HandSwitch(63, 13, false, &CSw19);
	HandSwitch(63, 9, true, &CSw21);
	HandAdditional(66, 9, true, &CSw21);

//Fleeting

	Fleeting(CFltL16.R, &CSigL24);
	Fleeting(CFltL16.R, &CSigL22);

//Set signal lever locks

	CSigL24.LockR = C24R.Lock || B20.LvrW;
	CSigL24.LockL = C24L.Lock || B21.LvrE;
	CSigL22.LockR = C22R.Lock || B10.LvrW;
	CSigL22.LockL = C22L.Lock || B11.LvrE;

//Set signals

	Esig(CSigL24.R, &CSigL24, &C24R, &B20, RegAspects);
	Wsig(CSigL24.L, &CSigL24, &C24L, &B21, RegAspects);
	SigInd(&CSigL24);

	Esig(CSigL22.R, &CSigL22, &C22R, &B10, RegAspects);
	Wsig(CSigL22.L, &CSigL22, &C22L, &B11, RegAspects);
	SigInd(&CSigL22);

//Set signal lever locks

	CSigL24.LockR = C24R.Lock || B20.LvrW;
	CSigL24.LockL = C24L.Lock || B21.LvrE;
	CSigL22.LockR = C22R.Lock || B10.LvrW;
	CSigL22.LockL = C22L.Lock || B11.LvrE;

//Interlocking at Bank East

//Clear routes

	B11.RtE = B21.RtE = C13.RtW = Nil;

//set pointers, routes and switch locks in accordance with switch positions and
//OS occupancy

	if(CSw17.RI)
	{
		B11.NxtE = &C13;		//B11 to C13
		C13.NxtW = &B11;
		B11.RtE = Restricting;
		C13.RtW = Diverging;
		B11.OSE = C13.OSW = BKOS3;
		if(CSigL18.R || CSigL18.L || B11.OSE && OSSLock)
			CSw17.L = true;
	}

	if(CSw17.NI)
	{
		B21.NxtE = &C13;		//B21 to C13
		C13.NxtW = &B21;
		B21.RtE = C13.RtW = Main;
		B21.OSE = C13.OSW = BKOS3;
		if(CSigL18.R || CSigL18.L || B21.OSE && OSSLock)
			CSw17.L = true;
	}

//Interlocking Columns

	USSColumn(&NaCf.USSCol[13]);
	USSColumn(&NaCf.USSCol[14]);
	USSColumn(&NaCf.USSCol[15]);
	USSColumn(&NaCf.USSCol[16]);
    USSColumn(&NaCf.USSCol[17]);

//Set signals

	Esig(CSigL18.R, &CSigL18, &C18RA, &B11, RegAspects);
	Esig(CSigL18.R, &CSigL18, &C18RB, &B21, RegAspects);
	Wsig(CSigL18.L, &CSigL18, &C18L, &C13, RegAspects);

	SigInd(&CSigL18);

//Set signal lever locks

	CSigL18.LockR = (C18RA.Lock || B11.LvrW) && (C18RB.Lock || B21.LvrW);
	CSigL18.LockL = C18L.Lock || C13.LvrE;

//Block indications

	BlkInd(&B20);
	BlkInd(&B11);
	BlkInd(&B21);

//Train control & identification

	TC(&B20, &N24L, &C24R);
	TC(&B11, &C22L, &C18RA);
	TC(&B21, &C24L, &C18RB);

	TrainID(&B20);
	TrainID(&B11);
	TrainID(&B21);

//Update Nassau-Cliff image

//Switches

	Switch(54, 10, &CSw23, 2, 9);
	Switch(56, 12, &CSw23, 2, 10);
	Switch(63, 10, &CSw21A, 2, 10);
	Switch(66, 10, &CSw21B, 2, 10);
	Switch(63, 12, &CSw19, 2, 9);
	Switch(71, 12, &CSw17, 2, 10);

//Blocks

	Tracker(45, 12, &B20, DBlk);

	XTracker(53, 10, &B10, OSE, &BKOS1);
	XTracker(53, 12, &B20, OSE, &BKOS2);

	Tracker(58, 10, &B11, DBlk);
	Tracker(58, 12, &B21, DBlk);

	XTracker(68, 10, &B11, OSE, &BKOS3);
	XTracker(68, 12, &B21, OSE, &BKOS3);

//Signals

	SignalE(53, 11, &B10); //22L
	SignalE(53, 13, &B20); //24L
	SignalW(57, 9, &B11);  //22R
	SignalW(57, 11, &B21); //24R

	SignalE(68, 11, &B11); //18LB
	SignalE(68, 13, &B21); //18LB
//Train identification

	DisplayID(46, 12, &B20);
	DisplayID(59, 10, &B11);
	DisplayID(59, 12, &B21);

//DCC Circuit Breaker

	CBBank = Flash && CktBkr[9];
}
