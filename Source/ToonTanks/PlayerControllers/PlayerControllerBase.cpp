// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

void APlayerControllerBase::SetEnabled(bool IsEnabled)
{
	if (IsEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = IsEnabled;
}