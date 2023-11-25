// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "AnimalPerceptionComponentBase.generated.h"

/**
 * 
 */
UCLASS()
class ECOSYSTEM_API UAnimalPerceptionComponentBase : public UAIPerceptionComponent
{
	GENERATED_BODY()


	virtual void BeginPlay()override;
	UFUNCTION()
	void OnAnimalPreceptionUpdate(class AActor* actor , FAIStimulus Stimulus);

	
	class AAnimalControllerBase* GetAnimalController();


};
