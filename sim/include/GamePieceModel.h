/**
 * Copyright (c) 2019 FRC Team 3260
 */

#ifndef ROBOT_SIM_GAMEPIECEMODEL_H
#define ROBOT_SIM_GAMEPIECEMODEL_H

#include "ConfigReader.h"
#include "BaseModel.h"


class GamePieceModel : public BaseModel
{
friend class GamePieceView;
friend class PhysicsEngine;
public:
    /**
     * Constructor
     */
    GamePieceModel(const ConfigReader& configReader, double x=0, double y=0) : _initialX(x), _initialY(y),
            _radius(configReader.sim.constants.gamePiece.radius), _state({ { x, y, 0, 0 } }) {};

    /**
     * Reset
     */
    void reset()
    {
        _state = { _initialX, _initialY, 0, 0 };
    }

    /**
     * Return the model type
     */
    virtual ModelType modelType() { return GAME_PIECE_MODEL; }

    /**
     * Collision callback
     */
    virtual void isInCollision(bool c) {};

private:
    double _radius;
    double _initialX;
    double _initialY;

    struct
    {
        struct
        {
            double x, y;
            double vx, vy;
        } pose;
    } _state;
};


#endif //ROBOT_SIM_GAMEPIECEMODEL_H
