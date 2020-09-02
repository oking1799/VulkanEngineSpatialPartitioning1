#include "pch.h"
#include "GameObject.h"

#include "EntityManager.h"
#include "PhysicsManager.h"

#pragma region Constructor

GameObject::GameObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Transform> transform, std::shared_ptr<PhysicsObject> physicsObject)
{
	this->mesh = mesh;
	this->transform = transform;
	this->physicsObject = physicsObject;

	if (physicsObject != nullptr) {
		PhysicsManager::GetInstance()->AddPhysicsObject(physicsObject);
	}

	instanceId = -1;
	active = false;
}

#pragma endregion

#pragma region Accessors

std::shared_ptr<Transform> GameObject::GetTransform()
{
	return transform;
}

void GameObject::SetTransform(std::shared_ptr<Transform> value)
{
	transform = value;

	if (physicsObject != nullptr) {
		physicsObject->SetTransform(value);
	}
}

std::shared_ptr<PhysicsObject> GameObject::GetPhysicsObject()
{
	return physicsObject;
}

void GameObject::SetPhysicsObject(std::shared_ptr<PhysicsObject> value)
{
	physicsObject = value;
	PhysicsManager::GetInstance()->AddPhysicsObject(physicsObject);
}

std::shared_ptr<Mesh> GameObject::GetMesh()
{
	return mesh;
}

bool GameObject::GetActive()
{
	return active;
}

#pragma endregion

#pragma region Spawning

void GameObject::Init()
{
	physicsObject->GetCollider()->GenerateFromMesh(mesh);
	physicsObject->GetCollider()->ToggleVisible(true);
}

void GameObject::Spawn()
{
	if (transform == nullptr) {
		transform = std::make_shared<Transform>();
	}

	if (physicsObject == nullptr) {
		physicsObject = std::make_shared<PhysicsObject>(transform);
		PhysicsManager::GetInstance()->AddPhysicsObject(physicsObject);
	}

	instanceId = mesh->AddInstance(transform);
	physicsObject->SetAlive(true);
	active = true;
}

void GameObject::Despawn()
{
	mesh->RemoveInstance(instanceId);
	instanceId = -1;
	physicsObject->SetAlive(false);
	active = false;
}

#pragma endregion

#pragma region Update

void GameObject::Update()
{
}

#pragma endregion