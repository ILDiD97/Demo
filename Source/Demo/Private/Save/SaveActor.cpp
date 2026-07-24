// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/SaveActor.h"

#include "Save/LessonInstanceSubsystem.h"

// Sets default values
ASaveActor::ASaveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>("Collider");
	RootComponent = Box;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	Mesh->SetupAttachment(Box);
}

void ASaveActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (UGameInstance* GI = GetGameInstance())
		{
			if (ULessonInstanceSubsystem* Sub = 
				GI->GetSubsystem<ULessonInstanceSubsystem>())
			{
				FVector Position = GetActorLocation();
				FPlayerTransformState PlayerState;
				PlayerState.XPosition = Position.X;
				PlayerState.YPosition = Position.Y;
				PlayerState.ZPosition = Position.Z;
				Sub->SavePlayerState(PlayerState);
				
				if(GEngine)
				GEngine->AddOnScreenDebugMessage(-1,
					10,FColor::Red,
					"Saved");
			}
		}
	}
}

// Called when the game starts or when spawned
void ASaveActor::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this,&ASaveActor::OnBeginOverlap);
}

// Called every frame
void ASaveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

