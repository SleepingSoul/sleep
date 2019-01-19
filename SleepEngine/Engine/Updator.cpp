#include "stdafx.h"
#include "Updator.h"


void Updator::addChild(Updator* const child)
{
    m_children.push_back(child);
}

void Updator::addChildren(std::initializer_list <Updator*> children)
{
    m_children.insert(m_children.end(), children);
}

void Updator::update()
{
    for (auto* const child : m_children)
    {
        child->update();
    }
}

void Updator::render()
{
    for (auto* const child : m_children)
    {
        child->render();
    }
}
