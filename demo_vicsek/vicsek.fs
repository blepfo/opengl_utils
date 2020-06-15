#version 330 core

out vec4 FragColor;

uniform vec2 iResolution;
uniform float iTime;

#define PI (3.14)
#define ITERATIONS (5)

float cubeSdf(vec2 p, vec2 halves) {
    vec2 edgeDist = abs(p) - halves;
    return length(max(edgeDist, 0.)) 
        + min(max(edgeDist.x, edgeDist.y), 0.);
}

vec2 fold(vec2 uv, float theta) {
	vec2 normal = vec2(sin(-theta), cos(-theta));
    // proj(uv, n) = dot(uv, n) / dot(n, n)
    // n has norm 1
    float d = dot(uv, normal);
    return uv - (2. * max(d, 0.) * normal);
}

vec2 vicsekSnowflake(vec2 uv, float time) {
    // Period 0 -- fold angle from (PI / 4) -> (PI / 6)
    // angle denominator increment ranges 0->2 from 0->1
    // Period 1 -- Translate 1 from 0.5 to 1.5
    time = mod(time, 4.);
    float denominatorIncrement = 
        // Transition from 0 to 1
        ((1. - step(1., time)) * fract(time) * 2.)
        // After 1 stay at 2, but stay back down after 3
        + ((step(1., time) * 2.) * (1. - step(3., time)))
        // After 2 decrease from 2 back to 0
        - ((step(2., time) * fract(time) * 2.) * (1. - step(3., time)));
    	
    
    float translateIncrement = 
        // Transition from 1 to 2
        ((1. - step(2., time)) * step(1., time) * fract(time))
    	// After 2 stay at 1
        + step(2., time)
    	// After 3 decrease to 0
    	- (step(3., time) * fract(time));
    
    
    for (int i = 0; i < ITERATIONS; i++) {
        uv *= 3.;
        uv = abs(uv);
    	uv = fold(uv, PI / (4. + denominatorIncrement));
    	uv.x -= 0.5 + translateIncrement;
    	uv.x = abs(uv.x);
    	uv.x -= 0.5;
    }
    return uv;
}

void main() {
    vec2 uv = gl_FragCoord.xy/iResolution.xy;
    uv -= 0.5;
    uv.x *= iResolution.x/iResolution.y;
	
    uv = vicsekSnowflake(uv, iTime* 0.8);
    
    float s = cubeSdf(uv, vec2(0.5));
    float pixelSize = (1. * pow(3., float(ITERATIONS))) / iResolution.x;
    float c = smoothstep(-pixelSize, pixelSize, s);
    
    vec3 color = vec3(uv.x, uv.y, 0.);
    color = vec3(0.105,0.154,0.300);
    color = mix(color, vec3(0.81,0.93,1.), 1.-c);

    FragColor = vec4(color,1.0);
}
