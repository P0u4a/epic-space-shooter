#include "./AssetLoader.hpp"
#include "./FileSystem.hpp"
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <unordered_map>

void AssetLoader::loadTextureAsset(sf::Texture *&texture, const std::string &asset_rel_path)
{
    // If texture hasn't been loaded into cache yet
    if (!textures.count(asset_rel_path))
    {
        sf::Texture texture;
        // Load texture from file
        if (!texture.loadFromFile(FileSystem::getExecutablePath() + "assets/" + asset_rel_path))
            // Error while loading texture
            exit(1); // NOLINT(concurrency-mt-unsafe)
        // Place texture in cache
        textures[asset_rel_path] = texture;
    }
    // Set 'texture' to point to cached texture
    texture = &textures[asset_rel_path];
}
