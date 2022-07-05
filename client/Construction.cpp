#include "Construction.h"
#include <utility>

#include <iostream>

#define STILL_ANIMATION 0
#define CREATE_ANIMATION 1
#define DEAD_ANIMATION 2
#define EXPLOSION_ANIMATION 3
#define LIFE_BAR_WIDTH 32
#define LIFE_BAR_HEIGHT 4
#define IDENTIFIER_DIMENSION 4

/*
Pre-Condiciones: Constructor de Construction.
Post-Condiciones: -
*/

Construction::Construction(std::map<std::tuple<int, int>,
                           SdlTexture>& newAnimationsRepository,
                           std::map<int, SdlTexture>& lifeTextures,
                           SdlTexture* identifierTexture,
                           int sizeW,
                           int sizeH,
                           float posX,
                           float posY,
                           int constType,
                           int playerId,
                           bool propiety,
                           int house)
: animationsRepository(newAnimationsRepository),
  lifeTextures(lifeTextures),
  identifierTexture(identifierTexture),
  sizeW(sizeW),
  sizeH(sizeH),
  posX(posX),
  posY(posY),
  house(house),
  constType(constType),
  playerId(playerId),
  propiety(propiety),
  animationId(1),
  lifeId(4),
  isDead(false),
  previosAnimationId(0) {
    int actualSprite = 0;
    std::vector<SdlTexture*> textures;
    for (const auto& [key, value] : animationsRepository) {
        if (std::get<0>(key) != actualSprite) {
            animations.emplace_back(textures);
            actualSprite = std::get<0>(key);
            textures.clear();
        }
        int animationType = std::get<0>(key);
        int animationSprite = std::get<1>(key);
        textures.push_back(&(animationsRepository.at(std::make_tuple(
                             animationType, animationSprite))));
    }
    animations.emplace_back(std::move(textures));
    getTexture();
    getLifeTexture();
}

/*
Pre-Condiciones: Se renderiza un edificio.
Post-Condiciones: -
*/

int Construction::render(Camera &camera, int posX, int posY) {
    if (isDead) return 0;
    Area srcLife(0, 0, LIFE_BAR_WIDTH, LIFE_BAR_HEIGHT);
    camera.renderInSightForUnit(currentLifeTexture, srcLife, posX, posY - 0.2);
    Area srcIdentifier(0, 0, IDENTIFIER_DIMENSION, IDENTIFIER_DIMENSION);
    camera.renderInSightForUnit(identifierTexture, srcIdentifier, posX + 1.2,
                                posY - 0.2);
    Area src(0, 0, sizeW, sizeH);
    return camera.renderInSightForUnit(texture, src, posX, posY);
}

/*
Pre-Condiciones: -
Post-Condiciones: Se obtiene la posicion x de un edificio.
*/

float Construction::getX() {
    return posX;
}

/*
Pre-Condiciones: -
Post-Condiciones: Se obtiene la posicion y de un edificio.
*/

float Construction::getY() {
    return posY;
}

/*
Pre-Condiciones: -
Post-Condiciones: Se obtiene la casa de un edificio.
*/

int Construction::getHouse() {
    return house;
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve true si el edificio es propiedad del
jugador o false si no.
*/

bool Construction::getPropiety() {
    return propiety;
}

/*
Pre-Condiciones: Devuelve el tipo de edificio.
Post-Condiciones: -
*/

int Construction::getConstType() {
    return constType;
}

/*
Pre-Condiciones: Devuelve la textura del edificio.
Post-Condiciones: -
*/

void Construction::getTexture() {
    texture = animations.at(animationId).getTexture();
}

/*
Pre-Condiciones: Devuelve el ancho del edificio.
Post-Condiciones: -
*/

int Construction::getWidth() {
    return sizeW;
}

/*
Pre-Condiciones: Devuelve el largo del edificio.
Post-Condiciones: -
*/

int Construction::getHeight() {
    return sizeH;
}

/*
Pre-Condiciones: Setea la textura para la barra de vida del edificio. 
Post-Condiciones: -
*/

void Construction::getLifeTexture() {
    currentLifeTexture = &(lifeTextures.at(lifeId));
}

/*
Pre-Condiciones: Devuelve true si el edificio fue destruido o false si no. 
Post-Condiciones: -
*/

bool Construction::getIsDead() {
    return isDead;
}

/*
Pre-Condiciones: Setea al edificio como destruido. 
Post-Condiciones: -
*/

void Construction::kill() {
    isDead = true;
}

/*
Pre-Condiciones: Actualiza la vida del edificio y con ella 
la textura para la barra de vida. En caso de que la vida sea 0, se va a 
setear la animación de destruccion. 
Post-Condiciones: -
*/

void Construction::updateLife(int currentLife, int totalLife) {
    lifeId = static_cast<int>(currentLife / (totalLife / 4));
    if (lifeId == 0) lifeId = 1;
    getLifeTexture();
    if (currentLife == 0) {
        animationId = DEAD_ANIMATION;
    }
}

/*
Pre-Condiciones: Actualiza el animation id de la construcción y en
caso de que sea distinto cambia la textura. 
Post-Condiciones: -
*/

void Construction::update(int delta) {
    if (isDead) return;
    if (animationId == DEAD_ANIMATION &&
        animations.at(animationId).isLastFrame()) {
        isDead = true;
        return;
    }
    if (animationId == STILL_ANIMATION) return;
    animations.at(animationId).update(delta);
    getTexture();
    if (animationId == EXPLOSION_ANIMATION &&
        animations.at(animationId).isLastFrame()) {
        animationId = previosAnimationId;
        getTexture();
        previosAnimationId = 0;
    }
    if (animations.at(animationId).isLastFrame() &&
        animationId == CREATE_ANIMATION) {
        animationId = STILL_ANIMATION;
    }
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve el id de la animación actual.
*/

int Construction::getAnimationId() {
    return animationId;
}

/*
Pre-Condiciones: Setea una explosión en el edificio.
Post-Condiciones: -
*/

void Construction::setExplosion() {
    previosAnimationId = animationId;
    animationId = EXPLOSION_ANIMATION;
    animations.at(animationId).reset();
    getTexture();
}

/*
Pre-Condiciones: Constructor de Construction.
Post-Condiciones: -
*/

Construction::Construction(Construction &&other)
: animations(std::move(other.animations)),
  animationsRepository(other.animationsRepository),
  lifeTextures(other.lifeTextures),
  identifierTexture(other.identifierTexture),
  sizeW(other.sizeW),
  sizeH(other.sizeH),
  posX(other.posX),
  posY(other.posY),
  constType(other.constType),
  playerId(other.playerId),
  propiety(other.propiety),
  animationId(other.animationId),
  lifeId(other.lifeId),
  isDead(other.isDead),
  previosAnimationId(other.previosAnimationId),
  texture(other.texture),
  currentLifeTexture(other.currentLifeTexture)
{}

/*
Pre-Condiciones: Destructor de Construction.
Post-Condiciones: -
*/

Construction::~Construction() {
}
