xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 26;
 0.00000;2.00008;-1.00000;,
 0.00000;1.00008;1.00000;,
 -0.70711;1.70719;-1.00000;,
 0.00000;1.00008;1.00000;,
 -1.00000;1.00008;-1.00000;,
 0.00000;1.00008;1.00000;,
 -0.70711;0.29297;-1.00000;,
 0.00000;1.00008;1.00000;,
 0.00000;0.00008;-1.00000;,
 0.00000;1.00008;1.00000;,
 0.70711;0.29297;-1.00000;,
 0.00000;1.00008;1.00000;,
 1.00000;1.00008;-1.00000;,
 0.00000;1.00008;1.00000;,
 0.70711;1.70719;-1.00000;,
 0.00000;1.00008;1.00000;,
 0.00000;2.00008;-1.00000;,
 0.00000;1.00008;-1.00000;,
 0.00000;2.00008;-1.00000;,
 -0.70711;1.70719;-1.00000;,
 -1.00000;1.00008;-1.00000;,
 -0.70711;0.29297;-1.00000;,
 0.00000;0.00008;-1.00000;,
 0.70711;0.29297;-1.00000;,
 1.00000;1.00008;-1.00000;,
 0.70711;1.70719;-1.00000;;
 
 16;
 3;2,1,0;,
 3;4,3,2;,
 3;6,5,4;,
 3;8,7,6;,
 3;10,9,8;,
 3;12,11,10;,
 3;14,13,12;,
 3;16,15,14;,
 3;19,18,17;,
 3;20,19,17;,
 3;21,20,17;,
 3;22,21,17;,
 3;23,22,17;,
 3;24,23,17;,
 3;25,24,17;,
 3;18,25,17;;
 
 MeshMaterialList {
  1;
  16;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.000000;0.756000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  14;
  0.000000;0.894427;0.447213;,
  -0.632457;0.632455;0.447213;,
  -0.894428;-0.000000;0.447213;,
  -0.632455;-0.632456;0.447214;,
  -0.000001;-0.894427;0.447213;,
  0.632455;-0.632456;0.447214;,
  0.894428;0.000000;0.447213;,
  0.632457;0.632455;0.447213;,
  0.000000;-0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-0.000000;-1.000000;,
  0.000001;-0.000001;-1.000000;,
  0.000000;-0.000001;-1.000000;,
  0.000000;-0.000001;-1.000000;;
  16;
  3;1,1,0;,
  3;2,1,1;,
  3;3,3,2;,
  3;4,3,3;,
  3;5,5,4;,
  3;6,5,5;,
  3;7,7,6;,
  3;0,7,7;,
  3;9,9,8;,
  3;9,9,8;,
  3;10,9,8;,
  3;11,10,8;,
  3;12,11,8;,
  3;13,12,8;,
  3;9,13,8;,
  3;9,9,8;;
 }
 MeshTextureCoords {
  26;
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
 MeshVertexColors {
  26;
  0;1.000000;1.000000;1.000000;1.000000;,
  1;1.000000;1.000000;1.000000;1.000000;,
  2;1.000000;1.000000;1.000000;1.000000;,
  3;1.000000;1.000000;1.000000;1.000000;,
  4;1.000000;1.000000;1.000000;1.000000;,
  5;1.000000;1.000000;1.000000;1.000000;,
  6;1.000000;1.000000;1.000000;1.000000;,
  7;1.000000;1.000000;1.000000;1.000000;,
  8;1.000000;1.000000;1.000000;1.000000;,
  9;1.000000;1.000000;1.000000;1.000000;,
  10;1.000000;1.000000;1.000000;1.000000;,
  11;1.000000;1.000000;1.000000;1.000000;,
  12;1.000000;1.000000;1.000000;1.000000;,
  13;1.000000;1.000000;1.000000;1.000000;,
  14;1.000000;1.000000;1.000000;1.000000;,
  15;1.000000;1.000000;1.000000;1.000000;,
  16;1.000000;1.000000;1.000000;1.000000;,
  17;1.000000;1.000000;1.000000;1.000000;,
  18;1.000000;1.000000;1.000000;1.000000;,
  19;1.000000;1.000000;1.000000;1.000000;,
  20;1.000000;1.000000;1.000000;1.000000;,
  21;1.000000;1.000000;1.000000;1.000000;,
  22;1.000000;1.000000;1.000000;1.000000;,
  23;1.000000;1.000000;1.000000;1.000000;,
  24;1.000000;1.000000;1.000000;1.000000;,
  25;1.000000;1.000000;1.000000;1.000000;;
 }
}