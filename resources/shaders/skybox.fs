#version 330 core
out vec4 FragColor;

in vec3 texCoords;

uniform samplerCube skybox;

uniform float iTime;

void main()
{    


    //float angle = iTime * 0.001; // color version
    //vec2 normalizedCoord = texCoords.xy / vec2(900,600) * 2.0 - 1.0;
    //for(float i = 0.0; i < 128.0; i+=1.0)
    //{
    //    normalizedCoord = abs(normalizedCoord);
    //    normalizedCoord -= 0.3;
    //    normalizedCoord *= 1.08;
    //    normalizedCoord *= mat2( cos(angle),-sin(angle), sin(angle),cos(angle));
    //}
    //
	//FragColor = texture(skybox, texCoords) * vec4(length(normalizedCoord - vec2(-0.42,-0.51)),
	//	length(normalizedCoord + vec2(0.2,-0.3)),
	//	length(normalizedCoord + vec2(-0.4,-0.1)),1.0);
    //
    //
    //FragColor = texture(skybox, texCoords);

    vec2 uv = texCoords.xy/vec2(300,500);
    vec3 col = 0.5 + 0.5*cos(iTime+uv.xyx+vec3(0,2,4));
    FragColor = vec4(col,1.0) * texture(skybox, texCoords);
}
