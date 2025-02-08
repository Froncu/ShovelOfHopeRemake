#pragma once

#include <map>

class SoundStream;
class SoundEffect;
class SoundManager final
{
public:
	//	Other


	//	Rule of 5
	~SoundManager() = delete;

	SoundManager(const SoundManager& other) = delete;
	SoundManager(SoundManager&& other) = delete;
	SoundManager& operator=(const SoundManager& other) = delete;
	SoundManager& operator=(SoundManager&& other) = delete;

	//	Other special methods
	SoundManager() = delete;

	//	Methods
	static void PlayStream(const std::string& path, bool repeat);
	static void PlayEffect(const std::string& path, bool repeat);

	static void StopStream();
	static void StopEffects();

	static void PauseStream();
	static void PauseEffects();

	static void ResumeStream();
	static void ResumeEffects();

	static void SetVolumeStream(int value);
	static void SetVolumeEffect(int value);

	static void DeleteAll();

	//	Setters
	

	//	Getters


protected:


private:
	static SoundEffect* GetSoundEffect(const std::string& path);

	static SoundStream* m_pSOUND_STREAM;
	static std::map<const std::string, SoundEffect* const>m_mSOUND_EFFECTS;
};