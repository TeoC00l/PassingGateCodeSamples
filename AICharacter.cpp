//@Author: Teodor Tysklind / Teodor.Tysklind@Futuregames.nu

#include "AI/AICharacter.h"
#include "MyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/CustomComponents/HealthComponent.h"
#include "MagicSpells/AbilityStats.h"

AAICharacter::AAICharacter()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnTakeDamage.AddDynamic(this, &AAICharacter::OnDamageTaken);
	GetCharacterMovement()->bUseRVOAvoidance = true;
	GetCharacterMovement()->SetRVOAvoidanceWeight(RVOAvoidanceWeight);
}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->Health = HealthComponent->MaxHealth;
}

void AAICharacter::OnDamageTaken(UAbilityStats* AbilityStats)
{
	if(!AbilityStats->bPlayerProjectile)
	{
		return;
	} 
	
	HealthComponent->Health -= AbilityStats->GetDamage();
	
	if(HealthComponent->Health <= 0)
	{
		AMyAIController* AICon = Cast<AMyAIController>( GetController() );
		AICon->GetBrainComponent()->StopLogic(TEXT("DEATH"));
		OnDeath();
		HealthComponent->OnTakeDamage.RemoveDynamic(this, &AAICharacter::OnDamageTaken);
	}
}

void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

