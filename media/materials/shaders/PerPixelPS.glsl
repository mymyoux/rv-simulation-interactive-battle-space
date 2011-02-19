
//
// Global variable definitions
//

uniform vec4 ambient;
uniform sampler2D baseMap;
uniform vec4 diffuse;
uniform vec3 light_direction;
uniform vec4 specular;
uniform vec3 view_direction;

//
// Function declarations
//

vec4 xlat_main( in vec4 Diff, in vec3 Normal, in vec2 Texcoord );

//
// Function definitions
//

vec4 xlat_main( in vec4 Diff, in vec3 Normal, in vec2 Texcoord ) {
    float Ks = 0.280000;
    float Kd = 1.00000;
    float Ka = 1.00000;
    float n_specular = 6.00000;
    vec3 vReflect;
    vec4 AmbientColor;
    vec4 DiffuseColor;
    vec4 SpecularColor;
    vec4 texColor;
    vec4 FinalColor;

    vReflect = normalize( (((2.00000 * Normal) * dot( Normal, light_direction)) - light_direction) );
    AmbientColor = (ambient * Ka);
    DiffuseColor = ((diffuse * Kd) * max( 0.000000, dot( Normal, light_direction)));
    SpecularColor = ((specular * Ks) * pow( max( 0.000000, dot( vReflect, view_direction)), n_specular));
    texColor = texture2D( baseMap, Texcoord);
    FinalColor = (((AmbientColor + DiffuseColor) * texColor) + SpecularColor);
    return FinalColor;
}


//
// Translator's entry point
//
void main() {
    vec4 xlat_retVal;

    xlat_retVal = xlat_main( vec4(gl_Color), vec3(gl_TexCoord[0]), vec2(gl_TexCoord[4]));

    gl_FragData[0] = vec4( xlat_retVal);
}


 