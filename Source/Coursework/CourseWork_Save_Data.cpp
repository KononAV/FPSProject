// Fill out your copyright notice in the Description page of Project Settings.

#include "CourseWork_Save_Data.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#include "Serialization/BufferArchive.h"
#include "Serialization/MemoryReader.h"

UCourseWork_Save_Data::UCourseWork_Save_Data()
{
    Name = TEXT("Player");
    Kills = 0;
    Score = 0;
    PlayerCount = 1;
    SecondPlayerON = false;

    DataFilePath = FPaths::ProjectSavedDir() + TEXT("PlayerDataFile.bin");

    Name = "";
    Score = 0;
    Kills = 0;
}

void UCourseWork_Save_Data::Set_Name_Input(const FString& input)
{
    Name = input;
}

FString UCourseWork_Save_Data::Get_Name_Input() const
{
    return Name;
}

FString UCourseWork_Save_Data::Get_DataForTable_Input() const
{
    return DataForTable;
}

void UCourseWork_Save_Data::LoadDataFromFile(TArray<FPlayerData>& OutPlayers)
{
    OutPlayers.Empty();

    TArray<uint8> BinaryData;
    if (FFileHelper::LoadFileToArray(BinaryData, *DataFilePath))
    {
        FMemoryReader Reader(BinaryData, true);
        Reader.Seek(0);

        int32 Count = 0;
        Reader << Count;

        for (int32 i = 0; i < Count; ++i)
        {
            FPlayerData Data;
            Reader << Data;  
            OutPlayers.Add(Data);
        }
    }
}

void UCourseWork_Save_Data::SaveDataToFile(const TArray<FPlayerData>& InPlayers)
{
    FBufferArchive Writer;
    int32 Count = InPlayers.Num();
    Writer << Count;

    for (FPlayerData Data : InPlayers)
    {
        Writer << Data;  
    }

    FFileHelper::SaveArrayToFile(Writer, *DataFilePath);
    Writer.FlushCache();
    Writer.Empty();
}

void UCourseWork_Save_Data::Table_Write()
{
    FPlayerData ThisPlayer(Name, Kills, Score);
    TArray<FPlayerData> AllPlayers;

    LoadDataFromFile(AllPlayers);

    bool bFound = false;
    for (FPlayerData& Player : AllPlayers)
    {
        if (Player.Name == ThisPlayer.Name)
        {
            Player = ThisPlayer;
            bFound = true;
            break;
        }
    }

    if (!bFound && !Name.IsEmpty())
    {
        AllPlayers.Add(ThisPlayer);
    }

    SaveDataToFile(AllPlayers);

    Kills = 0;
    Score = 0;
}

FString UCourseWork_Save_Data::Table_Read()
{
    TArray<FPlayerData> AllPlayers;
    LoadDataFromFile(AllPlayers);

    DataForTable.Empty();
    for (const FPlayerData& Player : AllPlayers)
    {
        FString NamePad = FString::ChrN(FMath::Max(0, 12 - Player.Name.Len()), ' ');
        FString KillPad = FString::ChrN(FMath::Max(0, 12 - FString::FromInt(Player.Kills).Len()), ' ');

        DataForTable += FString::Printf(TEXT("%s%s%i%s%i\n"),
            *Player.Name,
            *NamePad,
            Player.Kills,
            *KillPad,
            Player.Score);
    }

    return DataForTable;
}
