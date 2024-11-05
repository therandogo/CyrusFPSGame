#include "CyrusFPSGameGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h" // Include for UTextBlock

void ACyrusFPSGameGameMode::BeginPlay()
{
    Super::BeginPlay();

    // Create and add the score display widget to the viewport
    if (ScoreDisplayWidgetClass)
    {
        ScoreWidget = CreateWidget<UUserWidget>(GetWorld(), ScoreDisplayWidgetClass);
        if (ScoreWidget)
        {
            ScoreWidget->AddToViewport();

            // Assuming the widget has a UTextBlock named "ScoreText"
            ScoreTextBlock = Cast<UTextBlock>(ScoreWidget->GetWidgetFromName(TEXT("ScoreText")));
            if (!ScoreTextBlock)
            {
                UE_LOG(LogTemp, Warning, TEXT("ScoreTextBlock not found in widget."));
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to create Score Widget."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ScoreDisplayWidgetClass is null."));
    }

    // Initialize the score display
    UpdateScoreDisplay();
}

void ACyrusFPSGameGameMode::IncreaseScore(int32 Amount)
{
    CurrentScore += Amount;
    UpdateScoreDisplay(); // Update the display whenever the score changes
}

void ACyrusFPSGameGameMode::UpdateScoreDisplay()
{
    // Ensure ScoreTextBlock is valid before updating
    if (ScoreTextBlock)
    {
        ScoreTextBlock->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), CurrentScore)));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ScoreTextBlock is null, cannot update score display."));
    }
}
