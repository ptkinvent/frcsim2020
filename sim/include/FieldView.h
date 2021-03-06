/**
 * Copyright (c) 2020 FRC Team 3260
 */

#pragma once

#include <osg/PositionAttitudeTransform>
#include "ConfigReader.h"
#include "Types.h"


class FieldView : public osg::PositionAttitudeTransform
{
public:
    /**
     * Constructor
     */
    FieldView(const ConfigReader& config);

    /**
     * Updates the field view based on the field model
     */
    void update(const SimState::FieldState& state);

private:
    /**
     * Draws the ground plane as a gray rectangle
     */
    osg::ref_ptr<osg::Geode> drawGround(const ConfigReader& config);

    /**
     * Draws the bounding collision polygon of the field as green walls
     */
    osg::ref_ptr<osg::Geode> drawBoundary(const ConfigReader& config);

    /**
     * Draws the goal regions as red and blue outlined regions
     */
    osg::ref_ptr<osg::Geode> drawGoals(const ConfigReader& config);

    /**
     * Draws the outtakes as red and blue squares on the field walls
     */
    osg::ref_ptr<osg::Geode> drawOuttakes(const ConfigReader& config);

private:
    osg::ref_ptr<osg::Node> _fieldNode;
    osg::ref_ptr<osg::Geode> _fieldBounds;
};
