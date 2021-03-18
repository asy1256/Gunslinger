// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class GunslingerSW : ModuleRules
{
	public GunslingerSW(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(_GetModule() );

        if (Target.Type == TargetRules.TargetType.Server)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "EasyAntiCheatCommon", "EasyAntiCheatClient", "EasyAntiCheatServer" });
            PublicDefinitions.Add("GP2_SERVER");
        }
        else
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "VivoxCore", "EasyAntiCheatCommon", "EasyAntiCheatClient", "EasyAntiCheatServer" });
        }
	}

    private string[] _GetModule()
    {
		if (Target.Type == TargetRules.TargetType.Server)
		{
			return new string[]
			{
                "Core" ,
                "CoreUObject" ,
                "Engine" ,
                "InputCore" ,
                "UMG",
                "SocketIOClient",
                "GameLiftServerSDK",
                "Http",
                "Json",
                "Paper2D",
                "JsonUtilities",
                "ApexDestruction",
                "AkAudio",
                "LevelSequence",
                "AIModule",
                "GameplayTasks"
            };
		}
		else
		{
			return new string[]
			{
				"Core" ,
				"CoreUObject" ,
				"Engine" ,
				"InputCore" ,
				"UMG",
				"SocketIOClient",
				"GameLiftServerSDK",
				"Http",
                "Json",
                "JsonUtilities",
                "ApexDestruction",
				"LogitechG",  
                "Paper2D",
                "Slate",
                "SlateCore",
                "ChromaSDKPlugin",
                "AkAudio",
                "LevelSequence",
                "AIModule",
                "GameplayTasks"
            };
		}
    }
}
