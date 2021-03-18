#pragma once

///============================================================================
/// EWebResultEnum
///============================================================================
UENUM( BlueprintType )
enum EWebResultEnum
{
	FAIL
	, SUCCESS                                    // (������ ��û����) ����
	, INVALID_VERSION                            // ���� Ŭ�� ���� �̽���ġ
	, WRONG_PASSWORD                             // ��й�ȣ�� Ʋ��
	, NOT_FOUND_USER                             // ���� ���� ����
	, ALREADY_IN_CONNECT                         // �̹� �α��� ��
	, AUTH_TOKEN_INVALID                         // ��ū ����
	, GAMELIFT_NO_AVAILABLE_PROCESS		         // ��� ������ ��������Ʈ ������ ����. ( ����� �ִ� ���� ���� )
	, GAMELIFT_GAMESESSION_FULL                  // ���� �Ϸ��� ���� �̹� Ǯ ����
	, GAMELIFT_GAMESESSION_INVALID_STATUS        // �� ������ �Ұ� ����
	, GAMELIFT_GAMESESSION_ACTIVATING_RETRY      // �� ���� ������ ���� �غ������� 1�� �� �ٽ� ���� �õ� ó��
	, GAMELIFT_PLAYERSESSION_TERMINATED          // �̹� ����� ��
	, GAMELIFT_PLAYERSESSION_ALREADY_CONNECTED   // �̹� �濡 ������ ����
	, GAMELIFT_PLAYERSESSION_DISCONNECT          // ���� �� ������ ����
	, GAMELFIT_PLAYERSESSION_TIMEOUT             // ���� ó���� �ð� �������� ����
	, GAMELFIT_PLAYERSESSION_ALREADY_GAMESTART   // ������ ���۵Ǿ� ������ �� ����
	, GAMELIFT_ETC_ERROR					     // ��Ÿ gamelift ����
	, UNKNOWN_DB_ERROR = 1001                    // �˼� ���� DB ����
	, UNKNOWN_SERVER_ERROR                       // �˼� ���� ���� ����
	, WRONG_PARAMETER                            // �߸��� �Ķ���� ����
	, NO_VERSION_PARAMETER                       // ���� ���� �Ķ���� ����
	, NO_GAME_BAISC_SET_DATA                     // ���� �⺻ ���� ���� ����
	, DIFFERENT_GAME_VERSION                     // ���� Ŭ���̾�Ʈ�� ���� ������ �ٸ�
	, REDIS_DB_SELECT_ERROR = 1010               // ���� DB select ����
	, REDIS_DB_RANK_ERROR                        // ���� DB rank ����
	, REDIS_DB_RANGE_ERROR                       // ���� DB range ����
	, REDIS_DB_ADD_ERROR                         // ���� DB add ����
	, REDIS_DB_COUNT_ERROR                       // ���� DB count ����
	, ERROR_CHARACTER_NAME_USED = 1050           // �̹� �����ϴ� �ɸ��͸��Դϴ�.(�̸���)
	, ERROR_CHARACTER_CREATE_ALREADY             // �̹� �����ϴ� �ɸ��͸��Դϴ�.(�ش� ���Կ�)
	, FAILED_HTTP_HANDLER = 1101                 // HTTP ȣ�� ��û ����
	, TEMP_INSPECTION = 2000                     // �ӽ� ���� ���Դϴ�.
	, INSPECTION                                 // ���� ���Դϴ�.
};
