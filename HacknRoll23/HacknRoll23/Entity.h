#ifndef entity_H
#define entity_H

#include "HitboxComponent.h"
#include "AttributeComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{

protected:
    sf::Sprite sprite;  
    HitboxComponent* hitboxComponent; 
    AttributeComponent* attributeComponent;
    MovementComponent* movementComponent;
    AnimationComponent* animationComponent;

public:
    //Constructor and destructor 
    Entity();
    virtual ~Entity();

    void initVariables();

    //Component functions   
    void setTexture(sf::Texture& texture);

    void createHitbox(sf::Sprite& sprite, float offsetX, float offsetY, float width, float height);
    void createAttribute(const int level, const int hpMax, const int damage);
    void createMovement(const float maxVelo, const float acceleration, const float drag);
    void createAnimation(sf::Texture& textureSheet);


    //Accessors
    HitboxComponent* getHitboxComponent();
    AttributeComponent* getAttributeComponent();
    MovementComponent* getMovementComponent();
    AnimationComponent* getAnimationComponent();

    virtual const sf::Vector2f& getPosition() const;
    virtual const sf::Vector2f& getSpritePosition() const;
    virtual const sf::Vector2f getCenter() const;
    virtual const sf::Vector2f getSpriteCenter() const;
    virtual const sf::Vector2i getGridPosition(const int gridSizeI) const;
    virtual const sf::FloatRect getGlobalBounds() const;
    virtual const sf::FloatRect getNextPositionBounds(const float& dt) const;
    sf::Sprite getSprite();

    //Mutator
    virtual void setPosition(const float x, const float y);

    //Functions 
    virtual void move(const float x, const float y, const float& dt);//passed into movement component
    virtual void stopVelocity();
    virtual void stopVelocityX();
    virtual void stopVelocityY();
    

    //Calculations
    virtual void checkCollision(const float& dt);
    virtual float getDistance(const Entity& entity) const; //used for collison and enemy movement logic
    virtual float getSpriteDistance(const Entity& entity) const; //center ± sprite center


    //Abstract functions
    virtual void update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox) = 0;
};

#endif