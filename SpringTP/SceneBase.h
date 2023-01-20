#pragma once
class SceneBase
{
public:
    SceneBase();
    virtual ~SceneBase();
    virtual void Update() = 0;
    bool isEnd();

protected:
    bool endFlag;
};