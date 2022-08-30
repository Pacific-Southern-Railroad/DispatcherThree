//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "PortUnit.h"

//Initialize Port

void TPSRY::InitializePort(void)
{
    P1.NxtW = &DummyBlock;
	P1.NxtE = &P40;

    P2.NxtW = &DummyBlock;
    P2.NxtE = &P40;

    P3.NxtW = &DummyBlock;
    P3.NxtE = &P62;

    P4.NxtW = &DummyBlock;
    P4.NxtE = &P20;

    P5.NxtW = &DummyBlock;
    P5.NxtE = &P10;

    P6.NxtW = &DummyBlock;
    P6.NxtE = &P10;

    P7.NxtW = &DummyBlock;
    P7.NxtE = &P60;

    V10.NxtW = &P7;
    V10.NxtE = &DummyBlock;

    V11.NxtW = &DummyBlock;
    V11.NxtE = &P11;

    P60.NxtW = &P7;
    P60.NxtE = &P11;

    P61.NxtW = &P7;
    P61.NxtE = &P11;

    P10.NxtW = &P5;
    P10.NxtE = &P11;

    P20.NxtW = &P6;
    P20.NxtE = &P21;

    P62.NxtW = &P3;
    P62.NxtE = &DummyBlock;

    P63.NxtW = &P3;
    P63.NxtE = &DummyBlock;

    P64.NxtW = &P3;
    P64.NxtE = &DummyBlock;

    P40.NxtW = &P2;
    P40.NxtE = &P41;

    P30.NxtW = &P31;
    P30.NxtE = &P11;

    P50.NxtW = &Y21;
    P50.NxtE = &P10;

    P11.NxtW = &P10;
    P11.NxtE = &L21;

    P21.NxtW = &P20;
    P21.NxtE = &L31;

    P31.NxtW = &P30;
    P31.NxtE = &P32;

    P32.NxtW = &S20;
    P32.NxtE = &P31;

    P41.NxtW = &P40;
    P41.NxtE = &P42;

    P42.NxtE = &N25;
    P42.NxtW = &P41;

	PBSw5.Hand = PBSw5.N = true; PBSw5.pBlk = &P41;
	PBSw15.Hand = PBSw15.N = true; PBSw15.pBlk = &P42;

	PortAAborts = PortBAborts = ParsonsAborts = 0;

    P1.Dir = P2.Dir = P3.Dir = P4.Dir = P5.Dir = P6.Dir = P7.Dir = true;
	P20.Dir = P21.Dir = P32.Dir = P41.Dir = true;

	//Switches

	PASw1.NI = PASw3.NI = PASw5.NI = PASw7.NI = PASw9.NI = PASw11.NI = true;
	PASw13.NI = PASw15.NI = PASw17.NI = PASw19.NI = PASw21.NI = PASw23.NI = true;
	PASw27.NI = PASw29.NI = PASw31.NI = PASw33.NI = PASw35.NI = PASw37.NI = true;
	PBSw1.NI = PBSw3.NI = PBSw5.NI = PBSw11.NI = PBSw13.NI =
	PBSw15.NI = PBSw15A.NI = PBSw15B.NI = true;

	//Signals

	PASigL4.N = PASigL6.N = PASigL8.N = PASigL10.N = PASigL12.N = true;
	PASigL32.N = PASigL34.N = true;

	PBSigL2.N = PBSigL4.N = PBSigL12.N = PBSigL14.N = true;

	//Block IDs

	P1.BlkID = "P1";
	P2.BlkID = "P2";
	P3.BlkID = "P3";
	P4.BlkID = "P4";
	P5.BlkID = "P5";
	P6.BlkID = "P6";
	P7.BlkID = "P7";
	P10.BlkID = "P10";
	P11.BlkID = "P11";
	P20.BlkID = "P20";
	P21.BlkID = "P21";
	P30.BlkID = "P30";
	P31.BlkID = "P31";
	P32.BlkID = "P32";
	P40.BlkID = "P40";
	P41.BlkID = "P41";
	P42.BlkID = "P42";
	P50.BlkID = "P50";
	P60.BlkID = "P60";
	P61.BlkID = "P61";
	P62.BlkID = "P62";
	P63.BlkID = "P63";
	P64.BlkID = "P64";
	V10.BlkID = "V10";
	V11.BlkID = "V11";

//Loco pointers

	P1.pLoco = P2.pLoco = P3.pLoco = P4.pLoco = P5.pLoco = &DummyLoco;
	P6.pLoco = P7.pLoco = P10.pLoco = P11.pLoco = P20.pLoco = &DummyLoco;
	P21.pLoco = P30.pLoco = P31.pLoco = P32.pLoco = P41.pLoco = &DummyLoco;
	P42.pLoco = P50.pLoco = P60.pLoco = P61.pLoco = P62.pLoco = &DummyLoco;
	P63.pLoco = P64.pLoco = V10.pLoco = V11.pLoco = &DummyLoco;

}

//Port service function

void TPSRY::Port(void)
{
//Southport interlocking

//Clear routes and switch locks

	P1.RtE = P2.RtE = P3.RtE = P4.RtE = P5.RtE = P6.RtE = P7.RtE = Nil;
	V10.RtW = P60.RtW = P61.RtW = P10.RtW = P20.RtW = P62.RtW = P63.RtW = P64.RtW = P40.RtW = Nil;

    PASw1.L = PASw3.L = PASw5.L = PASw7.L = PASw9.L = PASw11.L = PASw13.L =
		PASw15.L = PASw17.L = PASw19.L = PASw21.L = PASw23.L = false;

//Set pointers, routes and switch locks in accordance with switch positions and
//OS occupancy

	if(PASw15.RI && PASw17.NI)
    {
    	P7.NxtE = &V10;			//P7 to V10
        V10.NxtW = &P7;
        P7.RtE = V10.RtW = Restricting;
        P7.OSE = V10.OSW = PAOS1;
        if(PASigL12.R || PASigL12.L || P7.OSE && !PARelease)
			PASw15.L = SPL7 = true;
    }

    else if(PASw15.RI && PASw17.RI)
    {
    	P7.NxtE = &P60;			//P7 to P60
        P60.NxtW = &P7;
        P7.RtE = P60.RtW = Restricting;
        P7.OSE = P60.OSW = PAOS1;
        if(PASigL12.R || PASigL12.L || P7.OSE && !PARelease)
			PASw15.L = SPL7 = true;
    }

    else if(PASw15.NI && PASw19.NI)
    {
    	P7.NxtE = &P61;			//P7 to P61
        P61.NxtW = &P7;
        P7.RtE = P61.RtW = Restricting;
        P7.OSE = P61.OSW = PAOS1;
        if(PASigL12.R || PASigL12.L || P7.OSE && !PARelease)
			PASw15.L = PASw19.L = SPL7 = true;
    }

    else if(PASw15.NI && PASw19.RI && PASw21.RI && PASw23.NI && PASw7.NI)
    {
    	P7.NxtE = &P10;			//P7 to P10
        P10.NxtW = &P7;
        P7.RtE = P10.RtW = Slow;
        P7.OSE = P10.OSW = PAOS1 || PAOS2;
        if(PASigL12.R || PASigL10.L || P7.OSE && !PARelease)
			PASw15.L = PASw19.L = PASw21.L = PASw23.L = PASw7.L =
				SPL7 = SPL6 = SPL5 = true;
	}

	else if(PASw15.NI && PASw19.RI && PASw21.RI && PASw23.RI && PASw5.NI && PASw7.NI)
	{
		P7.NxtE = &P20;			//P7 to P20
		P20.NxtW = &P7;
		P7.RtE = Slow;
		P20.RtW = Restricting;
		P7.OSE = P20.OSW = PAOS1 || PAOS2 || PAOS3;
		if(PASigL12.R || PASigL8.L || P7.OSE && !PARelease)
			PASw15.L = PASw19.L = PASw21.L = PASw23.L = PASw5.L = PASw7.L =
				SPL7 = SPL6 = SPL5 = SPL4 = true;
	}

	if(PASw19.NI && PASw21.RI && PASw23.NI && PASw7.NI)
	{
    	P6.NxtE = &P10;			//P6 to P10
        P10.NxtW = &P6;
        P6.RtE = Slow;
        P10.RtW = Restricting;
        P6.OSE = P10.OSW = PAOS2;
        if(PASigL10.R || PASigL10.L || P6.OSE && !PARelease)
			PASw19.L = PASw21.L = PASw23.L = PASw7.L =
				SPL6 = SPL5 = true;
    }

    else if(PASw19.NI && PASw21.RI && PASw23.RI && PASw5.NI && PASw7.NI)
    {
    	P6.NxtE = &P20;			//P6 to P20
        P20.NxtW = &P6;
        P6.RtE = Slow;
        P20.RtW = Restricting;
        P6.OSE = P20.OSW = PAOS2 || PAOS3;
        if(PASigL10.R || PASigL8.L || P6.OSE && !PARelease)
			PASw19.L = PASw21.L = PASw23.L = PASw5.L = PASw7.L =
				SPL6 = SPL5 = SPL4 = true;
    }

    if(PASw21.NI && PASw23.NI && PASw7.NI)
    {
    	P5.NxtE = &P10;			//P5 to P10
        P10.NxtW = &P5;
        P5.RtE = P10.RtW = Slow;
        P5.OSE = P10.OSW = PAOS2;
        if(PASigL10.R || PASigL10.L || P5.OSE && !PARelease)
			PASw21.L = PASw23.L = PASw7.L =
				SPL5 = true;
    }

    else if(PASw21.NI && PASw23.RI && PASw5.NI && PASw7.NI)
    {
    	P5.NxtE = &P20;			//P5 to P20
        P20.NxtW = &P5;
        P5.RtE = Slow;
        P20.RtW = Restricting;
        P5.OSE = P20.OSW = PAOS2 || PAOS3;
        if(PASigL10.R || PASigL8.L || P5.OSE && !PARelease)
			PASw21.L = PASw23.L = PASw5.L = PASw7.L =
				SPL5 = SPL4 = true;
    }

    if(PASw23.NI && PASw5.NI && PASw7.RI)
    {
    	P4.NxtE = &P10;			//P4 to P10
        P10.NxtW = &P4;
        P4.RtE = P10.RtW = Slow;
        P4.OSE = P10.OSW = PAOS3 || PAOS2;
        if(PASigL8.R || PASigL10.R || P4.OSE && !PARelease)
			PASw23.L = PASw5.L = PASw7.L =
				SPL4 = SPL5 = true;
    }

    else if(PASw23.NI && PASw5.NI && PASw7.NI)
    {
    	P4.NxtE = &P20;			//P4 to P20
        P20.NxtW = &P4;
        P4.RtE = Slow;
        P20.RtW = Restricting;
        P4.OSE = P20.OSW = PAOS3;
        if(PASigL8.R || PASigL8.L || P4.OSE && !PARelease)
			PASw23.L = PASw5.L = PASw7.L =
				SPL4 = true;
    }

    if(PASw9.NI && PASw3.NI && PASw5.RI && PASw7.RI)
    {
    	P3.NxtE = &P10;			//P3 to P10
        P10.NxtW = &P3;
        P3.RtE = P10.RtW = Slow;
        P3.OSE = P10.OSW = PAOS4 || PAOS3 || PAOS2;
        if(PASigL6.R || PASigL10.L || P3.OSE && !PARelease)
			PASw9.L = PASw3.L = PASw5.L = PASw7.L =
				SPL3 = SPL4 = SPL5 = true;
    }

    else if(PASw9.NI && PASw3.NI && PASw5.RI && PASw7.NI)
    {
    	P3.NxtE = &P20;			//P3 to P20
        P20.NxtW = &P3;
        P3.RtE = Slow;
        P20.RtW = Restricting;
        P3.OSE = P20.OSW = PAOS4 || PAOS3;
        if(PASigL6.R || PASigL8.L || P3.OSE && !PARelease)
			PASw9.L = PASw3.L = PASw5.L = PASw7.L =
				SPL3 = SPL4 = true;
    }

    else if(PASw9.NI && PASw3.NI && PASw5.NI && PASw11.NI)
    {
    	P3.NxtE = &P62;			//P3 to P62
        P62.NxtW = &P3;
        P3.RtE = P62.RtW = Restricting;
        P3.OSE = P62.OSW = PAOS4;
        if(PASigL6.R || PASigL6.L || P3.OSE && !PARelease)
			PASw9.L = PASw3.L = PASw5.L = PASw11.L =
				SPL3 = true;
    }

    else if(PASw9.NI && PASw3.NI && PASw5.NI && PASw11.RI && PASw13.RI)
    {
		P3.NxtE = &P63;			//P3 to P63
        P63.NxtW = &P3;
        P3.RtE = P63.RtW = Restricting;
        P3.OSE = P63.OSW = PAOS4;
        if(PASigL6.R || PASigL6.L || P3.OSE && !PARelease)
			PASw9.L = PASw3.L = PASw5.L = PASw11.L =
				SPL3 = true;
    }

    else if(PASw9.NI && PASw3.NI && PASw5.NI && PASw11.RI && PASw13.NI)
    {
    	P3.NxtE = &P64;			//P3 to P64
        P64.NxtW = &P3;
        P3.RtE = P64.RtW = Restricting;
        P3.OSE = P64.OSW = PAOS4;
        if(PASigL6.R || PASigL6.L || P3.OSE && !PARelease)
			PASw9.L = PASw3.L = PASw5.L = PASw11.L =
				SPL3 = true;
    }

    else if(PASw9.RI&& PASw3.NI)
    {
    	P3.NxtE = &P40;			//P3 to P40
        P40.NxtW = &P3;
        P3.RtE = P40.RtW = Slow;
        P3.OSE = P40.OSW = PAOS4 || PAOS5;
        if(PASigL6.R || PASigL4.L || P3.OSE && !PARelease)
			PASw9.L = PASw3.L =
				SPL3 = SPL2 = true;
    }

    if(PASw1.NI && PASw3.RI && PASw9.NI && PASw5.RI && PASw7.RI)
    {
    	P2.NxtE = &P10;			//P2 to P10
		P10.NxtW = &P2;
        P2.RtE = P10.RtW = Slow;
        P2.OSE = P10.OSW = PAOS5 || PAOS4 || PAOS3 || PAOS2;
        if(PASigL4.R || PASigL10.L || P2.OSE && !PARelease)
			PASw1.L = PASw3.L = PASw9.L = PASw5.L = PASw7.L =
				SPL2 = SPL3 = SPL4 = SPL5 = true;
    }

    else if(PASw1.NI && PASw3.RI && PASw9.NI && PASw5.RI && PASw7.NI)
    {
    	P2.NxtE = &P20;			//P2 to P20
        P20.NxtW = &P2;
        P2.RtE = Slow;
        P20.RtW = Restricting;
        P2.OSE = P20.OSW = PAOS5 || PAOS4 || PAOS3;
        if(PASigL4.R || PASigL8.L || P2.OSE && !PARelease)
			PASw1.L = PASw3.L = PASw9.L = PASw5.L = PASw7.L =
				SPL2 = SPL3 = SPL4 = true;
    }

    else if(PASw1.NI && PASw3.RI && PASw9.NI && PASw5.NI && PASw11.NI)
    {
		P2.NxtE = &P62;			//P2 to P62
        P62.NxtW = &P2;
        P2.RtE = P62.RtW = Restricting;
        P2.OSE = P62.OSW = PAOS5 || PAOS4;
        if(PASigL4.R || PASigL6.L || P2.OSE && !PARelease)
			PASw1.L = PASw3.L = PASw9.L = PASw5.L = PASw11.L =
				SPL2 = SPL3 = true;
    }

    else if(PASw1.NI && PASw3.RI && PASw9.NI && PASw5.NI && PASw11.RI && PASw13.RI)
    {
		P2.NxtE = &P63;			//P2 to P63
        P63.NxtW = &P2;
        P2.RtE = P63.RtW = Restricting;
        P2.OSE = P63.OSW = PAOS5 || PAOS4;
        if(PASigL4.R || PASigL6.L || P2.OSE && !PARelease)
			PASw1.L = PASw3.L = PASw9.L = PASw5.L = PASw11.L =
				SPL2 = SPL3 = true;
    }

    else if(PASw1.NI && PASw3.RI && PASw9.NI && PASw5.NI && PASw11.RI && PASw13.NI)
    {
    	P2.NxtE = &P64;			//P2 to P64
		P64.NxtW = &P2;
        P2.RtE = P64.RtW = Restricting;
        P2.OSE = P64.OSW = PAOS5 || PAOS4;
        if(PASigL4.R || PASigL6.L || P2.OSE && !PARelease)
			PASw1.L = PASw3.L = PASw9.L = PASw5.L = PASw11.L =
				SPL2 = SPL3 = true;
    }

    else if(PASw1.NI && PASw3.NI && PASw9.NI)
    {
    	P2.NxtE = &P40;			//P2 to P40
        P40.NxtW = &P2;
        P2.RtE = P40.RtW = Slow;
        P2.OSE = P40.OSW = PAOS5;
        if(PASigL4.R || PASigL4.L || P2.OSE && !PARelease)
			PASw1.L = PASw3.L = PASw9.L =
				SPL2 = true;
    }

    if(PASw1.RI && PASw3.RI && PASw9.NI && PASw5.RI && PASw7.RI)
    {
    	P1.NxtE = &P10;			//P1 to P10
        P10.NxtW = &P1;
        P1.RtE = Slow;
        P10.RtW = Restricting;
        P1.OSE = P10.OSW = PAOS5 || PAOS4 || PAOS3 || PAOS2;
        if(PASigL4.R || PASigL10.L || P1.OSE && !PARelease)
			PASw1.L = PASw3.L = PASw9.L = PASw5.L = PASw7.L =
				SPL2 = SPL3 = SPL4 = SPL5 = true;
    }

    else if(PASw1.RI && PASw3.RI && PASw9.NI && PASw5.RI && PASw7.NI)
    {
    	P1.NxtE = &P20;			//P1 to P20
        P20.NxtW = &P1;
        P1.RtE = Slow;
        P20.RtW = Restricting;
        P1.OSE = P20.OSW = PAOS5 || PAOS4 || PAOS3;
        if(PASigL4.R || PASigL8.L || P1.OSE && !PARelease)
			PASw1.L = PASw3.L = PASw9.L = PASw5.L = PASw7.L =
				SPL2 = SPL3 = SPL4 = true;
    }

    else if(PASw1.RI && PASw3.RI && PASw9.NI && PASw5.NI && PASw11.NI)
    {
    	P1.NxtE = &P62;			//P1 to P62
        P62.NxtW = &P1;
        P1.RtE = P62.RtW = Restricting;
        P1.OSE = P62.OSW = PAOS5 || PAOS4;
        if(PASigL4.R || PASigL6.L || P1.OSE && !PARelease)
			PASw1.L = PASw3.L = PASw9.L = PASw5.L = PASw11.L =
				SPL2 = SPL3 = true;
    }

    else if(PASw1.RI && PASw3.RI && PASw9.NI && PASw5.NI && PASw11.RI && PASw13.RI)
    {
    	P1.NxtE = &P63;			//P1 to P63
        P63.NxtW = &P1;
        P1.RtE = P63.RtW = Restricting;
        P1.OSE = P63.OSW = PAOS5 || PAOS4;
        if(PASigL4.R || PASigL6.L || P1.OSE && !PARelease)
			PASw1.L = PASw3.L = PASw9.L = PASw5.L = PASw11.L =
				SPL2 = SPL3 = true;
    }

    else if(PASw1.RI && PASw3.RI && PASw9.NI && PASw5.NI && PASw11.RI && PASw13.NI)
    {
    	P1.NxtE = &P64;			//P1 to P64
        P64.NxtW = &P1;
        P1.RtE = P64.RtW = Restricting;
        P1.OSE = P64.OSW = PAOS5 || PAOS4;
        if(PASigL4.R || PASigL6.L || P1.OSE && !PARelease)
			PASw1.L = PASw3.L = PASw9.L = PASw5.L = PASw11.L =
				SPL2 = SPL3 = true;
    }

    else if(PASw1.RI && PASw3.NI && PASw9.NI)
    {
    	P1.NxtE = &P40;			//P1 to P40
        P40.NxtW = &P1;
        P1.RtE = Slow;
        P40.RtW = Restricting;
        P1.OSE = P40.OSW = PAOS5;
        if(PASigL4.R || PASigL4.L || P1.OSE && !PARelease)
			PASw1.L = PASw3.L = PASw9.L =
				SPL2 = true;
    }

//Set Signals

	Esig(PASigL12.R, &PASigL12, &PA12R, &P7, SloAspects);
    Wsig(PASigL12.L, &PASigL12, &PA12LA, &V10, RegAspects);
    Wsig(PASigL12.L, &PASigL12, &PA12LB, &P60, RegAspects);
    Wsig(PASigL12.L, &PASigL12, &PA12LC, &P61, RegAspects);
    SigInd(&PASigL12);

	Esig(PASigL10.R, &PASigL10, &PA10RA, &P6, SloAspects);
	Esig(PASigL10.R, &PASigL10, &PA10RB, &P5, SloAspects);
    Wsig(PASigL10.L, &PASigL10, &PA10L, &P10, SloAspects);
    SigInd(&PASigL10);

    PA10La = PA10Lb = false;                         //Semaphore 10L
    if(!PA10L.Aspect[0] && PA10L.Aspect[1])
    	PA10La = true;                              //Clear
    else if(PA10L.Aspect[0] && !PA10L.Aspect[1])
    	PA10Lb = true;                              //Restricting

	Esig(PASigL8.R, &PASigL8, &PA8R, &P4, SloAspects);
    Wsig(PASigL8.L, &PASigL8, &PA8L, &P20, RegAspects);
    SigInd(&PASigL8);

	Esig(PASigL6.R, &PASigL6, &PA6R, &P3, SloAspects);
    Wsig(PASigL6.L, &PASigL6, &PA6LA, &P62, RegAspects);
    Wsig(PASigL6.L, &PASigL6, &PA6LB, &P63, RegAspects);
    Wsig(PASigL6.L, &PASigL6, &PA6LC, &P64, RegAspects);
    SigInd(&PASigL6);

	Esig(PASigL4.R, &PASigL4, &PA4RA, &P2, SloAspects);
	Esig(PASigL4.R, &PASigL4, &PA4RB, &P1, SloAspects);
    Wsig(PASigL4.L, &PASigL4, &PA4L, &P40, SloAspects);
    SigInd(&PASigL4);

    PA4La = PA4Lb = false;							//Semaphore 4L
    if(!PA4L.Aspect[0] && PA4L.Aspect[1])
    	PA4La= true;                                //Clear
    else if(PA4L.Aspect[0] && !PA10L.Aspect[1])
    	PA4Lb = true;                               //Restricting

//Parsons Jct Interlocking

//Clear routes and switch locks

	V11.RtE = P60.RtE = P61.RtE = P10.RtE = P20.RtE = P30.RtE =
		P50.RtE = P11.RtW = P21.RtW = Nil;

    PASw27.L = PASw29.L = PASw31.L = PASw33.L = PASw35.L = PASw37.L = false;
	PJSwL1 = PJSwL2 = false;

//Set pointers, routes and switch locks in accordance with switch positions and
//OS occupancy

	if(PASw27.NI && PASw29.NI && PASw31.RI && PASw35.NI && PASw37.RI)
    {
		V11.NxtE = &P50;			//V11 to P50 (direction change)
        P50.NxtE = &V11;
        V11.RtE = P50.RtE = Restricting;
        V11.OSE = P50.OSE = PJOS1;
        if(PASigL34.R || PASigL34.L || V11.OSE && !PARelease)
			PJSwL1 = true;
	}

	else if(PASw27.RI && PASw29.NI && PASw31.RI && PASw35.NI && PASw37.RI)
    {
		P60.NxtE = &P50;			//P60 to P50 (direction change)
        P50.NxtE = &P60;
        P60.RtE = P50.RtE = Restricting;
		P60.OSE = P50.OSE = PJOS1;
        if(PASigL34.R || PASigL34.L || P60.OSE && !PARelease)
			PJSwL1 = true;
    }

	else if(PASw29.RI && PASw31.RI && PASw35.NI && PASw37.RI)
    {
    	P61.NxtE = &P50;			//P61 to P50 (direction change)
        P50.NxtE = &P61;
        P61.RtE = P50.RtE = Restricting;
        P61.OSE = P50.OSE = PJOS1;
        if(PASigL34.R || PASigL34.L || P61.OSE && !PARelease)
			PJSwL1 = true;
    }

	else if(PASw31.NI && PASw35.NI && PASw37.RI)
    {
    	P10.NxtE = &P50;			//P10 to P50 (direction change)
        P50.NxtE = &P10;
        P10.RtE = P50.RtE = Diverging;
        P10.OSE = P50.OSE = PJOS1;
        if(PASigL34.R || PASigL34.L || P10.OSE && !PARelease)
			PJSwL1 = true;
    }

    if(PASw27.NI && PASw29.NI && PASw31.RI && PASw35.NI && PASw37.NI)
    {
    	V11.NxtE = &P11;			//V11 to P11
        P11.NxtW = &V11;
        V11.RtE = P11.RtW = Restricting;
        V11.OSE = P11.OSW = PJOS1;
        if(PASigL34.R || PASigL34.L || V11.OSE && !PARelease)
			PJSwL1 = true;
	}

    else if(PASw27.RI && PASw29.NI && PASw31.RI && PASw35.NI && PASw37.NI)
    {
    	P60.NxtE = &P11;			//P60 to P11
        P11.NxtW = &P60;
        P60.RtE = P11.RtW = Restricting;
        P60.OSE = P11.OSW = PJOS1;
        if(PASigL34.R || PASigL34.L || P60.OSE && !PARelease)
			PJSwL1 = true;
    }

    else if(PASw29.RI && PASw31.RI && PASw35.NI && PASw37.NI)
    {
    	P61.NxtE = &P11;			//P61 to P11
        P11.NxtW = &P61;
        P61.RtE = P11.RtW = Restricting;
        P61.OSE = P11.OSW = PJOS1;
        if(PASigL34.R || PASigL34.L || P61.OSE && !PARelease)
			PJSwL1 = true;
	}

    else if(PASw31.NI && PASw35.NI && PASw37.NI)
    {
		P10.NxtE = &P11;			//P10 to P11
        P11.NxtW = &P10;
        P10.RtE = Restricting;
        P11.RtW = Main;
        P10.OSE = P11.OSW = PJOS1;
		if(PASigL34.R || PASigL34.L || P10.OSE && !PARelease)
			PJSwL1 = true;
    }

    if(PASw33.NI && PASw35.RI && PASw37.RI)
    {
    	P20.NxtE = &P50;			//P20 to P50 (Direction change)
        P50.NxtE = &P20;
		P20.RtE = Diverging;
        P50.RtE = Restricting;
        P20.OSE = P50.OSE = PJOS2 || PJOS1;
        if(PASigL32.R || PASigL34.L || P20.OSE && !PARelease)
			PJSwL1 = PJSwL2 = true;
	}

    else if(PASw33.RI && PASw35.RI && PASw37.RI)
    {
    	P30.NxtE = &P50;			//P30 to P50 (Direction change)
        P50.NxtE = &P30;
        P30.RtE = P50.RtE = Main;
        P30.OSE = P50.OSE = PJOS2 || PJOS1;
        if(PASigL32.R || PASigL34.L || P30.OSE && !PARelease)
			 PJSwL1 = PJSwL2 = true;
    }

    if(PASw33.NI && PASw35.RI && PASw37.NI)
    {
    	P20.NxtE = &P11;			//P20 to P11
        P11.NxtW = &P20;
        P20.RtE = P11.RtW = Restricting;
        P20.OSE = P11.OSW = PJOS2 || PJOS1;
        if(PASigL32.R || PASigL34.L || P20.OSE && !PARelease)
			PJSwL1 = PJSwL2 = true;
    }

    else if(PASw33.RI && PASw35.RI && PASw37.NI)
    {
    	P30.NxtE = &P11;			//P30 to P11
        P11.NxtW = &P30;
        P30.RtE = Restricting;
        P11.RtW = Diverging;
        P30.OSE = P11.OSW = PJOS2 || PJOS1;
        if(PASigL32.R || PASigL34.L || P30.OSE && !PARelease)
			PJSwL1 = PJSwL2 = true;
    }

    if(PASw33.NI && PASw35.NI)
    {
		P20.NxtE = &P21;			//P20 to P21
        P21.NxtW = &P20;
        P20.RtE = Main;
        P21.RtW = Restricting;
        P20.OSE = P21.OSW = PJOS2;
        if(PASigL32.R || PASigL32.L || P20.OSE && !PARelease)
			PJSwL2 = true;
    }

    else if(PASw33.RI && PASw35.NI)
    {
    	P30.NxtE = &P21;			//P30 to P21
        P21.NxtW = &P30;
        P30.RtE = Diverging;
        P21.RtW = Restricting;
        P30.OSE = P21.OSW = PJOS2;
		if(PASigL32.R || PASigL32.L || P30.OSE && !PARelease)
			PJSwL2 = true;
	}

	PASw27.L = PASw29.L = PASw31.L = PASw35.L = PASw37.L = PJSwL1;
	PASw33.L = PASw35.L = PJSwL2;

//Fleeting

	Fleeting(PortFleetOn->Checked, &PASigL32);
    Fleeting(PortFleetOn->Checked, &PASigL34);

//Set Signals

	if(PASw37.RI)		//Direction change
	{
		EWsig(PASigL34.R, &PASigL34, &PA34RA, &V11, RegAspects);
		EWsig(PASigL34.R, &PASigL34, &PA34RB, &P60, RegAspects);
		EWsig(PASigL34.R, &PASigL34, &PA34RC, &P61, RegAspects);
		EWsig(PASigL34.R, &PASigL34, &PA34RD, &P10, RegAspects);
	}
	else				//No direction change
	{
		Esig(PASigL34.R, &PASigL34, &PA34RA, &V11, RegAspects);
		Esig(PASigL34.R, &PASigL34, &PA34RB, &P60, RegAspects);
		Esig(PASigL34.R, &PASigL34, &PA34RC, &P61, RegAspects);
		Esig(PASigL34.R, &PASigL34, &PA34RD, &P10, RegAspects);
	}

   	EWsig(PASigL34.L, &PASigL34, &PA34LA, &P50, RegAspects);
   	Wsig(PASigL34.L, &PASigL34, &PA34LB, &P11, RegAspects);

    SigInd(&PASigL34);

	if(PASw35.RI && PASw37.RI)	//Direction change
	{
		EWsig(PASigL32.R, &PASigL32, &PA32RA, &P20, RegAspects);
		EWsig(PASigL32.R, &PASigL32, &PA32RB, &P30, RegAspects);
	}
	else                        //No direction change
	{
		Esig(PASigL32.R, &PASigL32, &PA32RA, &P20, RegAspects);
		Esig(PASigL32.R, &PASigL32, &PA32RB, &P30, RegAspects);
	}
	Wsig(PASigL32.L, &PASigL32, &PA32L, &P21, RegAspects);
	SigInd(&PASigL32);

//South Jct Interlocking

//Clear routes and switch locks

	P30.RtW = P31.RtE = P40.RtE = P41.RtE = Nil;
    PBSw1.L = PBSw3.L = false;

//Switch-switch locks

	PBSw1.L = PBSw3.RI && !PBRelease;
    PBSw3.L = PBSw1.RI && !PBRelease;

//Crossing signal block P40

	if(P40.M && !PBE)
		PBW = true;
	if(P40.E && !PBW)
		PBE = true;
	if(!P40.M && !P40.E)
		PBW = PBE = false;
	PBXO = P40.E && PBE || P40.M && PBW;

//Set pointers, routes and switch locks in accordance with switch positions and
//OS occupancy

	if(PBSw1.NI && PBSw3.NI)
    {
		P30.NxtW = &P31;		//P30 to P31
		P31.NxtE = &P30;
		if(PASw33.RI && PASw35.RI && PASw37.RI)  //to keep train longer than P30 from speeding up under ATC
			P30.RtW = Main;
		else
			P30.RtW = Diverging;
		P31.RtE = Main;
        P30.OSW = P31.OSE = PBOS2;
		if(PBSigL4.R || PBSigL4.L || P30.OSW && !PBRelease)
        	PBSw1.L = PBSw3.L = true;
    }

	else if(PBSw1.NI && PBSw3.RI)
    {
    	P30.NxtW = &P41;		//P30 to P41
        P41.NxtE = &P30;
        P30.RtW = P41.RtE = Diverging;
        P30.OSW = P41.OSE = PBOS1 || PBOS2;
        if(PBSigL4.R || PBSigL2.L || P30.OSW && !PBRelease)
        	PBSw1.L = PBSw3.L = true;
    }

	if(PBSw1.RI && PBSw3.NI)
    {
    	P40.NxtE = &P31;		//P40 to P31 (Direction change)
        P31.NxtE = &P40;
        P40.RtE = P31.RtE = Diverging;
        P40.OSE = P31.OSE = PBOS1 || PBOS2;
        if(PBSigL2.R || PBSigL4.L || P40.OSE && !PBRelease)
        	PBSw1.L = PBSw3.L = true;
    }

 	else if(PBSw1.NI && PBSw3.NI)
    {
    	P40.NxtE = &P41;		//P40 to P41 (Direction change)
        P41.NxtE = &P40;
        P40.RtE = P41.RtE = Main;
        P40.OSE = P41.OSE = PBOS1;
        if(PBSigL2.R || PBSigL2.L || P40.OSE && !PBRelease)
        	PBSw1.L = PBSw3.L = true;
    }

//Fleeting

	Fleeting(PortFleetOn->Checked, &PBSigL2);
    Fleeting(PortFleetOn->Checked, &PBSigL4);

//Set signals

	Wsig(PBSigL4.R, &PBSigL4, &PB4R, &P30, RegAspects);
	if(PBSw1.RI && PBSw3.NI)	//Direction change
		EWsig(PBSigL4.L, &PBSigL4, &PB4L, &P31, RegAspects);
	else
		Esig(PBSigL4.L, &PBSigL4, &PB4L, &P31, RegAspects);
	SigInd(&PBSigL4);

	EWsig(PBSigL2.R, &PBSigL2, &PB2R, &P40, RegAspects);
	if(PBSw1.NI && PBSw3.NI)	//Direction change
		EWsig(PBSigL2.L, &PBSigL2, &PB2L, &P41, RegAspects);
	else
		Esig(PBSigL2.L, &PBSigL2, &PB2L, &P41, RegAspects);
	SigInd(&PBSigL2);

//Circus Jct Interlocking

//Clear routes and switch locks

	P42.RtW = P32.RtE = P41.RtW = P31.RtW = Nil;

    PBSw5.L = PBSw11.L = PBSw13.L = PBSw15.L = false;

//Switch-switch locks

	PBSw11.L = PBSw13.RI && !PBRelease;
    PBSw13.L = PBSw11.RI && !PBRelease;

//Set pointers, routes and switch locks in accordance with switch positions and
//OS occupancy

	if(PBSw11.NI && PBSw13.NI)
    {
    	P42.NxtW = &P41;		//P42 to P41 (Direction change)
        P41.NxtW = &P42;
        P42.RtW = P41.RtW = Main;
        P42.OSW = P41.OSW = PBOS3;
        if(PBSigL12.R || PBSigL12.L || P42.OSW && !PBRelease)
        	PBSw11.L = PBSw13.L = true;
    }

	else if(PBSw11.RI && PBSw13.NI)
    {
    	P42.NxtW = &P31;		//P42 to P31 (Direction change)
        P31.NxtW = &P42;
        P42.RtW = P31.RtW = Diverging;
        P42.OSW = P31.OSW = PBOS3 || PBOS4;
        if(PBSigL14.R || PBSigL12.L || P42.OSW && !PBRelease)
        	PBSw11.L = PBSw13.L = true;
    }

	if(PBSw11.NI && PBSw13.RI)
    {
    	P32.NxtE = &P41;		//P32 to P41
        P41.NxtW = &P32;
        P32.RtE = P41.RtW = Diverging;
        P32.OSE = P41.OSW = PBOS3 || PBOS4;
        if(PBSigL12.R || PBSigL14.L || P32.OSE && !PBRelease)
        	PBSw11.L = PBSw13.L = true;
    }

 	else if(PBSw11.NI && PBSw13.NI)
    {
    	P32.NxtE = &P31;		//P32 to P31
        P31.NxtW = &P32;
        P32.RtE = P31.RtW = Main;
        P32.OSE = P31.OSW = PBOS4;
        if(PBSigL14.R || PBSigL14.L || P32.OSE && !PBRelease)
        	PBSw11.L = PBSw13.L = true;
    }

//Fleeting

	Fleeting(PortFleetOn->Checked, &PBSigL12);
    Fleeting(PortFleetOn->Checked, &PBSigL14);

//Set signals

	if(PBSw11.RI && PBSw13.NI)
		WEsig(PBSigL14.R, &PBSigL14, &PB14R, &P31, RegAspects);
	else
		Wsig(PBSigL14.R, &PBSigL14, &PB14R, &P31, RegAspects);
	Esig(PBSigL14.L, &PBSigL14, &PB14L, &P32, RegAspects);
	SigInd(&PBSigL14);

	if(PBSw11.NI && PBSw13.RI)
		Wsig(PBSigL12.R, &PBSigL12, &PB12R, &P41, RegAspects);
	else
		WEsig(PBSigL12.R, &PBSigL12, &PB12R, &P41, RegAspects);
	WEsig(PBSigL12.L, &PBSigL12, &PB12L, &P42, RegAspects);
	SigInd(&PBSigL12);

//Hand-operated switches

	HandSwitch(130, 35, false, &PBSw5);
    HandSwitch(146, 33, true, &PBSw15);
    HandAdditional(150, 35, false, &PBSw15);

 //Block indications

 	BlkInd(&P1);
	BlkInd(&P2);
    BlkInd(&P3);
    BlkInd(&P4);
    BlkInd(&P5);
    BlkInd(&P6);
    BlkInd(&P7);
    BlkInd(&P10);
    BlkInd(&P11);
    BlkInd(&P20);
	BlkInd(&P30);
    BlkInd(&P31);
	BlkInd(&P32);
    BlkInd(&P40);
    BlkInd(&P41);
	BlkInd(&P50);

 //Automatic train control

	WStubATC(&P1, &PA4RB);
	WStubATC(&P2, &PA4RA);
	WStubATC(&P3, &PA6R);
	WStubATC(&P4, &PA8R);
	WStubATC(&P5, &PA10RB);
	WStubATC(&P6, &PA10RA);
    WStubATC(&P7, &PA12R);

	TC(&P10, &PA10L, &PA34RD);
	TC(&P20, &PA8L, &PA32RA);
	TC(&P11, &PA34LB, &L6RB);
	TC(&P30, &PB4R, &PA32RB);
	TC(&P31, &PB14R, &PB4L);
	if(P32.pLoco->ATC && !P32.Dir)
		P32.W = P32.M && !P32.E && !P32.OSE && !P32.NxtE->Blk;       //ATC rear stop westbound
	else
        P32.W = PBIn[2].bit.b5;
	TC(&P32, &S4LC, &PB14L);
	TC(&P50, &Y4RA, &PA34LA);
	TC(&P40, &PA4L, &PB2R);
    TC(&P41, &PB12R, &PB2L);

 //Train identification

	TrainID(&P1);
	TrainID(&P2);
	TrainID(&P3);
	TrainID(&P4);
	TrainID(&P5);
	TrainID(&P6);
	TrainID(&P7);
	TrainID(&V11);
	TrainID(&P60);
	TrainID(&P61);
	TrainID(&P62);
	TrainID(&P63);
	TrainID(&P10);
	TrainID(&P20);
	TrainID(&P30);
	TrainID(&P50);
	TrainID(&P11);
	TrainID(&P40);
	TrainID(&P31);
	TrainID(&P32);
	TrainID(&P41);

 //Update display

	Switch(105, 17, &PASw17, 2, 9);
	Switch(100, 19, &PASw15, 2, 11);
	Switch(101, 19, &PASw19, 2, 9);
	Switch(103, 21, &PASw19, 9, 7);
	DSSwitch(105, 23, &PASw21, &PASw23, 2, 10, 7, 9);
	Switch(110, 23, &PASw7, 2, 8);
	Switch(107, 25, &PASw23, 2, 10);
	DSSwitch(108, 25, &PASw5, &PASw7, 2, 8, 6, 11);
	Scissors(105, 28, &PASw3, &PASw9);
	Switch(104, 27, &PASw9, 2, 9);
	DSSwitch(106, 27, &PASw3, &PASw5, 2, 8, 6, 11);
	Switch(108, 27, &PASw11, 2, 9);
	DSSwitch(104, 29, &PASw1, &PASw3, 2, 8, 6, 11);
	Switch(106, 29, &PASw9, 9, 7);
	Switch(110, 29, &PASw13, 7, 10);

	Switch(119, 19, &PASw27, 7, 9);
	Switch(121, 21, &PASw29, 7, 9);
	Switch(123, 23, &PASw31, 2, 10);
	DSSwitch(125, 23, &PASw35, &PASw37, 2, 8, 6, 11);
	DSSwitch(123, 25, &PASw33, &PASw35, 2, 8, 6, 11);

	Switch(121, 34, &PBSw1, 2, 11);
	Switch(123, 32, &PBSw1, 2, 8);
	Switch(124, 32, &PBSw3, 2, 9);
	Switch(126, 34, &PBSw3, 2, 10);
	Switch(130, 34, &PBSw5, 2, 9);
	Switch(137, 32, &PBSw11, 2, 9);
	Switch(139, 34, &PBSw11, 2, 10);
	Switch(140, 34, &PBSw13, 2, 11);
	Switch(142, 32, &PBSw13, 2, 8);
	Switch(146, 34, &PBSw15A, 2, 11);
	Switch(150, 34, &PBSw15B, 2, 8);

	Tracker(90, 19, &P7, DBlk);
	Tracker(94, 21, &P6, DBlk);
	Tracker(90, 23, &P5, DBlk);
	Tracker(90, 25, &P4, DBlk);
	Tracker(90, 27, &P3, DBlk);
	Tracker(90, 29, &P2, DBlk);
	Tracker(94, 31, &P1, DBlk);

	Tracker(99, 19, &P7, OSE);
	Tracker(101, 21, &P6, OSE);
	Tracker(103, 23, &P5, OSE);
	Tracker(103, 25, &P4, OSE);
	Tracker(102, 27, &P3, OSE);
	Tracker(101, 29, &P2, OSE);
	Tracker(101, 31, &P1, OSE);

	Tracker(109, 19, &P60, Yd);
	Tracker(108, 21, &P61, Yd);
	Tracker(111, 27, &P62, Yd);
	Tracker(113, 29, &P63, Yd);

	Tracker(113, 17, &V11, Yd);
	Tracker(112, 23, &P10, DBlk);
	Tracker(112, 25, &P20, DBlk);
	Tracker(113, 34, &P40, DBlk);
	Tracker(117, 28, &P30, Blk);
	Tracker(117, 29, &P30, Blk);

	Tracker(116, 17, &V11, OSE);
	Tracker(117, 19, &P60, OSE);
	Tracker(119, 21, &P61, OSE);
	Tracker(120, 23, &P10, OSE);
	Tracker(120, 25, &P20, OSE);
	Tracker(120, 27, &P30, OSE);

	Tracker(138, 14, &P50, Blk);
	Tracker(129, 21, &P50, RDBlk);
	Tracker(129, 23, &P11, DBlk);
	Tracker(129, 25, &P21, DBlk);

	Tracker(120, 32, &P30, OSW);
	Tracker(120, 34, &P40, OSE);

	Tracker(128, 32, &P31, RDBlk);
	Tracker(128, 34, &P41, RDBlk);

	Tracker(136, 32, &P31, OSW);
	Tracker(136, 34, &P41, OSW);

	Tracker(144, 32, &P32, RDBlk);
	Tracker(144, 34, &P42, DBlk);

 //Signals

	SignalE(99, 20, &P7);
	SignalE(101, 22, &P6);
	SignalE(103, 24, &P5);
	SignalE(103, 26, &P4);
	SignalE(102, 28, &P3);
	SignalE(101, 30, &P2);
	SignalE(101, 32, &P1);

	SignalW(108, 16, &V10);
	SignalW(108, 18, &P60);
	SignalW(107, 20, &P61);
	SignalW(111, 22, &P10);
	SignalW(111, 24, &P20);
	SignalW(110, 26, &P62);
	SignalW(112, 28, &P63);
	SignalW(113, 30, &P64);
	SignalW(112, 33, &P40);

	SignalE(116, 18, &V11);
	SignalE(117, 20, &P60);
	SignalE(119, 22, &P61);
	SignalE(120, 24, &P10);
	SignalE(120, 26, &P20);
	SignalE(120, 28, &P30);

	SignalW(137, 13, &P50);
	SignalWE(128, 20, &P50);
	SignalW(128, 22, &P11);
	SignalW(128, 24, &P21);

	SignalEW(120, 33, &P30);
	SignalE(120, 35, &P40);

	SignalWE(127, 31, &P31);
	SignalWE(127, 33, &P41);

	SignalEW(136, 33, &P31);
	SignalEW(136, 35, &P41);

	SignalWE(143, 31, &P32);
	SignalW(143, 33, &P42);

 //Train ID display

	DisplayID(95, 19, &P7);
	DisplayID(95, 21, &P6);
	DisplayID(95, 23, &P5);
	DisplayID(95, 25, &P4);
	DisplayID(95, 27, &P3);
	DisplayID(95, 29, &P2);
	DisplayID(95, 31, &P1);

//	DisplayID(110, 19, &P60);
//	DisplayID(110, 21, &P61);
//	DisplayID(111, 27, &P62);
//	DisplayID(113, 29, &P63);

//	DisplayID(113, 17, &V11);
	DisplayID(113, 23, &P10);
	DisplayID(113, 25, &P20);
	DisplayID(114, 34, &P40);

	DisplayID(130, 21, &P50);
	DisplayID(130, 23, &P11);
	DisplayID(130, 25, &P21);

	EraseID(118, 30, &P30, 3);  //needed for diagonal track
	DisplayID(117, 30, &P30);

	DisplayID(132, 32, &P31);
	DisplayID(132, 34, &P41);

	DisplayID(151, 28, &P32);
	DisplayID(151, 34, &P42);

 //DCC circuit breakers

    CBLavin = CktBkr[34] && SFlash;
 	CBSouthport = CktBkr[33] && SFlash;
    CBParsons = (CktBkr[30] || CktBkr[37]) && SFlash;	//includes reverser P50
    CBSouthJct = (CktBkr[31] || CktBkr[35] || CktBkr[36]) && SFlash;	//includes reversers P31 & P41
	CBCircusJct = CktBkr[32] && SFlash;

}


//---------------------------------------------------------------------------
