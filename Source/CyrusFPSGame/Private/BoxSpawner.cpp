#include "BoxSpawner.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "Engine/World.h"

// Sets default values
ABoxSpawner::ABoxSpawner()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ABoxSpawner::BeginPlay()
{
    Super::BeginPlay();
    FetchBoxData();
}

void ABoxSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABoxSpawner::FetchBoxData()
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &ABoxSpawner::OnResponseReceived);
    Request->SetURL(TEXT("https://raw.githubusercontent.com/CyrusCHAU/Varadise-Technical-Test/refs/heads/main/data.json"));
    Request->SetVerb(TEXT("GET"));
    Request->ProcessRequest();
}

void ABoxSpawner::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response.IsValid() && Response->GetResponseCode() == 200)
    {
        const FString ResponseString = Response->GetContentAsString();
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(ResponseString);

        if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
        {
            const TArray<TSharedPtr<FJsonValue>>* BoxArray;
            if (JsonObject->TryGetArrayField(TEXT("objects"), BoxArray))
            {
                BoxDataArray.Empty();
                for (const TSharedPtr<FJsonValue>& BoxValue : *BoxArray)
                {
                    FBoxTypeData BoxData;
                    const TSharedPtr<FJsonObject> BoxObject = BoxValue->AsObject();

                    // Get box type
                    FString BoxType;
                    if (BoxObject->TryGetStringField(TEXT("type"), BoxType))
                    {
                        // Find box type data
                        const TArray<TSharedPtr<FJsonValue>>* TypesArray;
                        if (JsonObject->TryGetArrayField(TEXT("types"), TypesArray))
                        {
                            for (const TSharedPtr<FJsonValue>& TypeValue : *TypesArray)
                            {
                                const TSharedPtr<FJsonObject> TypeObject = TypeValue->AsObject();
                                FString TypeName;
                                if (TypeObject->TryGetStringField(TEXT("name"), TypeName) && TypeName == BoxType)
                                {
                                    const TArray<TSharedPtr<FJsonValue>>* ColorArray;
                                    if (TypeObject->TryGetArrayField(TEXT("color"), ColorArray) && ColorArray->Num() == 3)
                                    {
                                        // Get the color values
                                        float R = ColorArray->GetData()[0]->AsNumber();
                                        float G = ColorArray->GetData()[1]->AsNumber();
                                        float B = ColorArray->GetData()[2]->AsNumber();
                                        BoxData.Color = FColor(R, G, B, 255);
                                    }

                                    //Get the health and score
                                    TypeObject->TryGetNumberField(TEXT("health"), BoxData.Health);
                                    TypeObject->TryGetNumberField(TEXT("score"), BoxData.Score);
                                    break;
                                }
                            }
                        }
                    }

                    // Get transform data
                    const TSharedPtr<FJsonObject>* TransformObject;
                    if (BoxObject->TryGetObjectField(TEXT("transform"), TransformObject))
                    {
                        // Get location
                        const TArray<TSharedPtr<FJsonValue>>* LocationArray;
                        if ((*TransformObject)->TryGetArrayField(TEXT("location"), LocationArray) && LocationArray->Num() == 3)
                        {
                            float PosX = LocationArray->GetData()[0]->AsNumber();
                            float PosY = LocationArray->GetData()[1]->AsNumber();
                            float PosZ = LocationArray->GetData()[2]->AsNumber();
                            BoxData.Position = FVector(PosX, PosY, PosZ);
                            UE_LOG(LogTemp, Log, TEXT("Parsed Position: (%f, %f, %f)"), PosX, PosY, PosZ);
                        }

                        // Get rotation
                        const TArray<TSharedPtr<FJsonValue>>* RotationArray;
                        if ((*TransformObject)->TryGetArrayField(TEXT("rotation"), RotationArray) && RotationArray->Num() == 3)
                        {
                            float RotPitch = RotationArray->GetData()[0]->AsNumber();
                            float RotYaw = RotationArray->GetData()[1]->AsNumber();
                            float RotRoll = RotationArray->GetData()[2]->AsNumber();
                            BoxData.Rotation = FRotator(RotPitch, RotYaw, RotRoll);
                            UE_LOG(LogTemp, Log, TEXT("Parsed Rotation: (%f, %f, %f)"), RotPitch, RotYaw, RotRoll);
                        }

                        // Get scale
                        const TArray<TSharedPtr<FJsonValue>>* ScaleArray;
                        if ((*TransformObject)->TryGetArrayField(TEXT("scale"), ScaleArray) && ScaleArray->Num() == 3)
                        {
                            float ScaleX = ScaleArray->GetData()[0]->AsNumber();
                            float ScaleY = ScaleArray->GetData()[1]->AsNumber();
                            float ScaleZ = ScaleArray->GetData()[2]->AsNumber();
                            BoxData.Scale = FVector(ScaleX, ScaleY, ScaleZ);
                            UE_LOG(LogTemp, Log, TEXT("Parsed Scale: (%f, %f, %f)"), ScaleX, ScaleY, ScaleZ);
                        }
                    }

                    //add the data to the array
                    BoxDataArray.Add(BoxData);
                }
                //Spawn the boxes
                SpawnBoxes();
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to deserialize JSON."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to fetch data! Response code: %d"), Response->GetResponseCode());
    }
}

//box spawner function
void ABoxSpawner::SpawnBoxes()
{
    if (!BoxClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("BoxClass is not set in the BoxSpawner."));
        return;
    }

    for (const FBoxTypeData& BoxData : BoxDataArray)
    {
        FActorSpawnParameters SpawnParams;
        ABoxActor* SpawnedBox = GetWorld()->SpawnActor<ABoxActor>(BoxClass, BoxData.Position, BoxData.Rotation, SpawnParams);

        if (SpawnedBox)
        {
            SpawnedBox->SetActorScale3D(BoxData.Scale);
            SpawnedBox->InstantiateBox(BoxData.Color, BoxData.Health, BoxData.Score);
        }
    }
}
