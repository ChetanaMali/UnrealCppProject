#pragma once
#include "DrawDebugHelpers.h"

#define DRAW_SPHERE(Location) if (GetWorld()) DrawDebugSphere(GetWorld(),Location,20.f, 30.f, FColor::Red, true);//Macro Creation
//I Do this Single frame because i want to move sphere  in world offset using event tick 
#define DRAW_SINGLE_FRAME_SPHERE(Location) if (GetWorld()) DrawDebugSphere(GetWorld(),Location,20.f, 30.f, FColor::Red, false, -1.f);//Macro Creation
#define DRAW_LINE(StartLoc, EndLoc) if(GetWorld()) DrawDebugLine(GetWorld(),StartLoc, EndLoc, FColor::Red,true,-1.f,0.f,0.5f);
#define DRAW_SINGLE_FRAME_LINE(StartLoc, EndLoc) if(GetWorld()) DrawDebugLine(GetWorld(),StartLoc, EndLoc, FColor::Red,false,-1.f,0.f,0.5f);
#define DRAW_POINT(Location) if(GetWorld()) DrawDebugPoint(GetWorld(),Location,10.f, FColor::Red,true);
#define DRAW_SINGLE_FRAME_POINT(Location) if(GetWorld()) DrawDebugPoint(GetWorld(),Location,10.f, FColor::Red,false,-1.f);

#define DRAW_VECTOR(StartLoc, EndLoc)\
if(GetWorld())\
{\
	DrawDebugLine(GetWorld(),StartLoc, EndLoc, FColor::Red,true,-1.f,0.f,0.5f);\
	DrawDebugPoint(GetWorld(), EndLoc,10.f, FColor::Red,true);\
}
#define DRAW_SINGLE_FRAME_VECTOR(StartLoc, EndLoc)\
if (GetWorld())\
{\
DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, false, -1.f, 0.f, 0.5f); \
DrawDebugPoint(GetWorld(), EndLoc, 10.f, FColor::Red, false,-1.f);\
}