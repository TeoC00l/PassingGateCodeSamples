//@Author: Teodor Tysklind / Teodor.Tysklind@Futuregames.nu

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FireProjectile.generated.h"

class UAbilityStats;
class USoundCue;
class AForwardProjectile;

/**
 * Fire projectile task node.
 * Fires the specified projectile when executed.
 */
UCLASS()
class GP4PLATFORMER_API UFireProjectile : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	/** Projectile to fire */
	UPROPERTY(Category=Node, EditAnywhere)
	TSubclassOf<AForwardProjectile> ProjectileToFire;

	UPROPERTY(Category=Node, EditAnywhere)
	UAbilityStats* UAbilityStats;

	/** Delay to add before projectile is fired */
	UPROPERTY(Category=Node, EditAnywhere, meta=(ClampMin = "0.0", UIMin = "0.0"))
	float Delay;

	const float ProjectileStartOffset = 100.f;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	EBTNodeResult::Type Fire(UBlackboardComponent* BlackboardComp, UBehaviorTreeComponent& OwnerComp) const;
public:
	UFireProjectile();


};
