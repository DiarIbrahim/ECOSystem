// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim


#include "Components/GenderManagerComponent.h"
#include "Components/AnimalAgeManagerComponent.h"

#include "ECOSystem/Public/Animal/AnimalBase.h"
#include "ECOSystem/Public/Types/ECOSystemTypes.h"
#include "helpers/GenderHelper.h"

#include "Singletones/ECOSGameMode.h"
#include "Kismet/GameplayStatics.h"

#include "helpers/Helper.h"



// Sets default values for this component's properties
UGenderManagerComponent::UGenderManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGenderManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



// Called every frame
void UGenderManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UGenderManagerComponent::OnAgeTick(int age)
{

	// scale over age
	
	
	if (GetGender() == EGender_Male) {
		// it is a male
		OnAgeTick_Male(age);
	}
	else if (GetGender() == EGender_Female) {
		// it is a female
		OnAgeTick_Female(age);
	}

}

int male_child_fever = 0;
void UGenderManagerComponent::OnAgeTick_Male(int age)
{
	male_child_fever++;

	if (male_child_fever > GetAnimalCommonInfo().ChildFeverRate && GetLover()) {
		AskForChild();
		male_child_fever = 0;
	}
}


void UGenderManagerComponent::OnAgeTick_Female(int age)
{
	if (IsPragnent()) {
		onPragnency();
	}

}

void UGenderManagerComponent::AskMakeLove(AAnimalBase* animalToAsk)
{
	if (IsInLove() || !CanMakeNewLove() || !CanAskOrReceiveLoveRequest(animalToAsk) || GetGender() != EGender_Male ) return;
	AskedForLoveAnimal = animalToAsk;
	animalToAsk->GetGenderManager()->ReceiveMakeLove(GetAnimal());

}

void UGenderManagerComponent::ReceiveMakeLove(AAnimalBase* animalToMakeLove)
{
	if (IsInLove() || !CanMakeNewLove() || !CanAskOrReceiveLoveRequest(animalToMakeLove)) {
		// this love reuest is rejected
		animalToMakeLove->GetGenderManager()->OnLoveDenied(GetAnimal());
		return;
	}

	LoverAnimal = animalToMakeLove;
	animalToMakeLove->GetGenderManager()->OnLoveAcepted(GetAnimal());


	// fire the delegate
	OnFallInLove_Female.Broadcast();
}

void UGenderManagerComponent::OnLoveAcepted(AAnimalBase* Animal)
{
	if(IsInLove()) return;

	ensure(AskedForLoveAnimal);

	// make sure the @Animal is the same as AskedForLoveAnimal (the caller of OnLoveAcepted is the same Animal asked for love by this animal !  ) 
	if (Animal != AskedForLoveAnimal) return;
	LoverAnimal = Animal;

	UHelper::print(" love request Accepted ! ");

	// free
	AskedForLoveAnimal = nullptr;



	// call for OnAnimal info Changed !
	if (GetAnimal()) {
		GetAnimal()->OnInfoChanged();
	}


	// fire the delegate
	OnFallInLove_Male.Broadcast();
}

void UGenderManagerComponent::OnLoveDenied(AAnimalBase* Animal)
{
	AskedForLoveAnimal = nullptr;
}

void UGenderManagerComponent::AskForChild()
{
	if (!GetLover()) return;

	GetLover()->GetGenderManager()->OnRecieveMakeChildRequest(GetAnimal());

}

void UGenderManagerComponent::OnRecieveMakeChildRequest(AAnimalBase* AskingAnimal)
{
	if (GetGender() != EGender_Female || IsPragnent() || !GetLover() || !AskingAnimal || GetLover() != AskingAnimal) return;


	// stop if this is not first pragnency for this animal and not yet much time passed after the last birth
	if (lastPragnancyDate != -1 && (GetAge() - lastPragnancyDate) < GetAnimalCommonInfo().periodToNextBerth) return;

	
	float randomFloat = FMath::RandRange(0.0,1.0);
	// if the acceptance rate is valid
	if (randomFloat > GetAnimalCommonInfo().ChildFeverRequestAcceptanceRate) return;

	StartPragnency();

}


void UGenderManagerComponent::StartPragnency()
{
	// this is like an anouncement for the starting of the pragnency peocess
	pragnency_day = 0; 

}

void UGenderManagerComponent::onPragnency()
{
	if (!IsPragnent()) return;

	pragnency_day++;

	// give birth
	if (pragnency_day > GetAnimalCommonInfo().DaysToGiveBirth) {
		GiveBirth();
	}
}

float UGenderManagerComponent::GetPragnencyPercentage() const
{
	if (GetGender() != EGender_Female) return 0.0;
	return (float)pragnency_day/(float)GetAnimalCommonInfo().DaysToGiveBirth;
}

void UGenderManagerComponent::GiveBirth()
{
	pragnency_day = -1;
	lastPragnancyDate = GetAge();

	// call game mode to spawn baby !
	if(AECOSGameMode* gm = Cast<AECOSGameMode>(UGameplayStatics::GetGameMode(GetWorld()))){
		gm->SpawnNewBorn(GetAnimal(),FAnimalCommonInfo::MakeForNewBorn(this , LoverAnimal->GetGenderManager()));
	}
	else { UHelper::print("GM failed   UGenderManagerComponent::GiveBirth"); }
	
}

bool UGenderManagerComponent::IsPragnent()
{
	return pragnency_day != -1;
}

bool UGenderManagerComponent::CanMakeNewLove()
{
	// if there is no lover , yes
	return LoverAnimal == nullptr && AskedForLoveAnimal == nullptr;
}

bool UGenderManagerComponent::CanAskOrReceiveLoveRequest(AAnimalBase* AskerOrReceiverAnimal)
{
	if (!GetAnimal()) return false;
	return  GetAnimal()->GetCommonInfo().MatureAge <= GetAge() && UGenderHelper::CanMakeLove(GetAnimal() , AskerOrReceiverAnimal);
}

void UGenderManagerComponent::OnPartnerDied()
{
	LoverAnimal = nullptr;
}

bool UGenderManagerComponent::IsInLove() const
{
	return LoverAnimal != nullptr;
}

EAnimalGender UGenderManagerComponent::GetGender() const
{
	if (GetAnimal()) {
		return GetAnimalCommonInfo().Gender;
	}
	else return EAnimalGender::EGender_NONE;
}

AAnimalBase* UGenderManagerComponent::GetAnimal() const
{
	return Cast<AAnimalBase>(GetOwner());
}

int UGenderManagerComponent::GetAge() const
{
	return GetAnimal()->GetAgeManager()->GetAge();
}

FAnimalCommonInfo UGenderManagerComponent::GetAnimalCommonInfo() const
{
	if (!GetAnimal()) return FAnimalCommonInfo();
	return GetAnimal()->GetCommonInfo();
}

AAnimalBase* UGenderManagerComponent::GetLover()
{
	return LoverAnimal;
}

