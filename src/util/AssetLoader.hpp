#ifndef SRC_UTIL_ASSETLOADER_HPP
#define SRC_UTIL_ASSETLOADER_HPP

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <unordered_map>

class AssetLoader
{
  private:
    inline static std::unordered_map<std::string, sf::Texture> textures;

  public:
    static void loadTextureAsset(sf::Texture &texture, const std::string &asset_rel_path);
};

#endif // SRC_UTIL_ASSETLOADER_HPP
