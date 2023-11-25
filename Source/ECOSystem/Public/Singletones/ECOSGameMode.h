// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Engine/DataTable.h"
#include "ECOSGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ECOSYSTEM_API AECOSGameMode : public AGameMode
{
	GENERATED_BODY()

protected:

	AECOSGameMode();

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite , EditAnywhere)
	class UGMTimeManagerComponent* timeManager;



protected:


	/*
		animal classes
	*/

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AAnimalBase> animalNewBornClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AAIController> AnimalControllerClass;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere , Category = "Statics | records")
	class UDataTable* WorldHistryRecord;


public:

	/*
		returns all animals in @OutAnimals and returns true if founds any
	*/
	bool GetAnimals(TArray<class AAnimalBase*>& OutAnimals) const;

	class AMainPlayer* GetMainPlayer() const;


	/*
		this can be calle by female animals only
		this function is called after a female animale gives birth to a new born !
	*/
	void SpawnNewBorn(class AAnimalBase* mother,struct FAnimalCommonInfo info);
	/*
		 returns a proper location to spawn new born animals 
	*/
	FVector FindLocationForNewBorn(class AAnimalBase* mother);
	

	/*
		calls to desstroy animals and their controller after the animal died
	*/

	void AnimalDied(AAnimalBase* animal);



	/*
	   the General statics of the world
	   internal use only
	*/
	struct FGeneralGameStatics GetGeneralStatics_Internal()const;

	FGeneralGameStatics GeneralStatics_lastSavedRecord;

	/*
	   the General statics of the world
	*/
	UFUNCTION(BlueprintCallable)
	struct FGeneralGameStatics GetGeneralStatics()const;

	/*
		this function can be called to record the statistics of the current date and saves them into @WorldHistoryRecord
	*/

	void SaveCurrentRecord();
	
};
