#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "../CyrusFPSGameGameMode.h"
#include "BoxActor.generated.h"

UCLASS()
class CYRUSFPSGAME_API ABoxActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABoxActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    virtual void Destroyed() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    // Static Mesh component for the box
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* mesh;

    // Base material that will be used to create a dynamic instance
    UPROPERTY(EditAnywhere, Category = "Materials")
    UMaterialInterface* baseMaterial;

    // Function to create and apply a dynamic material instance to the mesh
    void CreateAndApplyMaterial();

    void AddScoreToGameMode();
};
