// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GMTimeManagerComponent.generated.h"


/*
		The Time in this game will be mesured with days
		the time is tick in a spisific interval
		after each Tick interval the MakeATimeTick() will be called and then all animals will be notified about the time tick

*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECOSYSTEM_API UGMTimeManagerComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	class AECOSGameMode* GetGameMode();

public:	
	// Sets default values for this component's properties
	UGMTimeManagerComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*  Variables */

	// Time  in days ( set to -1 as a wormup)
	int32 Time = - 1;
	
	// this is the interval between smallest time tick in this game  ( in this case TimeTickIntervalInSec == 5  , each 1 hour in real life is 2 yeasr in the game !)
	float TimeTickIntervalInSec = 5;
	/* 
		this is how fast the time ticks (effects @TimeTickIntervalInSec ) 
		TimeTickIntervalInSec = @TimeTickIntervalInSec/@SpeedRate )
		(bigger @SpeedRate smaller tick interval)
	*/
	float SpeedRate = 1;

	// makes a tick
	void MakeATimeTick();
	// notifies the tick
	void NotifyTimeTick();

	
	/*
		updates the time tick interval
		@newSpeedRate is either 1x, 2x, 5x, 10x, 20x or 60x (whitch means x times faster of the initial @TimeTickIntervalInSec  )
	*/
	UFUNCTION(BlueprintCallable)
	void UpdateTimeTickInterval(int32 newSpeedRate);

	// Getters

	int32 GetDate() const { return Time; }

	
};
