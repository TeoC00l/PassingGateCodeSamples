//@Author: Teodor Tysklind / Teodor.Tysklind@Futuregames.nu

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TakeDamage.generated.h"

/**
 * 
 */
UCLASS()
class GP4PLATFORMER_API UTakeDamage : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY(Category=Damage, EditAnywhere)
	class UAbilityStats* AbilityStats;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
