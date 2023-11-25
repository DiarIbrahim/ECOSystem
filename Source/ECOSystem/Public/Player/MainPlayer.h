// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MainPlayer.generated.h"

UCLASS()
class ECOSYSTEM_API AMainPlayer : public APawn
{
	GENERATED_BODY()


	//       Components

protected:

	USceneComponent* root;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UCameraComponent* Camera;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USpringArmComponent* SpringArm;


	// variables
	bool bCtrl = false;
	// max = 40 min = 5
	float CameraMoovmentSpeed = 10;

public:

	// Sets default values for this pawn's properties
	AMainPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void INPUT_MouseX(float v);
	void INPUT_MouseY(float v);
	void INPUT_UpDown(float v);
	void INPUT_RightLeft(float v);
	void INPUT_ForwardBackward(float v);
	void INPUT_MouseScrol(float v);
	void INPUT_Taggle_Ctrl();

	/*
		Changes Input mode from GameAndUI to UIOnly and viceVersa
	*/
	void Taggle_Input_Mode(bool bGame);

	/*
		Follows an actor and rotates around it
	*/
	void FollowAnimal(float Deltatime , AActor* ActorToFollow);
	/*
		returns a point around the @actor
		returns true if the point is valid to use
		@actor
		@OutLocation the location of the point around @actor
		@OutRotator rotation that looks to the @actor
	*/
	bool GetpointNearActor(AActor* actor , FVector& OutLocation , FRotator& OutRotator);
	/*
		returns the playercontroller as AMainPlayerController
	*/
	class AMainPlayerController* GetPlayerController();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
