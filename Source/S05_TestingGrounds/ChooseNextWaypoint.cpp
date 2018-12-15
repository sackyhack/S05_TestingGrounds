// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingCharacter.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	auto Owner = Cast<APatrollingCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, Owner->PatrolPointsCPP[Index]);
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, (Index + 1) % Owner->PatrolPointsCPP.Num());

	UE_LOG(LogTemp, Warning, TEXT("Waypoint Index: %i"), Index);

	return EBTNodeResult::Succeeded;
}
