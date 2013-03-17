/***********************************************************
Heart A Run
ZTY Studio
***********************************************************/

#ifndef HAR_SCENE_H
#define HAR_SCENE_H

class Scene {
public:
    virtual ~Scene() {}
    virtual bool Update() = 0;
};

#endif//HAR_SCENE_H
