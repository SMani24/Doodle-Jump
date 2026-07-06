/* ========== Naming Convention Guideline ==========
 * Class names: PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * ================================================= */

#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <map>
#include <string>
#include <memory>
#include <stdexcept>

template <typename T>
class ResourceManager {
private:
    std::map<std::string, std::shared_ptr<T>> resourceMap;

public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    void loadResource(const std::string& resourceId, const std::string& filePath);
    std::shared_ptr<T> getResource(const std::string& resourceId) const;
};

template <typename T>
void ResourceManager<T>::loadResource(const std::string& resourceId, const std::string& filePath) {
    if (resourceMap.find(resourceId) != resourceMap.end()) {
        return; 
    }

    std::shared_ptr<T> newResource = std::make_shared<T>();
    
    if (!newResource->loadFromFile(filePath)) {
        throw std::runtime_error("Failed to load resource: " + filePath);
    }

    resourceMap[resourceId] = newResource;
}

template <typename T>
std::shared_ptr<T> ResourceManager<T>::getResource(const std::string& resourceId) const {
    auto iterator = resourceMap.find(resourceId);
    
    if (iterator != resourceMap.end()) {
        return iterator->second;
    }
    
    throw std::runtime_error("Resource not found in memory: " + resourceId);
}

#endif // RESOURCE_MANAGER_HPP