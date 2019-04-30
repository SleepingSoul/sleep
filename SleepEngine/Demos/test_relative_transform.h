// Copyright 2019 Tihran Katolikian

#pragma once


class TestRelativeSceneIniter
{
public:
    void operator ()(slp::Game::Scene& scene) const
    {
        auto background = slp::createRenderableObject();
        auto* const renderer = background->getComponent<slp::Renderer>();

        auto* const bgTexture = slp::globalResourceManager().getTexture(slp::Textures::LiMing);
        renderer->setTexture(bgTexture);

        auto* const transform = background->getComponent<slp::Transform2D>();

        transform->setSize(slp::pixelsToMeters(bgTexture->getSize()));

        auto initialCiri = createCirilla();

        auto* prevCiri = initialCiri.get();

        for (size_t i = 0; i < 5; ++i)
        {
            auto ciri = createCirilla();
            
            prevCiri = slp::getHierarchy(*prevCiri).addChild(std::move(ciri));
        }

        scene.addToRoot(std::move(background));
        scene.addToRoot(std::move(initialCiri));
    };

private:

    std::unique_ptr <slp::Object> createCirilla() const
    {
        auto ciri = slp::createRenderableObject();
        slp::getRenderer(*ciri).setTexture(slp::globalResourceManager().getTexture(slp::Textures::Cirilla));

        auto* const transform = ciri->getComponent<slp::Transform2D>();
        transform->setPosition({ 1.f, 0.f });
        transform->setRotation(25.f);
        transform->setSize({ 5.f, 5.f });

        ciri->addComponent<slp::HierarchyNode>();

        return ciri;
    }
};
