// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyController.h"
#include "BaseEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ABaseEnemyController::BeginPlay()
{
   Super::BeginPlay();

   ABaseEnemyCharacter* Enemy = Cast<ABaseEnemyCharacter>(GetPawn());
   if (Enemy && Enemy->BTAsset)
   {
      RunBehaviorTree(Enemy->BTAsset);
      GetBlackboardComponent()->SetValueAsObject("Player", UGameplayStatics::GetPlayerCharacter(this, 0));
   }

}
