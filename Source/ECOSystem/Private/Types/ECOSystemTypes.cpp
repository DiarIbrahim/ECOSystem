// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim


#include "Types/ECOSystemTypes.h"
#include "ECOSystem/Public/Animal/AnimalBase.h"
#include "ECOSystem/Public/Components/GenderManagerComponent.h"
#include "helpers/GenderHelper.h"


FAnimalCommonInfo FAnimalCommonInfo::MakeForNewBorn(UGenderManagerComponent* father, UGenderManagerComponent* mother)
{
	FAnimalCommonInfo info = FAnimalCommonInfo();
	info.Gender = UGenderHelper::GetRandomGender();
	return info;
}
