#include "Unit.h"
#include <utility>

#include <iostream>

#define LIFE_BAR_WIDTH 12
#define LIFE_BAR_HEIGHT 4
#define FRAME_DIMENSION 25
#define ATTACK_DIMENSION 6
#define VEHICLE_DEAD_ANIMATION 7
#define SOLDIER_DEAD_ANIMATION 5
#define IDENTIFIER_DIMENSION 4
#define LIFE_COMPLETE 4

/*
Pre-Condiciones: Constructor de Unit.
Post-Condiciones: -
*/

Unit::Unit(std::map<std::tuple<int, int>,
           SdlTexture>& newAnimationsRepository,
           std::map<int, SdlTexture>&  lifeTextures,
           std::vector<SdlTexture*> attackTextures,
           SdlTexture* identifierTexture,
           int sizeW,
           int sizeH,
           float posX,
           float posY,
           bool propiety,
           int unitType,
           int playerId,
           int newAnimationId)
: animationsRepository(newAnimationsRepository),
  lifeTextures(lifeTextures),
  attackTextures(attackTextures),
  identifierTexture(identifierTexture),
  attackAnimation(attackTextures),
  sizeW(sizeW),
  sizeH(sizeH),
  posX(posX),
  posY(posY),
  propiety(propiety),
  unitType(unitType),
  playerId(playerId),
  animationId(findAnimationId(newAnimationId)),
  lifeId(LIFE_COMPLETE),
  isCurrentlyAttacking(false),
  isDead(false),
  isTouched(false) {
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
        textures.push_back(&(animationsRepository.at(
            std::make_tuple(animationType, animationSprite))));
    }
    animations.emplace_back(std::move(textures));
    getTexture();
    getLifeTexture();
}

/*
Pre-Condiciones: Obtiene el id de animación según el tipo de .
Post-Condiciones: -
*/

int Unit::findAnimationId(int animationType) {
    if (animationType >= 0 && animationType < 3) return 0;
    if (animationType == 3) {
        return 1;
    }
    if (animationType == 5) {
        return 2;
    }
    if (animationType >= 6 && animationType < 9) return 3;
    if (unitType < 7) {
        if (animationType == 4) return 2;
    }
    return 4;
}

/*
Pre-Condiciones: Actualiza el animation id.
Post-Condiciones: -
*/

void Unit::updateAnimationId(int oldAnimationId, int newAnimationId) {
    // solo si soy vehiculo
    if ((oldAnimationId == 2)) {
        if (newAnimationId >= 0 && newAnimationId < 3) animationId = 6;
        if (newAnimationId == 3) animationId = 5;
        if (newAnimationId >= 6 && newAnimationId < 9) animationId = 4;
    }
}

/*
Pre-Condiciones: Renderiza la unidad
Post-Condiciones: -
*/

int Unit::render(Camera &camera, float posX, float posY) {
    if (isDead) return 0;
    if (isTouched) {
        Area frameArea(0, 0, FRAME_DIMENSION, FRAME_DIMENSION);
        camera.renderUnitFrame(frameArea, posX - 0.1, posY - 0.3);
    }
    if (isCurrentlyAttacking) {
        Area srcAttack(0, 0, ATTACK_DIMENSION, ATTACK_DIMENSION);
        float direcX, direcY;
        if (animationId == 0) {  // mirando al norte
            direcX = posX;
            direcY = posY - static_cast<float>(0.5) -
                     static_cast<float>(0.2 * attackAnimation.getFrame());
        } else if (animationId == 1) {  // mirando al oeste
            direcX = posX - static_cast<float>(0.5) -
                     static_cast<float>(0.2 * attackAnimation.getFrame());
            direcY = posY;
        } else if ((unitType < 7 && animationId == 2) ||
              (unitType > 6 && animationId == 4)) {  // mirando al este
            direcX = posX + static_cast<float>(0.5) +
                     static_cast<float>(0.2 * attackAnimation.getFrame());
            direcY = posY;
        } else {  // mirando al sur
            direcX = posX;
            direcY = posY + static_cast<float>(0.5) +
                     static_cast<float>(0.2 * attackAnimation.getFrame());
        }
        camera.renderInSightForUnit(attackAnimation.getTexture(),
                                    srcAttack, direcX, direcY);
    }
    Area srcLife(0, 0, LIFE_BAR_WIDTH, LIFE_BAR_HEIGHT);
    camera.renderInSightForUnit(currentLifeTexture, srcLife, posX, posY - 0.2);
    Area srcIdentifier(0, 0, IDENTIFIER_DIMENSION, IDENTIFIER_DIMENSION);
    camera.renderInSightForUnit(identifierTexture, srcIdentifier,
                                posX + 0.5, posY - 0.2);
    Area src(0, 0, sizeW, sizeH);
    return camera.renderInSightForUnit(texture, src, posX, posY);
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve la posición x de la unidad.
*/

float Unit::getX() {
    return posX;
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve la posición y de la unidad.
*/

float Unit::getY() {
    return posY;
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve el ancho de la unidad.
*/

int Unit::getWidth() {
    return sizeW;
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve el largo de la unidad.
*/

int Unit::getHeight() {
    return sizeH;
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve true si la unidad es del jugador 
o false si no.
*/

bool Unit::getPropiety() {
    return propiety;
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve el animation id de la unidad.
*/

int Unit::getAnimationId() {
    return animationId;
}

/*
Pre-Condiciones: Determina el animation id de la unidad.
Post-Condiciones: -
*/

void Unit::setAnimationId(int newAnimationId) {
    if (unitType < 7 && animationId == 2) {
        // si era vehiculo y estaba quieto, cualq direc es rotacion
        updateAnimationId(animationId, newAnimationId);
    } else {
        animationId = findAnimationId(newAnimationId);
    }
}

/*
Pre-Condiciones: Determina la nueva posición de la unidad.
Post-Condiciones: -
*/

void Unit::setNewPosition(float x, float y) {
    posX = x;
    posY = y;
}

/*
Pre-Condiciones: Determina la textura de la unidad.
Post-Condiciones: -
*/

void Unit::getTexture() {
    texture = animations.at(animationId).getTexture();
}

/*
Pre-Condiciones: Determina la textura de la barra de vida de la unidad.
Post-Condiciones: -
*/

void Unit::getLifeTexture() {
    currentLifeTexture = &(lifeTextures.at(lifeId));
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve true si la unidad esta muerta o false si no.
*/

bool Unit::getIsDead() {
    return isDead;
}

/*
Pre-Condiciones: Setea en true que la unidad esta muerta.
Post-Condiciones: -
*/

void Unit::kill() {
    isDead = true;
}

/*
Pre-Condiciones: Setea en true que la unidad fue tocada.
Post-Condiciones: -
*/

void Unit::setIsTouched(bool status) {
    isTouched = status;
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve el tipo de unidad.
*/

int Unit::getUnitType() {
    return unitType;
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve true si la unidad esta atacando o false si no.
*/

bool Unit::isAttacking() {
    return isCurrentlyAttacking;
}


/*
Pre-Condiciones: Setea a la unidad en ataque.
Post-Condiciones: -
*/

void Unit::startAttacking() {
    isCurrentlyAttacking = true;
    attackAnimation.reset();
}

/*
Pre-Condiciones: Actualiza la vida de la unidad.
Post-Condiciones: -
*/

void Unit::updateLife(int currentLife, int totalLife) {
    lifeId = static_cast<int>(currentLife / (totalLife / 4));
    if (lifeId == 0) lifeId = 1;
    getLifeTexture();
    if (currentLife == 0) {
        if (unitType < 7) {
            animationId = VEHICLE_DEAD_ANIMATION;
        } else {
            animationId = SOLDIER_DEAD_ANIMATION;
        }
    }
}

/*
Pre-Condiciones: Actualiza el animation id de la unidad y su textura.
Post-Condiciones: -
*/

void Unit::update(int delta) {
    if (isDead) return;
    if (unitType < 7 && animationId == VEHICLE_DEAD_ANIMATION
        && animations.at(animationId).isLastFrame()) {
            isDead = true;
            return;
    }
    if (unitType > 6 && animationId == SOLDIER_DEAD_ANIMATION
        && animations.at(animationId).isLastFrame()) {
            isDead = true;
            return;
    }
    if (isCurrentlyAttacking) {
        if (attackAnimation.isLastFrame()) {
            isCurrentlyAttacking = false;
        } else {
            attackAnimation.update(delta);
        }
    }
    // quieto para vehiculo
    if (unitType < 7 && !(animationId >= 4 && animationId < 8)) return;
    // quieto para soldado
    if (unitType > 6 && animationId == 4) return;
    animations.at(animationId).update(delta);
    getTexture();
    // soy vehiculo estoy en ultimo frame
    if (unitType < 7 && animations.at(animationId).isLastFrame()
        && animationId != VEHICLE_DEAD_ANIMATION) {
        if (animationId == 4) {
            animationId = 3;
        } else if (animationId == 5) {
            animationId = 1;
        } else {
            animationId = 0;
        }
    }
}

/*
Pre-Condiciones: Constructor de Unit.
Post-Condiciones: -
*/

Unit::Unit(Unit &&other)
: animations(std::move(other.animations)),
  animationsRepository(other.animationsRepository),
  lifeTextures(other.lifeTextures),
  attackTextures(other.attackTextures),
  identifierTexture(other.identifierTexture),
  attackAnimation(std::move(other.attackAnimation)),
  sizeW(other.sizeW),
  sizeH(other.sizeH),
  posX(other.posX),
  posY(other.posY),
  propiety(other.propiety),
  unitType(other.unitType),
  playerId(other.playerId),
  animationId(other.animationId),
  lifeId(other.lifeId),
  isCurrentlyAttacking(other.isCurrentlyAttacking),
  isDead(other.isDead),
  isTouched(other.isTouched),
  texture(other.texture),
  currentLifeTexture(other.currentLifeTexture) {
}

/*
Pre-Condiciones: Destructor de Unit.
Post-Condiciones: -
*/

Unit::~Unit() {
}
