#include "Unit.h"
#include <utility>

#include <iostream>

#define LIFE_BAR_WIDTH 12
#define LIFE_BAR_HEIGHT 4
#define FRAME_DIMENSION 25
#define ATTACK_DIMENSION 6
#define VEHICLE_DEAD_ANIMATION 12
#define SOLDIER_DEAD_ANIMATION 9
#define VEHICLE_EXPLOSION_ANIMATION 13
#define SOLDIER_EXPLOSION_ANIMATION 10
#define CONSTRUCTION_DEAD_ANIMATION 2
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
#define MAX_ITERATION 11
#define DEVASTATOR_ID 5
#define DEVASTATOR_DYING_DIMENSIONS 32
#define MISIL_ATTACK 1
#define CANION_P_ATTACK 5

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
  isTouched(false),
  destinationX(0),
  destinationY(0),
  bulletPaseX(BULLET_MOVEMENT),
  bulletPaseY(BULLET_MOVEMENT),
  reachedDestination(false),
  misilIteration(1),
  previosAnimationId(0),
  currentAttackType(0),
  attackedUnit(nullptr),
  attackedConstruction(nullptr) {
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

void Unit::calculateMisilPosition(float& direcX, float& direcY, int animationId) {
    // std::cout << "missil iteration es " << misilIteration << std::endl;
    switch (animationId) {
        case NOROESTE:
            direcX = posX  -
                     static_cast<float>(static_cast<float>(bulletPaseX) *
                     static_cast<float>(misilIteration));
            direcY = posY -
                     static_cast<float>(static_cast<float>(bulletPaseY) *
                     static_cast<float>(misilIteration));
            break;
        case NORTE:
            direcX = posX;
            direcY = posY -
                     static_cast<float>(static_cast<float>(bulletPaseY) *
                     static_cast<float>(misilIteration));
            break;
        case NORESTE:
            direcX = posX +
                     static_cast<float>(static_cast<float>(bulletPaseX) *
                     static_cast<float>(misilIteration));
            direcY = posY -
                     static_cast<float>(static_cast<float>(bulletPaseY) *
                     static_cast<float>(misilIteration));
            break;
        case OESTE:
            direcX = posX -
                     static_cast<float>(static_cast<float>(bulletPaseX) *
                     static_cast<float>(misilIteration));
            direcY = posY;
            break;
        case STILL:
            direcX = posX +
                     static_cast<float>(static_cast<float>(bulletPaseX) *
                     static_cast<float>(misilIteration));
            direcY = posY;
            break;
        case ESTE:
            direcX = posX +
                     static_cast<float>(static_cast<float>(bulletPaseX) *
                     static_cast<float>(misilIteration));
            direcY = posY;
            break;
        case SUROESTE:
            direcX = posX -
                     static_cast<float>(static_cast<float>(bulletPaseX) *
                     static_cast<float>(misilIteration));
            direcY = posY +
                     static_cast<float>(static_cast<float>(bulletPaseY) *
                     static_cast<float>(misilIteration));
            break;
        case SUR:
            direcX = posX;
            direcY = posY +
                     static_cast<float>(static_cast<float>(bulletPaseY) *
                     static_cast<float>(misilIteration));
            break;
        case SURESTE:
            direcX = posX +
                     static_cast<float>(static_cast<float>(bulletPaseX) *
                     static_cast<float>(misilIteration));
            direcY = posY +
                     static_cast<float>(static_cast<float>(bulletPaseY) *
                     static_cast<float>(misilIteration));
            break;
    }
}

void Unit::calculateBulletPosition(float& direcX, float& direcY, int animationId) {
    switch (animationId) {
        case NOROESTE:
            direcX = posX - static_cast<float>(UNIT_OFFSET) -
                     static_cast<float>(bulletPaseX * attackAnimation.getFrame());
            direcY = posY - static_cast<float>(UNIT_OFFSET) -
                     static_cast<float>(bulletPaseY * attackAnimation.getFrame());
            break;
        case NORTE:
            direcX = posX;
            direcY = posY - static_cast<float>(UNIT_OFFSET) -
                     static_cast<float>(bulletPaseY * attackAnimation.getFrame());
            break;
        case NORESTE:
            direcX = posX + static_cast<float>(UNIT_OFFSET) +
                     static_cast<float>(bulletPaseX * attackAnimation.getFrame());
            direcY = posY - static_cast<float>(UNIT_OFFSET) -
                     static_cast<float>(bulletPaseY * attackAnimation.getFrame());
            break;
        case OESTE:
            direcX = posX - static_cast<float>(UNIT_OFFSET) -
                     static_cast<float>(bulletPaseX * attackAnimation.getFrame());
            direcY = posY;
            break;
        case STILL:
            direcX = posX + static_cast<float>(UNIT_OFFSET) +
                     static_cast<float>(bulletPaseX * attackAnimation.getFrame());
            direcY = posY;
            break;
        case ESTE:
            direcX = posX + static_cast<float>(UNIT_OFFSET) +
                     static_cast<float>(bulletPaseX * attackAnimation.getFrame());
            direcY = posY;
            break;
        case SUROESTE:
            direcX = posX - static_cast<float>(UNIT_OFFSET) -
                     static_cast<float>(bulletPaseX * attackAnimation.getFrame());
            direcY = posY + static_cast<float>(UNIT_OFFSET) +
                     static_cast<float>(bulletPaseY * attackAnimation.getFrame());
            break;
        case SUR:
            direcX = posX;
            direcY = posY + static_cast<float>(UNIT_OFFSET) +
                     static_cast<float>(bulletPaseY * attackAnimation.getFrame());
            break;
        case SURESTE:
            direcX = posX + static_cast<float>(UNIT_OFFSET) +
                     static_cast<float>(bulletPaseX * attackAnimation.getFrame());
            direcY = posY + static_cast<float>(UNIT_OFFSET) +
                     static_cast<float>(bulletPaseY * attackAnimation.getFrame());
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
        if (((unitType > 3 && unitType < 6) ||
            (unitType > 7 && unitType < 11)) &&
            (currentAttackType == MISIL_ATTACK ||
            currentAttackType == CANION_P_ATTACK)) {
            calculateMisilPosition(direcX, direcY, animationId);
            misilIteration ++;
            if (misilIteration == MAX_ITERATION) {
                reachedDestination = true;
                misilIteration = 1;
                bulletPaseX = BULLET_MOVEMENT;
                bulletPaseY = BULLET_MOVEMENT;
            }
        } else {
            calculateBulletPosition(direcX, direcY, animationId);
            if (attackAnimation.isLastFrame()) {
                bulletPaseX = BULLET_MOVEMENT;
                bulletPaseY = BULLET_MOVEMENT;
            }
        }
        camera.renderInSightForUnit(attackAnimation.getTexture(),
                                    srcAttack, direcX, direcY);
    }
    Area srcLife(0, 0, LIFE_BAR_WIDTH, LIFE_BAR_HEIGHT);
    camera.renderInSightForUnit(currentLifeTexture, srcLife, posX, posY - 0.2);
    Area srcIdentifier(0, 0, IDENTIFIER_DIMENSION, IDENTIFIER_DIMENSION);
    camera.renderInSightForUnit(identifierTexture, srcIdentifier,
                                posX + 0.5, posY - 0.2);

    if (unitType == DEVASTATOR_ID && isDying) {
        Area src(0, 0, DEVASTATOR_DYING_DIMENSIONS, DEVASTATOR_DYING_DIMENSIONS);
        float posBorderX = static_cast<int>(posX);
        float posBorderY = static_cast<int>(posY);
        return camera.renderInSightForUnit(texture, src, posBorderX, posBorderY);    
    } else {
        Area src(0, 0, sizeW, sizeH);
        return camera.renderInSightForUnit(texture, src, posX, posY);
    }
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

int Unit::getAttackType() {
    return currentAttackType;
}

int Unit::getPlayerId() {
    return playerId;
}

void Unit::setPlayerId(int newPlayerId, SdlTexture* newIdentifier) {
    playerId = newPlayerId;
    identifierTexture = newIdentifier;
}

void Unit::setPropiety(bool newPropiety) {
    propiety = newPropiety;
}

void Unit::setExplosion() {
    // std::cout << "me setean una explosion\n";
    previosAnimationId = animationId;
    // std::cout << "id anterior " << previosAnimationId << std::endl;
    if (unitType < 7) {  // soy vehiculo
        animationId = VEHICLE_EXPLOSION_ANIMATION;
        animations.at(animationId).reset();
        getTexture();
    } else {
        animationId = SOLDIER_EXPLOSION_ANIMATION;
        animations.at(animationId).reset();
        getTexture();
    }
}

/*
Pre-Condiciones: Determina el animation id de la unidad.
Post-Condiciones: -
*/

void Unit::setAnimationId(int newAnimationId) {
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
        if (((unitType > 3 && unitType < 6) ||
            (unitType > 7 && unitType < 11)) &&
            (currentAttackType == MISIL_ATTACK ||
            currentAttackType == CANION_P_ATTACK) &&
            reachedDestination) {
            isCurrentlyAttacking = false;
            reachedDestination = false;
            if (attackedUnit != nullptr &&
                !(attackedUnit->getIsDying()) &&
                !(attackedUnit->getIsDead()) &&
                unitType != DEVASTATOR_ID) {
                attackedUnit->setExplosion();
                attackedUnit = nullptr;
            } else if (attackedConstruction != nullptr &&
                !(attackedConstruction->getAnimationId() ==
                CONSTRUCTION_DEAD_ANIMATION) &&
                !(attackedConstruction->getIsDead()) &&
                unitType != DEVASTATOR_ID) {
                attackedConstruction->setExplosion();
                attackedConstruction = nullptr;
            } else {
                if (attackedConstruction != nullptr) attackedConstruction = nullptr;
                if (attackedUnit != nullptr) attackedUnit = nullptr;
            }
        } else if (attackAnimation.isLastFrame() &&
                   currentAttackType != MISIL_ATTACK &&
                   currentAttackType != CANION_P_ATTACK) {
            isCurrentlyAttacking = false;
        } else {
            attackAnimation.update(delta);
        }
    }
    // quieto para vehiculo (no rotacion ni muerte)
    if (unitType < 7 && !(animationId >= 9 && animationId < 14)) return;
    // quieto para soldado
    if (unitType > 6 && animationId == STILL) return;
    animations.at(animationId).update(delta);
    getTexture();
    if ((unitType < 7 && animationId == VEHICLE_EXPLOSION_ANIMATION
        && animations.at(animationId).isLastFrame()) ||
        (unitType > 6 && animationId == SOLDIER_EXPLOSION_ANIMATION
        && animations.at(animationId).isLastFrame())) {
        animationId = previosAnimationId;
        getTexture();
        previosAnimationId = 0;
    }
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
Pre-Condiciones: Calcula la longitud de los saltos necesarios para llegar al
destino en 10 saltos.
Post-Condiciones: -
*/

void Unit::calculateSteps() {
    float xDifference = posX - destinationX;
    if (xDifference < 0) {
        xDifference = destinationX - posX;
    }
    float yDifference = posY - destinationY;
    if (yDifference < 0) {
        yDifference = destinationY - posY;
    }
    bulletPaseX = xDifference / float(10);
    bulletPaseY = yDifference / float(10);
}

/*
Pre-Condiciones: Setea la posicion de destino del misil cuando se ataca una
unidad.
Post-Condiciones: -
*/

void Unit::setMisilDestinationForUnit(float x, float y, Unit* attackedUnit) {
    destinationX = x;
    destinationY = y;
    calculateSteps();
    this->attackedUnit = attackedUnit;
}

/*
Pre-Condiciones: Setea la posicion de destino del misil cuando se ataca un
edificio.
Post-Condiciones: -
*/

void Unit::setMisilDestinationForConstruction(float x, float y,
                                        Construction* attackedConstruction) {
    destinationX = x;
    destinationY = y;
    calculateSteps();
    this->attackedConstruction = attackedConstruction;
}

/*
Pre-Condiciones: Calula el paso de una onda sonica para que mantega
el ratio entre x e y.
Post-Condiciones: -
*/

void Unit::setSoundWaveDestination(float x, float y) {
    if (animationId == NORTE || animationId == SUR || animationId == ESTE ||
        animationId == OESTE || animationId == STILL) return;
    float xDifference = posX - x;
    if (xDifference < 0) {
        xDifference = x - posX;
    }
    float yDifference = posY - y;
    if (yDifference < 0) {
        yDifference = y - posY;
    }
    float ratio = (xDifference) / (yDifference);
    if (ratio > 1) {
        bulletPaseY /= ratio;
    } else {
        bulletPaseX *= ratio;
    }
}

bool Unit::hasNoAttack() {
    return this->attackTextures.size() == 0;
}

void Unit::setAttackType(int attackType, std::vector<SdlTexture*> attack) {
    currentAttackType = attackType;
    attackAnimation.setTextures(attack);
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
  destinationX(0),
  destinationY(0),
  bulletPaseX(other.bulletPaseX),
  bulletPaseY(other.bulletPaseY),
  reachedDestination(other.reachedDestination),
  misilIteration(other.misilIteration),
  previosAnimationId(other.previosAnimationId),
  currentAttackType(other.currentAttackType),
  attackedUnit(other.attackedUnit),
  attackedConstruction(other.attackedConstruction),
  texture(other.texture),
  currentLifeTexture(other.currentLifeTexture) {
}

/*
Pre-Condiciones: Destructor de Unit.
Post-Condiciones: -
*/

Unit::~Unit() {
}
