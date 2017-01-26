uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture1z;
uniform sampler2D texture2z;
uniform sampler2D texture3z;
uniform sampler2D blendtexture;
uniform float scale;

vec3 blend(vec4 tex1, vec4 tex1z, vec4 tex2, vec4 tex2z, vec4 tex3, vec4 tex3z)
{
	float depth = 0.2;
	float ma = max(max(tex1z.r + tex1.a, tex2z.r + tex2.a),tex3z.r + tex3.a) - depth;

	float b1 = max(tex1z.r + tex1.a - ma, 0);
	float b2 = max(tex2z.r + tex2.a - ma, 0);
	float b3 = max(tex3z.r + tex3.a - ma, 0);
	
	return (tex1.rgb * b1 + tex2.rgb * b2 + tex3.rgb * b3) / (b1 + b2 + b3);
	//tex1z.r > tex2z.r ? tex1.rgb : tex2.rgb;//tex1 * tex1.a + tex2 * tex2.a;//a1 > a2 ? tex1.rgb : tex2.rgb;
}

void main()
{
    // lookup the pixel in the texture
    vec3 pixel1 = texture2D(texture1, gl_TexCoord[0].xy / 0.2 ).rgb;
	vec3 pixel2 = texture2D(texture2, gl_TexCoord[0].xy / 0.2 ).rgb;
	vec3 pixel3 = texture2D(texture3, gl_TexCoord[0].xy / 0.2 ).rgb;//texture2D(texture3, gl_TexCoord[0].xy / scale).rgb;
	
	vec4 pixel1z = texture2D(texture1z, gl_TexCoord[0].xy / 0.2 );
	vec4 pixel2z = texture2D(texture2z, gl_TexCoord[0].xy / 0.2 );
	vec4 pixel3z = texture2D(texture3z, gl_TexCoord[0].xy / 0.2 );//texture2D(texture3z, gl_TexCoord[0].xy / scale);
	
	vec4 bl = texture2D(blendtexture, gl_TexCoord[0].xy);
	
	

    // multiply it by the color
    gl_FragColor = gl_Color * vec4(blend(vec4(pixel1, bl.r), pixel1z, vec4(pixel2, bl.b), pixel2z, vec4(pixel3, bl.g), pixel3z), 1.0);
}