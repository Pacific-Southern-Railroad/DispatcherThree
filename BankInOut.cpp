//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "BankInOut.h"

void TPSRY::BankInOut(void)
{
#ifndef _SIMULATION
	BKOut[0].bit.b0 = C22R.Aspect[0];  //Bank West eastbound signals
	BKOut[0].bit.b1 = C24R.Aspect[0];
	BKOut[0].bit.b2 = C24R.Aspect[1];
	BKOut[0].bit.b3 = C24R.Aspect[2];
	BKOut[0].bit.b4 = C24L.Aspect[0];  //Westbound signals
	BKOut[0].bit.b5 = C24L.Aspect[1];
	BKOut[0].bit.b6 = C24L.Aspect[2];
	BKOut[0].bit.b7 = C22L.Aspect[0];

	BKOut[1].bit.b0 = C22L.Aspect[1];
	BKOut[1].bit.b1 = C22L.Aspect[2];
	BKOut[1].bit.b2 = C18RA.Aspect[0];   //Bank East eastbound signals
	BKOut[1].bit.b3 = C18RB.Aspect[0];
	BKOut[1].bit.b4 = C18RB.Aspect[1];
	BKOut[1].bit.b5 = C18RB.Aspect[2];
	BKOut[1].bit.b6 = C18L.Aspect[0];    //Westbound signal
	BKOut[1].bit.b7 = C18L.Aspect[1];

	BKOut[2].bit.b0 = C18L.Aspect[2];
   	BKOut[2].bit.b1 = B10.Blk;          //Block indicators
	BKOut[2].bit.b2 = C13.Blk;
	BKOut[2].bit.b3 = CSw21.Locked;		//Hand switch locks
   	BKOut[2].bit.b4 = CSw19.Locked;
	BKOut[2].bit.b5 = CSw23.NO;			//Switch outputs
	BKOut[2].bit.b6 = CSw23.RO;
	BKOut[2].bit.b7 = CSw17.NO;

	BKOut[3].bit.b0 = CSw17.RO;
   	BKOut[3].bit.b1 = B20.Srel;			//Stop relays
	BKOut[3].bit.b2 = B11.Srel;
	BKOut[3].bit.b3 = B21.Srel;
   	BKOut[3].bit.b4 = CBBank;           //DCC Circuit breaker
   	BKOut[3].bit.b5 = B20.ClrE;			//Signal 24L indicator

  	SendPacket(BANK, &BankAborts, &BKIn[0], &BKOld[0], &BKOut[0], 4, true);
   	BKText = "Bank\t" + OutText;

   	if (Match)
   	{
	   	CSw23.NI  = BKIn[0].bit.b0;		//Switch positions
		CSw23.RI  = BKIn[0].bit.b1;
		CSw21A.NI = BKIn[0].bit.b2;
		CSw21A.RI = BKIn[0].bit.b3;
		CSw21B.NI = BKIn[0].bit.b4;
		CSw21B.RI = BKIn[0].bit.b5;
		CSw19.NI  = BKIn[0].bit.b6;
		CSw19.RI  = BKIn[0].bit.b7;

	   	CSw17.NI  = BKIn[1].bit.b0;
		CSw17.RI  = BKIn[1].bit.b1;
		B20.M    = BKIn[1].bit.b2;		//Detection
		B20.E    = BKIn[1].bit.b3;
		BKOS1    = BKIn[1].bit.b4;
		BKOS2    = BKIn[1].bit.b5;
		B11.W    = BKIn[1].bit.b6;
		B11.M    = BKIn[1].bit.b7;

	   	B21.W    = BKIn[2].bit.b0;
		B21.M    = BKIn[2].bit.b1;
		B21.E    = BKIn[2].bit.b2;
		BKOS3    = BKIn[2].bit.b3;
	   	CktBkr[9]      = !BKIn[2].bit.b4;	//South	Bank
      	CktBkr[10]     = !BKIn[2].bit.b5;   //  "		Kale
      	CktBkr[11]     = !BKIn[2].bit.b6;   //	 "		Waterman
      	CktBkr[12]     = !BKIn[2].bit.b7;   //  "		Engine Yard

      	CktBkr[13]		= !BKIn[3].bit.b0;   //  "		East End Jct.
      	CktBkr[14]     = !BKIn[3].bit.b1;   //  "		Shore
      	CktBkr[15]     = !BKIn[3].bit.b2;   //	 "		Rocky Hill
      	CktBkr[16]     = !BKIn[3].bit.b3;   //  "		Harper's Ferry
      	CktBkr[17]     = !BKIn[3].bit.b4;   //  "		Block Y30
      	CktBkr[18]     = !BKIn[3].bit.b5;   //	 "		Block Y81

      	CSw21.NI = CSw21A.NI && CSw21B.NI;
      	CSw21.RI = CSw21A.RI || CSw21B.RI;
	}
#endif
}
//---------------------------------------------------------------------------
