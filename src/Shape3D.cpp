#include "../include/Shape3D.h"


Shape3D::Shape3D()
{
}

Shape3D::Shape3D(int platonicSolidID)
{
    double SCALE = 50;
    const double PHI   = 1.61803398874989484820;
    if (platonicSolidID == 0) // Cube
    {
        vertices = {{ SCALE, SCALE, SCALE}, { SCALE, SCALE, -SCALE}, { SCALE, -SCALE, SCALE}, { SCALE, -SCALE, -SCALE},
                    {-SCALE, SCALE, SCALE}, {-SCALE, SCALE, -SCALE}, {-SCALE, -SCALE, SCALE}, {-SCALE, -SCALE, -SCALE}};
        edges    = {{0, 1}, {0, 2}, {0, 4}, {1, 3}, {1, 5}, {2, 3},
                    {2, 6}, {3, 7}, {4, 5}, {4, 6}, {5, 7}, {6, 7}};
        position = {0, 0, 100};
        for (auto& vertex : vertices)
            {
                vertex.x += position.x;
                vertex.y += position.y;
                vertex.z += position.z;
            }
    }
    else if (platonicSolidID == 1) // Tetrahedron
    {
        vertices = {{SCALE, SCALE, SCALE}, {-SCALE, -SCALE, SCALE}, {-SCALE, SCALE, -SCALE}, {SCALE, -SCALE, -SCALE}};
        edges    = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}};
        position = {200, 200, 100};
        for (auto& vertex : vertices)
            {
                vertex.x += position.x;
                vertex.y += position.y;
                vertex.z += position.z;
            }
    }
    else if (platonicSolidID == 2) // Octahedron
    {
        SCALE *= 1.25;    
        vertices = {{SCALE, 0, 0},  {-SCALE, 0, 0}, {0, SCALE, 0},
                    {0, -SCALE, 0}, {0, 0, SCALE},  {0, 0, -SCALE}};
        edges    = {{0, 2}, {0, 3}, {0, 4}, {0, 5}, {1, 2}, {1, 3},
                    {1, 4}, {1, 5}, {2, 4}, {2, 5}, {3, 4}, {3, 5}};
        position = {200, -200, 100};
        for (auto& vertex : vertices)
            {
                vertex.x += position.x;
                vertex.y += position.y;
                vertex.z += position.z;
            }
    }
    else if (platonicSolidID == 3) // Dodecahedron
    {
        SCALE *= .75;    
        vertices = {{SCALE, SCALE, SCALE},     {SCALE, SCALE, -SCALE},     {SCALE, -SCALE, SCALE},      {SCALE, -SCALE, -SCALE},
                    {-SCALE, SCALE, SCALE},    {-SCALE, SCALE, -SCALE},    {-SCALE, -SCALE, SCALE},     {-SCALE, -SCALE, -SCALE},
                    {0, SCALE/PHI, SCALE*PHI}, {0, SCALE/PHI, -SCALE*PHI}, {0, -SCALE /PHI, SCALE*PHI}, {0, -SCALE/PHI, -SCALE*PHI},
                    {SCALE/PHI, SCALE*PHI, 0}, {SCALE/PHI, -SCALE*PHI, 0}, {-SCALE/PHI, SCALE*PHI, 0},  {-SCALE/PHI, -SCALE*PHI, 0},
                    {SCALE*PHI, 0, SCALE/PHI}, {SCALE*PHI, 0, -SCALE/PHI}, {-SCALE*PHI, 0, SCALE/PHI},  {-SCALE*PHI, 0, -SCALE/PHI}};
        edges    = {{ 0,  8}, { 0, 12}, { 0, 16}, { 1,  9}, { 1, 12}, { 1, 17},
                    { 2, 10}, { 2, 13}, { 2, 16}, { 3, 11}, { 3, 13}, { 3, 17},
                    { 4,  8}, { 4, 14}, { 4, 18}, { 5,  9}, { 5, 14}, { 5, 19},
                    { 6, 10}, { 6, 15}, { 6, 18}, { 7, 11}, { 7, 15}, { 7, 19},
                    { 8, 10}, { 9, 11}, {12, 14}, {13, 15}, {16, 17}, {18, 19}};
        position = {-200, 200, 100};
        for (auto& vertex : vertices)
            {
                vertex.x += position.x;
                vertex.y += position.y;
                vertex.z += position.z;
            }
    }
    else if (platonicSolidID == 4) // Icosahedron
    {
        SCALE *= .75;    
        vertices = {{0, SCALE, SCALE*PHI}, {0, SCALE, -SCALE*PHI}, {0, -SCALE, SCALE*PHI}, {0, -SCALE, -SCALE*PHI},
                    {SCALE, SCALE*PHI, 0}, {SCALE, -SCALE*PHI, 0}, {-SCALE, SCALE*PHI, 0}, {-SCALE, -SCALE*PHI, 0},
                    {SCALE*PHI, 0, SCALE}, {SCALE*PHI, 0, -SCALE}, {-SCALE*PHI, 0, SCALE}, {-SCALE*PHI, 0, -SCALE}};
        edges    = {{ 0,  2}, { 0,  4}, { 0,  6}, { 0,  8}, { 0, 10}, { 1,  3},
                    { 1,  4}, { 1,  6}, { 1,  9}, { 1, 11}, { 2,  5}, { 2,  7},
                    { 2,  8}, { 2, 10}, { 3,  5}, { 3,  7}, { 3,  9}, { 3, 11},
                    { 4,  6}, { 4,  8}, { 4,  9}, { 5,  7}, { 5,  8}, { 5,  9},
                    { 6, 10}, { 6, 11}, { 7, 10}, { 7, 11}, { 8,  9}, {10, 11}};
        position = {-200, -200, 100};
        for (auto& vertex : vertices)
            {
                vertex.x += position.x;
                vertex.y += position.y;
                vertex.z += position.z;
            }
    }
}

Shape3D::~Shape3D()
{
}