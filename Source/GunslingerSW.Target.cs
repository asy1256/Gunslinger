// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class GunslingerSWTarget : TargetRules
{

    public GunslingerSWTarget(TargetInfo Target) : base(Target)
	{

        this.bUseLoggingInShipping = true;

        Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "GunslingerSW" } );

        bCompileChaos = true;
   
    }
}
