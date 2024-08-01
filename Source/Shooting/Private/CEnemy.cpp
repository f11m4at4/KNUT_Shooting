// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy.h"
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include "CPlayer.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ACEnemy::ACEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	// boxComp 를 Root 로 등록하고 싶다.
	RootComponent = BoxComp;
	// Collision Profile 설정해주기
	BoxComp->SetCollisionProfileName(TEXT("EnemyProfile"));
	// 충돌(overlap) 처리 이벤트 등록하기
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy::OnComponentBeginOverlap);

	// BodyMesh 그릇에 StaticMeshComponent 를 만들어서 담고 싶다.
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(BoxComp);
	// Collision Profile 설정해주기
	BodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); 
	
	// 사용할 Static Mesh 데이터를 읽어들여서 컴포넌트에 할당하고싶다.
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Drone/Drone_low.Drone_low'"));
	// 로딩이 성공하면
	if (TempMesh.Succeeded())
	{
		// -> BodyMesh 에 사용할 스태틱메시로 TempMesh 의 값을 넣어주고 싶다.
		BodyMesh->SetStaticMesh(TempMesh.Object);
		BodyMesh->SetRelativeLocation(FVector(50, 0, 0));
		BodyMesh->SetRelativeRotation(FRotator(0, -90, -90));
	}
}

// Called when the game starts or when spawned
void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	// 타겟을 찾고 싶다.
	target = UGameplayStatics::GetActorOfClass(GetWorld(), ACPlayer::StaticClass());

	// 아래로 방향을 설정하기
	dir = FVector(0, 0, -1);

	// 타겟이 있고 30% 의 확율안에 들어온 경우에는 타겟쪽으로
	int percent = FMath::RandRange(1, 10);
	if (IsValid(target) && percent <= 3)
	{
		// 타겟쪽으로 이동하도록 하고싶다.
		dir = target->GetActorLocation() - GetActorLocation();
		dir.Normalize();
	}
	// 타겟방향으로 회전하기
	FRotator rot = UKismetMathLibrary::MakeRotFromXZ(GetActorForwardVector(), dir);
	SetActorRotation(rot);
}

// Called every frame
void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 3. 이동하고 싶다.
	// P = P0 + vt
	FVector P0 = GetActorLocation();
	FVector vt = dir * speed * DeltaTime;
	FVector P = P0 + vt;
	SetActorLocation(P);
}

void ACEnemy::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 너도 죽고
	OtherActor->Destroy();
	// 나도 죽자
	Destroy();
}

