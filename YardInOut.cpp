//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "YardInOut.h"

//Cornell Jct----------------------------------------------------------------

void TPSRY::YardInOut(void)
{

//Cornell Jct----------------------------------------------------------------

	CJOut[0].bit.b0 = Y4L.Aspect[0];	//Eastbound signals
	CJOut[0].bit.b1 = Y4L.Aspect[1];
	CJOut[0].bit.b2 = Y4L.Aspect[2];
	CJOut[0].bit.b3 = Y2L.Aspect[0];
	CJOut[0].bit.b4 = Y2R.Aspect[0];	//Westbound signals
    CJOut[0].bit.b5 = Y2R.Aspect[1];
	CJOut[0].bit.b6 = Y2R.Aspect[2];
	CJOut[0].bit.b7 = Y4RA.Aspect[0];

	CJOut[1].bit.b0 = Y4RA.Aspect[1];
	CJOut[1].bit.b1 = Y4RA.Aspect[2];
	CJOut[1].bit.b2 = Y4RB.Aspect[0];
	CJOut[1].bit.b3 = Y21.Srel;
	CJOut[1].bit.b4 = L10.Srel;

	SendPacket(CORNELL, &CornellAborts, &CJIn[0], &CJOld[0], &CJOut[0], 2, true);
  	CJText = "Cornell\t" + OutText;

    if (Match)
    {
   		YSw1.NI = CJIn[0].bit.b0;	//Switch positions
   		YSw1.RI = CJIn[0].bit.b1;
   		YSw3.NI = CJIn[0].bit.b2;
		YSw3.RI = CJIn[0].bit.b3;
   		Y21.W  = CJIn[0].bit.b4;	//Detection
   		Y21.M  = CJIn[0].bit.b5;
 		Y21.E  = CJIn[0].bit.b6;
   		CJOS1  = CJIn[0].bit.b7;

   		CJOS2  = CJIn[1].bit.b0;
   		L10.W  = CJIn[1].bit.b1;
   		L10.M  = CJIn[1].bit.b2;
    }

//East Junction-----------------------------------------------------------------

    EJOut[0].bit.b0 = Y10L.Aspect[0];	//Signals
    EJOut[0].bit.b1 = Y10L.Aspect[1];
    EJOut[0].bit.b2 = Y10L.Aspect[2];
    EJOut[0].bit.b3 = Y8LA.Aspect[0];
    EJOut[0].bit.b4 = Y8LB.Aspect[0];
    EJOut[0].bit.b5 = Y8LC.Aspect[0];
    EJOut[0].bit.b6 = Y8R.Aspect[0];
    EJOut[0].bit.b7 = Y8R.Aspect[1];

    EJOut[1].bit.b0 = Y8R.Aspect[2];
    EJOut[1].bit.b1 = Y10R.Aspect[0];
    EJOut[1].bit.b2 = Y20.Srel;			//Stopping relays
    EJOut[1].bit.b3 = Y11.Srel;

	SendPacket(EASTJCT, &EJuncAborts, &EJIn[0], &EJOld[0], &EJOut[0], 2, true);
  	EJText = "EastJct\t" + OutText;

	if (Match)
    {
   		YSw7.NI  = EJIn[0].bit.b0;		//Switch positions
   		YSw7.RI  = EJIn[0].bit.b1;
   		YSw9.NI  = EJIn[0].bit.b2;
   		YSw9.RI  = EJIn[0].bit.b3;
   		YSw11.NI = EJIn[0].bit.b4;
   		YSw11.RI = EJIn[0].bit.b5;
   		Y20.M = EJIn[0].bit.b6;			//Detection
   		Y20.E = EJIn[0].bit.b7;

   		EJOS1 = EJIn[1].bit.b0;
   		EJOS2 = EJIn[1].bit.b1;
   		Y11.W = EJIn[1].bit.b2;
   		Y11.M = EJIn[1].bit.b3;
    }

//Kale-----------------------------------------------------------------------

    KAOut[0].bit.b0 = Y22L.Aspect[0];		//Signals
    KAOut[0].bit.b1 = Y26LA.Aspect[0];
    KAOut[0].bit.b2 = Y26LB.Aspect[0];
    KAOut[0].bit.b3 = Y26LC.Aspect[0];
    KAOut[0].bit.b4 = Y24LA.Aspect[0];
    KAOut[0].bit.b5 = Y24LB.Aspect[0];
    KAOut[0].bit.b6 = Y20H;
    KAOut[0].bit.b7 = Y20D;

    KAOut[1].bit.b0 = Y26R.Aspect[0];
    KAOut[1].bit.b1 = Y22Ra;
    KAOut[1].bit.b2 = Y22Rb;

    SendPacket(KALE, &KaleAborts, &KAIn[0], &KAOld[0], &KAOut[0], 4, true);
  	KAText = "Kale\t" + OutText;

    if(Match)
    {
    	YSw17.NI = KAIn[0].bit.b0;		//Switch positions
    	YSw17.RI = KAIn[0].bit.b1;
    	YSw19.NI = KAIn[0].bit.b2;
    	YSw19.RI = KAIn[0].bit.b3;
    	YSw21.NI = KAIn[0].bit.b4;
    	YSw21.RI = KAIn[0].bit.b5;
    	YSw23.NI = KAIn[0].bit.b6;
    	YSw23.RI = KAIn[0].bit.b7;

    	YSw25.NI = KAIn[1].bit.b0;
    	YSw25.RI = KAIn[1].bit.b1;
    	YSw27.NI = KAIn[1].bit.b2;
    	YSw27.RI = KAIn[1].bit.b3;
    	YSw29.NI = KAIn[1].bit.b4;
    	YSw29.RI = KAIn[1].bit.b5;
    	Y30.M = KAIn[1].bit.b6;       //Detection
    	KAOS1 = KAIn[1].bit.b7;

    	Y53.M = KAIn[2].bit.b0;
    	Y52.M = KAIn[2].bit.b1;
    	Y51.M = KAIn[2].bit.b2;
    	Y50.M = KAIn[2].bit.b3;
    	KAOS3 = KAIn[2].bit.b4;
    	KAOS4 = KAIn[2].bit.b5;
    	KAOS2 = KAIn[2].bit.b6;
    	Y10.M = KAIn[2].bit.b7;
	}

//Yard-----------------------------------------------------------------------

    YDOut[0].bit.b0 = YSigL2.LI;	//Signal indicators
    YDOut[0].bit.b1 = YSigL2.NI;
    YDOut[0].bit.b2 = YSigL2.RI;
    YDOut[0].bit.b3 = YSigL4.LI;
    YDOut[0].bit.b4 = YSigL4.NI;
    YDOut[0].bit.b5 = YSigL4.RI;
    YDOut[0].bit.b6 = YSigL8.LI;
    YDOut[0].bit.b7 = YSigL8.NI;

    YDOut[1].bit.b0 = YSigL8.RI;
    YDOut[1].bit.b1 = YSigL10.LI;
    YDOut[1].bit.b2 = YSigL10.NI;
    YDOut[1].bit.b3 = YSigL10.RI;
    YDOut[1].bit.b4 = YSigL22.LI;
    YDOut[1].bit.b5 = YSigL22.NI;
    YDOut[1].bit.b6 = YSigL22.RI;
    YDOut[1].bit.b7 = YSigL24.LI;

    YDOut[2].bit.b0 = YSigL24.NI;
    YDOut[2].bit.b1 = YSigL26.LI;
    YDOut[2].bit.b2 = YSigL26.NI;
    YDOut[2].bit.b3 = YSigL26.RI;
    YDOut[2].bit.b4 = YSigL34.LI;
    YDOut[2].bit.b5 = YSigL34.NI;
    YDOut[2].bit.b6 = YSigL34.RI;
    YDOut[2].bit.b7 = Y34RA.Aspect[0];	//Signals

    YDOut[3].bit.b0 = Y34RB.Aspect[0];
    YDOut[3].bit.b1 = Y34L.Aspect[0];
    YDOut[3].bit.b2 = Y34L.Aspect[1];
    YDOut[3].bit.b3 = Y34L.Aspect[2];
    YDOut[3].bit.b4 = CBKale;			//Circuit breakers
    YDOut[3].bit.b5 = CBEastEnd;
    YDOut[3].bit.b6 = CBCornell;
    YDOut[3].bit.b7 = CBEngineYard;

    YDOut[4].bit.b0 = CBWaterman;
    YDOut[4].bit.b1 = L20.Blk;          //Adjacent block indicators
    YDOut[4].bit.b2 = P50.Blk;
    YDOut[4].bit.b3 = YSw1.L;			//Switch locks
    YDOut[4].bit.b4 = YSw3.L;
    YDOut[4].bit.b5 = YSw7.L;
    YDOut[4].bit.b6 = YSw9.L;
    YDOut[4].bit.b7 = YSw17.L;

    YDOut[5].bit.b0 = YSw19.L;
    YDOut[5].bit.b1 = YSw21.L;
    YDOut[5].bit.b2 = YSw23.L;
    YDOut[5].bit.b3 = YSw25.L;
    YDOut[5].bit.b4 = YSw29.L;
	YDOut[5].bit.b5 = YSw33.L;

	SendPacket(YARD, &YardAborts, &YDIn[0], &YDOld[0], &YDOut[0], 6, true);
	YDText = "Yard\t" + OutText;

    if(Match)
    {
    	YSw33.NI = YDIn[0].bit.b0;		//Switch position
		YSw33.RI = YDIn[0].bit.b1;

		if(RBYard->Checked)
		{
			YSigL2.R = YDIn[0].bit.b2;      //Signals
			YSigL2.Callon = YDIn[0].bit.b3;
			YSigL2.L = YDIn[0].bit.b4;
			YSigL4.R = YDIn[0].bit.b5;
			YSigL4.Callon = YDIn[0].bit.b6;
			YSigL4.L = YDIn[0].bit.b7;

			YSigL8.R = YDIn[1].bit.b0;
			YSigL8.Callon = YDIn[1].bit.b1;
			YSigL8.L = YDIn[1].bit.b2;
			YSigL10.R = YDIn[1].bit.b3;
			YSigL10.Callon = YDIn[1].bit.b4;
			YSigL10.L = YDIn[1].bit.b5;
			YSigL22.R = YDIn[1].bit.b6;
			YSigL22.Callon = YDIn[1].bit.b7;

			YSigL22.L = YDIn[2].bit.b0;
			YSigL24.Callon = YDIn[2].bit.b1;
			YSigL24.L = YDIn[2].bit.b2;
			YSigL26.R = YDIn[2].bit.b3;
			YSigL26.Callon = YDIn[2].bit.b4;
			YSigL26.L = YDIn[2].bit.b5;
			YSigL34.R = YDIn[2].bit.b6;
			YSigL34.Callon = YDIn[2].bit.b7;

			YSigL34.L = YDIn[3].bit.b0;
		}

		YRelease = YDIn[3].bit.b1;
		WOS1Norm = YDIn[3].bit.b2;      //switches normal for WOS1 into Y70
		Y81W = YDIn[3].bit.b3;
		Y82W = YDIn[3].bit.b4;
		Y83W = YDIn[3].bit.b5;
		Y84W = YDIn[3].bit.b6;
		Y81E = YDIn[3].bit.b7;

		Y82E = YDIn[4].bit.b0;
		Y83E = YDIn[4].bit.b1;
		Y84E = YDIn[4].bit.b2;
		Y70.M = YDIn[4].bit.b3;         //Waterman detection
		WOS1 = YDIn[4].bit.b4;
	//	Y81.M = YDIn[4].bit.b5;
		Y82.M = YDIn[4].bit.b6;         //bad bit
		Y83.M = YDIn[4].bit.b7;

		Y84.M = YDIn[5].bit.b0;
		WOS2 = YDIn[5].bit.b1;
		Y87.M = YDIn[5].bit.b2;
		Y81.M = YDIn[5].bit.b3;
		// = YDIn[5].bit.b4;
		// = YDIn[5].bit.b5;
		// = YDIn[5].bit.b6;
		// = YDIn[5].bit.b7;
	}

	//Yard and Waterman switch control by dispatcher

	YSWOut[0].bit.b0 = YSw1.NO;
	YSWOut[0].bit.b1 = YSw1.RO;
	YSWOut[0].bit.b2 = YSw3.NO;
	YSWOut[0].bit.b3 = YSw3.RO;
	YSWOut[0].bit.b4 = YSw7.NO;
	YSWOut[0].bit.b5 = YSw7.RO;
	YSWOut[0].bit.b6 = YSw9.NO;
	YSWOut[0].bit.b7 = YSw9.RO;

	YSWOut[1].bit.b0 = YSw11.NO;
	YSWOut[1].bit.b1 = YSw11.RO;
	YSWOut[1].bit.b2 = YSw17.NO;
	YSWOut[1].bit.b3 = YSw17.RO;
	YSWOut[1].bit.b4 = YSw19.NO;
	YSWOut[1].bit.b5 = YSw19.RO;
	YSWOut[1].bit.b6 = YSw21.NO;
	YSWOut[1].bit.b7 = YSw21.RO;

	YSWOut[2].bit.b0 = YSw23.NO;
	YSWOut[2].bit.b1 = YSw23.RO;
	YSWOut[2].bit.b2 = YSw25.NO;
	YSWOut[2].bit.b3 = YSw25.RO;
	YSWOut[2].bit.b4 = YSw27.NO;
	YSWOut[2].bit.b5 = YSw27.RO;
	YSWOut[2].bit.b6 = YSw29.NO;
	YSWOut[2].bit.b7 = YSw29.RO;

	YSWOut[3].bit.b0 = SBY51W;
	YSWOut[3].bit.b1 = SBY50W;
//	YSWOut[3].bit.b2 = ;
//	YSWOut[3].bit.b3 = ;
//	YSWOut[3].bit.b4 = ;
//	YSWOut[3].bit.b5 = ;
//	YSWOut[3].bit.b6 = ;
//	YSWOut[3].bit.b7 = ;

	YSWOut[4].bit.b0 = SBY81W;
	YSWOut[4].bit.b1 = SBY82W;
	YSWOut[4].bit.b2 = SBY83W;
	YSWOut[4].bit.b3 = SBY84W;
	YSWOut[4].bit.b4 = SBY81E;
	YSWOut[4].bit.b5 = SBY82E;
	YSWOut[4].bit.b6 = SBY83E;
	YSWOut[4].bit.b7 = SBY84E;

	SendPacket(YARDSW, &YardSWAborts, &YSWIn[0], &YSWOld[0], &YSWOut[0], 5, true);
	YSWText = "YardSW\t" + OutText;

}
//---------------------------------------------------------------------------