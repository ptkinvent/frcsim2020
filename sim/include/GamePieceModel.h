/**
 * Copyright (c) 2020 FRC Team 3260
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
    enum IngestionState
    {
        NOT_INGESTED,
        CENTER_INGESTIBLE,
        LEFT_INGESTIBLE,
        RIGHT_INGESTIBLE,
        INGESTED
    };

    /**
     * Constructor
     */
    GamePieceModel(double radius, double x, double y) : _initialX(x), _initialY(y),
            _radius(radius), _state({ { x, y, 0, 0 } }) {};

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
        IngestionState ingestion;
    } _state;
};


#endif //ROBOT_SIM_GAMEPIECEMODEL_H
