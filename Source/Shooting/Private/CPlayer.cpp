// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayer.h"

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
}
 
// Called when the game starts or when spawned
void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	int32 number1 = 200;
	int32 number2 = 5;
	UE_LOG(LogTemp, Warning, TEXT("%d"), number1 + number2);
}

// Called every frame
void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

