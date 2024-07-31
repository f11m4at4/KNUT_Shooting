// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayer.h"
#include <CBullet.h>

// Sets default values
ACPlayer::ACPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// BodyMesh �׸��� StaticMeshComponent �� ���� ��� �ʹ�.
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	// BodyMesh �� Root �� ����ϰ� �ʹ�.
	RootComponent = BodyMesh;

	SpaceShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpaceShipMesh"));
	SpaceShipMesh->SetupAttachment(BodyMesh);

	// ����� Static Mesh �����͸� �о�鿩�� ������Ʈ�� �Ҵ��ϰ�ʹ�.
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("/Script/Engine.StaticMesh'/Game/SpaceShip/Spaceship_ARA.Spaceship_ARA'"));
	// �ε��� �����ϸ�
	if(TempMesh.Succeeded())
	{
		// -> SpaceShipMesh �� ����� ����ƽ�޽÷� TempMesh �� ���� �־��ְ� �ʹ�.
		SpaceShipMesh->SetStaticMesh(TempMesh.Object);
		// ��ġ���� �����ϰ� �ʹ�.
		SpaceShipMesh->SetRelativeRotation(FRotator(0, 90, 90));
		// ũ�Ⱚ�� �����ϰ� �ʹ�.
		SpaceShipMesh->SetRelativeScale3D(FVector(6));
	}

	// �ѱ� ������Ʈ ����ϱ�
	FirePosition = CreateDefaultSubobject<USceneComponent>(TEXT("FirePosition"));
	FirePosition->SetupAttachment(BodyMesh);
	FirePosition->SetRelativeLocation(FVector(0, 0, 80));
}
 
// Called when the game starts or when spawned
void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ����ڰ� �����¿�Ű�� ������ �� �������� �̵��ϰ� �ʹ�.
	// 1. ����� �Է¿� ����
	// 2. ������ �ʿ��ϴ�.
	// -> ������ ����
	FVector dir(0, h, v);
	// 3. �̵��ϰ� �ʹ�.
	// P = P0 + vt
	FVector P0 = GetActorLocation();
	FVector vt = dir * speed * DeltaTime;
	FVector P = P0 + vt;
	SetActorLocation(P);
}

// Called to bind functionality to input
void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// �¿��Է� Horizontal �Է��� ������ ó���� �Լ��� Horizontal �Լ��� ���������
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ACPlayer::Horizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ACPlayer::Vertical);
	// �Ѿ˹߻� ��ư �Է°� ó���Լ��� ��������.
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ACPlayer::Fire);
}

void ACPlayer::Horizontal(float value)
{
	h = value;
}

void ACPlayer::Vertical(float value)
{
	v = value;
}

// ����ڰ� �߻� ��ư�� ������ ��
void ACPlayer::Fire()
{
	// �Ѿ��� �߻��ϰ� �ʹ�.
	// 1. �Ѿ��� �־���Ѵ�.
	// 2. �Ѿ��� �߻��ϰ� �ʹ�.
	// -> �Ѿ��� ����� �ѱ���ġ�� ��ġ�Ѵ�.
	GetWorld()->SpawnActor<ACBullet>(bulletFactory, 
				FirePosition->GetComponentLocation(), FRotator());
}

