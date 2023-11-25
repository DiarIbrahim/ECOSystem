// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim


#include "helpers/GenderHelper.h"
#include "Animal/AnimalBase.h"
#include "Components/GenderManagerComponent.h"


EAnimalGender UGenderHelper::GenderFromInt(int32 genderinInt)
{
    if (genderinInt == 0) return EAnimalGender::EGender_Male;
    else if (genderinInt == 1) return EAnimalGender::EGender_Female;
    else return EAnimalGender::EGender_NONE;
}

int32 UGenderHelper::GenderToInt(EAnimalGender gender)
{
    switch (gender)
    {
    case EGender_NONE:
        return -1;
        break;
    case EGender_Male:
        return 0;
        break;
    case EGender_Female:
        return 1;
        break;
    default:
        return -1;
        break;
    }
}

bool UGenderHelper::CanMakeLove(AAnimalBase* A, AAnimalBase* B)
{
    if (!A || !B) return false;
    return CanMakeLove(A->GetGenderManager(), B->GetGenderManager());
}
bool UGenderHelper::CanMakeLove(UGenderManagerComponent* A, UGenderManagerComponent* B)
{
    if (!A || !B) return false;

    return CanMakeLove(A->GetGender(), B->GetGender());
}
bool UGenderHelper::CanMakeLove(EAnimalGender A, EAnimalGender B)
{
    return A == EGender_Female && B == EGender_Male || B == EGender_Female && A == EGender_Male;
}
