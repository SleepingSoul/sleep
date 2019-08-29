// Copyright 2019 Taras Martyniuk
#pragma once

BEGIN_NAMESPACE_SLEEP

#pragma region Non changing

template <class TContainer>
bool contains(TContainer const& container, typename TContainer::const_reference value)
{
    return std::find(container.cbegin(), container.cend(), value) != container.cend();
}

template <class TContainer, class TPred>
bool containsIf(TContainer const& container, TPred pred)
{
    return findIf(container, pred) != container.cend();
}

template <class TContainer, class TValue>
std::pair<bool, typename TContainer::const_iterator> find(TContainer const& container, TValue const& value)
{
    auto const cend = container.cend();
    auto const it = std::find(container.cbegin(), cend, value);
    return { it != cend, it };
}

template <class TContainer, class TValue>
std::pair<bool, typename TContainer::iterator> find(TContainer& container, TValue const& value)
{
    auto const end = container.end();
    auto const it = std::find(container.begin(), end, value);
    return { it != end, it };
}

template <class TContainer, class TPred>
std::pair<bool, typename TContainer::const_iterator> findIf(TContainer const& container, TPred pred)
{
    auto const cend = container.cend();
    auto const it = std::find_if(container.cbegin(), cend, pred);
    return { it != cend, it };
}

template <class TContainer, class TPred>
std::pair<bool, typename TContainer::iterator> findIf(TContainer& container, TPred pred)
{
    auto const end = container.end();
    auto const it = std::find_if(container.begin(), end, pred);
    return { it != end, it };
}

template <class TContainer, class TPred>
bool all(TContainer const& container, TPred pred)
{
    return std::all_of(container.cbegin(), container.cend(), pred);
}

// true if no elements from v1 are found in v2
template <class T>
bool areDistinct(std::vector<T> const& v1, std::vector<T> const& v2)
{
    return intersection(v1, v2).empty();
}

// complexity: len v1 * len v2
template <class TContainer, class TOtherContainer>
bool areDistinctFind(TContainer const& v1, TOtherContainer const& v2)
{
    using Ref = typename TContainer::const_reference;
    static_assert(std::is_same_v<Ref, typename TOtherContainer::const_reference>,
        "TContainer and TOtherContainer must hold elements of same type");

    return all(v1, [&v2](Ref element){
            return !contains(v2, element);
        });
}

template <class TContainer>
bool areUnique(TContainer container)
{
    auto oldEnd = container.cend();
    auto it = std::unique(container.begin(), container.end());
    return it == oldEnd;
}

#pragma endregion

#pragma region Changing

// complexity: N + NLogN + 2*(N)-1 where N = len v1 + len v2
template <class T>
std::vector<T> intersection(std::vector<T> v1, std::vector<T> v2)
{
    std::vector<T> v3;

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));

    return v3;
}

template <class TContainer, class TContainerToAppend>
void append(TContainer& base, TContainerToAppend const& toAppend)
{
    std::copy(toAppend.cbegin(), toAppend.cend(), back_inserter(base));
}

// pred signature : bool(typename TContainer::const_reference)
template <class TContainer, class TPred>
void removeIf(TContainer& container, TPred pred)
{
    auto it = std::remove_if(container.begin(), container.end(), pred);
    container.erase(it, container.cend());
}

// transforms toMap container to another by applying mapFunction to each element of toMap container
// mapFunc signature: TOut(typename InContainer::const_reference)
template <class TOut, class InContainer, class TMapFunc>
std::vector<TOut> map(InContainer const& toMap, TMapFunc mapFunc)
{
    std::vector<TOut> res;
    for (auto const& element : toMap)
    {
        res.push_back(mapFunc(element));
    }
    assert(res.size() == toMap.size());
    return res;
}

// filter signature: bool(typename TContainer::const_reference)
template <class TContainer, class TFilter>
TContainer filter(TContainer const& orig, TFilter filter)
{
    TContainer filtered;
    std::copy_if(orig.cbegin(), orig.cend(), std::back_inserter(filtered), filter);
    assert(filtered.size() <= orig.size());
    return filtered;
}

#pragma endregion

#define SLP_ELEMENT_NOT_IN_MAP_MSG "Element not found in the map"

 //asserts when not found
template <class TMap>
bool tryGetCopy(TMap const& map, typename TMap::key_type const& key, typename TMap::mapped_type& outElement, std::string_view message = SLP_ELEMENT_NOT_IN_MAP_MSG)
{
    // can prevent copypaste by reusing ptr variant, but it actually takes more code
    auto it = map.find(key);
    if (it == map.end())
    {
        LOG_AND_FAIL(message)
        return false;
    }

    outElement = it->second;
    return true;
}


template <class TMap>
bool tryGet(TMap& map, typename TMap::key_type const& key, typename TMap::mapped_type*& outElement, std::string_view message = SLP_ELEMENT_NOT_IN_MAP_MSG)
{
    typename TMap::mapped_type const* element = nullptr;
    bool const found = tryGet(map, key, element);
    // god save const cast
    outElement = const_cast<typename TMap::mapped_type*>(element);
    return found;
}

template <class TMap>
bool tryGet(TMap const& map, typename TMap::key_type const& key, typename TMap::mapped_type const*& outElement, std::string_view message = SLP_ELEMENT_NOT_IN_MAP_MSG)
{
    auto it = map.find(key);
    if (it == map.cend())
    {
        LOG_AND_FAIL(message)
        return false;
    }

    outElement = &(it->second);
    return true;
}

END_NAMESPACE_SLEEP
