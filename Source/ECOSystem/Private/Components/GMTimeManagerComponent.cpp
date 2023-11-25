// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim


#include "Components/GMTimeManagerComponent.h"
#include "ECOSystem/Public/Singletones/ECOSGameMode.h"
#include "ECOSystem/Public/Player/MainPlayer.h"
#include "ECOSystem/Public/Animal/AnimalBase.h"
#include "controllers/MainPlayerController.h"
#include "ECOSystem/Public/Components/AnimalAgeManagerComponent.h"




// Sets default values for this component's properties
UGMTimeManagerComponent::UGMTimeManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGMTimeManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

AECOSGameMode* UGMTimeManagerComponent::GetGameMode()
{
	return Cast<AECOSGameMode>(GetOwner());
}


// Called every frame
float TimeIntervalCounter = 0;
void UGMTimeManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimeIntervalCounter += DeltaTime;
	if (TimeIntervalCounter >= (TimeTickIntervalInSec/SpeedRate)) {
		MakeATimeTick();
	}
	
	
}

void UGMTimeManagerComponent::MakeATimeTick()
{
	Time++;
	TimeIntervalCounter = 0;

	NotifyTimeTick();
}

void UGMTimeManagerComponent::NotifyTimeTick()
{
	if (Time <= 0) return;

	//
	// Notify animals
	//

	TArray<AAnimalBase*> animals;
	if (GetGameMode() && GetGameMode()->GetAnimals(animals)) {
		
		// notify animals
		for (AAnimalBase* animal : animals) {
			animal->GetAgeManager()->ReceiveTimeTick();
		}


		// save new records
		GetGameMode()->SaveCurrentRecord();
	}


	//
	//  Notify Player
	//
	if (AMainPlayerController* controller = Cast<AMainPlayerController>(GetGameMode()->GetMainPlayer()->GetController())) {
		controller->TimeTick(Time);
	}

}

void UGMTimeManagerComponent::UpdateTimeTickInterval(int32 newSpeedRate)
{
	SpeedRate = newSpeedRate;
	newSpeedRate = FMath::Clamp(SpeedRate , 1,60);
}

