// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class GunslingerSWEditorTarget : TargetRules
{
	public GunslingerSWEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
        BuildEnvironment = TargetBuildEnvironment.Shared;
        ExtraModuleNames.Add("GunslingerSW");
        // ExtraModuleNames.AddRange( new string[] { "" } );
        bCompileChaos = true;
    }
}
