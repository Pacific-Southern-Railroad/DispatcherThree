//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ClivedenInOut.h"

void TPSRY::ClivedenInOut(void)
{
#ifndef _SIMULATION

	CVOut[0].bit.b0 = C14R.Aspect[0];  //Cliveden West eastbound signal
	CVOut[0].bit.b1 = C14R.Aspect[1];
	CVOut[0].bit.b2 = C14R.Aspect[2];
	CVOut[0].bit.b3 = C14LA.Aspect[0];  //Westbound signals
	CVOut[0].bit.b4 = C14LA.Aspect[1];
	CVOut[0].bit.b5 = C14LA.Aspect[2];
	CVOut[0].bit.b6 = C14LB.Aspect[0];
	CVOut[0].bit.b7 = C14LB.Aspect[1];

	CVOut[1].bit.b0 = C14LB.Aspect[2];
	CVOut[1].bit.b1 = C12R.Aspect[0];	//Cliveden East eastbound signals
	CVOut[1].bit.b2 = C12R.Aspect[1];
	CVOut[1].bit.b3 = C12R.Aspect[2];
	CVOut[1].bit.b4 = C10R.Aspect[0];
	CVOut[1].bit.b5 = C10R.Aspect[1];
	CVOut[1].bit.b6 = C10R.Aspect[2];
//	CVOut[1].bit.b7 = 

	CVOut[2].bit.b0 = C12L.Aspect[0];   //Westbound signals
	CVOut[2].bit.b1 = C12L.Aspect[1];
	CVOut[2].bit.b2 = C12L.Aspect[2];
	CVOut[2].bit.b3 = C10L.Aspect[0];
	CVOut[2].bit.b4 = C10L.Aspect[1];
	CVOut[2].bit.b5 = C10L.Aspect[2];
	CVOut[2].bit.b6 = CSw11.Locked;   	//Cliveden unlock
	CVOut[2].bit.b7 = CSw13.NO;			//Switch outputs

	CVOut[3].bit.b0 = CSw13.RO;
	CVOut[3].bit.b1 = CSw9.NO;
 //	CVOut[3].bit.b2 = CSw9.RO;          //Bad transistor
	CVOut[3].bit.b3 = C13.Srel;			//Stop relays
	CVOut[3].bit.b4 = C23.Srel;
	CVOut[3].bit.b5 = C12.Srel;
    CVOut[3].bit.b6 = CSw9.RO;

  	SendPacket(CLIVEDEN, &ClivedenAborts, &CVIn[0], &CVOld[0], &CVOut[0], 4, true);
	CVText = "Cliveden " + OutText;

	if (Match)
	{
		CSw13.NI  = CVIn[0].bit.b2;     //Switch positions
		CSw13.RI  = CVIn[0].bit.b3;
		CSw11.NI  = CVIn[0].bit.b4;
		CSw11.RI  = CVIn[0].bit.b5;
		CSw9.NI  = CVIn[0].bit.b6;
		CSw9.RI  = CVIn[0].bit.b7;

		C13.W  = CVIn[1].bit.b0;			//Detection
		C13.M  = CVIn[1].bit.b1;
		C13.E  = CVIn[1].bit.b2;
		CVOS1  = CVIn[1].bit.b3;
		C12.W  = CVIn[1].bit.b4;
		C12.M  = CVIn[1].bit.b5;
		C23.W  = CVIn[1].bit.b6;
		C23.M  = CVIn[1].bit.b7;

		CVOS2  		= CVIn[2].bit.b0;
		CVOS3  		= CVIn[2].bit.b1;
		C22.M  		= CVIn[2].bit.b2;

		CktBkr[0]	= !CVIn[2].bit.b4;	//North: Green Mountain Station
		CktBkr[1]   = !CVIn[2].bit.b5;	//  "	 Sheffield A
		CktBkr[2]	= !CVIn[2].bit.b6;  //  "	 Green Mountain Yard
		CktBkr[3]   = !CVIn[2].bit.b7;	//  " 	 Hyde Junction

		CktBkr[4]	= !CVIn[3].bit.b0;  //  "    Hyde West
		CktBkr[5]	= !CVIn[3].bit.b1;  //  "    Hyde East
		CktBkr[6]	= !CVIn[3].bit.b2;  //  "    Southport Junction
		CktBkr[7]   = !CVIn[3].bit.b3;	//  "    Carlton
		CktBkr[38]  = !CVIn[3].bit.b4;  //  "    Sheffield B
   }
#endif
}
//---------------------------------------------------------------------------
