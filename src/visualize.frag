#version 130

uniform sampler2D inputMap;

out vec4 outColor;

in vec2 fTexCoord;
uniform int zoom;
uniform int left;
uniform int top;

void main(void){     
    ivec2 pos = ivec2(gl_FragCoord[0]/zoom + left,gl_FragCoord[1]/zoom + top);	
	//ivec2 pos = ivec2((gl_FragCoord[0] + left)/zoom,(gl_FragCoord[1] + top)/zoom);	

	vec4 data = vec4(0.3, 0.3, 0.3, 1);		
	if(pos[0] < 600 && pos[1]<600 && pos[0]>=0 && pos[1]>=0)
	{
      data = texelFetch(inputMap, pos, 0);		
	}	

	outColor = data;
}

