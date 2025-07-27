// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CourseWork_Save_Data.generated.h"

USTRUCT(BlueprintType)
struct FPlayerData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString Name;

    UPROPERTY(BlueprintReadWrite)
    int32 Kills;

    UPROPERTY(BlueprintReadWrite)
    int32 Score;

    FPlayerData()
        : Name(TEXT("Player")), Kills(0), Score(0) {
    }

    FPlayerData(const FString& InName, int32 InKills, int32 InScore)
        : Name(InName), Kills(InKills), Score(InScore) {
    }

    friend FArchive& operator<<(FArchive& Ar, FPlayerData& Data)
    {
        Ar << Data.Name;
        Ar << Data.Kills;
        Ar << Data.Score;
        return Ar;
    }
};

UCLASS(Blueprintable)
class COURSEWORK_API UCourseWork_Save_Data : public UObject
{
    GENERATED_BODY()

public:
    UCourseWork_Save_Data();

    // Player State
    UPROPERTY(BlueprintReadWrite, Category = "SaveData")
    int32 PlayerCount;

    UPROPERTY(BlueprintReadWrite, Category = "SaveData")
    FString Name;

    UPROPERTY(BlueprintReadWrite, Category = "SaveData")
    int32 Kills;

    UPROPERTY(BlueprintReadWrite, Category = "SaveData")
    int32 Score;

    UPROPERTY(BlueprintReadWrite, Category = "SaveData")
    bool SecondPlayerON;

    UPROPERTY(BlueprintReadOnly, Category = "SaveData")
    FString DataForTable;

    // Functions
    UFUNCTION(BlueprintCallable, Category = "SaveData")
    int32 Get_PlayerCount() const { return PlayerCount; }

    UFUNCTION(BlueprintCallable, Category = "SaveData")
    void Ser_PlayerCount() { PlayerCount = 4; }

    UFUNCTION(BlueprintCallable, Category = "SaveData")
    int32 Get_Kills() const { return Kills; }

    UFUNCTION(BlueprintCallable, Category = "SaveData")
    int32 Get_Score() const { return Score; }

    UFUNCTION(BlueprintCallable, Category = "SaveData")
    bool Get_SecondPlayer() const { return SecondPlayerON; }

    UFUNCTION(BlueprintCallable, Category = "SaveData")
    void Ser_SecondPlayer(bool setting) { SecondPlayerON = setting; }

    UFUNCTION(BlueprintCallable, Category = "SaveData")
    void Set_Kills(int32 InKills) { Kills = InKills; }

    UFUNCTION(BlueprintCallable, Category = "SaveData")
    void Set_Name_Input(const FString& input);

    UFUNCTION(BlueprintCallable, Category = "SaveData")
    FString Get_Name_Input() const;

    UFUNCTION(BlueprintCallable, Category = "SaveData")
    FString Get_DataForTable_Input() const;

    UFUNCTION(BlueprintCallable, Category = "SaveData")
    void Table_Write();

    UFUNCTION(BlueprintCallable, Category = "SaveData")
    FString Table_Read();

private:
    FString DataFilePath;

    void LoadDataFromFile(TArray<FPlayerData>& OutPlayers);
    void SaveDataToFile(const TArray<FPlayerData>& InPlayers);
};
