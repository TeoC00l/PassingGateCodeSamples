//@Author: Teodor Tysklind / Teodor.Tysklind@Futuregames.nu

#include "AI/BTTasks/TakeDamage.h"
#include "AIController.h"
#include "AI/AICharacter.h"

EBTNodeResult::Type UTakeDamage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(AbilityStats == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	AAICharacter* AI = Cast<AAICharacter>( OwnerComp.GetAIOwner()->GetPawn() );
	UHealthComponent* HealthComp = Cast<UHealthComponent>( AI->GetComponentByClass(UHealthComponent::StaticClass() ) );

	if(HealthComp == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	HealthComp->OnTakeDamage.Broadcast(AbilityStats);

	return EBTNodeResult::Succeeded;
}
