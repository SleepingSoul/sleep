// Copyright 2019 Taras Martyniuk
#pragma once

class Loadable
{
public:
    virtual ~Loadable() = default;

    GETTER(isLoaded, m_isLoaded);

    virtual void load()
    {
        m_isLoaded = doLoad();
    }

protected:
    // parses config file
    // true if success
    virtual bool doLoad() = 0;

private:
    bool m_isLoaded = false;
};
