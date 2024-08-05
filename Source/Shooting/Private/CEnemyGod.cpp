// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemyGod.h"
#include <CEnemy.h>

// Sets default values
ACEnemyGod::ACEnemyGod()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACEnemyGod::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACEnemyGod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �����ð��� �ѹ��� ���� ����� �ʹ�.
	// 1. �ð��� �귶���ϱ�
	currentTime += DeltaTime;
	// 2. ������ �����ϱ�
	// -> ���� ����ð��� �����ð��� �ʰ��ߴٸ�
	if (currentTime > createTime)
	{
		// 3. ���� ����� �ʹ�.
		GetWorld()->SpawnActor<ACEnemy>(enemyFactory,
			GetActorLocation(), FRotator());
		// 4. �ð� �ʱ�ȭ �ϱ�
		currentTime = 0;
	}
}

