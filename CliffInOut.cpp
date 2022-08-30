//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CliffInOut.h"
//---------------------------------------------------------------------------

void TPSRY::CliffInOut(void)
{
//Green Mountain

	GMOut[0].bit.b0 = C2LB.Aspect[0];	//East end signals
	GMOut[0].bit.b1 = C2LB.Aspect[1];
	GMOut[0].bit.b2 = C2LB.Aspect[2];
	GMOut[0].bit.b3 = C2LD.Aspect[0];
	GMOut[0].bit.b4 = C2R.Aspect[0];
	GMOut[0].bit.b5 = C2R.Aspect[1];
	GMOut[0].bit.b6 = C2R.Aspect[2];
	GMOut[0].bit.b7 = C2LA.Aspect[0];

	GMOut[1].bit.b0 = C2LA.Aspect[1];
	GMOut[1].bit.b1 = C2LC.Aspect[0];
	GMOut[1].bit.b2 = C4RA.Aspect[0];	//West end signals
	GMOut[1].bit.b3 = C4RA.Aspect[1];
	GMOut[1].bit.b4 = C4RB.Aspect[0];
	GMOut[1].bit.b5 = C4RB.Aspect[1];
	GMOut[1].bit.b6 = C4RC.Aspect[0];
	GMOut[1].bit.b7 = C4RC.Aspect[1];

	GMOut[2].bit.b0 = C4RC.Aspect[2];
	GMOut[2].bit.b1 = C4RD.Aspect[0];
	GMOut[2].bit.b2 = C4L.Aspect[0];
	GMOut[2].bit.b3 = C4L.Aspect[1];
	GMOut[2].bit.b4 = C4L.Aspect[2];
	GMOut[2].bit.b5 = !CSw3.Locked;    //Unlock for switch 3

	SendPacket(GREENMTN, &GMAborts, &GMIn[0], &GMOld[0], &GMOut[0], 3, true);
		GMText = "GM\t" + OutText;

	if(Match)
	{
		C30E = GMIn[0].bit.b0;		//Route settings
		C10E = GMIn[0].bit.b1;
		G10E = GMIn[0].bit.b2;
		G12E = GMIn[0].bit.b3;
		C31W = GMIn[0].bit.b4;
		C30W = GMIn[0].bit.b5;
		C10W = GMIn[0].bit.b6;
		G21W = GMIn[0].bit.b7;

		CSw3.NI = GMIn[1].bit.b0;    //Switch 3
		CSw3.RI = GMIn[1].bit.b1;
		C11.M = GMIn[1].bit.b2;      //Detection
		COS1  = GMIn[1].bit.b3;
		C10.M = GMIn[1].bit.b4;
		C30.M = GMIn[1].bit.b5;
		C31.M = GMIn[1].bit.b6;
		COS2  = GMIn[1].bit.b7;

		C20.M = GMIn[2].bit.b0;
   }

//Cliff

	CFOut[0].bit.b0 = CSigL2.RI;	//Signal Indicators
	CFOut[0].bit.b1 = CSigL2.NI;
	CFOut[0].bit.b2 = CSigL2.LI;
	CFOut[0].bit.b3 = CSigL4.RI;
	CFOut[0].bit.b4 = CSigL4.NI;
	CFOut[0].bit.b5 = CSigL4.LI;
	CFOut[0].bit.b6 = CSigL6.RI;
	CFOut[0].bit.b7 = CSigL6.NI;

	CFOut[1].bit.b0 = CSigL6.LI;
	CFOut[1].bit.b1 = CSigL8.RI;
	CFOut[1].bit.b2 = CSigL8.NI;
	CFOut[1].bit.b3 = CSigL8.LI;
	CFOut[1].bit.b4 = CSigL10.RI; 	//Signal 10L at Cliff
	CFOut[1].bit.b5 = CSigL10.NI;
	CFOut[1].bit.b6 = CSigL10.LI;
	CFOut[1].bit.b7 = CSigL12.RI;	//Signal 12L at Cliff

	CFOut[2].bit.b0 = CSigL12.NI;
	CFOut[2].bit.b1 = CSigL12.LI;
	CFOut[2].bit.b2 = CSigL14.RI;	//Signal 14L at Cliff
	CFOut[2].bit.b3 = CSigL14.NI;
	CFOut[2].bit.b4 = CSigL14.LI;
	CFOut[2].bit.b5 = !CFltL16.R;	//Fleet indicator
	CFOut[2].bit.b6 = CFltL16.R;
	CFOut[2].bit.b7 = CSigL18.RI;	//Signal 18L at Cliff

	CFOut[3].bit.b0 = CSigL18.NI;
	CFOut[3].bit.b1 = CSigL18.LI;
	CFOut[3].bit.b2 = CSigL22.RI;	//Signal 22L at Cliff
	CFOut[3].bit.b3 = CSigL22.NI;
	CFOut[3].bit.b4 = CSigL22.LI;
	CFOut[3].bit.b5 = CSigL24.RI;	//Signal 24L at Cliff
	CFOut[3].bit.b6 = CSigL24.NI;
	CFOut[3].bit.b7 = CSigL24.LI;

	CFOut[4].bit.b0 = CSw3.Locked;     //Unlock Indicators
	CFOut[4].bit.b1 = !CSw3.Locked;
	CFOut[4].bit.b2 = CSw11.Locked;  //Switch 11 at Cliff
	CFOut[4].bit.b3 = !CSw11.Locked;
	CFOut[4].bit.b4 = CSw15.Locked;		//Switch 15 at Cliff
	CFOut[4].bit.b5 = !CSw15.Locked;
	CFOut[4].bit.b6 = CSw19.Locked;		//Switch 19 at Cliff
	CFOut[4].bit.b7 = !CSw19.Locked;

	CFOut[5].bit.b0 = CSw21.Locked;   	//Switch 21 at Cliff
	CFOut[5].bit.b1 = !CSw21.Locked;
	CFOut[5].bit.b2 = B10.Blk;		      //Block Indicator
	CFOut[5].bit.b3 = CBGreenMountain;  //DCC circuit breakers
	CFOut[5].bit.b4 = CBSheffield;
	CFOut[5].bit.b5 = CBCliveden;
	CFOut[5].bit.b6 = CBReverser;
	CFOut[5].bit.b7 = CBBank;

	CFOut[6].bit.b0 = CSw31.L;		//Switch locks
	CFOut[6].bit.b1 = CSw41.L;
	CFOut[6].bit.b2 = CSw43.L;
	CFOut[6].bit.b3 = CSw61.L;
	CFOut[6].bit.b4 = CSw9.L;
	CFOut[6].bit.b5 = CSw13.L;
	CFOut[6].bit.b6 = CSw17.L;
	CFOut[6].bit.b7 = CSw23.L;

	CFOut[7].bit.b0 = CSw21A.RI;		//Remote hand switch indications
	CFOut[7].bit.b1 = CSw21B.RI;
	CFOut[7].bit.b2 = CSw19.RI;
	CFOut[7].bit.b3 = CSw15.RI;
	CFOut[7].bit.b4 = CSw11.RI;
	CFOut[7].bit.b5 = CliffBell;

	SendPacket(CLIFF, &CFAborts, &CFIn[0], &CFOld[0], &CFOut[0], 8, true);
			CFText = "Cliff\t" + OutText;

	if(Match)
	{
		C21W = CFIn[0].bit.b0;    //Routes
		C40W = CFIn[0].bit.b1;
		C44W = CFIn[0].bit.b2;
		C43W = CFIn[0].bit.b3;
		C42W = CFIn[0].bit.b4;
		C41W = CFIn[0].bit.b5;
		C41E = CFIn[0].bit.b6;
		C42E = CFIn[0].bit.b7;

		C21E = CFIn[1].bit.b0;
		C40E = CFIn[1].bit.b1;
		C44E = CFIn[1].bit.b2;
		C43E = CFIn[1].bit.b3;
		COS3 = CFIn[1].bit.b4;        //Detection
		C21.M = CFIn[1].bit.b5;
		C40.M = CFIn[1].bit.b6;
		C41.M = CFIn[1].bit.b7;

		C42.M = CFIn[2].bit.b0;
		C43.M = CFIn[2].bit.b1;
		C44.M = CFIn[2].bit.b2;
		COS4 = CFIn[2].bit.b3;

		if(!RBDispatcherAll->Checked)
		{
			CSigL2.L = CFIn[2].bit.b4;			//Signal levers
			CSigL2.Callon = CFIn[2].bit.b5;
			CSigL2.R = CFIn[2].bit.b6;
			CSigL4.L = CFIn[2].bit.b7;

			CSigL4.Callon = CFIn[3].bit.b0;
			CSigL4.R = CFIn[3].bit.b1;
			CSigL6.L = CFIn[3].bit.b2;
			CSigL6.Callon = CFIn[3].bit.b3;
			CSigL6.R = CFIn[3].bit.b4;
			CSigL8.L = CFIn[3].bit.b5;
			CSigL8.Callon = CFIn[3].bit.b6;
			CSigL8.R = CFIn[3].bit.b7;
		}

		if(RBCliff->Checked)
        {

			CSigL10.L = CFIn[4].bit.b0;
			CSigL10.Callon = CFIn[4].bit.b1;
			CSigL10.R = CFIn[4].bit.b2;
			CSigL12.L = CFIn[4].bit.b3;
			CSigL12.Callon = CFIn[4].bit.b4;
			CSigL12.R = CFIn[4].bit.b5;
			CSigL14.L = CFIn[4].bit.b6;
			CSigL14.Callon = CFIn[4].bit.b7;

			CSigL14.R = CFIn[5].bit.b0;
			CFltL16.R = CFIn[5].bit.b1;				//Fleet
			CSigL18.L = CFIn[5].bit.b2;
			CSigL18.Callon = CFIn[5].bit.b3;
			CSigL18.R = CFIn[5].bit.b4;
			CSigL22.L = CFIn[5].bit.b5;
			CSigL22.Callon = CFIn[5].bit.b6;
			CSigL22.R = CFIn[5].bit.b7;

			CSigL24.L = CFIn[6].bit.b0;
			CSigL24.Callon = CFIn[6].bit.b1;
			CSigL24.R = CFIn[6].bit.b2;
		}

		CRelease = CFIn[6].bit.b3;

		CSigL2.N = !CSigL2.L && !CSigL2.R;
		CSigL4.N = !CSigL4.L && !CSigL4.R;
		CSigL6.N = !CSigL6.L && !CSigL6.R;
		CSigL8.N = !CSigL8.L && !CSigL8.R;

		if(RBCliff->Checked)
		{
			CSw3.UnlockReq = CFIn[6].bit.b4;
			CSw11.UnlockReq = CFIn[6].bit.b5;
			CSw15.UnlockReq = CFIn[6].bit.b6;
			CSw19.UnlockReq = CFIn[6].bit.b7;
			CSw21.UnlockReq = CFIn[7].bit.b0;

			CSw3.N = !CSw3.R;
			CSw11.N = !CSw11.R;
			CSw15.N = !CSw15.R;
			CSw19.N = !CSw19.R;
			CSw21.N = !CSw21.R;
		}
	}

//Sheffield

	SHOut[0].bit.b0 = SBC54E;  //Switch outputs Sheffield
	SHOut[0].bit.b1 = SBC53E;
	SHOut[0].bit.b2 = SBC52E;
	SHOut[0].bit.b3 = SBC51E;
	SHOut[0].bit.b4 = SBC50E;
	SHOut[0].bit.b5 = SBC21E;
	SHOut[0].bit.b6 = SBC40E;
	SHOut[0].bit.b7 = SBC41E;

	SHOut[1].bit.b0 = SBC42E;
	SHOut[1].bit.b1 = SBC43E;
	SHOut[1].bit.b2 = SBC44E;
	SHOut[1].bit.b3 = SBC54W;
	SHOut[1].bit.b4 = SBC53W;
	SHOut[1].bit.b5 = SBC52W;
	SHOut[1].bit.b6 = SBC51W;
	SHOut[1].bit.b7 = SBC50W;

	SHOut[2].bit.b0 = SBC21W;
	SHOut[2].bit.b1 = SBC40W;
	SHOut[2].bit.b2 = SBC41W;
	SHOut[2].bit.b3 = SBC42W;
	SHOut[2].bit.b4 = SBC43W;
	SHOut[2].bit.b5 = SBC44W;
	SHOut[2].bit.b6 = SBC30E;  //Switch outputs Green Mtn.
	SHOut[2].bit.b7 = SBC10E;

	SHOut[3].bit.b0 = SBG10E;
	SHOut[3].bit.b1 = SBG12E;
	SHOut[3].bit.b2 = SBC30W;
	SHOut[3].bit.b3 = SBC31W;
	SHOut[3].bit.b4 = SBC10W;
	SHOut[3].bit.b5 = SBG21W;
	SHOut[3].bit.b6 = 0;
	SHOut[3].bit.b7 = 0;

	SendPacket(SHEFFIELD, &SHAborts, &SHIn[0], &SHOld[0], &SHOut[0], 4, true);
			SFText = "Sheffield " + OutText;

	if(Match)
	{
		C50W = SHIn[0].bit.b0;   //Routes
		C51W = SHIn[0].bit.b1;
		C52W = SHIn[0].bit.b2;
		C53W = SHIn[0].bit.b3;
		C54W = SHIn[0].bit.b4;
		C50E = SHIn[0].bit.b5;
		C51E = SHIn[0].bit.b6;
		C52E = SHIn[0].bit.b7;

		C53E = SHIn[1].bit.b0;
		C54E = SHIn[1].bit.b1;
		C50.M = SHIn[1].bit.b2;        //Detection
		C51.M = SHIn[1].bit.b3;
		C52.M = SHIn[1].bit.b4;
		C53.M = SHIn[1].bit.b5;
		C54.M = SHIn[1].bit.b6;
	}
}
