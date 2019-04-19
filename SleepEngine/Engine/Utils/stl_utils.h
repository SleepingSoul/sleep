#pragma once

#pragma region Check Find

template <class TContainer>
bool Contains(TContainer const& container, typename TContainer::const_reference value)
{
    return std::find(container.cbegin(), container.cend(), value) != container.cend();
}

template <class TContainer, class TPred>
bool ContainsIf(TContainer const& container, TPred pred)
{
    return FindIf(container, pred) != container.cend();
}

template <class TContainer, class TPred>
bool All(TContainer const& container, TPred pred)
{
    return std::all_of(container.cbegin(), container.cend(), pred);
}

// true if no elements from v1 are found in v2
template <class T>
bool AreDistinct(std::vector<T> const& v1, std::vector<T> const& v2)
{
    return Intersection(v1, v2).empty();
}

// complexity: len v1 * len v2
template <class TContainer, class TOtherContainer>
bool AreDistinctFind(TContainer const& v1, TOtherContainer const& v2)
{
    using Ref = typename TContainer::const_reference;
    static_assert(std::is_same_v<Ref, typename TOtherContainer::const_reference>,
        "TContainer and TOtherContainer must hold elements of same type");

    return All(v1, [&v2](Ref element){
            return !Contains(v2, element);
        });
}

template <class TContainer, class TPred>
typename TContainer::const_iterator FindIf(TContainer const& container, TPred pred)
{
    return std::find_if(container.cbegin(), container.cend(), pred);
}

template <class TContainer>
bool AreUnique(TContainer container)
{
    auto oldEnd = container.cend();
    auto it = std::unique(container.begin(), container.end());
    return it == oldEnd;
}

#pragma endregion

#pragma region Transform Map

// complexity: N + NLogN + 2*(N)-1 where N = len v1 + len v2
template <class T>
std::vector<T> Intersection(std::vector<T> v1, std::vector<T> v2)
{
    std::vector<T> v3;

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));

    return v3;
}

template <class TContainer, class TContainerToAppend>
void Append(TContainer& base, TContainerToAppend const& toAppend)
{
    std::copy(toAppend.cbegin(), toAppend.cend(), back_inserter(base));
}

template <class TContainer>
void RemoveIf(TContainer& container, std::function<bool(typename TContainer::const_reference)> pred)
{
	auto it = std::remove_if(container.begin(), container.end(), pred);
	container.erase(it, container.cend());
}

// transforms toMap container to another by applying mapFunction to each element of toMap container
template <class TOut, class InContainer>
std::vector<TOut> Map(InContainer const& toMap,
                      std::function<TOut(typename InContainer::const_reference)> mapFunc)
{
    std::vector<TOut> res;
    for (auto const& element : toMap)
    {
        res.push_back(mapFunc(element));
    }
    assert(res.size() == toMap.size());
    return res;
}

template <class TContainer>
TContainer Filter(TContainer const& orig, std::function<bool(typename TContainer::const_reference)> filter)
{
    TContainer filtered;
    std::copy_if(orig.cbegin(), orig.cend(), std::back_inserter(filtered), filter);
    assert(filtered.size() <= orig.size());
    return filtered;
}

#pragma endregion


