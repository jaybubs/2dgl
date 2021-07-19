#version 140

in vec2 fragPosition;
in vec4 fragColor;
in vec2 fragUV;

out vec4 color;

//textures are always uniform
uniform sampler2D mySampler;

void main() {

  //textures use uv - fractional normalised repeatable coordinates
  vec4 textureColor = texture(mySampler, fragUV);

  color = fragColor * textureColor;
}
