//@Author: Teodor Tysklind / Teodor.Tysklind@FutureGames.nu

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Set_Rotation_Flanking.generated.h"

/**
 * Sets the AI:s rotation towards target given LOS, otherwise in movement direction.
 */
UCLASS()
class GP4PLATFORMER_API UBTService_Set_Rotation_Flanking : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_Set_Rotation_Flanking();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

private:
	/** Target to rotate towards */
	UPROPERTY(EditAnywhere, Category=Rotation, meta=(AllowPrivateAccess="true"))
	struct FBlackboardKeySelector AttackTarget;
	
	/** Position AI moving towards*/
	UPROPERTY(EditAnywhere, Category=Rotation, meta=(AllowPrivateAccess="true"))
	struct FBlackboardKeySelector MovementTarget;

	UPROPERTY(EditAnywhere, Category=Rotation, meta=(AllowPrivateAccess="true"))
	struct FBlackboardKeySelector HasLineOfSightKey;

	UPROPERTY()
	FQuat TargetQuat;

	void Rotate(UBehaviorTreeComponent& OwnerComp) const;
	void FindTargetRotation(UBehaviorTreeComponent& OwnerComp);

	const float StopRotatingAtDistance = 200.f;
};
