#include <//./z/video/stdEnv.inc>

const vec4 gsQuadPos[4] = vec4[](vec4(-1, 1, 0, 1), vec4(-1,-1, 0, 1), vec4(1, 1, 0, 1), vec4(1,-1, 0, 1));
const vec2 gsQuadUvFlippedXy[4] = vec2[](vec2(1, 0), vec2(1, 1), vec2(0, 0), vec2(0, 1));
// flipped UV

out block
{
    vec2 uv0;
} sgl_v;

void main()
{
    // draw a full coverage quad based on two tristripped triangles (4 indices). AfxDraw(0, 1, 0, 4)
    gl_Position = gsQuadPos[gl_VertexID];
    sgl_v.uv0 = gsQuadUvFlippedXy[gl_VertexID];
}
