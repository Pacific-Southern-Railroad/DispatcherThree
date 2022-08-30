//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "KrulishInOut.h"
//Includes new track arrangement at Krulish Jct.

void TPSRY::KrulishInOut(void)
{
	KOut[0].bit.b0 = K8R.Aspect[0];  //Eastbound signals
	KOut[0].bit.b1 = K8R.Aspect[1];
	KOut[0].bit.b2 = K8R.Aspect[2];
	KOut[0].bit.b3 = K4R.Aspect[0];
	KOut[0].bit.b4 = K4R.Aspect[1];
	KOut[0].bit.b5 = K4R.Aspect[2];
	KOut[0].bit.b6 = K2R.Aspect[0];
	KOut[0].bit.b7 = K2R.Aspect[1];

	KOut[1].bit.b0 = K2R.Aspect[2];
	KOut[1].bit.b1 = K2L.Aspect[0];   //Westbound signals
	KOut[1].bit.b2 = K2L.Aspect[1];
	KOut[1].bit.b3 = K2L.Aspect[2];
	KOut[1].bit.b4 = K8LA.Aspect[0];
	KOut[1].bit.b5 = K8LB.Aspect[0];
	KOut[1].bit.b6 = K8LB.Aspect[1];
	KOut[1].bit.b7 = K8LB.Aspect[2];

	KOut[2].bit.b0 = 0;
	KOut[2].bit.b1 = 0;
	KOut[2].bit.b2 = 0;
	KOut[2].bit.b3 = 0;
	KOut[2].bit.b4 = CBKrulishYard;
	KOut[2].bit.b5 = N10.Srel;		  //Stop relays
	KOut[2].bit.b6 = N20.Srel;
	KOut[2].bit.b7 = N11.Srel;

	SendPacket(KRULISH, &KrulishAborts, &KIn[0], &KOld[0], &KOut[0], 3, true);
		KRText = "Krulish\t" + OutText;

	if(Match)
	{
		KSw1.NI	= KIn[0].bit.b0;   //Switch positions
		KSw1.RI	= KIn[0].bit.b1;
		KSw3.NI	= KIn[0].bit.b2;
		KSw3.RI = KIn[0].bit.b3;
		KSw5.NI = KIn[0].bit.b4;
		KSw5.RI = KIn[0].bit.b5;
		KSw7.NI = KIn[0].bit.b6;
		KSw7.RI = KIn[0].bit.b7;

		// = KIn[1].bit.b0;
		// = KIn[1].bit.b1;
		N10.W 	= KIn[1].bit.b2;   //Detection
		N10.M 	= KIn[1].bit.b3;
		N10.E 	= KIn[1].bit.b4;
		N20.W 	= KIn[1].bit.b5;
		N20.M 	= KIn[1].bit.b6;
		N20.E 	= KIn[1].bit.b7;

		KOS1 	= KIn[2].bit.b0;
		KOS2 	= KIn[2].bit.b1;
		KOS3    = KIn[2].bit.b2;
		N11.W 	= KIn[2].bit.b3;
		N11.M 	= KIn[2].bit.b4;
		N11.E 	= KIn[2].bit.b5;
	}
}

//---------------------------------------------------------------------------
