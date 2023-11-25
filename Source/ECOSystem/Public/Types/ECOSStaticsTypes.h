// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "ECOSStaticsTypes.generated.h"

class AAnimalBase;

/**
 *   all structs and types needed to represent datas of the game to UI or for saving purpose
 */





/*
		General Game Statics
		holds general datas for overall review of the game 
		datas : {number of amnimals , types of animals , number per types , gender ratio  and more}

		datas will be gathered from gamemode  (see ECOSGameMode.h)
*/
USTRUCT(BlueprintType)
struct FGeneralGameStatics{
	GENERATED_BODY();

	/*
		total number of animals in the World
	*/ 
	UPROPERTY(BlueprintReadOnly , VisibleAnywhere)
	int32 NumAnimal;
	/*
		number of females animals
	*/ 
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 numMales;
	/*
		number of Male animals
	*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 numFemales;

	/*
		number of the new born animals (age between 1day to 30 days)
	*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 NumNewBorns;
	/*
		number of couple animals
	*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 NumCoubles;


};

/*
	FAnimalStatics 
	All statics and datas available for an animal
	datas : {Gender , Age , RelationShip and more}
*/
USTRUCT(BlueprintType)
struct FAnimalStatics {
	GENERATED_BODY();

	FAnimalStatics(){}

	// age in days
	UPROPERTY(BlueprintReadOnly)
	int32 Age;
	// age in days in String Format
	UPROPERTY(BlueprintReadOnly)
	FString AgeString;
	// Gennder in int (0 = male , 1 = female  else = unknown)
	UPROPERTY(BlueprintReadOnly)
	int32 Gedner;
	// wheather this animal is in love
	UPROPERTY(BlueprintReadOnly)
	bool bIsInLove;
	/*
		whether this animal is pragnent or not
	*/
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsPragnent;
	UPROPERTY(BlueprintReadOnly)
	float PragnencyPercentage;


};


/*
	history records
	stores world statics along with date

*/

USTRUCT(BlueprintType)
struct FECOSHistoryRecord : public FTableRowBase {
	GENERATED_BODY();


	FECOSHistoryRecord() {}

	static FECOSHistoryRecord MakeFromGeneralStatics(struct FGeneralGameStatics generalStatics);

	/*
		the date(in days) that the record captured
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 Date = 0;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 NumAnimals = 0;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 NumMales = 0;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 NumFemales = 0;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 NumCouples = 0;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 NumNewborns = 0;



};
