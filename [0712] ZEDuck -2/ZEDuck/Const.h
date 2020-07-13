#pragma once

// DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN, DIR_END
const char ccDirKey[OBJ::DIR_END] = { 'A', 'D', 'W', 'S' };
const float cfDeltaX[OBJ::DIR_END] = { -1.f, 1.f, 0.f, 0.f };
const float cfDeltaY[OBJ::DIR_END] = { 0.f, 0.f, -1.f, 1.f };

// 플레이어 상수
const size_t ciPlayerSize = 50;
const float cfPlayerSpeed = 5.f;
const size_t ciPlayerMaxPower = 5;
const size_t ciPlayerMinPower = 1;
const size_t ciPlayerCollideMarginSpace = 17;
const float cfPlayerDegree = 0.f;

const float cfPlayerAttackRange = 100.f;
const float cfPlayerDamage = 50.f;

// 총알 상수
const size_t ciBulletSize = 8;
const float cfBulletSpeed = 10.f;
const float cfBulletDamage = 5.f;
const float cfBulletDegree = 90.f;
const float cfSubBulletDistance = 20.f;
const float cfSubBulletSpeed = 5.f;

// 몬스터 상수
const size_t ciMonsterSize = 50;
const float cfMonsterSpeed = 1.5f;
const float cfMonsterHp = 1000.f;
const float cfMonsterAttackRange = 100.f; // 50 점프
const float cfMonsterDetectRange = /*400.f*/ 400.f;

// 몬스터 총알 상수
const float cfMonsterBulletSpeed = 2.f;
const float cfMonsterBulletDamage = 5.f;
const float cfSlowAttackPatternSpeed = 2.f;

// 메테오 불렛 상수
const size_t ciMeteorSize = 60;
const float cfMeteorSpeed = 1.5f;
const float cfMeteorDamage = 5.f;
const float cfMeteorDegree = 90.f;


// 파티클 상수
const size_t ciParticleMaxSize = 9;
const size_t ciParticleMinSize = 4;
const float cfPopParticleMaxTime = 0.5f;
const float cfPopParticleMinTime = 0.05f;

// 쉴드 상수
const size_t ciShieldSize = 12;
const float cfShieldSpeed = 5.f;
const float cfShieldDistance = 50.f;

// 중력 상수
const float cfGravity = 2.f;

