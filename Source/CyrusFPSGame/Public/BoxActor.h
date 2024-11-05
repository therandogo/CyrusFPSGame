#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "../CyrusFPSGameGameMode.h"
#include "HealthComponent.h"
#include "BoxActor.generated.h"

UCLASS()
class CYRUSFPSGAME_API ABoxActor : public AActor
{
    GENERATED_BODY()

public:
    ABoxActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    virtual void Destroyed() override;

    //health component refernce
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UHealthComponent* HealthComponent;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    void InstantiateBox(FColor boxColor, float boxHealth, int32 boxScore);

private:
    // Static Mesh component for the box
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* mesh;

    // Base material that will be used to create a dynamic instance
    UPROPERTY(EditAnywhere, Category = "Materials")
    UMaterialInterface* baseMaterial;

    UPROPERTY(EditAnywhere, Category = "Materials")
    int32 score;

    // Function to create and apply a dynamic material instance to the mesh
    void CreateAndApplyMaterial(FColor color);

    //function to add score to the game mode
    void AddScoreToGameMode();
    
    //function for setting health values
    void SetBoxHealth(float boxHealth);

};
