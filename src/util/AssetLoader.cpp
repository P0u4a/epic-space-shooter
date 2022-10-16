#include "./AssetLoader.hpp"
#include "./FileSystem.hpp"
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <unordered_map>

void AssetLoader::loadTextureAsset(sf::Texture &texture, const std::string &asset_rel_path)
{
    if (!textures.count(asset_rel_path))
    {
        sf::Texture texture;
        if (!texture.loadFromFile(FileSystem::getExecutablePath() + "assets/" + asset_rel_path))
            // Error while loading texture
            exit(1); // NOLINT(concurrency-mt-unsafe)
        textures[asset_rel_path] = texture;
    }

    texture = textures[asset_rel_path];
}
