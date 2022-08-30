//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ClivedenUnit.h"

void TPSRY::InitializeCliveden(void)
{
	C13.NxtW = &B21;
	C13.NxtE = &C23;
	C12.NxtW = &C13;
	C12.NxtE = &C11;
	C23.NxtW = &C13;
	C23.NxtE = &C22;
	C22.NxtW = &C23;
	C22.NxtE = &C21;
	C11.NxtW = &C12;
	C11.NxtE = &C10;

	ClivedenAborts = 0;

	C13.Dir = C12.Dir = true;

//Pointer setup for Cliveden and Cliff

	NaCf.USSCol[17].pFltL = &CFltL16;                               //Fleet
	NaCf.USSCol[18].pSw = &CSw15; NaCf.USSCol[18].pSigL = &CSigL14;     //Switch 15, signal 14
	NaCf.USSCol[19].pSw = &CSw13; NaCf.USSCol[19].pSigL = &CSigL12;     //Switch 13, signal 12
	NaCf.USSCol[20].pSw = &CSw11; NaCf.USSCol[20].pSigL = &CSigL10;    	//Switch 11, signal 10
	NaCf.USSCol[21].pSw = &CSw9;  NaCf.USSCol[21].pSigL = &CSigL8;		//Switch 9, Signal 8
	NaCf.USSCol[22].pSigL = &CSigL6;                                //Signal 6
	NaCf.USSCol[23].pSigL = &CSigL4;                                //Signal 4
	NaCf.USSCol[24].pSw = &CSw3; NaCf.USSCol[24].pSigL = &CSigL2;       //Switch 3, signal 2

//Lever setup for Cliveden and Cliff

	NaCf.USSCol[18].Long = NaCf.USSCol[20].Long = NaCf.USSCol[22].Long = NaCf.USSCol[24].Long = true;
	CFltL16.L = true;
	CSw15.Hand = CSw15.N = true; CSw15.pBlk = &C13;
	CSw13.N = true;
	CSigL14.CButton = CSigL14.N = true;
	CSw11.Hand = CSw11.N = true; CSw11.pBlk = &C23;
	CSigL12.CButton = CSigL12.N = true;
	CSw9.N = true;
	CSigL10.CButton = CSigL10.N = true;
	CSigL8.CButton = CSigL8.N = true;
	CSigL6.CButton = CSigL6.N = true;
	CSigL4.CButton = CSigL4.N = true;
	CSw3.Hand = CSw3.N = true; CSw3.pBlk = &C30;
	CSigL2.CButton = CSigL2.N = true;

//Switches

	CSw9.NI = CSw11.NI = CSw13.NI = CSw15.NI = true;

//Block IDs

	C13.BlkID = "C13";
	C12.BlkID = "C12";
	C23.BlkID = "C23";
	C11.BlkID = "C11";
	C22.BlkID = "C22";

//Loco pointers

	C13.pLoco = C12.pLoco = C23.pLoco = C11.pLoco = C22.pLoco = &DummyLoco;


	BkClState = Idle;    //for auto routing
}
//Cliveden service function-----------------------------------------------------

void TPSRY::Cliveden(void)
{
//Hand-operated switches

	HandSwitch(78, 11, true, &CSw15);
	HandSwitch(92, 11, true, &CSw11);

//Interlocking at Cliveden West

//Clear routes and set switch locks

	C13.RtE = C12.RtW = C23.RtW = Nil;

	CSw13.L = CSw9.L = false;

  //set pointers, routes and switch locks in accordance with switch positions and
//OS occupancy

	if(CSw13.NI)
	{
		C13.NxtE = &C23;		//C13 to C23
		C23.NxtW = &C13;
		C13.RtE = C23.RtW = Main;
		C13.OSE = C23.OSW = CVOS1;
		if(CSigL14.R || CSigL14.L || C13.OSE && OSSLock)
			CSw13.L = true;
	}

	if(CSw13.RI)
	{
		C13.NxtE = &C12;		//C13 to C12
		C12.NxtW = &C13;
		C13.RtE = C12.RtW = Diverging;
		C13.OSE = C12.OSW = CVOS1;
		if(CSigL14.R || CSigL14.L || C13.OSE && OSSLock)
			CSw13.L = true;
	}

//Set signals
//Note: Signal R & L markings are reversed on computer diagram to correspond with
//markings on Cliff tower panel

	Esig(CSigL14.R, &CSigL14, &C14R, &C13, RegAspects);

	Wsig(CSigL14.L, &CSigL14, &C14LA, &C12, RegAspects);
	Wsig(CSigL14.L, &CSigL14, &C14LB, &C23, RegAspects);

	SigInd(&CSigL14);

//Set signal lever locks

	CSigL14.LockR = C14R.Lock || C13.LvrW;
	CSigL14.LockL = (C14LA.Lock || C12.LvrE) && (C14LB.Lock || C23.LvrE);


//Interlocking at Cliveden East

//Clear routes

	C23.RtE = C12.RtE = C22.RtW = C11.RtW = Nil;

//set pointers, routes and switch locks in accordance with switch positions and
//OS occupancy

	if(CSw9.NI)
	{
		C23.NxtE = &C22;		//C23 to C22
     	C22.NxtW = &C23;
     	C23.RtE = C22.RtW = Main;
     	C23.OSE = C22.OSW = CVOS2;
     	if(CSigL10.R || CSigL10.L || C23.OSE && OSSLock)
     		CSw9.L = true;
	}

	if(CSw9.RI)
	{
    	C23.NxtE = &C11;		//C23 to C11
     	C11.NxtW = &C23;
     	C23.RtE = C11.RtW = Diverging;
     	C23.OSE = C11.OSW = CVOS2 || CVOS3;
     	if(CSigL10.R || CSigL12.L || C23.OSE && OSSLock)
     		CSw9.L = true;
	}

	if(CSw9.NI)
	{
		C12.NxtE = &C11;		//C12 to C11
		C11.NxtW = &C12;
		C12.RtE = C11.RtW = Main;
		C12.OSE = C11.OSW = CVOS3;
		if(CSigL12.R || CSigL12.L || C12.OSE && OSSLock)
			CSw9.L = true;
	}

//USS Columns for Cliveden and Cliff

	USSColumn(&NaCf.USSCol[18]);
	USSColumn(&NaCf.USSCol[19]);
	USSColumn(&NaCf.USSCol[20]);
	USSColumn(&NaCf.USSCol[21]);
	USSColumn(&NaCf.USSCol[22]);
	USSColumn(&NaCf.USSCol[23]);
	USSColumn(&NaCf.USSCol[24]);

//Fleeting for Cliveden and Cliff

	Fleeting(CFltL16.R, &CSigL12);
	Fleeting(CFltL16.R, &CSigL10);

	if(RBDispatcherAll->Checked)
	{
		CliffFleetOn->Visible = true;
		CliffLabel->Visible = true;
	}
	else
	{
	CliffFleetOn->Visible = false;
	CliffLabel->Visible = false;
	}

	Fleeting(CliffFleetOn->Checked, &CSigL2);
	Fleeting(CliffFleetOn->Checked, &CSigL4);
	Fleeting(CliffFleetOn->Checked, &CSigL6);
	Fleeting(CliffFleetOn->Checked, &CSigL8);


//Set signals

	Esig(CSigL12.R, &CSigL12, &C12R, &C12, RegAspects);
	Esig(CSigL10.R, &CSigL10, &C10R, &C23, RegAspects);

	Wsig(CSigL12.L, &CSigL12, &C12L, &C11, RegAspects);
	Wsig(CSigL10.L, &CSigL10, &C10L, &C22, RegAspects);

//Signal indications on Cliff panel

	SigInd(&CSigL12);
	SigInd(&CSigL10);

//Set signal lever locks

	CSigL12.LockR = C12R.Lock || C12.LvrW;
	CSigL12.LockL = C12L.Lock || C11.LvrE;
	CSigL10.LockR = C10R.Lock || C23.LvrW;
	CSigL10.LockL = C10L.Lock || C22.LvrE;

//Block indications

	BlkInd(&C12);
	BlkInd(&C13);
	BlkInd(&C22);
	BlkInd(&C23);

//Train control & identification
	TC(&C23, &C14LB, &C10R);
	TC(&C13, &C18L, &C14R);

//For short block C12 and ATC control

	if(C13.pLoco->ATC && C13.Dir)
		C12.Switch = C12.Dir && !C12.ClrE;    //Stops 14L from clearing into C12 if 12L not clear

	if(C11.Blk && C11.Dir && C11.pLoco->ATC && !C4L.Proceed && !C12.OSW)
		C11.E = C11.SDCC = true;          //Stops train short of signal if 4L not clear
	else
		C11.E = C11.SDCC = false;

	TrainID(&C13);
	TrainID(&C23);
	TrainID(&C12);
	TrainID(&C22);

//Update Nassau-Cliff image

//Switches

	Switch(78, 12, &CSw15, 2, 10);
	Switch(83, 12, &CSw13, 2, 9);
	Switch(92, 12, &CSw11, 2, 11);
	Switch(96, 12, &CSw9, 2, 9);
	Switch(98, 14, &CSw9, 2, 10);

//Blocks

	Tracker(73, 12, &C13, DBlk);
	XTracker(82, 12, &C13, OSE, &CVOS1);

	Tracker(87, 12, &C23, DBlk);
	Tracker(87, 14, &C12, DBlk);

	XTracker(95, 12, &C23, OSE, &CVOS2);
	XTracker(95, 14, &C12, OSE, &CVOS3);

	Tracker(100, 12, &C22, DBlk);

//Signals

	SignalW(72, 11, &C13);

	SignalE(82, 13, &C13);

	SignalW(86, 11, &C23);
	SignalW(86, 13, &C12);

	SignalE(95, 13, &C23);
	SignalE(95, 15, &C12);

	SignalW(99, 11, &C22);
	SignalW(99, 13, &C11);

//Train identification

	DisplayID(74, 12, &C13);

	DisplayID(88, 12, &C23);
	DisplayID(88, 14, &C12);

	DisplayID(101, 12, &C22);
	DisplayID(101, 14, &C11);

//Train count

	NumTrains = 0;
	if(C13.Blk)
		NumTrains++;
	if(C12.Blk || C11.Blk)
		NumTrains++;
	if(C10.Blk)
		NumTrains++;
	if(C30.Blk)
		NumTrains++;
	if(C20.Blk)
        NumTrains++;
	if(C21.Blk)
		NumTrains++;
	if(C40.Blk)
		NumTrains++;
	if(C41.Blk)
		NumTrains++;
	if(C42.Blk)
		NumTrains++;
	if(C43.Blk)
		NumTrains++;
	if(C44.Blk)
		NumTrains++;
	if(C50.Blk)
		NumTrains++;
	if(C51.Blk)
		NumTrains++;
	if(C52.Blk)
		NumTrains++;
	if(C53.Blk)
		NumTrains++;
	if(C54.Blk)
		NumTrains++;
	if(C22.Blk || C23.Blk)
		NumTrains++;
	if(NumTrains < 13)
	{
		NumberOfTrains->Caption = NumTrains;
		Full = false;
	}
	else
	{
		NumberOfTrains->Caption = "Full";
		Full = true;
	}

//Dispatcher control of Cliff

	if(!CSigL24.N || !CSigL22.N || !CSigL18.N || CFltL16.R ||
		!CSigL14.N || !CSigL12.N || !CSigL10.N || !CSigL8.N || !CSigL6.N ||
			 !CSigL4.N || !CSigL2.N || CSw21.UnlockReq || CSw19.UnlockReq ||
					CSw15.UnlockReq || CSw11.UnlockReq || CSw3.UnlockReq)
	{
 //		RBCliff->Enabled = false;
		RBDispatcherBkCl->Enabled = false;
		RBDispatcherAll->Enabled =false;
	}
	else
	{
//		RBCliff->Enabled = true;
		RBDispatcherBkCl->Enabled = true;
		RBDispatcherAll->Enabled = true;
	}

	if(CfEn != RBCliff->Enabled)          //message to remote dispatcher if change
	{
		MessageToRemDis("CfEn", BoolToStr(RBCliff->Enabled));
		CfEn = RBCliff->Enabled;
	}
	if(BkClEn != RBDispatcherBkCl->Enabled)
	{
		MessageToRemDis("BkClEn", BoolToStr(RBDispatcherBkCl->Enabled));
		BkClEn = RBDispatcherBkCl->Enabled;
	}
	if(AllEn != RBDispatcherAll->Enabled)
	{
		MessageToRemDis("AllEn", BoolToStr(RBDispatcherAll->Enabled));
		AllEn = RBDispatcherAll->Enabled;
	}

//Enable USS levers

	if(RBDispatcherBkCl->Checked || RBDispatcherAll->Checked)
	{
		NaCf.USSCol[13].Enabled = true;
		NaCf.USSCol[14].Enabled = true;
		NaCf.USSCol[15].Enabled = true;
		NaCf.USSCol[16].Enabled = true;
		NaCf.USSCol[17].Enabled = true;
		NaCf.USSCol[18].Enabled = true;
		NaCf.USSCol[19].Enabled = true;
		NaCf.USSCol[20].Enabled = true;
	}
	else
	{
		NaCf.USSCol[13].Enabled = false;
		NaCf.USSCol[14].Enabled = false;
		NaCf.USSCol[15].Enabled = false;
		NaCf.USSCol[16].Enabled = false;
		NaCf.USSCol[17].Enabled = false;
		NaCf.USSCol[18].Enabled = false;
		NaCf.USSCol[19].Enabled = false;
		NaCf.USSCol[20].Enabled = false;
	}
	if(RBDispatcherAll->Checked)
	{
		NaCf.USSCol[21].Enabled = true;
		NaCf.USSCol[22].Enabled = true;
		NaCf.USSCol[23].Enabled = true;
		NaCf.USSCol[24].Enabled = true;
	}
	else
	{
		NaCf.USSCol[21].Enabled = false;
		NaCf.USSCol[22].Enabled = false;
		NaCf.USSCol[23].Enabled = false;
		NaCf.USSCol[24].Enabled = false;
	}

//Auto routing Bank-Cliveden

	if(RBDispatcherBkCl->Checked || RBDispatcherAll->Checked)
		BkClRoutes->Visible = true;
	else
	{
		BkClRoutes->Visible = false;
		BkClOff->Checked = true;
	}

	C31Incl->Enabled = BkClOn->Checked && C31.M;
	if(C31Incl->Enabled != C31En)
	{
		MessageToRemDis("C31En", BoolToStr(C31Incl->Enabled));
		C31En = C31Incl->Enabled;
	}

	if(BkClOn->Checked)
	{
		LeverX = NaCf.XOrigin;
		LeverY = NaCf.YOrigin;

		bool C13Occupied = C13.OSW || C13.Blk || C13.OSE;

		if(BkClState == Idle && !C13Occupied && (B20.OSW || B20.Blk) && !C12.Blk &&
			!C12.OSE && !C11.Blk && !C11.OSE && !C11.AsstW)        //B20 is trigger for EBMain
		{
			BkClRoute = "EBMain";
			USSSigNormal(NaCf.USSCol[13].pCol);      //signal 24
			USSSigNormal(NaCf.USSCol[14].pCol);      //signal 22
			USSSigNormal(NaCf.USSCol[16].pCol);      //signal 18
			USSSigNormal(NaCf.USSCol[18].pCol);      //signal 14
			USSSigNormal(NaCf.USSCol[19].pCol);      //signal 12
			USSFltNormal(NaCf.USSCol[17].pCol); 	 //Fleet 16
			BkClState = Pause;
		}
		else if(BkClState == Idle && !C13Occupied &&   //C22 or C23 are triggers for WBMain
			(C23.Blk || C22.Blk) && !B11.Blk && !B11.OSW)
		{
			BkClRoute = "WBMain";
			USSSigNormal(NaCf.USSCol[13].pCol);      //signal 24
			USSSigNormal(NaCf.USSCol[14].pCol);      //signal 22
			USSSigNormal(NaCf.USSCol[16].pCol);      //signal 18
			USSSigNormal(NaCf.USSCol[18].pCol);      //signal 14
			if(CSw9.RI)
				USSSigNormal(NaCf.USSCol[19].pCol);  //signal 12
			USSSigNormal(NaCf.USSCol[20].pCol);      //signal 10
			USSFltNormal(NaCf.USSCol[17].pCol); 	 //Fleet 16
			BkClState = Pause;
		}
		else if(BkClState == Idle && !C13Occupied && !B11.Blk && ! B11.OSW &&
			!B21.Blk && !B21.OSE && !C12.Blk && !C12.OSE && !C11.Blk && !C11.OSE &&
				C31Incl->Checked && C31.M && C31W) //trigger for WBLocal
		{
			C31Incl->Checked = false;
			BkClRoute = "WBLocal";
			USSSigNormal(NaCf.USSCol[13].pCol);      //signal 24
			USSSigNormal(NaCf.USSCol[14].pCol);      //signal 22
			USSSigNormal(NaCf.USSCol[16].pCol);      //signal 18
			USSSigNormal(NaCf.USSCol[18].pCol);      //signal 14
			USSSigNormal(NaCf.USSCol[19].pCol);      //signal 12
			USSSigNormal(NaCf.USSCol[20].pCol);      //signal 10
			USSFltNormal(NaCf.USSCol[17].pCol); 	 //Fleet 16
			BkClState = Pause;
		}
		else if(BkClState == Pause)
		{
			BkClState = SigsNormal;
		}
		else if(BkClState == SigsNormal && BkClRoute == "EBMain")
		{
			USSSwNormal(NaCf.USSCol[14].pCol);   //Switch 23
			USSSwNormal(NaCf.USSCol[17].pCol);  //switch 17
			USSSwReverse(NaCf.USSCol[19].pCol);   //switch 13
			USSSwNormal(NaCf.USSCol[21].pCol);   //Switch 9
			BkClState = Setting;
		}
		else if(BkClState == SigsNormal && BkClRoute == "WBMain")
		{
			USSSwNormal(NaCf.USSCol[14].pCol);   //Switch 23
			USSSwReverse(NaCf.USSCol[17].pCol);  //switch 17
			USSSwNormal(NaCf.USSCol[19].pCol);   //switch 13
			USSSwNormal(NaCf.USSCol[21].pCol);   //Switch 9
			BkClState = Setting;
		}
		else if(BkClState == SigsNormal && BkClRoute == "WBLocal")
		{
			USSSwReverse(NaCf.USSCol[14].pCol);   //Switch 23
			USSSwNormal(NaCf.USSCol[17].pCol);  //switch 17
			USSSwNormal(NaCf.USSCol[19].pCol);   //switch 13
			USSSwReverse(NaCf.USSCol[21].pCol);  //Switch 9
			BkClState = Setting;
		}
		else if(BkClState == Setting && BkClRoute == "EBMain" &&
			CSw23.NI && CSw19.NI && CSw17.NI && CSw15.NI && CSw13.RI && CSw9.NI)
		{
			USSSigRight(NaCf.USSCol[13].pCol);   	//Signal 24L
			USSSigRight(NaCf.USSCol[16].pCol);    	//signal 18L
			USSSigRight(NaCf.USSCol[18].pCol); 		//signal 14L
			USSSigRight(NaCf.USSCol[19].pCol);   	//Signal 12L
			USSSigLeft(NaCf.USSCol[20].pCol);   	//Signal 10R
			BkClState = SetFleet;
		}
		else if(BkClState == Setting && BkClRoute == "WBMain" &&
			CSw23.NI && CSw21B.NI && CSw21A.NI && CSw17.RI && CSw15.NI &&
				CSw13.NI && CSw9.NI)
		{
			USSSigLeft(NaCf.USSCol[14].pCol);    	//Signal 22R
			USSSigLeft(NaCf.USSCol[16].pCol);    	//signal 18R
			USSSigLeft(NaCf.USSCol[18].pCol); 		//signal 14R
			USSSigLeft(NaCf.USSCol[20].pCol);   	//Signal 10R
			BkClState = SetFleet;
		}
		else if(BkClState == Setting && BkClRoute == "WBLocal" &&
			CSw23.RI && CSw19.NI && CSw17.NI && CSw15.NI && CSw13.NI && CSw9.RI)
		{
			USSSigLeft(NaCf.USSCol[13].pCol);   	//Signal 24R
			USSSigLeft(NaCf.USSCol[16].pCol);    	//signal 18R
			USSSigLeft(NaCf.USSCol[18].pCol); 		//signal 14R
			USSSigLeft(NaCf.USSCol[19].pCol);   	//Signal 12R
			BkClState = SigsCleared;
		}
		else if(BkClState == SetFleet)
		{
			USSFltReverse(NaCf.USSCol[17].pCol);    //Fleet 16
			BkClState = SigsCleared;
		}
		else if(BkClState == SigsCleared && BkClRoute == "EBMain" && C13Occupied)
		{

			BkClState = Running;
		}
		else if(BkClState == SigsCleared && BkClRoute == "WBMain" && C13Occupied)
		{
			BkClState = Running;
		}
		else if(BkClState == SigsCleared && BkClRoute == "WBLocal" &&
			(C13Occupied || B21.Blk || B21.OSW))
		{
			BkClState = Running;
		}
		else if(BkClState == Running && BkClRoute == "EBMain" &&
			!C13Occupied)
		{
			BkClState = Idle;
		}
		else if(BkClState == Running && BkClRoute == "WBMain" &&
			!C13Occupied)
		{
			BkClState = Idle;
		}
		else if(BkClState == Running && BkClRoute == "WBLocal" &&
			 !C13Occupied && !B21.Blk && !B21.OSW)
		{
			BkClState = Idle;
		}

		BCState = "BkClState: " +  GetRouteState(BkClState);
	}
	else
		BkClState = Idle;
}

//---------------------------------------------------------------------------
