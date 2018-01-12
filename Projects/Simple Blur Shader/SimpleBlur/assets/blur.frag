#version 150

uniform sampler2D	tex0;
uniform vec2		sample_offset;
uniform float		attenuation;

in vec2 vTexCoord0;

out vec4 oColor;

void main()
{ 
	vec4 sum = vec4( 0.0, 0.0, 0.0, 0.0 );	
	float zero = 0.00001f;

	if( texture( tex0, vTexCoord0 + -10.0 * sample_offset ).a > zero ) sum += texture( tex0, vTexCoord0 + -10.0 * sample_offset ) * 0.009167927656011385;
	if( texture( tex0, vTexCoord0 +  -9.0 * sample_offset ).a > zero ) sum += texture( tex0, vTexCoord0 +  -9.0 * sample_offset ) * 0.014053461291849008;
	if( texture( tex0, vTexCoord0 +  -8.0 * sample_offset ).a > zero ) sum += texture( tex0, vTexCoord0 +  -8.0 * sample_offset ) * 0.020595286319257878;
	if( texture( tex0, vTexCoord0 +  -7.0 * sample_offset ).a > zero ) sum += texture( tex0, vTexCoord0 +  -7.0 * sample_offset ) * 0.028855245532226279;
	if( texture( tex0, vTexCoord0 +  -6.0 * sample_offset ).a > zero ) sum += texture( tex0, vTexCoord0 +  -6.0 * sample_offset ) * 0.038650411513543079;
	if( texture( tex0, vTexCoord0 +  -5.0 * sample_offset ).a > zero ) sum += texture( tex0, vTexCoord0 +  -5.0 * sample_offset ) * 0.049494378859311142;
	if( texture( tex0, vTexCoord0 +  -4.0 * sample_offset ).a > zero ) sum += texture( tex0, vTexCoord0 +  -4.0 * sample_offset ) * 0.060594058578763078;
	if( texture( tex0, vTexCoord0 +  -3.0 * sample_offset ).a > zero ) sum += texture( tex0, vTexCoord0 +  -3.0 * sample_offset ) * 0.070921288047096992;
	if( texture( tex0, vTexCoord0 +  -2.0 * sample_offset ).a > zero ) sum += texture( tex0, vTexCoord0 +  -2.0 * sample_offset ) * 0.079358891804948081;
	if( texture( tex0, vTexCoord0 +  -1.0 * sample_offset ).a > zero ) sum += texture( tex0, vTexCoord0 +  -1.0 * sample_offset ) * 0.084895951965930902;
	if( texture( tex0, vTexCoord0 +   0.0 * sample_offset ).a > zero ) sum += texture( tex0, vTexCoord0 +   0.0 * sample_offset ) * 0.086826196862124602;
	if( texture( tex0, vTexCoord0 +  +1.0 * sample_offset ).a > zero ) sum += texture( tex0, vTexCoord0 +  +1.0 * sample_offset ) * 0.084895951965930902;
	if( texture( tex0, vTexCoord0 +  +2.0 * sample_offset ).a > zero ) sum += texture( tex0, vTexCoord0 +  +2.0 * sample_offset ) * 0.079358891804948081;
	if( texture( tex0, vTexCoord0 +  +3.0 * sample_offset ).a > zero ) sum += texture( tex0, vTexCoord0 +  +3.0 * sample_offset ) * 0.070921288047096992;
	if( texture( tex0, vTexCoord0 +  +4.0 * sample_offset ).a > zero ) sum += texture( tex0, vTexCoord0 +  +4.0 * sample_offset ) * 0.060594058578763078;
	if( texture( tex0, vTexCoord0 +  +5.0 * sample_offset ).a > zero ) sum += texture( tex0, vTexCoord0 +  +5.0 * sample_offset ) * 0.049494378859311142;
	if( texture( tex0, vTexCoord0 +  +6.0 * sample_offset ).a > zero ) sum += texture( tex0, vTexCoord0 +  +6.0 * sample_offset ) * 0.038650411513543079;
	if( texture( tex0, vTexCoord0 +  +7.0 * sample_offset ).a > zero ) sum += texture( tex0, vTexCoord0 +  +7.0 * sample_offset ) * 0.028855245532226279;
	if( texture( tex0, vTexCoord0 +  +8.0 * sample_offset ).a > zero ) sum += texture( tex0, vTexCoord0 +  +8.0 * sample_offset ) * 0.020595286319257878;
	if( texture( tex0, vTexCoord0 +  +9.0 * sample_offset ).a > zero ) sum += texture( tex0, vTexCoord0 +  +9.0 * sample_offset ) * 0.014053461291849008;
	if( texture( tex0, vTexCoord0 + +10.0 * sample_offset ).a > zero ) sum += texture( tex0, vTexCoord0 + +10.0 * sample_offset ) * 0.009167927656011385;

	oColor = attenuation * sum;
	//oColor.a = 1.0;
}