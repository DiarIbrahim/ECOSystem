// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim


#include "Singletones/ECOSGameMode.h"
#include "AIController.h"
#include "ECOSystem/Public/Components/GMTimeManagerComponent.h"
#include "ECOSystem/Public/Components/AnimalAgeManagerComponent.h"
#include "ECOSystem/Public/Components/GenderManagerComponent.h"
#include "ECOSystem/Public/Animal/AnimalBase.h"
#include "ECOSystem/Public/player/mainplayer.h"
#include "ECOSystem/Public/Types/ECOSystemTypes.h"
#include "ECOSystem/Public/Types/ECOSStaticsTypes.h"
#include "helpers/Helper.h"
#include "Kismet/GameplayStatics.h"

AECOSGameMode::AECOSGameMode()
{
	if (!timeManager) {
		timeManager = CreateDefaultSubobject<UGMTimeManagerComponent>(FName("TimeManager"));
	}
	
}

void AECOSGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (WorldHistryRecord) {
		WorldHistryRecord->EmptyTable();
	}
}

bool AECOSGameMode::GetAnimals(TArray<class AAnimalBase*>& OutAnimals) const
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAnimalBase::StaticClass(), OutActors);

	if (OutActors.Num() <= 0) return false;

	for (AActor* a :OutActors) {
		if (AAnimalBase* animal = Cast<AAnimalBase>(a)) {
			OutAnimals.Add(animal);
		}
	}
	return OutAnimals.Num() > 0;
}

AMainPlayer* AECOSGameMode::GetMainPlayer() const
{
	return Cast<AMainPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AMainPlayer::StaticClass()));
}

void AECOSGameMode::SpawnNewBorn(AAnimalBase* mother, FAnimalCommonInfo info)
{

	if (!mother || mother->GetGenderManager()->GetGender() != EGender_Female) return;

	AAIController* Controller = GetWorld()->SpawnActor<AAIController>(AnimalControllerClass);

	if (!Controller) {
		UHelper::print_Error("AnimalController is invalid  AECOSGameMode::SpawnNewBorn");
		return;
	}


	FTransform transform;
	transform.SetLocation(FindLocationForNewBorn(mother));
	transform.SetRotation(FQuat::Identity);
	if(AAnimalBase* animal =  GetWorld()->SpawnActor<AAnimalBase>(animalNewBornClass, transform)){
		animal->SetCommonInfo(info);
		Controller->Possess(animal);
		UHelper::print("New Born");
	}
	else { UHelper::print_Error("failed to spawn new born !  AECOSGameMode::SpawnNewBorn"); }

}

FVector AECOSGameMode::FindLocationForNewBorn(AAnimalBase* mother)
{
	FVector result = mother->GetMesh()->GetComponentLocation();
	result = result + mother->GetActorForwardVector() * -100;
	return result;
}

void AECOSGameMode::AnimalDied(AAnimalBase* animal)
{
	animal->GetController()->Destroy();
	animal->Destroy();
}

FGeneralGameStatics AECOSGameMode::GetGeneralStatics_Internal() const
{
	TArray<AAnimalBase*> animals;
	if (GetAnimals(animals)) {

		FGeneralGameStatics statics = FGeneralGameStatics();
		// number of animals
		statics.NumAnimal = animals.Num();

		for (AAnimalBase* a : animals) {
			if (a->GetGenderManager()->GetGender() == EGender_Male) {
				// males
				statics.numMales++;
			}
			else if (a->GetGenderManager()->GetGender() == EGender_Female) {
				//  females
				statics.numFemales++;
				
				// num couples only check females
				if (a->GetGenderManager()->IsInLove()) {
					statics.NumCoubles++;
				}
			}
			// new borns
			if (a->GetAgeManager()->GetAge() < 30) {
				statics.NumNewBorns++;
			}

		}
		return statics;

	} else return FGeneralGameStatics();
}

FGeneralGameStatics AECOSGameMode::GetGeneralStatics() const
{
	// returns already calculated statics
	return GeneralStatics_lastSavedRecord;
}



void AECOSGameMode::SaveCurrentRecord()
{
	// update data
	GeneralStatics_lastSavedRecord = GetGeneralStatics_Internal();

	if (!timeManager || !WorldHistryRecord) return;

	FECOSHistoryRecord record = FECOSHistoryRecord::MakeFromGeneralStatics(GeneralStatics_lastSavedRecord);
	record.Date = timeManager->GetDate();

	FString name = FString("Day_").Append(FString::FromInt(record.Date));

	WorldHistryRecord->AddRow(FName(name), record);

}

