
// matrix indexes
#define PLAYER_MAT_BEGIN	0
#define PLAYER_MAT_END		3
#define TOWER_MAT_BEGIN		4
#define TOWER_MAT_END		9
#define CAM_MAT_BEGIN		10
#define CAM_MAT_END			13
#define PPDL_MAT			14
#define PLATFORM_BEGIN      15     
#define PLATFORM_END		19
#define GLOBAL				20
#define PLATFORM_STATUS		21

//player bit info
#define SHOOTBIT			1
#define DAMAGEDBIT			2
#define KILLEDBIT			3
#define SHOOT_ID_BEGIN		4
#define SHOOT_ID_END		6

#define NOPOWER				0
#define SPEEDUP				1
#define DOUBLEDAMAGE		2
#define HEALTHBOOST			3
#define FASTERSHOOT			4
#define FARTHERSHOOT		5

#define PLAYER0				0
#define PLAYER1				1
#define PLAYER2				2
#define PLAYER3				3

#define VECSPERPLAYER		4
#define RECVINDEXP0			0
#define RECVINDEXP1			4
#define RECVINDEXP2			8
#define RECVINDEXP3			12

// base0 location
#define ORIGINX0			0
#define ORIGINY0			10
#define ORIGINZ0			130

// base1 location
#define ORIGINX1			0
#define ORIGINY1			10
#define ORIGINZ1			-130

// base parameters
#define PERIMETER_WALL_RADIUS 35
#define PERIMETER_WALL_HEIGHT 5
#define CENTER_TOWERPLAT_HEIGHT 15
#define CENTER_PLAT_SPACING   10
#define CENTER_PLAT_HEIGHT    10

// object types
#define CUBE 0
#define MODEL 1
#define GROUND 2
#define ELEVATOR 3
#define TELEPORTER 4
#define TRAMPOLINE 5
