// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreDisplayWidget.h"

void UScoreDisplayWidget::UpdateScoreDisplay(int32 NewScore)
{
    if (ScoreText)
    {
        ScoreText->SetText(FText::AsNumber(NewScore));
    }
}
