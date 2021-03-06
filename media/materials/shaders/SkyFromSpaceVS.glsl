//
// Structure definitions
//

struct VS_OUTPUT {
    vec4 Position;
    vec4 RayleighColor;
    vec4 MieColor;
    vec3 Texcoord;
};

struct VS_INPUT {
    vec4 Position;
};


//
// Global variable definitions
//

uniform float fCameraHeightSqr;
uniform float fInnerRadius;
uniform float fKm4PI;
uniform float fKmESun;
uniform float fKr4PI;
uniform float fKrESun;
uniform float fOuterRadius;
uniform float fOuterRadiusSqr;
uniform float fScale;
uniform float fScaleOverScaleDepth;
uniform vec4 fvCameraPos;
uniform vec3 fvInvWavelengths;
uniform vec4 fvLightDir;
uniform mat4 matWorldViewProjection;

//
// Function declarations
//

VS_OUTPUT vs_main( in VS_INPUT Input );
float getNearIntersection( in vec3 v3Pos, in vec3 v3Ray, in float fDistance2, in float fRadius2 );
float scale( in float fCos );

//
// Function definitions
//

VS_OUTPUT vs_main( in VS_INPUT Input ) {
    vec3 fvPos;
    vec3 fvRay;
    float fFar;
    float fNear;
    vec3 fvStart;
    float fStartAngle;
    float fStartDepth;
    float fStartOffset;
    float fSampleLength;
    float fScaledLength;
    vec3 fvSampleRay;
    vec3 fvSamplePoint;
    vec3 fvFrontColor = vec3( 0.000000, 0.000000, 0.000000);
    int i = 0;
    float fHeight;
    float fSampleDepth;
    float fLightAngle;
    float fCameraAngle;
    float fScatter;
    vec3 fvAttenuate;
    VS_OUTPUT Output;

    fvPos = Input.Position.xyz ;
    fvRay = (fvPos - fvCameraPos.xyz );
    fvPos = normalize( fvPos );
    fFar = length( fvRay );
    fvRay /= fFar;
    fNear = getNearIntersection( vec3( fvCameraPos), fvRay, fCameraHeightSqr, fOuterRadiusSqr);
    fvStart = (vec3( fvCameraPos) + (fvRay * fNear));
    fFar -= fNear;
    fStartAngle = (dot( fvRay, fvStart) / fOuterRadius);
    fStartDepth = exp( -4.00000 );
    fStartOffset = (fStartDepth * scale( fStartAngle));
    fSampleLength = (fFar / 3.00000);
    fScaledLength = (fSampleLength * fScale);
    fvSampleRay = (fvRay * fSampleLength);
    fvSamplePoint = (fvStart + (fvSampleRay * 0.500000));
	
	vec4 lightDir = -fvLightDir;
	
    for ( ; (i < 3); ( i++ )) {
        fHeight = length( fvSamplePoint );
        fSampleDepth = exp( (fScaleOverScaleDepth * (fInnerRadius - fHeight)) );
        fLightAngle = (dot( lightDir.xyz , fvSamplePoint) / fHeight);
        fCameraAngle = (dot( fvRay, fvSamplePoint) / fHeight);
        fScatter = (fStartOffset + (fSampleDepth * (scale( fLightAngle) - scale( fCameraAngle))));
        fvAttenuate = exp( (( -fScatter ) * ((fvInvWavelengths * fKr4PI) + fKm4PI)) );
        fvFrontColor += (fvAttenuate * (fSampleDepth * fScaledLength));
        fvSamplePoint += fvSampleRay;
    }
    Output.Position = ( matWorldViewProjection * Input.Position );
    Output.RayleighColor = vec4( (fvFrontColor * (fvInvWavelengths * fKrESun)), 1.00000);
    Output.MieColor = vec4( (fvFrontColor * fKmESun), 1.00000);
    Output.Texcoord = (fvCameraPos.xyz  - fvPos);
    return Output;
}


float getNearIntersection( in vec3 v3Pos, in vec3 v3Ray, in float fDistance2, in float fRadius2 ) {
    float B;
    float C;
    float fDet;

    B = (2.00000 * dot( v3Pos, v3Ray));
    C = (fDistance2 - fRadius2);
    fDet = max( 0.000000, ((B * B) - (4.00000 * C)));
    return (0.500000 * (( -B ) - sqrt( fDet )));
}


float scale( in float fCos ) {
    float x;

    x = (1.00000 - fCos);
    return (0.250000 * exp( (-0.00287000 + (x * (0.459000 + (x * (3.83000 + (x * (-6.80000 + (x * 5.25000)))))))) ));
}


//
// Translator's entry point
//
void main() {
    VS_OUTPUT xlat_retVal;
    VS_INPUT xlat_temp_Input;
    xlat_temp_Input.Position = vec4( gl_Vertex);

    xlat_retVal = vs_main( xlat_temp_Input);

    gl_Position = vec4( xlat_retVal.Position);
    gl_TexCoord[0] = vec4( xlat_retVal.RayleighColor);
    gl_TexCoord[1] = vec4( xlat_retVal.MieColor);
    gl_TexCoord[2] = vec4( xlat_retVal.Texcoord, 0.0);
}


 