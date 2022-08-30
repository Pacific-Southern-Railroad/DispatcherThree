//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "LathamInOut.h"

void TPSRY::LathamInOut()
{
#ifndef _SIMULATION

// Latham

	LOut[0].bit.b0 = LSw1.NO;   //Switch outputs
	LOut[0].bit.b1 = LSw1.RO;
//	LOut[0].bit.b2 = LSw3.NO;   //bad output, switched to 2/2
	LOut[0].bit.b3 = LSw3.RO;
	LOut[0].bit.b4 = LSw5.NO;
	LOut[0].bit.b5 = LSw5.RO;
	LOut[0].bit.b6 = LSw7.RO;
	LOut[0].bit.b7 = LSw7.NO;

	LOut[1].bit.b0 = LSw9.NO;
	LOut[1].bit.b1 = LSw9.RO;
	LOut[1].bit.b2 = L4R.Aspect[0];	//signals
	LOut[1].bit.b3 = L4R.Aspect[1];
	LOut[1].bit.b4 = L4R.Aspect[2];
	LOut[1].bit.b5 = L6RB.Aspect[0];
	LOut[1].bit.b6 = L6RA.Aspect[0];
	LOut[1].bit.b7 = L6RA.Aspect[1];

	LOut[2].bit.b0 = L6RA.Aspect[2];
	LOut[2].bit.b1 = L8R.Aspect[0];
	LOut[2].bit.b2 = LSw3.NO;
//	LOut[2].bit.b3 = ;
	LOut[2].bit.b4 = L4L.Aspect[0];
	LOut[2].bit.b5 = L6L.Aspect[0];
	LOut[2].bit.b6 = L6L.Aspect[1];
	LOut[2].bit.b7 = L6L.Aspect[2];

	LOut[3].bit.b0 = L8L.Aspect[0];
	LOut[3].bit.b1 = L8L.Aspect[1];
	LOut[3].bit.b2 = L8L.Aspect[2];
	LOut[3].bit.b3 = L10.Blk;     	//block indicators
	LOut[3].bit.b4 = L31.Blk;
	LOut[3].bit.b5 = P11.Blk;
	LOut[3].bit.b6 = L20.Srel;		//Stopping relays
	LOut[3].bit.b7 = P21.Srel;

	LOut[4].bit.b0 = L11.Srel;
	LOut[4].bit.b1 = L21.Srel;
	LOut[4].bit.b2 = P50.Srel;		//Temporary

	SendPacket(LATHAM, &LathamAborts, &LIn[0], &LOld[0], &LOut[0], 5, true);
	LAText = "Latham\t" + OutText;

	if(Match)
	{
		LSw1.NI = LIn[0].bit.b0;   //Switch positions
		LSw1.RI = LIn[0].bit.b1;
		LSw3.NI = LIn[0].bit.b2;
		LSw3.RI = LIn[0].bit.b3;
		LSw5.NI = LIn[0].bit.b4;
		LSw5.RI = LIn[0].bit.b5;
		LSw7.NI = LIn[0].bit.b6;
		LSw7.RI = LIn[0].bit.b7;

		LSw9.NI = LIn[1].bit.b0;
		LSw9.RI = LIn[1].bit.b1;
		L20.M	= LIn[1].bit.b2;  //Detection for Latham
		L20.E	= LIn[1].bit.b3;
		P21.M	= LIn[1].bit.b4;
		P21.E	= LIn[1].bit.b5;
		LOS1	= LIn[1].bit.b6;
		LOS2	= LIn[1].bit.b7;

		LOS3	= LIn[2].bit.b0;
		L11.W	= LIn[2].bit.b1;
		L11.M	= LIn[2].bit.b2;
		L21.W	= LIn[2].bit.b3;
		L21.M	= LIn[2].bit.b4;
		L21.E	= LIn[2].bit.b5;
		CktBkr[27] = !LIn[2].bit.b6;   //Cliveden
		CktBkr[28] = !LIn[2].bit.b7;	//Latham

		CktBkr[29] = !LIn[3].bit.b0;	//Cornell Jct.
		CktBkr[30] = !LIn[3].bit.b1;	//Parsons Jct.
		CktBkr[31] = !LIn[3].bit.b2;	//South Jct.
		CktBkr[32] = !LIn[3].bit.b3;   //Circus Jct.
		CktBkr[33] = !LIn[3].bit.b4;   //Southport
		CktBkr[34] = !LIn[3].bit.b5;   //Lavin Yard
		CktBkr[35] = !LIn[3].bit.b6;   //Reverser P31
		CktBkr[36] = !LIn[3].bit.b7;   //Reverser P41

		CktBkr[37] = !LIn[4].bit.b0;	//Reverser P50
		CktBkr[8] = !LIn[4].bit.b1;   //Reverser C22/C23
	}

// Carlton (includes Krulish West tracks and signals

	CAOut[0].bit.b0 = L16R.Aspect[0];       //signals
	CAOut[0].bit.b1 = L16R.Aspect[1];
	CAOut[0].bit.b2 = L16R.Aspect[2];
	CAOut[0].bit.b3 = L18R.Aspect[0];
	CAOut[0].bit.b4 = L14R.Aspect[0];
	CAOut[0].bit.b5 = L14R.Aspect[1];
	CAOut[0].bit.b6 = L14R.Aspect[2];
	CAOut[0].bit.b7 = L14L.Aspect[0];

	CAOut[1].bit.b0 = L18L.Aspect[0];
	CAOut[1].bit.b1 = L18L.Aspect[1];
	CAOut[1].bit.b2 = L18L.Aspect[2];
	CAOut[1].bit.b3 = !LSw11.Locked;		//Unlocks
	CAOut[1].bit.b4 = !LSw13.Locked;
	CAOut[1].bit.b5 = LSw15.NO;            	//Switch outputs
	CAOut[1].bit.b6 = LSw15.RO;
	CAOut[1].bit.b7 = LSw17.NO;

	CAOut[2].bit.b0 = LSw17.RO;
	CAOut[2].bit.b1 = L31.Srel;				//Carlton stop relays
	CAOut[2].bit.b2 = D10.Srel;
	CAOut[2].bit.b3 = S21E.Aspect[0];		//S21/N20 block signals
	CAOut[2].bit.b4 = S21E.Aspect[1];
	CAOut[2].bit.b5 = S21E.Aspect[2];
	CAOut[2].bit.b6 = N20W.Aspect[0];
	CAOut[2].bit.b7 = N20W.Aspect[1];

	CAOut[3].bit.b0 = N20W.Aspect[2];
	CAOut[3].bit.b1 = 0;
	CAOut[3].bit.b2 = 0;
	CAOut[3].bit.b3 = 0;
	CAOut[3].bit.b4 = S11E.Aspect[0];		//S11/N10 block signals
	CAOut[3].bit.b5 = S11E.Aspect[1];
	CAOut[3].bit.b6 = S11E.Aspect[2];
	CAOut[3].bit.b7 = N10W.Aspect[0];

	CAOut[4].bit.b0 = N10W.Aspect[1];
	CAOut[4].bit.b1 = N10W.Aspect[2];
	CAOut[4].bit.b2 = S21.Srel;				//Krulish West stopping relays
	CAOut[4].bit.b3 = N25.Srel;

	SendPacket(CARLTON, &CarltonAborts, &CAIn[0], &CAOld[0], &CAOut[0], 5, true);
		CAText = "Carlton\t" + OutText;

	if(Match)
	{
		LSw11.NI = CAIn[0].bit.b0;			//Carlton switch positions
		LSw11.RI = CAIn[0].bit.b1;
		LSw13.NI = CAIn[0].bit.b2;
		LSw13.RI = CAIn[0].bit.b3;
		LSw15.NI = CAIn[0].bit.b4;
		LSw15.RI = CAIn[0].bit.b5;
		LSw17.NI = CAIn[0].bit.b6;
		LSw17.RI = CAIn[0].bit.b7;

		L31.M	= CAIn[1].bit.b0;		  	//Carlton detection
		L31.E 	= CAIn[1].bit.b1;
		CAOS1 	= CAIn[1].bit.b2;
		CAOS2 	= CAIn[1].bit.b3;
		CAOS3 	= CAIn[1].bit.b4;
		D10.W 	= CAIn[1].bit.b5;
		D10.M 	= CAIn[1].bit.b6;

		S21.W 	= CAIn[2].bit.b0;		  	//Krulish West detection
		S21.M 	= CAIn[2].bit.b1;
		S21.E 	= CAIn[2].bit.b2;
		N25.W 	= CAIn[2].bit.b3;
		N25.M 	= CAIn[2].bit.b4;
		N25.E 	= CAIn[2].bit.b5;
	}
#endif
}
//---------------------------------------------------------------------------
