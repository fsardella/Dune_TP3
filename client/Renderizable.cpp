#include "Renderizable.h"

Renderizable::Renderizable(SdlTexture& texture,
                           int sizeW,
                           int sizeH,
                           float posX,
                           float posY)
: texture(texture),
  sizeW(sizeW),
  sizeH(sizeH),
  posX(posX),
  posY(posY) {
}

Renderizable::~Renderizable() {
}

Renderizable::Renderizable(Renderizable &&other)
: texture(other.texture),
  sizeW(other.sizeW),
  sizeH(other.sizeH),
  posX(other.posX),
  posY(other.posY) {
}
