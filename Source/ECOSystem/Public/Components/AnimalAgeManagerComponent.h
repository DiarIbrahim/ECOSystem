// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AnimalAgeManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECOSYSTEM_API UAnimalAgeManagerComponent : public UActorComponent
{
	GENERATED_BODY()

	// age of ths animal (animal that owns this component ) in Days 
	int32 Age = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Sets default values for this component's properties
	UAnimalAgeManagerComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*
	  This function called from GameMode to notify about one Day time passed
	*/
	void ReceiveTimeTick();

	/*
		returns the owner as AAnimalBase
	*/
	class AAnimalBase* GetAnimal();

	void InitStartingAge(int _age);


	//
	//// Getters
	//

	/*
		returns the age of this animal in days
	*/
	int32 GetAge() const;

	/*
		returns age as string (e.g.  5 days , 2 months 3 days,  1 year 3 months 1 day)
	*/
	FString GetAgeAsString();


	
};
