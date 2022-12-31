// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();
	
	FString ObjectName = GetOwner()->GetActorLabel();
	FString ObjectLocation = GetOwner()->GetActorLocation().ToString();
	
	UE_LOG(LogTemp, Warning, TEXT("%s position in world %s"), *ObjectName, *ObjectLocation);

}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
