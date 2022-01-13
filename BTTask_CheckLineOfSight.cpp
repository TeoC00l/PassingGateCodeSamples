//@Author Teodor Tysklind / Teodor.Tysklind@FutureGames.nu

#include "AI/BTTasks/BTTask_CheckLineOfSight.h"

#include "AI/AICharacter.h"
#include "AI/MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MagicSpells/BaseSpell.h"
#include "MagicSpells/Projectile/ForwardProjectile.h"
#include "Player/Wizard.h"

UBTTask_CheckLineOfSight::UBTTask_CheckLineOfSight()
{
	bCreateNodeInstance = true;
	Output.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_CheckLineOfSight,Output));
	Target.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_CheckLineOfSight, Target), AActor::StaticClass());
}

EBTNodeResult::Type UBTTask_CheckLineOfSight::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetAIOwner()->GetBlackboardComponent();


	const bool bIsTargetValid = BBComp->IsValidKey(Target.GetSelectedKeyID());
	const bool bIsOutputValid = BBComp->IsValidKey(Output.GetSelectedKeyID());

	if (!bIsTargetValid || !bIsOutputValid)
	{
		UE_LOG(LogTemp, Warning, TEXT("BTService_CheckLineOfSight key(s) is set to invalid value" ));
	}
	else
	{
		BBComp->SetValueAsBool( Output.SelectedKeyName, PerformSweep(OwnerComp) );
	}
	
	return EBTNodeResult::Succeeded;
}

bool UBTTask_CheckLineOfSight::PerformSweep(UBehaviorTreeComponent& OwnerComp) const
{
	UBlackboardComponent* BBComp = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	AMyAIController* AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());

	AActor* TargetActor = Cast<AActor>(BBComp->GetValueAsObject(Target.SelectedKeyName));

	const FVector Start = AICon->GetPawn()->GetActorLocation();
	const FVector End = TargetActor->GetActorLocation();

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(AICon->GetPawn());

	const FCollisionShape SweepSphere = FCollisionShape::MakeSphere(SweepRadius);
	TArray<FHitResult> OutResults;

	GetWorld()->SweepMultiByChannel
	(
		OutResults,
		Start,
		End,
		FQuat::Identity,
		ECC_Camera,
		SweepSphere
	);

	bool bHasLineOfSight = true;

	for (FHitResult Hit : OutResults)
	{
		if (Hit.GetActor()->IsA(ABaseSpell::StaticClass()))
		{
			continue;
		}

		if(Hit.GetActor()->GetName() == AICon->GetPawn()->GetName())
		{
			continue;
		}

		if (Hit.GetActor()->IsA(AForwardProjectile::StaticClass()))
		{
			continue;
		}

		if ( Hit.GetActor()->IsA(AWizard::StaticClass()))
		{
			continue;
		}

		bHasLineOfSight = false;
		break;
	}

	return bHasLineOfSight;
}


void UBTTask_CheckLineOfSight::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBAsset = GetBlackboardAsset();

	if (ensure(BBAsset))
	{
		Target.ResolveSelectedKey(*BBAsset);
		Output.ResolveSelectedKey(*BBAsset);
	}
}
