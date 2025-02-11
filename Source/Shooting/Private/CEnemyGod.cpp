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

	// 일정시간에 한번씩 적을 만들고 싶다.
	// 1. 시간이 흘렀으니까
	currentTime += DeltaTime;
	// 2. 생성이 됐으니까
	// -> 만약 경과시간이 생성시간을 초과했다면
	if (currentTime > createTime)
	{
		// 3. 적을 만들고 싶다.
		GetWorld()->SpawnActor<ACEnemy>(enemyFactory,
			GetActorLocation(), FRotator());
		// 4. 시간 초기화 하기
		currentTime = 0;
	}
}

