#include "jenia.h"
#include "qwt3d_types.h"
#include "track.h"

Jenia::Jenia() : Qwt3D::SurfacePlot() {
    for (unsigned i=0; i!=coordinates()->axes.size(); ++i)
    {
      coordinates()->axes[i].setMajors(7);
      coordinates()->axes[i].setMinors(4);
    }

    coordinates()->axes[Qwt3D::X1].setLabelString("x");
    coordinates()->axes[Qwt3D::Y1].setLabelString("y");
    coordinates()->axes[Qwt3D::Z1].setLabelString("z");

    setCoordinateStyle(Qwt3D::BOX);

    setPlotStyle(Qwt3D::WIREFRAME);
    Qwt3D::RGBA color(1, 0, 0, 1);
    setMeshColor(color);

    setRotation(30,0,15);
    setScale(1,1,1);
    setShift(0.15,0,0);
    setZoom(0.9);

    resize(800, 600);
}

void Jenia::updateLine() {
    updateData();
    updateGL();
}


void Jenia::updateProjection(std::string x1, std::string y1, std::string z1) {
    coordinates()->axes[Qwt3D::X1].setLabelString(QString(x1.at(0)));
    coordinates()->axes[Qwt3D::Y1].setLabelString(QString(y1.at(0)));
    coordinates()->axes[Qwt3D::Z1].setLabelString(QString(z1.at(0)));
}
