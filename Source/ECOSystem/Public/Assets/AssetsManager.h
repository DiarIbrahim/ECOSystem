// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ECOSystem/public/Types/ECOSystemTypes.h"
#include "AssetsManager.generated.h"

UCLASS()
class ECOSYSTEM_API UAssetsManager : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite ,EditAnywhere)
	TArray<FAnimalAssetsData> animals;
	

};
