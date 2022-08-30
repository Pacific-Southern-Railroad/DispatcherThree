//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "PortInOut.h"
//---------------------------------------------------------------------------

void TPSRY::PortInOut(void)
{

//Port A

//Southport

	PAOut[0].bit.b0 = PA12R.Aspect[0];	//Signals
    PAOut[0].bit.b1 = PA12R.Aspect[1];
    PAOut[0].bit.b2 = PA10RA.Aspect[0];
    PAOut[0].bit.b3 = PA10RA.Aspect[1];
    PAOut[0].bit.b4 = PA12LA.Aspect[0];
    PAOut[0].bit.b5 = PA10RB.Aspect[0];
    PAOut[0].bit.b6 = PA10RB.Aspect[1];
    PAOut[0].bit.b7 = PA8R.Aspect[0];

	PAOut[1].bit.b0 = PA8R.Aspect[1];
    PAOut[1].bit.b1 = PA12LB.Aspect[0];
    PAOut[1].bit.b2 = PA6R.Aspect[0];
    PAOut[1].bit.b3 = PA6R.Aspect[1];
    PAOut[1].bit.b4 = PA4RA.Aspect[0];
    PAOut[1].bit.b5 = PA4RA.Aspect[1];
    PAOut[1].bit.b6 = PA12LC.Aspect[0];
    PAOut[1].bit.b7 = PA4RB.Aspect[0];

	PAOut[2].bit.b0 = PA4RB.Aspect[1];
    PAOut[2].bit.b1 = PA8L.Aspect[0];
    PAOut[2].bit.b2 = PA6LA.Aspect[0];
    PAOut[2].bit.b3 = PA6LB.Aspect[0];
    PAOut[2].bit.b4 = PA6LC.Aspect[0];
    PAOut[2].bit.b5 = P10.ClrW;				//Semaphore signal
    PAOut[2].bit.b6 = P10.RstrW;
    PAOut[2].bit.b7 = PASigL4.LI;			//Signal indicators

	PAOut[3].bit.b0 = PASigL4.NI;
    PAOut[3].bit.b1 = PASigL4.RI;
    PAOut[3].bit.b2 = PASigL6.LI;
    PAOut[3].bit.b3 = PASigL6.NI;
    PAOut[3].bit.b4 = PASigL6.RI;
    PAOut[3].bit.b5 = PASigL8.LI;
    PAOut[3].bit.b6 = PASigL8.NI;
    PAOut[3].bit.b7 = PASigL8.RI;

	PAOut[4].bit.b0 = PASigL10.LI;
    PAOut[4].bit.b1 = PASigL10.NI;
    PAOut[4].bit.b2 = PASigL10.RI;
    PAOut[4].bit.b3 = PASigL12.LI;
    PAOut[4].bit.b4 = PASigL12.NI;
    PAOut[4].bit.b5 = PASigL12.RI;
	PAOut[4].bit.b6 = PASigL32.LI;
    PAOut[4].bit.b7 = PASigL32.NI;

    PAOut[5].bit.b0 = PASigL32.RI;
    PAOut[5].bit.b1 = PASigL34.LI;
    PAOut[5].bit.b2 = PASigL34.NI;
    PAOut[5].bit.b3 = PASigL34.RI;
    PAOut[5].bit.b4 = P21.Blk;				//Block indicators
    PAOut[5].bit.b5 = P40.Blk;
    PAOut[5].bit.b6 = P50.RstrW || P50.ClrW;	//Yard signal
    PAOut[5].bit.b7 = P11.RstrE;				//Latham signals

    PAOut[6].bit.b0 = P21.ClrE;
    PAOut[6].bit.b1 = CBParsons;             //DCC circuit breakers
    PAOut[6].bit.b2 = CBSouthport;
    PAOut[6].bit.b3 = CBLavin;
    PAOut[6].bit.b4 = PASw1.L;              //Switch locks
    PAOut[6].bit.b5 = PASw3.L;
   	PAOut[6].bit.b6 = PASw5.L;
    PAOut[6].bit.b7 = PASw7.L;

    PAOut[7].bit.b0 = PASw9.L;
    PAOut[7].bit.b1 = PASw11.L;				//Also locks 13
    PAOut[7].bit.b2 = PASw15.L;             //Also locks 17
    PAOut[7].bit.b3 = PASw19.L;
    PAOut[7].bit.b4 = PASw21.L;
    PAOut[7].bit.b5 = PASw23.L;
    PAOut[7].bit.b6 = PASw31.L;				//Also locks 27 & 29
    PAOut[7].bit.b7 = PASw33.L;

    PAOut[8].bit.b0 = PASw35.L;
    PAOut[8].bit.b1 = PASw37.L;
	PAOut[8].bit.b2 = P10.Srel;             //Stop relay
    PAOut[8].bit.b3 = P40.Srel;             //South Jct. stop relays
    PAOut[8].bit.b4 = P31.Srel;
    PAOut[8].bit.b5 = P40.ClrW;       		//Semaphore signal
    PAOut[8].bit.b6 = P40.RstrW;

	SendPacket(PORTA, &PortAAborts, &PAIn[0], &PAOld[0], &PAOut[0], 9, true);
   		PAText = "PortA\t" + OutText;

    if(Match)
    {
		PASw1.NI = PAIn[0].bit.b0;	//Switch positions
	    PASw1.RI = PAIn[0].bit.b1;
	    PASw3.NI = PAIn[0].bit.b2;
	    PASw3.RI = PAIn[0].bit.b3;
	    PASw5.NI = PAIn[0].bit.b4;
	    PASw5.RI = PAIn[0].bit.b5;
	    PASw7.NI = PAIn[0].bit.b6;
	    PASw7.RI = PAIn[0].bit.b7;

		PASw9.NI = PAIn[1].bit.b0;
	    PASw9.RI = PAIn[1].bit.b1;
	    PASw11.NI = PAIn[1].bit.b2;
	    PASw11.RI = PAIn[1].bit.b3;
		PASw13.RI = PAIn[1].bit.b4;
	    PASw13.NI = PAIn[1].bit.b5;
	    PASw15.NI = PAIn[1].bit.b6;
	    PASw15.RI = PAIn[1].bit.b7;

		PASw17.NI = PAIn[2].bit.b0;
	    PASw17.RI = PAIn[2].bit.b1;
	    PASw19.NI = PAIn[2].bit.b2;
	    PASw19.RI = PAIn[2].bit.b3;
	    PASw21.NI = PAIn[2].bit.b4;
	    PASw21.RI = PAIn[2].bit.b5;
	    PASw23.NI = PAIn[2].bit.b6;
	    PASw23.RI = PAIn[2].bit.b7;

		P1.M = PAIn[3].bit.b0;			//Detection
	    P2.M = PAIn[3].bit.b1;
	    P3.M = PAIn[3].bit.b2;
	    P4.M = PAIn[3].bit.b3;
	    P5.M = PAIn[3].bit.b4;
	    P6.M = PAIn[3].bit.b5;
	    P7.M = PAIn[3].bit.b6;
		PAOS1 = PAIn[3].bit.b7;         //OS sections

		PAOS2 = PAIn[4].bit.b0;
	    PAOS3 = PAIn[4].bit.b1;
	    PAOS4 = PAIn[4].bit.b2;
	    PAOS5 = PAIn[4].bit.b3;
	    P10.M = PAIn[4].bit.b4;
	    P10.E = PAIn[4].bit.b5;
	    PASigL4.R 		= PAIn[4].bit.b6;    //Signal levers
		PASigL4.Callon 	= PAIn[4].bit.b7;

	    PASigL4.L 		= PAIn[5].bit.b0;
	    PASigL6.R 		= PAIn[5].bit.b1;
	    PASigL6.Callon 	= PAIn[5].bit.b2;
	    PASigL6.L		= PAIn[5].bit.b3;
	    PASigL8.R		= PAIn[5].bit.b4;
	    PASigL8.Callon	= PAIn[5].bit.b5;
	    PASigL8.L		= PAIn[5].bit.b6;
		PASigL10.R		= PAIn[5].bit.b7;

	    PASigL10.Callon	= PAIn[6].bit.b0;
	    PASigL10.L		= PAIn[6].bit.b1;
	    PASigL12.R		= PAIn[6].bit.b2;
	    PASigL12.Callon	= PAIn[6].bit.b3;
	    PASigL12.L		= PAIn[6].bit.b4;
	    PASigL32.R		= PAIn[6].bit.b5;
		PASigL32.Callon	= PAIn[6].bit.b6;
	    PASigL32.L		= PAIn[6].bit.b7;

    	PASigL34.R		= PAIn[7].bit.b0;
	    PASigL34.Callon	= PAIn[7].bit.b1;
	    PASigL34.L		= PAIn[7].bit.b2;
        PARelease 		= PAIn[7].bit.b3;	 //Switch release
    }

    //Parsons Jct.

    PJOut[0].bit.b0 = PA34LB.Aspect[0];	//Westward signals
    PJOut[0].bit.b1 = PA34LB.Aspect[1];
    PJOut[0].bit.b2 = PA34LB.Aspect[2];
    PJOut[0].bit.b3 = PA32L.Aspect[0];
    PJOut[0].bit.b4 = PA34LA.Aspect[0];
    PJOut[0].bit.b5 = PA34LA.Aspect[1];
    PJOut[0].bit.b6 = PA34LA.Aspect[2];
    PJOut[0].bit.b7 = PA34RD.Aspect[0];	//Eastward signals

    PJOut[1].bit.b0 = PA34RD.Aspect[1];
    PJOut[1].bit.b1 = PA34RD.Aspect[2];
    PJOut[1].bit.b2 = PA34RC.Aspect[0];
    PJOut[1].bit.b3 = PA32RA.Aspect[0];
    PJOut[1].bit.b4 = PA32RA.Aspect[1];
    PJOut[1].bit.b5 = PA32RA.Aspect[2];
    PJOut[1].bit.b6 = PA34RB.Aspect[0];
    PJOut[1].bit.b7 = PA32RB.Aspect[0];

    PJOut[2].bit.b0 = PA32RB.Aspect[1];
    PJOut[2].bit.b1 = PA32RB.Aspect[2];
    PJOut[2].bit.b2 = PA34RA.Aspect[0];
    PJOut[2].bit.b3 = P20.Srel;            //Stop relays
    PJOut[2].bit.b4 = P30.Srel;
    PJOut[2].bit.b5 = P50.Srel;
    PJOut[2].bit.b6 = P11.Srel;

	SendPacket(PARSONS, &ParsonsAborts, &PJIn[0], &PJOld[0], &PJOut[0], 4, true);
   		PJText = "Parsons Jct" + OutText;

    if(Match)
    {
    	PASw27.NI = PJIn[0].bit.b0;		//Switch positions
    	PASw27.RI = PJIn[0].bit.b1;
    	PASw29.NI = PJIn[0].bit.b2;
    	PASw29.RI = PJIn[0].bit.b3;
    	PASw31.NI = PJIn[0].bit.b4;
    	PASw31.RI = PJIn[0].bit.b5;
    	PASw33.NI = PJIn[0].bit.b6;
    	PASw33.RI = PJIn[0].bit.b7;

    	PASw35.NI = PJIn[1].bit.b0;
    	PASw35.RI = PJIn[1].bit.b1;
    	PASw37.NI = PJIn[1].bit.b2;
    	PASw37.RI = PJIn[1].bit.b3;
    	P20.M = PJIn[1].bit.b4;			//Detection
    	P20.E = PJIn[1].bit.b5;
    	P30.W = PJIn[1].bit.b6;
    	P30.M = PJIn[1].bit.b7;

        P30.E = PJIn[2].bit.b0;
    	PJOS1 = PJIn[2].bit.b1;          //OS sections
    	PJOS2 = PJIn[2].bit.b2;
    	P50.W = PJIn[2].bit.b3;
    	P50.M = PJIn[2].bit.b4;
    	P50.E = PJIn[2].bit.b5;
    	P11.W = PJIn[2].bit.b6;
    	P11.M = PJIn[2].bit.b7;

    	P11.E = PJIn[3].bit.b0;
    }

    //Port B

    PBOut[0].bit.b0 = PB2R.Aspect[0];	//South Jct Eastward signals
    PBOut[0].bit.b1 = PB2R.Aspect[1];
    PBOut[0].bit.b2 = PB2R.Aspect[2];
    PBOut[0].bit.b3	= PB4R.Aspect[0];
    PBOut[0].bit.b4 = PB4R.Aspect[1];
    PBOut[0].bit.b5 = PB4R.Aspect[2];
    PBOut[0].bit.b6 = PB2L.Aspect[0];	//South Jct Westward signals
    PBOut[0].bit.b7 = PB2L.Aspect[1];

    PBOut[1].bit.b0 = PB2L.Aspect[2];
    PBOut[1].bit.b1 = PB4L.Aspect[0];
    PBOut[1].bit.b2 = PB4L.Aspect[1];
    PBOut[1].bit.b3 = PB4L.Aspect[2];
    PBOut[1].bit.b4 = PB12L.Aspect[0];	//Circus Jct Eastward signals
    PBOut[1].bit.b5 = PB12L.Aspect[1];
    PBOut[1].bit.b6 = PB12L.Aspect[2];
    PBOut[1].bit.b7 = PB14L.Aspect[0];

    PBOut[2].bit.b0 = PB14L.Aspect[1];
    PBOut[2].bit.b1 = PB14L.Aspect[2];
    PBOut[2].bit.b2 = PB12R.Aspect[0];	//Westward signals
    PBOut[2].bit.b3 = PB12R.Aspect[1];
    PBOut[2].bit.b4 = PB12R.Aspect[2];
    PBOut[2].bit.b5 = PB14R.Aspect[0];
    PBOut[2].bit.b6 = PB14R.Aspect[1];
    PBOut[2].bit.b7 = PB14R.Aspect[2];

    PBOut[3].bit.b0 = PBSigL2.LI;		//Signal indicators
    PBOut[3].bit.b1 = PBSigL2.NI;
    PBOut[3].bit.b2 = PBSigL2.RI;
    PBOut[3].bit.b3 = PBSigL4.LI;
    PBOut[3].bit.b4 = PBSigL4.NI;
    PBOut[3].bit.b5 = PBSigL4.RI;
    PBOut[3].bit.b6 = PBSw5.Locked;		//Unlock indicator
    PBOut[3].bit.b7 = !PBSw5.Locked;

    PBOut[4].bit.b0 = PBSigL12.LI;      //Signal indicators
    PBOut[4].bit.b1 = PBSigL12.NI;
    PBOut[4].bit.b2 = PBSigL12.RI;
    PBOut[4].bit.b3 = PBSigL14.LI;
    PBOut[4].bit.b4 = PBSigL14.NI;
    PBOut[4].bit.b5 = PBSigL14.RI;
    PBOut[4].bit.b6 = PBSw15.Locked;  	//Unlock indicator
    PBOut[4].bit.b7 = !PBSw15.Locked;

    PBOut[5].bit.b0 = P30.Blk;          //Block indicators
    PBOut[5].bit.b1 = P42.Blk;
    PBOut[5].bit.b2 = P32.ClrW;			//Shore signal
    PBOut[5].bit.b3 = P42.ClrE;         //Hyde Jct. signal
    PBOut[5].bit.b4 = CBSouthJct;       //DCC Circuit breakers
    PBOut[5].bit.b5 = CBCircusJct;
    PBOut[5].bit.b6 = PBSw1.L;			//Switch locks
    PBOut[5].bit.b7 = PBSw3.L;

    PBOut[6].bit.b0 = PBSw5.Locked;
    PBOut[6].bit.b1 = PBSw11.L;
    PBOut[6].bit.b2 = PBSw13.L;
    PBOut[6].bit.b3 = PBSw15.Locked;
    PBOut[6].bit.b4 = P32.Srel;			//Stop relays
    PBOut[6].bit.b5 = P41.Srel;
    PBOut[6].bit.b6 = PBXO;				//Crossing signal


	SendPacket(PORTB, &PortBAborts, &PBIn[0], &PBOld[0], &PBOut[0], 7, true);
   		PBText = "PortB\t" + OutText;

    if(Match)
    {
    	PBSw1.NI = PBIn[0].bit.b0;		//Switch positions
    	PBSw1.RI = PBIn[0].bit.b1;
    	PBSw3.NI = PBIn[0].bit.b2;
    	PBSw3.RI = PBIn[0].bit.b3;
    	PBSw11.NI = PBIn[0].bit.b4;
    	PBSw11.RI = PBIn[0].bit.b5;
    	PBSw13.NI = PBIn[0].bit.b6;
    	PBSw13.RI = PBIn[0].bit.b7;

    	PBSw5.NI = PBIn[1].bit.b0;
    	PBSw5.RI = PBIn[1].bit.b1;
    	PBSw15A.NI = PBIn[1].bit.b2;
    	PBSw15A.RI = PBIn[1].bit.b3;
    	PBSw15B.NI = PBIn[1].bit.b4;
    	PBSw15B.RI = PBIn[1].bit.b5;
    	P40.M = PBIn[1].bit.b6;			//South Jct Detection
    	P40.E = PBIn[1].bit.b7;

    	PBOS1 = PBIn[2].bit.b0;
    	PBOS2 = PBIn[2].bit.b1;
    	P31.W = PBIn[2].bit.b2;
    	P31.M = PBIn[2].bit.b3;
    	P31.E = PBIn[2].bit.b4;
    	P32.W = PBIn[2].bit.b5;			//Circus Jct Detection
    	P32.M = PBIn[2].bit.b6;
    	P32.E = PBIn[2].bit.b7;

    	PBOS3 = PBIn[3].bit.b0;
    	PBOS4 = PBIn[3].bit.b1;
    	P41.W = PBIn[3].bit.b2;
    	P41.M = PBIn[3].bit.b3;
    	P41.E = PBIn[3].bit.b4;
    	PBSigL2.R 		= PBIn[3].bit.b5;	//Signal levers
    	PBSigL2.Callon 	= PBIn[3].bit.b6;
     	PBSigL2.L 		= PBIn[3].bit.b7;

    	PBSigL4.R 		= PBIn[4].bit.b0;
    	PBSigL4.Callon	= PBIn[4].bit.b1;
    	PBSigL4.L		= PBIn[4].bit.b2;
    	PBSw5.UnlockReq	= PBIn[4].bit.b3;
    	PBSigL12.R		= PBIn[4].bit.b4;
    	PBSigL12.Callon = PBIn[4].bit.b5;
    	PBSigL12.L		= PBIn[4].bit.b6;
    	PBSigL14.R		= PBIn[4].bit.b7;

    	PBSigL14.Callon = PBIn[5].bit.b0;
    	PBSigL14.L		= PBIn[5].bit.b1;
    	PBSw15.UnlockReq	= PBIn[5].bit.b2;
        PBRelease 		= PBIn[5].bit.b3;
	}

    PBSw15.NI = PBSw15A.NI && PBSw15B.NI;
	PBSw15.RI = PBSw15A.RI || PBSw15B.RI;
}
