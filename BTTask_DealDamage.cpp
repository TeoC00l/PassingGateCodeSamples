//@Author: Teodor Tysklind / Teodor.Tysklind@Futuregames.nu

#include "AI/BTTasks/BTTask_DealDamage.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "AIController.h"
#include "AI/AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "MagicSpells/AbilityStats.h"

UBTTask_DealDamage::UBTTask_DealDamage()
{
	BlackboardKey.AddObjectFilter(this, "BlackboardKey", AActor::StaticClass());
}

EBTNodeResult::Type UBTTask_DealDamage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	
	UObject* KeyValue = BBComp->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
	AActor* TargetActor = Cast<AActor>(KeyValue);
	
	UHealthComponent* HealthComp = TargetActor->FindComponentByClass<UHealthComponent>();

	if(HealthComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *TargetActor->GetName());
		UE_LOG(LogTemp, Warning, TEXT("%f"), AbilityStats->GetDamage());

		HealthComp->OnTakeDamage.Broadcast(AbilityStats);
		UE_LOG(LogTemp, Warning, TEXT("%f"), HealthComp->Health);
	}
	
	return EBTNodeResult::Succeeded;
}

void UBTTask_DealDamage::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
}

FString UBTTask_DealDamage::GetStaticDescription() const
{
	return FString::Printf(TEXT("%s: '%s'"), *Super::GetStaticDescription(), AbilityStats ? *AbilityStats->GetName() : TEXT(""));
}
