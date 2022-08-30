//---------------------------------------------------------------------------
//Dell input output lists for Dell node and Foss node.
//7/8/07

#include <vcl.h>
#pragma hdrstop

#include "DellInOut.h"

void TPSRY::DellInOut(void)
{
#ifndef _SIMULATION

//Dell------------------------------------------------------------------------

	DOut[0].bit.b0 = D4RA.Aspect[0];  //Eastbound signals
	DOut[0].bit.b1 = D4RA.Aspect[1];
	DOut[0].bit.b2 = D4RA.Aspect[2];
	DOut[0].bit.b3 = D4RB.Aspect[0];
	DOut[0].bit.b4 = D4RB.Aspect[1];
	DOut[0].bit.b5 = D4RB.Aspect[2];
	DOut[0].bit.b6 = D6RA.Aspect[0];
	DOut[0].bit.b7 = D6RB.Aspect[0];

	DOut[1].bit.b0 = D4L.Aspect[0];	//Westbound signals
	DOut[1].bit.b1 = D4L.Aspect[1];
	DOut[1].bit.b2 = D4L.Aspect[2];
	DOut[1].bit.b3 = D6L.Aspect[0];
	DOut[1].bit.b4 = D6L.Aspect[1];
	DOut[1].bit.b5 = D6L.Aspect[2];
	DOut[1].bit.b6 = DXO;			//Laporte crossing signal
	DOut[1].bit.b7 = H13.Blk;       //Block indicators

	DOut[2].bit.b0 = D10.Blk;
	DOut[2].bit.b1 = S20.Blk;
	DOut[2].bit.b2 = !DSw9.Locked;	//unlock for switch 9
	DOut[2].bit.b3 = DSw1.NO;		//Switch outputs
	DOut[2].bit.b4 = DSw1.RO;
	DOut[2].bit.b5 = DSw3.NO;
	DOut[2].bit.b6 = DSw3.RO;
	DOut[2].bit.b7 = DSw5.NO;

	DOut[3].bit.b0 = DSw5.RO;
	DOut[3].bit.b1 = DSw7.NO;
	DOut[3].bit.b2 = DSw7.RO;
	DOut[3].bit.b3 = DSw11.NO;
	DOut[3].bit.b4 = DSw11.RO;
	DOut[3].bit.b5 = D20.Srel;		//Stop relays
	DOut[3].bit.b6 = H23.Srel;
	DOut[3].bit.b7 = D11.Srel;

	SendPacket(DELL, &DellAborts, &DIn[0], &DOld[0], &DOut[0], 5, true);
	DLText = "Dell\t" + OutText;

	if (Match)
	{
		DSw1.NI = DIn[0].bit.b0;		//Switch positions
		DSw1.RI = DIn[0].bit.b1;
		DSw3.NI = DIn[0].bit.b2;
		DSw3.RI = DIn[0].bit.b3;
		DSw5.NI = DIn[0].bit.b4;
		DSw5.RI = DIn[0].bit.b5;
		DSw7.NI = DIn[0].bit.b6;
		DSw7.RI = DIn[0].bit.b7;

		DSw9.NI	= DIn[1].bit.b0;
		DSw9.RI	= DIn[1].bit.b1;
		DSw11.NI	= DIn[1].bit.b2;
		DSw11.RI	= DIn[1].bit.b3;
		D20.M		= DIn[1].bit.b4;    //Detection
		D20.E 		= DIn[1].bit.b5;
		H23.M		= DIn[1].bit.b6;
		H23.E	 	= DIn[1].bit.b7;

		DOS1		= DIn[2].bit.b0;
		DOS2 		= DIn[2].bit.b1;
		D11.W	 	= DIn[2].bit.b2;
		D11A	 	= DIn[2].bit.b3;
		D11B		= DIn[2].bit.b4;
		D11.E		= DIn[2].bit.b5;

		D11.M = D11A || D11B;
	}

//Foss-----------------------------------------------------------------------

	MFOut[0].bit.b0 = D10R.Aspect[0];		//Eastbound signals
	MFOut[0].bit.b1 = D10R.Aspect[1];
	MFOut[0].bit.b2 = D10R.Aspect[2];
	MFOut[0].bit.b3 = D12R.Aspect[0];
	MFOut[0].bit.b4 = D12R.Aspect[1];
	MFOut[0].bit.b5 = D12R.Aspect[2];

	MFOut[1].bit.b0 = D10L.Aspect[0];		//Westbound signals
	MFOut[1].bit.b1 = D10L.Aspect[1];
	MFOut[1].bit.b2 = D10L.Aspect[2];
	MFOut[1].bit.b3 = D12L.Aspect[0];
	MFOut[1].bit.b4 = D12L.Aspect[1];
	MFOut[1].bit.b5 = D12L.Aspect[2];
	MFOut[1].bit.b6 = D21.Srel;				//Stopping relays
	MFOut[1].bit.b7 = S10.Srel;

//   	MFOut[2].bit.b0 =                   //Bad transistor
	MFOut[2].bit.b1 = R10.Srel;
	MFOut[2].bit.b2 = RXO;					//Rocky Hill crossing signal
	MFOut[2].bit.b3 = R10W.Aspect[0];       //Rocky Hill distant for Nassau
	MFOut[2].bit.b4 = R10W.Aspect[1];
	MFOut[2].bit.b5 = R10W.Aspect[2];

	SendPacket(FOSS, &FossAborts, &MFIn[0], &MFOld[0], &MFOut[0], 3, true);
	MFText = "Foss\t" + OutText;

	if(Match)
	{
		D21.W = MFIn[0].bit.b0;		//Foss detection
		D21A  = MFIn[0].bit.b1;
		D21B  = MFIn[0].bit.b2;
		D21.E = MFIn[0].bit.b3;
		MFOS1 = MFIn[0].bit.b4;
		MFOS2 = MFIn[0].bit.b5;
		S10.W = MFIn[0].bit.b6;
		S10A  = MFIn[0].bit.b7;

		S10B  = MFIn[1].bit.b0;
		S10C  = MFIn[1].bit.b1;
		S10.E = MFIn[1].bit.b2;
		R10.W = MFIn[1].bit.b3;    //Rocky Hill detection
		R10A = MFIn[1].bit.b4;
		R10B = MFIn[1].bit.b5;
		R10C = MFIn[1].bit.b6;
		R11.M = MFIn[1].bit.b7;

        R10.M = R10A || R10B || R10C;

		R12.M = MFIn[2].bit.b0;

		D21.M = D21A || D21B;
		S10.M = S10A || S10B || S10C;

		R10.M = R10A || R10B || R10C;
	}
#endif
}
//---------------------------------------------------------------------------
