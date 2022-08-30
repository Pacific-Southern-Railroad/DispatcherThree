//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "HydeUnit.h"
//----------------------------------------------------------------------------

//Initialize Hyde

void TPSRY::InitializeHyde(void)
{
	H11.NxtE = &H12;
 	H21.NxtE = &H22;

	H30.NxtW = &S10; H30.NxtE = &H31;
	H31.NxtW = &H30; H31.NxtE = &H13;
	H32.NxtW = &H11; H32.NxtE = &H13;
	H33.NxtW = &H11; H33.NxtE = &H13;
	H34.NxtW = &H11; H34.NxtE = &H13;
	H12.NxtW = &H11; H12.NxtE = &H13;

	H22.NxtW = &H21; H22.NxtE = &H23;
	H43.NxtW = &H21; H43.NxtE = &H23;
	H42.NxtW = &H21; H42.NxtE = &H23;
	H41.NxtW = &H21; H41.NxtE = &H23;
	H40.NxtE = &H23;

	H13.NxtW = &H12;
	H23.NxtW = &H22;

	HydeAborts = 0;

// Initialize directions

	H21.Dir = H22.Dir = H23.Dir = true;
	H40.Dir = H41.Dir = H42.Dir = H43.Dir = true;

//Turn on power

	H30Power = true;
	HydeEastPower = true;
	HydeWestPower = true;

//Switches

	H12E = H12W = H22E = H22W = H30E = true;

//Signals

	HSigL4.N = HSigL6.N = HSigL8.N = HSigL10.N = HSigL12.N = true;

//Block ID

	H11.BlkID = "H11";
	H21.BlkID = "H21";
	H31.BlkID = "H31";
	H32.BlkID = "H32";
	H33.BlkID = "H33";
	H34.BlkID = "H34";
	H12.BlkID = "H12";
	H22.BlkID = "H22";
	H43.BlkID = "H43";
	H42.BlkID = "H42";
	H41.BlkID = "H41";
	H40.BlkID = "H40";
	H13.BlkID = "H13";
	H23.BlkID = "H23";

//Loco pointers

	H11.pLoco = H21.pLoco = H31.pLoco = H32.pLoco = H33.pLoco = &DummyLoco;
	H34.pLoco = H12.pLoco = H22.pLoco = H43.pLoco = H42.pLoco = &DummyLoco;
	H41.pLoco = H40.pLoco = H13.pLoco = H23.pLoco = &DummyLoco;

}

//Hyde service function---------------------------------------------------------

void TPSRY::Hyde(void)
{
//Fleet lever lock

	if(HSigL4.L || HSigL4.R || HSigL6.L || HSigL6.R || HSigL8.L || HSigL8.R ||
		HSigL10.L || HSigL10.R || HSigL12.L || HSigL12.R)
			HFltL2.L = false;
	else
		HFltL2.L = true;

//Hyde West interlocking

//Clear routes and switch locks

	H30.RtE = H11.RtE = H21.RtE = Nil;
	H31.RtW = H32.RtW = H33.RtW = H34.RtW = H12.RtW = Nil;
	H22.RtW = H43.RtW = H42.RtW = H41.RtW = Nil;

	HSw1.L = HSw3.L = HSw5.L = HSw7.L = HSw9.L = HSw11.L = HSw13.L = false;

//set pointers, routes and switch locks in accordance with switch positions and
//OS occupancy

	if(HSw7.NI)
  	{
  		H30.NxtE = &H31;					//H30 to H31
     	H31.NxtW = &H30;
     	H30.RtE = Restricting;
     	H31.RtW = Main;
     	H30.OSE = H31.OSW = HOS4;
     	if(HSigL8.R || HSigL8.L || H30.OSE && OSSLock)
     		HSw7.L = true;
	}

   if(HSw1.RI && HSw3.RI && HSw7.RI)
	{
		H11.NxtE = &H31;					//H11 to H31
		H31.NxtW = &H11;
		H11.RtE = H31.RtW = Restricting;
		H11.OSE = H31.OSW = HOS5 || HOS4;
		if(HSigL6.R || HSigL8.L || H11.OSE && OSSLock)
			HSw1.L = HSw5.L = HSw7.L = true;
	}

	else if(HSw1.RI && HSw3.RI && HSw7.NI)
	{
		H11.NxtE = &H32;					//H11 to H32
		H32.NxtW = &H11;
		H11.RtE = H32.RtW = Restricting;
		H11.OSE = H32.OSW = HOS5;
		if(HSigL6.R || HSigL6.L || H11.OSE && OSSLock)
			HSw1.L = HSw5.L = HSw7.L = true;
	}

	else if(HSw1.RI && HSw3.NI)
	{
		H11.NxtE = &H33;					//H11 to H33
		H33.NxtW = &H11;
		H11.RtE = H33.RtW = Restricting;
		H11.OSE = H33.OSW = HOS5;
		if(HSigL6.R || HSigL6.L || H11.OSE && OSSLock)
			HSw1.L = HSw5.L = true;
	}

	else if(HSw1.NI && HSw3.RI)
	{
		H11.NxtE = &H34;					//H11 to H34
		H34.NxtW = &H11;
		H11.RtE = H34.RtW = Restricting;
		H11.OSE = H34.OSW = HOS5;
    	if(HSigL6.R || HSigL6.L || H11.OSE && OSSLock)
     		HSw1.L = HSw3.L = true;
	}

	else if(HSw1.NI && HSw3.NI)
	{
  	 	H11.NxtE = &H12;					//H11 to H12
		H12.NxtW = &H11;
		H11.RtE = H12.RtW = Restricting;
		H11.OSE = H12.OSW = HOS5;
		if(HSigL6.R || HSigL6.L || H11.OSE && OSSLock)
     		HSw1.L = HSw3.L = true;
	}

	if(HSw9.NI && HSw11.NI)
	{
     	H21.NxtE = &H22;					//H21 to H22
     	H22.NxtW = &H21;
		H21.RtE = Main;
		H22.RtW = Restricting;
     	H21.OSE = H22.OSW = HOS6;
     	if(HSigL4.R || HSigL4.L || H21.OSE && OSSLock)
     		HSw9.L = HSw11.L = true;
	}

	else if(HSw9.NI && HSw11.RI)
	{
		H21.NxtE = &H43;					//H21 to H43
		H43.NxtW = &H21;
		H21.RtE = Diverging;
		H43.RtW = Restricting;
		H21.OSE = H43.OSW = HOS6;
		if(HSigL4.R || HSigL4.L || H21.OSE && OSSLock)
			HSw9.L = HSw11.L = true;
	}

	else if(HSw9.RI && HSw13.NI)
	{
		H21.NxtE = &H42;					//H21 to H42
		H42.NxtW = &H21;
		H21.RtE = Diverging;
		H42.RtW = Restricting;
		H21.OSE = H42.OSW = HOS6;
		if(HSigL4.R || HSigL4.L || H21.OSE && OSSLock)
			HSw9.L = HSw13.L = true;
	}

	else if(HSw9.RI && HSw13.RI)
	{
		H21.NxtE = &H41;					//H21 to H41
		H41.NxtW = &H21;
		H21.RtE = Diverging;
		H41.RtW = Restricting;
		H21.OSE = H41.OSW = HOS6;
		if(HSigL4.R || HSigL4.L || H21.OSE && OSSLock)
			HSw9.L = HSw13.L = true;
	}

//Switch buttons

	SBH30E = SwitchButton(28, 4, &SBH30E);
	SBH31W = SwitchButton(33, 4, &SBH31W);
	SBH32W = SwitchButton(33, 6, &SBH32W);
	SBH33W = SwitchButton(33, 8, &SBH33W);
	SBH34W = SwitchButton(33, 10, &SBH34W);
	SBH12W = SwitchButton(33, 12, &SBH12W);
	SBH22W = SwitchButton(33, 14, &SBH22W);
	SBH43W = SwitchButton(33, 16, &SBH43W);
	SBH42W = SwitchButton(33, 18, &SBH42W);
	SBH41W = SwitchButton(33, 20, &SBH41W);

//Switches

	HSw1.NO = !HSw1.L && (SBH34W || SBH12W);
	HSw1.RO = !HSw1.L && (SBH31W || SBH32W || SBH33W);
	HSw3.NO = !HSw3.L && !HSw5.L && (SBH12W || SBH33W);
	HSw3.RO = !HSw3.L && !HSw5.L && (SBH34W || SBH32W || SBH31W);
	HSw7.NO = !HSw7.L && (SBH30E || SBH32W);
	HSw7.RO = !HSw7.L && SBH31W;

	HSw9.NO = !HSw9.L && (SBH22W || SBH43W);
	HSw9.RO = !HSw9.L && (SBH42W || SBH41W);
	HSw11.NO = !HSw11.L && (SBH22W || SBH42W);
	HSw11.RO = !HSw11.L && (SBH43W || SBH41W);

//Signal clicks

	ClickSignalE(28, 5, R, &HSigL8, &H30);
	ClickSignalE(22, 13, R, &HSigL6, &H11);
	ClickSignalE(22, 15, R, &HSigL4, &H21);

	ClickSignalW(33, 3, L, &HSigL8, &H31);
	ClickSignalW(33, 5, L, &HSigL6, &H32);
	ClickSignalW(33, 7, L, &HSigL6, &H33);
	ClickSignalW(33, 9, L, &HSigL6, &H34);
	ClickSignalW(33, 11, L, &HSigL6, &H12);
	ClickSignalW(33, 13, L, &HSigL4, &H22);
	ClickSignalW(33, 15, L, &HSigL4, &H43);
	ClickSignalW(33, 17, L, &HSigL4, &H42);
	ClickSignalW(33, 19, L, &HSigL4, &H41);

//Fleeting

	Fleeting(HydeFleetOn->Checked, &HSigL4);
	Fleeting(HydeFleetOn->Checked, &HSigL6);
	Fleeting(HydeFleetOn->Checked, &HSigL8);

//Set signal lever locks

	HSigL4.LockR = H4R.Lock || H21.LvrW;
	HSigL4.LockL = (H4LA.Lock || H22.LvrE) && (H4LB.Lock || H43.LvrE)
		&& (H4LC.Lock || H42.LvrE) && (H4LD.Lock || H41.LvrE);
	HSigL6.LockR = H6R.Lock || H11.LvrW;
	HSigL6.LockL = (H6LA.Lock || H32.LvrE) && (H6LB.Lock || H33.LvrE)
		&& (H6LC.Lock || H34.LvrE) && (H6LD.Lock || H12.LvrE);
	HSigL8.LockR = H8R.Lock || H30.LvrW;
	HSigL8.LockL = H8L.Lock || H31.LvrE;

//ATC settings for short blocks

	H11.Switch = !H11.Dir && !H11.ClrW;
	H21.Switch = H21.Dir && !H21.ClrE;

//Set signals

	Esig(HSigL4.R, &HSigL4, &H4R, &H21, RegAspects);
	Wsig(HSigL4.L, &HSigL4, &H4LA, &H22, RegAspects);
	Wsig(HSigL4.L, &HSigL4, &H4LB, &H43, RegAspects);
	Wsig(HSigL4.L, &HSigL4, &H4LC, &H42, RegAspects);
	Wsig(HSigL4.L, &HSigL4, &H4LD, &H41, RegAspects);

	Esig(HSigL6.R, &HSigL6, &H6R, &H11, RegAspects);
	Wsig(HSigL6.L, &HSigL6, &H6LA, &H32, RegAspects);
	Wsig(HSigL6.L, &HSigL6, &H6LB, &H33, RegAspects);
	Wsig(HSigL6.L, &HSigL6, &H6LC, &H34, RegAspects);
	Wsig(HSigL6.L, &HSigL6, &H6LD, &H12, RegAspects);

	Esig(HSigL8.R, &HSigL8, &H8R, &H30, RegAspects);
	Wsig(HSigL8.L, &HSigL8, &H8L, &H31, RegAspects);

//Hyde East interlocking

//Clear routes and switch locks

	H30.RtE = H31.RtE = H32.RtE = H33.RtE = H34.RtE = H12.RtE = Nil;
	H22.RtE = H43.RtE = H42.RtE = H41.RtE = H40.RtE = Nil;

	H13.RtW = H23.RtW = Nil;

	HSw15.L = HSw17.L = HSw19.L = HSw21.L = false;
	HSw23.L = HSw25.L = HSw27.L = HSw29.L = false;

//Clear OSE sections

	H31.OSE = H32.OSE = H33.OSE = H34.OSE = H12.OSE = false;
	H22.OSE = H40.OSE = H41.OSE = H42.OSE = H43.OSE = false;

//set pointers, routes and switch locks in accordance with switch positions and
//OS occupancy

	if(HSw21.RI)
	{
		H31.NxtE = &H13;						//H31 to H13
		H13.NxtW = &H31;
		H31.RtE = Restricting;
		H13.RtW = Main;
		H31.OSE = H13.OSW = HOS7;
		if(HSigL12.R || HSigL12.L || H31.OSE && OSSLock)
			HSw15.L = HSw17.L = HSw19.L = HSw21.L = true;
	}

	else if(HSw19.RI && HSw21.NI)
	{
		H32.NxtE = &H13;                 //H32 to H13
		H13.NxtW = &H32;
		H32.RtE = Restricting;
		H13.RtW = Diverging;
		H32.OSE = H13.OSW = HOS7;
		if(HSigL12.R || HSigL12.L || H32.OSE && OSSLock)
			HSw15.L = HSw17.L = HSw19.L = HSw21.L = true;
	}

	else if(HSw17.RI && HSw19.NI && HSw21.NI)
	{
		H33.NxtE = &H13;               //H33 to H13
		H13.NxtW = &H33;
		H33.RtE = Restricting;
		H13.RtW = Diverging;
		H33.OSE = H13.OSW = HOS7;
		if(HSigL12.R || HSigL12.L || H33.OSE && OSSLock)
			HSw15.L = HSw17.L = HSw19.L = HSw21.L = true;
	}

	else if(HSw15.RI && HSw17.NI && HSw19.NI && HSw21.NI)
	{
		H34.NxtE = &H13;              //H34 to H13
		H13.NxtW = &H34;
		H34.RtE = Restricting;
		H13.RtW = Diverging;
		H34.OSE = H13.OSW = HOS7;
		if(HSigL12.R || HSigL12.L || H34.OSE && OSSLock)
			HSw15.L = HSw17.L = HSw19.L = HSw21.L = true;
	}

	else if(HSw15.NI && HSw17.NI && HSw19.NI && HSw21.NI)
	{
		H12.NxtE = &H13;            //H12 to H13
		H13.NxtW = &H12;
		H12.RtE = Restricting;
		H13.RtW = Main;
		H12.OSE = H13.OSW = HOS7;
		if(HSigL12.R || HSigL12.L || H12.OSE && OSSLock)
			HSw15.L = HSw17.L = HSw19.L = HSw21.L = true;
	}

	if(HSw27.NI && HSw29.NI)
	{
		H22.NxtE = &H23;           //H22 to H23
		H23.NxtW = &H22;
		H22.RtE = H23.RtW = Restricting;
		H22.OSE = H23.OSW = HOS8;
		if(HSigL10.R || HSigL10.L || H22.OSE && OSSLock)
			HSw27.L = HSw29.L = true;
	}

	else if(HSw25.RI && HSw27.RI && HSw29.NI)
	{
		H43.NxtE = &H23;         //H43 to H23
		H23.NxtW = &H43;
		H43.RtE = H23.RtW = Restricting;
		H43.OSE = H23.OSW = HOS8;
		if(HSigL10.R || HSigL10.L || H43.OSE && OSSLock)
			HSw25.L = HSw27.L = HSw29.L = true;
	}

	else if(HSw23.RI && HSw25.NI && HSw27.RI && HSw29.NI)
	{
		H42.NxtE = &H23;        //H42 to H23
		H23.NxtW = &H42;
		H42.RtE = H23.RtW = Restricting;
		H42.OSE = H23.OSW = HOS8;
		if(HSigL10.R || HSigL10.L || H42.OSE && OSSLock)
			HSw23.L = HSw25.L = HSw27.L = HSw29.L = true;
	}

	else if(HSw23.NI && HSw25.NI && HSw27.RI && HSw29.NI)
	{
		H41.NxtE = &H23;      //H41 to H23
		H23.NxtW = &H41;
		H41.RtE = H23.RtW = Restricting;
		H41.OSE = H23.OSW = HOS8;
		if(HSigL10.R || HSigL10.L || H41.OSE && OSSLock)
			HSw23.L = HSw25.L = HSw27.L = HSw29.L = true;
	}

	else if(HSw29.RI)
	{
		H40.NxtE = &H23;   //H40 to H23
		H23.NxtW = &H40;
		H40.RtE = H23.RtW = Restricting;
		H40.OSE = H23.OSW = HOS8;
		if(HSigL10.R || HSigL10.L || H40.OSE && OSSLock)
			HSw29.L = true;
	}

//Switch buttons

	SBH31E = SwitchButton(42, 4, &SBH31E);
	SBH32E = SwitchButton(42, 6, &SBH32E);
	SBH33E = SwitchButton(42, 8, &SBH33E);
	SBH34E = SwitchButton(42, 10, &SBH34E);
	SBH12E = SwitchButton(42, 12, &SBH12E);
	SBH22E = SwitchButton(42, 14, &SBH22E);
	SBH43E = SwitchButton(42, 16, &SBH43E);
	SBH42E = SwitchButton(42, 18, &SBH42E);
	SBH41E = SwitchButton(42, 20, &SBH41E);
	SBH40E = SwitchButton(42, 22, &SBH40E);

//Signal clicks

	ClickSignalE(42, 5, R, &HSigL12, &H31);
	ClickSignalE(42, 7, R, &HSigL12, &H32);
	ClickSignalE(42, 9, R, &HSigL12, &H33);
	ClickSignalE(42, 11, R, &HSigL12, &H34);
	ClickSignalE(42, 13, R, &HSigL12, &H12);
	ClickSignalE(42, 15, R, &HSigL10, &H22);
	ClickSignalE(42, 17, R, &HSigL10, &H43);
	ClickSignalE(42, 19, R, &HSigL10, &H42);
	ClickSignalE(42, 21, R, &HSigL10, &H41);
	ClickSignalE(42, 23, R, &HSigL10, &H40);

	ClickSignalW(57, 11, L, &HSigL12, &H13);
	ClickSignalW(57, 13, L, &HSigL10, &H23);

//Switches

	HSw15.NO = !HSw15.L && SBH12E;
	HSw15.RO = !HSw15.L && SBH34E;
	HSw17.NO = !HSw17.L && (SBH12E || SBH34E);
	HSw17.RO = !HSw17.L && SBH33E;
	HSw19.NO = !HSw19.L && (SBH12E || SBH34E || SBH33E);
	HSw19.RO = !HSw19.L && SBH32E;
	HSw21.NO = !HSw21.L && (SBH12E || SBH34E || SBH33E || SBH32E);
	HSw21.RO = !HSw21.L && SBH31E;

	HSw23.NO = !HSw23.L && SBH41E;
	HSw23.RO = !HSw23.L && SBH42E;
	HSw25.NO = !HSw25.L && (SBH42E || SBH41E);
	HSw25.RO = !HSw25.L && SBH43E;
	HSw27.NO = !HSw27.L && SBH22E;
	HSw27.RO = !HSw27.L && (SBH43E || SBH42E || SBH41E);
	HSw29.NO = !HSw29.L && (SBH22E || SBH43E || SBH42E || SBH41E);
	HSw29.RO = !HSw29.L && SBH40E;

//Fleeting

	Fleeting(HydeFleetOn->Checked, &HSigL10);
	Fleeting(HydeFleetOn->Checked, &HSigL12);

//Set signal lever locks

	HSigL10.LockR = (H10RA.Lock || H22.LvrW) && (H10RB.Lock || H43.LvrW) &&
		(H10RC.Lock || H42.LvrW) && (H10RD.Lock || H41.LvrW) && (H10RE.Lock || H40.LvrW);
	HSigL10.LockL = H10L.Lock || H23.LvrE;
	HSigL12.LockR = (H12RA.Lock || H31.LvrW) && (H12RB.Lock || H32.LvrW) &&
		(H12RC.Lock || H33.LvrW) && (H12RD.Lock || H34.LvrW) && (H12RE.Lock || H12.LvrW);
	HSigL12.LockL = H12L.Lock || H13.LvrE;

//Set signals

	Esig(HSigL10.R, &HSigL10, &H10RA, &H22, RegAspects);
	Esig(HSigL10.R, &HSigL10, &H10RB, &H43, RegAspects);
	Esig(HSigL10.R, &HSigL10, &H10RC, &H42, RegAspects);
	Esig(HSigL10.R, &HSigL10, &H10RD, &H41, RegAspects);
	Esig(HSigL10.R, &HSigL10, &H10RE, &H40, RegAspects);
	Wsig(HSigL10.L, &HSigL10, &H10L, &H23, RegAspects);

	Esig(HSigL12.R, &HSigL12, &H12RA, &H31, RegAspects);
	Esig(HSigL12.R, &HSigL12, &H12RB, &H32, RegAspects);
	Esig(HSigL12.R, &HSigL12, &H12RC, &H33, RegAspects);
	Esig(HSigL12.R, &HSigL12, &H12RD, &H34, RegAspects);
	Esig(HSigL12.R, &HSigL12, &H12RE, &H12, RegAspects);
	Wsig(HSigL12.L, &HSigL12, &H12L, &H13, RegAspects);

//Block indications

	BlkInd(&H21);
	BlkInd(&H31);
	BlkInd(&H32);
	BlkInd(&H33);
	BlkInd(&H34);
	BlkInd(&H12);
	BlkInd(&H22);
	BlkInd(&H43);
	BlkInd(&H42);
	BlkInd(&H41);
	BlkInd(&H40);
	BlkInd(&H13);

//Train control

	TC(&H21, &S18LA, &H4R);
	WRearATC(&H31, &H8L);
	WRearATC(&H32, &H6LA);
	WRearATC(&H33, &H6LB);
	WRearATC(&H34, &H6LC);
	WRearATC(&H12, &H6LD);
	ERearATC(&H22, &H10RA);
	ERearATC(&H43, &H10RB);
	ERearATC(&H42, &H10RC);
	ERearATC(&H41, &H10RD);
	ERearATC(&H40, &H10RE);

	TC(&H13, &H12L, &D6RA);

	TrainID(&H21);

	TrainID(&H31);
	TrainID(&H32);
	TrainID(&H33);
	TrainID(&H34);
	TrainID(&H12);
	TrainID(&H22);
	TrainID(&H43);
	TrainID(&H42);
	TrainID(&H41);
	TrainID(&H40);

	TrainID(&H13);

//Power control buttons

	PBH30 = SwitchButton(4, 3, &PBH30);
	if(PBH30 && !lastH30)
	{
		if(!H30Power)
			H30Power = true;
		else
			H30Power = false;
		lastH30 = true;
		PBH30 = 0;
	}
	else
		lastH30 = false;

	PBHydeWest = SwitchButton(4, 5, &PBHydeWest);
	if(PBHydeWest && !lastHydeWest)
	{
		if(!HydeWestPower)
			HydeWestPower = true;
		else
			HydeWestPower = false;
		lastHydeWest = true;
		PBHydeWest = 0;
	}
	else
		lastHydeWest = false;

	PBHydeEast = SwitchButton(4, 7, &PBHydeEast);
	if(PBHydeEast && !lastHydeEast)
	{
		if(!HydeEastPower)
			HydeEastPower = true;
		else
			HydeEastPower = false;
		lastHydeEast = true;
		PBHydeEast = 0;
	}
	else
		lastHydeEast = false;

//Display: Update Hyde/Yard/Port image

//Switches

	Switch(23, 12, &HSw1, 2, 11);
	Switch(26, 12, &HSw3, 2, 11);
	Switch(27, 8, &HSw3, 8, 6);     //5 linked to 3
	Switch(29, 6, &HSw7, 8, 6);
	Switch(31, 4, &HSw7, 2, 8);

	Switch(23, 14, &HSw9, 2, 9);
	Switch(26, 14, &HSw11, 2, 9);
	Switch(27, 18, &HSw11, 10, 7);  //13 linked to 11

	Switch(46, 12, &HSw15, 2, 10);
	Switch(49, 12, &HSw17, 2, 10);
	Switch(52, 12, &HSw19, 2, 10);
	Switch(55, 12, &HSw21, 2, 10);

	Switch(47, 18, &HSw23, 6, 11);
	Switch(49, 16, &HSw25, 6, 11);
	Switch(51, 14, &HSw27, 2, 8);
	Switch(54, 14, &HSw29, 2, 8);

//Blocks

	Tracker(14, 10, &H30, DBlk);
	Tracker(14, 12, &H11, DBlk);
	Tracker(14, 14, &H21, DBlk);
	Tracker(14, 16, &H40, OSW);
	Tracker(17, 16, &H40, DBlk);

	XTracker(29, 4, &H30, OSE, &HOS4);
	XTracker(22, 12, &H11, OSE, &HOS5);
	XTracker(22, 14, &H21, OSE, &HOS6);

	Tracker(34, 4, &H31, DBlk);
	Tracker(34, 6, &H32, DBlk);
	Tracker(34, 8, &H33, DBlk);
	Tracker(34, 10, &H34, DBlk);
	Tracker(34, 12, &H12, DBlk);
	Tracker(34, 14, &H22, DBlk);
	Tracker(34, 16, &H43, DBlk);
	Tracker(34, 18, &H42, DBlk);
	Tracker(34, 20, &H41, DBlk);

	XTracker(43, 4, &H31, OSE, &HOS7);
	XTracker(43, 6, &H32, OSE, &HOS7);
	XTracker(43, 8, &H33, OSE, &HOS7);
	XTracker(43, 10, &H34, OSE, &HOS7);
	XTracker(43, 12, &H12, OSE, &HOS7);
	XTracker(43, 14, &H22, OSE, &HOS8);
	XTracker(43, 16, &H43, OSE, &HOS8);
	XTracker(43, 18, &H42, OSE, &HOS8);
	XTracker(43, 20, &H41, OSE, &HOS8);
	XTracker(43, 22, &H40, OSE, &HOS8);

	Tracker(58, 12, &H13, DBlk);
	Tracker(58, 14, &H23, DBlk);

//Signals

	SignalE(28, 5, &H30);
	SignalE(22, 13, &H11);
	SignalE(22, 15, &H21);

	SignalW(33, 3, &H31);
	SignalW(33, 5, &H32);
	SignalW(33, 7, &H33);
	SignalW(33, 9, &H34);
	SignalW(33, 11, &H12);
	SignalW(33, 13, &H22);
	SignalW(33, 15, &H43);
	SignalW(33, 17, &H42);
	SignalW(33, 19, &H41);

	SignalE(42, 5, &H31);
	SignalE(42, 7, &H32);
	SignalE(42, 9, &H33);
	SignalE(42, 11, &H34);
	SignalE(42, 13, &H12);
	SignalE(42, 15, &H22);
	SignalE(42, 17, &H43);
	SignalE(42, 19, &H42);
	SignalE(42, 21, &H41);
	SignalE(42, 23, &H40);

	SignalW(57, 11, &H13);
	SignalW(57, 13, &H23);

//Train identification

	DisplayID(15, 10, &H30);
	DisplayID(15, 12, &H11);
	DisplayID(15, 14, &H21);

	DisplayID(36, 4, &H31);
	DisplayID(36, 6, &H32);
	DisplayID(36, 8, &H33);
	DisplayID(36, 10, &H34);
	DisplayID(36, 12, &H12);
	DisplayID(36, 14, &H22);
	DisplayID(36, 16, &H43);
	DisplayID(36, 18, &H42);
	DisplayID(36, 20, &H41);
	DisplayID(36, 22, &H40);

	DisplayID(60, 12, &H13);
	DisplayID(60, 14, &H23);

   //Derive switch positions from inputs

	HSw1.NI = H12W || H34W;
	HSw1.RI = H31W || H32W || H33W;
	HSw3.NI = HSw5.NI = H12W || H33W;
	HSw3.RI = HSw5.RI = H31W || H32W || H34W;
	HSw7.NI = H30E || H32W;
	HSw7.RI = H31W || !H30E;
	HSw9.NI = H22W || H43W;
	HSw9.RI = H41W || H42W;
	HSw11.NI = HSw13.NI = H22W || H42W;
	HSw11.RI = HSw13.RI = H41W || H43W;

	HSw15.NI = H12E || H33E || H32E || H31E;
	HSw15.RI = H34E;
	HSw17.NI = H12E || H34E || H32E || H31E;
	HSw17.RI = H33E;
	HSw19.NI = H12E || H34E || H33E || H31E;
	HSw19.RI = H32E;
	HSw21.NI = H12E || H34E || H33E || H32E;
	HSw21.RI = H31E;

	HSw23.NI = H41E || H43E || H22E || H40E;
	HSw23.RI = H42E;
	HSw25.NI = H41E || H42E || H22E || H40E;
	HSw25.RI = H43E;
	HSw27.NI = H22E || H40E;
	HSw27.RI = H41E || H42E || H43E;
	HSw29.NI = H41E || H42E || H43E || H22E;
	HSw29.RI = H40E;

	//Auto routing

	if(HyInOn->Checked)
	{
		LeverX = LaKr.XOrigin;
		LeverY = LaKr.YOrigin;

	//State machine for Hyde inbound west

		if(HydeWState == Idle && (H13.Blk || H13.OSE))  //H13 is the trigger block
		{
			HydeWRoute = GetDest(H13.Train, "HydeInW");
			if(HydeWRoute == "None")
				HydeWState = Idle;
			else
			{
				HSigL12.L = false;
				HSigL12.N = true;                   //WB Signals normal
				HSigL8.L = false;
				HSigL8.N = true;
				HydeWState = SigsNormal;
			}
		}
		else if(HydeWState == SigsNormal)
		{
			if(HydeWRoute == "H30")
			{
				SBH31E = true;
				SBH30E = true;
					HydeWState = Pause;
			}
			else if(HydeWRoute == "H31")
			{
				SBH31E = true;
				HydeWState = Pause;
			}
			else if(HydeWRoute == "H32")
			{
				SBH32E = true;
				HydeWState = Pause;
			}
			else if(HydeWRoute == "H33")
			{
				SBH33E = true;
				HydeWState = Pause;
			}
			else if(HydeWRoute == "H34")
			{
				SBH34E = true;
				HydeWState = Pause;
			}
			else if(HydeWRoute == "H12")
			{
				SBH12E = true;
				HydeWState = Pause;
			}
			else
				HydeWState = Idle;
		}
		else if(HydeWState == Pause)            //pause for switch machines to operate
		{
			HydeWState = Setting;
		}
		else if(HydeWState == Setting && HydeWRoute == "H30" && H30E && H31E)
		{
			SBH31E = SBH30E = false;
			HSigL12.N = false;
			HSigL12.L = true;          //Signal 12L cleared
			HSigL8.N = false;
			HSigL8.L = true;           //Signal 8
			HydeWState = SigsCleared;
		}
		else if(HydeWState == Setting && HydeWRoute == "H31" && H31E)
		{
			SBH31E = false;
			HSigL12.N = false;
			HSigL12.L = true;          //Signal 12L cleared
			HydeWState = SigsCleared;
		}
		else if(HydeWState == Setting && HydeWRoute == "H32" && H32E)
		{
			SBH32E = false;
			HSigL12.N = false;
			HSigL12.L = true;          //Signal 12L cleared
			HydeWState = SigsCleared;
		}
		else if(HydeWState == Setting && HydeWRoute == "H33" && H33E)
		{
			SBH33E = false;
			HSigL12.N = false;
			HSigL12.L = true;          //Signal 12L cleared
			HydeWState = SigsCleared;
		}
		else if(HydeWState == Setting && HydeWRoute == "H34" && H34E)
		{
			SBH34E = false;
			HSigL12.N = false;
			HSigL12.L = true;          //Signal 12L cleared
			HydeWState = SigsCleared;
		}
		else if(HydeWState == Setting && HydeWRoute == "H12" && H12E)
		{
			SBH12E = false;
			HSigL12.N = false;
			HSigL12.L = true;          //Signal 12L cleared
			HydeWState = SigsCleared;
		}
		else if(HydeWState == SigsCleared && (H13.Blk || H13.OSW))
		{
			HydeWState = Running;           //Approach still occupied
		}
		else if(HydeWState == Running && !H13.Blk && !H13.OSW)
		{
			HydeWState = Idle;
		}
		HWState = "HydeWState: " + GetRouteState(HydeWState);

		//State machine for Hyde inbound east

		if(HydeEState == Idle && (H20.Blk || H20.OSW))    //S20 is the trigger block
		{
			HydeERoute = GetDest(H20.Train, "HydeInE");
			if(HydeERoute == "None")
				HydeEState = Idle;
			else
			{
				Screen = &LaKr;                     //Change screen to draw Hyde Jct. levers
				USSSigNormal(LaKr.USSCol[28].pCol);  //Hyde Jct. signal 18R normal
				Screen = &HyYdPt;
				HSigL4.N = true;                 	//Hyde signal 4R normal
				HSigL4.R = false;
				HydeEState = SigsNormal;
			}
		}
		else if(HydeEState == SigsNormal)
		{
			if(HydeERoute == "H22")
			{
				Screen = &LaKr;                     //Change screen to draw Hyde Jct. levers
				USSSwNormal(LaKr.USSCol[27].pCol);   //Hyde Jct. switches S15 and S19 normal
				USSSwNormal(LaKr.USSCol[29].pCol);   //Hyde Jct. switch S17 normal
				USSSwNormal(LaKr.USSCol[28].pCol);
				Screen = &HyYdPt;
				SBH22W = true;
				HydeEState = Pause;
			}
			else if(HydeERoute == "H40")
			{
				Screen = &LaKr;                     //Change screen to draw Hyde Jct. levers
				USSSwNormal(LaKr.USSCol[27].pCol);   //Hyde Jct. switches S15 and S19 normal
				USSSwNormal(LaKr.USSCol[29].pCol);
				USSSwReverse(LaKr.USSCol[28].pCol);  //Hyde Jct. switch S17 reverse
				Screen = &HyYdPt;
				HydeEState = Pause;
			}
			else if(HydeERoute == "H41")
			{
				Screen = &LaKr;                     //Change screen to draw Hyde Jct. levers
				USSSwNormal(LaKr.USSCol[27].pCol);   //Hyde Jct. switches S15 and S19 normal
				USSSwNormal(LaKr.USSCol[29].pCol);
				USSSwNormal(LaKr.USSCol[28].pCol);   //Hyde Jct. switch S17 normal
				Screen = &HyYdPt;
				SBH41W = true;
				HydeEState = Pause;
			}
			else if(HydeERoute == "H42")
			{
				Screen = &LaKr;                     //Change screen to draw Hyde Jct. levers
				USSSwNormal(LaKr.USSCol[27].pCol);   //Hyde Jct. switches S15 and S19 normal
				USSSwNormal(LaKr.USSCol[29].pCol);
				USSSwNormal(LaKr.USSCol[28].pCol);   //Hyde Jct. switch S17 normal
				Screen = &HyYdPt;
				SBH42W = true;
				HydeEState = Pause;
			}
			else if(HydeERoute == "H43")
			{
				Screen = &LaKr;                     //Change screen to draw Hyde Jct. levers
				USSSwNormal(LaKr.USSCol[27].pCol);   //Hyde Jct. switches S15 and S19 normal
				USSSwNormal(LaKr.USSCol[29].pCol);
				USSSwNormal(LaKr.USSCol[28].pCol);   //Hyde Jct. switch S17 normal
				Screen = &HyYdPt;
				SBH43W = true;
				HydeEState = Pause;
			}
			else
				HydeEState = Idle;
		}
		else if(HydeEState == Pause)
		{
			HydeEState = Setting;
        }
		else if(HydeEState == Setting && HydeERoute == "H22" &&
			SSw15.NI && SSw17.NI && SSw19.NI && H22W)
		{
			SBH22W = false;
			Screen = &LaKr;
		   SSigL18.LockR = false;
			USSSigRight(LaKr.USSCol[28].pCol);  //Shore signal 18R cleared
			Screen = &HyYdPt;
			HSigL4.R = true;                 	//Hyde signal 4R cleared
			HSigL4.N = false;
			HydeEState = SigsCleared;
		}
		else if(HydeEState == Setting && HydeERoute == "H43" &&
			SSw15.NI && SSw17.NI && SSw19.NI && H43W)
		{
			SBH43W = false;
			Screen = &LaKr;
		   SSigL18.LockR = false;
			USSSigRight(LaKr.USSCol[28].pCol);  //Shore signal 18R cleared
			Screen = &HyYdPt;
			HSigL4.R = true;                 	//Hyde signal 4R cleared
			HSigL4.N = false;
			HydeEState = SigsCleared;
		}
		else if(HydeEState == Setting && HydeERoute == "H42" &&
			SSw15.NI && SSw17.NI && SSw19.NI && H42W)
		{
			SBH42W = false;
			Screen = &LaKr;
		   SSigL18.LockR = false;
			USSSigRight(LaKr.USSCol[28].pCol);  //Shore signal 18R cleared
			Screen = &HyYdPt;
			HSigL4.R = true;                 	//Hyde signal 4R cleared
			HSigL4.N = false;
			HydeEState = SigsCleared;
		}
		else if(HydeEState == Setting && HydeERoute == "H41" &&
			SSw15.NI && SSw17.NI && SSw19.NI && H41W)
		{
			SBH41W = false;
			Screen = &LaKr;
		   SSigL18.LockR = false;
			USSSigRight(LaKr.USSCol[28].pCol);  //Shore signal 18R cleared
			Screen = &HyYdPt;
			HSigL4.R = true;                 	//Hyde signal 4R cleared
			HSigL4.N = false;
			HydeEState = SigsCleared;
		}
		else if(HydeEState == Setting && HydeERoute == "H40" &&
			SSw15.NI && SSw17.RI)
		{
			Screen = &LaKr;
		   SSigL18.LockR = false;
			USSSigRight(LaKr.USSCol[28].pCol);  //Shore signal 18R cleared
			Screen = &HyYdPt;
			HydeEState = SigsCleared;
		}
		else if(HydeEState == SigsCleared && (H20.Blk || H20.OSE || H21.Blk || H21.OSE))
		{
			HydeEState = Running;             //Approach still occupied
		}

		else if(HydeEState == SigsCleared && (H20.Blk || H20.OSE || H21.Blk || H21.OSE))
		{
			HydeEState = Running;             //Approach still occupied
		}
		else if(HydeEState == Running && !H20.Blk && !H20.OSE && !H21.Blk && !H21.OSE)
			HydeEState = Idle;
		HEState = "HydeEState: " + GetRouteState(HydeEState);
	}
	else
		HydeEState = HydeWState = Idle;

//Power indicators

	if(H30Power)
		Indicator(6, 3, 83);
	else
		Indicator(6, 3, 82);

	if(HydeWestPower)
		Indicator(6, 5, 83);
	else
		Indicator(6, 5, 82);

	if(HydeEastPower)
		Indicator(6, 7, 83);
	else
		Indicator(6, 7, 82);

//Circuit breakers

	CBHydeJct = Flash && CktBkr[3];
	CBHydeWest = Flash && CktBkr[4];
	CBHydeEast = Flash && CktBkr[5];

}

//---------------------------------------------------------------------------
