// Fill out your copyright notice in the Description page of Project Settings.

#include "BoxActor.h"


class ACyrusFPSGameGameMode; // Forward declaration of the GameMode class

// Sets default values
ABoxActor::ABoxActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;


    mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My mesh"));
    RootComponent = mesh;

}

// Called when the game starts or when spawned
void ABoxActor::BeginPlay()
{
    Super::BeginPlay();

    CreateAndApplyMaterial();
}

// Called every frame
void ABoxActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ABoxActor::CreateAndApplyMaterial() {
    if (mesh && baseMaterial)
    {
        // Create a dynamic material instance
        UMaterialInstanceDynamic* materialInstance = UMaterialInstanceDynamic::Create(baseMaterial, this);
        if (materialInstance)
        {
            // Set the color parameter
            materialInstance->SetVectorParameterValue(TEXT("BoxColor"), FLinearColor(0.0f, 0.0f, 0.0f, 1.0f));
            mesh->SetMaterial(0, materialInstance);
            UE_LOG(LogTemp, Warning, TEXT("Material applied successfully."));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to create dynamic material instance."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Mesh or Base Material is null."));
    }
}

// Override Destroyed
void ABoxActor::Destroyed()
{
    Super::Destroyed(); // Call base class implementation
    AddScoreToGameMode(); // Add score to GameMode
}

void ABoxActor::AddScoreToGameMode()
{
    ACyrusFPSGameGameMode* GameMode = Cast<ACyrusFPSGameGameMode>(GetWorld()->GetAuthGameMode());
    if (GameMode)
    {
        GameMode->IncreaseScore(10); // Increase score by 10
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to cast to CyrusFPSGameGameMode."));
    }
}