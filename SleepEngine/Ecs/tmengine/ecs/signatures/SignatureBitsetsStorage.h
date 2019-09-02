//
// Created by Taras Martyniuk on 7/25/2018.
//
#ifndef SFML_GAME_ENGINE_SIGNATUREBITSETSSTORAGE_H
#define SFML_GAME_ENGINE_SIGNATUREBITSETSSTORAGE_H
#include <array>
#include <ecs/signatures/SignatureBitsets.h>
#include <ecs/signatures/brigand_type_macro.h>

namespace tmengine::ecs
{
    // holds all the bitsets for the signatures,
    // bitsets are init-ed (at runtime) depending on TSettings param,
    // which is parsed through meta-programming (at compile time)
    // TSettings must be a ecs::Settings
    template<typename TSettings>
    class SignatureBitsetsStorage
    {
    private:
        using SignatureBitsets = ::tmengine::ecs::SignatureBitsets<TSettings>;
    public:
        using Bitset = typename SignatureBitsets::Bitset;

        SignatureBitsetsStorage()
        {
            brigand::for_each<typename TSettings::Signatures>([this](auto x) {
                this->initializeBitset<BRIGAND_TYPE(x)>();
            });
        }

        // retrieve signature-check bitset by signature type
        template<typename TSignature>
        const Bitset& getSignatureBitset() const noexcept
        {
            static_assert(TSettings::template isSignature<TSignature>(), "");

            static const std::size_t kSignatureId = TSettings::template signatureId<TSignature>();
            return signature_bitsets_.at(kSignatureId);
        }

    private:
        // constant of the time of compilation...
        // but oh what wonders can we do before that!
        static const int kSignaturesCount = TSettings::signatureCount();

        std::array<Bitset, kSignaturesCount> signature_bitsets_;

    private:
        template<typename TSignature>
        Bitset& getNonConstSignatureBitset() noexcept
        {
            return const_cast<Bitset&>(
                static_cast<const SignatureBitsetsStorage&>(*this).
                    getSignatureBitset<TSignature>()
                );
        }

        template<typename TSignature>
        void initializeBitset() noexcept
        {
            auto& bitset(this->getNonConstSignatureBitset<TSignature>());

            using SignatureComponents =
                typename SignatureBitsets::template SignatureComponents<TSignature>;
            using SignatureTags =
                typename SignatureBitsets::template SignatureTags<TSignature>;

            brigand::for_each<SignatureComponents>(
                [&bitset](auto component) {
                bitset.set(SignatureBitsets::template componentBit<BRIGAND_TYPE(component)>());
            });
            brigand::for_each<SignatureTags>(
                [&bitset](auto tag) {
                bitset.set(SignatureBitsets::template tagBit<BRIGAND_TYPE(tag)>());
            });
        }
    };
}
#endif //SFML_GAME_ENGINE_SIGNATUREBITSETSSTORAGE_H
