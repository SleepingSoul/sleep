#include "stdafx.h"
#include "Transform2D.h"

BEGIN_NAMESPACE_SLEEP

Transform2D::Transform2D() noexcept(true)
    : Base(getComponentTypeID <Transform2D>())
{}

Transform2DData Transform2D::getGlobalData() const
{
	auto data = m_data;

	auto const relativeTransform = getRelativeTransform();

	data.Position += relativeTransform.Position;
	data.Rotation += relativeTransform.Rotation;

	return data;
}

Transform2D::RelativeTransform Transform2D::getRelativeTransform() const
{
	RelativeTransform transform;

	auto const* const hierarchyNode = m_object->getComponent<HierarchyNode>();

	if (!hierarchyNode)
	{
		return transform;
	}

	auto const* parent = hierarchyNode->getParent();

	while (parent)
	{
		auto const* const parentsTransform2D = parent->getComponent<Transform2D>();

		if (!parentsTransform2D)
		{
			break;
		}

		transform.Position += parentsTransform2D->getPosition();
		transform.Rotation += parentsTransform2D->getRotation();

		auto const* const parentsHierarchyNode = parent->getComponent<HierarchyNode>();

		parent = parentsHierarchyNode->getParent();
	}

	return transform;
}

void Transform2D::translate(glm::vec2 translation)
{
    setPosition(getPosition() + translation);
}

void Transform2D::rotate(float rotation)
{
    setRotation(getRotation() + rotation);
}

END_NAMESPACE_SLEEP
