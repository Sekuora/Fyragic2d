#include "ECS.h"
#include <iostream>
#include <Log.h>

using std::find;
using std::remove_if;
using std::to_string;



int BComponent::nextId = 0;


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

vector<Entity> System::GetSystemEntities() const
{
	return std::vector<Entity>();
}
	

Entity Registry::CreateEntity()
{
	int entityId;

	entityId = numberOfEntities++;

	Entity entity(entityId);

	entitiesToAdd.insert(entity);

	Log::Message("Entity created with id = " + to_string(entityId));

	return entity;

}

void Registry::Update()
{

}