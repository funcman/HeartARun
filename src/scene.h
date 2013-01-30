/***********************************************************
Heart A Run
ZTY Studio
***********************************************************/

// 场景抽象基类

#ifndef HAR_SCENE_H
#define HAR_SCENE_H

class Scene {
public:
    virtual ~Scene() {}
    virtual bool Update() = 0;  //每个场景都有处理更新的函数
};

#endif//HAR_SCENE_H
