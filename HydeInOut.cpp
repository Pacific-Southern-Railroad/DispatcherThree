//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "HydeInOut.h"

//Hyde

void TPSRY::HydeInOut(void)
{
	HOut[0].bit.b0 = HSw1.NO;			//Switch outputs
	HOut[0].bit.b1 = HSw1.RO;
	HOut[0].bit.b2 = HSw3.NO;
	HOut[0].bit.b3 = HSw3.RO;
	HOut[0].bit.b4 = HSw7.NO;
	HOut[0].bit.b5 = HSw7.RO;
	HOut[0].bit.b6 = HSw9.NO;
	HOut[0].bit.b7 = HSw9.RO;

	HOut[1].bit.b0 = HSw11.NO;
	HOut[1].bit.b1 = HSw11.RO;
	HOut[1].bit.b2 = HSw23.NO;
	HOut[1].bit.b3 = HSw23.RO;
	HOut[1].bit.b4 = HSw25.NO;
	HOut[1].bit.b5 = HSw25.RO;
	HOut[1].bit.b6 = HSw27.NO;
	HOut[1].bit.b7 = HSw27.RO;

	HOut[2].bit.b0 = HSw29.NO;
	HOut[2].bit.b1 = HSw29.RO;
	HOut[2].bit.b2 = HSw15.NO;
	HOut[2].bit.b3 = HSw15.RO;
	HOut[2].bit.b4 = HSw17.NO;
	HOut[2].bit.b5 = HSw17.RO;
	HOut[2].bit.b6 = HSw19.NO;
	HOut[2].bit.b7 = HSw19.RO;

	HOut[3].bit.b0 = HSw21.NO;
	HOut[3].bit.b1 = HSw21.RO;
	HOut[3].bit.b2 = H30.Blk;		//Block indicators
	HOut[3].bit.b3 = H10.Blk;
	HOut[3].bit.b4 = H23.Blk;
	HOut[3].bit.b5 = N25.Blk;
	HOut[3].bit.b6 = H21.Srel;		//Stopping relays
	HOut[3].bit.b7 = H13.Srel;

	HOut[4].bit.b0 = CBHydeJct;	//Circuit breakers
	HOut[4].bit.b1 = CBHydeWest;
	HOut[4].bit.b2 = CBHydeEast;
	HOut[4].bit.b3 = HydeWestPower;		//Power control
	HOut[4].bit.b4 = HydeEastPower;

	SendPacket(HYDE, &HydeAborts, &HIn[0], &HOld[0], &HOut[0], 5, true);
		HText = "Hyde \t" + OutText;

	if(Match)
	{
		H12W = HIn[0].bit.b0;	//Switch positions
		H34W = HIn[0].bit.b1;
		H33W = HIn[0].bit.b2;
		H30E = HIn[0].bit.b3;
		H31W = HIn[0].bit.b4;
		H32W = HIn[0].bit.b5;
		H22W = HIn[0].bit.b6;
		H43W = HIn[0].bit.b7;

		H42W = HIn[1].bit.b0;
		H41W = HIn[1].bit.b1;
		H41E = HIn[1].bit.b2;
		H42E = HIn[1].bit.b3;
		H43E = HIn[1].bit.b4;
		H22E = HIn[1].bit.b5;
		H40E = HIn[1].bit.b6;
		H12E = HIn[1].bit.b7;

		H34E = HIn[2].bit.b0;
		H33E = HIn[2].bit.b1;
		H32E = HIn[2].bit.b2;
		H31E = HIn[2].bit.b3;
		H21.M = HIn[2].bit.b4;		//Detection
		H21.E = HIn[2].bit.b5;
		HOS4  = HIn[2].bit.b6;
		HOS5  = HIn[2].bit.b7;

		HOS6  = HIn[3].bit.b0;
		H31.M = HIn[3].bit.b1;
		H32.M = HIn[3].bit.b2;
		H33.M = HIn[3].bit.b3;
		H34.M = HIn[3].bit.b4;
		H12.M = HIn[3].bit.b5;
		H22.M = HIn[3].bit.b6;
		H43.M = HIn[3].bit.b7;

		H42.M = HIn[4].bit.b0;
		H41.M = HIn[4].bit.b1;
		H40.M = HIn[4].bit.b2;
		HOS7  = HIn[4].bit.b3;
		HOS8  = HIn[4].bit.b4;
		H13.W = HIn[4].bit.b5;
		H13.M = HIn[4].bit.b6;
	}
}
//---------------------------------------------------------------------------
