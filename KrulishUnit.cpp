//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "KrulishUnit.h"
#include "PSRYUnit.h"
//---------------------------------------------------------------------------
void TPSRY::InitializeKrulish(void)
{
	N10.NxtW = &S11;
	N10.NxtE = &N11;

	N20.NxtW = &S21;
	N20.NxtE = &N21;

	K10.NxtW = &N10;
	K10.NxtE = &DummyBlock;

	N25.NxtW = &P42;
	N25.NxtE = &N21;
    SKD2 = true;

	N10.RtW = S11.RtE = Main;
	N20.RtW = S21.RtE = Main;
	S21.Dir = N20.Dir = true;

	KrulishAborts = 0;

	LaKr.USSCol[32].pSw = &KSw1; LaKr.USSCol[32].pSigL = &KSigL2;
	LaKr.USSCol[33].pSw = &KSw3; LaKr.USSCol[33].pSigL = &KSigL4;
	LaKr.USSCol[34].pSw = &KSw5; LaKr.USSCol[34].pFltL = &KFltL6;
	LaKr.USSCol[35].pSw = &KSw7; LaKr.USSCol[35].pSigL = &KSigL8;

	LaKr.USSCol[33].Long = LaKr.USSCol[35].Long = true;
	KSw1.N = KSw3.N = KSw5.N = KSw7.N = true;
	KSigL2.CButton = KSigL2.N = true;
	KSigL4.CButton = KSigL4.N = KSigL4.LockL = true;
	KFltL6.N = true;
	KSigL8.CButton = KSigL8.N = true;

	LaKr.USSCol[32].Enabled = true;
	LaKr.USSCol[33].Enabled = true;
	LaKr.USSCol[34].Enabled = true;
	LaKr.USSCol[35].Enabled = true;

//Switches

	KSw1.NI = KSw3.NI = KSw5.NI = KSw7.NI = true;

}

//Krulish service function

void TPSRY::Krulish(void)
{
//Intermediate block signals on track 1, blocks S11 and N10

	N10.AsstE = S11.AsstE;
	S11.AsstW = N10.AsstW;

	if(S11.AsstE || N10.ClrE)
		SKD1 = true;    //Eastbound
	if(N10.AsstW || S11.ClrW)
		SKD1 = false;   //Westbound

	if(InTestMode)     //Derive OS section between blocks
		S11.OSE = N10.OSW = S11.M && N10.M;
	else
		S11.OSE = N10.OSW = S11.E && N10.W;

	EBkcon(SKD1, &S11E, &S11, RegAspects);
	WBkcon(SKD1, &N10W, &N10, RegAspects);

//Intermediate block signals on track 2, blocks S21 and N20

	N20.AsstE = S21.AsstE;
	S21.AsstW = N20.AsstW;

	if(S21.AsstE || N20.ClrE)
		SKD2 = true;    //Eastbound
	if(N20.AsstW || S21.ClrW)
		SKD2 = false;   //Westbound

	if(InTestMode)           //Derive OS section between blocks
		S21.OSE = N20.OSW = S21.M && N20.M;
	else
		S21.OSE = N20.OSW = S21.E && N20.W;

	EBkcon(SKD2, &S21E, &S21, RegAspects);
	WBkcon(SKD2, &N20W, &N20, RegAspects);

//Fleet lever lock

	if(KSigL2.L || KSigL2.R || KSigL4.L || KSigL4.R ||
			KSigL8.L || KSigL8.R || KFltL6.R)
		KFltL6.L = false;
	else
		KFltL6.L = true;

//Interlocking at Krulish

//Clear routes and switch locks

	N10.RtE = N11.RtW = K10.RtW = N20.RtE = N21.RtW = N25.RtE = Nil;

	KSw1.L = KSw3.L = KSw5.L = KSw7.L = false;

//Switch-switch locks

	KSw3.L = KSw5.RI && OSSLockOn->Checked;
	KSw5.L = KSw3.RI && OSSLockOn->Checked;

	if(KSw1.Out)
		KSw3.L = KSw5.L = KSw7.L = true;
	if(KSw3.Out)
		KSw1.L = KSw5.L = KSw7.L = true;
	if(KSw5.Out)
		KSw1.L = KSw3.L = KSw7.L = true;
	if(KSw7.Out)
		KSw1.L = KSw3.L = KSw5.L = true;

	KSwOut = KSw1.Out || KSw3.Out || KSw5.Out || KSw7.Out;

//set pointers, routes and switch locks in accordance with switch positions and
//OS occupancy

	if(KSw3.NI && KSw5.NI && KSw7.RI)
	{
		N10.NxtE = &K10;				//N10 to K10
		K10.NxtW = &N10;
		N10.RtE = K10.RtW = Restricting;
		N10.OSE = K10.OSW = KOS1;
		if(KSigL8.R || KSigL8.L || N10.OSE && OSSLock)
			KSw3.L = KSw5.L = KSw7.L = true;
	}

	else if(KSw3.NI && KSw5.NI && KSw7.NI)
	{
		N10.NxtE = &N11;				//N10 to N11
		N11.NxtW = &N10;
		N10.RtE = N11.RtW = Main;
		N10.OSE = N11.OSW = KOS1;
		if(KSigL8.R || KSigL8.L || N10.OSE && OSSLock)
			KSw3.L = KSw5.L = KSw7.L = true;
	}

	else if(KSw3.NI && KSw5.RI)
	{
		N10.NxtE = &N21;				//N10 to N21
		N21.NxtW = &N10;
		N10.RtE = N21.RtW = Diverging;
		N10.OSE = N21.OSW = KOS1 || KOS3;
		if(KSigL8.R || KSigL2.L || N10.OSE && OSSLock)
			KSw3.L = KSw5.L = true;
	}

	if(KSw3.RI && KSw5.NI && KSw7.RI)
	{
		N25.NxtE = &K10;                //N25 to K10
		K10.NxtW = &N25;
		N25.RtE = K10.RtW = Restricting;
		N25.OSE = K10.OSW = KOS1 || KOS2;
		if(KSigL4.R || KSigL8.L || N25.OSE && OSSLock)
			KSw3.L = KSw5.L = KSw7.L = true;
	}

	else if(KSw3.RI && KSw5.NI && KSw7.NI)
	{
		N25.NxtE = &N11;                //N25 to N11
		N11.NxtW = &N25;
		N25.RtE = N11.RtW = Diverging;
		N25.OSE = N11.OSW = KOS1 || KOS2;
		if(KSigL4.R || KSigL8.L || N25.OSE && OSSLock)
			KSw3.L = KSw5.L = KSw7.L = true;
	}

	else if(KSw1.RI && KSw3.NI && KSw5.NI)
	{
		N25.NxtE = &N21;                //N25 to N21
		N21.NxtW = &N25;
		N25.RtE = N21.RtW = Main;
		N25.OSE = N21.OSW = KOS2 || KOS3;
		if(KSigL4.R || KSigL2.L || N25.OSE && OSSLock)
			KSw1.L = KSw3.L = KSw5.L = true;
	}

	if(KSw1.NI && KSw5.NI)
	{
		N20.NxtE = &N21;				//N20 to N21
		N21.NxtW = &N20;
		N20.RtE = N21.RtW = Diverging;
		N20.OSE = N21.OSW = KOS3;
		if(KSigL2.R || KSigL2.L || N20.OSE && OSSLock)
			KSw1.L = KSw5.L = true;
	}

   //Interlocking Columns

	USSColumn(&LaKr.USSCol[32]);
	USSColumn(&LaKr.USSCol[33]);
	USSColumn(&LaKr.USSCol[34]);
	USSColumn(&LaKr.USSCol[35]);

   //Fleeting

    Fleeting(KFltL6.R, &KSigL2);
	Fleeting(KFltL6.R, &KSigL4);
	Fleeting(KFltL6.R, &KSigL8);

   //Set signals

	Esig(KSigL2.R, &KSigL2, &K2R, &N20, RegAspects);
	Wsig(KSigL2.L, &KSigL2, &K2L, &N21, RegAspects);

	Esig(KSigL4.R, &KSigL4, &K4R, &N25, RegAspects);

	Esig(KSigL8.R, &KSigL8, &K8R, &N10, RegAspects);
	Wsig(KSigL8.L, &KSigL8, &K8LA, &K10, RegAspects);
	Wsig(KSigL8.L, &KSigL8, &K8LB, &N11, RegAspects);

   //Set signal lever locks


	KSigL4.LockR = K4R.Lock || N25.LvrW || KSwOut;
	KSigL2.LockR = K2R.Lock || S21.LvrW || KSwOut;
	KSigL2.LockL = K2L.Lock || N21.LvrE || KSwOut;
	KSigL8.LockR = K8R.Lock || S11.LvrW || KSwOut;
	KSigL8.LockL = K8LA.Lock && (K8LB.Lock || N11.LvrE) || KSwOut;


   //Block indications

	BlkInd(&N10);
	BlkInd(&N20);
	BlkInd(&N25);
	BlkInd(&S21);
	BlkInd(&N11);
    BlkInd(&K10);

   //Train control & identification

	TC(&N25, &S16L, &K4R);
	TC(&S21, &S4LB, &S21E);

	TC(&N10, &N10W, &K8R);
	TC(&N20, &N20W, &K2R);

	TC(&N11, &K8LB, &N16R);

	TrainID(&N25);
	TrainID(&S21);
	TrainID(&N10);
	TrainID(&N20);
	TrainID(&K10);
	TrainID(&N11);

   //Display

//Update Latham-Krulish image

	Switch(145, 12, &KSw1, 8, 2);

	Switch(142, 12, &KSw3, 2, 11);
	Switch(144, 10, &KSw3, 2, 8);

	Switch(145, 10, &KSw5, 2, 9);
	Switch(147, 12, &KSw5, 2, 10);

	Switch(146, 10, &KSw7, 2, 11);

//Blocks

	Tracker(122, 6,  &N10, DBlk);
	Tracker(121, 16, &N25, DBlk);
	Tracker(122, 18, &N20, DBlk);

	XTracker(141, 10, &N10, OSE, &KOS1);
	XTracker(141, 12, &N25, OSE, &KOS2);
	XTracker(141, 14, &N20, OSE, &KOS3);

	Tracker(150, 8, &K10, Yd);
	Tracker(150, 10, &N11, DBlk);
	Tracker(150, 12, &N21, DBlk);

//Signals

	SignalW(109, 17, &S21);

	SignalW(121, 5, &N10);
	SignalE(122, 7, &S11);
    SignalW(120, 15, &N25);
	SignalE(122, 19, &S21);

	SignalW(121, 17, &N20);

	SignalE(141, 11, &N10);
	SignalE(141, 13, &N25);
	SignalE(141, 15, &N20);

	SignalW(149, 7, &K10);
	SignalW(149, 9, &N11);
	SignalW(149, 11, &N21);

//Train identification

	DisplayID(123, 16, &N25);
	DisplayID(117, 18, &S21);
	DisplayID(126, 6, &N10);
	DisplayID(126, 18, &N20);
//	DisplayID(152, 8, &K10);
	DisplayID(153, 10, &N11);
	DisplayID(153, 12, &N21);

//Direction indicators

	if(SKD1)
	{
		Indicator(119, 4, 84);
		Indicator(124, 4, 83);
	}
	else
	{
		Indicator(119, 4, 83);
		Indicator(124, 4, 84);
	}

	if(SKD2)
	{
		Indicator(119, 23, 84);
		Indicator(124, 23, 83);
	}
	else
	{
		Indicator(119, 23, 83);
		Indicator(124, 23, 84);
	}

//DCC Circuit breaker

	CBKrulishYard = CktBkr[19] && Flash;
}
//---------------------------------------------------------------------------