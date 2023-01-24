//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CliffUnit.h"
//---------------------------------------------------------------------------
//Initialize Cliff
void TPSRY::InitializeCliff(void)
{
	C10.NxtW = &C11;
	C10.NxtE = &C20;
	C30.NxtW = &C11;
	C30.NxtE = &C20;
	C31.NxtW = &C11;
	C31.NxtE = &DummyBlock;
	G21.NxtW = &C11;
	G21.NxtE = &DummyBlock;
	G10.NxtW = &DummyBlock;
	G10.NxtE = &C20;
	G12.NxtW = &DummyBlock;
	G12.NxtE = &C20;
	C20.NxtW = &C10;
	C20.NxtE = &C21;
	C21.NxtW = &C22;
	C21.NxtE = &C20;
	C40.NxtW = &C22;
	C40.NxtE = &C20;
	C41.NxtW = &C22;
	C41.NxtE = &C20;
	C42.NxtW = &C22;
	C42.NxtE = &C20;
	C43.NxtW = &C22;
	C43.NxtE = &C20;
	C44.NxtW = &C22;
	C44.NxtE = &C20;
	C50.NxtW = &C22;
	C50.NxtE = &C20;
	C51.NxtW = &C22;
	C51.NxtE = &C20;
	C52.NxtW = &C22;
	C52.NxtE = &C20;
	C53.NxtW = &C22;
	C53.NxtE = &C20;
	C54.NxtW = &C22;
	C54.NxtE = &C20;

    //Hand switch

	CSw3.pBlk = &C31;
	CSw3.NI = true;

	C11.Dir = C10.Dir = C30.Dir = C20.Dir = true;
	G10.Dir = G12.Dir = true;

	//Next blocks

	C44.BlkID = "C44";
	C43.BlkID = "C43";
	C42.BlkID = "C42";
	C41.BlkID = "C41";
	C40.BlkID = "C40";
	C21.BlkID = "C21";
	C50.BlkID = "C50";
	C51.BlkID = "C51";
	C52.BlkID = "C52";
	C53.BlkID = "C53";
	C54.BlkID = "C54";
	C20.BlkID = "C20";
	C10.BlkID = "C10";
	C30.BlkID = "C30";
	C31.BlkID = "C31";
	G10.BlkID = "G10";
	G12.BlkID = "G12";
	G21.BlkID = "G21";

	//Loco pointers

	C44.pLoco = C43.pLoco = C42.pLoco = C41.pLoco = C40.pLoco = C21.pLoco = &DummyLoco;
	C50.pLoco = C51.pLoco = C52.pLoco = C53.pLoco = C54.pLoco = &DummyLoco;
	C20.pLoco = C10.pLoco = C30.pLoco = C31.pLoco = G10.pLoco = &DummyLoco;
	G12.pLoco = G21.pLoco = &DummyLoco;

}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------

//Cliff service function

void TPSRY::Cliff(void)
{
//Interlocking at GM West

//Clear routes and switch locks

	C11.RtE = G21.RtW = C10.RtW = C30.RtW = C31.RtW = Nil;

	CSw41.L = false;

//set pointers, routes and switch locks in accordance with switch positions and
//OS occupancy

	if(C31W)
	{
		C11.NxtE = &C31;		//C11 to C31
		C31.NxtW = &C11;
		C11.RtE = Restricting;
		C31.RtW = Slow;
		C11.OSE = C31.OSW = COS1;
		if(CSigL4.R || CSigL4.L || COS1 && !CRelease)
			CSw41.L = true;
	}

	else if(C30W)
	{
		C11.NxtE = &C30;		//C11 to C30
		C30.NxtW = &C11;
		C11.RtE = C30.RtW = Slow;
		C11.OSE = C30.OSW = COS1;
		if(CSigL4.R || CSigL4.L || COS1 && !CRelease)
			CSw41.L = true;
	}

	else if(C10W)
	{
		C11.NxtE = &C10;		//C11 to C10
		C10.NxtW = &C11;
		C11.RtE = C10.RtW = Main;
		C11.OSE = C10.OSW = COS1;
		if(CSigL4.R || CSigL4.L || COS1 && !CRelease)
			CSw41.L = true;
	}

	else if(G21W)
	{
		C11.NxtE = &G21;		//C11 to G21
		G21.NxtW = &C11;
		C11.RtE = G21.RtW = Restricting;
		C11.OSE = G21.OSW = COS1;
		if(CSigL4.R || CSigL4.L || COS1 && !CRelease)
			CSw41.L = true;
	}

	//Switch Buttons

	if(RBDispatcherAll->Checked && !CSw41.L)
	{
		SBC31W = SwitchButton(126, 33, &SBC31W);
		SBC30W = SwitchButton(126, 31, &SBC30W);
		SBC10W = SwitchButton(126, 29, &SBC10W);
		SBG21W = SwitchButton(126, 27, &SBG21W);
	}

   //Set signals

	Esig(CSigL4.R, &CSigL4, &C4L, &C11, RegSloAspects);

	Wsig(CSigL4.L, &CSigL4, &C4RA, &C31, SloAspects);
	Wsig(CSigL4.L, &CSigL4, &C4RB, &C30, SloAspects);
	Wsig(CSigL4.L, &CSigL4, &C4RC, &C10, RegAspects);
	Wsig(CSigL4.L, &CSigL4, &C4RD, &G21, RegAspects);

	//Set signal lever locks

	CSigL4.LockR = C4L.Lock || C11.LvrW;
	CSigL4.LockL = C4RA.Lock && (C4RB.Lock || C30.LvrE) &&
		(C4RC.Lock || C10.LvrE) && C4RD.Lock;
	SigInd(&CSigL4);

//Hand-operated switch 3

	HandSwitch(142, 32, false, &CSw3);

//Interlocking at GM East

//Clear routes and switch locks

	C10.RtE = C30.RtE = G10.RtE = G12.RtE = C20.RtW = Nil;
	CSw31.L = false;

//set pointers, routes and switch locks in accordance with switch positions and
//OS occupancy

	if(C30E)
	{
		C30.NxtE = &C20;		//C30 to C20
		C20.NxtW = &C30;
		C30.RtE = C20.RtW = Slow;
		C30.OSE = C20.OSW = COS2;
		if(CSigL2.R || CSigL2.L || COS2 && !CRelease)
			CSw31.L = true;
	}

	else if(C10E)
	{
		C10.NxtE = &C20;		//C10 to C20
		C20.NxtW = &C10;
		C10.RtE = C20.RtW = Main;
		C10.OSE = C20.OSW = COS2;
		if(CSigL2.R || CSigL2.L || COS2 && !CRelease)
			CSw31.L = true;
	}

	else if(G10E)
	{
		G10.NxtE = &C20;		//G10 to C20
		C20.NxtW = &G10;
		G10.RtE = C20.RtW = Restricting;
		G10.OSE = C20.OSW = COS2;
		if(CSigL2.R || CSigL2.L || COS2 && !CRelease)
			CSw31.L = true;
	}

	else if(G12E)
	{
		G12.NxtE = &C20;		//G12 to C20
		C20.NxtW = &G12;
		G12.RtE = C20.RtW = Restricting;
		G12.OSE = C20.OSW = COS2;
		if(CSigL2.R || CSigL2.L || COS2 && !CRelease)
			CSw31.L = true;
	}

   //Switch Buttons

	if(RBDispatcherAll->Checked && !CSw31.L)
	{
		SBC30E = SwitchButton(145, 31, &SBC30E);
		SBC10E = SwitchButton(145, 29, &SBC10E);
		SBG10E = SwitchButton(145, 27, &SBG10E);
		SBG12E = SwitchButton(145, 25, &SBG12E);
	}

	//Special signal settings for ATC for short blocks

	C20.Switch = C20.Dir && !C20.ClrE;
	if(!BkClOn->Checked)
		C22.Switch = !C22.Dir && !C22.ClrW;
	else
        C22.Switch = false;

	//Set signals

	Esig(CSigL2.R, &CSigL2, &C2LA, &C30, SloAspects);
	Esig(CSigL2.R, &CSigL2, &C2LB, &C10, RegAspects);
	Esig(CSigL2.R, &CSigL2, &C2LC, &G10, RegAspects);
	Esig(CSigL2.R, &CSigL2, &C2LD, &G12, RegAspects);

	Wsig(CSigL2.L, &CSigL2, &C2R, &C20, RegSloAspects);

	SigInd(&CSigL2);

	//Signal lever locks

	CSigL2.LockR = (C2LA.Lock || C30.LvrW) && (C2LB.Lock || C10.LvrW) &&
		C2LC.Lock && C2LD.Lock;
	CSigL2.LockL = C2R.Lock || C20.LvrE;

 //Derive switch positions from inputs

	if(C30E)
	{
		CSw33.RI = CSw35.RI = CSw31.NI = true;
		CSw33.NI = CSw35.NI = CSw31.RI = false;
	}
	else if(C10E)
	{
		CSw33.NI = CSw35.NI = CSw31.NI = true;
		CSw33.RI = CSw35.RI = CSw31.RI = false;
	}
	else if(G10E)
	{
		CSw33.RI = CSw35.RI = CSw31.RI = true;
		CSw33.NI = CSw35.NI = CSw31.NI = false;
	}
	else if(G12E)
	{
		CSw33.NI = CSw35.NI = CSw31.RI = true;
		CSw33.RI = CSw35.RI = CSw31.NI = false;
	}
	else
	{
		C10E = true;
		CSw33.NI = CSw35.NI = CSw31.NI = true;
		CSw33.RI = CSw35.RI = CSw31.RI = false;
	}

	if(C31W)
	{
		CSw37.NI = CSw39.RI = CSw41.NI = true;
		CSw37.RI = CSw39.NI = CSw41.RI = false;
	}
	else if(C30W)
	{
		CSw37.RI = CSw39.RI = CSw41.NI = true;
		CSw37.NI = CSw39.NI = CSw41.RI = false;
	}
	else if(C10W)
	{
		CSw37.NI = CSw39.NI = CSw41.NI = true;
		CSw37.RI = CSw39.RI = CSw41.RI = false;
	}
	else if(G21W)
	{
		CSw37.NI = CSw39.NI = CSw41.RI = true;
		CSw37.RI = CSw39.RI = CSw41.NI = false;
	}
	else
	{
		C10W = true;
		CSw37.NI = CSw39.NI = CSw41.NI = true;
		CSw37.RI = CSw39.RI = CSw41.RI = false;
	}


//Interlocking at Sheffield East
//Note, here eastbound becomes westbound in both directions

   //Clear routes and switch locks

	C21.RtE = C40.RtE = C41.RtE = C42.RtE = C43.RtE = C44.RtE = C20.RtE = Nil;
	C50.RtE = C51.RtE = C52.RtE = C53.RtE = C54.RtE = Nil;

	CSw43.L = false;

   //set pointers, routes and switch locks in accordance with switch positions and
	//OS occupancy

	if(C21W)
	{
		C21.NxtE = &C20;		//C21 to C20
		C20.NxtE = &C21;
		C21.RtE = C20.RtE = Main;
		C21.OSE = C20.OSE = COS3;
		if(CSigL6.R || CSigL6.L || COS3 && !CRelease)
			CSw43.L = true;
	}

	else if(C40W)
	{
		C40.NxtE = &C20;		//C40 to C20
		C20.NxtE = &C40;
		C40.RtE = C20.RtE = Slow;
		C40.OSE = C20.OSE = COS3;
		if(CSigL6.R || CSigL6.L || COS3 && !CRelease)
			CSw43.L = true;
	}

	else if(C41W)
	{
		C41.NxtE = &C20;		//C41 to C20
		C20.NxtE = &C41;
		C41.RtE = C20.RtE = Slow;
		C41.OSE = C20.OSE = COS3;
		if(CSigL6.R || CSigL6.L || COS3 && !CRelease)
			CSw43.L = true;
	}

	else if(C42W)
	{
		C42.NxtE = &C20;		//C42 to C20
		C20.NxtE = &C42;
		C42.RtE = C20.RtE = Slow;
		C42.OSE = C20.OSE = COS3;
		if(CSigL6.R || CSigL6.L || COS3 && !CRelease)
			CSw43.L = true;
	}

	else if(C43W)
	{
		C43.NxtE = &C20;		//C43 to C20
		C20.NxtE = &C43;
		C43.RtE = C20.RtE = Slow;
		C43.OSE = C20.OSE = COS3;
		if(CSigL6.R || CSigL6.L || COS3 && !CRelease)
			CSw43.L = true;
	}

	else if(C44W)
	{
		C44.NxtE = &C20;		//C44 to C20
		C20.NxtE = &C44;
		C44.RtE = C20.RtE = Slow;
		C44.OSE = C20.OSE = COS3;
		if(CSigL6.R || CSigL6.L || COS3 && !CRelease)
			CSw43.L = true;
	}
	else if(C50W)
	{
		C50.NxtE = &C20;     //C50 to C20
		C20.NxtE = &C50;
		C50.RtE = C20.RtE = Slow;
		C50.OSE = C20.OSE = COS3;
		if(CSigL6.R || CSigL6.L || COS3 && !CRelease)
			CSw43.L = true;
	}
	else if(C51W)
	{
		C51.NxtE = &C20;     //C51 to C20
		C20.NxtE = &C51;
		C51.RtE = C20.RtE = Slow;
		C51.OSE = C20.OSE = COS3;
		if(CSigL6.R || CSigL6.L || COS3 && !CRelease)
			CSw43.L = true;
	}
	else if(C52W)
	{
		C52.NxtE = &C20;     //C52 to C20
		C20.NxtE = &C52;
		C52.RtE = C20.RtE = Slow;
		C52.OSE = C20.OSE = COS3;
		if(CSigL6.R || CSigL6.L || COS3 && !CRelease)
			CSw43.L = true;
	}
	else if(C53W)
	{
		C53.NxtE = &C20;     //C53 to C20
		C20.NxtE = &C53;
		C53.RtE = C20.RtE = Slow;
		C53.OSE = C20.OSE = COS3;
		if(CSigL6.R || CSigL6.L || COS3 && !CRelease)
			CSw43.L = true;
	}
	else if(C54W)
	{
		C54.NxtE = &C20;     //C54 to C20
		C20.NxtE = &C54;
		C54.RtE = C20.RtE = Slow;
		C54.OSE = C20.OSE = COS3;
		if(CSigL6.R || CSigL6.L || COS3 && !CRelease)
			CSw43.L = true;
	}

   //Switch buttons

	if(RBDispatcherAll->Checked && !CSw43.L)
	{
		SBC44E = SwitchButton(143, 2, &SBC44E);
		SBC43E = SwitchButton(143, 4, &SBC43E);
		SBC42E = SwitchButton(143, 6, &SBC42E);
		SBC41E = SwitchButton(143, 8, &SBC41E);
		SBC40E = SwitchButton(138, 10, &SBC40E);
		SBC21E = SwitchButton(138, 12, &SBC21E);
		SBC50E = SwitchButton(138, 14, &SBC50E);
		SBC51E = SwitchButton(132, 16, &SBC51E);
		SBC52E = SwitchButton(132, 18, &SBC52E);
		SBC53E = SwitchButton(132, 20, &SBC53E);
		SBC54E = SwitchButton(132, 22, &SBC54E);
	}

//Set signals (Eastbound to westbound)

	EWsig(CSigL6.R, &CSigL6, &C6LA, &C21, RegAspects);
	EWsig(CSigL6.R, &CSigL6, &C6LB, &C40, RegAspects);
	EWsig(CSigL6.R, &CSigL6, &C6LC, &C41, RegAspects);
	EWsig(CSigL6.R, &CSigL6, &C6LD, &C42, RegAspects);
	EWsig(CSigL6.R, &CSigL6, &C6LE, &C43, RegAspects);
	EWsig(CSigL6.R, &CSigL6, &C6LF, &C44, RegAspects);
	EWsig(CSigL6.R, &CSigL6, &C6LG, &C50, RegAspects);
	EWsig(CSigL6.R, &CSigL6, &C6LH, &C51, RegAspects);
	EWsig(CSigL6.R, &CSigL6, &C6LJ, &C52, RegAspects);
	EWsig(CSigL6.R, &CSigL6, &C6LK, &C53, RegAspects);
	EWsig(CSigL6.R, &CSigL6, &C6LL, &C54, RegAspects);

	EWsig(CSigL6.L, &CSigL6, &C6R, &C20, RegAspects);

	SigInd(&CSigL6);

//Signal lever locka

	CSigL6.LockL = C6R.Lock || C20.LvrW;
	CSigL6.LockR = (C6LF.Lock || C44.LvrW) && (C6LE.Lock || C43.LvrW) && (C6LD.Lock || C42.LvrW) &&
		(C6LC.Lock || C41.LvrW) && (C6LB.Lock || C40.LvrW) && (C6LA.Lock || C21.LvrW) &&
			(C6LG.Lock || C50.LvrW) && (C6LH.Lock || C51.LvrW) && (C6LJ.Lock || C52.LvrW) &&
				(C6LK.Lock || C53.LvrW) && (C6LL.Lock || C54.LvrW);

//Interlocking at Sheffield West

//Clear routes and switch locks

	C21.RtW = C40.RtW = C41.RtW = C42.RtW = C43.RtW = C44.RtW = C22.RtE = Nil;
	C50.RtW = C51.RtW = C52.RtW = C53.RtW = C54.RtW = Nil;

	CSw61.L = false;

   //set pointers, routes and switch locks in accordance with switch positions and
	//OS occupancy

	if(C21E)
	{
		C22.NxtE = &C21;		//C22 to C21
		C21.NxtW = &C22;
		C22.RtE = Main;
		C21.RtW = Diverging;
		C22.OSE = C21.OSW = COS4;
		if(CSigL8.R || CSigL8.L || COS4 && !CRelease)
			CSw61.L = true;
	}

	else if(C40E)
	{
		C22.NxtE = &C40;		//C22 to C40
		C40.NxtW = &C22;
		C22.RtE = C40.RtW = Slow;
		C22.OSE = C40.OSW = COS4;
		if(CSigL8.R || CSigL8.L || COS4 && !CRelease)
			CSw61.L = true;
	}

	else if(C41E)
	{
		C22.NxtE = &C41;		//C22 to C41
		C41.NxtW = &C22;
		C22.RtE = C41.RtW = Slow;
		C22.OSE = C41.OSW = COS4;
		if(CSigL8.R || CSigL8.L || COS4 && !CRelease)
			CSw61.L = true;
	}

	else if(C42E)
	{
		C22.NxtE = &C42;		//C22 to C42
		C42.NxtW = &C22;
		C22.RtE = C42.RtW = Slow;
		C22.OSE = C42.OSW = COS4;
		if(CSigL8.R || CSigL8.L || COS4 && !CRelease)
			CSw61.L = true;
	}

	else if(C43E)
	{
		C22.NxtE = &C43;		//C22 to C43
		C43.NxtW = &C22;
		C22.RtE = C43.RtW = Slow;
		C22.OSE = C43.OSW = COS4;
		if(CSigL8.R || CSigL8.L || COS4 && !CRelease)
			CSw61.L = true;
	}

	else if(C44E)
	{
		C22.NxtE = &C44;		//C22 to C44
		C44.NxtW = &C22;
		C22.RtE = C44.RtW = Slow;
		C22.OSE = C44.OSW = COS4;
		if(CSigL8.R || CSigL8.L || COS4 && !CRelease)
			CSw61.L = true;
	}
	else if(C50E)
	{
		C22.NxtE = &C50;		//C22 to C50
		C50.NxtW = &C22;
		C22.RtE = C50.RtW = Slow;
		C22.OSE = C50.OSW = COS4;
		if(CSigL8.R || CSigL8.L || COS4 && !CRelease)
			CSw61.L = true;
	}
	else if(C51E)
	{
		C22.NxtE = &C51;		//C22 to C51
		C51.NxtW = &C22;
		C22.RtE = C51.RtW = Slow;
		C22.OSE = C51.OSW = COS4;
		if(CSigL8.R || CSigL8.L || COS4 && !CRelease)
			CSw61.L = true;
	}
	else if(C52E)
	{
		C22.NxtE = &C52;		//C22 to C52
		C52.NxtW = &C22;
		C22.RtE = C52.RtW = Slow;
		C22.OSE = C52.OSW = COS4;
		if(CSigL8.R || CSigL8.L || COS4 && !CRelease)
			CSw61.L = true;
	}
	else if(C53E)
	{
		C22.NxtE = &C53;		//C22 to C53
		C53.NxtW = &C22;
		C22.RtE = C53.RtW = Slow;
		C22.OSE = C53.OSW = COS4;
		if(CSigL8.R || CSigL8.L || COS4 && !CRelease)
			CSw61.L = true;
	}
	else if(C54E)
	{
		C22.NxtE = &C54;		//C22 to C54
		C54.NxtW = &C22;
		C22.RtE = C54.RtW = Slow;
		C22.OSE = C54.OSW = COS4;
		if(CSigL8.R || CSigL8.L || COS4 && !CRelease)
			CSw61.L = true;
	}
   //Switch buttons

	if(RBDispatcherAll->Checked && !CSw61.L)
	{
		SBC44W = SwitchButton(118, 2, &SBC44W);
		SBC43W = SwitchButton(118, 4, &SBC43W);
		SBC42W = SwitchButton(118, 6, &SBC42W);
		SBC41W = SwitchButton(118, 8, &SBC41W);
		SBC40W = SwitchButton(118, 10, &SBC40W);
		SBC21W = SwitchButton(118, 12, &SBC21W);
		SBC50W = SwitchButton(118, 14, &SBC50W);
		SBC51W = SwitchButton(124, 16, &SBC51W);
		SBC52W = SwitchButton(124, 18, &SBC52W);
		SBC53W = SwitchButton(124, 20, &SBC53W);
		SBC54W = SwitchButton(124, 22, &SBC54W);
	}

   //Set signals

	Esig(CSigL8.R, &CSigL8, &C8L, &C22, RegAspects);

	Wsig(CSigL8.L, &CSigL8, &C8RA, &C21, RegAspects);
	Wsig(CSigL8.L, &CSigL8, &C8RB, &C40, RegAspects);
	Wsig(CSigL8.L, &CSigL8, &C8RC, &C41, RegAspects);
	Wsig(CSigL8.L, &CSigL8, &C8RD, &C42, RegAspects);
	Wsig(CSigL8.L, &CSigL8, &C8RE, &C43, RegAspects);
	Wsig(CSigL8.L, &CSigL8, &C8RF, &C44, RegAspects);
	Wsig(CSigL8.L, &CSigL8, &C8RG, &C50, RegAspects);
	Wsig(CSigL8.L, &CSigL8, &C8RH, &C51, RegAspects);
	Wsig(CSigL8.L, &CSigL8, &C8RJ, &C52, RegAspects);
	Wsig(CSigL8.L, &CSigL8, &C8RK, &C53, RegAspects);
	Wsig(CSigL8.L, &CSigL8, &C8RL, &C54, RegAspects);

	SigInd(&CSigL8);

   //Signal lever locks

	CSigL8.LockL = (C8RF.Lock || C44.LvrE) && (C8RE.Lock || C43.LvrE) && (C8RD.Lock || C42.LvrE) &&
		(C8RC.Lock || C41.LvrE) && (C8RB.Lock || C40.LvrE) && (C8RA.Lock || C21.LvrE) &&
			(C8RG.Lock || C50.LvrE) && (C8RH.Lock || C51.LvrE) && (C8RJ.Lock || C52.LvrE) &&
				(C8RK.Lock || C53.LvrE) && (C8RL.Lock || C54.LvrE);
	CSigL8.LockR = C8L.Lock || C22.LvrW;

//Derive switch settings from routes

//West end

	if(C54W)
	{
		CSw43.RI = CSw45.RI = CSw47.RI = CSw63.NI = CSw65.NI = CSw67.NI = CSw69.RI = true;
		CSw43.NI = CSw45.NI = CSw47.NI = CSw63.RI = CSw65.RI = CSw67.RI = CSw69.NI = false;
	}
	else if(C53W)
	{
		CSw43.RI = CSw45.RI = CSw47.RI = CSw63.NI = CSw65.NI = CSw67.NI = CSw69.NI = true;
		CSw43.NI = CSw45.NI = CSw47.NI = CSw63.RI = CSw65.RI = CSw67.RI = CSw69.RI = false;
	}
	else if(C52W)
	{
		CSw43.RI = CSw45.RI = CSw47.RI = CSw63.NI = CSw65.NI = CSw67.RI = CSw69.RI = true;
		CSw43.NI = CSw45.NI = CSw47.NI = CSw63.RI = CSw65.RI = CSw67.NI = CSw69.NI = false;
	}
	else if(C51W)
	{
		CSw43.RI = CSw45.RI = CSw47.RI = CSw63.NI = CSw65.NI = CSw67.RI = CSw69.NI = true;
		CSw43.NI = CSw45.NI = CSw47.NI = CSw63.RI = CSw65.RI = CSw67.NI = CSw69.RI = false;
	}
	else if(C50W)
	{
		CSw43.RI = CSw45.RI = CSw47.RI = CSw63.NI = CSw65.RI = true;
		CSw43.NI = CSw45.NI = CSw47.NI = CSw63.RI = CSw65.NI = false;
	}
	else if(C21W)

	{	CSw43.RI = CSw45.RI = CSw47.RI = CSw63.RI = true;
		CSw43.NI = CSw45.NI = CSw47.NI = CSw63.NI = false;
	}
	else if(C40W)
	{
		CSw43.RI = CSw45.RI = CSw47.NI = true;
		CSw43.NI = CSw45.NI = CSw47.RI = false;
	}
	else if(C41W)
	{
		CSw43.RI = CSw45.NI = CSw47.RI = true;
		CSw43.NI = CSw45.RI = CSw47.NI = false;
	}
	else if(C42W)
	{
		CSw43.RI = CSw45.NI = CSw47.NI = true;
		CSw43.NI = CSw45.RI = CSw47.RI = false;
	}
	else if(C43W)
	{
		CSw43.NI = CSw45.RI = true;
		CSw43.RI = CSw45.NI = false;
	}
	else if(C44W)
	{
		CSw43.NI = CSw45.NI = true;
		CSw43.RI = CSw45.RI = false;
	}
	else
	{
		C21W = true;
		CSw43.RI = CSw45.RI = CSw47.RI = CSw63.RI = CSw65.NI = CSw67.NI = CSw69.NI = true;
		CSw43.NI = CSw45.NI = CSw47.NI = CSw63.NI = CSw65.RI = CSw67.RI = CSw69.RI = false;
	}

//East end

	if(C54E)
	{
		CSw79.RI = CSw77.NI = CSw75.NI = CSw53.NI = CSw55.NI = CSw61.NI = true;
		CSw79.NI = CSw77.RI = CSw75.RI = CSw53.RI = CSw55.RI = CSw61.RI = false;
	}
	else if(C53E)
	{
		CSw79.NI = CSw77.NI = CSw75.NI = CSw53.NI = CSw55.NI = CSw61.NI = true;
		CSw79.RI = CSw77.RI = CSw75.RI = CSw53.RI = CSw55.RI = CSw61.RI = false;
	}
	else if(C52E)
	{
		CSw79.RI = CSw77.RI = CSw75.NI = CSw53.NI = CSw55.NI = CSw61.NI = true;
		CSw79.NI = CSw77.NI = CSw75.RI = CSw53.RI = CSw55.RI = CSw61.RI = false;
   }
	else if(C51E)
	{
		CSw79.NI = CSw77.RI = CSw75.NI = CSw53.NI = CSw55.NI = CSw61.NI = true;
		CSw79.RI = CSw77.NI = CSw75.RI = CSw53.RI = CSw55.RI = CSw61.RI = false;
   }
	else if(C50E)
	{
		CSw75.RI = CSw53.NI = CSw55.NI = CSw61.NI = true;
		CSw75.NI = CSw53.RI = CSw55.RI = CSw61.RI = false;
   }
	else if(C21E)
	{
		CSw53.RI = CSw55.NI = CSw61.NI = true;
		CSw53.NI = CSw55.RI = CSw61.RI = false;
	}
	else if(C40E)
	{
		CSw55.RI = CSw61.NI = true;
		CSw55.NI = CSw61.RI = false;
	}
	else if(C41E)
	{
		CSw53.NI = CSw55.NI = CSw61.RI = true;
		CSw53.RI = CSw55.RI = CSw61.NI = false;
	}
	else if(C42E)
	{
		CSw53.RI = CSw55.NI = CSw61.RI = true;
		CSw53.NI = CSw55.RI = CSw61.NI = false;
	}
	else if(C43E)
	{
		CSw53.NI = CSw55.RI = CSw61.RI = true;
		CSw53.RI = CSw55.NI = CSw61.NI = false;
	}
	else if(C44E)
	{
		CSw53.RI = CSw55.RI = CSw61.RI = true;
		CSw53.NI = CSw55.NI = CSw61.NI = false;
	}
	else
	{
		C21E = true;
		CSw79.NI = CSw77.NI = CSw75.NI = CSw53.RI = CSw55.NI = CSw61.NI = true;
		CSw79.RI = CSw77.RI = CSw75.RI = CSw53.NI = CSw55.RI = CSw61.RI = false;
	}

//Block indications

	BlkInd(&C10);
	BlkInd(&C11);
	BlkInd(&C30);
	BlkInd(&C31);
	BlkInd(&C20);
	BlkInd(&C21);
	BlkInd(&C40);
	BlkInd(&C41);
	BlkInd(&C42);
	BlkInd(&C43);
	BlkInd(&C44);
	BlkInd(&C50);
	BlkInd(&C51);
	BlkInd(&C52);
	BlkInd(&C53);
	BlkInd(&C54);

//Automatic train control

	ERearATC(&C10, &C2LB);
	ERearATC(&C30, &C2LA);

	WRearATC(&C40, &C8RB);
	WRearATC(&C41, &C8RC);
	WRearATC(&C42, &C8RD);
	WRearATC(&C43, &C8RE);
	WRearATC(&C44, &C8RF);
	WRearATC(&C21, &C8RA);
	WRearATC(&C50, &C8RG);
	WRearATC(&C51, &C8RH);
	WRearATC(&C52, &C8RJ);
	WRearATC(&C53, &C8RK);
	WRearATC(&C54, &C8RL);

	TrainID(&C44);
	TrainID(&C43);
	TrainID(&C42);
	TrainID(&C41);
	TrainID(&C40);
	TrainID(&C21);
	TrainID(&C50);
	TrainID(&C51);
	TrainID(&C52);
	TrainID(&C53);
	TrainID(&C54);

	TrainID(&C11);

	TrainID(&G21);
	TrainID(&G10);
	TrainID(&G12);
	TrainID(&C10);
	TrainID(&C30);
	TrainID(&C31);

	TrainID(&C20);

//Update Cliff/Hyde image

//Switches

	Switch(107, 12, &CSw61, 2, 11);
	Switch(110, 12, &CSw55, 2, 11);  //Switches 55 and 59 linked
	Switch(111, 8, &CSw55, 8, 6);
	Switch(114, 8, &CSw53, 2, 11);   //Switches 53, 57 and 73 linked
	Switch(115, 4, &CSw53, 8, 6);
	Switch(113, 12, &CSw53, 9, 2);
	Switch(115, 14, &CSw75, 7, 10);
	Switch(117, 16, &CSw77, 7, 10);
	Switch(120, 16, &CSw79, 2, 9);   //Switches 79 and 81 linked
	Switch(121, 20, &CSw79, 10, 7);

	Switch(135, 20, &CSw69, 11, 6);  //Switches 69 and 71 linked
	Switch(136, 16, &CSw69, 2, 8);
	Switch(139, 16, &CSw67, 6, 11);
	Switch(141, 14, &CSw65, 6, 11);
	Switch(143, 12, &CSw63, 6, 11);
	Switch(145, 10, &CSw47, 11, 6);
	Switch(146, 6, &CSw47, 2, 8);
	Switch(149, 6, &CSw45, 11, 6);   //Switches 45 and 49 linked
	Switch(150, 2, &CSw45, 2, 8);
	Switch(153, 2, &CSw43, 2, 8);

	Switch(120, 29, &CSw41, 2, 11);
	Switch(121, 29, &CSw39, 2, 9);
	Switch(123, 31, &CSw37, 7, 10);

	Switch(142, 31, &CSw3, 2, 8);

	Switch(148, 27, &CSw35, 7, 9);
	Switch(149, 29, &CSw33, 2, 8);
	Switch(150, 29, &CSw31, 2, 10);

//Blocks

	XTracker(106, 12, &C22, OSE, &COS4);

	Tracker(119, 2, &C44, Blk);
	Tracker(119, 4, &C43, Blk);
	Tracker(119, 6, &C42, Blk);
	Tracker(119, 8, &C41, Blk);
	Tracker(119, 10, &C40, Blk);
	Tracker(119, 12, &C21, DBlk);
	Tracker(119, 14, &C50, Blk);
	Tracker(125, 16, &C51, Blk);
	Tracker(125, 18, &C52, Blk);
	Tracker(125, 20, &C53, Blk);
	Tracker(125, 22, &C54, Blk);

	XTracker(144, 2, &C44, OSE, &COS3);
	XTracker(144, 4, &C43, OSE, &COS3);
	XTracker(144, 6, &C42, OSE, &COS3);
	XTracker(144, 8, &C41, OSE, &COS3);
	XTracker(139, 10, &C40, OSE, &COS3);
	XTracker(139, 12, &C21, OSE, &COS3);
	XTracker(139, 14, &C50, OSE, &COS3);
	XTracker(133, 16, &C51, OSE, &COS3);
	XTracker(133, 18, &C52, OSE, &COS3);
	XTracker(133, 20, &C53, OSE, &COS3);
	XTracker(133, 22, &C54, OSE, &COS3);

	Tracker(152, 29, &C20, DBlk);
	Tracker(155, 2, &C20, RDBlk);
	Tracker(100, 14, &C11, DBlk);

	XTracker(119, 29, &C11, OSE, &COS1);

	Tracker(127, 27, &G21, Yd);
	Tracker(142, 25, &G12, Yd);
	Tracker(142, 27, &G10, Yd);

	Tracker(127, 29, &C10, DBlk);
	Tracker(127, 31, &C30, DBlk);
	Tracker(127, 33, &C31, Blk);

	XTracker(146, 25, &G12, OSE, &COS2);
	XTracker(146, 27, &G10, OSE, &COS2);
	XTracker(146, 29, &C10, OSE, &COS2);
	XTracker(146, 31, &C30, OSE, &COS2);

//Signals

	SignalE(106, 13, &C22); //8L

	SignalW(118, 1, &C44);	//8RF
	SignalW(118, 3, &C43);	//8RE
	SignalW(118, 5, &C42);	//8RD
	SignalW(118, 7, &C41);	//8RC
	SignalW(118, 9, &C40);	//8RB
	SignalW(118, 11, &C21);	//8RA
	SignalW(118, 13, &C50);	//8RG
	SignalW(124, 15, &C51);	//8RH
	SignalW(124, 17, &C52);	//8RJ
	SignalW(124, 19, &C53);	//8RK
	SignalW(124, 21, &C54);	//8RL

	SignalE(143, 3, &C44);	//6LF
	SignalE(143, 5, &C43);	//6LE
	SignalE(143, 7, &C42);	//6LD
	SignalE(143, 9, &C41);	//6LC
	SignalE(138, 11, &C40);	//6LB
	SignalE(138, 13, &C21);	//6LA
	SignalE(138, 15, &C50);	//6LG
	SignalE(132, 17, &C51);	//6LH
	SignalE(132, 19, &C52);	//6LJ
	SignalE(132, 21, &C53);	//6LK
	SignalE(132, 23, &C54);	//6LL

	SignalWE(154, 1, &C20); //6R
	SignalE(119, 30, &C11);	//4L

	SignalW(126, 26, &G21);	//4RD
	SignalW(126, 28, &C10);	//4RC
	SignalW(126, 30, &C30);	//4RB
	SignalW(126, 32, &C31);	//4RA

	SignalE(145, 26, &G12);	//2LD
	SignalE(145, 28, &G10);	//2LC
	SignalE(145, 30, &C10); //2LB
	SignalE(145, 32, &C30); //2LA

	SignalW(151, 28, &C20); //2R

//Train Identification

	DisplayID(126, 2, &C44);
	DisplayID(126, 4, &C43);
	DisplayID(126, 6, &C42);
	DisplayID(126, 8, &C41);
	DisplayID(126, 10, &C40);
	DisplayID(126, 12, &C21);
	DisplayID(126, 14, &C50);
	DisplayID(126, 16, &C51);
	DisplayID(126, 18, &C52);
	DisplayID(126, 20, &C53);
	DisplayID(126, 22, &C54);
 //	DisplayID(127, 27, &G21);
 //	DisplayID(142, 25, &G12);
 //	DisplayID(142, 27, &G10);
	DisplayID(128, 29, &C10);
	DisplayID(128, 31, &C30);
	DisplayID(128, 33, &C31);

	DisplayID(153, 29, &C20);

//Circuit breaker indications

   CBGreenMountain = Flash && (CktBkr[0] || CktBkr[2]);
   CBSheffield = Flash && (CktBkr[1] || CktBkr[38]);
   CBReverser = Flash && (CktBkr[8]);
}
