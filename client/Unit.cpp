#include "Unit.h"
#include <utility>

#include <iostream>

#define LIFE_BAR_WIDTH 12
#define LIFE_BAR_HEIGHT 4
#define FRAME_DIMENSION 25
#define ATTACK_DIMENSION 6
#define VEHICLE_DEAD_ANIMATION 12
#define SOLDIER_DEAD_ANIMATION 9
#define IDENTIFIER_DIMENSION 4
#define LIFE_COMPLETE 4
#define NOROESTE 0
#define NORTE 1
#define NORESTE 2
#define OESTE 3
#define STILL 4
#define ESTE 5
#define SUROESTE 6
#define SUR 7
#define SURESTE 8
#define UNIT_OFFSET 0.5
#define BULLET_MOVEMENT 0.2

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
  animationId(newAnimationId),
  lifeId(LIFE_COMPLETE),
  isCurrentlyAttacking(false),
  isDead(false),
  isDying(false),
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
Pre-Condiciones: Actualiza el animation id.
Post-Condiciones: -
*/

void Unit::updateAnimationId(int oldAnimationId, int newAnimationId) {
    // solo si soy vehiculo
    if ((oldAnimationId == 4)) {
        if (newAnimationId == SUR) animationId = 9;
        if (newAnimationId == OESTE) animationId = 10;
        if (newAnimationId == NORTE) animationId = 11;
    }
    // era noroeste, noreste, suroeste, sur
    animationId = newAnimationId;
}

void Unit::calculateBulletPosition(float& direcX, float& direcY, int animationId) {
        switch (animationId) {
        case NOROESTE:
            direcX = posX  - static_cast<float>(UNIT_OFFSET) -
                     static_cast<float>(BULLET_MOVEMENT * attackAnimation.getFrame());
            direcY = posY - static_cast<float>(UNIT_OFFSET) -
                     static_cast<float>(BULLET_MOVEMENT * attackAnimation.getFrame());
            break;
        case NORTE:
            direcX = posX;
            direcY = posY - static_cast<float>(UNIT_OFFSET) -
                     static_cast<float>(BULLET_MOVEMENT * attackAnimation.getFrame());
            break;
        case NORESTE:
            direcX = posX + static_cast<float>(UNIT_OFFSET) +
                     static_cast<float>(BULLET_MOVEMENT * attackAnimation.getFrame());
            direcY = posY - static_cast<float>(UNIT_OFFSET) -
                     static_cast<float>(BULLET_MOVEMENT * attackAnimation.getFrame());
            break;
        case OESTE:
            direcX = posX - static_cast<float>(UNIT_OFFSET) -
                     static_cast<float>(BULLET_MOVEMENT * attackAnimation.getFrame());
            direcY = posY;
            break;
        case STILL:
            direcX = posX + static_cast<float>(UNIT_OFFSET) +
                     static_cast<float>(BULLET_MOVEMENT * attackAnimation.getFrame());
            direcY = posY;
            break;
        case ESTE:
            direcX = posX + static_cast<float>(UNIT_OFFSET) +
                     static_cast<float>(BULLET_MOVEMENT * attackAnimation.getFrame());
            direcY = posY;
            break;
        case SUROESTE:
            direcX = posX - static_cast<float>(UNIT_OFFSET) -
                     static_cast<float>(BULLET_MOVEMENT * attackAnimation.getFrame());
            direcY = posY + static_cast<float>(UNIT_OFFSET) +
                     static_cast<float>(BULLET_MOVEMENT * attackAnimation.getFrame());
            break;
        case SUR:
            direcX = posX;
            direcY = posY + static_cast<float>(UNIT_OFFSET) +
                     static_cast<float>(BULLET_MOVEMENT * attackAnimation.getFrame());
            break;
        case SURESTE:
            direcX = posX + static_cast<float>(UNIT_OFFSET) +
                     static_cast<float>(BULLET_MOVEMENT * attackAnimation.getFrame());;
            direcY = posY + static_cast<float>(UNIT_OFFSET) +
                     static_cast<float>(BULLET_MOVEMENT * attackAnimation.getFrame());
            break;
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
        calculateBulletPosition(direcX, direcY, animationId);
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
    // std::cout << "recibi la animacion " << newAnimationId << " y tengo propiety " << propiety << std::endl; 
    if (unitType < 7 && animationId == STILL) {
        // si era vehiculo y estaba quieto, cualq direc es rotacion
        updateAnimationId(animationId, newAnimationId);
    } else {
        animationId = newAnimationId;
    }
    getTexture();
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
            isDying = true;
        } else {
            animationId = SOLDIER_DEAD_ANIMATION;
            isDying = true;
        }
    }
}

bool Unit::getIsDying() {
    return isDying;
}

/*
Pre-Condiciones: Actualiza el animation id de la unidad y su textura.
Post-Condiciones: -
*/

void Unit::update(int delta) {
    if (isDead) return;
    // std::cout << "tengo el la propiety " << propiety << " y tengo la animacion " << animationId << std::endl;
    if (unitType < 7 && animationId == VEHICLE_DEAD_ANIMATION
        && animations.at(animationId).isLastFrame()) {
            // std::cout << "termino de mostrar la animacion\n";
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
    // quieto para vehiculo (no rotacion ni muerte)
    if (unitType < 7 && !(animationId >= 9 && animationId < 13)) {
        // std::cout << "retorne aca\n";
        return;
    }
    // quieto para soldado
    if (unitType > 6 && animationId == STILL) return;
    // std::cout << "lo updateo\n";
    animations.at(animationId).update(delta);
    getTexture();
    // soy vehiculo estoy en ultimo frame de rotacion
    if (unitType < 7 && animations.at(animationId).isLastFrame()
        && animationId != VEHICLE_DEAD_ANIMATION) {
        if (animationId == 9) {  // rotacion a sur
            animationId = 7;
        } else if (animationId == 10) {  // rotacion a oeste
            animationId = 3;
        } else {  // rotacion a norte
            animationId = 1;
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
  isDying(other.isDying),
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
