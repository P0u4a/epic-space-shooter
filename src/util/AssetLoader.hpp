#ifndef SRC_UTIL_ASSETLOADER_HPP
#define SRC_UTIL_ASSETLOADER_HPP

#include "util/FileSystem.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <unordered_map>

class AssetLoader
{
  public:
    /**
     * @brief Load asset from /assets dir, caching on load
     *
     * @tparam T The type of asset - must have a loadFromFile method e.g. sf::Texture, sf::Font
     * @param asset A pointer that will be set to point to the loaded asset
     * @param asset_rel_path The path to the asset relative to /assets
     */
    template <typename T> static void loadAsset(T *&asset, const std::string &asset_rel_path);
};

template <typename T> inline void AssetLoader::loadAsset(T *&asset, const std::string &asset_rel_path)
{
    // Store loaded asset of type T for duration of program
    static std::unordered_map<std::string, T> assets;
    // If asset hasn't been loaded into cache yet
    if (!assets.count(asset_rel_path))
    {
        T tmp_asset;
        // Load asset from file
        if (!tmp_asset.loadFromFile(FileSystem::getExecutablePath() + "assets/" + asset_rel_path))
            // Error while loading asset
            exit(1); // NOLINT(concurrency-mt-unsafe)
        // Place asset in cache
        assets[asset_rel_path] = tmp_asset;
    }
    // Set 'asset' to point to cached asset
    asset = &assets[asset_rel_path];
}

#endif // SRC_UTIL_ASSETLOADER_HPP
