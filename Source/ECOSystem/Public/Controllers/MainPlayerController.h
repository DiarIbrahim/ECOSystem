// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ECOSYSTEM_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;


	// Reference to the selected Animal
	class AAnimalBase* SelectedAnimal;


	// called when ever left mouse button pressed
	void LeftMouseClick();
	
	/*
		checks under mouse for any interactable actor
	*/ 
	void CheckInteractableUnderCursor();

protected:

	/*
	    Called when CheckInteractableUnderCursor() called and an Animal been detected
		@animal is the clicked Actor
	*/
	virtual void OnAnimalSelected(class AAnimalBase* animal);
	
	/*
		Called by OnAnimalInfoChanged Delegate to inform the main controller that some DataChanged for the selected Animal
	*/
	UFUNCTION()
	void OnAnimalSelectedAnimalDataChanged(struct FAnimalStatics AnimalInfo);

	/*
		call this to cancel the selection of animals this 
	*/
	void CancelAnimalSelection();

	/*
		returns true an Animal is selected by the controller
	*/
	bool IsSelectsAnimal();

	/*
		Returns a Reference pointer to the MainScreen Widget
	*/
	class UMainScreen* GetMainScreen();


public:
	/*
		Returns The true if  an AnimalSelected and it is prefered for Camera to follow the SelectedAnimal
		@OutActorToFollow is holds the reference to theactor to follow;
	*/
	bool GetFollowAnimal(AActor*& OutActorToFollow);


	/*
		called when ever Universal time ticks in the ECOS
	*/

	void TimeTick(int32 time);
};
