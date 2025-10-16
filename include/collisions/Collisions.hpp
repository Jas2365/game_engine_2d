_Pragma("once");

#include <Types.hpp>
#include <cmath>

// rect rect
inline bool collide_rect_rect(const rect_t& a, const rect_t& b){
    return !(a.x + a.w < b.x || b.x + b.w < a.x || 
             a.y + a.h < b.y || b.y + b.h < a.y );
}

// circle circle
inline bool collide_circle_circle(const circle_t& a, const circle_t& b){
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float dr = a.r - b.r;

    return (dx * dx + dy * dy) <= (dr * dr);
}

// circle rect
inline bool collide_circle_rect(const circle_t& c, const rect_t& r){
    // clamp circle center to rectangel bounds
    float closest_x = std::fmax(r.x, std::fmin(c.x, r.x + r.w));
    float closest_y = std::fmax(r.y, std::fmin(c.y, r.y + r.h));

    float dx = c.x - closest_x;
    float dy = c.y - closest_y;

    return (dx * dx + dy * dy) <= (c.r * c.r);
}
