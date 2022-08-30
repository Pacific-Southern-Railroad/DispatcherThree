//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("PSRYUnit.cpp", PSRY);
USEFORM("EditLoco.cpp", EditLocos);
USEFORM("EditRoutesUnit.cpp", EditRoutes);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TPSRY), &PSRY);
		Application->CreateForm(__classid(TEditLocos), &EditLocos);
		Application->CreateForm(__classid(TEditRoutes), &EditRoutes);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
