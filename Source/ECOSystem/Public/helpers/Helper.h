// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Helper.generated.h"

/**
 * 
 */
UCLASS()
class ECOSYSTEM_API UHelper : public UObject
{
	GENERATED_BODY()

#pragma region Print

public:

	static void print(FString str) {
		GEngine->AddOnScreenDebugMessage(-1, 9, FColor::Blue, *str);
		UE_LOG(LogTemp, Error, TEXT("%s"), *str);

	}
	static void print_Inf(FString str, float v, int32 key = 122) {
		GEngine->AddOnScreenDebugMessage(key, 4, FColor::Blue, *str + FString(" : ").Append(FString::SanitizeFloat(v)));
	}
	static void print_Inf_bool(FString str, bool b, int32 key = 122) {
		GEngine->AddOnScreenDebugMessage(key, 9, FColor::Blue, *str + FString(" : ").Append(b ? "true" : "false"));
	}
	static void print_Error(FString str) {
		GEngine->AddOnScreenDebugMessage(-1, 9, FColor::Red, *str);
		UE_LOG(LogTemp, Error, TEXT("%s"), *str);
	}
	static void print(FString str, float v) {
		GEngine->AddOnScreenDebugMessage(-1, 9, FColor::Blue, *str + FString(" : ").Append(FString::SanitizeFloat(v)));
	}
	static void print(FString str, int32 v) {
		GEngine->AddOnScreenDebugMessage(-1, 9, FColor::Blue, *str + FString(" : ").Append(FString::FromInt(v)));
	}
	static void print_bool(FString str, bool b) {
		GEngine->AddOnScreenDebugMessage(-1, 9, FColor::Blue, *str + FString(" : ").Append(b ? "true" : "false"));
	}

#pragma endregion

};
