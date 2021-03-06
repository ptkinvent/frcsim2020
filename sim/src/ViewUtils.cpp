/**
 * Copyright (c) 2020 Team 3260
 */

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osg/Point>
#include "ViewUtils.h"


osg::ref_ptr<osg::Geometry> ViewUtils::drawArrow(const osg::Vec3d& center, float theta, float tailLength, const osg::Vec4& color)
{
    float headFrontDist = 0.1/4;
    float headSidesDist = 0.1/4;
    float tailSideDist = 0.05/4;

    osg::Matrix A = osg::Matrix::rotate(theta, osg::Z_AXIS);

    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    if (tailLength > 0)
    {
        vertices->push_back(center + osg::Vec3(headFrontDist, 0, 0) * A);
        vertices->push_back(center + osg::Vec3(0, headSidesDist, 0) * A);
        vertices->push_back(center + osg::Vec3(0, tailSideDist, 0) * A);
        vertices->push_back(center + osg::Vec3(-tailLength, tailSideDist, 0) * A);
        vertices->push_back(center + osg::Vec3(-tailLength, -tailSideDist, 0) * A);
        vertices->push_back(center + osg::Vec3(0, -tailSideDist, 0) * A);
        vertices->push_back(center + osg::Vec3(0, -headSidesDist, 0) * A);
    }
    else
    {
        vertices->push_back(center + osg::Vec3(headFrontDist/4, -headSidesDist, 0) * A);
        vertices->push_back(center + osg::Vec3(headFrontDist/4, headSidesDist, 0) * A);
        vertices->push_back(center + osg::Vec3(-headFrontDist/4, headSidesDist, 0) * A);
        vertices->push_back(center + osg::Vec3(-headFrontDist/4, -headSidesDist, 0) * A);
    }
    return drawTriangleFan(vertices, color);
}



osg::ref_ptr<osg::Geometry> ViewUtils::drawPoints(osg::ref_ptr<osg::Vec3Array> vertices, const osg::Vec4& color)
{
    osg::ref_ptr<osg::Geometry> geom = drawGeometry(vertices, color, osg::PrimitiveSet::POINTS);
    constexpr float pointSize = 20.0;
    osg::ref_ptr<osg::Point> p = new osg::Point(pointSize);
    p->setDistanceAttenuation(osg::Vec3(0.0, 0.0000, 0.05f));
    geom->getOrCreateStateSet()->setAttribute(p, osg::StateAttribute::ON);
    return geom;
}



osg::ref_ptr<osg::Geometry> ViewUtils::drawLines(osg::ref_ptr<osg::Vec3Array> vertices, const osg::Vec4& color)
{
    return drawGeometry(vertices, color, osg::PrimitiveSet::LINES);
}



osg::ref_ptr<osg::Geometry> ViewUtils::drawLineLoop(osg::ref_ptr<osg::Vec3Array> vertices, const osg::Vec4& color)
{
    return drawGeometry(vertices, color, osg::PrimitiveSet::LINE_LOOP);
}



osg::ref_ptr<osg::Geometry> ViewUtils::drawTriangleFan(osg::ref_ptr<osg::Vec3Array> vertices, const osg::Vec4& color)
{
    return drawGeometry(vertices, color, osg::PrimitiveSet::TRIANGLE_FAN);
}



osg::ref_ptr<osg::Geometry> ViewUtils::drawQuads(osg::ref_ptr<osg::Vec3Array> vertices, const osg::Vec4& color)
{
    return drawGeometry(vertices, color, osg::PrimitiveSet::QUADS);
}



osg::ref_ptr<osg::ShapeDrawable> ViewUtils::drawCylinder(const osg::Vec3& pos, float radius, float height, const osg::Vec4& color)
{
    osg::ref_ptr<osg::Cylinder> cylinder = new osg::Cylinder(pos, radius, height);
    cylinder->setRotation(osg::Quat(M_PI/2, osg::X_AXIS));
    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(cylinder);
    shape->setColor(color);
    return shape;
}



osg::ref_ptr<osg::ShapeDrawable> ViewUtils::drawBox(const osg::Vec3& pos, float lengthX, float lengthY, float lengthZ, const osg::Vec4& color)
{
    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(new osg::Box(pos, lengthX, lengthY, lengthZ));
    shape->setColor(color);
    return shape;
}



osg::ref_ptr<osg::Geometry> ViewUtils::drawGeometry(osg::ref_ptr<osg::Vec3Array> vertices, const osg::Vec4& color, GLenum primitive)
{
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
    colors->push_back(color);

    geom->setVertexArray(vertices);
    geom->setColorArray(colors);
    geom->setColorBinding(osg::Geometry::BIND_OVERALL);
    geom->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF); // Turn off lighting
    geom->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON); // Turn on blending
    geom->addPrimitiveSet(new osg::DrawArrays(primitive, 0, vertices->size())); // Set geometry type
    return geom;
}
