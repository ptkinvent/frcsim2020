/**
 * Copyright (c) 2020 Team 3260
 */

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include "ViewUtils.h"


osg::ref_ptr<osg::Geometry> ViewUtils::makeLines(osg::ref_ptr<osg::Vec3Array> vertices, const osg::Vec4& color)
{
    return makeBaseGeometry(vertices, color, osg::PrimitiveSet::LINES);
}



osg::ref_ptr<osg::Geometry> ViewUtils::makeLineLoop(osg::ref_ptr<osg::Vec3Array> vertices, const osg::Vec4& color)
{
    return makeBaseGeometry(vertices, color, osg::PrimitiveSet::LINE_LOOP);
}



osg::ref_ptr<osg::Geometry> ViewUtils::makeTriangleFan(osg::ref_ptr<osg::Vec3Array> vertices, const osg::Vec4& color)
{
    return makeBaseGeometry(vertices, color, osg::PrimitiveSet::TRIANGLE_FAN);
}



osg::ref_ptr<osg::Geometry> ViewUtils::makeQuads(osg::ref_ptr<osg::Vec3Array> vertices, const osg::Vec4& color)
{
    return makeBaseGeometry(vertices, color, osg::PrimitiveSet::QUADS);
}



osg::ref_ptr<osg::ShapeDrawable> ViewUtils::makeCylinder(const osg::Vec3& pos, float radius, float height, const osg::Vec4& color)
{
    osg::ref_ptr<osg::Cylinder> cylinder = new osg::Cylinder(pos, radius, height);
    cylinder->setRotation(osg::Quat(M_PI/2, osg::X_AXIS));
    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(cylinder);
    shape->setColor(color);
    return shape;
}



osg::ref_ptr<osg::ShapeDrawable> ViewUtils::makeBox(const osg::Vec3& pos, float lengthX, float lengthY, float lengthZ, const osg::Vec4& color)
{
    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(new osg::Box(pos, lengthX, lengthY, lengthZ));
    shape->setColor(color);
    return shape;
}



osg::ref_ptr<osg::Geometry> ViewUtils::makeBaseGeometry(osg::ref_ptr<osg::Vec3Array> vertices, const osg::Vec4& color, GLenum primitive)
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
