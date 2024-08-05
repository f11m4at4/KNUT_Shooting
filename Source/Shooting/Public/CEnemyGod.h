// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEnemyGod.generated.h"

UCLASS()
class SHOOTING_API ACEnemyGod : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACEnemyGod();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// �����ð��� �ѹ��� ���� ����� �ʹ�.
	// �ʿ�Ӽ� : �����ð�, ����ð�
	UPROPERTY(EditAnywhere, Category="MySettings")
	float createTime = 2.0f;
	float currentTime = 0;
	// ������
	UPROPERTY(EditAnywhere, Category="MySettings")
	TSubclassOf<class ACEnemy> enemyFactory;
};
