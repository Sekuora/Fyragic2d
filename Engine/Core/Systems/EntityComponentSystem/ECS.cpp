#include "ECS.h"
#include <iostream>
#include <Log.h>

using std::find;
using std::remove_if;

void System::AddEntityToSystem(Entity entity)
{
	entities.push_back(entity);

}

void System::RemoveEnitytFromSystem(Entity entity)
{
	entities.erase(remove_if(entities.begin(), entities.end(), [&entity](Entity other)
		{
			return entity == other;
		}),
		entities.end());


}

std::vector<Entity> System::GetSystemEntities() const
{
	return std::vector<Entity>();
}
	

Entity Registry::CreateEntity()
{
	int entityId;

	entityId = numEntities++;

	Entity entity(entityId);

	entitiesToAdd.insert(entity);

	Log::Message("Entity created with id = " + std::to_string(entityId));

	return entity;

}

void Registry::Update()
{

}