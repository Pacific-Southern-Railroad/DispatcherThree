//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DellUnit.h"
//Initialize Dell

void TPSRY::InitializeDell()
{
	D10.NxtW = &L11;
   	D20.NxtW = &L21;
   	H13.NxtW = &H12;
   	H23.NxtW = &H22;

   	H13.NxtE = &D11; D10.NxtE = &D11;
   	D20.NxtE = &D21; H23.NxtE = &D21;

   	D11.NxtW = &D10; D21.NxtW = &D20;
   	D11.NxtE = &S10; D21.NxtE = &S20;

   	S10.NxtW = &D11;

	DellAborts = 0;
   	FossAborts = 0;

   	D20.Dir = H23.Dir = D21.Dir = true;

//Pointer setup
	LaKr.USSCol[11].pSw = &DSw1; LaKr.USSCol[11].pFltL = &DFltL2;
	LaKr.USSCol[12].pSw = &DSw3; LaKr.USSCol[12].pSigL = &DSigL4;
	LaKr.USSCol[13].pSw = &DSw5; LaKr.USSCol[13].pSigL = &DSigL6;
	LaKr.USSCol[14].pSw = &DSw7; LaKr.USSCol[14].pFltL = &DFltL8;
	LaKr.USSCol[15].pSw = &DSw9; LaKr.USSCol[15].pSigL = &DSigL10;
	LaKr.USSCol[16].pSw = &DSw11; LaKr.USSCol[16].pSigL = &DSigL12;

//Lever setup

	LaKr.USSCol[12].Long = LaKr.USSCol[14].Long = LaKr.USSCol[16].Long = true;
	DSw1.N = DSw3.N = DSw5.N = DSw7.N = DSw11.N = true;
   	DFltL2.N = true;
	DSigL4.CButton = DSigL4.N = true;
	DSigL6.CButton = DSigL6.N = true;
   	DFltL8.N = true;
	DSw9.Hand = DSw9.N = true; DSw9.pBlk = &D21;
	DSigL10.CButton = DSigL10.N = true;
	DSigL12.CButton = DSigL12.N = true;

//Enable Columns

	LaKr.USSCol[11].Enabled = true;
	LaKr.USSCol[12].Enabled = true;
	LaKr.USSCol[13].Enabled = true;
	LaKr.USSCol[14].Enabled = true;
	LaKr.USSCol[15].Enabled = true;
	LaKr.USSCol[16].Enabled = true;

//Switch positions

	DSw1.NI = DSw3.NI = DSw5.NI = DSw7.NI = DSw9.NI = DSw11.NI = true;

//Block ID

	D10.BlkID = "D10";
	D11.BlkID = "D11";
	D20.BlkID = "D20";
	D21.BlkID = "D21";

//Loco pointers

	D10.pLoco = D11.pLoco = D20.pLoco = D21.pLoco = &DummyLoco;

//Auto routing

	DellEState = DellWState = Idle;
}

//Dell service function---------------------------------------------------------

void TPSRY::Dell(void)
{

//Hand-operated switch at Loland

	HandSwitch(63, 13, false, &DSw9);

//Crossing signal at Laporte

	if(DOS1 && !D1W)
   		D1E = true;
	if((D11.W || D11A) && !D1E)
     	D1W = true;
	if(!DOS1 && !(D11.W || D11A))
     	D1E = D1W = false;

	if(DOS2 && !D2W)
   		D2E = true;
	if((D21.W || D21A) && !D2E)
     	D2W = true;
	if(!DOS2 && !(D21.W || D21A))
     	D2E = D2W = false;

	DXO = D1E && DOS1 || D1W && (D11.W || D11A) ||
   		D2E && DOS2 || D2W && (D21.W || D21A);

//Interlocking at Valley Jct------------------------------------------------

//Fleet lever lock

	if(DSigL4.L || DSigL4.R || DSigL6.L || DSigL6.R || DFltL2.R)
   		DFltL2.L = false;
   	else
   		DFltL2.L = true;

//clear routes and switch locks

	H13.RtE = D10.RtE = D20.RtE = H23.RtE = Nil;
	D11.RtW = D21.RtW = Nil;

   	DSw1.L = DSw3.L = DSw5.L = DSw7.L = false;

//switch-switch locks

	DSw5.L = DSw7.R && OSSLockOn->Checked;
   	DSw7.L = DSw5.R && OSSLockOn->Checked;

//set pointers, routes and switch locks in accordance with switch positions and
//OS occupancy

	if (DSw1.NI && DSw5.NI && DSw7.NI)
   	{
		D10.NxtE = &D11;                 //D10 to D11
		D11.NxtW = &D10;
      	D10.RtE = Restricting;
      	D11.RtW = Main;
		D10.OSE = D11.OSW = DOS1;
      	if (DSigL6.R || DSigL6.L || D10.OSE && OSSLock)
			DSw1.L = DSw5.L = DSw7.L = true;
	}

	else if (DSw1.RI && DSw5.NI && DSw7.NI)
   	{
    	H13.NxtE = &D11;				//H13 to D11
	  	D11.NxtW = &H13;
      	H13.RtE = Restricting;
      	D11.RtW = Diverging;
      	H13.OSE = D11.OSW = DOS1;
      	if (DSigL6.R || DSigL6.L || H13.OSE && OSSLock)
			DSw1.L = DSw5.L = DSw7.L = true;
    }

	else if (DSw3.NI && DSw5.RI && DSw7.NI)
   	{
		D20.NxtE = &D11;                 //D20 to D11
		D11.NxtW = &D20;
      	D20.RtE = Diverging;
      	D11.RtW = Restricting;
      	D20.OSE = D11.OSW = DOS1 || DOS2;
      	if (DSigL4.R || DSigL6.L || D20.OSE && OSSLock)
      		DSw3.L = DSw5.L = DSw7.L = true;
	}

	else if (DSw3.RI && DSw5.RI && DSw7.NI)
   	{
		H23.NxtE = &D11;				//H23 to D11
		D11.NxtW = &H23;
    	H23.RtE = Diverging;
      	D11.RtW = Restricting;
      	H23.OSE = D11.OSW = DOS1 || DOS2;
      	if (DSigL4.R || DSigL6.L || H23.OSE && OSSLock)
      		DSw3.L = DSw5.L = DSw7.L = true;
	}

	if (DSw3.NI && DSw5.NI && DSw7.NI)
   	{
		D20.NxtE = &D21;				//D20 to D21
		D21.NxtW = &D20;
    	D20.RtE = Main;
      	D21.RtW = Restricting;
      	D20.OSE = D21.OSW = DOS2;
      	if (DSigL4.R || DSigL4.L || D20.OSE && OSSLock)
      		DSw3.L = DSw5.L = DSw7.L = true;
	}

	else if (DSw1.RI && DSw5.NI && DSw7.RI)
   	{
		H13.NxtE = &D21;						//H13 to D21
		D21.NxtW = &H13;
     	H13.RtE = Restricting;
     	D21.RtW = Diverging;
     	H13.OSE = D21.OSW = DOS1 || DOS2;
    	if (DSigL6.R || DSigL4.L || H13.OSE && OSSLock)
     		DSw1.L = DSw5.L = DSw7.L = true;
	}

	else if (DSw1.NI && DSw5.NI && DSw7.RI)
	{
		D10.NxtE = &D21;                 //D10 to D21
		D21.NxtW = &D10;
    	D10.RtE = Restricting;
      	D21.RtW = Diverging;
      	D10.OSE = D21.OSW = DOS1 || DOS2;
      	if (DSigL6.R || DSigL4.L || D10.OSE && OSSLock)
      		DSw1.L = DSw5.L = DSw7.L = true;
	}

	else if (DSw3.RI && DSw5.NI && DSw7.NI)
   	{
		H23.NxtE = &D21;						//H23 to D21
		D21.NxtW = &H23;
    	H23.RtE = Diverging;
      	D21.RtW = Restricting;
      	H23.OSE = D21.OSW = DOS2;
      	if (DSigL4.R || DSigL4.L || H23.OSE && OSSLock)
      		DSw3.L = DSw5.L = DSw7.L = true;
   	}

//Interlocking Columns

	USSColumn(&LaKr.USSCol[11]);
	USSColumn(&LaKr.USSCol[12]);
	USSColumn(&LaKr.USSCol[13]);
	USSColumn(&LaKr.USSCol[14]);

//Fleeting

	Fleeting(DFltL2.R, &DSigL4);
	Fleeting(DFltL2.R, &DSigL6);

	DSwOut = DSw1.Out || DSw3.Out || DSw5.Out || DSw7.Out;


//Set signals

	Esig(DSigL4.R, &DSigL4, &D4RA, &D20, RegAspects);
	Esig(DSigL4.R, &DSigL4, &D4RB, &H23, RegAspects);
	Wsig(DSigL4.L, &DSigL4, &D4L, &D21, RegAspects);

	Esig(DSigL6.R, &DSigL6, &D6RA, &H13, RegAspects);
    Esig(DSigL6.R, &DSigL6, &D6RB, &D10, RegAspects);
	Wsig(DSigL6.L, &DSigL6, &D6L, &D11, RegAspects);

//Set signal lever locks

	DSigL4.LockR = (D4RA.Lock || D20.LvrW) && (D4RB.Lock || H23.LvrW) || DSwOut;
	DSigL4.LockL = D4L.Lock || DSwOut || D21.LvrE;
	DSigL6.LockR = (D6RA.Lock || H13.LvrW) && (D6RB.Lock || D10.LvrW) || DSwOut;
	DSigL6.LockL = D6L.Lock || DSwOut || D11.LvrE;

//Interlocking at Mt. Foss--------------------------------------------------

//Fleet lever lock

	if(DSigL10.L || DSigL10.R || DSigL12.L || DSigL12.R || DFltL8.R)
   		DFltL8.L = false;
    else
   		DFltL8.L = true;

//Clear routes and switch locks

	D11.RtE = D21.RtE = Nil;
	S10.RtW = S20.RtW = Nil;

	DSw11.L = false;

//set pointers, routes and switch locks in accordance with switch positions and
//OS occupancy

	if (DSw11.NI)
    {
		D11.NxtE = &S10;				//D11 to S10
		S10.NxtW = &D11;
        D11.RtE = S10.RtW = Main;
		D11.OSE = S10.OSW = MFOS1;
   	    if(DSigL12.R || DSigL12.L || D11.OSE && OSSLock)
        	DSw11.L = true;

	    D21.NxtE = &S20;				//D21 to S20
		S20.NxtW = &D21;
   	    D21.RtE = S20.RtW = Main;
        D21.OSE = S20.OSW = MFOS2;
   		if(DSigL10.R || DSigL10.L || D21.OSE && OSSLock)
      		DSw11.L = true;
	}
    
	else if (DSw11.RI)
    {
		D21.NxtE = &S10;				//D21 to S10
		S10.NxtW = &D21;
    	D21.RtE = S10.RtW = Diverging;
        D21.OSE = S10.OSW = MFOS1 || MFOS2;
    	if(DSigL10.R || DSigL12.L || D21.OSE && OSSLock)
        	DSw11.L = true;
    }

 //USS Columns

	USSColumn(&LaKr.USSCol[15]);
    USSColumn(&LaKr.USSCol[16]);

//Fleeting

    Fleeting(DFltL8.R, &DSigL10);
    Fleeting(DFltL8.R, &DSigL12);


 //Set signals

	Esig(DSigL10.R, &DSigL10, &D10R, &D21, RegAspects);
   	Wsig(DSigL10.L, &DSigL10, &D10L, &S20, RegAspects);

	Esig(DSigL12.R, &DSigL12, &D12R, &D11, RegAspects);
 	Wsig(DSigL12.L, &DSigL12, &D12L, &S10, RegAspects);

//Set signal lever locks

	DSigL10.LockR = D10R.Lock || DSw11.Out || D21.LvrW;
	DSigL10.LockL = D10L.Lock || DSw11.Out || S20.LvrE;
	DSigL12.LockR = D12R.Lock || DSw11.Out || D11.LvrW;
	DSigL12.LockL = D12L.Lock || DSw11.Out || S10.LvrE;

   	BlkInd(&D20);
	BlkInd(&H23);
	BlkInd(&D11);
	BlkInd(&D21);
	BlkInd(&S10);

 //Train control & identification

	TC(&D20, &L14L, &D4RA);
	TC(&H23, &H10L, &D4RB);
	TC(&D11, &D6L, &D12R);
	TC(&D21, &D4L, &D10R);
    TC(&S10, &D12L, &S12R);

	TrainID(&D20);
    TrainID(&H23);
	TrainID(&D11);
	TrainID(&D21);
    TrainID(&S10);

//Update Latham-Krulish image

//Switches

   	Switch(49, 10, &DSw1, 2, 10);
    DSSwitch(49, 12, &DSw3, &DSw5, 2, 8, 6, 11);
	Switch(51, 10, &DSw5, 2, 8);
    Switch(52, 10, &DSw7, 2, 9);
   	Switch(54, 12, &DSw7, 2, 10);
	Switch(63, 12, &DSw9, 2, 8);
   	Switch(67, 12, &DSw11, 2, 11);
    Switch(69, 10, &DSw11, 2, 8);

	Switch(77, 10, &SSw1, 2, 10);

//Blocks

	Tracker(40, 8, &H13, DBlk);
	Tracker(36, 12, &D20, DBlk);
	Tracker(40, 14, &H23, DBlk);

	XTracker(46, 8, &H13, OSE, &DOS1);
	XTracker(46, 10, &D10, OSE, &DOS1);
	XTracker(46, 12, &D20, OSE, &DOS2);
	XTracker(46, 14, &H23, OSE, &DOS2);

	Tracker(56, 10, &D11, DBlk);
	Tracker(56, 12, &D21, DBlk);
	XTracker(66, 10, &D11, OSE, &MFOS1);
	XTracker(66, 12, &D21, OSE, &MFOS2);

	Tracker(71, 10, &S10, DBlk);

//Signals

 	SignalE(46, 9, &H13); //6RA
    SignalE(46, 13, &D20); //4RA
    SignalE(46, 15, &H23); //4RB

  	SignalW(55, 9, &D11); //6L
    SignalW(55, 11, &D21); //4L

  	SignalE(66, 11, &D11); //12R
    SignalE(66, 13, &D21); //10R

  	SignalW(70, 9, &S10); //12L

//Train identification

	DisplayID(41, 8, &H13);
	DisplayID(38, 12, &D20);
   	DisplayID(41, 14, &H23);
	DisplayID(58, 10, &D11);
	DisplayID(58, 12, &D21);

	DisplayID(73, 10, &S10);

//Auto routing at Dell

//State machine for Valley Jct. eastbound ---------------------------------------------------------------

	if(DSROn->Checked)	{

		if(DellEState == Idle && !D21.OSW && ((L21.Blk ||L21.OSW) && L21.ClrE ||
			(L31.Blk || L31.OSW) && L31.ClrE || D20.Blk))         //Train from Latham
		{
			DellERoute = "Latham";
			USSSigNormal(LaKr.USSCol[12].pCol);  //signal 4
			DellEState = SigsNormal;
		}
		else if(DellEState == Idle && !D21.OSW && H23.Blk)     //Train from Hyde
		{
			DellERoute = "Hyde";
			USSSigNormal(LaKr.USSCol[12].pCol);  //signal 4
			DellEState = SigsNormal;
		}
		else if(DellEState == SigsNormal && DellERoute == "Latham")
		{
			USSSwNormal(LaKr.USSCol[12].pCol);  //Switch 3 normal
			USSSwNormal(LaKr.USSCol[13].pCol);  //Switch 5 normal
			USSSwNormal(LaKr.USSCol[14].pCol);  //Switch 7 normal
			USSSwNormal(LaKr.USSCol[16].pCol);  //Switch 11 normal
			DellEState = Pause;
		}
		else if(DellEState == SigsNormal && DellERoute == "Hyde")
		{
			USSSwReverse(LaKr.USSCol[12].pCol);  //Switch 3 reverse
			USSSwNormal(LaKr.USSCol[13].pCol);  //Switch 5 normal
			USSSwNormal(LaKr.USSCol[14].pCol);  //Switch 7 normal
			USSSwNormal(LaKr.USSCol[16].pCol);  //Switch 11 normal
			DellEState = Pause;
		}

		else if(DellEState == Pause)
		{
			DellEState = Setting;
        }

		else if(DellEState == Setting && DellERoute == "Latham" &&
			DSw3.NI && DSw5.NI && DSw7.NI && DSw9.NI && DSw11.NI)
		{
			USSSigRight(LaKr.USSCol[12].pCol);  //Signal 4RA cleared
			DellEState = SigsCleared;
		}
		else if(DellEState == Setting && DellERoute == "Hyde" &&
			DSw3.RI && DSw5.NI && DSw7.NI && DSw9.NI && DSw11.NI)
		{
			USSSigRight(LaKr.USSCol[12].pCol);  //Signal 4RB cleared
			DellEState = SigsCleared;
		}
		else if(DellEState == SigsCleared && D21.OSW)
		{
			DellEState = Running;
		}
		else if(DellEState == Running && !D21.OSW)
			DellEState = Idle;

		DEState =  "DellEState: " + GetRouteState(DellEState);

	//State machine for Valley Jct. westbound

		if(DellWState == Idle && (S10.Blk || S10.OSE))     //S10 is the trigger
		{
			DellWRoute = GetDest(S10.Train, "Dell/ShoreW");
			if(DellWRoute == "None")
				DellWState = Idle;
			else
			{
				USSSigNormal(LaKr.USSCol[13].pCol); 	//Signal 6
                DellWState = SigsNormal;
			}
		}
		else if(DellWState == SigsNormal)
		{
			if(DellWRoute == "Latham")
			{
				USSSwNormal(LaKr.USSCol[13].pCol);  	//Switch 5
				USSSwNormal(LaKr.USSCol[14].pCol);  	//Switch 7
				USSSwNormal(LaKr.USSCol[16].pCol);  	//Switch 11
				USSSwNormal(LaKr.USSCol[11].pCol);    	//Switch 1 normal
				DellWState = Pause;
			}
			else if(DellWRoute == "Hyde")
			{
				USSSwNormal(LaKr.USSCol[13].pCol);  	//Switch 5
				USSSwNormal(LaKr.USSCol[14].pCol);  	//Switch 7
				USSSwNormal(LaKr.USSCol[16].pCol);  	//Switch 11
				USSSwReverse(LaKr.USSCol[11].pCol);    	//Switch 1 reverse
				DellWState = Pause;
			}
			else
            	DellWState = Idle;
		}

		else if(DellWState == Pause)
		{
			DellWState = Setting;
		}

		else if(DellWState == Setting && DellWRoute == "Latham" &&
			DSw1.NI && DSw5.NI && DSw7.NI && DSw11.NI) //if route set
		{
			USSSigLeft(LaKr.USSCol[13].pCol);           //Signal 6L cleared
			DellWState = SigsCleared;
		}
		else if(DellWState == Setting && DellWRoute == "Hyde" &&
			DSw1.RI && DSw5.NI && DSw7.NI && DSw11.NI) //if route set
		{
			USSSigLeft(LaKr.USSCol[13].pCol);           //Signal 6L cleared
			DellWState = SigsCleared;
		}
		else if(DellWState == SigsCleared && (D11.OSW))
		{
			DellWState = Running;                   //Train still in OS
		}
		else if(DellWState == Running && !D11.OSW)
		{
			DellWState = Idle;
		}

		DWState = "DellWState: " + GetRouteState(DellWState);
	}
	else
		DellEState = DellWState = Idle;

//Rocky Hill operations

	if(R10B && !RXW)							//Crossing signal
    {
   		RXE = true;
    }
    if(R10C && !RXE)
   	{
    	RXW = true;
    	R10.Dir = false;
    }
    if(!R10B && !R10C)
	   	RXE = RXW = false;

    RXO = R10B && RXE || R10C && RXW;

    BlkInd(&R10);

	Clear = !R10A && !R10.W;  //Block signal R10W
    NxtClr = R10.ClrW;
    NxtRte = Slow;
	SetBsig(&R10W, true, RegAspects);
}
//---------------------------------------------------------------------------


