// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "types/ECOSystemTypes.h"
#include "GenderHelper.generated.h"

/**
 * 
 */
UCLASS()
class ECOSYSTEM_API UGenderHelper : public UObject
{
	GENERATED_BODY()
	
	

public:

	// Coverting gender enum to string
	UFUNCTION(BlueprintPure)
	static FString GenderAsString(TEnumAsByte<EAnimalGender> type) {
		switch (type)
		{
		case EAnimalGender::EGender_NONE:
			return "Unspecified";
		case EAnimalGender::EGender_Male:
			return "Male";
		case EAnimalGender::EGender_Female:
			return "Female";

		default:
			return "Unspecified";
		}
	}

	// converting String to Enum
	UFUNCTION(BlueprintPure)
	static TEnumAsByte<EAnimalGender> GenderFromString(FString genderString) {
		if (genderString.Equals("male")) return  EAnimalGender::EGender_Male;
		else if (genderString.Equals("female")) return EAnimalGender::EGender_Female;
		else return EAnimalGender::EGender_NONE;
	}

	// returns random Gender
	UFUNCTION(BlueprintPure)
	static TEnumAsByte<EAnimalGender> GetRandomGender() {
		if (FMath::RandBool()) return EAnimalGender::EGender_Male;
		else return EAnimalGender::EGender_Female;
	}

	// wheather to Animals Can make Love (be partners)
	UFUNCTION(BlueprintPure, meta = (DesplayName = "CanMakeLove Enum"))
	static bool CanMakeLove(EAnimalGender A, EAnimalGender B);
	static bool CanMakeLove(class UGenderManagerComponent* A, class UGenderManagerComponent* B);
	static bool CanMakeLove(class AAnimalBase* A, class AAnimalBase* B);

	// Gender from Int  
	// converts int to EAnimalGender   {e.g.  0 = male , 1 = female , else = unknown}
	UFUNCTION(BlueprintPure)
	static EAnimalGender GenderFromInt(int32 genderinInt);

	// Gender To Int  
	// converts EAnimalGender   to int {e.g.  0 = male , 1 = female , else = unknown
	UFUNCTION(BlueprintPure)
	static int32 GenderToInt(EAnimalGender gender);
};


