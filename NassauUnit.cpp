//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "NassauUnit.h"

//Initialize Nassau

void TPSRY::InitializeNassau()
{
	N11.NxtW = &N10;
   	N11.NxtE = &N12;

   	N12.NxtW = &N11;
   	N12.NxtE = &B10;

   	N21.NxtW = &N20;
   	N21.NxtE = &N22;

   	N22.NxtW = &N21;
	N22.NxtE = &B20;

	N31.NxtW = &N60;
   	N31.NxtE = &B10;

	N32.NxtW = &N60;
   	N32.NxtE = &B10;

   	N41.NxtW = &N21;
   	N41.NxtE = &B20;

   	N42.NxtW = &N21;
   	N42.NxtE = &B20;

	N60.NxtW = &DummyBlock;
	N60.NxtE = &N31;

   	T12.NxtW = &DummyBlock;
   	T12.NxtE = &W10;

   	W10.NxtW = &T12;
   	W10.NxtE = &DummyBlock;

   	W11.NxtW = &DummyBlock;
	W11.NxtE = &R10;

	W20.NxtE = &DummyBlock;
	W20.NxtW = &DummyBlock;

   	R10.NxtW = &W11;
   	R10.NxtE = &F10;

   	NassauWAborts = 0;
   	NassauEAborts = 0;

	N21.Dir = N22.Dir = N41.Dir = N42.Dir = W11.Dir = N60.Dir = true;
	N60A.Dir = N60B.Dir = N60C.Dir = N60D.Dir = true;

	//Pointer setup

	NaCf.USSCol[0].pFltL = &NFltL12;
	NaCf.USSCol[1].pSigL = &NSigL14;
	NaCf.USSCol[2].pSigL = &NSigL16;
	NaCf.USSCol[3].pSigL = &NSigL18;
	NaCf.USSCol[4].pSigL = &NSigL20;
	NaCf.USSCol[6].pSigL = &NSigL24;
	NaCf.USSCol[7].pSigL = &NSigL26;
	NaCf.USSCol[8].pSigL = &NSigL28;

	//Lever setup

	NaCf.USSCol[1].Long = NaCf.USSCol[3].Long = NaCf.USSCol[5].Long = NaCf.USSCol[7].Long = true;
	NSigL14.CButton = NSigL14.N = true;
	NSigL16.CButton = NSigL16.N = true;
	NSigL18.CButton = NSigL18.N = true;
	NSigL20.CButton = NSigL20.N = true;
	NFltL12.N = true;
	NSigL24.CButton = NSigL24.N = true;
	NSigL26.CButton = NSigL26.N = true;
	NSigL28.CButton = NSigL28.N = true;

	//Switches

	NSw13.NI = NSw15.NI = NSw17.NI = true;
	NSw19.NI = NSw21.NI = NSw23.NI = NSw25.NI = NSw27.NI = NSw29.NI =
		NSw31.NI = NSw33.NI = NSw35.NI = true;
	NSw39.NI = NSw41.NI = NSw43.NI = NSw45.NI = NSw47.NI = NSw51.NI = NSw53.NI =
		NSw55.NI = NSw57.NI = true;

	// NX
	NWLeft = NWRight = NELeft = NERight = 0;

	//Signals

	NSigL14.N = NSigL16.N = NSigL18.N = NSigL20.N = true;
	NSigL24.N = NSigL26.N = NSigL28.N = true;

	//Block IDs

	N10.BlkID = "N10";
	N20.BlkID = "N20";
	K10.BlkID = "K10";
	N11.BlkID = "N11";
	N21.BlkID = "N21";
	T12.BlkID = "T12";
	N60.BlkID = "N60";
	N60A.BlkID = "N60A";
	N60B.BlkID = "N60B";
	N60C.BlkID = "N60C";
	N60D.BlkID = "N60D";
	W10.BlkID = "W10";
	W11.BlkID = "W11";
	N32.BlkID = "N32";
	N31.BlkID = "N31";
	N12.BlkID = "N12";
	N22.BlkID = "N22";
	N41.BlkID = "N41";
	N42.BlkID = "N42";
	W20.BlkID = "W20";

	R10.BlkID = "R10";

    //Loco pointers

	N10.pLoco = N20.pLoco = K10.pLoco = N11.pLoco = N21.pLoco = T12.pLoco = &DummyLoco;
	N60.pLoco = N60A.pLoco = N60B.pLoco = N60C.pLoco = N60D.pLoco = W10.pLoco = &DummyLoco;
	W11.pLoco = N32.pLoco = N31.pLoco = N12.pLoco = N22.pLoco = N41.pLoco = &DummyLoco;
	N42.pLoco = W20.pLoco = R10.pLoco = &DummyLoco;

	PulseTime = 0;      //Nassau NX pulses

	NassauWState = NassauEState = Idle;
}

//Nassau service function

void TPSRY::Nassau()
{
//Coach yard

	N60A.NxtE = N60B.NxtE = N60C.NxtE = N60D.NxtE = &DummyBlock;
	N60A.RtE = N60B.RtE = N60C.RtE = N60D.RtE = N60.RtW = Nil;
	N60A.ClrW = N60B.ClrW = N60C.ClrW = N60D.ClrW = false;
	N60.ClrW = true;

	if(NSw13.RI && NSw17.RI)
	{
		N60A.NxtE = N60.NxtE;       //N60A to N60
		N60.NxtW = &N60A;
		N60.RtW = N60A.RtE = Restricting;
		N60A.OSE = N60.OSE;
	}

	else if(NSw13.NI && NSw17.RI)
	{
		N60B.NxtE = N60.NxtE;       //N60B to N60
		N60.NxtW = &N60B;
		N60.RtW = N60B.RtE = Restricting;
		N60B.OSE = N60.OSE;
	}

	else if(NSw15.RI && NSw17.NI)
	{
		N60C.NxtE = N60.NxtE;       //N60C to N60
		N60.NxtW = &N60C;
		N60.RtW = N60C.RtE = Restricting;
        N60C.OSE = N60.OSE;
	}

	else if(NSw15.NI && NSw17.NI)
	{
		N60D.NxtE = N60.NxtE;       //N60D to N60
		N60.NxtW = &N60D;
		N60.RtW = N60D.RtE = Restricting;
		N60D.OSE = N60.OSE;
        N60D.RstrE = N60.RstrE;
	}
	Esig(NSigL18.R, &NSigL18, &N18RA, &N60D, SloAspects);
	Esig(NSigL18.R, &NSigL18, &N18RB, &N60C, SloAspects);
	Esig(NSigL18.R, &NSigL18, &N18RC, &N60B, SloAspects);
	Esig(NSigL18.R, &NSigL18, &N18RD, &N60A, SloAspects);
	N60.RstrW = true;

//"NASSAUW" interlocking ------------------------------------------------------

	if(NSigL14.L || NSigL14.R || NSigL16.L || NSigL16.R || NSigL18.L || NSigL18.R ||
		NSigL24.L || NSigL24.R || NSigL26.L || NSigL26.R || NFltL12.R)
		NFltL12.L = false;
	else
		NFltL12.L = true;

//Clear routes and switch locks

	T12.RtE = N60.RtE = N11.RtE = N21.RtE = Nil;
	W10.RtW = N32.RtW = N31.RtW = N12.RtW = N22.RtW = N41.RtW = N42.RtW = W20.RtW = Nil;

	NWSL2 = NWSL3 = NWSL4 = false;
	if(RBNDispatcherMain->Checked)
		NWSL1 = true;
	else
		NWSL1 = false;

//set pointers, routes and switch locks in accordance with switch positions and
//OS occupancy

	if(NSw25.NI)
   	{
   		T12.NxtE = &W10;         	//T12 to W10
      	W10.NxtW = &T12;
		T12.RtE = W10.RtW = Restricting;
		T12.OSE = W10.OSW = NWOS1;
      	if(NSigL20.R || NSigL20.L || T12.OSE && !NRelease)
      		NWSL1 = true;
   	}

   	if(NSw27.NI && NSw21.NI && NSw23.NI)
   	{
		N60.NxtE = &N31;				//N60 to N31
		N31.NxtW = N60.NxtW;
		N60.RtE = N31.RtW = Restricting;
		N60.OSE = N31.OSW = NWOS2;
		if(NSigL18.R || NSigL18.L || N60.OSE && !NRelease)
			NWSL2 = true;
	}

	else if(NSw27.NI && NSw21.NI && NSw23.RI && NSw25.RI)
	{
		N60.NxtE = &W10;				//N60 to W10
		W10.NxtW = N60.NxtW;
		N60.RtE = W10.RtW = Restricting;
		N60.OSE = W10.OSW = NWOS2 || NWOS1;
		if(NSigL18.R || NSigL20.L || N60.OSE && !NRelease)
			NWSL1 = NWSL2 = true;
	}

	else if(NSw27.NI && NSw21.NI && NSw23.RI && NSw25.NI)
	{
		N60.NxtE = &N32;				//N60 to N32
		N32.NxtW = N60.NxtW;
		N60.RtE = N32.RtW = Restricting;
		N60.OSE = N32.OSW = NWOS2;
		if(NSigL18.R || NSigL18.L || N60.OSE && !NRelease)
			NWSL2 = true;
	}

	else if(NSw27.RI && NSw29.NI && NSw21.NI)
	{
		N60.NxtE = &N12;				//N60 to N12
		N12.NxtW = N60.NxtW;
		N60.RtE = N12.RtW = Restricting;
		N60.OSE = N12.OSW = NWOS2 || NWOS3;
		if(NSigL18.R || NSigL16.L || N60.OSE && !NRelease)
			NWSL2 = NWSL3 = true;
	}

	else if(NSw27.RI && NSw29.RI && NSw31.NI)
	{
		N60.NxtE = &N22;				//N60 to N22
		N22.NxtW = N60.NxtW;
		N60.RtE = N22.RtW = Restricting;
		N60.OSE = N22.OSW = NWOS2 || NWOS3 || NWOS4;
		if(NSigL18.R || NSigL14.L || N60.OSE && !NRelease)
			NWSL2 = NWSL3 = NWSL4 = true;
	}

	else if(NSw27.RI && NSw29.RI && NSw31.RI && NSw33.RI)
	{
		N60.NxtE = &N41;				//N60 to N41
		N41.NxtW = N60.NxtW;
		N60.RtE = N41.RtW = Restricting;
		N60.OSE = N41.OSW = NWOS2 || NWOS3 || NWOS4;
		if(NSigL18.R || NSigL14.L || N60.OSE && !NRelease)
			NWSL2 = NWSL3 = NWSL4 = true;
	}

	else if(NSw27.RI && NSw29.RI && NSw31.RI && NSw33.NI && NSw35.RI)
	{
		N60.NxtE = &N42;				//N60 to N42
		N42.NxtW = N60.NxtW;
		N60.RtE = N42.RtW = Restricting;
		N60.OSE = N42.OSW = NWOS2 || NWOS3 || NWOS4;
		if(NSigL18.R || NSigL14.L || N60.OSE && !NRelease)
			NWSL2 = NWSL3 = NWSL4 = true;
	}

	else if(NSw27.RI && NSw29.RI && NSw31.RI && NSw33.NI && NSw35.NI)
	{
		N60.NxtE = &W20;				//N60 to W20
		W20.NxtW = N60.NxtW;
		N60.RtE = W20.RtW = Restricting;
		N60.OSE = W20.OSW = NWOS2 || NWOS3 || NWOS4;
		if(NSigL18.R || NSigL14.L || N60.OSE && !NRelease)
			NWSL2 = NWSL3 = NWSL4 = true;
	}

	if(NSw19.NI && NSw27.NI && NSw29.NI && NSw21.NI)
	{
		N11.NxtE = &N12;				//N11 to N12
		N12.NxtW = &N11;
		N11.RtE = N12.RtW = Slow;
		N11.OSE = N12.OSW = NWOS3;
        if(NSigL16.R || NSigL16.L || N11.OSE && !NRelease)
      		NWSL3 = true;
	}

   	else if(NSw19.NI && NSw27.NI && NSw29.NI && NSw21.RI && NSw23.RI && NSw25.RI)
   	{
   		N11.NxtE = &W10;				//N11 to W10
      	W10.NxtW = &N11;
      	N11.RtE = W10.RtW = Restricting;
      	N11.OSE = W10.OSW = NWOS1 || NWOS2 || NWOS3;
      	if(NSigL16.R || NSigL20.L || N11.OSE && !NRelease)
      		NWSL1 = NWSL2 = NWSL3 = true;
   	}

   	else if(NSw19.NI && NSw27.NI && NSw29.NI && NSw21.RI && NSw23.RI && NSw25.NI)
   	{
   		N11.NxtE = &N32;				//N11 to N32
      	N32.NxtW = &N11;
      	N11.RtE = Restricting;
        N32.RtW = Slow;
      	N11.OSE = N32.OSW = NWOS2 || NWOS3;
      	if(NSigL16.R || NSigL18.L || N11.OSE && !NRelease)
      		NWSL2 = NWSL3 = true;
   	}

	else if(NSw19.NI && NSw27.NI && NSw29.NI && NSw21.RI && NSw23.NI)
	{
   		N11.NxtE = &N31;				//N11 to N31
      	N31.NxtW = &N11;
      	N11.RtE = Restricting;
        N31.RtW = Slow;
      	N11.OSE = N31.OSW = NWOS2 || NWOS3;
      	if(NSigL16.R || NSigL18.L || N11.OSE && !NRelease)
      		NWSL2 = NWSL3 = true;
   	}

   	else if(NSw19.NI && NSw27.NI && NSw29.RI && NSw31.NI)
   	{
   		N11.NxtE = &N22;				//N11 to N22
      	N22.NxtW = &N11;
      	N11.RtE = N22.RtW = Slow;
      	N11.OSE = N22.OSW = NWOS3 || NWOS4;
      	if(NSigL16.R || NSigL14.L || N11.OSE && !NRelease)
      		NWSL3 = NWSL4 = true;
   	}

   	else if(NSw19.NI && NSw27.NI && NSw29.RI && NSw31.RI && NSw33.RI)
   	{
   		N11.NxtE = &N41;				//N11 to N41
      	N41.NxtW = &N11;
      	N11.RtE = Slow;
      	N41.RtW = Restricting;
      	N11.OSE = N41.OSW = NWOS3 || NWOS4;
      	if(NSigL16.R || NSigL14.L || N11.OSE && !NRelease)
      		NWSL3 = NWSL4 = true;
   	}

	else if(NSw19.NI && NSw27.NI && NSw29.RI && NSw31.RI && NSw33.NI && NSw35.RI)
	{
		N11.NxtE = &N42;				//N11 to N42
		N42.NxtW = &N11;
		N11.RtE = Slow;
		N42.RtW = Restricting;
		N11.OSE = N42.OSW = NWOS3 || NWOS4;
		if(NSigL16.R || NSigL14.L || N11.OSE && !NRelease)
			NWSL3 = NWSL4 = true;
	}

	else if(NSw19.NI && NSw27.NI && NSw29.RI && NSw31.RI && NSw33.NI && NSw35.NI

	)
	{
		N11.NxtE = &W20;				//N11 to W20
		W20.NxtW = &N11;
		N11.RtE = W20.RtW = Restricting;
		N11.OSE = N42.OSW = NWOS3 || NWOS4;
		if(NSigL16.R || NSigL14.L || N11.OSE && !NRelease)
			NWSL3 = NWSL4 = true;
	}

   	if(NSw19.NI && NSw29.NI && NSw31.NI)
   	{
   		N21.NxtE = &N22;				//N21 to N22
      	N22.NxtW = &N21;
		N21.RtE = N22.RtW = Slow;
		N21.OSE = N22.OSW = NWOS4;
      	if(NSigL14.R || NSigL14.L || N21.OSE && !NRelease)
      		NWSL4 = true;
   	}

   	else if(NSw19.RI && NSw27.NI && NSw29.NI && NSw21.RI && NSw23.RI && NSw25.RI)
   	{
   		N21.NxtE = &W10;				//N21 to W10
      	W10.NxtW = &N21;
      	N21.RtE = W10.RtW = Restricting;
      	N21.OSE = W10.OSW = NWOS1 || NWOS2 || NWOS3 || NWOS4;
      	if(NSigL14.R || NSigL20.L || N21.OSE && !NRelease)
     	 	NWSL1 = NWSL2 = NWSL3 = NWSL4 = true;
   	}

   	else if(NSw19.RI && NSw27.NI && NSw29.NI && NSw21.RI && NSw23.RI && NSw25.NI)
   	{
   		N21.NxtE = &N32;				//N21 to N32
      	N32.NxtW = &N21;
      	N21.RtE = Restricting;
      	N32.RtW = Slow;
      	N21.OSE = N32.OSW = NWOS2 || NWOS3 || NWOS4;
      	if(NSigL14.R || NSigL18.L || N21.OSE && !NRelease)
      		NWSL2 = NWSL3 = NWSL4 = true;
   	}

   	else if(NSw19.RI && NSw27.NI && NSw29.NI && NSw21.RI && NSw23.NI)
   	{
   		N21.NxtE = &N31;				//N21 to N31
      	N31.NxtW = &N21;
      	N21.RtE = Restricting;
      	N31.RtW = Slow;
		N21.OSE = N31.OSW = NWOS2 || NWOS3 || NWOS4;
		if(NSigL14.R || NSigL18.L || N21.OSE && !NRelease)
      		NWSL2 = NWSL3 = NWSL4 = true;
	}

   	else if(NSw19.RI && NSw27.NI && NSw29.NI && NSw21.NI)
   	{
   		N21.NxtE = &N12;				//N21 to N12
      	N12.NxtW = &N21;
      	N21.RtE = Slow;
      	N12.RtW = Slow;
      	N21.OSE = N12.OSW = NWOS3 || NWOS4;
      	if(NSigL14.R || NSigL16.L || N21.OSE && !NRelease)
      		NWSL3 = NWSL4 = true;
   	}

   	else if(NSw19.NI && NSw29.NI && NSw31.RI && NSw33.RI)
   	{
   		N21.NxtE = &N41;				//N21 to N41
      	N41.NxtW = &N21;
      	N21.RtE = Slow;
      	N41.RtW = Restricting;
      	N21.OSE = N41.OSW = NWOS4;
		if(NSigL14.R || NSigL14.L || N21.OSE && !NRelease)
      		NWSL4 = true;
   	}

	else if(NSw19.NI && NSw29.NI && NSw31.RI && NSw33.NI && NSw35.RI)
	{
		N21.NxtE = &N42;				//N21 to N42
		N42.NxtW = &N21;
		N21.RtE = Slow;
		N42.RtW = Restricting;
		N21.OSE = N42.OSW = NWOS4;
		if(NSigL14.R || NSigL14.L || N21.OSE && !NRelease)
			NWSL4 = true;
	}

	else if(NSw19.NI && NSw29.NI && NSw31.RI && NSw33.NI && NSw35.NI)
	{
		N21.NxtE = &W20;				//N21 to W20
		W20.NxtW = &N21;
		N21.RtE = W20.RtW = Restricting;
		N21.OSE = N42.OSW = NWOS4;
		if(NSigL14.R || NSigL14.L || N21.OSE && !NRelease)
			NWSL4 = true;
	}

//Interlocking Columns

	USSColumn(&NaCf.USSCol[0]);
	USSColumn(&NaCf.USSCol[1]);
	USSColumn(&NaCf.USSCol[2]);
	USSColumn(&NaCf.USSCol[3]);
	USSColumn(&NaCf.USSCol[4]);
//Fleeting

	Fleeting(NFltL12.R, &NSigL14);
	Fleeting(NFltL12.R, &NSigL16);
	Fleeting(NFltL12.R, &NSigL18);

//Signals

	if((N20.pLoco->ATC || N21.pLoco->ATC) && N21.NxtE == &N22 && !N22.ClrE)   //Changes for ATC
		N22.Switch = true;
	else
		N22.Switch = false;
	if((N20.pLoco->ATC || N21.pLoco->ATC) && N21.NxtE == &N41 && !N41.ClrE)
		N41.Switch = true;
	else
		N41.Switch = false;
	if((N20.pLoco->ATC || N21.pLoco->ATC) && N21.NxtE == &N42 && !N42.ClrE)
		N42.Switch = true;
	else
		N42.Switch = false;

	Esig(NSigL14.R, &NSigL14, &N14R, &N21, SloAspects);
	Wsig(NSigL14.L, &NSigL14, &N14LA, &N22, SloAspects);
   	Wsig(NSigL14.L, &NSigL14, &N14LB, &N41, SloAspects);
	Wsig(NSigL14.L, &NSigL14, &N14LC, &N42, SloAspects);
	Wsig(NSigL14.L, &NSigL14, &N14LD, &W20, SloAspects);
	SigInd(&NSigL14);

   	Esig(NSigL16.R, &NSigL16, &N16R, &N11, SloAspects);
	Wsig(NSigL16.L, &NSigL16, &N16L, &N12, SloAspects);
	SigInd(&NSigL16);

	Esig(NSigL18.R, &NSigL18, &N18R, &N60, SloAspects);
	Wsig(NSigL18.L, &NSigL18, &N18LA, &N32, SloAspects);
   	Wsig(NSigL18.L, &NSigL18, &N18LB, &N31, SloAspects);
	SigInd(&NSigL18);

   	Esig(NSigL20.R, &NSigL20, &N20R, &T12, SloAspects);
   	Wsig(NSigL20.L, &NSigL20, &N20L, &W10, SloAspects);
	SigInd(&NSigL20);

//Signal lever lockss

	NSigL20.LockR = N20R.Lock;
	NSigL20.LockL = N20L.Lock;

	NSigL18.LockR = N18R.Lock;
    NSigL18.LockL = (N18LA.Lock || N32.LvrE) && (N18LB.Lock || N31.LvrE);

	NSigL16.LockR = N16R.Lock || N11.LvrW;
	NSigL16.LockL = N16L.Lock || N12.LvrE;

	NSigL14.LockR = N14R.Lock || N21.LvrW;
	NSigL14.LockL = (N14LA.Lock || N22.LvrE) && (N14LB.Lock || N41.LvrE) &&
		(N14LC.Lock || N42.LvrE);	NxtClr = N11.ClrW;
    NxtRte = N11.RtW;
    SetBsig(&N11W, N11.Blk, RegAspects);

    Clear = !N21.Dir && !N21.W && !N21.M && !N21.E;  //Block signal N21W
    NxtClr = N21.ClrW;
    NxtRte = N21.RtW;
    SetBsig(&N21W, N21.Blk, RegAspects);

//NASSAUE Interlocking--------------------------------------------------------

//Clear routes and switch locks

	W11.RtW = W11.RtE = R10.RtE = Nil;
	N32.RtE = N31.RtE = N12.RtE = N22.RtE = N41.RtE = N42.RtE = Nil;
   	R10.RtW = B10.RtW = B20.RtW = Nil;

	NESL2 = NESL3 = false;
	if(RBNDispatcherMain->Checked)
		NESL1 = true;
	else
		NESL1 = false;
    
//set pointers, routes and switch locks in accordance with switch positions and
//OS occupancy

   	if(NSw55.NI && NSw47.NI)
   	{
   		W11.NxtE = &R10;			//W11 to R10
      	R10.NxtW = &W11;
      	W11.RtE = R10.RtW = Restricting;
      	W11.OSE = R10.OSW = NEOS1;
		if(NSigL28.R || NSigL28.L || W11.OSE && !NRelease)
      		NESL1 = true;
   	}
    else if(NSw51.NI && NSw53.RI && NSw55.NI && NSw45.NI && NSw47.RI)
   	{
   		N32.NxtE = &R10;			//N32 to R10
      	R10.NxtW = &N32;
      	N32.RtE = Restricting;
      	R10.RtW = Slow;
      	N32.OSE = R10.OSW = NEOS1 || NEOS2;
      	if(NSigL26.R || NSigL28.L || N32.OSE && !NRelease)
      		NESL1 = NESL2 = true;
   	}
   	else if(NSw51.RI && NSw53.RI && NSw55.NI && NSw45.NI && NSw47.RI)
   	{
   		N31.NxtE = &R10;			//N31 to R10
      	R10.NxtW = &N31;
      	N31.RtE = Restricting;
      	R10.RtW = Slow;
      	N31.OSE = R10.OSW = NEOS1 ||NEOS2;
   		if(NSigL26.R || NSigL28.L || N31.OSE && !NRelease)
      		NESL1 = NESL2 = true;
   	}
   	else if(NSw53.NI && NSw55.NI && NSw45.NI && NSw47.RI)
   	{
   		N12.NxtE = &R10;			//N12 to R10
      	R10.NxtW = &N12;
      	N12.RtE = Slow;
      	R10.RtW = Slow;
      	N12.OSE = R10.OSW = NEOS1 ||NEOS2;
   		if(NSigL26.R || NSigL28.L || N12.OSE && !NRelease)
      		NESL1 = NESL2 = true;
   	}
   	else if(NSw43.NI && NSw45.RI && NSw47.RI)
   	{
   		N22.NxtE = &R10;			//N22 to R10
      	R10.NxtW = &N22;
      	N22.RtE = R10.RtW = Slow;
      	N22.OSE = R10.OSW = NEOS1 || NEOS2 || NEOS3;
   		if(NSigL24.R || NSigL28.L || N22.OSE && !NRelease)
      		NESL1 = NESL2 = NESL3 = true;
   	}
	else if(NSw41.RI && NSw43.RI && NSw45.RI && NSw47.RI)
   	{
   		N41.NxtE = &R10;			//N41 to R10
      	R10.NxtW = &N41;
      	N41.RtE = Slow;
      	R10.RtW = Restricting;
      	N41.OSE = R10.OSW = NEOS1 || NEOS2 || NEOS3;
      	if(NSigL24.R || NSigL28.L || N41.OSE && !NRelease)
      		NESL1 = NESL2 = NESL3 = true;
   	}
	else if(NSw39.RI && NSw41.NI && NSw43.RI && NSw45.RI && NSw47.RI)
	{
		N42.NxtE = &R10;			//N42 to R10
		R10.NxtW = &N42;
		N42.RtE = Slow;
		R10.RtW = Restricting;
		N42.OSE = R10.OSW = NEOS1 || NEOS2 || NEOS3;
		if(NSigL24.R || NSigL28.L || N42.OSE && !NRelease)
			NESL1 = NESL2 = NESL3 = true;
	}
	else if(NSw39.NI && NSw41.NI && NSw43.RI && NSw45.RI && NSw47.RI)
	{
		W20.NxtE = &R10;			//W20 to R10
		R10.NxtW = &W20;
		W20.RtE = R10.RtW = Restricting;
		W20.OSE = R10.OSW = NEOS1 || NEOS2 || NEOS3;
		if(NSigL24.R || NSigL28.L || W20.OSE && !NRelease)
			NESL1 = NESL2 = NESL3 = true;
	}

   	if(NSw53.NI && NSw55.NI && NSw45.NI && NSw47.NI && NSw57.NI)
    {
   		N12.NxtE = &B10;			//N12 to B10
      	B10.NxtW = &N12;
      	N12.RtE = Restricting;
		B10.RtW = Slow;
      	N12.OSE = B10.OSW = NEOS2;
      	if(NSigL26.R || NSigL26.L || N12.OSE && !NRelease)
      		NESL2 = true;
   	}
   	else if(NSw55.RI && NSw45.NI && NSw47.NI && NSw57.NI)
   	{
   		W11.NxtE = &B10;			//W11 to B10
		B10.NxtW = &W11;
      	W11.RtE = B10.RtW = Restricting;
      	W11.OSE = B10.OSW = NEOS1 || NEOS2;
      	if(NSigL28.R || NSigL26.L || W11.OSE && !NRelease)
      		NESL1 = NESL2 = true;
   	}
   	else if(NSw51.NI && NSw53.RI && NSw55.NI && NSw45.NI && NSw47.NI && NSw57.NI)
   	{
   		N32.NxtE = &B10;			//N32 to B10
      	B10.NxtW = &N32;
      	N32.RtE = Restricting;
      	B10.RtW = Slow;
      	N32.OSE = B10.OSW = NEOS2;
       	if(NSigL26.R || NSigL26.L || N32.OSE && !NRelease)
      		NESL2 = true;
   	}
   	else if(NSw51.RI && NSw53.RI && NSw55.NI && NSw45.NI && NSw47.NI && NSw57.NI)
   	{
   		N31.NxtE = &B10;			//N31 to B10
      	B10.NxtW = &N31;
      	N31.RtE = Restricting;
      	B10.RtW = Slow;
      	N31.OSE = B10.OSW = NEOS2;
      	if(NSigL26.R || NSigL26.L || N31.OSE && !NRelease)
      		NESL2 = true;
   	}
   	else if(NSw43.NI && NSw45.RI && NSw47.NI && NSw57.NI)
   	{
   		N22.NxtE = &B10;			//N22 to B10
      	B10.NxtW = &N22;
      	N22.RtE = Restricting;
      	B10.RtW = Slow;
      	N22.OSE = B10.OSW = NEOS2 || NEOS3;
      	if(NSigL24.R || NSigL26.L || N22.OSE && !NRelease)
      		NESL2 = NESL3 = true;
   	}
   	else if(NSw41.RI && NSw43.RI && NSw45.RI && NSw47.NI && NSw57.NI)
   	{
   		N41.NxtE = &B10;			//N41 to B10
      	B10.NxtW = &N41;
      	N41.RtE = B10.RtW = Restricting;
      	N41.OSE = B10.OSW = NEOS2 || NEOS3;
      	if(NSigL24.R || NSigL26.L || N41.OSE && !NRelease)
      		NESL2 = NESL3 = true;
   	}
	else if(NSw39.RI && NSw41.NI && NSw43.RI && NSw45.RI && NSw47.NI && NSw57.NI)
	{
		N42.NxtE = &B10;			//N42 to B10
		B10.NxtW = &N42;
		N42.RtE = Restricting;
		B10.RtW = Restricting;
		N42.OSE = B10.OSW = NEOS2 || NEOS3;
		if(NSigL24.R || NSigL26.L || N42.OSE && !NRelease)
			NESL2 = NESL3 = true;
	}
	else if(NSw39.NI && NSw41.NI && NSw43.RI && NSw45.RI && NSw47.NI && NSw57.NI)
	{
		W20.NxtE = &B10;			//W20 to B10
		B10.NxtW = &W20;
		W20.RtE = B10.RtW = Restricting;
		W20.OSE = B10.OSW = NEOS2 || NEOS3;
		if(NSigL24.R || NSigL26.L || W20.OSE && !NRelease)
			NESL2 = NESL3 = true;
	}

   	if(NSw43.NI && NSw45.NI && NSw57.NI)
   	{
   		N22.NxtE = &B20;			//N22 to B20
      	B20.NxtW = &N22;
		N22.RtE = Slow;
      	B20.RtW = Restricting;
      	N22.OSE = B20.OSW = NEOS3;
      	if(NSigL24.R || NSigL24.L || N22.OSE && !NRelease)
      		NESL3 = true;
   	}
   	else if(NSw55.RI && NSw45.NI && NSw47.NI && NSw57.RI)
   	{
   		W11.NxtE = &B20;			//W11 to B20
      	B20.NxtW = &W11;
      	W11.RtE = B20.RtW = Restricting;
		W11.OSE = B20.OSW = NEOS1 || NEOS2 || NEOS3;
      	if(NSigL28.R || NSigL24.L || W11.OSE && !NRelease)
      		NESL1 = NESL2 = NESL3 = true;
   	}
   	else if(NSw51.NI && NSw53.RI && NSw55.NI && NSw45.NI && NSw47.NI && NSw57.RI)
   	{
   		N32.NxtE = &B20;			//N32 to B20
      	B20.NxtW = &N32;
      	N32.RtE = B20.RtW = Restricting;
      	N32.OSE = B20.OSW = NEOS2 || NEOS3;
      	if(NSigL26.R || NSigL24.L || N32.OSE && !NRelease)
      		NESL2 = NESL3 = true;
   	}
   	else if(NSw51.RI && NSw53.RI && NSw55.NI && NSw45.NI && NSw47.NI && NSw57.RI)
   	{
   		N31.NxtE = &B20;			//N31 to B20
      	B20.NxtW = &N31;
      	N31.RtE = B20.RtW = Restricting;
      	N31.OSE = B20.OSW = NEOS2 || NEOS3;
      	if(NSigL26.R || NSigL24.L || N31.OSE && !NRelease)
      		NESL2 = NESL3 = true;
   	}
   	else if(NSw53.NI && NSw55.NI && NSw45.NI && NSw47.NI && NSw57.RI)
	{
   		N12.NxtE = &B20;			//N12 to B20
      	B20.NxtW = &N12;
        N12.RtE = Slow;
      	B20.RtW = Restricting;
      	N12.OSE = B20.OSW = NEOS2 || NEOS3;
      	if(NSigL26.R || NSigL24.L || N12.OSE && !NRelease)
      		NESL2 = NESL3 = true;
	}
	else if(NSw41.RI && NSw43.RI && NSw45.NI && NSw57.NI)
	{
   		N41.NxtE = &B20;			//N41 to B20
      	B20.NxtW = &N41;
      	N41.RtE = Slow;
      	B20.RtW = Restricting;
      	N41.OSE = B20.OSW = NEOS3;
      	if(NSigL24.R || NSigL24.L || N41.OSE && !NRelease)
      		NESL3 = true;
   	}
	else if(NSw39.RI && NSw41.NI && NSw43.RI && NSw45.NI && NSw57.NI)
	{
		N42.NxtE = &B20;			//N42 to B20
		B20.NxtW = &N42;
		N42.RtE = Slow;
		B20.RtW = Restricting;
		N42.OSE = B20.OSW = NEOS3;
		if(NSigL24.R || NSigL24.L || N42.OSE && !NRelease)
			NESL3 = true;
	}
	else if(NSw39.NI && NSw41.NI && NSw43.RI && NSw45.NI && NSw57.NI)
	{
		W20.NxtE = &B20;			//W20 to B20
		B20.NxtW = &W20;
		W20.RtE = B20.RtW = Restricting;
		W20.OSE = B20.OSW = NEOS3;
		if(NSigL24.R || NSigL24.L || W20.OSE && !NRelease)
			NESL3 = true;
	}

//Branch line direction

	R10.AsstW = F10.AsstW;
	F10.AsstE = R10.AsstE;

//Interlocking Columns

	USSColumn(&NaCf.USSCol[6]);
	USSColumn(&NaCf.USSCol[7]);
	USSColumn(&NaCf.USSCol[8]);

	Fleeting(NFltL12.R, &NSigL24);
	Fleeting(NFltL12.R, &NSigL26);

//Set signals

	if((B11.pLoco->ATC || B10.pLoco->ATC) && B10.NxtW == &N12 && !N12.ClrW)     //Changes for ATC
		N12.Switch = true;
	else
		N12.Switch = false;
	if((B11.pLoco->ATC || B10.pLoco->ATC) && B10.NxtW == &N31 && !N31.ClrW)
		N31.Switch = true;
	else
		N31.Switch = false;
	if((B11.pLoco->ATC || B10.pLoco->ATC) && B10.NxtW == &N32 && !N32.ClrW)
		N32.Switch = true;
	else
		N32.Switch = false;



	Esig(NSigL24.R, &NSigL24, &N24RA, &N22, SloAspects);
   	Esig(NSigL24.R, &NSigL24, &N24RB, &N41, SloAspects);
	Esig(NSigL24.R, &NSigL24, &N24RC, &N42, SloAspects);
	Esig(NSigL24.R, &NSigL24, &N24RD, &W20, SloAspects);
   	Wsig(NSigL24.L, &NSigL24, &N24L, &B20, SloAspects);
   	SigInd(&NSigL24);

   	Esig(NSigL26.R, &NSigL26, &N26RA, &N32, SloAspects);
   	Esig(NSigL26.R, &NSigL26, &N26RB, &N31, SloAspects);
   	Esig(NSigL26.R, &NSigL26, &N26RC, &N12, SloAspects);
	Wsig(NSigL26.L, &NSigL26, &N26L, &B10, SloAspects);
	SigInd(&NSigL26);

	Esig(NSigL28.R, &NSigL28, &N28R, &W11, SloAspects);
   	Wsig(NSigL28.L, &NSigL28, &N28L, &R10, SloAspects);
   	SigInd(&NSigL28);

    Clear = B20.Dir && !B20.M && !B20.E;  //Block signal B20E
    NxtClr = B20.ClrE;
    NxtClrAd = B21.ClrE;
	NxtRte = Main;

//Signal lever locks

	NSigL28.LockR = N28R.Lock;
	NSigL28.LockL = N28L.Lock;

	NSigL26.LockR = (N26RA.Lock || N32.LvrW) && (N26RB.Lock || N31.LvrW) &&
		(N26RC.Lock || N12.LvrW);
	NSigL26.LockL = N26L.Lock || B10.LvrE;
	NSigL24.LockR = (N24RA.Lock || N22.LvrW) && (N24RB.Lock || N41.LvrW) &&
		(N24RC.Lock || N42.LvrW);
	NSigL24.LockL = N24L.Lock || B20.LvrE;
	SetBsig(&B20E, B20.Blk, AdvAspects);

//Block indications

	BlkInd(&N21);
   	BlkInd(&N31);
   	BlkInd(&N32);
   	BlkInd(&N12);
   	BlkInd(&N22);
	BlkInd(&N41);
	BlkInd(&N42);
	BlkInd(&R10);
	BlkInd(&B10);
	BlkInd(&R10);
//	BlkInd(&N60);
	BlkInd(&N60A);
	BlkInd(&N60B);
	BlkInd(&N60C);
	BlkInd(&N60D);
	BlkInd(&N60D);
	BlkInd(&W10);
	BlkInd(&W11);
	BlkInd(&W20);

//Automatic train control

	TC(&N21, &K2L, &N14R);
	TC(&B10, &N26L, &C24R);
	TC(&R10, &N28L, &R10E);

	WRearATC(&N32, &N18LA);      //ATC stops in platform tracks
	WRearATC(&N31, &N18LB);

	ERearATC(&N41, &N24RB);
	ERearATC(&N42, &N24RC);

	TrainID(&N21);

	TrainID(&W10);
	TrainID(&W11);
	TrainID(&N32);
	TrainID(&N31);
	TrainID(&N12);
	TrainID(&N22);
	TrainID(&N41);
	TrainID(&N42);
	TrainID(&W20);
	TrainID(&N60);
	TrainID(&N60A);
	TrainID(&N60B);
	TrainID(&N60C);
	TrainID(&N60D);
	TrainID(&R10);
	TrainID(&B10);


//Update display--------------------------------------------------------

//Switches
	Switch(6, 6, &NSw13, 9, 7);
	Switch(6, 8, &NSw15, 2, 10);
	Switch(8, 8, &NSw17, 2, 10);
	Switch(9, 12, &NSw19, 2, 11);
	Switch(11, 10, &NSw19, 2, 8);
	Switch(10, 8, &NSw27, 2, 9);
	DSSwitch(12, 10, &NSw27, &NSw29, 2, 10, 7, 9);
	DSSwitch(14, 12, &NSw29, &NSw31, 2, 10, 7, 9);
	Switch(16, 14, &NSw33, 7, 10);
	Switch(13, 10, &NSw21, 2, 11);
	DSSwitch(15, 8, &NSw21, &NSw23,	2, 8, 6, 11);
	Switch(17, 6, &NSw25, 8, 6);
	Switch(19, 4, &NSw25, 2, 8);
	Switch(18, 16, &NSw35, 7, 10);

	Switch(32, 8, &NSw51, 7, 9);
	Switch(34, 10, &NSw53, 2, 10);
	Switch(34, 16, &NSw39, 6, 11);
	Switch(36, 14, &NSw41, 6, 11);
	Switch(37, 8, &NSw55, 10, 7);
	Switch(39, 10, &NSw55, 2, 10);
	DSSwitch(38, 12, &NSw43, &NSw45, 2, 8, 6, 11);
	DSSwitch(40, 10, &NSw45, &NSw47, 2, 8, 6, 11);
	Switch(42, 8, &NSw47, 2, 8);
	Switch(41, 10,&NSw57, 2, 9);
	Switch(43, 12, &NSw57, 2, 10);

//Blocks

	Tracker(0, 10, &N11, DBlk);
	Tracker(0, 12, &N21, DBlk);

	XTracker(1, 5, &N60A, Yd, &NWOS2);
	XTracker(1, 6, &N60B, Yd, &NWOS2);
	XTracker(1, 7, &N60C, Yd, &NWOS2);
	XTracker(1, 8, &N60D, Yd, &NWOS2);

	ButtonJump = true;
	XTracker(4, 5, &N60A, OSE, &NWOS2);
	ButtonJump = true;
	XTracker(4, 6, &N60B, OSE, &NWOS2);
	ButtonJump = true;
	XTracker(4, 7, &N60C, OSE, &NWOS2);
	ButtonJump = true;
	XTracker(4, 8, &N60D, OSE, &NWOS2);

	XTracker(17, 4, &T12, OSE, &NWOS1);
	XTracker(9, 10, &N11, OSE, &NWOS3);
	XTracker(9, 12, &N21, OSE, &NWOS4);

	Tracker(21, 4, &W10, Yd);
	Tracker(29, 4, &W11, Yd);
	Tracker(21, 6, &N32, DBlk);
	Tracker(21, 8, &N31, DBlk);
	Tracker(21, 10, &N12, DBlk);
	Tracker(21, 12, &N22, DBlk);
	Tracker(21, 14, &N41, DBlk);
	Tracker(21, 16, &N42, DBlk);
	Tracker(22, 18, &W20, Yd);
	Tracker(28, 18, &W20, Yd);

	XTracker(30, 6, &N32, OSE, &NEOS2);
	XTracker(30, 8, &N31, OSE, &NEOS2);
	XTracker(30, 10, &N12, OSE, &NEOS2);
	XTracker(30, 12, &N22, OSE, &NEOS3);
	XTracker(30, 14, &N41, OSE, &NEOS3);
	XTracker(30, 16, &N42, OSE, &NEOS3);
	XTracker(32, 18, &W20, OSE, &NEOS3);

	XTracker(33, 4, &W11, OSE, &NEOS1);
	Tracker(45, 8, &R10, DBlk);
	Tracker(45, 10, &B10, DBlk);

//Signals

	SignalE(16, 5, &T12);		//20R
	SignalE(9, 9, &N60);      //18R
	SignalE(8, 11, &N11);		//16R
	SignalE(8, 13, &N21);     //14R

	SignalW(20, 3, &W10);		//20L
	SignalW(20, 5, &N32);		//18LA
	SignalW(20, 7, &N31);		//18LB
	SignalW(20, 9, &N12);      //16L
	SignalW(20, 11, &N22);		//14LA
	SignalW(20, 13, &N41);		//14LB
	SignalW(20, 15, &N42);		//14LC
	SignalW(21, 17, &W20);      //14LD

	SignalE(32, 5, &W11);     //28R

	SignalE(29, 7, &N32);		//26RA
	SignalE(29, 9, &N31);		//26RB
	SignalE(29, 11, &N12);     //26RC
	SignalE(29, 13, &N22);		//24RA
	SignalE(29, 15, &N41);		//24RB
	SignalE(29, 17, &N42); 		//24RC
	SignalE(31, 19, &W20);      //24RD

	SignalW(44, 7, &R10);      //28L
	SignalW(44, 9, &B10);      //26L
	SignalW(44, 11, &B20);     //24L

//Train identification

	DisplayID(2, 10, &N11);
	DisplayID(2, 12, &N21);
	DisplayID(23, 6, &N32);
	DisplayID(23, 8, &N31);
	DisplayID(23, 10, &N12);
	DisplayID(23, 12, &N22);
	DisplayID(23, 14, &N41);
	DisplayID(23, 16, &N42);

	DisplayID(46, 8, &R10);
	DisplayID(46, 10, &B10);

//DCC circuit breaker indicators

	CBSptJct = CktBkr[6] && SFlash;
	CBKrulish = CktBkr[22] && SFlash;
	CBNassauW = CktBkr[23] && SFlash;
	CBNassauE = CktBkr[24] && SFlash;
	CBThomas = CktBkr[20] && SFlash;
	CBWilson = CktBkr[21] && SFlash;

//Dispatcher control of Nassau

	if(!NSigL14.N || !NSigL16.N || !NSigL18.N || !NSigL20.N ||
		!NFltL12.N || !NSigL24.N || !NSigL26.N || !NSigL28.N)
	{
//		RBNassau->Enabled = false;
		RBNDispatcherMain->Enabled = false;
		RBNDispatcherAll->Enabled = false;
	}
	else
	{
		RBNassau->Enabled = true;
		RBNDispatcherMain->Enabled = true;
		RBNDispatcherAll->Enabled = true;
	}
	if(NaEn != RBNassau->Enabled)
	{
		MessageToRemDis("NaEn", BoolToStr(RBNassau->Enabled));
		NaEn = RBNassau->Enabled;
	}
	if(NaMnEn != RBNDispatcherMain->Enabled)
	{
		MessageToRemDis("NaMnEn", BoolToStr(RBNDispatcherMain->Enabled));
		NaMnEn = RBNDispatcherMain->Enabled;
	}
	if(NaAllEn != RBNDispatcherAll->Enabled)
	{
		MessageToRemDis("NaAllEn", BoolToStr(RBNDispatcherAll->Enabled));
		NaAllEn = RBNDispatcherAll->Enabled;
	}

//Enable USS levers

	if(RBNDispatcherMain->Checked || RBNDispatcherAll->Checked)
	{
		NaCf.USSCol[0].Enabled = true;
		NaCf.USSCol[1].Enabled = true;
		NaCf.USSCol[2].Enabled = true;
		NaCf.USSCol[3].Enabled = true;
		NaCf.USSCol[6].Enabled = true;
		NaCf.USSCol[7].Enabled = true;
	}
	else
	{
		NaCf.USSCol[0].Enabled = false;
		NaCf.USSCol[1].Enabled = false;
		NaCf.USSCol[2].Enabled = false;
		NaCf.USSCol[3].Enabled = false;
		NaCf.USSCol[6].Enabled = false;
		NaCf.USSCol[7].Enabled = false;

	}
	if(RBNDispatcherAll->Checked)
	{
		NaCf.USSCol[4].Enabled = true;
		NaCf.USSCol[8].Enabled = true;
	}
	else
	{
		NaCf.USSCol[4].Enabled = false;
		NaCf.USSCol[8].Enabled = false;
	}

//Service NX buttons

	if(RBNDispatcherMain->Checked || RBNDispatcherAll->Checked)
	{
		//Nassau West NX Interlocking

		NWLeft = NXBtn(9, 8, NWLeft, 2, &NXBtnN60);        //N60
		NWLeft = NXBtn(8, 10, NWLeft, 3, &NXBtnN11);       //N11
		NWLeft = NXBtn(8, 12, NWLeft, 4, &NXBtnN21);       //N21

		NWRight = NXBtn(20, 6, NWRight, 2, &NXBtnN32W);     //N32W
		NWRight = NXBtn(20, 8, NWRight, 3, &NXBtnN31W);     //N31W
		NWRight = NXBtn(20, 10, NWRight, 4, &NXBtnN12W);    //N12W
		NWRight = NXBtn(20, 12, NWRight, 5, &NXBtnN22W);    //N22W
		NWRight = NXBtn(20, 14, NWRight, 6, &NXBtnN41W);    //N41W
		NWRight = NXBtn(20, 16, NWRight, 7, &NXBtnN42W);    //N42W
		NWRight = NXBtn(21, 18, NWRight, 8, &NXBtnW20W);    //W20W

		if(RBNDispatcherAll->Checked)
		{
			NWLeft = NXBtn(16, 4, NWLeft, 1, &NXBtnT12);     //T12
			NWRight = NXBtn(20, 4, NWRight, 1, &NXBtnW10);   //W10
        }

		//Nassau East NX Interlocking

		NELeft = NXBtn(29, 6, NELeft, 2, &NXBtnN32E);      //N32E
		NELeft = NXBtn(29, 8, NELeft, 3, &NXBtnN31E);      //N31E
		NELeft = NXBtn(29, 10, NELeft, 4, &NXBtnN12E);     //N12E
		NELeft = NXBtn(29, 12, NELeft, 5, &NXBtnN22E);     //N22E
		NELeft = NXBtn(29, 14, NELeft, 6, &NXBtnN41E);     //N41E
		NELeft = NXBtn(29, 16, NELeft, 7, &NXBtnN42E);     //N42E
		NELeft = NXBtn(31, 18, NELeft, 8, &NXBtnW20E);     //W20E

		NERight = NXBtn(44, 10, NERight, 2, &NXBtnB10);   //B10
		NERight = NXBtn(44, 12, NERight, 3, &NXBtnB20);   //B20

		if(RBNDispatcherAll->Checked)
		{
			NELeft = NXBtn(32, 4, NELeft, 1, &NXBtnW11);      //W11
			NERight = NXBtn(44, 8, NERight, 1, &NXBtnR10);    //R10
        }

		if(PulseTime)                               //Time output pulse
		{
			PulseTime--;
			if(!PulseTime)
				NWLeft = NWRight = NELeft = NERight = MaxTime = 0;
		}
		if(NWRight && NWLeft && !PulseTime ||
			NERight && NELeft && !PulseTime)
			PulseTime = 4;
		if(MaxTime)                                  //Clear single button after maxtime
		{
			MaxTime--;
			if(!MaxTime)
				NWLeft = NWRight = NELeft = NERight = 0;
		}
		if((NWRight || NWLeft || NERight || NELeft) && !MaxTime)
			MaxTime = 12;
	}
	else
		NWLeft = NWRight = NELeft = NERight = 0;

	//Auto routing

	if(RBNDispatcherMain->Checked || RBNDispatcherAll->Checked)
		NassauRoutes->Visible = true;
	else
	{
		NassauRoutes->Visible = false;
		NaOff->Checked = true;
	}

	if(NaOn->Checked)
	{
		LeverX = NaCf.XOrigin;
		LeverY = NaCf.YOrigin;

		//State machine for eastbound moves

		if(NassauEState == Idle && (N21.OSW || N21.Blk))    //N21 is trigger
		{
			NassauERoute = GetDest(N21.Train, "NassauE");
			if(NassauERoute == "None")
				NassauEState = Idle;
			else if(NassauERoute == "N41R10" &&
				(NassauWState != Idle || R10.Blk || R10.OSW))
				NassauEState = Idle;
			else
			{
				USSSigNormal(NaCf.USSCol[1].pCol);       //Signal 14 normal
				USSSigNormal(NaCf.USSCol[6].pCol);       //Signal 24 normal
				NassauEState = SigsNormal;
            }
		}

		else if(NassauEState == SigsNormal && NassauERoute == "N22B20") //Sigs Normal
		{
			NXBtnN21 = NXBtnN22W = true;
			NXBtnN22E = NXBtnB20 = true;
			NassauEState = Setting;
		}
		else if(NassauEState == SigsNormal && NassauERoute == "N41")
		{
			NXBtnN21 = NXBtnN41W = true;
			NassauEState = Pause;
		}
	else if(NassauEState == SigsNormal && NassauERoute == "N41R10")
		{
			USSSigNormal(NaCf.USSCol[7].pCol);        	//Signal 26 normal
			USSSigNormal(NaCf.USSCol[8].pCol);          //Signal 28 normal
			NXBtnN21 = NXBtnN41W = true;
			NXBtnN41E = NXBtnR10 = true;
			NassauEState = Pause;
		}
		else if(NassauEState == SigsNormal && NassauERoute == "N41B20")
		{
			NXBtnN21 = NXBtnN41W = true;
			NXBtnN41E = NXBtnB20 = true;
			NassauEState = Pause;
             NassauWState = Blocked;
		}
		else if(NassauEState == SigsNormal && NassauERoute == "N42")
		{
			NXBtnN21 = NXBtnN42W = true;
			NassauEState = Pause;
		}

		else if(NassauEState == Pause)
		{
			NassauEState = Setting;
        }


		else if(NassauEState == Setting && NassauERoute == "N22B20"&&             //Setting
			NSw19.NI && NSw29.NI && NSw31.NI && NSw43.NI && NSw45.NI && NSw57.NI)
		{
			NXBtnN21 = NXBtnN22W = NXBtnN22E = NXBtnB20 = NXBtnR10 =
				NXBtnN41W = NXBtnN41E = NXBtnN42W = false;

			USSSigRight(NaCf.USSCol[1].pCol);       //Signal 14R cleared
			USSSigRight(NaCf.USSCol[6].pCol);   //Signal 24R cleared
			NassauEState = SigsCleared;
		}
		else if(NassauEState == Setting && NassauERoute == "N41" &&
			NSw19.NI && NSw29.NI && NSw31.RI && NSw33.RI)
		{
			NXBtnN21 = NXBtnN22W = NXBtnN22E = NXBtnB20 = NXBtnR10 =
				NXBtnN41W = NXBtnN41E = NXBtnN42W = false;

			USSSigRight(NaCf.USSCol[1].pCol);       //Signal 14R cleared
			NassauEState = SigsCleared;
		}
		else if(NassauEState == Setting && NassauERoute == "N41R10" &&
			NSw19.NI && NSw29.NI && NSw31.RI && NSw33.RI && NSw41.RI &&
				NSw43.RI && NSw45.RI && NSw47.RI)
		{
			NXBtnN21 = NXBtnN22W = NXBtnN22E = NXBtnB20 = NXBtnR10 =
				NXBtnN41W = NXBtnN41E = NXBtnN42W = false;

			USSSigRight(NaCf.USSCol[1].pCol);       //Signal 14R cleared
			USSSigRight(NaCf.USSCol[6].pCol);   //Signal 24R cleared
			NassauEState = SigsCleared;
		}

		else if(NassauEState == Setting && NassauERoute == "N41B20" &&
			NSw19.NI && NSw29.NI && NSw31.RI && NSw33.RI && NSw41.RI &&
				NSw43.RI && NSw45.NI && NSw57.NI)
		{
			NXBtnN21 = NXBtnN22W = NXBtnN22E = NXBtnB20 = NXBtnR10 =
				NXBtnN41W = NXBtnN41E = NXBtnN42W = false;

			USSSigRight(NaCf.USSCol[1].pCol);       //Signal 14R cleared
			USSSigRight(NaCf.USSCol[6].pCol);   //Signal 24R cleared
			NassauEState = SigsCleared;
		}
		else if(NassauEState == Setting && NassauERoute == "N42" &&
			NSw19.NI && NSw29.NI && NSw31.RI && NSw33.NI && NSw35.RI)
		{
			NXBtnN21 = NXBtnN22W = NXBtnN22E = NXBtnB20 = NXBtnR10 =
				NXBtnN41W = NXBtnN41E = NXBtnN42W = false;

			USSSigRight(NaCf.USSCol[1].pCol);       //Signal 14R cleared
			NassauEState = SigsCleared;
		}

		else if(NassauEState == SigsCleared && (N21.Blk || N21.OSE))    //Sigs Cleared
		{
			NassauEState = Running;
		}
		else if(NassauEState == Running && !N21.Blk && !N21.OSE)        //Running
		{
			if(NassauERoute == "N22B20" || NassauERoute == "N41R10" ||
				NassauERoute == "N41B20")    //keep going through Nassau East
				NassauEState = RunningX;
			else
				NassauEState = Idle;
		}

		else if(NassauEState == RunningX && NassauERoute == "N22B20" && !N22.Blk && !N22.OSE)  //RunningX
		{
			USSSigNormal(NaCf.USSCol[6].pCol);       //Signal 24 normal
			NassauEState = Idle;
		}
		else if(NassauEState == RunningX && (NassauERoute == "N41R10" ||
			NassauERoute == "N41B20") && !N41.Blk && !N41.OSE)
		{
			USSSigNormal(NaCf.USSCol[6].pCol);       //Signal 24 normal
			NassauEState = Idle;
		}
		NEState = "NassauEState: " + GetRouteState(NassauEState);

		//State machine for westbound moves

		if(NassauWState == Idle && (B10.Blk || B10.OSE))    //B10 is trigges
		{
			NassauWRoute = GetDest(B10.Train, "NassauW");
			if(NassauWRoute == "None")
			{
				NassauWState = Idle;
			}
			else if(NassauERoute == "N41R10" && NassauEState != Idle)
				NassauWState = Idle;
			else
			{
				USSSigNormal(NaCf.USSCol[7].pCol);        	//Signal 26 normal
				USSSigNormal(NaCf.USSCol[8].pCol);          //Signal 28 normal
				USSSigNormal(NaCf.USSCol[3].pCol);        	//Signal 18 normal
				USSSigNormal(NaCf.USSCol[2].pCol);        	//Signal 16 normal
				NassauWState = SigsNormal;
			}
		}
		else if(NassauWState == Idle && R10.Blk && !R10.Dir)    //R10 is trigger
		{
			NassauWRoute = "N31R10";
			USSSigNormal(NaCf.USSCol[7].pCol);          //Signal 26 normal
			USSSigNormal(NaCf.USSCol[8].pCol);          //Signal 28 normal
			USSSigNormal(NaCf.USSCol[3].pCol);        	//Signal 18 normal
			USSSigNormal(NaCf.USSCol[2].pCol);        	//Signal 16 normal
			NassauWState = SigsNormal;
		}

		else if(NassauWState == SigsNormal && NassauWRoute == "N32")	//Sigs Normal
		{
			NXBtnB10 = NXBtnN32E = true;
			NassauWState = Pause;
		}
		else if(NassauWState == SigsNormal && NassauWRoute == "N31R10")
		{
			NXBtnR10 = NXBtnN31E = true;
			NXBtnN31W = NXBtnN11 = true;
			NassauWState = Pause;
		}
		else if(NassauWState == SigsNormal && NassauWRoute == "N31B10")
		{
			NXBtnB10 = NXBtnN31E = true;
			NXBtnN31W = NXBtnN11 = true;
			NassauWState = Pause;
		}
		else if(NassauWState == SigsNormal && NassauWRoute == "N12B10")
		{
			NXBtnB10 = NXBtnN12E = true;
			NXBtnN12W = NXBtnN11 = true;
			NassauWState = Pause;
		}

		else if(NassauWState == Pause)
		{
			NassauWState = Setting;
        }

		else if(NassauWState == Setting && NassauWRoute == "N32" &&          //Setting
			NSw45.NI && NSw47.NI && NSw55.NI && NSw57.NI && NSw53.RI && NSw51.NI)
		{
			NXBtnB10 = NXBtnN12E = NXBtnN31E = NXBtnN32E = NXBtnR10 =
				NXBtnN12W = NXBtnN31W = NXBtnN12E = false;

			USSSigLeft(NaCf.USSCol[7].pCol);      //Signal 26L cleared
			NassauWState = SigsCleared;
		}
		else if(NassauWState == Setting && NassauWRoute == "N31R10" &&
			NSw45.NI && NSw47.RI && NSw55.NI && NSw53.RI &&	NSw51.RI &&
				NSw19.NI && NSw21.RI && NSw23.NI && NSw27.NI && NSw29.NI)
		{
			NXBtnB10 = NXBtnN12E = NXBtnN31E = NXBtnN32E = NXBtnR10 =
				NXBtnN12W = NXBtnN31W = NXBtnN12E = false;

			USSSigLeft(NaCf.USSCol[8].pCol);      //Signal 28L cleared
			USSSigLeft(NaCf.USSCol[3].pCol);      //Signal 18L cleared
			NassauWState = SigsCleared;
		}
		else if(NassauWState == Setting && NassauWRoute == "N31B10" &&
			NSw45.NI && NSw47.NI && NSw55.NI && NSw57.NI && NSw53.RI && NSw51.RI &&
				NSw19.NI && NSw21.RI && NSw23.NI && NSw27.NI && NSw29.NI)
		{
			NXBtnB10 = NXBtnN12E = NXBtnN31E = NXBtnN32E = NXBtnR10 =
				NXBtnN12W = NXBtnN31W = NXBtnN12E = false;

			USSSigLeft(NaCf.USSCol[7].pCol);      //Signal 26L cleared
			USSSigLeft(NaCf.USSCol[3].pCol);      //Signal 18L cleared
			NassauWState = SigsCleared;
		}
		else if(NassauWState == Setting && NassauWRoute == "N12B10" &&
			NSw45.NI && NSw47.NI && NSw55.NI && NSw57.NI && NSw53.NI &&
				NSw19.NI && NSw21.NI && NSw27.NI && NSw29.NI)
		{
			NXBtnB10 = NXBtnN12E = NXBtnN31E = NXBtnN32E = NXBtnR10 =
				NXBtnN12W = NXBtnN31W = NXBtnN12E = false;

			USSSigLeft(NaCf.USSCol[7].pCol);      //Signal 26L cleared
			USSSigLeft(NaCf.USSCol[2].pCol);      //Signal 16L cleared
			NassauWState = SigsCleared;
		}

		else if(NassauWState == SigsCleared && NassauWRoute == "N31R10" && R10.Blk)    //Sigs cleared
		{
			NassauWState = Running;
		}
		else if(NassauWState == SigsCleared && NassauWRoute != "N31R10" && (B10.Blk || B10.OSW))
		{
			NassauWState = Running;
		}

		else if(NassauWState == Running && NassauWRoute != "N31R10" && !B10.Blk && !B10.OSW)       //Running
		{
			if(NassauWRoute == "N12B10" || NassauWRoute == "N31B10")
				NassauWState = RunningX;                         //continue through Nassau West
			else
			{
				USSSigNormal(NaCf.USSCol[7].pCol);        	//Signal 26 normal
				NassauWState = Idle;
			}
		}
		else if(NassauWState == Running && NassauWRoute == "N31R10" && !R10.Blk)
		{
			NassauWState = RunningX;
		}

		else if(NassauWState == RunningX && NassauWRoute == "N12B10" && !N12.Blk && !N12.OSW)  //RunningX
		{
			USSSigNormal(NaCf.USSCol[7].pCol);        	//Signal 26 normal
			NassauWState = Idle;
		}
		else if(NassauWState == RunningX && (NassauWRoute == "N31R10" ||
			NassauWRoute == "N31B10") && !N31.Blk && !N31.OSW)
		{
			USSSigNormal(NaCf.USSCol[7].pCol);        	//Signal 26 normal
			USSSigNormal(NaCf.USSCol[8].pCol);          //Signal 28 normal
			NassauWState = Idle;
		}
		NWState = "NassauWState; " +  GetRouteState(NassauWState);
	}
	else
        NassauWState = NassauEState = Idle;
}

//---------------------------------------------------------------------------
