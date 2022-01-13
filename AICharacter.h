//@Author: Teodor Tysklind / Teodor.Tysklind@Futuregames.nu

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Player/CustomComponents/HealthComponent.h"
#include "AICharacter.generated.h"

class UHealthComponent;
class UBehaviorTree;

UCLASS()
class GP4PLATFORMER_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAICharacter();

	UPROPERTY(EditAnywhere, Category=AI)
	UBehaviorTree* BehaviorTree;

	UFUNCTION(BlueprintImplementableEvent)
    void OnAttack();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeath();
	
private:
	UPROPERTY(EditAnywhere)
	UHealthComponent* HealthComponent;

	UFUNCTION()
	void OnDamageTaken(UAbilityStats* AbilityStats);

	const float RVOAvoidanceWeight = 0.5f;
};