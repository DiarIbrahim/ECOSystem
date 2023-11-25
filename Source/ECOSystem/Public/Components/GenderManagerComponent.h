// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ECOSystem/public/Types/ECOSystemTypes.h"
#include "GenderManagerComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionDelegate);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECOSYSTEM_API UGenderManagerComponent : public UActorComponent
{
	GENERATED_BODY()
protected:


public:	
	// Sets default values for this component's properties
	UGenderManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



	// Delegates

	/*
		broadcasted when ever this animal fallen in love with another
		called for males only
	*/
	UPROPERTY(BlueprintAssignable)
	FOnActionDelegate OnFallInLove_Male;

	/*
		broadcasted when ever this animal fallen in love with another
		called for females Only
	*/
	UPROPERTY(BlueprintAssignable)
	FOnActionDelegate OnFallInLove_Female;


	/*
		the days from the starting day of the pragnancy !
		represents the days that this female animal is pragnent from the starting of the pragnancy proccess

		-1 means this animal is not currently pragnent!
	*/
	int pragnency_day = -1;

	/*
		this is the date that this animal finishes a pragnancy process (gives birth to an other animal)
		this date callculated base on the animals age (if the animal finishes the pragnancy in age of 800 days then the date will be 800  (we are not useing the globla day as date) )

		-1 means this animal has never been in a pragnancy process!
	*/
	int lastPragnancyDate = -1;



	/*
	 The Animal that this animal makes love with
	*/
	class AAnimalBase* LoverAnimal;
	/*
	  temp Container for the animal that this animal may asked fro love
	*/
	class AAnimalBase* AskedForLoveAnimal;

	/*
		returns owner as AAnimalBase class
	*/ 
	class AAnimalBase* GetAnimal()const;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*
		called by age manager to notify the age changed and passes the @age
	*/
	virtual void OnAgeTick(int age);
	/*
		called by OnAgeTick() for Males-only
	*/
	virtual void OnAgeTick_Male(int age);
	/*
		called by OnAgeTick() for Females-only
	*/
	virtual void OnAgeTick_Female(int age);

	/*
	  calls @animalToAsk's ReceiveMakeLove()  to make love with

	  @animalToMakeLove is the animal to be asked for making love
	*/
	void AskMakeLove(class AAnimalBase* animalToAsk);

	/*
	  called by other animals when they want to make love with this animal

	  @animalToMakeLove is the animal asked for love
	*/

	void ReceiveMakeLove(class AAnimalBase* animalToMakeLove);

	/*
	   called when this animal requests/ask an other annimal for making love and other animal accepts it
	*/
	void OnLoveAcepted(class AAnimalBase* Animal);
	/*
	   called when this animal requests/ask an other annimal for making love and the other animal denies  it
	*/
	void OnLoveDenied(class AAnimalBase* Animal);

	/*
		Ask for child (this function is Male-Only )
		asks the female to make a child 
	*/
	void AskForChild();

	/*
		called by males to ask females to make child !
		@AskingAnimal is the animal to ask that request
	*/
	virtual void OnRecieveMakeChildRequest(AAnimalBase* AskingAnimal);

	/*
		starts the pragnency process
	*/
	void StartPragnency();
	
	/*
		called each day from the starting of the pragnency unril it gives berth
	*/
	void onPragnency();
	/*
		returns the percentage of the pragnency process
	*/
	float GetPragnencyPercentage() const;

	/*
		called on the last day of the pragnancy
	*/
	void GiveBirth();

	/*
		whether this animal is pragnent or not
	*/
	bool IsPragnent();

	/*
		wherther this animal is capeable to make love ?
	*/
	bool CanMakeNewLove();
	/*
		whether the asking animal is compatable for making love with this animal
	*/
	bool CanAskOrReceiveLoveRequest(AAnimalBase* AskerOrReceiverAnimal);
	
	/*
		this will be called when the partner is dead
	*/

	void OnPartnerDied();


	/*
	  whether this animal currently in love or not
	*/
	UFUNCTION(BlueprintPure)
	bool IsInLove() const;

	/*
		returns the gender of this animal
	*/
	enum EAnimalGender GetGender() const;
	
	/*
	returns the Age of this animal
	*/
	int GetAge() const;
	/*
		Returns animal common info for this animal
	*/
	struct FAnimalCommonInfo GetAnimalCommonInfo() const;


	UFUNCTION(BlueprintPure)
	class AAnimalBase* GetLover();



};
