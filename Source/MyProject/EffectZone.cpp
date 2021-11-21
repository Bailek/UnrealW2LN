// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectZone.h"
#include "GameFramework/Character.h"
#include "MyProjectCharacter.h"
#include <iostream>

// Sets default values
AEffectZone::AEffectZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneMesh(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NomMesh"));
	TrigerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("NomTriger"));
	if (PlaneMesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(PlaneMesh.Object);
	}

	StaticMesh->SetSimulatePhysics(false);
	TrigerBox->SetCollisionProfileName(TEXT("Trigger"), true);
	
	TrigerBox->OnComponentBeginOverlap.AddDynamic(this, &AEffectZone::OnOverlapBegin);
	
	RootComponent = StaticMesh;
}

// Called when the game starts or when spawned
void AEffectZone::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEffectZone::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	AMyProjectCharacter* Player = Cast<AMyProjectCharacter>(OtherActor);
	Player->Death();
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	
	if (Character == nullptr)
		return;
	takeModifierLife(Character);
}

void AEffectZone::takeModifierLife(class AActor* OtherActor)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);

	if (Character == nullptr)
		return;
	AMyProjectCharacter* Player = Cast<AMyProjectCharacter>(OtherActor);
	Player->LifeModifier(amoutLifeModifier);
	std::cout << "Player life is " << Player->currentHP << std::endl;
	//delay 0,5 second = 500 ms GetWorldTimerManager().SetTimer(HarvestTimerHandle, this, &ACubeFarmBlock::Harvest, HarvestTime,false);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDele, 0.5f, false);
	checkModifierLife(Character);
}

void AEffectZone::checkModifierLife(class AActor* OtherActor)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);

	if (Character == nullptr)
		return;
	AMyProjectCharacter* Player = Cast<AMyProjectCharacter>(OtherActor);

	if (Player->currentHP <= 0 || Player->currentHP == 100)
	{
		std::cout << "Player life is " << Player->currentHP << std::endl;
	}
	else
	{
		if (IsOverlappingActor(Character))
		{
			takeModifierLife(Character);
		}
	}
}

// Called every frame
void AEffectZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

