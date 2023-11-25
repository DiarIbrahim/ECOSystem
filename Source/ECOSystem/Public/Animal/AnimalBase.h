// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Types/ECOSystemTypes.h"
#include "Types/ECOSStaticsTypes.h"

#include "AnimalBase.generated.h"



/*
	this delegate use to fire an event while any of the datas of thi animal changed and the player can subscribe to changes (for instant UI change)
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnimalInfoChangedDelegate, FAnimalStatics, animalInfo);


UCLASS()
class ECOSYSTEM_API AAnimalBase : public ACharacter
{
	GENERATED_BODY()

public:


protected:

	/*
		Conatins all needed infos about the animal
	*/
	UPROPERTY(BlueprintReadWrite,EditAnywhere , Category = " Animal Info ")
	FAnimalCommonInfo CommonInfo;
	
	// Sets default values for this character's properties
	AAnimalBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	/*
	   Components
	*/

	UPROPERTY(BlueprintReadWrite , EditAnywhere)
	class UGenderManagerComponent* GenderManager;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UAnimalAgeManagerComponent* AgeManager;




	
public:


	/*
		Delegates
	*/
	UPROPERTY(BlueprintAssignable)
	FOnAnimalInfoChangedDelegate OnAnimalInfoChanged;


	/*
		initialize
	*/

	void InitializeAnimal(struct FAnimalInitInfo initInfo);

	/*
		can be called when ever any data changed for this animal and it will fire the OnAnimalInfoChanged delegate 
	*/
	void OnInfoChanged();

	/*
		sets the initial values for AnimalCommonInfo
	*/
	void SetCommonInfo (const FAnimalCommonInfo& info );

	/*
		This function can be called when this animal sees AnOther animal and tryes to make love with it 
	*/
	
	void makeLove(AAnimalBase* animal);


	/*
		over the age the size will chnage
		the size of new borns will continue to grow till the age meet @FAnimalCommonInfo::MatureAge
	*/
	void UpdateSizeOverAge();


	/*
		called when this animal died
	*/

	void Die();

	/*
		this will be called by the partner (if-has) about this animals death
	*/
	void ReceivePartnerDeathNotify();



	//
	/// Getters
	//

	const FAnimalCommonInfo GetCommonInfo() const { return CommonInfo;}
	class UGenderManagerComponent* GetGenderManager()const { return GenderManager; }
	class UAnimalAgeManagerComponent* GetAgeManager()const { return AgeManager; }

	struct FAnimalStatics GetAnimalStatics() const;


	

};
