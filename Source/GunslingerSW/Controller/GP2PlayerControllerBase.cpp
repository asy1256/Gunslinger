// Fill out your copyright notice in the Description page of Project Settings.

#include "GP2PlayerControllerBase.h"
#include "../GP2GameInstance.h"


AGP2PlayerControllerBase::AGP2PlayerControllerBase()
{
	bReplicates = true;
}

void AGP2PlayerControllerBase::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( AGP2PlayerControllerBase , PlayerData            );
	DOREPLIFETIME( AGP2PlayerControllerBase , StageInfo             );
	DOREPLIFETIME( AGP2PlayerControllerBase , UserSn                );
	DOREPLIFETIME( AGP2PlayerControllerBase , PlayerQuestList       );
	DOREPLIFETIME( AGP2PlayerControllerBase , PlayerMoney           );
	DOREPLIFETIME( AGP2PlayerControllerBase , PlayerLv              );
	DOREPLIFETIME( AGP2PlayerControllerBase , SenderText            );
	DOREPLIFETIME( AGP2PlayerControllerBase , SenderName            );
	DOREPLIFETIME( AGP2PlayerControllerBase , RecentWhisperUserName );
	DOREPLIFETIME( AGP2PlayerControllerBase , SystemInfo            );

	// DOREPLIFETIME_CONDITION( AGP2PlayerControllerBase, 
	// DOREPLIFETIME_ACTIVE_OVERRIDE
}