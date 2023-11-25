// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim


#include "UI/ECOSHUD.h"


void AECOSHUD::BeginPlay()
{
	GetMainScreen();
}

UMainScreen* AECOSHUD::GetMainScreen()
{
	if (MainScreen_Ref) return MainScreen_Ref;
	MainScreen_Ref = CreateWidget<UMainScreen>(GetWorld(), mainScreen_Class);
	MainScreen_Ref->AddToViewport();
	return MainScreen_Ref;
}
