#version 130

uniform sampler2D inputMap;

out vec4 outColor;

in vec2 fTexCoord;

void main(void){
   // Is current cell alive?
	vec4 data = texelFetch(inputMap, ivec2(gl_FragCoord), 0);	
	float IsAlive = data[0];

   // Count Neighbours
   
    float NumberOfNeighbours = round(texelFetch(inputMap, ivec2(gl_FragCoord) + ivec2(-1,  0), 0).x) +
                               round(texelFetch(inputMap, ivec2(gl_FragCoord) + ivec2( 1,  0), 0).x) +
                               round(texelFetch(inputMap, ivec2(gl_FragCoord) + ivec2( 0, -1), 0).x) +
                               round(texelFetch(inputMap, ivec2(gl_FragCoord) + ivec2( 0,  1), 0).x) +
					       	   round(texelFetch(inputMap, ivec2(gl_FragCoord) + ivec2(-1,  1), 0).x) +
                               round(texelFetch(inputMap, ivec2(gl_FragCoord) + ivec2( 1,  1), 0).x) +
                               round(texelFetch(inputMap, ivec2(gl_FragCoord) + ivec2( 1, -1), 0).x) +
                               round(texelFetch(inputMap, ivec2(gl_FragCoord) + ivec2(-1, -1), 0).x);

/*							   
    float NumberOfNeighbours = floor(texelFetch(inputMap, ivec2(gl_FragCoord) + ivec2(-1,  0), 0).x) +
                               floor(texelFetch(inputMap, ivec2(gl_FragCoord) + ivec2( 1,  0), 0).x) +
                               floor(texelFetch(inputMap, ivec2(gl_FragCoord) + ivec2( 0, -1), 0).x) +
                               floor(texelFetch(inputMap, ivec2(gl_FragCoord) + ivec2( 0,  1), 0).x);
							   */
if(IsAlive > 0.1)
{
  //Any live cell with fewer than two live neighbours dies, as if caused by under-population.
  if(NumberOfNeighbours<1.5)
  {
     data[0] = 0;
     data[1] = 0.7;
     data[2] = 0.2;
  }
  else
  //Any live cell with two or three live neighbours lives on to the next generation.
  if(NumberOfNeighbours>1.9 && NumberOfNeighbours<3.1)
  {
     data[0] = 1;
     data[1] = 0.3;
     data[2] = 0.3;
  }
  else
  //Any live cell with more than three live neighbours dies, as if by overcrowding.
  if(NumberOfNeighbours>3.1)
  {
     data[0] = 0;
     data[1] = 0;
     data[2] = 1;
  }
}
else
{
  //Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction. 
  if(NumberOfNeighbours<3.1 && NumberOfNeighbours > 2.9)
  {
     data[0] = 1;
     data[1] = 1;
     data[2] = 1;
  }
  else
  {
    data = data * 0.95;
  }
}   
	outColor = vec4(data[0], data[1], data[2], data[3]);
} 