#version 130

uniform sampler2D inputMap;
uniform ivec2 Coord;
uniform int button;

out vec4 outColor;

in vec2 fTexCoord;

void main(void){     
    ivec2 pos = ivec2(gl_FragCoord[0],gl_FragCoord[1]);
    vec4 data = texelFetch(inputMap, pos, 0);		
	ivec2 MCoord = ivec2(Coord.x, Coord.y);	
	
	if(pos == MCoord && button == 0)
	{	 
	   data[0] = 1;
	   data[1] = 1;
	   data[2] = 1;
	   data[3] = 1;
	}
	if(pos == MCoord && button == 2)
	{	 
	   data[0] = 0;
	   data[1] = 0;
	   data[2] = 0;
	   data[3] = 0;
	}
	else

	outColor = data;
}

