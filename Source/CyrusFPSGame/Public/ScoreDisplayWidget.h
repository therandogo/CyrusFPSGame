#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ScoreDisplayWidget.generated.h"

UCLASS()
class CYRUSFPSGAME_API UScoreDisplayWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void UpdateScoreDisplay(int32 NewScore);

protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* ScoreText;
};
