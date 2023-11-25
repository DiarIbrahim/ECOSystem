// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim


#include "Components/AnimalPerceptionComponentBase.h"
#include "ECOSystem/Public/Animal/AnimalBase.h"
#include "Controllers/AnimalControllerBase.h"
#include "Helpers/Helper.h"



void UAnimalPerceptionComponentBase::BeginPlay()
{
	Super::BeginPlay();
	OnTargetPerceptionUpdated.AddDynamic(this , &UAnimalPerceptionComponentBase::OnAnimalPreceptionUpdate);
}

void UAnimalPerceptionComponentBase::OnAnimalPreceptionUpdate(AActor* actor, FAIStimulus Stimulus) {

	if (!GetAnimalController() || !GetAnimalController()->GetAnimal()) return;

	if (actor && Cast<AAnimalBase>(actor)) {
		GetAnimalController()->GetAnimal()->makeLove(Cast<AAnimalBase>(actor));
	}
}

AAnimalControllerBase* UAnimalPerceptionComponentBase::GetAnimalController()
{
	return Cast<AAnimalControllerBase>(GetOwner());
}
