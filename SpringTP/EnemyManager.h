#pragma once
#include<vector>
#include"DxLib.h"
#include"Meteor.h"
#include"Needle.h"
class EnemyManager
{
public:
	EnemyManager();
	virtual ~EnemyManager();

private:
	std::vector<EnemyBase*> enemy;

};

