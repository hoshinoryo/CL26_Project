/*
    ファイル名：game_character.h
    作成者：張 楽晨
    作成日：2026/06/11
    内容：プレイヤーとエネミーで共通して使うHP処理をまとめたクラス
*/
#pragma once

#include "game_object.h"
#include "game_damage.h"

class GameCharacter : public GameObject
{
private:
    int m_hp_capacity;
    int m_hp;

public:
    GameCharacter(GameWorld* world, const Float2& position, int hp, const std::string& tag)
        : GameObject(world, position, tag)
        , m_hp_capacity(hp)
        , m_hp(hp)
    {
    }

protected:
    int GetHp() const
    {
        return m_hp;
    }

    int GetHpCapacity() const
    {
        return m_hp_capacity;
    }

    bool DecreaseHP(int amount)
    {
        if (amount <= 0 || IsDestory())
        {
            return false;
        }

        m_hp -= amount;
        if (m_hp < 0)
        {
            m_hp = 0;
        }

        if (m_hp == 0)
        {
            Destory();
            return true;
        }

        return false;
    }

    void RecoverHP(int amount)
    {
        if (amount <= 0 || IsDestory())
        {
            return;
        }

        m_hp += amount;
        if (m_hp > m_hp_capacity)
        {
            m_hp = m_hp_capacity;
        }
    }
};
