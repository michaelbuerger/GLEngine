#ifndef GLE_SCENE_HPP
#define GLE_SCENE_HPP

#include "GLEngine/graphics/GameObject.hpp"

namespace GLEngine
{

class Scene
{
public:
    Scene(const uint& gameObjectsCount);
public:
    void AddGameObject(const GameObject& gameObject);
private:
    GameObject* m_gameObjectsArrayPtr;
    uint m_gameObjectsCount; // 
    uint m_gameObjectsIndex; // index of next game object to be added or equal to m_gameObjectsCount if max reached
};

}

#endif