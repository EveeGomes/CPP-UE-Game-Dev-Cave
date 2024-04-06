// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_EnemyBasicShoot.h"
#include "BaseEnemyCharacter.h"
#include "AIController.h"


EBTNodeResult::Type UBTT_EnemyBasicShoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
   // Get the controller that this behavior tree is running on.
   //    For that we can get the character that that controller is linked to!

   // So, we make an AI controller
   AAIController* Controller = OwnerComp.GetAIOwner();
   // Get a reference of a BaseEnemyCharacter:
   ABaseEnemyCharacter* Enemy = Cast<ABaseEnemyCharacter>(Controller->GetPawn());

   Enemy->ShootBullet(Controller->GetPawn()->GetActorForwardVector());

   return EBTNodeResult::Type();
}
