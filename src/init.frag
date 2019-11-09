#version 130


uniform int type;

in vec2 fTexCoord;

out vec4 outColor;

void main(void){    
  if(type == 0)
  {
    outColor = vec4((tan(fTexCoord.x*25) * sin(fTexCoord.y*3) + sin(fTexCoord.y*12)),0, 0 ,1 ); 
  }
  else
  {
	outColor = vec4(0,0, 0 ,1 );
  }
 }