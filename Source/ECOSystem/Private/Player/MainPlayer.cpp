// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim


#include "Player/MainPlayer.h"
#include "gameframework/SpringarmComponent.h"
#include "Camera/CameraComponent.h"
#include "Controllers/MainPlayerController.h"
#include "Helpers/Helper.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AMainPlayer::AMainPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!root) {
		root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
		SetRootComponent(root);
	}

	if (!SpringArm) {
		//SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArm"));
		//SpringArm->SetupAttachment(GetRootComponent());
		//SpringArm->TargetArmLength = 20;

	}

	if (!Camera) {
		Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
		Camera->SetupAttachment(GetRootComponent());
	}

}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* pc = Cast<APlayerController>(GetController())) {
		pc->PlayerCameraManager->ViewPitchMax = 20;
		pc->PlayerCameraManager->ViewPitchMin = -50;
	}
	
}


// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AActor* actorToFollow = nullptr;
	if (GetPlayerController() && GetPlayerController()->GetFollowAnimal(actorToFollow)) {
		FollowAnimal(DeltaTime, actorToFollow);
	}


}

#pragma region Input functions


void AMainPlayer::INPUT_UpDown(float v)
{
	AddActorWorldOffset(FVector::UpVector * CameraMoovmentSpeed * v);
}

void AMainPlayer::INPUT_RightLeft(float v)
{
	AddActorWorldOffset(Camera->GetRightVector() * CameraMoovmentSpeed * v);
}

void AMainPlayer::INPUT_ForwardBackward(float v)
{

	AddActorWorldOffset(Camera->GetForwardVector() * CameraMoovmentSpeed *v);

}

void AMainPlayer::INPUT_MouseScrol(float v)
{
	CameraMoovmentSpeed += v;

	CameraMoovmentSpeed = FMath::Clamp(CameraMoovmentSpeed , 5,40);
}

void AMainPlayer::INPUT_Taggle_Ctrl()
{
	bCtrl = !bCtrl;
	Taggle_Input_Mode(bCtrl);
}

void AMainPlayer::Taggle_Input_Mode(bool bGame)
{
	if (APlayerController* pc = Cast<APlayerController>(GetController())) {
		if (bCtrl) {
			pc->SetInputMode(FInputModeGameAndUI());
			pc->bShowMouseCursor = true;
		}
		else {
			pc->SetInputMode(FInputModeGameOnly());
			pc->bShowMouseCursor = false;
		}
	}
}

void AMainPlayer::FollowAnimal(float Deltatime , AActor* ActorToFollow)
{
	if (!ActorToFollow) return;
	
	FVector loc;
	FRotator rot;
	if (GetpointNearActor(ActorToFollow,loc,rot)) {
		FVector smoothedLoc = FMath::Lerp(GetActorLocation() ,loc , 0.2);
		FRotator smoothedRot = FMath::Lerp(Camera->GetComponentRotation(), rot, 0.2);

		SetActorLocation(smoothedLoc);
		Camera->SetWorldRotation(smoothedRot);
	}

}

void AMainPlayer::INPUT_MouseX(float v)
{
	//AddControllerYawInput(v);
	SetActorRotation(GetActorRotation() + FRotator(0, v, 0));
}

void AMainPlayer::INPUT_MouseY(float v)
{
	// AddControllerPitchInput(-v);
	Camera->SetWorldRotation(Camera->GetComponentRotation() + FRotator(v, 0, 0));
	if (Camera->GetComponentRotation().Pitch > -10 && Camera->GetComponentRotation().Pitch < 360) {
		Camera->SetRelativeRotation(FRotator(-10, 0, 0));
	}
	if (Camera->GetComponentRotation().Pitch < -65 && Camera->GetComponentRotation().Pitch > -200) {
		Camera->SetRelativeRotation(FRotator(-65, 0, 0));
	}
}


#pragma endregion

bool AMainPlayer::GetpointNearActor(AActor* actor, FVector& OutLocation, FRotator& OutRotator)
{
	if (!actor) return false;

	FVector DirectionFromActorToCamera = GetActorLocation() - actor->GetActorLocation();
	DirectionFromActorToCamera.Z = 0;
	DirectionFromActorToCamera.Normalize();

	OutLocation = actor->GetActorLocation() + FVector(0,0,500) /* <- Height */ + DirectionFromActorToCamera * 700 ;
	FVector DirectionFromPointLocationToActor = actor->GetActorLocation() - Camera->GetComponentLocation();
	OutRotator = UKismetMathLibrary::MakeRotFromX(DirectionFromPointLocationToActor);

	return true;
}

AMainPlayerController* AMainPlayer::GetPlayerController()
{
	return Cast<AMainPlayerController>(GetController());
}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Mouse X" , this , &AMainPlayer::INPUT_MouseX);
	PlayerInputComponent->BindAxis("Mouse Y" , this , &AMainPlayer::INPUT_MouseY);
	PlayerInputComponent->BindAxis("Up", this, &AMainPlayer::INPUT_UpDown);
	PlayerInputComponent->BindAxis("Right", this, &AMainPlayer::INPUT_RightLeft);
	PlayerInputComponent->BindAxis("Forward", this, &AMainPlayer::INPUT_ForwardBackward);
	PlayerInputComponent->BindAxis("Mouse Wheel", this, &AMainPlayer::INPUT_MouseScrol);


	PlayerInputComponent->BindAction("Ctrl",EInputEvent::IE_Pressed ,this, &AMainPlayer::INPUT_Taggle_Ctrl);



}

