#pragma once

#include <vector>
#include <variant>
#include <bitset>
#include <unordered_map>
#include <typeindex>
#include <set>

using std::vector;
using std::unordered_map;
using std::type_index;
using std::set;
using std::forward;

const unsigned int FYR_Max_Components = 32;
typedef std::bitset<FYR_Max_Components> Signature;


struct BComponent
{
protected:
	static int nextId;
};

template <typename T>
class Component : public BComponent
{
	static int GetId() { static auto id = nextId++;  return id; }
};

/*
* @brief Entity - Objects with in-game agency
*/
class Entity
{
private:
	int id;

public:
	Entity(int id) : id(id) {};
	Entity(const Entity& entity) = default;
	int GetId() const { return id; };

	// Operator Overload
	Entity& operator = (const Entity& other) = default;
	bool operator == (const Entity& other) const { return id == other.id; }
	bool operator != (const Entity& other) const { return id != other.id; }
	bool operator > (const Entity& other) const { return id > other.id; }
	bool operator < (const Entity& other) const { return id < other.id; }
};

/*
* @brief System - Manage Entity Components
*/
class System
{
private:
	Signature componentSignature;
	vector<Entity> entities;

public:
	System() = default;
	~System() = default;

	void AddEntityToSystem(Entity entity);
	void RemoveEnitytFromSystem(Entity entity);
	vector<Entity> GetSystemEntities() const;
	const Signature& GetComponentSignature() const { return componentSignature; };

	// Typename to be considered by the system
	template <typename TComponent> void RequireComponent();
};

class BPool
{
public:
	virtual ~BPool(){}
};

/*
* @brief Pool - Wrap of standard vector
* 
* Iterate over entities and systems with ease
*/
template <typename T>
class Pool : public BPool
{
private:
	vector<T> data;
public:
	Pool(int size = 100) { Resize(size); }
	virtual ~Pool() = default;

	bool IsEmpty() const { return data.empty(); }
	int GetSize() const { return data.size(); }
	void Resize(int newSize) { data.resize(newSize); }
	void Clear() { data.clear(); }
	void Add(T object) { data.push_back(object); }
	void Set(int index, T object) { data[index] = object; }

	T& Get(int index) { return static_cast<T&>(data[index]); }
	T& operator [](unsigned int index) { return data[index]; }
};

/*
* @brief Registry - Manage entities creation and removal processes
*/
class Registry
{
private:

	// Number of entities
	int numberOfEntities = 0;

	set<Entity> entitiesToAdd;
	set<Entity> entitiesToRemove;

	// Vector of component pools
	vector<Pool<BPool>*> componentPools;

	// Available Components in a system
	vector<Signature> entityComponentSignatures;

	// Registered systems
	unordered_map<type_index, System*> systems;


public:

	Registry() = default;
	void Update();

	/// Register Entities

	Entity CreateEntity();
	void AddEntityToSystem(Entity entity);
	void RemoveEntity(Entity entity);

	/// Register Components

	template <typename TComponent, typename ...TArgs> void AddComponent(Entity entity, TArgs&& ...args);
	template <typename TComponent> void RemoveComponent(Entity entity);
	template <typename TComponent> bool HasComponent(Entity entity);

	/// Register Systems

	void AddSystem();
	void RemoveSystem();
	void HasSystem();
	void GetSystem();

};

/// Generics / Templates

/*
* @brief TComponent - Generic Component Declaration
*/
template <typename TComponent>
void System::RequireComponent()
{
	const auto componentId = Component<TComponent>::GetId();
	componentSignature.set(componentId);
}

// Registry

template <typename TComponent, typename ...TArgs> 
void Registry::AddComponent(Entity entity, TArgs&& ...args)
{
	const auto entityId = entity.GetId();
	const auto componentId = Component<TComponent>::GetId();

	// Increase component pools size when adding a component id
	if (componentId >= componentPools.size())
	{
		componentPools.resize(componentId + 1, nullptr);
	}

	// When no componentId found at componentPools index
	if (!componentPools[componentId])
	{
		// Create new component pool
		Pool<TComponent>* componentPool = new Pool<TComponent>();
		// Let index equals componentPool
		componentPools[componentId] = componentPool;
	}

	
	Pool<TComponent>* componentPool = componentPools[componentId];

	
	if(entityId >= componentPool->GetSize())
	{
		componentPool->Resize(numberOfEntities);
	}
	
	TComponent component(forward<TArgs>(args)...);

	componentPool->Set(entityId, component);

	entityComponentSignatures[entityId].set(componentId);
}

template <typename TComponent> 
void Registry::RemoveComponent(Entity entity)
{
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.GetId();

	entityComponentSignatures[entityId].set(componentId, false);
}

template <typename TComponent> 
bool Registry::HasComponent(Entity entity)
{
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.GetId();

	return entityComponentSignatures[entityId].test(componentId);
}
