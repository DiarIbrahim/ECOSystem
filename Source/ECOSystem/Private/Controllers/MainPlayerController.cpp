// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim


#include "Controllers/MainPlayerController.h"
#include "UI/ECOSHUD.h"
#include "UI/MainScreen.h"
#include "Animal/AnimalBase.h"
#include "Types/ECOSStaticsTypes.h"
#include "Helpers/Helper.h"





void AMainPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();


	// Bind To Input 
	if (InputComponent) {
		InputComponent->BindAction("Left Mouse" , EInputEvent::IE_Pressed , this, &AMainPlayerController::LeftMouseClick);
		InputComponent->BindAction("Left Mouse", EInputEvent::IE_DoubleClick, this, &AMainPlayerController::CancelAnimalSelection);
	}

}

void AMainPlayerController::LeftMouseClick()
{
	// pply any condition
	CheckInteractableUnderCursor();
}

void AMainPlayerController::CheckInteractableUnderCursor()
{
	FHitResult hit;
	if (GetHitResultUnderCursor(ECC_Visibility, 0, hit)) {
		if (AAnimalBase* animal = Cast<AAnimalBase>(hit.GetActor())) {
			// animal selected !
			OnAnimalSelected(animal);
		}
	}
}

void AMainPlayerController::OnAnimalSelected(AAnimalBase* animal)
{
	if (!GetMainScreen()) return;

	 // if there was seleced before !
	if (SelectedAnimal) {
		SelectedAnimal->OnAnimalInfoChanged.Clear();
	}

	GetMainScreen()->OnAnimalSelected(1,animal->GetAnimalStatics());
	SelectedAnimal = animal;

	// bind to on animal info change delegate on the animal
	if (SelectedAnimal) {
		SelectedAnimal->OnAnimalInfoChanged.AddDynamic(this , &AMainPlayerController::OnAnimalSelectedAnimalDataChanged);
	}
}

void AMainPlayerController::OnAnimalSelectedAnimalDataChanged(FAnimalStatics AnimalInfo)
{
	if (!GetMainScreen()) return;
	GetMainScreen()->OnAnimalSelected(1, AnimalInfo);
}

void AMainPlayerController::CancelAnimalSelection()
{
	if (!SelectedAnimal) return;

	SelectedAnimal->OnAnimalInfoChanged.Clear();
	SelectedAnimal = nullptr;

	if (!GetMainScreen()) return;
	GetMainScreen()->OnAnimalSelected(0, FAnimalStatics());
}

bool AMainPlayerController::IsSelectsAnimal()
{
	return SelectedAnimal != nullptr;
}

UMainScreen* AMainPlayerController::GetMainScreen()
{
	if (AECOSHUD* hud = Cast<AECOSHUD>(GetHUD())) {
		return hud->GetMainScreen();
	}
	return nullptr;
}

bool AMainPlayerController::GetFollowAnimal(AActor*& OutActorToFollow)
{
	if (SelectedAnimal) {
		OutActorToFollow = (AActor*)SelectedAnimal;
		return true;
	}
	else return false;
}

void AMainPlayerController::TimeTick(int32 time)
{
	if (GetMainScreen()) {
		GetMainScreen()->OnTimeTick(time);
	}
}
