#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Http.h" 
#include "BoxActor.h"
#include "BoxSpawner.generated.h"

// Struct to hold box type data
USTRUCT(BlueprintType)
struct FBoxTypeData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FColor Color;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Score;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Position; 

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator Rotation; 

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Scale; 

    FBoxTypeData()
        : Color(FColor::White), Health(100.0f), Score(10),
        Position(FVector::ZeroVector), Rotation(FRotator::ZeroRotator),
        Scale(FVector(1.0f, 1.0f, 1.0f)) // Default values for fields
    {}
};

UCLASS()
class CYRUSFPSGAME_API ABoxSpawner : public AActor
{
    GENERATED_BODY()

public:
    ABoxSpawner();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    //Function and variable definitions
    void FetchBoxData();
    void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
    void SpawnBoxes();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FBoxTypeData> BoxDataArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<ABoxActor> BoxClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector SpawnLocation;

    UPROPERTY()
    TArray<AActor*> SpawnedBoxes;
};
