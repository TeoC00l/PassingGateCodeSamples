//@Author: Teodor Tysklind / Teodor.Tysklind@Futuregames.nu

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_DealDamage.generated.h"

/**
 * 
 */
UCLASS()
class GP4PLATFORMER_API UBTTask_DealDamage : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_DealDamage();

	UPROPERTY(Category=Damage, EditAnywhere)
	class UAbilityStats* AbilityStats;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual FString GetStaticDescription() const override;
};
