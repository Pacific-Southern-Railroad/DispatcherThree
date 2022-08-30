//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ShoreInOut.h"

//Shore (River Junction)

void TPSRY::ShoreInOut()
{
#ifndef _SIMULATION

	SOut[0].bit.b0 = S4R.Aspect[0];		//Main signals
	SOut[0].bit.b1 = S4R.Aspect[1];
	SOut[0].bit.b2 = S4R.Aspect[2];
	SOut[0].bit.b3 = S12R.Aspect[0];
	SOut[0].bit.b4 = S12R.Aspect[1];
	SOut[0].bit.b5 = S12R.Aspect[2];
	SOut[0].bit.b6 = S4LA.Aspect[0];
	SOut[0].bit.b7 = S4LB.Aspect[0];

	SOut[1].bit.b0 = S4LB.Aspect[1];
	SOut[1].bit.b1 = S4LB.Aspect[2];
	SOut[1].bit.b2 = S4LC.Aspect[0];
	SOut[1].bit.b3 = S4LC.Aspect[1];
	SOut[1].bit.b4 = S4LC.Aspect[2];
	SOut[1].bit.b5 = S12LA.Aspect[0];
  	SOut[1].bit.b6 = S12LA.Aspect[1];
	SOut[1].bit.b7 = S12LA.Aspect[2];

  	SOut[2].bit.b0 = S12LB.Aspect[0];
	SOut[2].bit.b1 = S12LC.Aspect[0];
	SOut[2].bit.b2 = S12LC.Aspect[1];
	SOut[2].bit.b3 = S12LC.Aspect[2];
	SOut[2].bit.b4 = F10H;					//Branch signals
	SOut[2].bit.b5 = F10D;
	SOut[2].bit.b6 = S8R.Aspect[0];
	SOut[2].bit.b7 = S8L.Aspect[0];

	SOut[3].bit.b0 = SXL1;				//Bortell crossing lights
	SOut[3].bit.b1 = SXL2;
	SOut[3].bit.b2 = S10.Blk;        	//Block occupancy
	SOut[3].bit.b3 = H20.Blk;
	SOut[3].bit.b4 = S21.Blk;
	SOut[3].bit.b5	= P32.Blk;
	SOut[3].bit.b6 = !ShoreCB;				//Circuit breakers
	SOut[3].bit.b7 = !HarpersCB;

	SOut[4].bit.b0 = !SSw1.Locked;	//Unlock for switch 1
	SOut[4].bit.b1	= SSw3.NO;			//Switch outputs
	SOut[4].bit.b2	= SSw3.RO;
	SOut[4].bit.b3	= SSw5.NO;
	SOut[4].bit.b4	= SSw5.RO;
	SOut[4].bit.b5	= SSw7.NO;
	SOut[4].bit.b6	= SSw7.RO;
	SOut[4].bit.b7	= SSw9.NO;

	SOut[5].bit.b0	= SSw9.RO;
	SOut[5].bit.b1	= SSw11.NO;
	SOut[5].bit.b2	= SSw11.RO;
	SOut[5].bit.b3	= SSw13.NO;
	SOut[5].bit.b4	= SSw13.RO;
	SOut[5].bit.b5 = BX;                //Diamond crossing power relay
	SOut[5].bit.b6 = S20.Srel;     		//Stop relays
	SOut[5].bit.b7 = S11.Srel;

	SOut[6].bit.b0 = H30Power && !H30.Srel;
	SOut[6].bit.b1 = H10.Srel;
	SOut[6].bit.b2 = F10.Srel;
	SOut[6].bit.b3 = F11.Srel;
	SOut[6].bit.b4 = CSw15.Locked;	//Unlock for switch at Spikes Peak
	SOut[6].bit.b5 = SXG;           //Bortell crossing gates

	SendPacket(SHORE, &ShoreAborts, &SIn[0], &SOld[0], &SOut[0], 8, true);
	SHText = "Shore\t" + OutText;

	if(Match)
	{
		SSw1.NI	= SIn[0].bit.b0;			//Switch positions
		SSw1.RI	= SIn[0].bit.b1;
		SSw3.NI	= SIn[0].bit.b2;
		SSw3.RI	= SIn[0].bit.b3;
		SSw5.NI	= SIn[0].bit.b4;
		SSw5.RI = SIn[0].bit.b5;
		SSw7.NI	= SIn[0].bit.b6;
		SSw7.RI	= SIn[0].bit.b7;

		SSw9.NI	= SIn[1].bit.b0;
		SSw9.RI	= SIn[1].bit.b1;
		SSw11.NI = SIn[1].bit.b2;
		SSw11.RI = SIn[1].bit.b3;
		SSw13.NI = SIn[1].bit.b4;
		SSw13.RI = SIn[1].bit.b5;
		S20.W = SIn[1].bit.b6;  	//Shore detection
		S20A = SIn[1].bit.b7;

		S20B = SIn[2].bit.b0;
		S20C = SIn[2].bit.b1;
		S20.E = SIn[2].bit.b2;
		SOS1 = SIn[2].bit.b3;
		SOS2 = SIn[2].bit.b4;
		S11.W = SIn[2].bit.b5;
		S11B = SIn[2].bit.b6;
		S11.E = SIn[2].bit.b7;

		H30.W = SIn[3].bit.b0;
		H30B = SIn[3].bit.b1;
		H10.W = SIn[3].bit.b2;
		H10B = SIn[3].bit.b3;
		F10.M = SIn[3].bit.b4;	//Harpers detection
		F10.E = SIn[3].bit.b5;
		SOS3  = SIn[3].bit.b6;
		F11.W = SIn[3].bit.b7;

		F11.M = SIn[4].bit.b0;
		SXON  = SIn[4].bit.b1;	//Crossing gate off normal
		CSw15.NI = SIn[4].bit.b2;  //Spikes Peak switch position
		CSw15.RI = SIn[4].bit.b3;
		S11A = SIn[4].bit.b4;  //Added approach cut sections
		H30A = SIn[4].bit.b5;
		H10A = SIn[4].bit.b6;

		S20.M = S20A || S20B || S20C;
		S11.M = S11A || S11B;
		H30.M = H30A || H30B;
		H10.M = H10A || H10B;
	}

   //Hyde Junction

	HJOut[0].bit.b0 = S16R.Aspect[0];	//Eastbound signals
	HJOut[0].bit.b1 = S16R.Aspect[1];
	HJOut[0].bit.b2 = S16R.Aspect[2];
	HJOut[0].bit.b3 = S18R.Aspect[0];
	HJOut[0].bit.b4 = S18R.Aspect[1];
	HJOut[0].bit.b5 = S18R.Aspect[2];
	HJOut[0].bit.b6 = S20R.Aspect[0];
	HJOut[0].bit.b7 = S16L.Aspect[0];	//Westbound signals

	HJOut[1].bit.b0 = S16L.Aspect[1];
	HJOut[1].bit.b1 = S16L.Aspect[2];
	HJOut[1].bit.b2 = S18LB.Aspect[0];
	HJOut[1].bit.b3 = S18LA.Aspect[0];
	HJOut[1].bit.b4 = S20L.Aspect[0];
	HJOut[1].bit.b5 = S20L.Aspect[1];
	HJOut[1].bit.b6 = S20L.Aspect[2];
	HJOut[1].bit.b7 = SSw15.NO;			//Switch outputs

	HJOut[2].bit.b0 = SSw15.RO;
	HJOut[2].bit.b1 = SSw17.NO;
	HJOut[2].bit.b2 = SSw17.RO;
	HJOut[2].bit.b3 = SSw19.NO;
	HJOut[2].bit.b4 = SSw19.RO;
	HJOut[2].bit.b5 = H20.Srel;			//Stopping relays
	HJOut[2].bit.b6 = P42.Srel;
	HJOut[2].bit.b7 = H11.Srel;

	SendPacket(HYDEJCT, &HydeJctAborts, &HJIn[0], &HJOld[0], &HJOut[0], 3, true);
	HJctText = "Hyde Jct " + OutText;

	if(Match)
   	{
   		SSw15.NI = HJIn[0].bit.b0;		//Switch positions
      	SSw15.RI = HJIn[0].bit.b1;
      	SSw17.NI = HJIn[0].bit.b2;
      	SSw17.RI = HJIn[0].bit.b3;
      	SSw19.NI = HJIn[0].bit.b4;
      	SSw19.RI = HJIn[0].bit.b5;
      	H20.M	 = HJIn[0].bit.b6;		//Detection
      	H20.E    = HJIn[0].bit.b7;

		P42.W		= HJIn[1].bit.b0;
      	P42.M		= HJIn[1].bit.b1;
      	P42.E		= HJIn[1].bit.b2;
      	HOS1		= HJIn[1].bit.b3;
      	HOS2		= HJIn[1].bit.b4;
      	HOS3		= HJIn[1].bit.b5;
      	H11.W		= HJIn[1].bit.b6;
      	H11.M		= HJIn[1].bit.b7;
	}
#endif
}

//---------------------------------------------------------------------------
