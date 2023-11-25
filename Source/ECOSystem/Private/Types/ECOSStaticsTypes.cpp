// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim


#include "Types/ECOSStaticsTypes.h"
#include "Animal/AnimalBase.h"

FECOSHistoryRecord FECOSHistoryRecord::MakeFromGeneralStatics(FGeneralGameStatics generalStatics)
{
	FECOSHistoryRecord instance = FECOSHistoryRecord();
	instance.NumAnimals = generalStatics.NumAnimal;
	instance.NumMales= generalStatics.numMales;
	instance.NumFemales= generalStatics.numFemales;
	instance.NumCouples= generalStatics.NumCoubles;
	instance.NumNewborns= generalStatics.NumNewBorns;
	return instance;
}
