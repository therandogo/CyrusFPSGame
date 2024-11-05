#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "CyrusFPSGameGameMode.generated.h"

UCLASS()
class CYRUSFPSGAME_API ACyrusFPSGameGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    void IncreaseScore(int32 Amount);

private:
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> ScoreDisplayWidgetClass; // Use UUserWidget instead of ScoreDisplayWidget

    UPROPERTY()
    UUserWidget* ScoreWidget; // General UserWidget reference

    UPROPERTY()
    UTextBlock* ScoreTextBlock; // Reference to the TextBlock in the widget

    int32 CurrentScore = 0;

    void UpdateScoreDisplay(); // Method to update score display
};
