// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

class Scene
{
public:
    using Initer = std::function<void()>;

    Scene(Initer&& initer, std::string_view id);

    std::string_view getID() const { return m_id; }

    void init() { m_initer(); }

private:
    Initer m_initer;
    std::string m_id;
};

END_NAMESPACE_SLEEP
