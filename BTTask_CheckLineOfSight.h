//@Author Teodor Tysklind / Teodor.Tysklind@FutureGames.nu

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CheckLineOfSight.generated.h"

/**
* Sweeps area between AI and target, ignoring projectiles.
*/
UCLASS()
class GP4PLATFORMER_API UBTTask_CheckLineOfSight : public UBTTaskNode
{
	GENERATED_BODY()
	
public:	
	UBTTask_CheckLineOfSight();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

private:
	/** Target to check for LOS */
	UPROPERTY(EditAnywhere, Category=LineOfSightCheck, meta=(AllowPrivateAccess="true"))
	struct FBlackboardKeySelector Target;
		
	/** Outputs result of LOS check into a key of type Bool */
	UPROPERTY(EditAnywhere, Category=LineOfSightCheck, meta=(AllowPrivateAccess="true"))
	struct FBlackboardKeySelector Output;

	/** Radius of sphere to sweep area */
	UPROPERTY(EditAnywhere, Category=LineOfSightCheck, meta=(ClampMin = "0.0", UIMin = "0.0"))
	float SweepRadius;

	bool PerformSweep(UBehaviorTreeComponent& OwnerComp) const;	
};
