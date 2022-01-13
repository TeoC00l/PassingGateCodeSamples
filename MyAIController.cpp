//@Author: Teodor Tysklind / Teodor.Tysklind@Futuregames.nu

#include "AI/MyAIController.h"
#include "AICharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/Wizard.h"

AMyAIController::AMyAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
}

void AMyAIController::SetUpBBKeys()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	if(!PC)
	{
		UE_LOG(LogTemp, Warning, TEXT(" %s: Player controller not found."), *GetName());
		return;
	}

	AWizard* Player = Cast<AWizard>(PC->GetPawn());

	if(!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Failed to get player pawn from controller."), *GetName());
		return;
	}

	BlackboardComponent->SetValueAsObject("Player", Player);
	BlackboardComponent->SetValueAsObject("SelfActor", GetPawn());

	BehaviorTreeComponent->StartTree(*AICharacter->BehaviorTree);
}

void AMyAIController::OnPossess(APawn *InPawn)
{
	Super::OnPossess(InPawn);

	AICharacter = Cast<AAICharacter>(InPawn);

	check(AICharacter);

	BlackboardComponent->InitializeBlackboard(*AICharacter->BehaviorTree->BlackboardAsset);

	FTimerHandle BBTimer;
	FTimerDelegate BBTimerDelegate;
	BBTimerDelegate.BindUFunction(this, "SetUpBBKeys");
	GetWorldTimerManager().SetTimer(BBTimer, BBTimerDelegate, 1.0f, false, InitialDelay);
}
