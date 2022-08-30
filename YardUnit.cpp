//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "YardUnit.h"

//Initialize Yard

int KaleLeft, KaleRight;
int KaleMaxTime;

int KaleState;
bool Y17N, Y17R, Y19N, Y19R, Y21N, Y21R, Y23N, Y23R;
bool Y25N, Y25R, Y27N, Y27R, Y29N, Y29R;

int EJLeft, EJRight;
int EJMaxTime;
int EJState;
bool Y7N, Y7R, Y9N, Y9R, Y11N, Y11R;

int CJLeft, CJRight;
int CJMaxTime;
int CJState;
bool Y1N, Y1R, Y3N, Y3R;

void TPSRY::InitializeYard(void)
{
	Y10.NxtW = &Y52;
	Y10.NxtE = &Y11;

	Y11.NxtW = &Y10;
	Y11.NxtE = &L10;

	Y20.NxtW = &Y51;
	Y20.NxtE = &Y21;

	Y21.NxtW = &Y20;
	Y21.NxtE = &L20;

	Y30.NxtW = &Y51;
	Y30.NxtE = &Y11;

	Y50.NxtW = &Y30;
	Y50.NxtE = &Y20;

	Y51.NxtW = &Y30;
	Y51.NxtE = &Y20;

	Y52.NxtW = &DummyBlock;
	Y52.NxtE = &Y10;

	Y53.NxtW = &DummyBlock;
	Y53.NxtE = &Y10;

	Y60.NxtW = &DummyBlock;
	Y60.NxtE = &Y10;

	Y70.NxtW = &Y81;

	Y70.NxtE = &Y11;

	Y81.NxtW = &Y70;
	Y81.NxtE = &Y87;

	Y82.NxtW = &Y70;
	Y82.NxtE = &Y87;

	Y83.NxtW = &Y70;
	Y83.NxtE = &Y87;

	Y84.NxtW = &Y70;
	Y84.NxtE = &Y87;

	Y87.NxtW = &Y81;

	Y87.NxtE = &Y11;

	YardAborts = KaleAborts = EJuncAborts = CornellAborts = YardSWAborts = 0;

	Y50.Dir = Y51.Dir = Y52.Dir = Y53.Dir = Y20.Dir = Y21.Dir = true;

   //Switches

	YSw1.NI = YSw3.NI = YSw7.NI = YSw9.NI = YSw11.NI = true;
	YSw1.N = YSw3.N = YSw7.N = YSw9.N = YSw11.N = true;
	YSw17.NI = YSw19.NI = YSw21.NI = YSw23.NI = YSw25.NI = YSw27.NI = YSw29.NI = YSw33.NI = true;
	YSw17.N = YSw19.N = YSw21.N = YSw23.N = YSw25.N = YSw27.N = YSw29.N = YSw33.N = true;

	Y81W = Y81E = true;

   //Signals

	YSigL2.N = YSigL4.N = YSigL8.N = YSigL10.N = true;
	YSigL22.N = YSigL24.N = YSigL26.N = YSigL34.N = true;
	YSigL40.N = YSigL42.N = true;

    //Block identifications

	Y10.BlkID = "Y10";
	Y20.BlkID = "Y20";
	Y11.BlkID = "Y11";
	Y21.BlkID = "Y21";
	Y30.BlkID = "Y30";
	Y50.BlkID = "Y50";
	Y51.BlkID = "Y51";
	Y52.BlkID = "Y52";
	Y53.BlkID = "Y53";
	Y60.BlkID = "Y60";
	Y70.BlkID = "Y70";
	Y81.BlkID = "Y81";
	Y82.BlkID = "Y82";
	Y83.BlkID = "Y83";
	Y84.BlkID = "Y84";
	Y87.BlkID = "Y87";

	//Loco pointers

	Y10.pLoco = Y20.pLoco = Y11.pLoco = Y21.pLoco = Y30.pLoco = &DummyLoco;
	Y50.pLoco = Y51.pLoco = Y52.pLoco = Y53.pLoco = Y60.pLoco = &DummyLoco;
	Y70.pLoco = Y81.pLoco = Y82.pLoco = Y83.pLoco = Y84.pLoco = &DummyLoco;
	Y87.pLoco = &DummyLoco;

}

//Yard service function---------------------------------------------------------

void TPSRY::Yard(void){

//Dispatcher control of Yard

	if(!YSigL2.N || !YSigL4.N || !YSigL8.N || !YSigL10.N ||
		!YSigL22.N || !YSigL24.N || !YSigL26.N || !YSigL34.N
			|| !WOS1Norm)
		RBYDispatcher->Enabled = false;
	else
		RBYDispatcher->Enabled = true;

//Cornell Junction Interlocking------------------------------------------------

//Clear routes and switch locks

	Y11.RtE = Y21.RtE = Nil;
	L10.RtW = L20.RtW = P50.RtW = Nil;

	YSw1.L = YSw3.L = false;

//Set pointers, routes and switch locks in accordance with switch positions and
//OS occupancy

	if(YSw3.NI)
   	{
   		Y11.NxtE = &L10;				//Y11 to L10
      	L10.NxtW = &Y11;
      	Y11.RtE = Restricting;
        L10.RtW = Main;
        Y11.OSE = L10.OSW = CJOS1;
        if(YSigL2.R || YSigL2.L || Y11.OSE && !YRelease)
	      	YSw3.L = true;
   	}

	else if(YSw1.NI && YSw3.RI)
   	{
   		Y11.NxtE = &L20;	 			//Y11 to L20
      	L20.NxtW = &Y11;
      	Y11.RtE = L20.RtW = Restricting;
        Y11.OSE = L20.OSW = CJOS1 || CJOS2;
      	if(YSigL4.R || YSigL2.L || Y11.OSE && !YRelease)
      		YSw1.L = YSw3.L = true;
   	}

   	else if(YSw1.RI && YSw3.RI)
   	{
   		Y11.NxtE = &P50;				//Y11 to P50
      	P50.NxtW = &Y11;
      	Y11.RtE = Restricting;
        P50.RtW = Diverging;
		Y11.OSE = P50.OSW = CJOS1 || CJOS2;
      	if(YSigL4.R || YSigL2.L || Y11.OSE && !YRelease)
			YSw1.L = YSw3.L = true;
  	}

   	if(YSw1.NI && YSw3.NI)
	{
   		Y21.NxtE = &L20;				//Y21 to L20
      	L20.NxtW = &Y21;
      	Y21.RtE = Main;
        L20.RtW = Restricting;
        Y21.OSE = L20.OSW = CJOS2;
      	if(YSigL4.R || YSigL4.L || Y21.OSE && !YRelease)
      		YSw1.L = YSw3.L = true;
   	}

   	else if(YSw1.RI && YSw3.NI)
	{
   		Y21.NxtE = &P50;				//Y21 to P50
      	P50.NxtW = &Y21;
		Y21.RtE = Diverging;
        P50.RtW = Restricting;
        Y21.OSE = P50.OSW = CJOS2;
      	if(YSigL4.R || YSigL4.L || Y21.OSE && !YRelease)
      		YSw1.L = YSw3.L = true;
	}

//Cornell Jct. NX

	if(RBYDispatcher->Checked)
	{
		CJLeft = NXBtn(130, 10, CJLeft, 1, &NXBtnY11E);
		CJLeft = NXBtn(130, 12, CJLeft, 2, &NXBtnY21E);

		CJRight = NXBtn(137, 10, CJRight, 1, &NXBtnL10W);
		CJRight = NXBtn(137, 12, CJRight, 2, &NXBtnL20W);
		CJRight = NXBtn(137, 14, CJRight, 3, &NXBtnP50W);

		if(CJMaxTime)                     //Clear single button after maxtime
		{
			CJMaxTime--;
			if(!CJMaxTime)
				CJLeft = CJRight = 0;
		}
		if((CJLeft || CJRight) && !CJMaxTime)
			CJMaxTime = 12;

		if(CJLeft && CJRight && CJState == 0) //find throws needed
		{
			if(CJLeft == 1 && CJRight == 1)			//Y11 - L10
			{
				Y3N = !YSw3.NI;
			}
			else if(CJLeft == 1 && CJRight == 2)    //Y11 - L20
			{
				Y3R = !YSw3.RI;
				Y1N = !YSw1.NI;
			}
			else if(CJLeft == 1 && CJRight == 3)      //Y11 - P50
			{
				Y3R = !YSw3.RI;
				Y1R = !YSw1.RI;
			}
			else if(CJLeft == 2 && CJRight == 2)     //Y21 - L20
			{
				Y3N = !YSw3.NI;
				Y1N = !YSw1.NI;
			}
			else if(CJLeft == 2 && CJRight == 3)     //Y21 - P50
			{
				Y3N = !YSw3.NI;
				Y1R = !YSw1.RI;
			}
			CJLeft = CJRight = CJMaxTime = 0;
			CJState = 1;
		}

		if(CJState == 2)
		{
			YSw1.NO = YSw1.RO = YSw3.NO = YSw3.RO = false;  //clear all outputs
			CJState = 1;                            //one cycle for recharge
		}

		else if(CJState == 1)
		{
			if(Y1N && !YSw1.L)
			{
				YSw1.N = YSw1.NO = true;
				YSw1.R = Y1N = false;
				CJState = 2;
			}
			else if(Y1R && ! YSw1.L)
			{
				YSw1.R = YSw1.RO = true;
				YSw1.N = Y1R = false;
				CJState = 2;
			}
			else if(Y3N && !YSw3.L)
			{
				YSw3.N = YSw3.NO = true;
				YSw3.R = Y3R = false;
				CJState = 2;
			}
			else if(Y3R && ! YSw3.L)
			{
				YSw3.R = YSw3.RO = true;
				YSw3.N = Y3R = false;
				CJState = 2;
			}
			else
				CJState = 0;
		}

	//Click signals

		ClickSignalE(130, 11, L, &YSigL2, &Y11);
		ClickSignalE(130, 13, L, &YSigL4, &Y21);

		ClickSignalW(137, 9, R, &YSigL2, &L10);
		ClickSignalW(137, 11, R, &YSigL4, &L20);
		ClickSignalW(137, 13, R, &YSigL4, &P50);
	}

//Fleeting

	Fleeting(YardFleetOn->Checked, &YSigL2);
	Fleeting(YardFleetOn->Checked, &YSigL4);

//Set signals

	Esig(YSigL2.L, &YSigL2, &Y2L, &Y11, RegAspects);
	Esig(YSigL4.L, &YSigL4, &Y4L, &Y21, RegAspects);

	Wsig(YSigL2.R, &YSigL2, &Y2R, &L10, RegAspects);
	Wsig(YSigL4.R, &YSigL4, &Y4RB, &L20, RegAspects);
	Wsig(YSigL4.R, &YSigL4, &Y4RA, &P50, RegAspects);

	SigInd(&YSigL2);
	SigInd(&YSigL4);

//East End Junction------------------------------------------------------------

//Clear routes and switch locks

	Y10.RtE = Y20.RtE = Y30.RtE = Y70.RtE = Nil;
	Y11.RtW = Y21.RtW = Nil;

	YSw7.L = YSw9.L = false;

//Set pointers, routes and switch locks in accordance with switch positions and
//OS occupancy

	if(YSw9.NI && YSw7.NI)
	{
		Y10.NxtE = &Y11;			//Y10 to Y11
		Y11.NxtW = &Y10;
		Y10.RtE = Restricting;
		Y11.RtW = Main;
		Y10.OSE = Y11.OSW = EJOS1;
		if(YSigL8.R || YSigL8.L || Y10.OSE && !YRelease)
			YSw7.L = YSw9.L = true;
	}

	else if(YSw11.RI && YSw9.RI && YSw7.NI)
	{
		Y30.NxtE = &Y11;			//Y30 to Y11
		Y11.NxtW = &Y30;
		Y11.RtW = Diverging;
		Y30.RtE = Restricting;
		Y30.OSE = Y11.OSW = EJOS1;
		if(YSigL8.R || YSigL8.L || Y30.OSE && !YRelease)
			YSw7.L = YSw9.L = true;
	}

	else if(YSw11.NI && YSw9.RI && YSw7.NI)
	{
		Y87.NxtE = &Y11;			//Y87 to Y11
		Y11.NxtW = &Y87;
		Y11.RtW = Y87.RtE = Restricting;
		Y87.OSE = Y11.OSW = EJOS1;
		if(YSigL8.R || YSigL8.L || Y87.OSE && !YRelease)
			YSw7.L = YSw9.L = true;
	}

	if(Y11.pLoco->ATC && Y11.RtW == Restricting)            //speed up Y11 westbound under ATC
		Y11.RtW = Diverging;

	if(YSw7.NI)
	{
		Y20.NxtE = &Y21;			//Y20 to Y21
		Y21.NxtW = &Y20;
		Y20.RtE = Main;
		Y21.RtW = Restricting;
		Y20.OSE = Y21.OSW = EJOS2;
		if(YSigL10.R || YSigL10.L || Y20.OSE && !YRelease)
			YSw7.L = true;
	}

	else if(YSw11.RI && YSw9.RI && YSw7.RI)
	{
		Y30.NxtE = &Y21;			//Y30 to Y21
		Y21.NxtW = &Y30;
		Y21.RtW = Y30.RtE = Restricting;
		Y30.OSE = Y21.OSW = EJOS1 || EJOS2;
		if(YSigL10.R || YSigL8.L || Y30.OSE && !YRelease)
			YSw7.L = YSw9.L = true;
	}

	else if(YSw11.NI && YSw9.RI && YSw7.RI)
	{
		Y87.NxtE = &Y21;				//Y87 to Y21
		Y21.NxtW = &Y87;
		Y21.RtW = Y87.RtE = Restricting;
		Y87.OSE = Y21.OSW = EJOS1 || EJOS2;
		if(YSigL10.R || YSigL8.L || Y87.OSE && !YRelease)
			YSw7.L = YSw9.L = true;
	}

	else if(YSw9.NI && YSw7.RI)
	{
		Y10.NxtE = &Y21;			//Y10 to Y21
		Y21.NxtW = &Y10;
		Y10.RtE = Y21.RtW = Restricting;
		Y10.OSE = Y21.OSW = EJOS1 || EJOS2;
		if(YSigL10.R || YSigL8.L || Y10.OSE && !YRelease)
			YSw7.L = YSw9.L = true;
	}

//East End Jct. NX

	if(RBYDispatcher->Checked)
	{
		EJLeft =  NXBtn(113, 6, EJLeft, 1, &NXBtnY30E);
		EJLeft =  NXBtn(114, 8, EJLeft, 2, &NXBtnY87E);
		EJLeft =  NXBtn(115, 10, EJLeft, 3, &NXBtnY10E);
		EJLeft =  NXBtn(115, 12, EJLeft, 4, &NXBtnY20E);

		EJRight = NXBtn(122, 10, EJRight, 1, &NXBtnY11W);
		EJRight = NXBtn(122, 12, EJRight, 2, &NXBtnY21W);

		if(EJMaxTime)                     //Clear single button after maxtime
		{
			EJMaxTime--;
			if(!EJMaxTime)
			   EJLeft = EJRight = 0;
		}
		if((EJLeft || EJRight) && !EJMaxTime)
			EJMaxTime = 12;

		if(EJLeft && EJRight && EJState == 0) //find throws needed
		{
			if (EJLeft == 1 && EJRight == 1)  // Y30 - Y11
			{
				Y7N = !YSw7.NI;
				Y9R = !YSw9.RI;
				Y11R = !YSw11.RI;
			}
			else if (EJLeft == 2 && EJRight == 1)   // Y87 - Y11
			{
				Y7N = !YSw7.NI;
				Y9R = !YSw9.RI;
				Y11N = !YSw11.NI;
			}
			else if (EJLeft == 3 && EJRight == 1)   // Y10 - Y11
			{
				Y7N = !YSw7.NI;
				Y9N = !YSw9.NI;
			}

			if (EJLeft == 1 && EJRight == 2)         // Y30 - Y21
			{
				Y7R = !YSw7.RI;
				Y9R = !YSw9.RI;
				Y11R = !YSw11.RI;
			}
			else if (EJLeft == 2 && EJRight == 2)   // Y87 - Y21
			{
				Y7R = !YSw7.RI;
				Y9R = !YSw9.RI;
				Y11N = !YSw11.NI;
			}
			else if (EJLeft == 3 && EJRight == 2)   // Y10 - Y21
			{
				Y7R = !YSw7.RI;
				Y9N = !YSw9.NI;
			}
			else if (EJLeft == 4 && EJRight == 2)   // Y20 - Y21
			{
				Y7N = !YSw7.NI;
			}
			EJLeft = EJRight = EJMaxTime = 0;
			EJState = 1;
		}

		if(EJState == 2)
		{
			YSw7.NO = YSw7.RO = false;  //Clear all outputs
			YSw9.NO = YSw9.RO = false;
			YSw11.NO = YSw11.RO = false;
			EJState = 1;       //1 cycle to recharge
		}

		else if(EJState == 1)       //throw switches
		{

			if(Y7N && !YSw7.L)                	//Switch 7 Normal
			{
				YSw7.N = YSw7.NO = true;
				YSw7.R = Y7N = false;
				EJState = 2;
			}
			else if(Y7R && !YSw7.L)           	//Switch 7 Reverse
			{
				YSw7.R = YSw7.RO = true;
				YSw7.N = Y7R = false;
				EJState = 2;
			}
			else if(Y9N && !YSw9.L)     	   	//Switch 9 Normal
			{
				YSw9.N = YSw9.NO = true;
				YSw9.R = Y9N = false;
				EJState = 2;
			}
			else if(Y9R && !YSw9.L)           	//Switch 9 Reverse
			{
				YSw9.R = YSw9.RO = true;
				YSw9.N = Y9R = false;
				EJState = 2;
			}
			else if(Y11N && !YSw11.L)           //Switch 11 Normal
			{
				YSw11.N = YSw11.NO = true;
				YSw11.R = Y11N = false;
				EJState = 2;
			}
			else if(Y11R && !YSw11.L)          	//Switch 11 Reverse
			{
				YSw11.R = YSw11.RO = true;
				YSw11.N = Y11R = false;
				EJState = 2;
			}
			else
				EJState = 0;
		}

	//Click signals

		ClickSignalE(113, 7, L, &YSigL8, &Y30);
		ClickSignalE(114, 9, L, &YSigL8, &Y87);
		ClickSignalE(115, 11, L, &YSigL8, &Y10);
		ClickSignalE(115, 13, L, &YSigL10, &Y20);

		ClickSignalW(122, 9, R, &YSigL8,  &Y11);
		ClickSignalW(122, 11, R, &YSigL10, &Y21);
	}

//Fleeting

	Fleeting(YardFleetOn->Checked, &YSigL8);
	Fleeting(YardFleetOn->Checked, &YSigL10);

//Set signals

	Esig(YSigL8.L, &YSigL8, &Y8LC, &Y30, RegAspects);
	Esig(YSigL8.L, &YSigL8, &Y8LB, &Y87, RegAspects);
	Esig(YSigL8.L, &YSigL8, &Y8LA, &Y10, RegAspects);
	Wsig(YSigL8.R, &YSigL8, &Y8R, &Y11, RegAspects);

    SigInd(&YSigL8);

    Esig(YSigL10.L, &YSigL10, &Y10L, &Y20, AdvAspects);	//Advance Approach aspect
    Wsig(YSigL10.R, &YSigL10, &Y10R, &Y21, RegAspects);

	SigInd(&YSigL10);

//Waterman Yard

	//Clear routes and switch locks

	Y70.RtE = Y81.RtW = Y81.RtE = Y82.RtW = Y82.RtE = Nil;
	Y83.RtW = Y83.RtE = Y84.RtW = Y84.RtE = Nil;
	Y87.RtW = Nil;

	YSw113.L = YSw134.L = false;

	//set pointers, routes and switch locks in accordance with switch positions and
	//OS occupancy

	if(Y81W)
	{
		Y70.NxtE = &Y81;			// Y70 - Y81
		Y81.NxtW = &Y70;
		Y70.RtE = Restricting;
		Y81.RtW = Diverging;
		Y70.OSE = Y81.OSW = WOS1;
		if(YSigL40.R || YSigL40.L || Y70.OSE && !YRelease)
			YSw113.L = true;
	}
	else if (Y82W)
	{
		Y70.NxtE = &Y82;			// Y70 - Y82
		Y82.NxtW = &Y70;
		Y70.RtE = Restricting;
		Y82.RtW = Diverging;
		Y70.OSE = Y82.OSW = WOS1;
		if(YSigL40.R || YSigL40.L || Y70.OSE && !YRelease)
			YSw113.L = true;
	}
	else if (Y83W)
	{
		Y70.NxtE = &Y83;			// Y70 - Y83
		Y83.NxtW = &Y70;
		Y70.RtE = Restricting;
		Y83.RtW = Diverging;
		Y70.OSE = Y83.OSW = WOS1;
		if(YSigL40.R || YSigL40.L || Y70.OSE && !YRelease)
			YSw113.L = true;
	}
	else if (Y84W)
	{
		Y70.NxtE = &Y84;			// Y70 - Y84
		Y84.NxtW = &Y70;
		Y70.RtE = Restricting;
		Y84.RtW = Diverging;
		Y70.OSE = Y84.OSW = WOS1;
		if(YSigL40.R || YSigL40.L || Y70.OSE && !YRelease)
			YSw113.L = true;
	}

	if (Y81E)
	{
		Y87.NxtW = &Y81;			// Y81 - Y87
		Y81.NxtE = &Y87;
		Y87.RtW = Restricting;
		Y81.RtE = Restricting;
		Y81.OSE = Y87.OSW = WOS2;
		if(YSigL42.R || YSigL42.L || Y81.OSE && !YRelease)
			YSw134.L = true;
	}
	else if(Y82E)
	{
		Y87.NxtW = &Y82;			// Y82 - Y87
		Y82.NxtE = &Y87;
		Y87.RtW = Restricting;
		Y82.RtE = Restricting;
		Y82.OSE = Y87.OSW = WOS2;
		if(YSigL42.R || YSigL42.L || Y82.OSE && !YRelease)
			YSw134.L = true;
	}
	else if (Y83E)
	{
		Y87.NxtW = &Y83;			// Y83 - Y87
		Y83.NxtE = &Y87;
		Y87.RtW = Restricting;
		Y83.RtE = Restricting;
		Y83.OSE = Y87.OSW = WOS2;
		if(YSigL42.R || YSigL42.L || Y83.OSE && !YRelease)
			YSw134.L = true;
	}
	else if (Y84E)
	{
		Y87.NxtW = &Y84;			// Y84 - Y87
		Y84.NxtE = &Y87;
		Y87.RtW = Restricting;
		Y84.RtE = Restricting;
		Y84.OSE = Y87.OSW = WOS2;
		if(YSigL42.R || YSigL42.L || Y84.OSE && !YRelease)
			YSw134.L = true;
	}

	if(RBYDispatcher->Checked)
	{
	//Switch Buttons

		if(!YSw113.L)
		{
			SBY81W = SwitchButton(33, 29, &SBY81W);
			SBY82W = SwitchButton(33, 31, &SBY82W);
			SBY83W = SwitchButton(33, 33, &SBY83W);
			SBY84W = SwitchButton(33, 35, &SBY84W);
		}
		if(!YSw134.L)
		{
			SBY81E = SwitchButton(46, 29, &SBY81E);
			SBY82E = SwitchButton(46, 31, &SBY82E);
			SBY83E = SwitchButton(46, 33, &SBY83E);
			SBY84E = SwitchButton(46, 35, &SBY84E);
		}

	//ATC settings for short blocks Y70 and Y87

	Y87.Switch = !Y87.Dir && !Y87.RstrW;
	Y70.Switch = !Y70.Dir && !Y70.ClrW;

	//Signal clicks

		ClickSignalE(22, 30, R, &YSigL40, &Y70);

		ClickSignalW(33, 28, L, &YSigL40, &Y81);
		ClickSignalW(33, 30, L, &YSigL40, &Y82);
		ClickSignalW(33, 32, L, &YSigL40, &Y83);
		ClickSignalW(33, 34, L, &YSigL40, &Y84);

		ClickSignalE(46, 30, R, &YSigL42, &Y81);
		ClickSignalE(46, 32, R, &YSigL42, &Y82);
		ClickSignalE(46, 34, R, &YSigL42, &Y83);
		ClickSignalE(46, 36, R, &YSigL42, &Y84);

		ClickSignalW(56, 28, L, &YSigL42, &Y87);
	}

	//Waterman signal operation when under YARD control

	//Inbound route, 42L cleared by 8R
	if(RBYard->Checked && YSw11.NI && YSw9.RI && YSw7.NI)
		Wsig(YSigL8.R, &YSigL42, &Y42L,  &Y87, RegAspects);
	else
		Wsig(YSigL42.L, &YSigL42, &Y42L,  &Y87, RegAspects);

	//Outbound route, 40LA, B, C, or D cleared by 26LA
	if(RBYard->Checked && WOS1Norm && YSw27.RI && YSw25.NI &&
		YSw23.NI && YSw21.NI && YSw17.NI)

		Wsig(YSigL26.L, &YSigL40, &Y40LA, &Y81, RegAspects);
	else
		Wsig(YSigL40.L, &YSigL40, &Y40LA, &Y81, RegAspects);

	//set signals
	Esig(YSigL40.R, &YSigL40, &Y40R,  &Y70, RegAspects);

	Wsig(YSigL40.L, &YSigL40, &Y40LB, &Y82, RegAspects);
	Wsig(YSigL40.L, &YSigL40, &Y40LC, &Y83, RegAspects);
	Wsig(YSigL40.L, &YSigL40, &Y40LD, &Y84, RegAspects);

	Esig(YSigL42.R, &YSigL42, &Y42RA, &Y81, RegAspects);
	Esig(YSigL42.R, &YSigL42, &Y42RB, &Y82, RegAspects);
	Esig(YSigL42.R, &YSigL42, &Y42RC, &Y83, RegAspects);
	Esig(YSigL42.R, &YSigL42, &Y42RD, &Y84, RegAspects);

   //Derive switch positions from inputs

   if(Y81W)
   {
	   YSw113.NI = YSw115.NI = YSw116.NI = true;
	   YSw113.RI = YSw115.RI = YSw116.RI = false;
   }
   else if(Y82W)
   {
	   YSw113.NI = YSw115.RI = YSw116.RI = true;
	   YSw113.RI = YSw115.NI = YSw116.NI = false;
   }
   else if(Y83W)
   {
	   YSw113.NI = YSw115.RI = YSw116.NI = true;
	   YSw113.RI = YSw115.NI = YSw116.RI = false;
   }
   else if(Y84W)
   {
	   YSw113.RI = YSw115.NI = YSw116.NI = true;
	   YSw113.NI = YSw115.RI = YSw116.RI = false;
   }

   if(Y81E)
   {
	   YSw131.NI = YSw132.NI = YSw134.NI = true;
	   YSw131.RI = YSw132.RI = YSw134.RI = false;
   }
   else if(Y82E)
   {
	   YSw131.RI = YSw132.RI = YSw134.NI = true;
	   YSw131.NI = YSw132.NI = YSw134.RI = false;
   }
   else if(Y83E)
   {
	   YSw131.NI = YSw132.RI = YSw134.NI = true;
	   YSw131.RI = YSw132.NI = YSw134.RI = false;
   }
   else if(Y84E)
   {
	   YSw131.NI = YSw132.NI = YSw134.RI = true;
	   YSw131.RI = YSw132.RI = YSw134.NI = false;
   }

//Kale Interlocking-----------------------------------------------------------

//Clear routes and switch locks

	Y10.RtW = Y20.RtW = Nil;
	Y50.RtE = Y51.RtE = Y52.RtE = Y53.RtE = Nil;
	Y60.RtE = Y70.RtW = Nil;

	YSw17.L = YSw19.L = YSw21.L = YSw23.L = YSw25.L = YSw29.L = false;

//Switch-switch locks

	if(RBYard->Checked)
	{
		YSw17.L = (YSw19.NI || YSw21.RI || YSw23.RI) && !YRelease;
		YSw19.L = YSw17.RI && !YRelease;
		YSw21.L = (YSw17.RI || YSw23.RI) && !YRelease;
		YSw23.L = (YSw17.RI || YSw21.RI) && !YRelease;
	}

//set pointers, routes and switch locks in accordance with switch positions and
//OS occupancy

   	if(YSw17.NI && YSw21.NI && YSw23.NI && YSw25.NI && YSw27.NI)
	{
   		Y20.NxtW = &Y51;			//Y20 to Y51
      	Y51.NxtE = &Y20;
      	Y20.RtW = Y51.RtE = Restricting;
        Y51.OSE = Y20.OSW = KAOS4;
      	if(YSigL26.L || YSigL26.R || Y51.OSE && !YRelease)
	      	YSw17.L = YSw21.L = YSw23.L = YSw25.L = true;
   	}

	else if(YSw17.NI && YSw21.NI && YSw23.NI && YSw25.RI)
   	{
   		Y20.NxtW = &Y50;			//Y20 to Y50
      	Y50.NxtE = &Y20;
      	Y20.RtW = Y50.RtE = Restricting;
        Y50.OSE = Y20.OSW = KAOS4;
      	if(YSigL26.L || YSigL26.R || Y50.OSE && !YRelease)
      		YSw17.L = YSw21.L = YSw23.L = YSw25.L = true;
	}

	else if(YSw17.NI && YSw21.NI && YSw23.NI && YSw25.NI && YSw27.RI)
   	{
   		Y20.NxtW = &Y70;			//Y20 to Y70
		Y70.NxtW = &Y20;                                        //Reverse direction for Y70
		Y20.RtW = Restricting;
		Y70.RtW = Diverging;
		Y70.OSW = Y20.OSW = KAOS4;
		if(YSigL26.L || YSigL26.R || Y70.OSW && !YRelease)
	      	YSw17.L = YSw21.L = YSw23.L = YSw25.L = true;
    }

    else if(YSw17.NI && YSw21.NI && YSw23.RI && YSw29.NI)
    {
   		Y20.NxtW = &Y52;			//Y20 to Y52
      	Y52.NxtE = &Y20;
      	Y20.RtW = Y52.RtE = Restricting;
        Y52.OSE = Y20.OSW = KAOS3 || KAOS4;
      	if(YSigL24.L || YSigL26.R || Y52.OSE && !YRelease)
	      	YSw17.L = YSw21.L = YSw23.L = YSw29.L = true;
   	}

   	else if(YSw17.NI && YSw21.NI && YSw23.RI && YSw29.RI)
   	{
   		Y20.NxtW = &Y53;			//Y20 to Y53
      	Y53.NxtE = &Y20;
      	Y20.RtW = Y53.RtE = Restricting;
        Y53.OSE = Y20.OSW = KAOS3 || KAOS4;
      	if(YSigL24.L || YSigL26.R || Y53.OSE && !YRelease)
	      	YSw17.L = YSw21.L = YSw23.L = YSw29.L = true;
   	}

   	else if(YSw17.RI && YSw19.RI && YSw21.NI)
   	{
   		Y20.NxtW = &Y60;			//Y20 to Y60
      	Y60.NxtE = &Y20;
      	Y20.RtW = Y60.RtE = Restricting;
        Y60.OSE = Y20.OSW = KAOS2;
      	if(YSigL22.L || YSigL26.R || Y60.OSE && !YRelease)
      		YSw17.L = YSw19.L = YSw21.L = true;
   	}

   	if(YSw17.NI && YSw19.NI && YSw21.NI && YSw23.NI && YSw29.NI)
   	{
   		Y10.NxtW = &Y52;			//Y10 to Y52
      	Y52.NxtE = &Y10;
		Y10.RtW = Slow;              //semaphore
        Y52.RtE = Restricting;
        Y52.OSE = Y10.OSW = KAOS3 || KAOS2;
      	if(YSigL24.L || YSigL22.R || Y52.OSE && !YRelease)
      		YSw17.L = YSw19.L = YSw21.L = YSw23.L = YSw29.L = true;
   	}

   	else if(YSw17.NI && YSw21.RI && YSw23.NI && YSw25.RI)
   	{
   		Y10.NxtW = &Y50;				//Y10 to Y50
      	Y50.NxtE = &Y10;
		Y10.RtW = Slow;              //semaphore
      	Y50.RtE = Restricting;
        Y50.OSE = Y10.OSW = KAOS2 || KAOS4;
      	if(YSigL26.L || YSigL22.R || Y50.OSE && !YRelease)
      		YSw17.L = YSw21.L = YSw23.L = YSw25.L = true;
   	}

   	else if(YSw17.NI && YSw21.RI && YSw23.NI && YSw25.NI && YSw27.NI)
   	{
   		Y10.NxtW = &Y51;			//Y10 to Y51
      	Y51.NxtE = &Y10;
		Y10.RtW = Slow;             //semaphore
      	Y51.RtE = Restricting;
        Y51.OSE = Y10.OSW = KAOS2 || KAOS4;
      	if(YSigL26.L || YSigL22.R || Y51.OSE && !YRelease)
      		YSw17.L = YSw21.L = YSw23.L = YSw25.L = true;
   	}

	else if(YSw17.NI && YSw21.RI && YSw23.NI && YSw25.NI && YSw27.RI)
   	{
   		Y10.NxtW = &Y70;			//Y10 to Y70
		Y70.NxtW = &Y10;                               //Reverse direction for Y70
		Y10.RtW = Restricting;
		Y70.RtW = Restricting;
		Y70.OSW = Y10.OSW = KAOS2 || KAOS4;
		if(YSigL26.L || YSigL22.R || Y70.OSW && !YRelease)
      		YSw17.L = YSw21.L = YSw23.L = YSw25.L = true;
   	}

   	else if(YSw17.NI && YSw19.NI && YSw21.NI && YSw23.NI && YSw29.RI)
  	{
   		Y10.NxtW = &Y53;			//Y10 to Y53
		Y53.NxtE = &Y10;
		Y10.RtW = Slow;
		Y53.RtE = Restricting;
        Y53.OSE = Y10.OSW = KAOS3 || KAOS2;
      	if(YSigL24.L || YSigL22.R || Y53.OSE && !YRelease)
      		YSw17.L = YSw19.L = YSw21.L = YSw23.L = YSw29.L = true;
    }

    else if(YSw17.NI && YSw19.RI && YSw21.NI)
    {
   	 	Y10.NxtW = &Y60;			//Y10 to Y60
     	Y60.NxtE = &Y10;
      	Y10.RtW = Y60.RtE = Restricting;
        Y60.OSE = Y10.OSW = KAOS2;
      	if(YSigL22.L || YSigL22.R || Y60.OSE && !YRelease)
      		YSw17.L = YSw19.L = YSw21.L = true;
	}

//Kale interlocking NX

	if(RBYDispatcher->Checked)
	{
		KaleLeft = NXBtn( 96, 4, KaleLeft, 1, &NXBtnY60E);
		KaleLeft = NXBtn( 96, 6, KaleLeft, 2, &NXBtnY53E);
		KaleLeft = NXBtn( 96, 8, KaleLeft, 3, &NXBtnY52E);
		KaleLeft = NXBtn( 97, 10, KaleLeft, 4, &NXBtnY70W);
		KaleLeft = NXBtn( 97, 12, KaleLeft, 5, &NXBtnY51E);
		KaleLeft = NXBtn( 97, 14, KaleLeft, 6, &NXBtnY50E);

		KaleRight = NXBtn(107,  10, KaleRight, 1, &NXBtnY10W);
		KaleRight = NXBtn(107,  12, KaleRight, 2, &NXBtnY20W);

		if(KaleMaxTime)                     //Clear single button after maxtime
		{
			KaleMaxTime--;
			if(!KaleMaxTime)
				KaleLeft = KaleRight = 0;
		}
		if((KaleLeft || KaleRight) && !KaleMaxTime)
			KaleMaxTime = 12;

		if(KaleLeft && KaleRight && KaleState == 0) //find throws needed
		{
			if (KaleLeft == 1 && KaleRight == 1)         // Y60 - Y10
			{
				Y17N = !YSw17.NI;
				Y19R = !YSw19.RI;
				Y21N = !YSw21.NI;
			}
			else if (KaleLeft == 2 && KaleRight == 1)   // Y53 - Y10
			{
				Y17N = !YSw17.NI;
				Y19N = !YSw19.NI;
				Y21N = !YSw21.NI;
				Y23N = !YSw23.NI;
				Y29R = !YSw29.RI;
			}
			else if (KaleLeft == 3 && KaleRight == 1)   // Y52 - Y10
			{
				Y17N = !YSw17.NI;
				Y19N = !YSw19.NI;
				Y21N = !YSw21.NI;
				Y23N = !YSw23.NI;
				Y29N = !YSw29.NI;
			}
			else if (KaleLeft == 4 && KaleRight == 1)   //  Y70 - Y10
			{
				Y17N = !YSw17.NI;
				Y21R = !YSw21.RI;
				Y23N = !YSw23.NI;
				Y25N = !YSw25.NI;
				Y27R = !YSw27.RI;
			}
			else if (KaleLeft == 5 && KaleRight == 1)   // Y51 - Y10
			{
				Y17N = !YSw17.NI;
				Y21R = !YSw21.RI;
				Y23N = !YSw23.NI;
				Y25N = !YSw25.NI;
				Y27N = !YSw27.NI;
			}
			else if (KaleLeft == 6 && KaleRight == 1)   // Y50 - Y10
			{
				Y17N = !YSw17.NI;
				Y21R = !YSw21.RI;
				Y23N = !YSw23.NI;
				Y25R = !YSw25.RI;
			}

			if (KaleLeft == 1 && KaleRight == 2)         // Y60 - Y20
			{
				Y17R = !YSw17.RI;
				Y19R = !YSw19.RI;
				Y21N = !YSw21.NI;
			}
			else if (KaleLeft == 2 && KaleRight == 2)   // Y53 - Y20
			{
				Y17N = !YSw17.NI;
		//		Y19R = !YSw19.RI;
				Y21N = !YSw21.NI;
				Y23R = !YSw23.RI;
				Y29R = !YSw29.RI;
			}
			else if (KaleLeft == 3 && KaleRight == 2)   // Y52 - Y20
			{
				Y17N = !YSw17.NI;
		//		Y19R = !YSw19.RI;
				Y21N = !YSw21.NI;
				Y23R = !YSw23.RI;
				Y29N = !YSw29.NI;
			}
			else if (KaleLeft == 4 && KaleRight == 2)   // Y70 - Y20
			{
				Y17N = !YSw17.NI;
				Y21N = !YSw21.NI;
				Y23N = !YSw23.NI;
				Y25N = !YSw25.NI;
				Y27R = !YSw27.RI;
			}
			else if (KaleLeft == 5 && KaleRight == 2)   // Y51 - Y20
			{
				Y17N = !YSw17.NI;
				Y21N = !YSw21.NI;
				Y23N = !YSw23.NI;
				Y25N = !YSw25.NI;
				Y27N = !YSw27.NI;
			}
			else if (KaleLeft == 6 && KaleRight == 2)   // Y50 - Y20
			{
				Y17N = !YSw17.NI;
				Y21N = !YSw21.NI;
				Y23N = !YSw23.NI;
				Y25R = !YSw25.RI;
			}
			KaleLeft = KaleRight = KaleMaxTime = 0;
			KaleState = 1;
		}

		if(KaleState == 2)
		{
			YSw17.NO = YSw17.RO = YSw19.NO = YSw19.RO = false;  //Clear all outputs
			YSw21.NO = YSw21.RO = YSw23.NO = YSw23.RO = false;
			YSw25.NO = YSw25.RO = YSw27.NO = YSw27.RO = false;
			YSw29.NO = YSw29.RO = false;
			KaleState = 1;       //1 cycle to recharge
		}

		else if(KaleState == 1)       //throw switches
		{

			if(Y17N && !YSw17.L)                	//Switch 17 Normal
			{
				YSw17.N = YSw17.NO = true;
				YSw17.R = Y17N = false;
				KaleState = 2;
			}

			else if(Y17R && !YSw17.L)           	//Switch 17 Reverse
			{
				YSw17.R = YSw17.RO = true;
				YSw17.N = Y17R = false;
				KaleState = 2;
			}

			else if(Y19N && !YSw19.L)             	//Switch 19 Normal
			{
				YSw19.N = YSw19.NO = true;
				YSw19.R = Y19N = false;
				KaleState = 2;
			}

			else if(Y19R && !YSw19.L)           	//Switch 19 Reverse
			{
				YSw19.R = YSw19.RO = true;
				YSw19.N = Y19R = false;
				KaleState = 2;
			}

			else if(Y21N && !YSw21.L)             	//Switch 21 Normal
			{
				YSw21.N = YSw21.NO = true;
				YSw21.R = Y21N = false;
				KaleState = 2;
			}

			else if(Y21R && !YSw21.L)           	//Switch 21 Reverse
			{
				YSw21.R = YSw21.RO = true;
				YSw21.N = Y21R = false;
				KaleState = 2;
			}

			else if(Y23N && !YSw23.L)             	//Switch 23 Normal
			{
				YSw23.N = YSw23.NO = true;
				YSw23.R = Y23N = false;
				KaleState = 2;
			}

			else if(Y23R && !YSw23.L)           	//Switch 23 Reverse
			{
				YSw23.R = YSw23.RO = true;
				YSw23.N = Y23R = false;
				KaleState = 2;
			}

			else if(Y25N && !YSw25.L)             	//Switch 25 Normal
			{
				YSw25.N = YSw25.NO = true;
				YSw25.R = Y25N = false;
				KaleState = 2;
			}

			else if(Y25R && !YSw25.L)           	//Switch 25 Reverse
			{
				YSw25.R = YSw25.RO = true;
				YSw25.N = Y25R = false;
				KaleState = 2;
			}

			else if(Y27N && !YSw27.L)             	//Switch 27 Normal
			{
				YSw27.N = YSw27.NO = true;
				YSw27.R = Y27N = false;
				KaleState = 2;
			}

			else if(Y27R && !YSw27.L)           	//Switch 27 Reverse
			{
				YSw27.R = YSw27.RO = true;
				YSw27.N = Y27R = false;
				KaleState = 2;
			}

			else if(Y29N && !YSw29.L)             	//Switch 29 Normal
			{
				YSw29.N = YSw29.NO = true;
				YSw29.R = Y29N = false;
				KaleState = 2;
			}

			else if(Y29R && !YSw29.L)           	//Switch 29 Reverse
			{
				YSw29.R = YSw29.RO = true;
				YSw29.N = Y29R = false;
				KaleState = 2;
			}
			else
				KaleState = 0;
		}

		ClickSignalE(96, 5, L, &YSigL22, &Y60);
		ClickSignalE(96, 7, L, &YSigL24, &Y53);
		ClickSignalE(96, 9, L, &YSigL24, &Y52);
		ClickSignalW(97, 11, L, &YSigL26, &Y70);
		ClickSignalE(97, 13, L, &YSigL26, &Y51);
		ClickSignalE(97, 15, L, &YSigL26, &Y50);

		ClickSignalW(107, 9, R, &YSigL22, &Y10);
		ClickSignalW(107, 11, R, &YSigL26, &Y20);
	}

//Fleeting

    Fleeting(YardFleetOn->Checked, &YSigL26);

//Set Signals

	Esig(YSigL22.L, &YSigL22, &Y22L, &Y60, RegAspects);
	if(YSw17.NI && YSw21.NI && YSw23.NI && YSw25.NI && YSw27.RI)  //Reverse direction out of Y70
		WEsig(YSigL22.R, &YSigL22, &Y22R, &Y10, RegSloAspects);
	else
		Wsig(YSigL22.R, &YSigL22, &Y22R, &Y10, RegSloAspects);

    Y22Ra = Y22Rb = false;					//Semaphore Y22R
	if(Y22R.Aspect[0] && !Y22R.Aspect[1] && Y22R.Aspect[2])  //Approach
    	Y22Ra = true;
    if(Y22R.Aspect[0] && !Y22R.Aspect[1] && !Y22R.Aspect[2])  //Restricting
    	Y22Rb = true;

    SigInd(&YSigL22);

    Esig(YSigL24.L, &YSigL24, &Y24LA, &Y52, RegAspects);
    Esig(YSigL24.L, &YSigL24, &Y24LB, &Y53, RegAspects);

    SigInd(&YSigL24);

    Esig(YSigL26.L, &YSigL26, &Y26LA, &Y50, RegAspects);
    Esig(YSigL26.L, &YSigL26, &Y26LB, &Y51, RegAspects);
	WEsig(YSigL26.L, &YSigL26, &Y26LC, &Y70, RegAspects);     //Reverse direction out of Y70
	if(YSw17.NI && YSw21.NI && YSw23.NI && YSw25.NI && YSw27.RI)
		WEsig(YSigL26.R, &YSigL26, &Y26R, &Y20, RegAspects);
	else
		Wsig(YSigL26.R, &YSigL26, &Y26R, &Y20, RegAspects);

    SigInd(&YSigL26);

	Y20H = !Y20.M && !Y20.E && Y20.Dir;			//Outbound block semaphore signal
    Y20D = Y20H && Y20.ClrE;

//KALE West Interlocking

//Clear routes and switch lock

	Y50.RtW = Y51.RtW = Y30.RtW = Nil;

   	YSw33.L = false;

//Set pointers, routes and locks in accordance with switch and signal lever
//settings and OS occupancy

	if(YSw33.RI)
   	{
   		Y50.NxtW = &Y30;				//Y50 to Y30 (direction change)
      	Y30.NxtW = &Y50;
		Y30.RtW = Slow;
        Y50.RtW = Restricting;
        Y30.OSW = Y50.OSW = KAOS1;
        if(YSigL34.L || YSigL34.R || Y30.OSW && !YRelease)
      		YSw33.L = true;
   	}

   	if(YSw33.NI)
   	{
   		Y51.NxtW = &Y30;				//Y51 to Y30 (direction change)
      	Y30.NxtW = &Y51;
		Y30.RtW = Slow;
      	Y51.RtW = Restricting;
        Y30.OSW = Y51.OSW = KAOS1;
        if(YSigL34.L || YSigL34.R || Y30.OSW && !YRelease)
      		YSw33.L = true;
	}

//Kale West switch and signals

	if(RBYDispatcher->Checked)
	{
		SBY50W = SwitchButton(89, 14, &SBY50W);
		SBY51W = SwitchButton(89, 12, &SBY51W);

		if(SBY50W) {YSw33.R = true; YSw33.N = false;}
		if(SBY51W) {YSw33.N = true; YSw33.R = false;}

		ClickSignalW(85, 13, L, &YSigL34, &Y30);

		ClickSignalW(89, 11, R, &YSigL34, &Y51);
		ClickSignalW(89, 13, R, &YSigL34, &Y50);
	}

//Fleeting

	Fleeting(YardFleetOn->Checked, &YSigL34);

//Signals

	WEsig(YSigL34.R, &YSigL34, &Y34RA, &Y50, RegAspects);
    WEsig(YSigL34.R, &YSigL34, &Y34RB, &Y51, RegAspects);
    WEsig(YSigL34.L, &YSigL34, &Y34L, &Y30, RegAspects);

    SigInd(&YSigL34);

//Block indications

	BlkInd(&L10);
	BlkInd(&Y10);
	BlkInd(&Y20);
	BlkInd(&Y11);
	BlkInd(&Y21);
	BlkInd(&Y30);
	BlkInd(&Y50);
	BlkInd(&Y51);
	BlkInd(&Y52);
	BlkInd(&Y53);
	BlkInd(&Y70);
	BlkInd(&Y81);
	BlkInd(&Y82);
	BlkInd(&Y83);
	BlkInd(&Y84);
	BlkInd(&Y87);

//Automatic train control

	TC(&Y20, &Y26R, &Y10L);
	TC(&Y11, &Y8R, &Y2L);
	TC(&Y21, &Y10R, &Y4L);
	TC(&L10, &Y2R, &L8R);
	WRearATC(&Y30, &Y34L);
	ERearATC(&Y51, &Y26LB);
	ERearATC(&Y50, &Y26LA);
	WStubATC(&Y52, &Y24LA);
	WStubATC(&Y53, &Y24LB);
	WRearATC(&Y81, &Y40LA);
	WRearATC(&Y82, &Y40LB);
	WRearATC(&Y83, &Y40LC);
	WRearATC(&Y84, &Y40LD);

//Train identification

	TrainID(&Y70);
	TrainID(&Y81);
	TrainID(&Y82);
	TrainID(&Y83);
	TrainID(&Y84);
	TrainID(&Y87);

	TrainID(&Y30);
	TrainID(&Y53);
	TrainID(&Y52);
	TrainID(&Y51);
	TrainID(&Y50);

	TrainID(&Y10);
	TrainID(&Y20);

	TrainID(&Y11);
	TrainID(&Y21);

//Update display

//Switches

	Switch(86, 12, &YSw33, 2, 9);
	Switch(100, 12, &YSw27, 2, 10);
	Switch(101, 12, &YSw25, 2, 8);
	Switch(103, 12, &YSw23, 2, 10);
	Switch(104, 12, &YSw21, 2, 11);
	Switch(106, 12, &YSw17, 2, 10);

	Switch(99, 8, &YSw29, 9, 7);
	Switch(101, 10, &YSw23, 10, 7);
	DSSwitch(104, 10, &YSw19, &YSw17, 2, 10, 7, 0);
	Scissors(105, 11, &YSw21, &YSw17);
	Switch(106, 10, &YSw21, 2, 8);

	Switch(116, 8, &YSw11, 9, 7);
	Switch(118, 10, &YSw9, 2, 10);
	Switch(119, 10, &YSw7, 2, 9);
	Switch(121, 12, &YSw7, 2, 10);

	Switch(131, 10, &YSw3, 2, 9);
	Switch(133, 12, &YSw3, 2, 10);
	Switch(134, 12, &YSw1, 2, 9);

	Switch(23, 29, &YSw113, 2, 9);
	Switch(26, 29, &YSw115, 2, 9);
	Switch(28, 31, &YSw116, 7, 10);

	Switch(50, 31, &YSw131, 6, 11);
	Switch(52, 29, &YSw132, 2, 8);
	Switch(55, 29, &YSw134, 2, 8);

	//Blocks

	Tracker(14, 29, &Y70, DBlk);

	XTracker(22, 29, &Y70, OSE, &WOS1);

	Tracker(34, 29, &Y81, DBlk);
	Tracker(34, 31, &Y82, DBlk);
	Tracker(34, 33, &Y83, DBlk);
	Tracker(34, 35, &Y84, DBlk);

	XTracker(47, 29, &Y81, OSE, &WOS2);
	XTracker(47, 31, &Y82, OSE, &WOS2);
	XTracker(47, 33, &Y83, OSE, &WOS2);
	XTracker(47, 35, &Y84, OSE, &WOS2);

	Tracker(57, 29, &Y87, DBlk);

	Tracker(82, 3, &Y30, DBlk);
	Tracker(82, 4, &Y30, Blk);
	XTracker(85, 12, &Y30, OSW, &KAOS1);

	Tracker(86, 6, &Y53, DBlk);
	Tracker(86, 8, &Y52, DBlk);
	Tracker(94, 10, &Y70, Yd);
	Tracker(90, 12, &Y51, DBlk);
	Tracker(90, 14, &Y50, DBlk);

	XTracker(97, 4, &Y60, OSE, &KAOS2);
	XTracker(97, 6, &Y53, OSE, &KAOS3);
	XTracker(97, 8, &Y52, OSE, &KAOS3);
	XTracker(98, 10, &Y70, OSW, &KAOS4);
	XTracker(98, 12, &Y51, OSE, &KAOS4);
	XTracker(98,14, &Y50, OSE, &KAOS4);

	Tracker(111, 8, &Y87, DBlk);
	Tracker(108, 10, &Y10, DBlk);
	Tracker(108, 12, &Y20, DBlk);

	XTracker(114, 6, &Y30, OSE, &EJOS1);
	XTracker(115, 8, &Y87, OSE, &EJOS1);
	XTracker(116, 10, &Y10, OSE, &EJOS1);
	XTracker(116, 12, &Y20, OSE, &EJOS2);

	Tracker(123, 10, &Y11, DBlk);
	Tracker(123, 12, &Y21, DBlk);

	XTracker(131, 10, &Y11, OSE, &CJOS1);
	XTracker(131, 12, &Y21, OSE, &CJOS2);

	Tracker(138, 10, &L10, DBlk);
	Tracker(138, 12, &L20, DBlk);

//Signals

	SignalEW(85, 13, &Y30);

	SignalW(89, 11, &Y51);
	SignalW(89, 13, &Y50);

	SignalE(96, 5, &Y60);
	SignalE(96, 7, &Y53);
	SignalE(96, 9, &Y52);
	SignalEW(97, 11, &Y70);
	SignalE(97, 13, &Y51);
	SignalE(97, 15, &Y50);
	SignalW(107, 9, &Y10);
	SignalW(107, 11, &Y20);

	SignalE(113, 7, &Y30);
	SignalE(114, 9, &Y87);
	SignalE(115, 11, &Y10);
	SignalE(115, 13, &Y20);

	SignalW(122, 9, &Y11);
	SignalW(122, 11, &Y21);

	SignalE(130, 11, &Y11);
	SignalE(130, 13, &Y21);

	SignalW(137, 9, &L10);
	SignalW(137, 11, &L20);

	SignalE(22, 30, &Y70);

	SignalW(33, 28, &Y81);
	SignalW(33, 30, &Y82);
	SignalW(33, 32, &Y83);
	SignalW(33, 34, &Y84);

	SignalE(46, 30, &Y81);
	SignalE(46, 32, &Y82);
	SignalE(46, 34, &Y83);
	SignalE(46, 36, &Y84);

	SignalW(56, 28, &Y87);

	DisplayID(88, 2, &Y30);
	DisplayID(88, 6, &Y53);
	DisplayID(88, 8, &Y52);
	DisplayID(91, 12, &Y51);
	DisplayID(91, 14, &Y50);

	DisplayID(109, 10, &Y10);
	DisplayID(109, 12, &Y20);

	DisplayID(124, 10, &Y11);
	DisplayID(124, 12, &Y21);

	DisplayID(141, 10, &L10);
	DisplayID(141, 12, &L20);

	DisplayID(94, 10, &Y70);
	DisplayID(15, 29, &Y70);
	DisplayID(36, 29, &Y81);
	DisplayID(36, 31, &Y82);
	DisplayID(36, 33, &Y83);
	DisplayID(36, 35, &Y84);
	DisplayID(59, 29, &Y87);
	DisplayID(111, 8, &Y87);

//Circuit breakers

	CBKale = (CktBkr[10] || CktBkr[17]) && Flash; //includes reverser Y30
	CBWaterman = (CktBkr[11] || CktBkr[18]) && Flash;
	CBEngineYard = CktBkr[12] && Flash;
	CBEastEnd = CktBkr[13] && Flash;
	CBCornell = CktBkr[29] && Flash;
}

//---------------------------------------------------------------------------

