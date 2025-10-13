_Pragma("once");

typedef struct {
  float r,g,b;
} color_t;

typedef struct {
    float x1, y1;
    float x2, y2;
} line_t;

typedef struct {
    float x, y;
    float w, h;
} rect_t;

typedef struct {
    float x, y;
    float r;
} circle_t;

typedef struct {
    float x;
    float y;
} pos2_t;

typedef struct {
    float width;
    float height;
} screen_t;

typedef struct {
    long x;
    long y;
} coords_t;


typedef int key_t; // keyboard key