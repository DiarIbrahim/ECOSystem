// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim


#include "Animal/AnimalBase.h"
#include "Singletones/ECOSGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ECOSystem/Public/Components/GenderManagerComponent.h"
#include "ECOSystem/Public/Components/AnimalAgeManagerComponent.h"
#include "helpers/TimeHelper.h"
#include "helpers/GenderHelper.h"
#include "helpers/Helper.h"




// Sets default values
AAnimalBase::AAnimalBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!GenderManager) {
		GenderManager = CreateDefaultSubobject<UGenderManagerComponent>("GenderManager");
	}
	if (!AgeManager) {
		AgeManager = CreateDefaultSubobject<UAnimalAgeManagerComponent>("AgeManager");
	}
}

// Called when the game starts or when spawned
void AAnimalBase::BeginPlay()
{
	Super::BeginPlay();

	// Set the minimal scale of the animal
	SetActorScale3D(FVector(GetCommonInfo().minimalScale));
}

// Called every frame
void AAnimalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAnimalBase::makeLove(AAnimalBase* animal)
{
	GetGenderManager()->AskMakeLove(animal);
}

void AAnimalBase::UpdateSizeOverAge()
{
	if (!GetMesh() || !GetAgeManager()) return;

	float size_overAge = (float)GetAgeManager()->GetAge() / (float)GetCommonInfo().MatureAge;
	// clamp so the new borns will not have a scale of 0
	size_overAge = FMath::Clamp(size_overAge ,GetCommonInfo().minimalScale, 1.0);
	
	SetActorScale3D(FVector(size_overAge));

}

void AAnimalBase::Die()
{
	// Notify GM about the death
	if (AECOSGameMode* GM = Cast<AECOSGameMode>(UGameplayStatics::GetGameMode(this))) {
		GM->AnimalDied(this);
	}

	// notify lover about the death
	if (GetGenderManager() && GetGenderManager()->GetLover()) {
		GetGenderManager()->GetLover()->ReceivePartnerDeathNotify();
	}
}

void AAnimalBase::ReceivePartnerDeathNotify()
{
	// implement any thing that animals need to do after their partners died

	// notify the lover
	if (GenderManager) {
		GenderManager->OnPartnerDied();
	}

}

FAnimalStatics AAnimalBase::GetAnimalStatics() const
{
	FAnimalStatics statics;
	statics.Age = GetAgeManager()->GetAge();
	statics.AgeString = GetAgeManager()->GetAgeAsString();
	statics.Gedner = UGenderHelper::GenderToInt(GetGenderManager()->GetGender());
	statics.bIsInLove = GetGenderManager()->IsInLove();
	statics.bIsPragnent = GetGenderManager()->IsPragnent();
	statics.PragnencyPercentage = GetGenderManager()->GetPragnencyPercentage();
//	if (statics.bIsInLove) {
//		GetGenderManager()->GetLover();
//	}

	return statics;
}




void AAnimalBase::InitializeAnimal(FAnimalInitInfo initInfo)
{
	if (GetAgeManager() && initInfo.startingAge != -1) {
		// modify the age of this animal
		GetAgeManager()->InitStartingAge(initInfo.startingAge);
	}

}

void AAnimalBase::OnInfoChanged()
{
	if (OnAnimalInfoChanged.IsBound()) {
		OnAnimalInfoChanged.Broadcast(GetAnimalStatics());
	}


}

void AAnimalBase::SetCommonInfo(const FAnimalCommonInfo& info)
{
	CommonInfo = info;
}
