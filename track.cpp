#include "track.h"
#include "interpolation.h"

Track::Track(lines_t* lines, QString projection, Qwt3D::SurfacePlot& pw)
    : Qwt3D::ParametricSurface(pw), x(0), y(0), z(0){
    this->line = lines;
    setProjection(projection);
}

Qwt3D::Triple Track::operator() (double u, double v) {
    int counter = 0;
    line_t *point;
    foreach(line_t *i, *line) {
        if (counter == (int) round(u) || counter == line->size() - 1) {
            point = i;
            break;
        }
        counter++;
    }
    line_t::iterator point_x = point->find(x1);
    if (point_x != point->end()) {
        x = point_x->second;
    }

    line_t::iterator point_y = point->find(y1);
    if (point_y != point->end()) {
       y = point_y->second;
    }

    line_t::iterator point_z = point->find(z1);
    if (point_z != point->end()) {
       z = point_z->second;
    }

    return Qwt3D::Triple(x, y, z);
}


void Track::setProjection(QString projection) {
    std::string std_proj = projection.toStdString();
    x1 = std_proj.substr(0, 1);
    y1 = std_proj.substr(1, 1);
    z1 = std_proj.substr(2, 1);
}

std::string Track::getX1() {
    return x1;
}

std::string Track::getY1() {
    return y1;
}

std::string Track::getZ1() {
    return z1;
}
