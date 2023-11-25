// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainScreen.generated.h"

/**
 * 
 */
UCLASS()
class ECOSYSTEM_API UMainScreen : public UUserWidget
{
	GENERATED_BODY()

	/// TEST
public:

	// called when the universal Time ticks on the ECOS
	UFUNCTION(BlueprintImplementableEvent)
	void OnTimeTick(int32 Time);

	// called when ever an animal selected or Unselected
	UFUNCTION(BlueprintImplementableEvent)
	void OnAnimalSelected(bool ShowInfo,struct FAnimalStatics animalStartics);

};
