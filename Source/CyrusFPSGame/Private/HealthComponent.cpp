// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	DefaultHealth = 100;
	Health = DefaultHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* owner = GetOwner();
	if (owner) {
		owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	}

}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) {

	if (Damage <= 0) {
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	if (Health <= 0.0f) {
		if (AActor* Owner = GetOwner()) { // Get the owner of this component
			Owner->Destroy(); // Destroy the owner actor
		}
	}
}
