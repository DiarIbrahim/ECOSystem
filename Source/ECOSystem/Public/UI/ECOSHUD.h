// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainScreen.h"

#include "ECOSHUD.generated.h"

/**
 * 
 */
UCLASS()
class ECOSYSTEM_API AECOSHUD : public AHUD
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadWrite , EditAnywhere)
	TSubclassOf<UMainScreen> mainScreen_Class;

	UMainScreen* MainScreen_Ref;

public:

	class UMainScreen* GetMainScreen();
	
};
