// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim


#include "Controllers/AnimalControllerBase.h"
#include "ECOSystem/Public/Components/AnimalPerceptionComponentBase.h"
#include "Animal/AnimalBase.h"


AAnimalControllerBase::AAnimalControllerBase()
{
	if (!Perception) {
		Perception = CreateDefaultSubobject<UAnimalPerceptionComponentBase>(FName("perception"));
	}

}

AAnimalBase* AAnimalControllerBase::GetAnimal()
{
	return Cast<AAnimalBase>(GetPawn());
}
