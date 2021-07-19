#include "SpriteBatch.h"

namespace njin {
  SpriteBatch::SpriteBatch():
    vbo(0),
    vao(0)
  {

  }

  SpriteBatch::~SpriteBatch(){

  }

  void SpriteBatch::init() {
    createVertexArray();

  }

  void SpriteBatch::begin(GlyphSortType sortType /* GlyphSortType::TEXTURE */) {
    sortType = gsType;
    renderBatches.clear();
    for (unsigned long int i = 0; i < glyphs.size(); ++i) {
      delete glyphs[i];
    }
    glyphs.clear(); //replaces memory allocs with 0s rather than ditching the whole thing
  }

  void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color) {
    //add a glyph to a vector of glyphs
    Glyph* newGlyph= new Glyph;
    newGlyph->texture = texture;
    newGlyph->depth = depth;

    newGlyph->topLeft.color = color;
    newGlyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
    newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

    newGlyph->bottomLeft.color = color;
    newGlyph->bottomLeft.setPosition(destRect.x, destRect.y);
    newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y);

    newGlyph->bottomRight.color = color;
    newGlyph->bottomRight.setPosition(destRect.x + destRect.z , destRect.y);
    newGlyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

    newGlyph->topRight.color = color;
    newGlyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
    newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

    glyphs.emplace_back(newGlyph);


  }

  void SpriteBatch::end() {
    sortGlyphs();
    createRenderBatches();
  }

  void SpriteBatch::renderBatch() {

    glBindVertexArray(vao);
    for (int i = 0; i < (int)renderBatches.size(); ++i) {
      glBindTexture(GL_TEXTURE_2D, renderBatches[i].texture);
      glDrawArrays(GL_TRIANGLES, renderBatches[i].offset, renderBatches[i].numVertices);
    }
    glBindVertexArray(0);

  }

  void SpriteBatch::createRenderBatches() {
    std::vector<Vertex> vertices;
    vertices.resize(glyphs.size()*6);

    if (glyphs.empty()) {
      return;
    }

    int offset = 0;
    int cv = 0; //current vertex
    //emplace the very first batch
    renderBatches.emplace_back(offset, 6, glyphs[0]->texture);
    vertices[cv++] = glyphs[0]->topLeft; //increase index after execution
    vertices[cv++] = glyphs[0]->bottomLeft; 
    vertices[cv++] = glyphs[0]->bottomRight; 
    vertices[cv++] = glyphs[0]->bottomRight; 
    vertices[cv++] = glyphs[0]->topRight; 
    vertices[cv++] = glyphs[0]->topLeft; 
    offset += 6;

    for (unsigned long int cg = 1; cg < glyphs.size(); ++cg) {
      if (glyphs[cg]->texture != glyphs[cg - 1]->texture) {
        renderBatches.emplace_back(offset, 6, glyphs[cg]->texture);
      } else {
        renderBatches.back().numVertices += 6;
      }
      vertices[cv++] = glyphs[cg]->topLeft;
      vertices[cv++] = glyphs[cg]->bottomLeft; 
      vertices[cv++] = glyphs[cg]->bottomRight; 
      vertices[cv++] = glyphs[cg]->bottomRight; 
      vertices[cv++] = glyphs[cg]->topRight; 
      vertices[cv++] = glyphs[cg]->topLeft; 
      offset +=6;
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //orphan the buffer
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
    //upload the data
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);

  }

  void SpriteBatch::createVertexArray() {
    if (vao == 0) {
      glGenVertexArrays(1, &vao);
    }
    glBindVertexArray(vao);
    if (vbo == 0) {
      glGenBuffers(1, &vbo);
    }
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    //this is the position attrib ptr, cast the position offset as a void ptr cos required
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    //now the color ptr
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    //and the uv ptr
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    glBindVertexArray(0); //will disable all vas

  }

  void SpriteBatch::sortGlyphs() {
    switch (gsType) {
      case GlyphSortType::BACK_TO_FRONT:
        std::stable_sort(glyphs.begin(), glyphs.end(), compareBTF);
        break;
      case GlyphSortType::FRONT_TO_BACK:
        std::stable_sort(glyphs.begin(), glyphs.end(), compareFTB);
        break;
      case GlyphSortType::TEXTURE:
        std::stable_sort(glyphs.begin(), glyphs.end(), compareTEX);
        break;
      default:
        break;

    }
  }

  bool SpriteBatch::compareBTF(Glyph* a, Glyph* b) {
    return (a->depth < b->depth);
  }
  bool SpriteBatch::compareFTB(Glyph* a, Glyph* b) {
    return (a->depth > b->depth);
  }
  bool SpriteBatch::compareTEX(Glyph* a, Glyph* b) {
    //sort by texture id since texture is an int referring to the id already
    return (a->texture < b->texture);
  }
}
