//@Author: Teodor Tysklind / Teodor.Tysklind@Futuregames.nu

#include "AI/BTTasks/FireProjectile.h"
#include "AI/AICharacter.h"
#include "AI/MyAIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Kismet/GameplayStatics.h"
#include "MagicSpells/Projectile/ForwardProjectile.h"

UFireProjectile::UFireProjectile()
{
	NodeName = "FireProjectile";
}

EBTNodeResult::Type UFireProjectile::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMyAIController* AIcon = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	
	if(!AIcon)
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BlackboardComp = AIcon->GetBlackBoardComp();

	if(!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	AAICharacter* AI = Cast<AAICharacter>(AIcon->GetPawn());
	AI->OnAttack();

	return Fire(BlackboardComp, OwnerComp);

}

EBTNodeResult::Type UFireProjectile::Fire(UBlackboardComponent* BlackboardComp, UBehaviorTreeComponent& OwnerComp) const
{
	UObject* KeyValue = BlackboardComp->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
	AActor* TargetActor = Cast<AActor>(KeyValue);
	
	FVector TargetLocation = FVector::ZeroVector;

	if(TargetActor)
	{
		TargetLocation = TargetActor->GetActorLocation();
	}
	else if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
	{
		TargetLocation = BlackboardComp->GetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID());
	}

	const FVector OwnerLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
	const FVector Direction(TargetLocation.X - OwnerLocation.X, TargetLocation.Y - OwnerLocation.Y, 0);
	const FVector DirectionNormal = Direction.GetSafeNormal();

	const FVector StartLocation = OwnerLocation + DirectionNormal * ProjectileStartOffset;
	
	if (TargetLocation == FVector::ZeroVector)
	{
		return EBTNodeResult::Failed;
	}

	const FRotator Rotator = OwnerComp.GetAIOwner()->GetPawn()->K2_GetActorRotation();
	const FActorSpawnParameters SpawnParameters;
		
	GetWorld()->SpawnActor<AForwardProjectile>(ProjectileToFire, StartLocation, Rotator, SpawnParameters);

	return EBTNodeResult::Succeeded;
}
