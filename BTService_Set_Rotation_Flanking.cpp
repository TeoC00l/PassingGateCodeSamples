//@Author: Teodor Tysklind / Teodor.Tysklind@FutureGames.nu

#include "AI/BTTasks/BTService_Set_Rotation_Flanking.h"
#include "AIController.h"
#include "AI/AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_Set_Rotation_Flanking::UBTService_Set_Rotation_Flanking()
{
	bNotifyTick = true;

	HasLineOfSightKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_Set_Rotation_Flanking, HasLineOfSightKey));
	AttackTarget.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_Set_Rotation_Flanking,AttackTarget), AActor::StaticClass());
	MovementTarget.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_Set_Rotation_Flanking, MovementTarget));
}

void UBTService_Set_Rotation_Flanking::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	float DeltaSeconds)
{
	UBlackboardComponent* BBComp = OwnerComp.GetAIOwner()->GetBlackboardComponent();

	const bool bIsLOSKeyValid = BBComp->IsValidKey(HasLineOfSightKey.GetSelectedKeyID());
	const bool bIsAttackTargetValid = BBComp->IsValidKey(AttackTarget.GetSelectedKeyID());
	const bool bIsMovementTargetValid = BBComp->IsValidKey(MovementTarget.GetSelectedKeyID());

	if(!bIsLOSKeyValid || !bIsAttackTargetValid || !bIsMovementTargetValid)
	{
		return;
	}
	
	FindTargetRotation(OwnerComp);
	Rotate(OwnerComp);
}

void UBTService_Set_Rotation_Flanking::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBAsset = GetBlackboardAsset();

	if(ensure(BBAsset))
	{
		AttackTarget.ResolveSelectedKey(*BBAsset);
		MovementTarget.ResolveSelectedKey(*BBAsset);
		HasLineOfSightKey.ResolveSelectedKey(*BBAsset);
	}
}

void UBTService_Set_Rotation_Flanking::Rotate(UBehaviorTreeComponent& OwnerComp) const
{
	AAIController* AIcon = Cast<AAIController>(OwnerComp.GetAIOwner());
	AAICharacter* AI = Cast<AAICharacter>(AIcon->GetPawn());

	AI->SetActorRotation(TargetQuat);
}

void UBTService_Set_Rotation_Flanking::FindTargetRotation(UBehaviorTreeComponent& OwnerComp)
{
	UBlackboardComponent* BBComp = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	AAIController* AIcon = Cast<AAIController>(OwnerComp.GetAIOwner());
	AAICharacter* AI = Cast<AAICharacter>(AIcon->GetPawn());

	const bool bHasLos = BBComp->GetValueAsBool(HasLineOfSightKey.SelectedKeyName);

	AActor* TargetActor = Cast<AActor>(BBComp->GetValueAsObject(AttackTarget.SelectedKeyName));
	const FVector TargetLocation = TargetActor->GetActorLocation();

	const float SqDist = FVector::DistSquared(AI->GetActorLocation(), TargetLocation);

	const FQuat CurrentQuat = AI->GetActorQuat();

	if(SqDist < (StopRotatingAtDistance*StopRotatingAtDistance) && !bHasLos)
	{
		TargetQuat = CurrentQuat;
		return;
    }
	
	FVector Dir = (TargetLocation - AIcon->GetPawn()->GetActorLocation());
	Dir.Z = 0.f;
	const FVector DirNormalized = Dir.GetSafeNormal();

	TargetQuat = DirNormalized.Rotation().Quaternion();
}
