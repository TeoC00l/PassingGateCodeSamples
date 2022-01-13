//@Author: Teodor Tysklind / Teodor.Tysklind@Futuregames.nu

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Player/CustomComponents/HealthComponent.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class GP4PLATFORMER_API AMyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMyAIController();
		
	UPROPERTY()
	class AAICharacter* AICharacter;

	FORCEINLINE UBlackboardComponent* GetBlackBoardComp() const {return BlackboardComponent;}

private:
	UPROPERTY()
	UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY()
	UBlackboardComponent* BlackboardComponent;

	UFUNCTION()
	void SetUpBBKeys();
	
	virtual void OnPossess(APawn* InPawn) override;

	const float InitialDelay = 0.5f;
};
