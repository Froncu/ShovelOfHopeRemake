#include "pch.h"
#include "SoundManager.h"

#include "SoundStream.h"
#include "SoundEffect.h"

#pragma region StaticVariables
SoundStream* SoundManager::m_pSOUND_STREAM{};
std::map<const std::string, SoundEffect* const> SoundManager::m_mSOUND_EFFECTS{};
#pragma endregion StaticVariables



#pragma region PublicMethods
void SoundManager::PlayStream(const std::string& path, bool repeat)
{
	if (m_pSOUND_STREAM && !m_pSOUND_STREAM->IsPlaying())
	{
		delete m_pSOUND_STREAM;
		m_pSOUND_STREAM = nullptr;
	}

	if (!m_pSOUND_STREAM)
	{
		m_pSOUND_STREAM = new SoundStream(path);
		m_pSOUND_STREAM->Play(repeat);
	}
}

void SoundManager::PlayEffect(const std::string& path, bool repeat)
{
	GetSoundEffect(path)->Play(repeat);
}

void SoundManager::StopStream()
{
	if (m_pSOUND_STREAM)
	{
		m_pSOUND_STREAM->Stop();

		delete m_pSOUND_STREAM;
		m_pSOUND_STREAM = nullptr;
	}
}

void SoundManager::StopEffects()
{
	SoundEffect::StopAll();

	for (const std::pair<const std::string, SoundEffect* const>& pair : m_mSOUND_EFFECTS)
	{
		delete pair.second;
	}

	m_mSOUND_EFFECTS.clear();
}

void SoundManager::PauseStream()
{
	SoundStream::Pause();
}

void SoundManager::PauseEffects()
{
	SoundEffect::PauseAll();
}

void SoundManager::ResumeStream()
{
	SoundStream::Resume();
}

void SoundManager::ResumeEffects()
{
	SoundEffect::ResumeAll();
}

void SoundManager::SetVolumeStream(int value)
{
	SoundStream::SetVolume(value);
}

void SoundManager::SetVolumeEffect(int value)
{
	for (const std::pair<const std::string, SoundEffect* const>& pair : m_mSOUND_EFFECTS)
	{
		pair.second->SetVolume(value);
	}
}

void SoundManager::DeleteAll()
{
	StopStream();
	StopEffects();
}
#pragma endregion PublicMethods



#pragma region PrivateMethods
SoundEffect* SoundManager::GetSoundEffect(const std::string& path)
{
	std::map<const std::string, SoundEffect* const>::iterator iterator{ m_mSOUND_EFFECTS.find(path) };
	if (iterator == m_mSOUND_EFFECTS.end())
	{
		m_mSOUND_EFFECTS.insert(std::pair<const std::string, SoundEffect* const>(path, new SoundEffect(path)));
	}

	return m_mSOUND_EFFECTS.at(path);
}
#pragma endregion PrivateMethods