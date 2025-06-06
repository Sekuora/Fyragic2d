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

const unsigned int FYR_Max_Components = 32;
typedef std::bitset<FYR_Max_Components> Signature;


struct BaseComponent
{
protected:
	static int nextId;

};

template <typename T>
class Component : public BaseComponent
{
	static int GetId() { static auto id = nextId++;  return id; }

};


class Entity
{
private:
	int id;

public:
	Entity(int id) : id(id) {};
	Entity(const Entity& entity) = default;
	int GetId() const { return id; };

	Entity& operator = (const Entity& other) = default;
	bool operator == (const Entity& other) const { return id == other.id; }
	bool operator != (const Entity& other) const { return id != other.id; }
	bool operator > (const Entity& other) const { return id > other.id; }
	bool operator < (const Entity& other) const { return id < other.id; }
};

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
	std::vector<Entity> GetSystemEntities() const;
	const Signature& GetComponentSignature() const { return componentSignature; };

	// Typename to be considered by the system
	template <typename TComponent> void RequireComponent();

};

class BasePool
{
public:
	virtual ~BasePool(){}
};

template <typename T>
class Pool : public BasePool
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

class Registry
{
private:

	// Number of entities
	int numEntities = 0;

	set<Entity> entitiesToAdd;
	set<Entity> entitiesToRemove;

	vector<Pool<BasePool>*> componentPools;

	vector<Signature> entityComponentSignatures;

	unordered_map<type_index, System*> systems;


public:

	Registry() = default;
	void Update();

	Entity CreateEntity();
	void AddEntityToSystem(Entity entity);
	void RemoveEntity(Entity entity);

	void AddComponent(Entity entity);
	void RemoveComponent(Entity entity);
	void HasComponent(Entity entity);

	void AddSystem();
	void RemoveSystem();
	void HasSystem();
	void GetSystem();


};




template <typename TComponent>
void System::RequireComponent()
{
	const auto componentId = Component<TComponent>::GetId();
	componentSignature.set(componentId);
}