#include <raylib.h>

#include <vector>
#include <ostream>

using std::vector;
 

/**
 * === Geometry ===
 */


// Triangle object
// * stores indices of the vertices and a couple other variables
struct Tri {
    int a, b, c;

    int group = 0;

    Tri(int _a, int _b, int _c, int _group)
        : a(_a), b(_b), c(_c), group(_group) {}

    int &operator[](int i) {
        if (i == 0) return a;
        if (i == 1) return b;
        return c;
    }
};

// Vertex object
// * Extends Vector2 and adds a vector of integers - indices of parent triangles
struct Vert : Vector2 {
    std::vector<int> tris;

    Vert(float _x, float _y) : Vector2{_x, _y} {}
    void operator=(Vector2 v) {
        x = v.x;
        y = v.y;
    }
};

// Create a vertex from two floats and insert it into the vector
void createVert(vector<Vert> &verts, float x, float y);

// Create a vertex from a vector and insert it into the vector
void createVert(vector<Vert> &verts, Vector2 v);

// Erase a vertex and its parent triangles from the vectors by index
void eraseVert(vector<Vert> &verts, vector<Tri> &tris, int vert);

// Check if given triangle contains a given index
bool triHasVert(Tri tri, int vert);

// Get the area of a triangle with a vector of verts and a trignale object
float getTriAreaFromVerts(const vector<Vert> &verts, const Tri &tri);

// Get the degeneracy value of a triangle with a vector of verts and a trignale object 
float triDegeneracyWithVerts(const vector<Vert> &verts, const Tri &tri);

// Erase a triangle with a given index from the triangle vector
void eraseTri(vector<Vert> &verts, vector<Tri> &tris, int i);

// Create a new triangle and insert it into a vector. Also assign the new 
// triangle as a parent of the triangles vertices
void insertNewTri(vector<Vert> &verts, vector<Tri> &tris, int a, int b, int c, int group = 0);

// Check if a given point lies inside a circumcircle of a triangle given the corners
bool pointInCircumcircle(Vector2 pt, Vector2 p1, Vector2 p2, Vector2 p3);

// Check if a point lies inside a triangle (a wrapper function for a raylib's implementation)
bool PointInTriangle(Vector2 pt, Vector2 v1, Vector2 v2, Vector2 v3);

// Get the area of a triangle given it's corners
float getTriArea(Vector2 a, Vector2 b, Vector2 c);

// Get the degeneracy value of a triangle given it's corners
float getTriDegeneracy(Vector2 a, Vector2 b, Vector2 c);

// Check if a given trio of vertices is in a clockwise order 
bool isClockwise(Vector2 a, Vector2 b, Vector2 c);

/**
 * === Utils ===
 */


// Draw a filled in triangle with a padding applied to the given points
void DrawTriangleFillPadded(Vector2 p1, Vector2 p2, Vector2 p3, int padding,
                            Color color);

// Draw an outline of a triangle with a padding applied to the given points
void DrawTriangleLinesPadded(Vector2 p1, Vector2 p2, Vector2 p3, int padding,
                             Color color);

// Draw an outline of a triangle with a padding and a stroke
void DrawTriangleLinesPadded(Vector2 p1, Vector2 p2, Vector2 p3, int padding,
                             int weight, Color color);

// Draw a triangle out of a texture
void DrawTriangleFromTexture(const Texture2D &texture, Vector2 *pos,
                             Vector2 *texcoords);

// Draw a padded triangle out of a texture
void DrawTriangleFromTexturePadded(const Texture2D &texture, Vector2 *pos,
                                   Vector2 *texcoords, int padding);

// Applie a padding to the given corners in-place
void paddTriangleInPlace(Vector2 &p1, Vector2 &p2, Vector2 &p3, int padding);

bool operator==(const Color &a, const Color &b);
std::ostream &operator<<(std::ostream &os, const Color &c);

// Vector operators
Vector2 operator-(const Vector2 &a, const Vector2 &b);
Vector2 operator-(const Vector2 &a);
Vector2 operator+(const Vector2 &a, const Vector2 &b);
float operator&(const Vector2 &a, const Vector2 &b);
float operator*(const Vector2 &a, const Vector2 &b);
Vector2 operator*(const Vector2 &a, const float &b);
Vector2 operator/(const Vector2 &a, const float &b);
Vector2 operator/(const Vector2 &a, const Vector2 &b);
std::ostream &operator<<(std::ostream &os, const Vector2 &v);

// Linear interpolation of two vectors
Vector2 lerp(const Vector2 &a, const Vector2 &b, const float &t);

// Get a squared magnitude of a Vector2 
float magSq(const Vector2 &vec);

// Get a magnitude of a Vector2 (uses sqrt(), be wary)
float mag(const Vector2 &vec);

// Normalize Vector2 in-place and return a reference
Vector2 normalize(Vector2 &vec);

// Get a normalized version of a Vector2
Vector2 normalized(const Vector2 &vec);

// Random float functions
float randf();
float randf(float max);
float randf(float min, float max);

// push unique
template <typename T>
void pushUnique(vector<T> &vec, T &elt) {
    bool isin = false;

    for (T thing : vec) {
        if (thing == elt) {
            isin = true;
            break;
        }
    }

    if (!isin) vec.push_back(elt);
}


/**
 * === World ===
 */

class World {
   public:
    int w, h, s, p;

    char pressed_key = '_';


    vector<Vert> verts;
    vector<Tri> tris;

    Vector2 mouse;
    Vector2 cursor;

    int vert_grid[9][9];

    int turn = 0;

   public:
    World(){};
    void create(int width, int height, int size);

    void update(int frameCount, Vector2 _mouse);
    void update(int frameCount);
    
    void mouseClicked(int mouse_button);
    void keyGotPressed(char key);

    int getTriangleWithPoint(const Vector2 & p);
    Vector2 getCursorTarget();

    void moveMade();
    void triangulate(int i);
};


/**
 * === Application ===
 */


class Application {
   public:
    // Technical definitions
    int width, height;
    int frameCount = 0;
    Application(){};
    bool setup(int _width, int _height);
    void setup();
    void start();
    void close();

    void update();
    void draw();

   public:
    // Cool definitions
    World wld;
};
