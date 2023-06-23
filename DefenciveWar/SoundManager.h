#pragma once

#include<string>

/// <summary>
/// サウンド管理クラス
/// シングルトン
/// </summary>
class SoundManager final
{
public:
	SoundManager();
	~SoundManager();

	enum Bgm
	{
		MAIN,
		RESULT,

		BGM_AMOUNT
	};

	
	enum Se
	{
		CHARACTER_HIT = 0,			// 接触音
		SHOOT_BULLET_PLAYER,		// 発射音（プレイヤー）
		SHOOT_BULLET_ENEMY,			// 発射音（エネミー）
		SHIELD_HIT_NORMAL,			// 防御音（通常）
		SHIELD_HIT_JUST,			// 防御音（ジャスト）
		SHIELD_HIT_BULLET = 5,		// 防御音（弾）
		HIT_BULLET_PLAYER,			// 弾被弾音（プレイヤー）
		HIT_BULLET_ENEMY,			// 弾被弾音（エネミー）
		SHIELD_BREAK,				// シールド破壊音
		PLAYER_DIE,					// プレイヤー死亡音
		ENEMY_DIE = 10,				// エネミー死亡音
		PINCH_HITPOINT,				// HitPoint危険音
		TELEPORT_ENEMY,				// テレポート音（エネミー）
		ACTIVE_SHIELD,				// シールド展開音
		DECIDE_SCORE,				// スコア確定音
		AVOIDANCE_PLAYER = 15,		// 回避音（プレイヤー）
		PUSH_START,					// ゲーム開始音
		RECOVERY_PLAYER,			// 回復音（プレイヤー）
		SOUND_SE_TEST,				// オプションSE設定音
		SELECT,						// 項目選択音

		SE_AMOUNT					// SE総数
	};

	void Update();

	void PlayBgm(Bgm bgm, bool loop = true);
	void StopBgm();

	// セッター
	void SetSePlayFlag(Se se);
	void SetBgmVolume(int volume);
	void SetSeVolume(int volume);
	// ゲッター
	const int GetBgmVolume() const { return BGM_VOLUME; }
	const int GetSeVolume() const { return SE_VOLUME; }

private:

	void LoadAllSound();
	void DeleteAllSound();

	void VolumeChange();
	//定数
	static const std::string SOUND_FOLDER_PATH;  // Soundフォルダまでのパス
	static const std::string BGM_PATH;           // BGMファイル名(連番除く)
	static const std::string SE_PATH;            // SEファイル名(連番除く)
	static const std::string BGM_FILENAME_EXTENSION; // BGM拡張子
	static const std::string SE_FILENAME_EXTENSION;  // SE拡張子

	int BGM_VOLUME;                 // BGMの音量
	int SE_VOLUME;                  // SEの音量


	int  bgmData[BGM_AMOUNT];  // BGM読み込み用
	int  seData[SE_AMOUNT];    // SE読み込み用
	bool sePlayFlag[SE_AMOUNT];// このフレームで再生するか
};

