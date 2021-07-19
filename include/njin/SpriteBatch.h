#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Vertex.h"
#include <vector>
#include <algorithm>

namespace njin{

  enum class GlyphSortType {
    NONE,
    FRONT_TO_BACK,
    BACK_TO_FRONT,
    TEXTURE //usually the most efficient
  };

  struct Glyph {
    GLuint texture;
    float depth;

    Vertex topLeft;
    Vertex bottomLeft;
    Vertex topRight;
    Vertex bottomRight;
  };

  struct RenderBatch {
    RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture):
      offset(Offset),
      numVertices(NumVertices),
      texture(Texture){};
    GLuint offset;
    GLuint numVertices;
    GLuint texture;
  };

  class SpriteBatch
  {
    private:
      GLuint vbo;
      GLuint vao;
      GlyphSortType gsType;
      std::vector<Glyph*> glyphs;
      std::vector<RenderBatch> renderBatches;

      void createRenderBatches();
      void createVertexArray();
      void sortGlyphs();

      static bool compareFTB(Glyph* a, Glyph* b);
      static bool compareBTF(Glyph* a, Glyph* b);
      static bool compareTEX(Glyph* a, Glyph* b);

    public:
      SpriteBatch();
      ~SpriteBatch();

      void init();
      void begin(GlyphSortType sortType = GlyphSortType::TEXTURE); //prep for drawing
      void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color); //adding sprites to the batch
      void end(); //sort images etc
      void renderBatch(); //blit the actual img
  };
}
