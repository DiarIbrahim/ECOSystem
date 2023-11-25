// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim


#include "Components/AnimalAgeManagerComponent.h"
#include "Components/GenderManagerComponent.h"
#include "helpers/Helper.h"
#include "Animal/AnimalBase.h"
#include "helpers/TimeHelper.h"
#include "Types/ECOSystemTypes.h"



// Sets default values for this component's properties
UAnimalAgeManagerComponent::UAnimalAgeManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAnimalAgeManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAnimalAgeManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAnimalAgeManagerComponent::ReceiveTimeTick()
{
	Age++;
	
	// call for OnAnimal info Changed !
	if (GetAnimal()) {
		GetAnimal()->OnInfoChanged();
		GetAnimal()->UpdateSizeOverAge();
		GetAnimal()->GetGenderManager()->OnAgeTick(Age);
	}

	// this randomizes tha age a bit
	int32 ageToDie = (GetAnimal()->GetCommonInfo().MaxAge) + (FMath::RandRange(-5, 5));
	if (GetAnimal() && Age > ageToDie) {
		GetAnimal()->Die();
	}
}

void UAnimalAgeManagerComponent::InitStartingAge(int _age)
{
	if (_age <= 0) return;
	Age = _age;

}

AAnimalBase* UAnimalAgeManagerComponent::GetAnimal()
{
	return Cast<AAnimalBase>(GetOwner());
}

int32 UAnimalAgeManagerComponent::GetAge() const 
{
	return Age;
}

FString UAnimalAgeManagerComponent::GetAgeAsString()
{
	return UTimeHelper::AgeToString(Age);
}

