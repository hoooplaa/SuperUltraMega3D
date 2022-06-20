#pragma once

#include "Engine/Core/Math/Vec.h"
#include "Engine/Graphics/Objects/Model.h"
#include "Engine/Scene.h"

namespace Mega
{
    class Entity
    {
    public:
        Entity();
        ~Entity();
        virtual void Initialize();
        virtual void Destroy();

        virtual void RunFrame();
        virtual void Render(const std::shared_ptr<Scene> in_scene);

        void SetModel(Model& in_model);
        void SetModel(VertexData& in_vData, TextureData& in_tData);

        Vec3F GetModelPosition() const { return m_model.GetPosition(); }
        Vec3F GetModelRotation() const { return m_model.GetRotation(); }
        Vec3F GetModelScale()    const { return m_model.GetScale(); }

        void SetColor(const Vec3F& in_c) { m_model.SetColor(in_c); }

        void ChangeHealth(float in_fHealthChange) { m_fHealth += in_fHealthChange; }

        float GetHealth() const { return m_fHealth; }
        void SetHealth(const float in_fHealth) { m_fHealth = in_fHealth; }

        float GetMaxHealth() const { return m_fMaxHealth; }
        void SetMaxHealth(const float in_fMaxHealth) { m_fMaxHealth = in_fMaxHealth; }

        float GetSpeed() const { return m_fSpeed; }
        void SetSpeed(const float in_fSpeed) { m_fSpeed = in_fSpeed; }

    protected:
        Model m_model;

    private:
        float m_fMaxHealth;
        float m_fHealth;

        float m_fSpeed;
    };
}