// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TimeHelper.generated.h"

/**
 * 
 */
UCLASS()
class ECOSYSTEM_API UTimeHelper : public UObject
{
	GENERATED_BODY()

	

public:
	/*
	 Converts age to year  returns 0 if it is completes a full year (365)
	*/ 
	UFUNCTION(BlueprintPure)
	static int32 AgeAsYear(const int32& age);
	/*
	 Converts age to month  returns 0 if it is completes a full month (30)
	*/
	UFUNCTION(BlueprintPure)
	static int32 AgeAsMonth(const int32& age);

	/*
	 Converts age to human readable Text  (e.g. 1 year and 6 months and 2 days)
	 @bIncludeMonth whther to include months  (e.g. 1 year and 6 months )
	 @bIncludeDays  whther to include Days (e.g. 1 year and 6 months and 1 day)

	*/
	UFUNCTION(BlueprintPure)
	static FString AgeToString(const int32& age , bool bIncludeMonth = true , bool bIncludeDays = true);



};
