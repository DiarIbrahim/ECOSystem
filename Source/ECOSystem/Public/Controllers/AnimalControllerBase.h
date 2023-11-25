// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AnimalControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class ECOSYSTEM_API AAnimalControllerBase : public AAIController
{
	GENERATED_BODY()

	AAnimalControllerBase();
protected:
	UPROPERTY(BlueprintReadWrite , EditAnywhere)
	class UAnimalPerceptionComponentBase* Perception;

public:
	class AAnimalBase* GetAnimal();

};
