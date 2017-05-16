#include "CollisionManager.h"
#include "Collider.h"
#include "GameObject.h"

//b2World* ce::CollisionManager::world;

std::map<Common::uint64, ce::Collider*> ce::CollisionManager::intToRectangles;
//std::map<Common::uint64, ce::Collider*> ce::CollisionManager::intToNewRectangles;

using ce::CollisionManager;


CollisionManager::CollisionManager()
{
	/*gravity.SetZero();
	world = new b2World(gravity);*/
}


CollisionManager::~CollisionManager()
{
}


//b2World* ce::CollisionManager::GetWorld()
//{
//	return world;
//}


void ce::CollisionManager::AddCollider(ce::Collider* collider)
{
	intToRectangles.insert(std::make_pair(collider->gameObject->GetID(), collider));
}


void ce::CollisionManager::RemoveCollider(ce::Collider* collider)
{
	if (collider != nullptr)
	{
		const unsigned long long ID = collider->gameObject->GetID();

		// Erases the collider from the map it belongs to
		/*if (collider->isNew)
			intToNewRectangles.erase(ID);
		else*/
			intToRectangles.erase(ID);
	}
}


void ce::CollisionManager::UpdateCollision()
{
	//world->Step(1.0f / 60.0f, 8, 3);
	for (auto it = intToRectangles.begin(); it != intToRectangles.end(); it++)
	{
		for (auto it2 = intToRectangles.begin(); it2 != intToRectangles.end(); it2++)
		{
			sf::FloatRect fRect = it->second->fRect;
			sf::FloatRect fRect2 = it2->second->fRect;

			if (fRect.intersects(fRect2) && fRect != fRect2)
			{
				if (it->second->isTrigger)
				{
					it->second->OnTrigger(it2->second->gameObject);
				}

				if (it2->second->isTrigger)
				{
					it2->second->OnTrigger(it->second->gameObject);
				}

				if (!it->second->isTrigger && !it2->second->isTrigger)
				{
					it->second->OnCollision(it2->second->gameObject);
					it2->second->OnCollision(it->second->gameObject);

					sf::Vector2f centerPos = sf::Vector2f(fRect.left + fRect.height / 2, fRect.top + fRect.width / 2);
					sf::Vector2f centerPos2 = sf::Vector2f(fRect2.left + fRect2.height / 2, fRect2.top + fRect2.width / 2);

					sf::Vector2f newPos;
					sf::Vector2f newPos2;

					bool move = false;
					bool move2 = false;

					if (it->second->transform->GetVelocity() != sf::Vector2f(0.0f, 0.0f))
					{
						/*enum sides{LEFT, RIGHT, TOP, DOWN};
						int side;

						if (centerPos.x < centerPos2.x)
						{
							side = LEFT;

							if (centerPos2 - )
						}

						switch (side)
						{
							case LEFT:
							case RIGHT:
							case TOP:
							case DOWN:
						}*/
						sf::Vector2f centerDist = centerPos2 - centerPos;
						//newPos = it->second->transform->GetPosition() - (sf::Vector2f(fRect2.width, fRect2.height) - centerDist);
						newPos = it->second->transform->GetPosition() - it->second->transform->GetVelocity();

						move = true;
					}

					if (it2->second->transform->GetVelocity() != sf::Vector2f(0.0f, 0.0f))
					{
						sf::Vector2f centerDist2 = centerPos - centerPos2;
						//newPos2 = it2->second->transform->GetPosition() - (sf::Vector2f(fRect.width, fRect.height) - centerDist2);
						newPos2 = it2->second->transform->GetPosition() - it2->second->transform->GetVelocity();
						move2 = true;
					}

					if (move)
					{
						it->second->transform->SetPosition(newPos);
						it->second->transform->ResetVelocity();
						move = false;
					}
					if (move2)
					{
						it2->second->transform->SetPosition(newPos2);
						it2->second->transform->ResetVelocity();
						move2 = false;
					}
				}
			}
		}
	}
}


