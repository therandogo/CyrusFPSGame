// Fill out your copyright notice in the Description page of Project Settings.

#include "BoxActor.h"


class ACyrusFPSGameGameMode; // Forward declaration of the GameMode class

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

}

// Called every frame
void ABoxActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

//Helper material function
void ABoxActor::CreateAndApplyMaterial(FColor color) {
    if (mesh && baseMaterial)
    {
        // Create a dynamic material instance
        UMaterialInstanceDynamic* materialInstance = UMaterialInstanceDynamic::Create(baseMaterial, this);
        if (materialInstance)
        {
            // Set the color parameter
            materialInstance->SetVectorParameterValue(TEXT("BoxColor"), FLinearColor(color));
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


// setting health
void ABoxActor::SetBoxHealth(float boxHealth) {
    // Attempt to find the health component by class
    HealthComponent = Cast<UHealthComponent>(GetComponentByClass(UHealthComponent::StaticClass()));

    if (HealthComponent) {
        HealthComponent->SetHealth(boxHealth); // Set the health value
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("HealthComponent not found!"));
    }
}

// Override Destroyed
void ABoxActor::Destroyed()
{
    Super::Destroyed(); // Call base class implementation
    
    AddScoreToGameMode(); // Add score to GameMode
}


//adding score 
void ABoxActor::AddScoreToGameMode()
{
    ACyrusFPSGameGameMode* GameMode = Cast<ACyrusFPSGameGameMode>(GetWorld()->GetAuthGameMode());
    if (GameMode)
    {
        GameMode->IncreaseScore(score);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to cast to CyrusFPSGameGameMode."));
    }
}


//Function called on box initialization in box spawner
void ABoxActor::InstantiateBox(FColor boxColor, float boxHealth, int32 boxScore) {
    CreateAndApplyMaterial(boxColor);
    score = boxScore;
    SetBoxHealth(boxHealth);
}