// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ECOSystemTypes.generated.h"



///
///  GENDER
/// 

UENUM(BlueprintType)
enum EAnimalGender {
		EGender_NONE = 0 UMETA(DisplayName = "NONE"),
		EGender_Male     UMETA(DisplayName = "Male"),
		EGender_Female   UMETA(DisplayName = "Female")
};

///  GENDER END


// COMMON Animal Data/Info

USTRUCT(BlueprintType)
struct FAnimalCommonInfo{
	GENERATED_BODY()
	/*
		default constructor
	*/ 
	FAnimalCommonInfo(){}
	
	/*
		 to make an inherited FAnimalCommonInfo for a new born animal from parents !
	*/
	static FAnimalCommonInfo MakeForNewBorn(class UGenderManagerComponent* father, class UGenderManagerComponent* mother);


	/*
		animals gender
	*/
	UPROPERTY(BlueprintReadWrite , EditAnywhere)
	TEnumAsByte<EAnimalGender> Gender;
	/*
		 how long can this animal live (default: 1825 days (5 years) ) (in days)
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxAge = 1825;
	/*
	* the age that the animal is considered as mature enough 
		in this age the animals can have partner(mature enogh ?) and make chaild  (default: 365 days )(in days)
		and they are grown in to their full body size
	*/ 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MatureAge = 365;

	/*
		 ChildFeverRate  is a property taht controls how offten males ask for child (Male-Only) (default: male askes for baby once each 3 days)(in days)
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 ChildFeverRate = 3;


	/*
		how logn it takes for this animal to give birth to a child (Female-Only)(in days)
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 DaysToGiveBirth = 120;

	/*
		period to take an other berth (FeMale-Only)(default: 50)(in days)
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 periodToNextBerth = 50;

	/*
		ChildFeverRequestAcceptance is the ratio of the females acceptance rate for ChildFever Request by males (FeMale-Only)(default: 0.6  (%60) )(in days)
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ChildFeverRequestAcceptanceRate = 0.6;
	/*
		minimal scale of the baby animal
		the baby animal will be scaled down to this scale when they are a newborn
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float minimalScale = 0.3;

};


/*
	data to init an animal while creating a new animal sometimes you want to add infos you want or change existing infos for a animal BP (e.g. starting age, gender)
	datas included : starting age,
*/ 

USTRUCT(BlueprintType)
struct FAnimalInitInfo{
	GENERATED_BODY()

	/*
		the age  (in days)
		if the data of @startingAge is anything except -1 the the age of the animal will be modified

	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int startingAge = -1;
	
	/*
		Gender of the animal
		if the data of @desiredGender is anything except EGender_NONE the the gender of the animal will be modified 
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EAnimalGender> desiredGender = EAnimalGender::EGender_NONE;


};




//  animal assset container Struct

USTRUCT(BlueprintType)
struct FAnimalAssetsData {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AAnimalBase> animalClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString AnimalName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* AssetImage;

};


UCLASS()
class ECOSYSTEM_API UECOSystemTypes : public UObject
{
	GENERATED_BODY()
	
};
