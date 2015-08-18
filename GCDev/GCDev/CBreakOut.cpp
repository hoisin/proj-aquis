#include "CBreakOut.h"

#include "CBaseEntity.h"
#include "CPaddle.h"
#include "CBall.h"
#include "CBrick.h"
#include "CLevel.h"

#include "GCMath.h"
#include "Utility.h"


CBreakOut::CBreakOut() : m_brickTextureID(-1), m_currentLevel(1)
{
}


CBreakOut::~CBreakOut()
{
}


bool CBreakOut::Initialise(CGfx* pGfx)
{
	// Grab world size
	m_worldWidth = pGfx->GetWindowWidth();
	m_worldHeight = pGfx->GetWindowHeight();

	m_worldSize.left = 0;
	m_worldSize.top = 0;
	m_worldSize.right = m_worldWidth;
	m_worldSize.bottom = m_worldHeight;

	// a storage instance for each entity type
	auto paddleStore = std::pair<std::string, std::vector<std::shared_ptr<CBaseEntity>>>("paddles", std::vector<std::shared_ptr<CBaseEntity>>());
	auto ballStore = std::pair<std::string, std::vector<std::shared_ptr<CBaseEntity>>>("balls", std::vector<std::shared_ptr<CBaseEntity>>());
	auto brickStore = std::pair<std::string, std::vector<std::shared_ptr<CBaseEntity>>>("bricks", std::vector<std::shared_ptr<CBaseEntity>>());

    m_entities = std::map<std::string, std::vector<std::shared_ptr<CBaseEntity>>>();
	m_entities.insert(paddleStore);
	m_entities.insert(ballStore);
	m_entities.insert(brickStore);

    // Setup paddle 
    int paddleTexID = pGfx->LoadTexture("..\\Assets\\paddle.bmp");
    auto paddleObj = std::shared_ptr<CPaddle>(new CPaddle);
    
    int texWidth, texHeight;
    pGfx->GetTextureAnimFrameDimensions(paddleTexID, texWidth, texHeight);

    paddleObj->SetActive(true);
    paddleObj->SetCollisionRect(gcmath::Rect<int>(0, texWidth, 0, texHeight));
    paddleObj->SetTextureFrame(gcmath::Rect<int>(0, texWidth, 0, texHeight));
    paddleObj->SetSpriteID(paddleTexID);
    paddleObj->SetPosition(gcmath::Vec2<int>(texWidth / 2, texHeight / 2));

    m_entities["paddles"].push_back(paddleObj);


    // Setup ball 
    // Reusing variables
    SDL_Color transparentKey;
    transparentKey.r = 0;
    transparentKey.g = 255;
    transparentKey.b = 0;

    int ballTexID = pGfx->LoadTexture("..\\Assets\\ball.bmp", transparentKey);
    auto ballObj = std::shared_ptr<CBall>(new CBall);

	pGfx->GetTextureAnimFrameDimensions(ballTexID, texWidth, texHeight);

    ballObj->SetActive(true);
    ballObj->SetCollisionRect(gcmath::Rect<int>(0, texWidth, 0, texHeight));
    ballObj->SetTextureFrame(gcmath::Rect<int>(0, texWidth, 0, texHeight));
    ballObj->SetSpriteID(ballTexID);
    ballObj->SetPosition(gcmath::Vec2<int>(100, 50));
	ballObj->SetSpeed(12);
	ballObj->SetDirection(gcmath::Vec2<float>(0.5f, 0.5f));
    m_entities["balls"].push_back(ballObj);

    // Load the brick texture
    m_brickTextureID = pGfx->LoadTexture("..\\Assets\\brick.bmp");
    m_brickDrawFrame.left = 0;
    m_brickDrawFrame.top = 0;
    pGfx->GetTextureAnimFrameDimensions(m_brickTextureID, m_brickDrawFrame.right, m_brickDrawFrame.bottom);

	m_levelMgr.reset(new CLevel);
	m_levelMgr->LoadLevelData(3);
	
	return true;
}


void CBreakOut::SetLevel(unsigned int levelNum, unsigned int screenWidth, unsigned int screenHeight)
{
	// Clear out any existing bricks
	m_entities["bricks"].clear();

	m_currentLevel = levelNum;

	// Grab common properties for the bricks
	for (const auto& brick : m_levelMgr->m_bricks[m_currentLevel-1]) {
		const auto& pBrick = std::shared_ptr<CBaseEntity>(new CBrick);

		pBrick->SetActive(true);
		pBrick->SetCollisionRect(m_brickDrawFrame);
		pBrick->SetSpriteID(m_brickTextureID);
		pBrick->SetTextureFrame(m_brickDrawFrame);
		pBrick->SetPosition(brick);

		m_entities["bricks"].push_back(pBrick);
	}

	m_remainingBricks = m_entities.size();

	// Position paddle at 85% of the height of the screen
	int yVal = (int)(0.85f * screenHeight);

	m_entities["balls"][0]->SetPosition(gcmath::Vec2<int>((int)screenWidth / 8, (int)(screenHeight * 0.45f)));
	m_entities["paddles"][0]->SetPositionCentered(gcmath::Vec2<int>((int)screenWidth / 2, yVal));
}


void CBreakOut::Update(unsigned int deltaT)
{
	// Update all entities
	for (auto const &mapIt : m_entities) {
		for (auto const &vecIt : mapIt.second) {
            if(vecIt->IsActive())
                vecIt->VUpdate(deltaT, this);
		}
	}

	// Perform collision detection
	// Paddle only needs to check against ball.
	// Ball needs to be checked against all.
	auto pBall = GetEntity("balls", 0);
	bool ballCollision = false;

	for (auto pBrick : m_entities["bricks"]) {
		if (pBrick->IsActive()) {
			if (pBall->GetWorldCollisionRect().Intersects(pBrick->GetWorldCollisionRect())) {
				pBall->VOnCollision(true, this, &pBrick->GetWorldCollisionRect());
				pBrick->VOnCollision(true, this, &pBall->GetWorldCollisionRect());
				ballCollision = true;
				break;
			}
		}
	}

	auto paddle = m_entities["paddles"][0];
	if (pBall->GetWorldCollisionRect().Intersects(paddle->GetWorldCollisionRect())) {
		pBall->VOnCollision(true, this, &paddle->GetWorldCollisionRect());
		ballCollision = true;
	}

	if (!ballCollision)
		pBall->VOnCollision(false, this);
}


void CBreakOut::Draw(unsigned int deltaT, CGfx* pGfx)
{
	// Draw background if required

	// Draw all the entities.
	// We can arrange it so that we draw certain objects first.
	// For now we just render all in any order.
	for (auto const &mapIt : m_entities) {
		for (auto const &vecIt : mapIt.second) {
            if(vecIt->IsActive())
                vecIt->VDraw(deltaT, pGfx);
		}
	}
}


std::vector<std::shared_ptr<CBaseEntity>>* CBreakOut::GetEntities(const std::string& key)
{
	auto found = m_entities.find(key);

	if (found != m_entities.end())
		return &found->second;

	return nullptr;
}


CBaseEntity* CBreakOut::GetEntity(const std::string& key, unsigned int index)
{
	auto found = m_entities.find(key);

	if (found != m_entities.end())
	{
		if (found->second.size() > 0 && found->second.size () > index) {
			return found->second[index].get();
		}
	}

	return nullptr;
}


void CBreakOut::LoadLevel(CLevel* pLevel)
{
	// Clear out any existing bricks
	m_entities["bricks"].clear();

    // Grab common properties for the bricks
	for (const auto& brick : pLevel->m_brickPositions) {
		const auto& pBrick = std::shared_ptr<CBaseEntity>(new CBrick);

        pBrick->SetActive(true);
        pBrick->SetCollisionRect(m_brickDrawFrame);
        pBrick->SetSpriteID(m_brickTextureID);
        pBrick->SetTextureFrame(m_brickDrawFrame);
		pBrick->SetPosition(brick);

		m_entities["bricks"].push_back(pBrick);
	}
}



int CBreakOut::GetMaxLevels()
{
	return (int)m_levelMgr->m_bricks.size();
}