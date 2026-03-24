struct VertexInput {
    @location(0) vertexPosition: vec3<f32>,
    @location(1) vertexTexCoord: vec2<f32>,
    @location(2) vertexColor: vec4<f32>,
};

struct VertexOutput {
    @builtin(position) position: vec4<f32>,
    @location(0) fragTexCoord: vec2<f32>,
    @location(1) fragColor: vec4<f32>,
};

struct Uniforms {
    mvp: mat4x4<f32>,
    tilePos: vec3<f32>,
    tileDim: vec2<f32>,
    screenCenter: vec2<f32>,
    colDiffuse: vec4<f32>,
};

@group(0) @binding(0) var<uniform> uniforms: Uniforms;

@group(0) @binding(1) var texture0: texture_2d<f32>;
@group(0) @binding(2) var sampler0: sampler;

@vertex
fn vs_main(input: VertexInput) -> VertexOutput {
    var output: VertexOutput;

    output.fragTexCoord = input.vertexTexCoord;
    output.fragColor = input.vertexColor;

    let isoX = (uniforms.tilePos.x - uniforms.tilePos.y) * (uniforms.tileDim.x / 2.0);
    let isoY = (uniforms.tilePos.x + uniforms.tilePos.y) * (uniforms.tileDim.y / 4.0)
               - uniforms.tilePos.z * (uniforms.tileDim.y / 2.0);

    let screenX = isoX + uniforms.screenCenter.x;
    let screenY = isoY + uniforms.screenCenter.y;

    var transformedPos = input.vertexPosition;
    transformedPos.x += screenX;
    transformedPos.y += screenY;

    var position = uniforms.mvp * vec4<f32>(transformedPos, 1.0);

    let depth = 1.0 - (uniforms.tilePos.x + uniforms.tilePos.y + uniforms.tilePos.z) / 1000.0;
    position.z = depth;

    output.position = position;
    return output;
}

@fragment
fn fs_main(input: VertexOutput) -> @location(0) vec4<f32> {
    let texelColor = textureSample(texture0, sampler0, input.fragTexCoord);

    var finalColor = texelColor * uniforms.colDiffuse * input.fragColor;

    if (finalColor.a < 0.1) {
        discard;
    }

    return finalColor;
}