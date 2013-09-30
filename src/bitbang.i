%module(directors="1") bitbang
%feature("director");

%include stl.i

%{
#include "bitbang/BBTypes.h"
%}
%include "bitbang/BBTypes.h"

%{
#include "bitbang/BBSchedule.h"
%}
%include "bitbang/BBSchedule.h"

%{
#include "bitbang/BBPoint.h"
%}
%include "bitbang/BBPoint.h"

%{
#include "bitbang/BBFeature.h"
%}
%include "bitbang/BBFeature.h"

%{
#include "bitbang/BBObject.h"
%}
%include "bitbang/BBObject.h"

%{
#include "bitbang/BBAgentInterface.h"
%}
%include "bitbang/BBAgentInterface.h"

%{
#include "bitbang/BBAction.h"
%}
%include "bitbang/BBAction.h"

%{
#include "bitbang/BBPerception.h"
%}
%include "bitbang/BBPerception.h"

%{
#include "bitbang/BBPerceptionSphere.h"
%}
%include "bitbang/BBPerceptionSphere.h"

%{
#include "bitbang/BBVisionReach3DCone.h"
%}
%include "bitbang/BBVisionReach3DCone.h"

%{
#include "bitbang/BBBrain.h"
%}
%include "bitbang/BBBrain.h"

%{
#include "bitbang/BBAgent.h"
%}
%include "bitbang/BBAgent.h"

%{
#include "bitbang/BBThing.h"
%}
%include "bitbang/BBThing.h"

%{
#include "bitbang/BBWorld.h"
%}
%include "bitbang/BBWorld.h"

%{
#include "bitbang/BBSchedule.h"
%}
%include "bitbang/BBSchedule.h"

%{
#include "bitbang/BBOS.h"
%}
%include "bitbang/BBOS.h"

%{
#include "bitbang/schedules/BBScheduleScriptable.h"
%}
%include "bitbang/schedules/BBScheduleScriptable.h"

%{
#include "bitbang/gridbrain/IGBComponent.h"
%}
%include "bitbang/gridbrain/IGBComponent.h"

%{
#include "bitbang/gridbrain/BBGBAction.h"
%}
%include "bitbang/gridbrain/BBGBAction.h"

%{
#include "bitbang/gridbrain/BBGBComponentAction.h"
%}
%include "bitbang/gridbrain/BBGBComponentAction.h"

%{
#include "bitbang/gridbrain/BBGBComponentMul.h"
%}
%include "bitbang/gridbrain/BBGBComponentMul.h"

%{
#include "bitbang/gridbrain/BBGBComponentNot.h"
%}
%include "bitbang/gridbrain/BBGBComponentNot.h"

%{
#include "bitbang/gridbrain/BBGBComponentThreshold.h"
%}
%include "bitbang/gridbrain/BBGBComponentThreshold.h"

%{
#include "bitbang/gridbrain/BBGBComponentMax.h"
%}
%include "bitbang/gridbrain/BBGBComponentMax.h"

%{
#include "bitbang/gridbrain/BBGBComponentPerception.h"
%}
%include "bitbang/gridbrain/BBGBComponentPerception.h"

%{
#include "bitbang/gridbrain/BBGBConnection.h"
%}
%include "bitbang/gridbrain/BBGBConnection.h"

%{
#include "bitbang/gridbrain/BBGBGrid.h"
%}
%include "bitbang/gridbrain/BBGBGrid.h"

%{
#include "bitbang/gridbrain/BBGBPerception.h"
%}
%include "bitbang/gridbrain/BBGBPerception.h"

%{
#include "bitbang/gridbrain/BBGBPerceptionWithParameter.h"
%}
%include "bitbang/gridbrain/BBGBPerceptionWithParameter.h"

%{
#include "bitbang/gridbrain/BBGridBrain.h"
%}
%include "bitbang/gridbrain/BBGridBrain.h"

