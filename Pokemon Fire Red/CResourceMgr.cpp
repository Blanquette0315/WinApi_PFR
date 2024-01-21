#include "pch.h"
#include "CResourceMgr.h"

#include "CPathMgr.h"

#include "CImage.h"
#include "CSound.h"

CResourceMgr::CResourceMgr()
{

}

CResourceMgr::~CResourceMgr()
{
	Safe_Del_Map(m_mapImage);
	Safe_Del_Map(m_mapSound);
}

void CResourceMgr::init()
{
	// Image 로딩	
	LoadImg(L"PlayerAtlas", L"Image\\Player\\Player Work.bmp");
	LoadImg(L"Player", L"Image\\Player\\Player.bmp");

	// UI 이미지 로딩
	LoadImg(L"Menu", L"Image\\UI\\Menu.bmp");
	LoadImg(L"MenuArrow", L"Image\\UI\\MenuArrow.bmp");

	LoadImg(L"PokemonSelectUI", L"Image\\UI\\PokemonSelectUI.bmp");
	LoadImg(L"CurPokemonBox", L"Image\\UI\\CurPokemonBox.bmp");
	LoadImg(L"CurPokemonBoxTarget", L"Image\\UI\\CurPokemonBoxTarget.bmp");
	LoadImg(L"PokemonBox", L"Image\\UI\\PokemonBox.bmp");
	LoadImg(L"PokemonBoxTarget", L"Image\\UI\\PokemonBoxTarget.bmp");
	LoadImg(L"CancelBox", L"Image\\UI\\CancelBox.bmp");
	LoadImg(L"CancelBoxTarget", L"Image\\UI\\CancelBoxTarget.bmp");

	LoadImg(L"BattleMessageBox", L"Image\\\BattleScene\\BattleMessageBox.bmp");
	LoadImg(L"BattleBox", L"Image\\\BattleScene\\BattleBox.bmp");
	LoadImg(L"BoxArrow", L"Image\\\BattleScene\\BoxArrow.bmp");
	LoadImg(L"MonsterInfoBox", L"Image\\\BattleScene\\MonsterInfoBox.bmp");
	LoadImg(L"PlayerActionBox", L"Image\\\BattleScene\\PlayerActionBox.bmp");
	LoadImg(L"PlayerMonsterInfoBox", L"Image\\\BattleScene\\PlayerMonsterInfoBox.bmp"); 

	// 포켓몬 선택 UI
	LoadImg(L"PokemonSelectUIHPbarG", L"Image\\UI\\PokemonSelectUIHPbarG.bmp");
	LoadImg(L"PokemonSelectUIHPbarY", L"Image\\UI\\PokemonSelectUIHPbarY.bmp");
	LoadImg(L"PokemonSelectUIHPbarR", L"Image\\UI\\PokemonSelectUIHPbarR.bmp");

	LoadImg(L"MenuBox", L"Image\\UI\\MenuBox.bmp");

	// 오박사 집 포켓몬 선택 UI
	LoadImg(L"OakUI", L"Image\\UI\\OakUI.bmp");

	// 가방 UI이미지
	LoadImg(L"BackPackUI", L"Image\\UI\\BackPackUI.bmp");
	LoadImg(L"BackPack", L"Image\\UI\\BackPack.bmp");
	LoadImg(L"BackPack2", L"Image\\UI\\BackPack2.bmp");
	LoadImg(L"BackPack3", L"Image\\UI\\BackPack3.bmp");
	LoadImg(L"BackPackUIArrow", L"Image\\UI\\BackPackUIArrow.bmp");
	LoadImg(L"BackPackUIArrowRight", L"Image\\UI\\BackPackUIArrowRight.bmp");

	// 폰트
	LoadImg(L"BattleMessageFontTable", L"Image\\\BattleScene\\BattleMessageFontTable.bmp");
	LoadImg(L"InfoBoxFont", L"Image\\\BattleScene\\InfoBoxFont.bmp");
	LoadImg(L"BattleBoxFont", L"Image\\\BattleScene\\BattleBoxFont.bmp");
	LoadImg(L"PPFont", L"Image\\\BattleScene\\PPFont.bmp");
	LoadImg(L"PokemonBoxFont", L"Image\\UI\\PokemonBoxFont.bmp");

	// 맵 배경
	LoadImg(L"PalletCity", L"Image\\map\\City\\Pallet City_Resize.bmp");
	LoadImg(L"Road1", L"Image\\map\\City\\Road1.bmp");
	LoadImg(L"ViridianCity", L"Image\\map\\City\\Viridian City.bmp");
	LoadImg(L"PewterCity", L"Image\\map\\City\\Pewter City.bmp");

	// 집들 내부
	LoadImg(L"CenterIn1f", L"Image\\map\\Building\\CenterIn1f.bmp");
	LoadImg(L"CenterIn2f", L"Image\\map\\Building\\CenterIn2f.bmp");
	LoadImg(L"GreenHouse", L"Image\\map\\Building\\GreenHouse.bmp");
	LoadImg(L"HeroHouse1f", L"Image\\map\\Building\\HeroHouse1f.bmp");
	LoadImg(L"HeroHouse2f", L"Image\\map\\Building\\HeroHouse2f.bmp");
	LoadImg(L"House1In", L"Image\\map\\Building\\House1In.bmp");
	LoadImg(L"House2In", L"Image\\map\\Building\\House2In.bmp");
	LoadImg(L"MartIn", L"Image\\map\\Building\\MartIn.bmp");
	LoadImg(L"OaksLabIn", L"Image\\map\\Building\\OaksLabIn.bmp");
	LoadImg(L"PewterGymInside", L"Image\\map\\Building\\PewterGymInside.bmp");
	LoadImg(L"MuseumInside", L"Image\\map\\Building\\MuseumInside.bmp");
	LoadImg(L"Museum2f", L"Image\\map\\Building\\Museum2f.bmp");
	LoadImg(L"HouseBlackRoofInside", L"Image\\map\\Building\\HouseBlackRoofInside.bmp");

	// 빌딩
	LoadImg(L"HouseRedRoof", L"Image\\map\\Building\\House Red Roof.bmp");
	LoadImg(L"Center", L"Image\\map\\Building\\Center.bmp");
	LoadImg(L"Gym", L"Image\\map\\Building\\Gym.bmp");
	LoadImg(L"House1", L"Image\\map\\Building\\House1.bmp");
	LoadImg(L"House2", L"Image\\map\\Building\\House2.bmp");
	LoadImg(L"Mart", L"Image\\map\\Building\\Mart.bmp");
	LoadImg(L"OaksLab", L"Image\\map\\Building\\OaksLab.bmp");
	LoadImg(L"Museum", L"Image\\map\\Building\\Museum.bmp");
	LoadImg(L"HouseBlackRoof", L"Image\\map\\Building\\HouseBlackRoof.bmp");
	LoadImg(L"PewterGym", L"Image\\map\\Building\\PewterGym.bmp");

	// 환경체
	LoadImg(L"Flower", L"Image\\map\\Environment\\Flower.bmp");
	LoadImg(L"Wave", L"Image\\map\\Environment\\Wave.bmp");
	LoadImg(L"ATree", L"Image\\map\\Environment\\ATree.bmp");
	LoadImg(L"AATree", L"Image\\map\\Environment\\AATree.bmp");
	LoadImg(L"Grass", L"Image\\map\\Environment\\Grass.bmp");
	LoadImg(L"MailBox", L"Image\\map\\Environment\\MailBox.bmp");
	LoadImg(L"WhiteFence", L"Image\\map\\Environment\\WhiteFence.bmp");
	LoadImg(L"WhiteFence1", L"Image\\map\\Environment\\WhiteFence1.bmp");
	LoadImg(L"WhiteFenceLeftBot", L"Image\\map\\Environment\\WhiteFenceLeftBot.bmp");
	LoadImg(L"WhiteFenceLeftTop", L"Image\\map\\Environment\\WhiteFenceLeftTop.bmp");
	LoadImg(L"WhiteFenceRightBot", L"Image\\map\\Environment\\WhiteFenceRightBot.bmp");
	LoadImg(L"WhiteFenceRightTop", L"Image\\map\\Environment\\WhiteFenceRightTop.bmp");
	LoadImg(L"WhiteSign", L"Image\\map\\Environment\\WhiteSign.bmp");
	LoadImg(L"WoodSign", L"Image\\map\\Environment\\WoodSign.bmp");
	LoadImg(L"WoodFence", L"Image\\map\\Environment\\WoodFence.bmp");
	LoadImg(L"WoodFence1", L"Image\\map\\Environment\\WoodFence1.bmp");
	LoadImg(L"WoodFenceLeftBot", L"Image\\map\\Environment\\WoodFenceLeftBot.bmp");
	LoadImg(L"WoodFenceLeftTop", L"Image\\map\\Environment\\WoodFenceLeftTop.bmp");
	LoadImg(L"WoodFenceRightBot", L"Image\\map\\Environment\\WoodFenceRightBot.bmp");
	LoadImg(L"WoodFenceRightTop", L"Image\\map\\Environment\\WoodFenceRightTop.bmp");
	LoadImg(L"SmallTree", L"Image\\map\\Environment\\SmallTree.bmp");
	LoadImg(L"PalletWave", L"Image\\map\\Environment\\PalletWave.bmp");
	LoadImg(L"RockTile", L"Image\\map\\Environment\\RockTile.bmp");
	LoadImg(L"RockConerTile", L"Image\\map\\Environment\\RockConerTile.bmp");
	LoadImg(L"GymSign", L"Image\\map\\Environment\\GymSign.bmp");
	LoadImg(L"WoodFence2", L"Image\\map\\Environment\\WoodFence2.bmp");


	LoadImg(L"Bed", L"Image\\map\\Environment\\Inside\\Bed.bmp");
	LoadImg(L"OakBookshelf", L"Image\\map\\Environment\\Inside\\OakBookshelf.bmp");
	LoadImg(L"OakBookshelfHalf", L"Image\\map\\Environment\\Inside\\OakBookshelfHalf.bmp");
	LoadImg(L"Flowerpot", L"Image\\map\\Environment\\Inside\\Flowerpot.bmp");
	LoadImg(L"OakBook", L"Image\\map\\Environment\\Inside\\OakBook.bmp");
	LoadImg(L"OakMachine", L"Image\\map\\Environment\\Inside\\OakMachine.bmp");
	LoadImg(L"Table", L"Image\\map\\Environment\\Inside\\Table.bmp");
	LoadImg(L"OakMonsterBall", L"Image\\map\\Environment\\Inside\\OakMonsterBall.bmp");
	LoadImg(L"OakTable", L"Image\\map\\Environment\\Inside\\OakTable.bmp");
	LoadImg(L"OakBookShelfHalf1", L"Image\\map\\Environment\\Inside\\OakBookShelfHalf1.bmp");
	LoadImg(L"CenterSofa", L"Image\\map\\Environment\\Inside\\CenterSofa.bmp");
	LoadImg(L"CenterTable", L"Image\\map\\Environment\\Inside\\CenterTable.bmp");
	LoadImg(L"MartStand", L"Image\\map\\Environment\\Inside\\MartStand.bmp");
	LoadImg(L"MartStand1", L"Image\\map\\Environment\\Inside\\MartStand1.bmp");
	LoadImg(L"MartTable", L"Image\\map\\Environment\\Inside\\MartTable.bmp");
	LoadImg(L"Museum2fStand", L"Image\\map\\Environment\\Inside\\Museum2fStand.bmp");
	LoadImg(L"Museum2fStand1", L"Image\\map\\Environment\\Inside\\Museum2fStand1.bmp");
	LoadImg(L"MuseumBox", L"Image\\map\\Environment\\Inside\\MuseumBox.bmp");
	LoadImg(L"MuseumStand", L"Image\\map\\Environment\\Inside\\MuseumStand.bmp");
	LoadImg(L"House2Table", L"Image\\map\\Environment\\Inside\\House2Table.bmp");
	LoadImg(L"Escalator1f", L"Image\\map\\Environment\\Inside\\Escalator1f.bmp");
	LoadImg(L"Escalator2f", L"Image\\map\\Environment\\Inside\\Escalator2f.bmp");

	LoadImg(L"WaveTem", L"Image\\map\\Environment\\WaveTem.bmp");

	// 아이템 이미지
	LoadImg(L"Potion", L"Image\\Item\\Potion.bmp");
	LoadImg(L"Revive", L"Image\\Item\\Revive.bmp");
	LoadImg(L"Candy", L"Image\\Item\\Candy.bmp");

	// 포켓몬 이미지
	LoadImg(L"Charmander", L"Image\\Pokemon\\Charmander.bmp");
	LoadImg(L"CharmanderPlayer", L"Image\\Pokemon\\CharmanderPlayer.bmp"); 
	LoadImg(L"CharmanderUI", L"Image\\Pokemon\\CharmanderUI.bmp");

	LoadImg(L"SquirtlePlayer", L"Image\\Pokemon\\SquirtlePlayer.bmp");
	LoadImg(L"Squirtle", L"Image\\Pokemon\\Squirtle.bmp");
	LoadImg(L"SquirtleUI", L"Image\\Pokemon\\SquirtleUI.bmp");

	LoadImg(L"Bulbasaur", L"Image\\Pokemon\\Bulbasaur.bmp");
	LoadImg(L"BulbasaurPlayer", L"Image\\Pokemon\\BulbasaurPlayer.bmp");
	LoadImg(L"BulbasaurUI", L"Image\\Pokemon\\BulbasaurUI.bmp");

	LoadImg(L"Caterpie", L"Image\\Pokemon\\Caterpie.bmp");
	LoadImg(L"CaterpiePlayer", L"Image\\Pokemon\\CaterpiePlayer.bmp");
	LoadImg(L"CaterpieUI", L"Image\\Pokemon\\CaterpieUI.bmp");

	LoadImg(L"Pidgev", L"Image\\Pokemon\\Pidgev.bmp");
	LoadImg(L"PidgevPlayer", L"Image\\Pokemon\\PidgevPlayer.bmp");
	LoadImg(L"PidgevUI", L"Image\\Pokemon\\PidgevUI.bmp");

	LoadImg(L"Rattata", L"Image\\Pokemon\\Rattata.bmp");
	LoadImg(L"RattataPlayer", L"Image\\Pokemon\\RattataPlayer.bmp");
	LoadImg(L"RattataUI", L"Image\\Pokemon\\RattataUI.bmp");

	LoadImg(L"Geodude", L"Image\\Pokemon\\Geodude.bmp");

	LoadImg(L"Onix", L"Image\\Pokemon\\Onix.bmp");

	// 배틀 씬 이미지
	LoadImg(L"GrassBattle", L"Image\\BattleScene\\GrassBattle.bmp"); 

	LoadImg(L"GreenHPbar", L"Image\\BattleScene\\GreenHPbar.bmp");
	LoadImg(L"YellowHPbar", L"Image\\BattleScene\\YellowHPbar.bmp");
	LoadImg(L"RedHPbar", L"Image\\BattleScene\\RedHPbar.bmp");
	LoadImg(L"Expbar", L"Image\\BattleScene\\Expbar.bmp");

	// 스킬
	LoadImg(L"Scratch", L"Image\\Skill\\Scratch.bmp"); 
	LoadImg(L"Ember", L"Image\\Skill\\Ember.bmp");
	LoadImg(L"Bubble", L"Image\\Skill\\Bubble.bmp");
	LoadImg(L"Vinewhip", L"Image\\Skill\\Vinewhip.bmp");
	LoadImg(L"Vinewhip2", L"Image\\Skill\\Vinewhip2.bmp");
	LoadImg(L"Tackle", L"Image\\Skill\\Tackle.bmp");
	LoadImg(L"Gust", L"Image\\Skill\\Gust.bmp");
	LoadImg(L"RockTomb", L"Image\\Skill\\RockTomb.bmp");
	LoadImg(L"X", L"Image\\Skill\\X.bmp");
	LoadImg(L"MetalClaw", L"Image\\Skill\\MetalClaw.bmp");
	LoadImg(L"RazorLeaf", L"Image\\Skill\\RazorLeaf.bmp");
	LoadImg(L"WaterGun", L"Image\\Skill\\WaterGun.bmp");
	LoadImg(L"WaterGunHit", L"Image\\Skill\\WaterGunHit.bmp");
	LoadImg(L"WaterGunOther", L"Image\\Skill\\WaterGunOther.bmp");
	
	// NPC
	LoadImg(L"Oak", L"Image\\\NPC\\Oak.bmp");
	
	// Sound 로딩
	LoadSound(L"PalletTownTheme", L"Sound\\PalletTownTheme.wav");
	LoadSound(L"OakLaboratory", L"Sound\\OakLaboratory.wav");
	LoadSound(L"BattleWildPokemon", L"Sound\\Battle WildPokemon.wav");
	LoadSound(L"VictoryWildPokemon", L"Sound\\Victory WildPokemon.wav");
	LoadSound(L"RoadtoViridianCity", L"Sound\\Road to Viridian City.wav");
	LoadSound(L"PewterCityTheme", L"Sound\\Pewter City Theme.wav");
	LoadSound(L"PokemonCenter", L"Sound\\PokemonCenter.wav");

	// 효과음
	LoadSound(L"BulidingEixt", L"Sound\\BulidingEixt.wav");
	LoadSound(L"BulidingIn", L"Sound\\BulidingIn.wav");
	LoadSound(L"SelectSound", L"Sound\\SelectSound.wav");
	LoadSound(L"RedHP", L"Sound\\RedHP.wav");

	//기술 효과음
	LoadSound(L"BubbleStart", L"Sound\\BubbleStart.wav");
	LoadSound(L"BubbleEnd", L"Sound\\BubbleEnd.wav");
	LoadSound(L"EmberStart", L"Sound\\EmberStart.wav");
	LoadSound(L"EmberEnd", L"Sound\\EmberEnd.wav");
	LoadSound(L"WaterGunStart", L"Sound\\WaterGunStart.wav");
	LoadSound(L"WaterGunEnd", L"Sound\\WaterGunEnd.wav");
	LoadSound(L"Gust", L"Sound\\Gust.wav");
	LoadSound(L"Gust2", L"Sound\\Gust2.wav");
	LoadSound(L"Gust3", L"Sound\\Gust3.wav");
	LoadSound(L"HIT", L"Sound\\HIT.wav");
	LoadSound(L"RockFoll", L"Sound\\RockFoll.wav");
	LoadSound(L"RockFollbgm", L"Sound\\RockFollbgm.wav");

}

CImage* CResourceMgr::LoadImg(const wstring& _strKey, const wstring& _strRelativePath)
{
	// 키값으로 탐색
	CImage* pImage = FindImg(_strKey);
	if (nullptr != pImage)
	{
		// 해당키로 이미 로딩된게 있으면 해당 리소스를 반환
		return pImage;
	}

	// 해당 키로 로딩된 이미지가 없다.

	// content 폴더 경로 + 상대경로 = 최종 경로
	wstring strFilePath = CPathMgr::CreateMgr()->GetContentPath();
	strFilePath += _strRelativePath;

	pImage = new CImage;
	if (FAILED(pImage->Load(strFilePath)))
	{
		MessageBox(nullptr, L"이미지 로딩 실패", L"에러", MB_OK);
		return nullptr;
	}

	pImage->SetKey(_strKey);
	pImage->SetRelativePath(_strRelativePath);
	m_mapImage.insert(make_pair(_strKey, pImage));

	return pImage;
}

CImage* CResourceMgr::CreateImg(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
	// 키값으로 탐색
	CImage* pImage = FindImg(_strKey);
	if (nullptr != pImage)
	{
		MessageBox(nullptr, L"중복 키 발생", L"이미지 생성 실패", MB_OK);
		return nullptr;
	}

	// 해당 키로 생성된 이미지가 없다.
	pImage = new CImage;
	if (FAILED(pImage->Create(_iWidth, _iHeight)))
	{
		MessageBox(nullptr, L"이미지 생성 실패", L"에러", MB_OK);
		return nullptr;
	}

	pImage->SetKey(_strKey);
	m_mapImage.insert(make_pair(_strKey, pImage));

	return pImage;
}

CImage* CResourceMgr::FindImg(const wstring& _strKey)
{
	map<wstring, CImage*>::iterator iter = m_mapImage.find(_strKey);

	// 이미 동일한 키값으로 다른 리소스가 먼저 등록되어 있었다.
	if (iter != m_mapImage.end())
	{
		return iter->second;
	}

	return nullptr;
}


CSound* CResourceMgr::FindSound(const wstring& _strKey)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_strKey);

	if (iter == m_mapSound.end())
		return nullptr;

	return (CSound*)iter->second;
}

CSound* CResourceMgr::LoadSound(const wstring& _strKey, const wstring& _strRelativePath)
{
	CSound* pSound = FindSound(_strKey);

	if (nullptr != pSound)
		return pSound;

	pSound = new CSound;

	wstring strFilePath = CPathMgr::CreateMgr()->GetContentPath();
	strFilePath += _strRelativePath;
	HRESULT hr = pSound->Load(strFilePath.c_str());

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"Sound 로딩 실패!!!", L"리소스 로딩 실패", MB_OK);
		delete pSound;
		return nullptr;
	}

	pSound->SetKey(_strKey);
	pSound->SetRelativePath(_strRelativePath);

	// map 에 등록
	m_mapSound.insert(make_pair(_strKey, pSound));

	return pSound;
}