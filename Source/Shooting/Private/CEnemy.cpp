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
	// boxComp �� Root �� ����ϰ� �ʹ�.
	RootComponent = BoxComp;
	// Collision Profile �������ֱ�
	BoxComp->SetCollisionProfileName(TEXT("EnemyProfile"));
	// �浹(overlap) ó�� �̺�Ʈ ����ϱ�
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy::OnComponentBeginOverlap);

	// BodyMesh �׸��� StaticMeshComponent �� ���� ��� �ʹ�.
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(BoxComp);
	// Collision Profile �������ֱ�
	BodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); 
	
	// ����� Static Mesh �����͸� �о�鿩�� ������Ʈ�� �Ҵ��ϰ�ʹ�.
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Drone/Drone_low.Drone_low'"));
	// �ε��� �����ϸ�
	if (TempMesh.Succeeded())
	{
		// -> BodyMesh �� ����� ����ƽ�޽÷� TempMesh �� ���� �־��ְ� �ʹ�.
		BodyMesh->SetStaticMesh(TempMesh.Object);
		BodyMesh->SetRelativeLocation(FVector(50, 0, 0));
		BodyMesh->SetRelativeRotation(FRotator(0, -90, -90));
	}
}

// Called when the game starts or when spawned
void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	// Ÿ���� ã�� �ʹ�.
	target = UGameplayStatics::GetActorOfClass(GetWorld(), ACPlayer::StaticClass());

	// �Ʒ��� ������ �����ϱ�
	dir = FVector(0, 0, -1);

	// Ÿ���� �ְ� 30% �� Ȯ���ȿ� ���� ��쿡�� Ÿ��������
	int percent = FMath::RandRange(1, 10);
	if (IsValid(target) && percent <= 3)
	{
		// Ÿ�������� �̵��ϵ��� �ϰ�ʹ�.
		dir = target->GetActorLocation() - GetActorLocation();
		dir.Normalize();
	}
	// Ÿ�ٹ������� ȸ���ϱ�
	FRotator rot = UKismetMathLibrary::MakeRotFromXZ(GetActorForwardVector(), dir);
	SetActorRotation(rot);
}

// Called every frame
void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 3. �̵��ϰ� �ʹ�.
	// P = P0 + vt
	FVector P0 = GetActorLocation();
	FVector vt = dir * speed * DeltaTime;
	FVector P = P0 + vt;
	SetActorLocation(P);
}

void ACEnemy::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �ʵ� �װ�
	OtherActor->Destroy();
	// ���� ����
	Destroy();
}

