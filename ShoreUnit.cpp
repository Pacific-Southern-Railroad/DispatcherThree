//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ShoreUnit.h"
//Initialize Shore--------------------------------------------------

void TPSRY::InitializeShore()
{
	S10.NxtW = &D11;
	S10.NxtE = &S11;

	S20.NxtW = &D21;
	S20.NxtE = &S21;

	S11.NxtW = &S10;
	S11.NxtE = &N10;

	S21.NxtW = &S20;
	S21.NxtE = &N20;

	F10.NxtW = &R10;
	F10.NxtE = &F11;
	F10.RtW = Main;
	F10.RtE = Main;

	F11.NxtW = &F10;
	F11.NxtE = &DummyBlock;

	H10.NxtE = &H11; H10.NxtW = &S10;
	H20.NxtE = &H21; H20.NxtW = &S20;
	P42.NxtE = &N25; P42.NxtW = &S20;

	H11.NxtW = &H10;
	H21.NxtW = &H20;
	H40.NxtW = &H20;
	N25.NxtW = &P42;

// Initialize directions

	S20.Dir = true;
	F10.Dir = true;
	H20.Dir = true;
    H21.Dir = true;

	ShoreAborts = 0;
	HydeJctAborts = 0;

//	Pointer setup

	LaKr.USSCol[20].pSw = &SSw1; LaKr.USSCol[20].pFltL = &SFltL2;
	LaKr.USSCol[21].pSw = &SSw3; LaKr.USSCol[21].pSigL = &SSigL4;
	LaKr.USSCol[22].pSw = &SSw5;
	LaKr.USSCol[23].pSw = &SSw7; LaKr.USSCol[23].pSigL = &SSigL8;
	LaKr.USSCol[24].pSw = &SSw9;
	LaKr.USSCol[25].pSw = &SSw11; LaKr.USSCol[25].pSigL = &SSigL12;
	LaKr.USSCol[26].pSw = &SSw13; LaKr.USSCol[26].pFltL = &SFltL14;
	LaKr.USSCol[27].pSw = &SSw15; LaKr.USSCol[27].pSigL = &SSigL16;
	LaKr.USSCol[28].pSw = &SSw17; LaKr.USSCol[28].pSigL = &SSigL18;
	LaKr.USSCol[29].pSw = &SSw19; LaKr.USSCol[29].pSigL = &SSigL20;

//Lever setup

	LaKr.USSCol[21].Long = LaKr.USSCol[23].Long = LaKr.USSCol[25].Long =
	LaKr.USSCol[27].Long = LaKr.USSCol[29].Long = true;
	SSw1.N = SSw3.N = SSw5.N = SSw7.N = SSw9.N = SSw11.N = SSw13.N =
	SSw15.N = SSw17.N = SSw19.N = true;
	SSw1.Hand = SSw1.N = true; SSw1.pBlk = &S10;
	SFltL2.N = SFltL14.N = true;
	SSigL4.CButton = SSigL4.N = true;
	SSigL8.CButton = SSigL8.N = true;
	SSigL12.CButton = SSigL12.N = true;
	SSigL16.CButton = SSigL16.N = true;
	SSigL18.CButton = SSigL18.N = true;
	SSigL20.CButton = SSigL20.N = true;

//Enable columns

	LaKr.USSCol[20].Enabled = true;
	LaKr.USSCol[21].Enabled = true;
	LaKr.USSCol[22].Enabled = true;
	LaKr.USSCol[23].Enabled = true;
	LaKr.USSCol[24].Enabled = true;
	LaKr.USSCol[25].Enabled = true;
	LaKr.USSCol[26].Enabled = true;
	LaKr.USSCol[27].Enabled = true;
	LaKr.USSCol[28].Enabled = true;
	LaKr.USSCol[29].Enabled = true;

//Switches

	SSw1.NI = SSw3.NI = SSw5.NI = SSw7.NI = SSw9.NI = SSw11.NI = SSw13.NI = true;
	SSw15.NI = SSw17.NI = SSw19.NI = true;

//Block IDs

	S10.BlkID = "S10";
	S11.BlkID = "S11";
	S20.BlkID = "S20";
	S21.BlkID = "S21";
	H30.BlkID = "H30";
	H10.BlkID = "H10";
	H20.BlkID = "H20";
	P32.BlkID = "P32";
	P42.BlkID = "P42";
	H11.BlkID = "H11";
	H21.BlkID = "H21";
	H40.BlkID = "H40";
	N25.BlkID = "N25";
	F10.BlkID = "F10";
	F11.BlkID = "F11";

	//Loco pointers

	S10.pLoco = S11.pLoco = S20.pLoco = S21.pLoco = H30.pLoco = &DummyLoco;
	H10.pLoco = H20.pLoco = P32.pLoco = P42.pLoco = H11.pLoco = &DummyLoco;
	S21.pLoco = H40.pLoco = N25.pLoco = F10.pLoco = F11.pLoco = &DummyLoco;

	//Auto routing

	ShoreERoute = ShoreWRoute = Idle;
}

//Shore service function-------------------------------------------------------

void TPSRY::Shore(void)
{

//Crossing gate at Bortell------------------------------------------------------

	if(S10B && !S1W)
		S1E = true;
	if(S10C && !S1E)
		S1W = true;
	if(!S10B && !S10C)
		S1E = S1W = false;
	if(S20B && !S2W)
		S2E = true;
	if(S20C && !S2E)
		S2W = true;
	if(!S20B && !S20C)
		S2E = S2W = false;

	SXT = S1E && S10B || S1W && S10C ||
		S2E && S20B || S2W && S20C;

	SXL = SXT || SXON;	//lights
	SXL1 = SXL && SFlash;
	SXL2 = SXL && !SFlash;

	if(SXT)					//gates
	{
		if(!SXTime)
			SXG = true;
		else
			SXTime--;
	}
	else
	{
		SXG = false;
		SXTime = 4;		//set gate start time
	}

//Hand-operated switch at Bortell

	HandSwitch(77, 9, true, &SSw1);

//Interlocking at River Jct-------------------------------------------------

//Fleet lever lock

	if(SSigL4.L || SSigL4.R || SSigL12.L || SSigL12.R || SFltL2.R)
		SFltL2.L = false;
	else
		SFltL2.L = true;

//clear routes and switch locks

	S10.RtE = S20.RtE = Nil;
	S11.RtW = S21.RtW = H30.RtW = H10.RtW = H20.RtW = Nil;
	P32.RtW = Nil;
	F10.RtE = F11.RtW = Nil;

	if(SSw3.Out || SSw5.Out || SSw7.Out || SSw9.Out || SSw11.Out || SSw13.Out)
		SSw3.L = SSw5.L = SSw7.L = SSw9.L = SSw11.L = SSw13.L = true;
	else
		SSw3.L = SSw5.L = SSw7.L = SSw9.L = SSw11.L = SSw13.L = false;

//Diamond crossing

	if(SSigL4.L || SSigL4.R || SSigL12.L || SSigL12.R || SOS1 || SOS2)
		MX = true;
	else
		MX = false;

	if(SSigL8.L || SSigL8.R)
	{
		BX = true;
		BXT = 2;
		if(SOS3)
			SSigL8.LockN = true;
		else
			SSigL8.LockN = false;
	}
	else
	{
	if(BXT)
		BXT --;
	else
		BX = false;
	}
	if(BX)
	{
		SSwBX.NI = false;
		SSwBX.RI = true;
	}
	else
	{
        SSwBX.NI = true;
		SSwBX.RI = false;
	}
//switch-switch locks

	SSw3.L = SSw5.R && OSSLockOn->Checked;
	SSw5.L = SSw3.R && OSSLockOn->Checked;

//set pointers, routes and switch locks in accordance with switch positions and
//OS occupancy

	if (SSw3.NI && SSw5.NI && SSw11.NI && !BX)
	{
		S10.NxtE = &S11;                         //S10 to S11
		S11.NxtW = &S10;
		S10.RtE = S11.RtW = Main;
		S10.OSE = S11.OSW = SOS1;
		if (SSigL12.R || SSigL12.L || S10.OSE && OSSLock)
			SSw3.L = SSw5.L = SSw11.L = true;
	}
	else if (SSw3.NI && SSw5.NI && SSw11.RI && SSw13.RI && !BX)
	{
		S10.NxtE = &H30;                        // S10 to H30
		H30.NxtW = &S10;
		S10.RtE = H30.RtW = Restricting;
		S10.OSE = H30.OSW = SOS1;
		if (SSigL12.R || SSigL12.L || S10.OSE && OSSLock)
			SSw3.L = SSw5.L = SSw11.L = SSw13.L = true;
	}
	else if (SSw3.NI && SSw5.NI && SSw11.RI && SSw13.NI && !BX)
	{
		S10.NxtE = &H10;                        //S10 to H10
		H10.NxtW = &S10;
		S10.RtE = Restricting;
		H10.RtW = Diverging;
		S10.OSE = H10.OSW = SOS1;
		if (SSigL12.R || SSigL12.L || S10.OSE && OSSLock)
			SSw3.L = SSw5.L = SSw11.L = SSw13.L = true;
	}
	else if (SSw3.RI && SSw5.NI && SSw7.NI && SSw9.RI && !BX)
	{
		S10.NxtE = &H20;                        // S10 to H20
		H20.NxtW = &S10;
		S10.RtE = Diverging;
		H20.RtW = Restricting;
		S10.OSE = H20.OSW = SOS1 || SOS2;
		if (SSigL12.R || SSigL4.L || S10.OSE && OSSLock)
			SSw3.L = SSw5.L = SSw7.L = SSw9.L = true;
	}
	else if (SSw3.RI && SSw5.NI && SSw7.NI && SSw9.NI && !BX)
	{
		S10.NxtE = &S21;                        //S10 to S21
		S21.NxtW = &S10;
		S10.RtE = S21.RtW = Diverging;
		S10.OSE = S21.OSW = SOS1 || SOS2;
		if (SSigL12.R || SSigL4.L || S10.OSE && OSSLock)
			SSw3.L = SSw5.L = SSw7.L = SSw9.L = true;
	}
	else if (SSw3.RI && SSw5.NI && SSw7.RI && !BX)
	{
		S10.NxtE = &P32;                        //S10 to P32
		P32.NxtW = &S10;
		S10.RtE = P32.RtW = Diverging;
		S10.OSE = P32.OSW = SOS1 || SOS2;
		if (SSigL12.R || SSigL4.L ||S10.OSE && OSSLock)
			SSw3.L = SSw5.L = SSw7.L = true;
	}

	if (SSw3.NI && SSw5.NI && SSw7.NI && SSw9.NI && !BX)
	{
		S20.NxtE = &S21;                        //S20 to S21
		S21.NxtW = &S20;
		S20.RtE = S21.RtW = Main;
		S20.OSE = S21.OSW = SOS2;
		if (SSigL4.R || SSigL4.L || S20.OSE && OSSLock)
			SSw3.L = SSw5.L = SSw7.L = SSw9.L = true;
	}
	else if (SSw3.NI && SSw5.RI && SSw11.NI && !BX)
	{
		S20.NxtE = &S11;                        //S20 to S11
		S11.NxtW = &S20;
		S20.RtE = S11.RtW = Diverging;
		S20.OSE = S11.OSW = SOS1 || SOS2;
		if (SSigL4.R || SSigL12.R || S20.OSE && OSSLock)
			SSw3.L = SSw5.L = SSw11.L = true;
	}
	else if (SSw3.NI && SSw5.RI && SSw11.RI && SSw13.RI && !BX)
	{
		S20.NxtE = &H30;                        //S20 to H30
		H30.NxtW = &S20;
		S20.RtE = H30.RtW = Restricting;
		S20.OSE = H30.OSW = SOS1 || SOS2;
		if (SSigL4.R || SSigL12.L || S20.OSE && OSSLock)
			SSw3.L = SSw5.L = SSw11.L = SSw13.L = true;
	}
	else if (SSw3.NI && SSw5.RI && SSw11.RI && SSw13.NI && !BX)
	{
		S20.NxtE = &H10;                        //S20 to H10
		H10.NxtW = &S20;
		S20.RtE = Restricting;
		H10.RtW = Diverging;
		S20.OSE = H10.OSW = SOS1 || SOS2;
		if (SSigL4.R || SSigL12.L || S20.OSE && OSSLock)
			SSw3.L = SSw5.L = SSw11.L = SSw13.L = true;
	}
	else if (SSw3.NI && SSw5.NI && SSw7.NI && SSw9.RI && !BX)
	{
		S20.NxtE = &H20;                        //S20 to H20
		H20.NxtW = &S20;
		S20.RtE = Diverging;
		H20.RtW = Restricting;
		S20.OSE = H20.OSW = SOS2;
		if (SSigL4.R || SSigL4.L || S20.OSE && OSSLock)
			SSw3.L = SSw5.L = SSw7.L = SSw9.L = true;
	}
	else if (SSw3.NI && SSw5.NI && SSw7.RI && !BX)
	{
		S20.NxtE = &P32;                        //S20 to P32
		P32.NxtW= &S20;
		S20.RtE = P32.RtW = Diverging;
		S20.OSE = P32.OSW = SOS2;
		if (SSigL4.R || SSigL4.L || S20.OSE && OSSLock)
			SSw3.L = SSw5.L = SSw7.L = true;
	}

	if(!MX)
	{
		F10.RtE = Restricting;   					//F10 to F11
		F11.RtW = Restricting;
		F10.OSE = F11.OSW = SOS3;
	}

//Interlocking at Hyde Junction

//Fleet lever lock

	if(SSigL16.L || SSigL16.R || SSigL18.L || SSigL18.R || SSigL20.L || SSigL20.R || SFltL14.R)
		SFltL14.L = false;
	else
		SFltL14.L = true;

//Clear routes and switch locks

	H10.RtE = H20.RtE = P42.RtE = Nil;
	H11.RtW = H21.RtW = H40.RtW = N25.RtW = Nil;

   SSw15.L = SSw17.L = SSw19.L = false;

//set pointers, routes and switch locks in accordance with switch positions and
//OS occupancy

	if(SSw19.NI)
   {
		H10.NxtE = &H11;						//H10 to H11
     	H11.NxtW = &H10;
     	H10.RtE = Restricting;
     	H11.RtW = Main;
     	H10.OSE = H11.OSW = HOS1;
		if(SSigL20.R || SSigL20.L || H10.OSE && OSSLock)
     		SSw19.L = true;
   }

   if(SSw15.NI && SSw17.NI && SSw19.NI)
   {
		H20.NxtE = &H21;						//H20 to H21
     	H21.NxtW = &H20;
     	H20.RtE = Main;
     	H21.RtW = Restricting;
		H20.OSE = H21.OSW = HOS2;
     	if(SSigL18.R || SSigL18.L || H20.OSE && OSSLock)
     		SSw15.L = SSw17.L = SSw19.L = true;
   }
   else if(SSw15.NI && SSw17.NI && SSw19.RI)
   {
		H20.NxtE = &H11;						//H20 to H11
     	H11.NxtW = &H20;
     	H20.RtE = H11.RtW = Restricting;
     	H20.OSE = H11.OSW = HOS1 || HOS2;
     	if(SSigL18.R || SSigL20.L || H20.OSE && OSSLock)
     		SSw15.L = SSw17.L = SSw19.L = true;
   }
   else if(SSw15.NI && SSw17.RI)
   {
		H20.NxtE = &H40;						//H20 to H40
     	H40.NxtW = &H20;
     	H20.RtE = Diverging;
    	H40.RtW = Restricting;
		H20.OSE = H40.OSW = HOS2;
     	if(SSigL18.R || SSigL18.L || H20.OSE && OSSLock)
     		SSw15.L = SSw17.L = true;
   }

   if(SSw15.NI)
   {
		P42.NxtE = &N25;						//P42 to P43
		N25.NxtW = &P42;
		P42.RtE = N25.RtW = Main;
		P42.OSE = N25.OSW = HOS3;
     	if(SSigL16.R || SSigL16.L || P42.OSE && OSSLock)
     		SSw15.L = true;
   }
   else if(SSw15.RI && SSw17.NI && SSw19.RI)
   {
		P42.NxtE = &H11;						//P42 to H11
     	H11.NxtW = &P42;
     	P42.RtE = Restricting;
     	H11.RtW = Diverging;
     	P42.OSE = H11.OSW = HOS1 || HOS2 || HOS3;
     	if(SSigL16.R || SSigL20.L || P42.OSE && OSSLock)
       	SSw15.L = SSw17.L = SSw19.L = true;
   }
   else if(SSw15.RI && SSw17.NI && SSw19.NI)
	{
		P42.NxtE = &H21;						//P42 to H21
     	H21.NxtW = &P42;
		P42.RtE = Diverging;
     	H21.RtW = Restricting;
     	P42.OSE = H21.OSW = HOS2 || HOS3;
     	if(SSigL16.R || SSigL18.L || P42.OSE && OSSLock)
     		SSw15.L = SSw17.L = SSw19.L = true;
   }
   else if(SSw15.RI && SSw17.RI)
   {
   		P42.NxtE = &H40;						//P42 to H40
     	H40.NxtW = &P42;
     	P42.RtE = H40.RtW = Restricting;
     	P42.OSE = H40.OSW = HOS2 || HOS3;
     	if(SSigL16.R || SSigL18.L || P42.OSE && OSSLock)
     		SSw15.L = SSw17.L = true;
   }

//CTC Columns

	USSColumn(&LaKr.USSCol[20]);
	USSColumn(&LaKr.USSCol[21]);
	USSColumn(&LaKr.USSCol[22]);
	USSColumn(&LaKr.USSCol[23]);
	USSColumn(&LaKr.USSCol[24]);
	USSColumn(&LaKr.USSCol[25]);
	USSColumn(&LaKr.USSCol[26]);
	USSColumn(&LaKr.USSCol[27]);
	USSColumn(&LaKr.USSCol[28]);
	USSColumn(&LaKr.USSCol[29]);

//Fleeting

	Fleeting(SFltL2.R, &SSigL4);
	Fleeting(SFltL2.R, &SSigL12);

	Fleeting(SFltL14.R, &SSigL16);
	Fleeting(SFltL14.R, &SSigL18);
	Fleeting(SFltL14.R, &SSigL20);


//Set signals

	Esig(SSigL4.R, &SSigL4, &S4R, &S20, RegAspects);
	Wsig(SSigL4.L, &SSigL4, &S4LA, &H20, RegAspects);
	Wsig(SSigL4.L, &SSigL4, &S4LB, &S21, RegAspects);
	Wsig(SSigL4.L, &SSigL4, &S4LC, &P32, RegAspects);

	Esig(SSigL8.R, &SSigL8, &S8R, &F10, RegAspects);
	Wsig(SSigL8.L, &SSigL8, &S8L, &F11, RegAspects);

	Esig(SSigL12.R, &SSigL12, &S12R, &S10, RegAspects);
	Wsig(SSigL12.L, &SSigL12, &S12LA, &S11, RegAspects);
	Wsig(SSigL12.L, &SSigL12, &S12LB, &H30, RegAspects);
	Wsig(SSigL12.L, &SSigL12, &S12LC, &H10, RegAspects);

	F10H = !SSigL8.L && !F10.Blk;		//Branch semaphore
	F10D = F10H && S8R.Aspect[0];

	Esig(SSigL16.R, &SSigL16, &S16R, &P42, RegAspects);
	Wsig(SSigL16.L, &SSigL16, &S16L, &N25, RegAspects);

	Esig(SSigL18.R, &SSigL18, &S18R, &H20, RegAspects);
	Wsig(SSigL18.L, &SSigL18, &S18LA, &H21, RegAspects);
	Wsig(SSigL18.L, &SSigL18, &S18LB, &H40, RegAspects);

	Esig(SSigL20.R, &SSigL20, &S20R, &H10, RegAspects);
	Wsig(SSigL20.L, &SSigL20, &S20L, &H11, RegAspects);

//Set signal locks

	SSigL4.LockR = S4R.Lock || S20.LvrW;
	SSigL4.LockL = (S4LA.Lock || H20.LvrE) && (S4LB.Lock || S21.LvrE) && (S4LC.Lock || P32.LvrE);
	SSigL8.LockR = S8R.Lock;
	SSigL8.LockL = S8L.Lock;
	SSigL12.LockR = S12R.Lock || S10.LvrW;
	SSigL12.LockL = (S12LA.Lock || N10.LvrE) && (S12LB.Lock || H30.LvrE) && (S12LC.Lock || H10.LvrE);

	SSigL16.LockR = S16R.Lock || P42.LvrW;
	SSigL16.LockL = S16L.Lock || N25.LvrE;
	SSigL18.LockR = S18R.Lock || H20.LvrW;
	SSigL18.LockL = (S18LA.Lock || H21.LvrE) && (S18LB.Lock || H40.LvrE);
	SSigL20.LockR = S20R.Lock || H10.LvrW;
	SSigL20.LockL = S20L.Lock || H11.LvrE;

//Block indicators & direction

	BlkInd(&S20);
	BlkInd(&S11);
	BlkInd(&H30);
	BlkInd(&H10);

	BlkInd(&H20);
	BlkInd(&H11);
	BlkInd(&P42);

	BlkInd(&F10);
	BlkInd(&F11);

	//Automatic Train Control

	TC(&S20, &D10L, &S4R);
	TC(&S11, &S12LA, &S11E);
	if(H30.pLoco->ATC || H30.pLoco->RTC || H30.pLoco->Mon)     //Use rear stop
		WRearATC(&H30, &S12LB);
	TC(&H30, &S12LB, &H8R);
	TC(&H10, &S12LC, &S20R);

	TC(&H20, &S4LA, &S18R);
	TC(&H11, &S20L, &H6R);
	TC(&P42, &PB12L, &S16R);

	//Branch line

	if(F10.E && !BX)
		F10.Srel = true;
	else
		F10.Srel = false;
	if(F11.W && !BX)
		F11.Srel = true;
	else
		F11.Srel = false;

//Train identification

	TrainID(&S20);

	TrainID(&S11);
	TrainID(&H30);
	TrainID(&H10);
	TrainID(&H20);
	TrainID(&P42);

	TrainID(&H11);

	TrainID(&F10);
	TrainID(&F11);

//Update Latham-Krulish image

//Switches

	Switch(84, 10, &SSw3, 2, 9);
	Switch(86, 12, &SSw3, 2, 10);
	Switch(87, 12, &SSw5, 2, 11);
	Switch(89, 10, &SSw5, 2, 8);

	Switch(99, 12, &SSw7, 2, 9);
	Switch(102, 12, &SSw9, 9, 2);
	Switch(99, 10, &SSw11, 11, 2);
	Switch(102, 10, &SSw13, 2, 11);

	Switch(115, 14, &SSw15, 2, 11);
	Switch(117, 12, &SSw15, 2, 8);
	Switch(118, 12, &SSw17, 2, 9);
	Switch(119, 12, &SSw19, 2, 11);
	Switch(121, 10, &SSw19, 2, 8);

//Diamond crossings

	Switch(90, 10, &SSwBX, 2, 7);
	Switch(92, 12, &SSwBX, 2, 7);

//Blocks
	Tracker(83, 8, &F10, DBlk);
	XTracker(87, 8, &F10, OSE, &SOS3);
	Tracker(96, 14, &F11, DBlk);

	Tracker(71, 12, &S20, DBlk);
	XTracker(83, 10, &S10, OSE, &SOS1);
	XTracker(83, 12, &S20, OSE, &SOS2);
	Tracker(106, 6, &S11, DBlk);
	Tracker(106, 8, &H30, DBlk);
	Tracker(106, 10, &H10, DBlk);
	Tracker(106, 12, &H20, DBlk);
	Tracker(110, 18, &S21, DBlk);

	Approach(106, 6, &S11, S11A);
	Approach(106, 8, &H30, H30A);
	Approach(106, 10, &H10, H10A);


	Tracker(110, 20, &P32, DBlk);


	Tracker(109, 14, &P42, DBlk);

	XTracker(114, 10, &H10, OSE, &HOS1);
	XTracker(114, 12, &H20, OSE, &HOS2);
	XTracker(114, 14, &P42, OSE, &HOS3);

	Tracker(123, 10, &H11, DBlk);
	Tracker(123, 12, &H21, DBlk);
	Tracker(123, 14, &H40, DBlk);

//Signals

	SignalW(70, 11, &S20);

	SignalE(83, 11, &S10);
	SignalE(83, 13, &S20);

	SignalE(87, 9, &F10);
	SignalW(95, 13, &F11);

	SignalW(105, 5, &S11);
	SignalW(105, 7, &H30);
	SignalW(105, 9, &H10);

	SignalW(109, 19, &P32);

	SignalE(114, 11, &H10);
	SignalE(114, 13, &H20);
	SignalE(114, 15, &P42);

	SignalW(122, 9, &H11);
	SignalW(122, 11, &H21);
	SignalW(122, 13, &H40);

	DisplayID(73, 12, &S20);
	DisplayID(110, 6, &S11);
	DisplayID(115, 8, &H30);

	DisplayID(110, 10, &H10);
	DisplayID(110, 12, &H20);
	DisplayID(109, 14, &P42);

	DisplayID(124, 10, &H11);
	DisplayID(124, 12, &H21);
	DisplayID(124, 14, &H40);

	DisplayID(111, 20, &P32);

	DisplayID(84, 8, &F10);
	DisplayID(97, 14, &F11);

//Auto routing
	if(DSROn->Checked)
	{
		H30Incl->Enabled = true;
		F11Incl->Enabled = true;
		P32Incl->Enabled = true;
		LeverX = LaKr.XOrigin;
        LeverY = LaKr.YOrigin;

		//State machine for River Jct. westbound

		if(ShoreWState == Idle && !SSigL12.LockL && !S10.OSE && H30Incl->Checked && H30.Blk)   //Train from H30
		{
			H30Incl->Checked = false;
			ShoreWRoute = "HydeH30";
			USSSigNormal(LaKr.USSCol[25].pCol);
			ShoreWState = SigsNormal;
		}
		else if(ShoreWState == Idle && !SSigL12.LockL && !S10.OSE && (S11.Blk || N10.Blk))      //Train from
		{
			ShoreWRoute = "Krulish";
			USSSigNormal(LaKr.USSCol[25].pCol);
			ShoreWState = SigsNormal;
		}
		else if(F11Incl->Checked && ShoreWState == Idle && ShoreEState == Idle &&
			!F10.Blk && !R10.Blk && !D21.Blk && !S20.Blk && ! S11.Blk && !N10.Blk)	  //Train from Harpers
		{
			F11Incl->Checked = false;
			ShoreWRoute = "Harpers";
			USSSigNormal(LaKr.USSCol[21].pCol);  //signals 4 & 12 normal
			USSSigNormal(LaKr.USSCol[25].pCol);
			ShoreWState = SigsNormal;
			ShoreEState = Blocked;
		}
		else if(ShoreWState == Idle && !SSigL12.LockL && !S10.OSE && SSw19.NI &&
			(H10.Blk || H10.OSE || H11.Blk))   										//Train from H10
		{
			ShoreWRoute = "HydeH10";
			USSSigNormal(LaKr.USSCol[25].pCol);
			ShoreWState = SigsNormal;
		}
		else if(ShoreEState == Idle && ShoreWState == Idle && P32Incl->Checked &&
			!SSigL12.LockL && !S10.OSE && P32.Blk)                                    //Train from P32
		{
			P32Incl->Checked = false;
			ShoreWRoute = "PortP32";
			USSSigNormal(LaKr.USSCol[21].pCol);  //signals 4 & 12 normal
			USSSigNormal(LaKr.USSCol[25].pCol);
			ShoreWState = SigsNormal;
			ShoreEState = Blocked;
		}

		else if(ShoreWState == SigsNormal && ShoreWRoute == "HydeH30")              //Sigs normal
		{
			USSSwNormal(LaKr.USSCol[21].pCol);  //Switch 3 normal
			USSSwNormal(LaKr.USSCol[22].pCol);  //Switch 5 normal
			USSSwReverse(LaKr.USSCol[25].pCol);  //Switch 11 reversed
			USSSwReverse(LaKr.USSCol[26].pCol);  //Switch 13 reversed
			ShoreWState = Setting;
		}
		else if(ShoreWState == SigsNormal && ShoreWRoute =="Krulish")
		{
			USSSwNormal(LaKr.USSCol[21].pCol);  //Switch 3 normal
			USSSwNormal(LaKr.USSCol[22].pCol);  //Switch 5 normal
			USSSwNormal(LaKr.USSCol[25].pCol);  //Switch 11 normal
			ShoreWState = Setting;
		}

		else if(ShoreWState == SigsNormal && ShoreWRoute == "HydeH10")
		{
			USSSwNormal(LaKr.USSCol[21].pCol);  //Switch 3 normal
			USSSwNormal(LaKr.USSCol[22].pCol);  //Switch 5 normal
			USSSwReverse(LaKr.USSCol[25].pCol);  //Switch 11 reversed
			USSSwNormal(LaKr.USSCol[26].pCol);  //Switch 13 normal
			ShoreWState = Setting;
		}
		else if(ShoreWState == SigsNormal && ShoreWRoute == "Harpers")
		{
			ShoreWState = Setting;
		}
			else if(ShoreWState == SigsNormal && ShoreWRoute == "PortP32")
		{
			USSSwReverse(LaKr.USSCol[21].pCol);  //Switch 3 reversed
			USSSwNormal(LaKr.USSCol[22].pCol);  //Switch 5 normal
			USSSwReverse(LaKr.USSCol[23].pCol);  //Switch 7 reversed
			ShoreWState = Setting;
		}

		else if(ShoreWState == Setting && SSw1.NI && SSw3.NI && SSw5.NI &&
			(ShoreWRoute == "Krulish" && SSw11.NI ||
				ShoreWRoute == "HydeH30" && SSw11.RI && SSw13.RI ||
					ShoreWRoute == "HydeH10" && SSw11.RI))       			//Setting
		{
			USSSigLeft(LaKr.USSCol[25].pCol);  //Signal 12LA, 12LB or 12LC cleared
			ShoreWState = SigsCleared;
		}
		else if(ShoreWState == Setting && ShoreWRoute == "Harpers")
		{
			USSSigLeft(LaKr.USSCol[23].pCol);   //Signal 8L cleared
			ShoreWState = SigsCleared;
		}
		else if(ShoreWState == Setting && ShoreWRoute == "PortP32" &&
			SSw3.RI && SSw5.NI && SSw7.RI)
		{
			USSSigLeft(LaKr.USSCol[21].pCol);   //Signal 4L cleared
			ShoreWState = SigsCleared;
		}

		else if(ShoreWState == SigsCleared && (ShoreWRoute != "Harpers" && S10.OSE) ||
			(ShoreWRoute == "Harpers" && (SOS3 || F10.E)))                  //Sigs Cleared
		{
			ShoreWState = Running;
		}

		else if(ShoreWState == Running &&!S10.OSE && (ShoreWRoute == "Krulish" ||
			ShoreWRoute == "HydeH30" || ShoreWRoute == "HydeH10"))                          //Running
		{
			ShoreWState = Idle;
		}
		else if(ShoreWState == Running && !S10.OSE && ShoreWRoute == "PortP32")
		{
			USSSigNormal(LaKr.USSCol[21].pCol); //Signal 4 normal
			SSw3.L = false;
			USSSwNormal(LaKr.USSCol[21].pCol);  //switch 3 normal
			ShoreWState = Idle;
			ShoreEState = Idle;
		}
		else if(ShoreWState == Running && ShoreWRoute == "Harpers" && !SOS3 && !F10.E)
		{
			SSigL8.LockN = false;
			USSSigNormal(LaKr.USSCol[23].pCol);   //Signal 8 normal
			ShoreWState = Idle;
			ShoreEState = Idle;
		}

		SWState = "ShoreWState: " + GetRouteState(ShoreWState);

	//State machine for River Jct. Eastbound


		if(F10.Blk && F10.Dir && ShoreWState == Idle && ShoreEState == Idle &&
			!F11.Blk && !D21.Blk && !S20.Blk && ! S11.Blk && !N10.Blk)	  				//Train to Harpers
		{
			ShoreERoute = "Harpers";
			USSSigNormal(LaKr.USSCol[21].pCol);  //signals 4 & 12 normal
			USSSigNormal(LaKr.USSCol[25].pCol);
			ShoreEState = SigsNormal;
			ShoreWState = Blocked;
		}
		 else if(ShoreEState == Idle && !SSigL4.LockR && (D21.OSW || D21.Blk)) //D21 is the trigger from Dell
		{
			ShoreERoute = GetDest(D21.Train, "Dell/ShoreE");
			if(ShoreERoute == "None")
				ShoreEState = Idle;
			else
			{
				USSSigNormal(LaKr.USSCol[21].pCol); //signals 4 & 8 normal
				ShoreEState = SigsNormal;
			}
		}
		 else if(ShoreEState == Idle && !SSigL4.LockR && (S20.OSW || S20.Blk)) //S20 is the trigger from Dell
		{
			ShoreERoute = GetDest(S20.Train, "Dell/ShoreE");
			if(ShoreERoute == "None")
				ShoreEState = Idle;
			else
			{
				USSSigNormal(LaKr.USSCol[21].pCol); //signals 4 & 8 normal
				ShoreEState = SigsNormal;
			}
		}
		else if(ShoreEState == SigsNormal)				   //Sigs normal
		{
			if(ShoreERoute == "Hyde")
			{
				USSSwNormal(LaKr.USSCol[21].pCol);  //Switch 3 normal
				USSSwNormal(LaKr.USSCol[22].pCol);  //Switch 5 normal
				USSSwNormal(LaKr.USSCol[23].pCol);  //Switch 7 normal
				USSSwReverse(LaKr.USSCol[24].pCol); //Switch 9 reversed
				ShoreEState = Setting;
			}
			else if(ShoreERoute == "Port")
			{
				USSSwNormal(LaKr.USSCol[21].pCol);  //Switch 3 normal
				USSSwNormal(LaKr.USSCol[22].pCol);  //Switch 5 normal
				USSSwReverse(LaKr.USSCol[23].pCol); //Switch 7 reverse
				ShoreEState = Setting;
			}
			else if(ShoreERoute == "Krulish")
			{
				USSSwNormal(LaKr.USSCol[21].pCol);  //Switch 3 normal
				USSSwNormal(LaKr.USSCol[22].pCol);  //Switch 5 normal
				USSSwNormal(LaKr.USSCol[23].pCol); 	//Switch 7 normal
				USSSwNormal(LaKr.USSCol[24].pCol); 	//Switch 9 normal
				ShoreEState = Setting;
			}
			else if(ShoreERoute == "Harpers")
			{
				ShoreEState = Setting;
			}
			else
                ShoreEState = Idle;
		}

		else if(ShoreEState == Setting && ShoreERoute == "Hyde" &&
			SSw3.NI && SSw5.NI && SSw7.NI && SSw9.RI)        			//Setting
		{
			USSSigRight(LaKr.USSCol[21].pCol);   //Signal 4R cleared
			ShoreEState = SigsCleared;
		}
		else if(ShoreEState == Setting && ShoreERoute == "Port" &&
			SSw3.NI && SSw5.NI && SSw7.RI)                   //Route set
		{
			USSSigRight(LaKr.USSCol[21].pCol);   //Signal 4R cleared
			ShoreEState = SigsCleared;
		}
		else if(ShoreEState == Setting && ShoreERoute == "Krulish" &&
			SSw3.NI && SSw5.NI && SSw7.NI && SSw9.NI)         //Route set
		{
			USSSigRight(LaKr.USSCol[21].pCol);    //Signal 4R cleared
			ShoreEState = SigsCleared;
		}
		else if(ShoreEState == Setting && ShoreERoute == "Harpers")
		{
			USSSigRight(LaKr.USSCol[23].pCol);       //Signal 8R cleared
			ShoreEState = SigsCleared;
		}

		else if(ShoreEState == SigsCleared && ShoreERoute != "Harpers" && S20.OSE)     //Sigs cleared
		{
			ShoreEState = Running;                //Approach block still occupied
		}
		else if(ShoreEState == SigsCleared && ShoreERoute == "Harpers" && SOS3)
		{
			ShoreEState = Running;
        }

		else if(ShoreEState == Running && ShoreERoute != "Harpers" && !S20.OSE)        //Running
		{
			ShoreEState = Idle;
		}
		else if(ShoreEState == Running && ShoreERoute == "Harpers" && !SOS3 && !F11.W && !F10.E)
		{
			SSigL8.LockN = false;
			USSSigNormal(LaKr.USSCol[23].pCol);      //Signal 8 normal
			ShoreEState = Idle;
			ShoreWState = Idle;
        }

		SEState = "ShoreEState: " + GetRouteState(ShoreEState);
	}
	else
	{
		H30Incl->Enabled = false;
		F11Incl->Enabled = false;
		P32Incl->Enabled = false;
		H30Incl->Checked = false;
		F11Incl->Checked = false;
		P32Incl->Checked = false;

		ShoreEState = ShoreWState = Idle;
	}
}
//---------------------------------------------------------------------------

